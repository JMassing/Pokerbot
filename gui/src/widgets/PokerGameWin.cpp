#include "PokerGameWin.h"        

namespace gui
{

    bool PokerGameWin::content()
    {
        bool changed = false;

        changed |= this->input_.draw("# of Opponents", this->min_players_, this->max_players_, this->data_poker_->nr_of_human_players, true); ImGui::SameLine(); this->helpMarker("Nr of opponents playing against the bot.");  

        ImGui::Text("Probability of winning = %.2f", static_cast<float>(this->data_poker_->probability.first));
        ImGui::Text("Probability of winning tie = %.2f", static_cast<float>(this->data_poker_->probability.second));
        ImGui::Text("Robot Cards:");
        ImGui::SameLine();
        for(const auto& card: this->robot_cards_)
        {   
            std::string text = this->mapping_.text_mappings.right.at(card.rank) + this->mapping_.text_mappings.right.at(card.suit);
            ImGui::Text(text.c_str());
            ImGui::SameLine();
        }
        ImGui::NewLine();
        ImGui::Text("Public Cards:");
        ImGui::SameLine();
        for(const auto& card: this->public_cards_)
        {   
            std::string text = this->mapping_.text_mappings.right.at(card.rank) + this->mapping_.text_mappings.right.at(card.suit);
            ImGui::Text(text.c_str());
            ImGui::SameLine();
        }
        ImGui::NewLine();

        changed |= this->slider_.draw("# of simulation runs", this->min_sim_runs_, this->max_sim_runs_, this->data_poker_->nr_of_simulation_runs, true);
        ImGui::SameLine(); this->helpMarker("Nr of times the simulation is run. CTRL+click to input value.");  
   
        this->button_.draw("Reset", true, [this](){this->setConfigToDefault();}); 
        ImGui::SameLine();
        this->button_.draw("Save Settings", true, [this](){this->show_ask_for_save_ = true;}); 
      
        if(this->show_ask_for_save_ == true)
        {
            if(this->save_win_.draw(this->show_ask_for_save_))
            {
                this->saveConfigAsDefault();
            }
        }
         
        return changed;
    }

    void PokerGameWin::setConfigToDefault()
    {   
        this->data_poker_->nr_of_simulation_runs = this->default_config_->nr_sim_runs;
    }

	void PokerGameWin::saveConfigAsDefault()
    {
        this->default_config_->nr_sim_runs = this->data_poker_->nr_of_simulation_runs;
        this->default_config_->saveConfig();
    };


} //end namespace gui