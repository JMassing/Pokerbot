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

		cv::glob(path, file_names, false);		

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

     std::pair<int, std::string> CardIdentifier::compareToTrainImage(
        const cv::Mat& image, 
        std::vector<TrainImage> rank_images,
		std::vector<TrainImage> suit_images
        )
    {
		Mapping mapping;
        double score = 10000.0;
        int count = 0;
        int val = Cards::UNKNOWN;
		std::string type = "UNKNOWN";

		for (const auto& rank_image: rank_images)
		{
			double tmp_score = this->compareImages(image, rank_image.getImage().image);

			if (tmp_score < score)
			{
				score = tmp_score;
				std::string name = rank_images.at(count).getLabel();	
				if (score < this->max_score_)
				{
					val = mapping.image_mappings.left.at(name);
					type = "rank";
				}
			}
			
            count++;
		}

		count = 0;
		for (const auto& suit_image: suit_images)
		{
			double tmp_score = this->compareImages(image, suit_image.getImage().image);

			if (tmp_score < score)
			{
				score = tmp_score;
				std::string name = suit_images.at(count).getLabel();	
				if (score < this->max_score_)
				{
					val = mapping.image_mappings.left.at(name);
					type = "suit";
				}
			}
			
            count++;
		}

        return std::make_pair(val, type);
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
			cv::Mat img1, img2;
			
			// sort contours for size. Rank and suit have the 
			// two largest bounding boxes
			std::sort(
                bounding_box.begin(), 
                bounding_box.end(), 
                [](const cv::Rect& lhs, const cv::Rect& rhs) {return lhs.area() > rhs.area();}
                );

			img1 = card_zoom(bounding_box.at(0)).clone();
			img2 = card_zoom(bounding_box.at(1)).clone();
		
			cv::Mat img1_binary, img2_binary;

			// resize suit train image to match rank train image size
			for(auto& img : train_suits_)
			{
				cv::Mat img_temp = img.getImage().image;
				cv::resize(img_temp, img_temp, train_ranks_.at(0).getImage().image.size(), 0, 0, cv::INTER_LINEAR);
				img.setImage(Image(img_temp));
			}

			// Binarize rank and suit image			
			img1_binary.create(
                this->train_ranks_.at(0).getImage().image.size(), 
                this->train_ranks_.at(0).getImage().image.type()
                );

			img2_binary.create(
                this->train_ranks_.at(0).getImage().image.size(), 
                this->train_ranks_.at(0).getImage().image.type()
                );

			cv::resize(img1, img1, img1_binary.size(), 0, 0, cv::INTER_LINEAR);
			ContourFinder::binarizeImage(
                img1, 
                img1_binary, 
                this->binarization_threshold_, 
                cv::THRESH_BINARY_INV
                );

			cv::resize(img2, img2, img2_binary.size(), 0, 0, cv::INTER_LINEAR); 
			ContourFinder::binarizeImage(
                img2, img2_binary, 
                this->binarization_threshold_, 
                cv::THRESH_BINARY_INV
                );

			// Compare to train images
			
            std::pair<int, std::string> result_img1 = this->compareToTrainImage(img1_binary, this->train_ranks_, this->train_suits_);
            std::pair<int, std::string> result_img2 = this->compareToTrainImage(img2_binary, this->train_ranks_, this->train_suits_);	

			if(result_img1.second == "rank")
			{
				card.rank =  result_img1.first;
				card.rank_image.image = img1_binary;
				card.suit = result_img2.first;
				card.suit_image.image = img2_binary;
			}
			else
			{
				card.rank =  result_img2.first;
				card.rank_image.image = img2_binary;
				card.suit = result_img1.first;
				card.suit_image.image = img1_binary;
			}
 	
		}
		else 
		{
			card.rank = UNKNOWN;
			card.suit = UNKNOWN;
		}
	}

}