#include "LiveImageWin.h"        

namespace gui
{

    bool LiveImageWin::content()
    {        
            cv::Mat shown_image = this->live_frame_.clone();

            if(this->show_cards_ && this->cards_.size() > 0)
            {
                this->visualize_.drawCards(this->cards_, shown_image, this->card_outline_color_);
            }

            this->drawer_.draw(shown_image, this->image_width_, this->image_height_);

            return true;
    }

    void LiveImageWin::update(const cv::Mat& live_frame, const int& image_width, const int& image_height, const std::vector<detect::Card>& cards, const cv::Scalar& card_outline_color)
    {
        this->live_frame_ = live_frame;
        this->image_width_ = image_width;
        this->image_height_ = image_height;
        this->cards_ = cards;
        this->card_outline_color_ = card_outline_color;
    }

} //end namespace gui