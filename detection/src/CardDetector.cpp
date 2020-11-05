#include "CardDetector.hpp"

namespace detect{

    void CardDetector::updateFrame(const Image& input_frame)
    {
        this->live_frame_ = input_frame;
        ++this->frame_nr_;
    }    

	// @brief: Add Card to a CardBuffer. For more information on the why we use
	// 		   CardBuffers, see CardBuffer.hpp
    void CardDetector::bufferCard(const Card& card)
	{
		if(this->card_buffers_.size() == 0)
		{
			this->card_buffers_.emplace_back(
                CardBuffer<CARD_BUFFER_SIZE>(card, this->frame_nr_)
                );
		}
		else
		{
			// calculate squared distances of card to known buffers
			std::vector<double> squared_distances;
			for(const auto& buffer: this->card_buffers_)
			{
				squared_distances.emplace_back(
                    templates::squaredEuclideanDistance2D(buffer.getCenter(), card.center_point)
                    );
			}

			// find min distance and add card to that buffer, if the distance is small enough. 
            // Otherwise it is a new card and a new buffer is created
			auto p = std::min_element(squared_distances.begin(), squared_distances.end());
			auto pos = std::distance(squared_distances.begin(), p);

			if( *p < MAX_DISTANCE_TO_BUFFER * MAX_DISTANCE_TO_BUFFER)
			{
				this->card_buffers_.at(pos).put(card, this->frame_nr_);
			}
			else
			{
				this->card_buffers_.emplace_back(
                    CardBuffer<CARD_BUFFER_SIZE>(card, this->frame_nr_)
                    );
			}			
		}
	}

    void CardDetector::detectCards()
	{
        this->cards_.clear();
		this->data_.cards.clear();

		// get settings from GUI if a GUI is connected
		if(this->gui_interface_ != nullptr)
		{
			if(this->gui_interface_->checkUserInput())
			{
				this->settings_ = this->gui_interface_->getSettings();
			}
		}

		// get live frame from camera if connected
		if(this->capture_interface_ != nullptr)
		{
			this->updateFrame(capture_interface_->getImage());
		}

		// Find Contours of interest in frame	
		std::vector<std::vector<cv::Point> > card_contours =	
            ContourFinder::findContours(this->live_frame_.image, this->settings_.live_threshold);

        // Filter Contours by area to get rid of contours that are too small or large to be a card, 
		// -> min- and max-card size were determined empirically, and depend on camera positioning
		ContourFinder::filterContours(
            card_contours, 
            ContourFinder::Filter::GE_AREA, 
            this->min_card_size_
            );
		ContourFinder::filterContours(
            card_contours, 
            ContourFinder::Filter::LE_AREA, 
            this->max_card_size_
            );

        // Find corner points and center points of contours
		std::vector < std::vector< cv::Point2f >> card_corners = 
			ContourFinder::calculateCornerPoints(card_contours);

		std::vector< cv::Point2f > card_centers =
		    ContourFinder::calculateCenterPoints(card_contours);

        // Identify Cards rank and suit

		int count = 0;
		cv::Mat card_image;

		fs::path rank_folder = fs::current_path() / "Card_Imgs" / "ranks" / "*.jpg";
		fs::path suit_folder = fs::current_path() / "Card_Imgs" / "suits" / "*.jpg";

        CardIdentifier card_identifier(
            rank_folder.string(),
            suit_folder.string(),
            this->settings_.identification_threshold,
            this->settings_.binary_threshold
            );

        for (const auto& contour : card_contours)
		{
			card_image.create(
                cv::Size(this->card_width_, 
                static_cast<int>(this->card_width_*this->card_aspect_ratio_)), 
                this->live_frame_.image.type()
                );
			
            // Rewarp cards to correct perspective errors 
			bool transform_result = this->perspective_corrector_.warpImage(
                this->live_frame_.image, 
                card_image, 
                card_corners.at(count),
                card_centers.at(count),
                this->perspective_transform_offset_
                );

			if (!transform_result)
			{
				card_image.release();
				break;
			}			
			
			Card card_tmp;
			card_tmp.contour = contour;
			card_tmp.center_point = card_centers.at(count);
			card_tmp.card_image.image = card_image;

            // Identify cards rank and suit
			card_identifier.identifyCard(card_tmp, card_image);

            // Add card to card buffer
			this->bufferCard(card_tmp);			

            // clear card_image
			card_image.release();								
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
	
		// Add detected Cards to poker interface
		for(auto& card: this->cards_)
		{
			if(!templates::contains(this->data_.cards.begin(), this->data_.cards.end(), card))
     		{	
				 this->data_.cards.emplace_back(card);
			 }
		}
		// send cards to GUI if a GUI is connected
		if(this->gui_interface_ != nullptr)
		{
			this->gui_interface_->setCards(this->cards_);
		}
    }

} // end namespace detect