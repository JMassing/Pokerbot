#include "CardImageWin.h"        

namespace gui
{

    bool CardImageWin::content()
    {        
        int height = static_cast<int>(this->image_height_ * static_cast<double>(this->image_height_percent_)/100.0);
        for(const auto& card: this->cards_)
        {
            this->drawer_.draw(card.card_image.image, height/this->aspect_ratio_, height); 
            ImGui::SameLine();  
        }
        return true;
    }

    void CardImageWin::update(const int& aspect_ratio, const int& image_height, const std::vector<detect::Card>& cards, const int& image_height_percent)
    {
        this->aspect_ratio_ = aspect_ratio;
        this->image_height_ = image_height;
        this->cards_ = cards;
        this->image_height_percent_ = image_height_percent;
    }

} //end namespace gui