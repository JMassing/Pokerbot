#pragma once

#include <vector>

#include "DataPoker.hpp"
#include "BaseCard.hpp"
#include "GameSettings.hpp"
#include "IController.hpp"

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
    class GameStateController: public IController{
        
        private: 

            DataPoker& data_;
            GameSettings& settings_;
            std::vector<BaseCard>& robot_cards_;
            std::vector<BaseCard>& public_cards_;

        public:

            /**
             * @brief starts game
             * 
             */
            void start() override;
            /**
             * @brief stop game
             * 
             */
            void stop() override;
            /**
             * @brief resets current game phase
             * 
             */
            void resetPhase() override;
            /**
             * @brief starts next round
             * 
             */
            void startNextRound() override;
            /**
             * @brief sets game phase
             * 
             */
            void setGamePhase() override;

            GameStateController(
                DataPoker& data, 
                GameSettings& settings,
                std::vector<BaseCard>& robot_cards,
                std::vector<BaseCard>& public_cards
                ): 
                data_(data), 
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