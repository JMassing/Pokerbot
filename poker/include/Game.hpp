#pragma once

#include <vector>
#include <memory>
#include <iostream>
#include <random>

#include "MonteCarlo.hpp"
#include "GameSettings.hpp"
#include "DataPoker.hpp"
#include "IPokerGui.hpp"
#include "IPokerDetect.hpp"
#include "BaseCard.hpp"
#include "CardAssigner.hpp"
#include "DecisionMaker.hpp"
#include "MoneyTracker.hpp"
#include "DecisionProcessor.hpp"
#include "GameStateController.hpp"

namespace poker{
    /**  \ingroup poker
	 * @class Game
	 * @author Julian Massing (julimassing@gmail.com)
	 * @brief Coordinates the poker module objects and the communication to the other modules during a game of poker        
	 *
	 * @version 1.1
	 * @date 2020-11-22
	 * 
	 * @copyright Copyright (c) 2020
	 * 
	 */
    class Game{
        
        protected: 

            bool getWinner();

            GameSettings settings_;
            MoneyTracker money_tracker_;
            DecisionProcessor decision_processor_;
            std::unique_ptr<IController> controller_;
            std::shared_ptr<IPokerGui> gui_interface_;
            std::shared_ptr<IPokerDetect> detect_interface_;
            std::vector<BaseCard> public_cards_;
            std::vector<BaseCard> robot_cards_; 
                        
        public:

            DataPoker data_;        

            void attachGuiInterface(std::shared_ptr<IPokerGui> interface)
			{
				this->gui_interface_ = interface;
			}

            void attachDetectInterface(std::shared_ptr<IPokerDetect> interface)
			{
				this->detect_interface_ = interface;
			}
            
            void play();

            Game(
                GameSettings settings,  
                const bool& log_sim = false
                ): 
                data_(),
                gui_interface_(nullptr),
                detect_interface_(nullptr),
                robot_cards_{},
                public_cards_{},
                settings_(settings),
                money_tracker_(this->data_),
                decision_processor_(this->data_)
            {
                this->controller_ = std::make_unique<GameStateController>
                    (this->data_, this->settings_, this->robot_cards_, this->public_cards_);
            };
            ~Game() {};   
                
            // Using default copy and move constructors. 
            Game(const Game& other) = default;
            Game& operator=(const Game& other) = default;
            Game(Game&& other) noexcept = default;
            Game& operator=(Game&& other) noexcept = default;        

    };

}//end namespace poker