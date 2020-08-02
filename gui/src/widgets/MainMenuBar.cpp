#include "MainMenuBar.hpp"

namespace gui {

    void MainMenuBar::draw()
    {
        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("View"))
            {
                ImGui::MenuItem("Settings", NULL, &this->show_settings_win_);
                ImGui::MenuItem("Live View", NULL, &this->show_live_image_);
                ImGui::MenuItem("Game Window", NULL, &this->show_poker_win_);
                ImGui::MenuItem("Card Images", NULL, &this->show_card_image_);
                ImGui::MenuItem("Rank Images", NULL, &this->show_rank_image_);
                ImGui::MenuItem("Suit Images", NULL, &this->show_suit_image_);

                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }
    }
} // end namespace gui