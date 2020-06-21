#include "CardDetector.h"

#include <iostream>


namespace detect
{


	CardDetector::CardDetector(std::shared_ptr<shared::ImProcSettings>& data_gui, std::shared_ptr<shared::DataPokerDetect>& data_poker, std::shared_ptr<shared::DefaultConfig>& default_config) :
		cards_{}, card_buffers_{}, frame_nr_(0), live_frame_{}, data_gui_(data_gui), data_poker_(data_poker)
	{
		// get default parameters
		this->card_width_ = default_config->card_width;
		this->card_aspect_ratio_ = default_config->card_aspect_ratio;							 // Aspect Ratio of real playing cards
		this->min_card_size_ = default_config->min_card_size;									 // Min size card image in pixel²
		this->max_card_size_ = default_config->max_card_size;								 // Max size card image in pixel²
		this->min_comparison_confidence_ =  default_config->min_comparison_confidence;						 // Maximum l2 error allowed for compareImages. If error is higher, card is marked as unknown			
		this->perspective_transform_offset_ = default_config->perspective_transform_offset;
		this->zoom_width_ratio_ = default_config->zoom_width_ratio;
		this->zoom_height_ratio_ = default_config->zoom_height_ratio;
		this->max_rank_contour_ratio_ = default_config->max_rank_contour_ratio;
		this->rank_suit_zoom_offset_ = default_config->rank_suit_zoom_offset;
			
		// reserve space for train images, these should be 13 ranks and 4 suits
		this->train_ranks_.reserve(13);
		this->train_ranks_.reserve(4);

		loadTrainImages("C:\\Users\\julim\\Desktop\\Projects\\Pokerbot\\Card_Imgs\\ranks\\*.jpg", this->train_ranks_);
		loadTrainImages("C:\\Users\\julim\\Desktop\\Projects\\Pokerbot\\Card_Imgs\\suits\\*.jpg", this->train_suits_);
	}

	CardDetector::~CardDetector()
	{
	}

	void CardDetector::updateFrame(const Image& input_frame)
	{
		// Clone (deep copy) live frame from camera view. We are changing the data of this cv::Mat in the Processing steps and do not want to change the original frame
		this->live_frame_ = input_frame;
		++this->frame_nr_;
	}
	
	//@brief: Detect Cards in live frame 
	void CardDetector::detectCards()
	{
		this->cards_.clear();
		// Step 1	: Find Contours of cards in frame
		// Step	1.1 : Find Contours of interest in frame	
		std::vector<std::vector<cv::Point> > card_contours;	
			
		ImProc::findContours(this->live_frame_.image, card_contours, this->data_gui_->live_threshold);

		// Step 1.2 : Filter Contours by area to get rid of contours that are too small or large to be a card, 
		// -> min_ and max_card size were determined empirically, and depend on camera positioning
		ImProc::contourFilter(card_contours, ImProc::GE_AREA, this->min_card_size_);
		ImProc::contourFilter(card_contours, ImProc::LE_AREA, this->max_card_size_);

		// Step 1.3 : Find corner points and center points of contours
		std::vector < std::vector< cv::Point2f >> card_corners;
		std::vector< cv::Point2f > card_centers;
		ImProc::calculateCornerPoints(card_contours, card_corners);
		ImProc::calculateCenterPoint(card_contours, card_centers);
		
		// Step 1.4 :  Rewarp cards to correct perspective errors:
		// This could be transformed to multithreading later
		int count = 0;
		
		cv::Mat card_image;
		std::vector< cv::Point2f > sorted_corners;
		for (const auto& contour : card_contours)
		{
			card_image.create(cv::Size(this->card_width_, static_cast<int>(this->card_width_*this->card_aspect_ratio_)), this->live_frame_.image.type());
			
			//Sort corners according to what is expected by image transformation method. Start lower right corner -> going clockwise
			sorted_corners=ImProc::sortCorners(card_corners.at(count), card_centers.at(count));
			bool transform_result = ImProc::perspectiveTransformation(this->live_frame_.image, card_image, sorted_corners, this->perspective_transform_offset_);

			if (!transform_result)
			{
				card_image.release();
				sorted_corners.clear();
				break;
			}			
			
			Card card_tmp;
			card_tmp.contour = contour;
			card_tmp.center_point = card_centers.at(count);
			card_tmp.card_image.image=card_image;

			this->identifyCard(card_tmp, card_image);
			this->bufferCard(card_tmp);			
			this->cards_.emplace_back(card_tmp);
			card_image.release();								// clear card_image
			std::vector< cv::Point2f > ().swap(sorted_corners);	// clear and reallocate sorted_corners
			++count;
		}

		for(auto p = this->card_buffers_.begin(); p != this->card_buffers_.end(); ++p)
		{
			Card card_tmp;
			// only use buffers that were updated in the last 3 frames
			if((*p).getLastUpdate() >= this->frame_nr_-3 && (*p).getCard(card_tmp))
			{				
				this->cards_.emplace_back(card_tmp);
			}	
			// remove buffers unused within the last 3 frames
			else if((*p).getLastUpdate() <= this->frame_nr_-3)
			{				
				// p mus be decremented after erase is called, as p is invalidated by erase
				this->card_buffers_.erase(p--);
			}			
			else
			{
					//do nothing
			}
			
		}	

		// assign cards to robot or public cards
		this->assignCards();	
	}

