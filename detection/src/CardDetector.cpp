#include "CardDetector.h"

#include <iostream>


namespace detect
{


	CardDetector::CardDetector() : cards_{}, card_buffers_{}, frame_nr_(0)
	{
		loadTrainImages("C:\\Users\\julim\\Desktop\\Projects\\Pokerbot\\Card_Imgs\\ranks_new\\*.jpg", this->train_ranks_);
		loadTrainImages("C:\\Users\\julim\\Desktop\\Projects\\Pokerbot\\Card_Imgs\\suits_new\\*.jpg", this->train_suits_);
	}

	CardDetector::~CardDetector()
	{
	}

	void CardDetector::updateFrame(const cv::Mat& input_frame)
	{
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
			
		this->findContours(this->live_frame_, card_contours, this->live_threshold_);

		// Step 1.2 : Filter Contours by area to get rid of contours that are too small or large to be a card, 
		// -> min_ and max_card size were determined empirically, and depend on camera positioning
		this->contourFilter(card_contours, GE_AREA, this->min_card_size_);
		this->contourFilter(card_contours, LE_AREA, this->max_card_size_);

		// Step 1.3 : Find corner points and center points of contours
		std::vector < std::vector< cv::Point2f >> card_corners;
		std::vector< cv::Point2f > card_centers;
		this->calculateCornerPoints(card_contours, card_corners);
		this->calculateCenterPoint(card_contours, card_centers);
		
		// Step 1.4 :  Rewarp cards to correct perspective errors:
		// This should be transformed to multithreading later
		int count = 0;
		
		cv::Mat card_image;
		std::vector< cv::Point2f > sorted_corners;
		for (const auto& contour : card_contours)
		{
			card_image.create(cv::Size(this->card_width_, static_cast<int>(this->card_width_*this->aspect_ratio_)), this->live_frame_.type());
			//Sort corners according to what is expected by image transformation method. Start lower right corner -> going clockwise
			sorted_corners=this->sortCorners(card_corners.at(count), card_centers.at(count));
			bool transform_result = this->perspectiveTransformation(this->live_frame_, card_image, sorted_corners);

			if (!transform_result)
			{
				card_image.release();
				sorted_corners.clear();
				break;
			}
			
			Card card_tmp;
			card_tmp.contour = contour;
			card_tmp.center_point = card_centers.at(count);
			this->identifyCard(card_tmp, card_image);
			this->bufferCard(card_tmp);			

			card_image.release();								// clear card_image
			std::vector< cv::Point2f > ().swap(sorted_corners);	// clear and reallocate sorted_corners
			++count;
		}

		for(auto p = this->card_buffers_.begin(); p != this->card_buffers_.end(); ++p)
		{
			Card card_tmp;
			// only use buffers that were updated in this frame
			if((*p).getLastUpdate() == this->frame_nr_ && (*p).getCard(card_tmp))
			{				
				this->cards_.emplace_back(card_tmp);
			}	
			// remove unused buffers
			else if((*p).getLastUpdate() != this->frame_nr_)
			{				
				// p mus be decremented after erase is called, as p is invalidated by erase
				this->card_buffers_.erase(p--);
			}			
			else
			{
					//do nothing
			}
		}	
	
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

	// @brief: finds contours in given image src for given binaryzation threshold and given binarization method 
	void CardDetector::findContours(const cv::Mat& src, std::vector<std::vector<cv::Point> >& contours, const int& threshold, const int& thresh_method)
	{
		cv::Mat edges;
		std::vector<cv::Vec4i> hierarchy;
		this->binarizeImage(src, edges, threshold, thresh_method);
		cv::findContours(edges, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_NONE, cv::Point(0, 0));
	}

	// @brief: filters contours after given method. Value ist given according to method
	// @brief: Methods are 
	// @brief: LARGEST_AREA = 0, only keept largest contour
	// @brief: SMALLEST_AREA = 1, only keep smalles contour 
	// @brief: LE_AREA = 2, contour area is smaller/equal then given value
	// @brief: GE_AREA =3 , contour area is larger/equal then given value 
	void CardDetector::contourFilter(std::vector<std::vector<cv::Point> >& contours, int method, double value)
	{
		// Calculate area vector first
		std::vector<double> areas(contours.size());
		int i = 0;
		for (std::vector<cv::Point> contour : contours)
		{
			areas[i]=cv::contourArea(contour, false);
			++i;
		}

		std::vector<std::vector<cv::Point> > filtered_contours;
		// Filter Contours according to method
		if (method == LARGEST_AREA || method == SMALLEST_AREA)
		{
			// Only keep largest contour
			std::vector<double>::iterator pos;
			if (method == LARGEST_AREA)
			{
				pos = std::max_element(areas.begin(), areas.end());
			}
			// Only keep smallest contour
			else
			{
				pos = std::min_element(areas.begin(), areas.end());
			}
			filtered_contours.emplace_back(contours[std::distance(areas.begin(), pos)]);
		}
		// Filter contours by area value
		else
		{
			for (auto it = areas.begin(); it != areas.end(); ++it)
			{
				if ((method == GE_AREA && *it >= value) || (method == LE_AREA && *it <= value))
				{
					filtered_contours.emplace_back(contours[std::distance(areas.begin(), it)]);
		
				}
			}
		}

		contours.clear();
		for (auto const &contour : filtered_contours)
		{
			contours.emplace_back(contour);
		}

	}
	//@brief: calculates corner points of given contours using cv::approxPolyDP
	void CardDetector::calculateCornerPoints(const std::vector<std::vector<cv::Point> >& contours, std::vector < std::vector< cv::Point2f >>& corners)
	{
		double d = 0.01;

		for (auto const &contour : contours)
		{
			std::vector<cv::Point2f> corner_points;
			do
			{
				d = d + 1;
				cv::approxPolyDP(contour, corner_points, d, true);

			} while (corner_points.size() > 4);
			if (corner_points.size() > 0)
			{
				corners.emplace_back(corner_points);
			}
		}
	}

	//@brief: Returns Center Point of contour using the contour moments, calculated with cv::moments
	void CardDetector::calculateCenterPoint(const std::vector<std::vector<cv::Point> >& contours, std::vector< cv::Point2f >& centers)
	{
		cv::Moments M;
		for (auto const &contour : contours)
		{
			M = cv::moments(contour);
			centers.emplace_back(cv::Point2f((M.m10 / M.m00), (M.m01 / M.m00)));
		}
	
	}

	//@brief: Transforms perspectively distorted card image into 2D upright view of card
	bool CardDetector::perspectiveTransformation(const cv::Mat src, cv::Mat& dst, const std::vector< cv::Point2f >& points)
	{
		int offset = 5;
		std::vector<cv::Point2f> ImageCorners = { cv::Point2f(dst.size().width - offset, +offset),cv::Point2f(+offset , +offset),							// Points to transform to, corners of cards.image
			cv::Point2f(+offset , dst.size().height - offset), cv::Point2f(dst.size().width - offset, dst.size().height - offset) };

		if (ImageCorners.size() == points.size())
		{
			cv::Mat M = cv::getPerspectiveTransform(points, ImageCorners);
			cv::warpPerspective(src, dst, M, dst.size());
			return true;
		}

		return false;
	}

	//@brief: sorts corner points given by calculateCornerPoints method to order expected by perspectiveTransformation. 
	//@brief: Start lower right corner -> going clockwise
	std::vector< cv::Point2f > CardDetector::sortCorners(std::vector< cv::Point2f > points, cv::Point2f center)
	{
		std::vector< cv::Point2f > sorted_points;

		int count = 0;
		do
		{
			for (auto point : points)
			{
				switch (sorted_points.size())
				{
				case 0:
				{
					if (point.x > center.x && point.y < center.y) {
						sorted_points.emplace_back(point);
					}
					break;
				}
				case 1:
				{
					if (point.x < center.x && point.y < center.y) {
						sorted_points.emplace_back(point);
					}
					break;
				}
				case 2:
				{
					if (point.x < center.x && point.y > center.y) {
						sorted_points.emplace_back(point);
					}
					break;
				}
				case 3:
				{
					if (point.x > center.x && point.y > center.y) {
						sorted_points.emplace_back(point);
					}
					break;
				}
				}
			}
			++count;
		} while (count < 4);
		if (sorted_points.size() < 4)
		{
			sorted_points = points;
			return sorted_points;
		}

		return sorted_points;
	}

	//@brief: Identifies what card is shown in card image
	//@brief: Card image is binarized and upper right corner is zoomed in
	//@brief: Upper right corner is then compared from train images using L2 Norm
	//@brief: Lowest difference wins.
	void CardDetector::identifyCard(Card& card, const cv::Mat& card_image) 
	{
		// Zoom into the upper left corner
		int zoom_width = this->card_width_ / 6;
		int zoom_height = static_cast<int>(static_cast<double>(this->card_width_)*this->aspect_ratio_ / 2.5);
		cv::Rect zoom(0, 0, zoom_width, zoom_height);
		cv::Mat card_zoom = card_image(zoom).clone();
		// find contours in the zoomed in image giving rank and suit contours
		std::vector<std::vector<cv::Point> > contours;
		this->findContours(card_zoom, contours, this->card_threshold_, cv::THRESH_BINARY);
		// filter suit and rank image contours by area. Sizes were found empirically
		double max_size = zoom_width * zoom_height * 0.8;
		double min_size = zoom_width;
		this->contourFilter(contours, LE_AREA, max_size);
		this->contourFilter(contours, GE_AREA, min_size);

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
			rank = card_zoom(bounding_box[1]).clone();
			suit = card_zoom(bounding_box[0]).clone();

			for (auto const& threshold : sliding_threshold_)
			{
				cv::Mat rank_binary, suit_binary;

				// Binarize rank and suit image
			
				rank_binary.create(this->train_ranks_[0].getImage().size(), this->train_ranks_[0].getImage().type());
				suit_binary.create(this->train_suits_[0].getImage().size(), this->train_suits_[0].getImage().type());

				cv::resize(rank, rank, rank_binary.size(), 0, 0, cv::INTER_LINEAR);				// resize to right size befor binarizing
				this->binarizeImage(rank, rank_binary, this->binary_threshold_ + threshold, cv::THRESH_BINARY_INV);
				
				cv::resize(suit, suit, suit_binary.size(), 0, 0, cv::INTER_LINEAR); 			// resize to right size befor binarizing
				this->binarizeImage(suit, suit_binary, this->binary_threshold_ + threshold, cv::THRESH_BINARY_INV);

				// Compare to train images
				// This could potentially be parallelized 
				int rank_count = 0;
				for (auto &train_rank : this->train_ranks_)
				{
					double tmp_score=this->compareImages(rank_binary, train_rank.getImage());
					if (tmp_score < score_rank)
					{
						score_rank = tmp_score;
						std::string rank_name = this->train_ranks_[rank_count].getLabel();	
						if (rank_name == "Ten_2")
						{
							rank_name = "Ten";
						}

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
					double tmp_score=this->compareImages(suit_binary, train_suit.getImage());
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

	//@brief: binarize given image 
	void CardDetector::binarizeImage(const cv::Mat & src, cv::Mat & dst, const int& threshold, const int& thresh_method)
	{
		cv::cvtColor(src, dst, cv::COLOR_RGB2GRAY);
		cv::Scalar temp_mean = cv::mean(dst);											// calculates mean image intensity. will be added to threshold to correct for lighting
		int mean_image_intensity = static_cast<int>(temp_mean[0]);
		cv::threshold(dst, dst, mean_image_intensity + threshold, 255, thresh_method);
	}

	//@brief: Compares given images using L2_Norm and returns similarity
	double CardDetector::compareImages(const cv::Mat &src, const cv::Mat &dst)
	{
		if (src.size() == dst.size() && src.type() == dst.type())
		{
			 // Calculate the L2 relative error between images.
			double errorL2 = cv::norm(src, dst, cv::NORM_L2);
			// Convert to a reasonable scale, since L2 error is summed across all pixels of the image.
			double similarity = errorL2 / static_cast<double>(src.rows * src.cols);
			return similarity;
		}
		else
		{
			return { -1 };
		}

	}

	void CardDetector::bufferCard(const Card& card)
	{
		if(this->card_buffers_.size() == 0)
		{
			this->card_buffers_.emplace_back(CardBuffer<globals::CARD_BUFFER_SIZE>(card, this->frame_nr_));
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

			if( *p < globals::MAX_DISTANCE_TO_BUFFER*globals::MAX_DISTANCE_TO_BUFFER)
			{
				this->card_buffers_.at(pos).put(card, this->frame_nr_);
			}
			else
			{
				this->card_buffers_.emplace_back(CardBuffer<globals::CARD_BUFFER_SIZE>(card, this->frame_nr_));
			}			
		}
	}
}// namespace detect