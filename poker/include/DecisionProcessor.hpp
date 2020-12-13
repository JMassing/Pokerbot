#pragma once

#include "DataPoker.hpp"

namespace poker{
    /**  \ingroup poker
	 * @class DecisionProcessor
	 * @author Julian Massing (julimassing@gmail.com)
	 * @brief Processes Player Decisions
	 *
	 * @version 1.0
	 * @date 2020-11-22
	 * 
	 * @copyright Copyright (c) 2020
	 * 
	 */
    class DecisionProcessor{
        
        private: 
            
            DataPoker& data_;

        public:

            bool hasPlayerRaised();
            bool hasRobotRaised();
            bool haveAllPlayersDecided();
            bool wasRaised();

            DecisionProcessor(DataPoker& data): data_(data) {};
            ~DecisionProcessor() {};   
                
            // Using default copy and move constructors. 
            DecisionProcessor(const DecisionProcessor& other) = default;
            DecisionProcessor& operator=(const DecisionProcessor& other) = default;
            DecisionProcessor(DecisionProcessor&& other) noexcept = default;
            DecisionProcessor& operator=(DecisionProcessor&& other) noexcept = default;        

    };

}//end namespace poker