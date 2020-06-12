#pragma once

#include <string>

#include "Mapping.h"
#include "View.h"
#include "BaseGUI.h"
#include "Image.h"

namespace gui
{

    class CaptureTrainImg
    {
        private:

            BaseGUI gui_;
            std::string train_images_folder_;
            detect::Mapping card_mapping_;
            View visualize_;
            bool show_question_;
            int card_value_;
            detect::Image train_image_;
            std::string card_;

            void drawTrainImagesQuestionWindow();
            void saveImage();

        public:
            
            bool capture_button_pressed_;
            bool capture_;
            int nr_of_cards_;
            std::string type_;

            void captureRequested()
            {
                this->show_question_ = true; this->capture_button_pressed_ = true;
            };
            void drawTrainImagesCaptureWindow();
            void drawTrainImagesGuiWindow();
            void printInstructions(cv::Mat& dst, const cv::Scalar& color);
            void setTrainImage(cv::Mat train_image){this->train_image_.image = train_image;};

            CaptureTrainImg(): gui_(), train_images_folder_(), card_mapping_(), visualize_(), capture_button_pressed_(false),
             capture_(false), show_question_(false), card_value_(2), nr_of_cards_(0), train_image_(),
             card_(), type_() {};
            ~CaptureTrainImg() {};

            // Use Default copy and move constructors
            CaptureTrainImg(const CaptureTrainImg& other) = default;	
            CaptureTrainImg& operator=(const CaptureTrainImg& other) = default;
            CaptureTrainImg(CaptureTrainImg&& other) noexcept = default;
            CaptureTrainImg& operator=(CaptureTrainImg&& other) noexcept = default;
    };

}//end namespace detect