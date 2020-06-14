#include "CardImageWin.h"        

namespace gui
{

    bool CardImageWin::content()
    {        
        int height = static_cast<int>(this->image_height_ * static_cast<double>(this->image_height_percent_)/100.0);
        int width = static_cast<int>(static_cast<double>(height)/this->aspect_ratio_);
        for(const auto& card: this->cards_)
        {
            this->drawer_.draw(card.card_image.image, width, height); 
            ImGui::SameLine();  
        }
        return true;
    }

    void CardImageWin::update(const double& aspect_ratio, const int& image_height, const std::vector<detect::Card>& cards, const int& image_height_percent)
    {
        this->aspect_ratio_ = aspect_ratio;
        this->image_height_ = image_height;
        this->cards_ = cards;
        this->image_height_percent_ = image_height_percent;
    }

} //end namespace gui