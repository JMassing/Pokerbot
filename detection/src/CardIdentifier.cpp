#include "CardIdentifier.hpp"

namespace detect{

    	CardIdentifier::CardIdentifier(
            const std::string& path_to_rank_training_images,
            const std::string& path_to_suit_training_images,
            int& identification_threshold,
            int& binarization_threshold
            ):
            identification_threshold_(identification_threshold),
            binarization_threshold_(binarization_threshold)
        {
            // reserve space for train images, these should be 13 ranks and 4 suits
		    this->train_ranks_.reserve(13);
		    this->train_suits_.reserve(4);

		    this->loadTrainImages(
                    path_to_rank_training_images,
                    this->train_ranks_
                    );

	        this->loadTrainImages(
                    path_to_suit_training_images,
                    this->train_suits_
                    );
        };
	
	//@brief: compares two images and returns L2 error
    double CardIdentifier::compareImages(const cv::Mat &src, const cv::Mat &dst)
    {
        if (src.size() == dst.size() && src.type() == dst.type())
		{
			 // Calculate the L2 relative error between images.
			double errorL2 = cv::norm(src, dst, cv::NORM_L2);
			// Convert to a reasonable scale, since L2 error is summed across all pixels of the image.
			double similarity = errorL2 / static_cast<double>(src.rows * src.cols);
			return similarity;
		}
		
		return -1.0;		
    }			

    // @brief: load training images for comparison with detected images
	void CardIdentifier::loadTrainImages(
        const std::string &path, 
        std::vector<TrainImage>& train_images
        )
	{	
		std::vector<std::string> file_names{};

		cv::glob(path + "\\*.jpg", file_names, false);		

        // check if input could be read
		if (file_names.size() == 0) 
        {  
            std::cout << "Training Images could not be read" << std::endl;
			return;
		}	

		for (const std::string &file_name: file_names) 
        {
			train_images.emplace_back(TrainImage{ file_name });
		}		
	}

    int CardIdentifier::compareToTrainImage(
        const cv::Mat& image, 
        std::vector<TrainImage> train_images
        )
    {
		Mapping mapping;
        double score = 10000.0;
        int count = 0;
        int val = Cards::UNKNOWN;

		for (auto &train_image: train_images)
		{
			double tmp_score = this->compareImages(image, train_image.getImage());

			if (tmp_score < score)
			{
				score = tmp_score;
				std::string name = train_images.at(count).getLabel();	
				if (score < this->max_score_)
				{
					val = mapping.image_mappings.left.at(name);
				}
			}
			
            count++;
		}
        return val;
    }

    //@brief: Identifies what card is shown in card image
	//	      Card image is binarized and upper right corner is zoomed in
	//		  Upper right corner is then compared from train images using L2 Norm
	//    	  Lowest difference wins.
	void CardIdentifier::identifyCard(Card& card, const cv::Mat& card_image) 
	{
		// Zoom into the upper left corner
		int zoom_width = 
            static_cast<int>(
				static_cast<double>(card_image.cols) * this->zoom_width_to_card_width_ratio_
				);

		int zoom_height = 
            static_cast<int>(
                static_cast<double>(card_image.rows) * this->zoom_height_to_card_height_ratio_
                );

		cv::Rect zoom(this->zoom_offset_, this->zoom_offset_, zoom_width, zoom_height);

		cv::Mat card_zoom = card_image(zoom).clone();

		// find contours in the zoomed in image giving rank and suit contours
		std::vector<std::vector<cv::Point> > contours{};
		contours = ContourFinder::findContours(
            card_zoom, 
            this->identification_threshold_, 
            cv::THRESH_BINARY
            );
	
		// filter suit and rank image contours by area. 
		double max_area = zoom_width * zoom_height * this->max_rank_area_ratio_ ;
		double min_area = zoom_width;
		ContourFinder::filterContours(contours, ContourFinder::Filter::LE_AREA, max_area);
		ContourFinder::filterContours(contours, ContourFinder::Filter::GE_AREA, min_area);

		// get bounding boxes of the contours
		std::vector<cv::Rect> bounding_box;
		for (const auto & contour: contours) {
			bounding_box.emplace_back(cv::boundingRect(contour));
		}
		
		// Identify suit and Rank of card
		if (bounding_box.size() > 1)
		{
			cv::Mat rank, suit;
			
			// sort contours for size. Rank has the largest bounding box, 
            // whereas suit has the second largest
			std::sort(
                bounding_box.begin(), 
                bounding_box.end(), 
                [](const cv::Rect& lhs, const cv::Rect& rhs) {return lhs.area() > rhs.area();}
                );

			rank = card_zoom(bounding_box.at(0)).clone();
			suit = card_zoom(bounding_box.at(1)).clone();
		
			cv::Mat rank_binary, suit_binary;

			// Binarize rank and suit image			
			rank_binary.create(
                this->train_ranks_[0].getImage().size(), 
                this->train_ranks_[0].getImage().type()
                );

			suit_binary.create(
                this->train_suits_[0].getImage().size(), 
                this->train_suits_[0].getImage().type()
                );

			cv::resize(rank, rank, rank_binary.size(), 0, 0, cv::INTER_LINEAR);
			ContourFinder::binarizeImage(
                rank, 
                rank_binary, 
                this->binarization_threshold_, 
                cv::THRESH_BINARY_INV
                );

			cv::resize(suit, suit, suit_binary.size(), 0, 0, cv::INTER_LINEAR); 
			ContourFinder::binarizeImage(
                suit, suit_binary, 
                this->binarization_threshold_, 
                cv::THRESH_BINARY_INV
                );

			card.rank_image.image = rank_binary;
			card.suit_image.image = suit_binary;
 
			// Compare to train images
			
            card.rank = this->compareToTrainImage(rank_binary, this->train_ranks_);
            card.suit = this->compareToTrainImage(suit_binary, this->train_suits_);		
		}
		else 
		{
			card.rank = UNKNOWN;
			card.suit = UNKNOWN;
		}
	}

}