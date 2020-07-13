#pragma once

#include <vector>
#include <string>
#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

#include "Card.hpp"
#include "Mapping.hpp"
#include "TrainImage.hpp"
#include "ContourFinder.hpp"

// Compares card images to train images and returns the rank and suit of the detected
// Card image

namespace detect 
{
    class CardIdentifier
	{

        private: 

            std::vector<TrainImage> train_suits_;
			std::vector<TrainImage> train_ranks_;
            int& identification_threshold_;
            int& binarization_threshold_;

            // Parameters for zoom into upper left corner. Ranks and Suit is
            // determined from zoomed image. Parameters were found empirically
            // and fit well to the cards used here
            const int zoom_offset_ = 5;
            const double zoom_width_to_card_width_ratio_ = 0.25;
            const double zoom_height_to_card_height_ratio_ = 0.4;

            // Upper limit for size of rank contour area as a ratio of the zoomed image area
            // This is used to filter out contours in the zoomed image that are to large to
            // be the contour of the rank/suit
            const double max_rank_area_ratio_ = 0.6;

            // Max comparison score to be considered a valid comparison. Empirical parameter
            const double max_score_ = 1.5;

   			void loadTrainImages(
                   const std::string &path, 
                   std::vector<TrainImage>& train_images
                   );			

           	double compareImages(const cv::Mat &src, const cv::Mat &dst);		

            int compareToTrainImage(
                const cv::Mat& image, 
                std::vector<TrainImage> train_images
                );	

		public:    

        	void identifyCard(Card& card, const cv::Mat& card_image);

			CardIdentifier(
                const std::string& path_to_rank_training_images,
                const std::string& path_to_suit_training_images,
                int& identification_threshold,
                int& binarization_threshold
                );

			~CardIdentifier(){};

			// Using default copy and move constructors. 
			CardIdentifier(const CardIdentifier& other) = default;	
			CardIdentifier& operator=(const CardIdentifier& other) = default;
			CardIdentifier(CardIdentifier&& other) noexcept = default;
			CardIdentifier& operator=(CardIdentifier&& other) noexcept = default;
					
	};

}//namespace detect