	// @brief: load training images for comparison with detected images
	void CardDetector::loadTrainImages(const std::string &path, std::vector<TrainImage>& train_images)
	{	
		std::vector<std::string> file_names{};
		cv::glob(path, file_names, false);		
		if (file_names.size() == 0) { // check if input could be read 
			return;
		}		
		for (const std::string &file_name: file_names) {
			train_images.emplace_back(TrainImage{ file_name });
		}
		
	}

	//@brief: Identifies what card is shown in card image
	//@brief: Card image is binarized and upper right corner is zoomed in
	//@brief: Upper right corner is then compared from train images using L2 Norm
	//@brief: Lowest difference wins.
	void CardDetector::identifyCard(Card& card, const cv::Mat& card_image) 
	{
		// Zoom into the upper left corner
		int zoom_width = static_cast<int>(this->card_width_ * this->zoom_width_ratio_);
		int zoom_height = static_cast<int>(static_cast<double>(this->card_width_)*this->card_aspect_ratio_ * this->zoom_height_ratio_);
		cv::Rect zoom(this->rank_suit_zoom_offset_, this->rank_suit_zoom_offset_, zoom_width, zoom_height);
		cv::Mat card_zoom = card_image(zoom).clone();

		// find contours in the zoomed in image giving rank and suit contours
		std::vector<std::vector<cv::Point> > contours;
		ImProc::findContours(card_zoom, contours, this->data_gui_->identification_threshold, cv::THRESH_BINARY);
	
		// filter suit and rank image contours by area. 
		double max_size = zoom_width * zoom_height * this->max_rank_contour_ratio_;
		double min_size = zoom_width;
		ImProc::contourFilter(contours, LE_AREA, max_size);
		ImProc::contourFilter(contours, GE_AREA, min_size);

		// get bounding boxes of the contours
		std::vector<cv::Rect> bounding_box;
		for (const auto & contour: contours) {
			bounding_box.emplace_back(cv::boundingRect(contour));
		}
		
		// Identify suit and Rank of card
		if (bounding_box.size() > 1)
		{

			double score_suit{ 1000.0 };
			double score_rank{ 1000.0 };
			Mapping mapping;
			cv::Mat rank, suit;
			
			// sort contours for size. Rank should have the largest bounding box, whereas suit should have the second largest
			std::sort(bounding_box.begin(), bounding_box.end(), [](const cv::Rect& lhs, const cv::Rect& rhs){return lhs.area() > rhs.area();});
			rank = card_zoom(bounding_box.at(0)).clone();
			suit = card_zoom(bounding_box.at(1)).clone();
		
			for (auto const& threshold : sliding_threshold_)
			{
				cv::Mat rank_binary, suit_binary;

				// Binarize rank and suit image
			
				rank_binary.create(this->train_ranks_[0].getImage().size(), this->train_ranks_[0].getImage().type());
				suit_binary.create(this->train_suits_[0].getImage().size(), this->train_suits_[0].getImage().type());

				cv::resize(rank, rank, rank_binary.size(), 0, 0, cv::INTER_LINEAR);				// resize to right size befor binarizing
				ImProc::binarizeImage(rank, rank_binary, this->data_gui_->binary_threshold + threshold, cv::THRESH_BINARY_INV);
				
				cv::resize(suit, suit, suit_binary.size(), 0, 0, cv::INTER_LINEAR); 			// resize to right size befor binarizing
				ImProc::binarizeImage(suit, suit_binary, this->data_gui_->binary_threshold + threshold, cv::THRESH_BINARY_INV);
				card.rank_image.image = rank_binary;
				card.suit_image.image = suit_binary;
 
				// Compare to train images
				// This could potentially be parallelized 
				int rank_count = 0;
				for (auto &train_rank : this->train_ranks_)
				{
					double tmp_score=ImProc::compareImages(rank_binary, train_rank.getImage());
					if (tmp_score < score_rank)
					{
						score_rank = tmp_score;
						std::string rank_name = this->train_ranks_[rank_count].getLabel();	
						if (score_rank < this->min_comparison_confidence_)
						{
							card.rank = mapping.image_mappings.left.at(rank_name);
						}
						else
						{
							card.rank = UNKNOWN;
						}
					}
					rank_count++;
				}

				int suit_count = 0;
				for (auto &train_suit : this->train_suits_)
				{
					double tmp_score=ImProc::compareImages(suit_binary, train_suit.getImage());
					if (tmp_score < score_suit)
					{
						score_suit = tmp_score;
						std::string suit_name = this->train_suits_[suit_count].getLabel();
						if (score_suit < this->min_comparison_confidence_)
						{
							card.suit = mapping.image_mappings.left.at(suit_name);
						}
						else
						{
							card.suit = UNKNOWN;
						}
					}
					suit_count++;
				}							
			}
						
		}
		else 
		{
			card.rank = UNKNOWN;
			card.suit = UNKNOWN;
		}
	}

