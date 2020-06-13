#include "RankImageWin.h"        

namespace gui
{

    bool RankImageWin::content()
    {        
        int height = static_cast<int>(this->image_height_ * static_cast<double>(this->image_height_percent_)/100.0);
        for(const auto& card: this->cards_)
        {
            this->drawer_.draw(card.rank_image.image, height, height);
            ImGui::SameLine();
        }
        return true;
    }

    void RankImageWin::update(const int& image_height, const std::vector<detect::Card>& cards, const int& image_height_percent)
    {
        this->image_height_ = image_height;
        this->cards_ = cards;
        this->image_height_percent_ = image_height_percent;
    }

} //end namespace gui