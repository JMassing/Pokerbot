#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <utility>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

#include "Card.hpp"
#include "Mapping.hpp"
#include "TrainImage.hpp"
#include "ContourFinder.hpp"

// 
namespace detect 
{
    /** *\ingroup detection
	 * @class CardIdentifier
	 * @author Julian Massing (julimassing@gmail.com)
	 * @brief Compares Card Image to TrainImage and returns the rank and suit of the detected Card Image
	 *		
	 * @version 1.0
	 * @date 2020-11-21
	 * 
	 * @copyright Copyright (c) 2020
	 * 
	 */
    class CardIdentifier
	{
        private: 

            std::vector<TrainImage> train_suits_;
			std::vector<TrainImage> train_ranks_;
            int& identification_threshold_;
            int& binarization_threshold_;
            /**
             * @brief Parameters for zoom into upper left corner. Ranks and Suit is
             * determined from zoomed image. Parameters were found empirically
             * and fit well to the cards used here
             */
            const int zoom_offset_ = 5;
            const double zoom_width_to_card_width_ratio_ = 0.25;
            const double zoom_height_to_card_height_ratio_ = 0.4;
            /**
             * @brief Upper limit for size of rank contour area as a ratio of the zoomed image area
             * This is used to filter out contours in the zoomed image that are to large to
             * be the contour of the rank/suit
             * 
             */
            const double max_rank_area_ratio_ = 0.6;
            // Max comparison score to be considered a valid comparison. Empirical parameter
            const double max_score_ = 1.5;

   			void loadTrainImages(
                   const std::string &path, 
                   std::vector<TrainImage>& train_images
                   );			

            /**
             * @brief Calculates similarity of two images 
             * 
             * @param src First image
             * @param dst Second image
             * @return double L2-error
             */
           	double compareImages(const cv::Mat &src, const cv::Mat &dst);		

            std::pair<int, std::string> compareToTrainImage(
                const cv::Mat& image, 
                std::vector<TrainImage> rank_images,
                std::vector<TrainImage> suit_images
                );	

		public:    

            /**
             * @brief Identifies what Card is shown in Card Image.
             * Card Image is binarized and upper right corner is zoomed in.
			 * Upper right corner is then compared to TrainImage using L2 Norm.
	   	     * Lowest difference wins.
             * 
             * @param card Detected card
             * @param card_image Training image
             */
		      
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