	void CardDetector::bufferCard(const Card& card)
	{
		if(this->card_buffers_.size() == 0)
		{
			this->card_buffers_.emplace_back(CardBuffer<CARD_BUFFER_SIZE>(card, this->frame_nr_));
		}
		else
		{
			// calculate squared distances of card to known buffers
			std::vector<double> squared_distances;
			for(const auto& buffer: this->card_buffers_)
			{
				squared_distances.emplace_back(templates::squaredEuclideanDistance2D(buffer.getCenter(), card.center_point));
			}

			// find min distance and add card to that buffer, if the distance is small enough. Otherwise it is a new card and a new buffer is created
			auto p = std::min_element(squared_distances.begin(), squared_distances.end());
			auto pos = std::distance(squared_distances.begin(), p);

			if( *p < MAX_DISTANCE_TO_BUFFER*MAX_DISTANCE_TO_BUFFER)
			{
				this->card_buffers_.at(pos).put(card, this->frame_nr_);
			}
			else
			{
				this->card_buffers_.emplace_back(CardBuffer<CARD_BUFFER_SIZE>(card, this->frame_nr_));
			}			
		}
	}

	// @brief: assigns detected cards to robot cards and public cards
	void CardDetector::assignCards()
	{
		this->data_gui_->public_cards.clear();
		this->data_gui_->robot_cards.clear();

		this->data_poker_->public_cards.clear();
		this->data_poker_->robot_cards.clear();

		for(const auto& card: this->cards_)
		{	
				if(card.rank != UNKNOWN && card.suit != UNKNOWN && isInArea(card, this->data_gui_->robot_area)
					&& !templates::contains(this->data_gui_->robot_cards.begin(), this->data_gui_->robot_cards.end(), card))
				{
					if(this->data_gui_->robot_cards.size()<2)
					{
						// assign cards to shared data with gui (plotting only) and simulation
						this->data_gui_->robot_cards.emplace_back(card);
						//the card object is slized here to BaseCard, which is sufficient in poker simulation. 
						this->data_poker_->robot_cards.emplace_back(card);
					}
				}
				else if(card.rank != UNKNOWN && card.suit != UNKNOWN && isInArea(card, this->data_gui_->public_area) &&
						!templates::contains(this->data_gui_->public_cards.begin(), this->data_gui_->public_cards.end(), card))
				{
					if(this->data_gui_->public_cards.size() < 5)
					{
						// assign cards to shared data with gui (plotting only) and simulation
						this->data_gui_->public_cards.emplace_back(card);
						//the card object is slized here to BaseCard, which is sufficient in poker simulation. 
						this->data_poker_->public_cards.emplace_back(card);
					}
				}
				else
				{
					//do nothing
				}	
		}		
	}


	bool CardDetector::isInArea(const Card& card, const cv::Rect& area)
	{

		if(card.center_point.x > area.x && card.center_point.x < area.x + area.width 
			&& card.center_point.y > area.y && card.center_point.y < area.y + area.height)
		{
			return true;
		}
		return false;
	}
}// namespace detect