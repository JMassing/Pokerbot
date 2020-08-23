#pragma once

#include "DataPoker.hpp"
#include "Player.hpp"
// Monte Carlo simulation of poker game
namespace poker{
    
    class DecisionMaker{

        private:
            DataPoker& data_;
            const int& big_blind_;

            void decideMove();
            void decideBetsize();

        public:
            
            void makeDecision();
            
            DecisionMaker(DataPoker& data, int big_blind): 
                data_(data), 
                big_blind_(big_blind)
            {};
            ~DecisionMaker() {};   
                
            // Using default copy and move constructors. 
            DecisionMaker(const DecisionMaker& other) = default;
            DecisionMaker& operator=(const DecisionMaker& other) = default;
            DecisionMaker(DecisionMaker&& other) noexcept = default;
            DecisionMaker& operator=(DecisionMaker&& other) noexcept = default;        

    };

}//end namespace poker