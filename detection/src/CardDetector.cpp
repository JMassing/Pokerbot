#include "CardDetector.hpp"

namespace detect{

    void CardDetector::updateFrame()
    {
       	this->data_handler_->getLiveFrame(this->live_frame_);
        ++this->frame_nr_;
    }    

    void CardDetector::detectCards()
	{
        this->cards_.clear();
		this->data_.cards.clear();

		this->updateFrame();
		this->data_handler_->getProcessingSettings(this->settings_);

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

		fs::path rank_folder = boost::dll::program_location().parent_path() / ".." / "Card_Imgs" / "ranks" / "*.jpg";
		fs::path suit_folder = boost::dll::program_location().parent_path() / ".." / "Card_Imgs" / "suits" / "*.jpg";

        CardIdentifier card_identifier(
            rank_folder.string(),
            suit_folder.string(),
            this->settings_.identification_threshold,
            this->settings_.binary_threshold
            );

		// Loop through all detected contours and identify the card that is enclosed by the contour
        for (const auto& contour : card_contours)
		{
			card_image.create(
                cv::Size(this->card_width_, 
                static_cast<int>(this->card_width_*this->card_aspect_ratio_)), 
                this->live_frame_.image.type()
                );
			
            // Rewarp image within contours to correct perspective errors 
			bool image_was_warped = this->perspective_corrector_.warpImage(
                this->live_frame_.image, 
                card_image, 
                card_corners.at(count),
                card_centers.at(count),
                this->perspective_transform_offset_
                );
			if (!image_was_warped)
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

            // Add card to card buffers
			buffer_manager_.addDetectedCard(card_tmp, this->frame_nr_, 30);			

            // clear card_image
			card_image.release();								
			++count;
		}

		// Remove stale Buffers and get cards from buffers
		this->buffer_manager_.removeStaleBuffers(3, this->frame_nr_);
		this->cards_ = this->buffer_manager_.getBufferedCards();	
		
		// Add detected Cards to Data
		for(auto& card: this->cards_)
		{
			if(!templates::contains(this->data_.cards.begin(), this->data_.cards.end(), card))
     		{	
				 this->data_.cards.emplace_back(card);
			 }
		}

		this->data_handler_->sendDetectedCards(this->cards_);
    }
} // end namespace detect