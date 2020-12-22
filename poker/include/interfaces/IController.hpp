#pragma once

#include <vector>

#include "GameSettings.hpp"
#include "DataPoker.hpp"

namespace poker
{
	/**  \ingroup poker
	 * @class IController
	 * @author Julian Massing (julimassing@gmail.com)
	 * @brief Interface for class to control the game state.
	 *		
	 * @version 1.0
	 * @date 2020-11-21
	 * 
	 * @copyright Copyright (c) 2020
	 * 
	 */	
	class IController
	{
		public:

			/**
             * @brief starts game
             * 
             */
            virtual void start() = 0;
            /**
             * @brief stop game
             * 
             */
            virtual void stop() = 0;
            /**
             * @brief resets current game phase
             * 
             */
            virtual void resetPhase() = 0;
            /**
             * @brief starts next round
             * 
             */
            virtual void startNextRound() = 0;
            /**
             * @brief sets game phase
             * 
             */
            virtual void setGamePhase() = 0;

			virtual ~IController() {};
	};

}//end namespace interfaces


