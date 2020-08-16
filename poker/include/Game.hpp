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

// Coordinates the entities needed to run a monte carlo simulation with the given cards
namespace poker{
    
    class Game{
        
        private: 

            void start();
            void stop();
            void processBet();
    	    bool haveAllPlayersDecided();
            bool hasPlayerRaised();
            void processPlayerDecisions();
            void resetPhase();
            bool getWinner();
            void startNextRound();
            void setGamePhase();
            void calcPotSize();
            bool isPlayerAllIn();
            bool hasPlayerNoMoney();

            GameSettings settings_;
            std::shared_ptr<IPokerGui> gui_interface_;
            std::shared_ptr<IPokerDetect> detect_interface_;
            std::vector<BaseCard> public_cards_;
            std::vector<BaseCard> robot_cards_; 
            int game_phase_;
                        
            const int starting_money_ = 10000;
            const int big_blind_ = 100;
            const int small_blind_ = 50;

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
                game_phase_(NOT_STARTED),
                robot_cards_{},
                public_cards_{},
                settings_{settings}
            {};
            ~Game() {};   
                
            // Using default copy and move constructors. 
            Game(const Game& other) = default;
            Game& operator=(const Game& other) = default;
            Game(Game&& other) noexcept = default;
            Game& operator=(Game&& other) noexcept = default;        

    };

}//end namespace poker