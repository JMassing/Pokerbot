#pragma once

#include "DataPoker.hpp"
#include "Player.hpp"

namespace poker{    
    /**  \ingroup poker
	* @class DecisionMaker
	* @author Julian Massing (julimassing@gmail.com)
	* @brief Decides move (check, call, raise, fold) and betsize for robot based on probability of winning
    *        with the robot hand and betsize of the opponent.        
	*
	* @version 1.0
	* @date 2020-11-22
	* 
	* @copyright Copyright (c) 2020
	* 
	*/
    class DecisionMaker{

        private:
            DataPoker& data_;
            const int big_blind_ = 100;

            void decideMove();
            void decideBetsize();

        public:
            
            void makeDecision();
            
            DecisionMaker(DataPoker& data): 
                data_(data)
            {};
            ~DecisionMaker() {};   
                
            // Using default copy and move constructors. 
            DecisionMaker(const DecisionMaker& other) = default;
            DecisionMaker& operator=(const DecisionMaker& other) = default;
            DecisionMaker(DecisionMaker&& other) noexcept = default;
            DecisionMaker& operator=(DecisionMaker&& other) noexcept = default;        

    };

}//end namespace poker