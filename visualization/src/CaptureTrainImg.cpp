#include "CaptureTrainImg.h"

namespace visualization
{
    void CaptureTrainImg::drawTrainImagesQuestionWindow()
    {
            ImGui::Text("Start Capture of new training images?");
            gui_.addButton("Yes", [this](){this->capture_ = true; this->show_question_ = false; this->capture_button_pressed_ = false;});
            ImGui::SameLine();
            gui_.addButton("Cancel", [this](){this->capture_ = false; this->show_question_ = false; this->capture_button_pressed_ = false;});
    }

    void CaptureTrainImg::drawTrainImagesCaptureWindow()
    {
        if(this->nr_of_cards_ == 1)
        {
            gui_.addButton("Save", [this](){this->saveImage(); ++this->card_value_;});
        }
        else
        {
            gui_.addButton("Save", [this](){});
        }

        ImGui::SameLine();
        gui_.addButton("Stop", [this](){this->capture_ = false;});

    }

    void CaptureTrainImg::saveImage()
    {   
        std::string name = this->train_images_folder_+ "\\" + this->card_ + ".jpg";
        cv::imwrite( name, this->train_image_ );

    }


    void CaptureTrainImg::drawTrainImagesGuiWindow()
    {
        if(!this->capture_ && this->show_question_)
        {
            gui_.addWindow("##show_question", this->show_question_ , [this](){this->drawTrainImagesQuestionWindow();});
        }
        else if(this->capture_)
        {
            gui_.addWindow("##capture", this->capture_ , [this](){this->drawTrainImagesCaptureWindow();});
        }
        else
        {
            // do nothing
        }
        if(this->card_value_ > 18)
        {
            this->card_value_ = 2;
            this->capture_ = false;
        }
    }

    void CaptureTrainImg::printInstructions(cv::Mat& dst, const cv::Scalar& color)
    {
        this->card_ = this->card_mapping_.image_mappings.right.at(this->card_value_);
        this->type_ = "";
        if(this->card_value_ < 15)
        {
            this->type_ = "rank";
            this->train_images_folder_ = "C:\\Users\\julim\\Desktop\\Projects\\Pokerbot\\Card_Imgs\\ranks";
        }
        else
        {
            this->type_ = "suit";
            this->train_images_folder_ = "C:\\Users\\julim\\Desktop\\Projects\\Pokerbot\\Card_Imgs\\suits";
        }
        std::string text_type = "Saving " + this->type_ + " train images.";
        std::string text_card = "Please place a " + this->card_ + " into the rectangle and hit save button when ready";
        
        this->visualize_.printText(dst, text_type, cv::Point(230,60), color);
        this->visualize_.printText(dst, text_card, cv::Point(230,80), color);
        if(this->nr_of_cards_ > 1)
        {
            std::string warning = "Please only place one card within the camera view";
            this->visualize_.printText(dst, warning, cv::Point(330,400), cv::Scalar{0,0,255});
        }
    }
}//end namespace detect