#pragma once

#include <vector>

#include "DataPoker.hpp"
#include "BaseCard.hpp"
#include "GameSettings.hpp"

namespace poker{
    /**  \ingroup poker
	 * @class GameStateController
	 * @author Julian Massing (julimassing@gmail.com)
	 * @brief Controls the state of the poker game        
	 *
	 * @version 1.0
	 * @date 2020-11-22
	 * 
	 * @copyright Copyright (c) 2020
	 * 
	 */
    class GameStateController{
        
        private: 

            DataPoker& data_;
            GameSettings& settings_;
            int& game_phase_;
            std::vector<BaseCard>& robot_cards_;
            std::vector<BaseCard>& public_cards_;

        public:

            /**
             * @brief starts game
             * 
             */
            void start();
            /**
             * @brief stop game
             * 
             */
            void stop();
            /**
             * @brief resets current game phase
             * 
             */
            void resetPhase();
            /**
             * @brief starts next round
             * 
             */
            void startNextRound();
            /**
             * @brief sets game phase
             * 
             */
            void setGamePhase();

            GameStateController(
                DataPoker& data, 
                int& game_phase, 
                GameSettings& settings,
                std::vector<BaseCard>& robot_cards,
                std::vector<BaseCard>& public_cards
                ): 
                data_(data), 
                game_phase_(game_phase),
                settings_(settings),
                robot_cards_(robot_cards),
                public_cards_(public_cards)
            {};
            ~GameStateController() {};   
                
            // Using default copy and move constructors. 
            GameStateController(const GameStateController& other) = default;
            GameStateController& operator=(const GameStateController& other) = default;
            GameStateController(GameStateController&& other) noexcept = default;
            GameStateController& operator=(GameStateController&& other) noexcept = default;        

    };

}//end namespace poker