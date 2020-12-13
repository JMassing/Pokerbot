#pragma once

#include "DataPoker.hpp"

namespace poker{
    /**  \ingroup poker
	 * @class MoneyTracker
	 * @author Julian Massing (julimassing@gmail.com)
	 * @brief Processes bets, Potsize and Potsize        
	 *
	 * @version 1.0
	 * @date 2020-11-22
	 * 
	 * @copyright Copyright (c) 2020
	 * 
	 */
    class MoneyTracker{
        
        private: 

            DataPoker& data_;  

        public:

            void processBet();
    	    void calcPotSize();
            bool isPlayerAllIn();
            bool hasPlayerLessThanBigblind(int big_blind);

            MoneyTracker(DataPoker& data): data_(data) {};
            ~MoneyTracker() {};   
                
            // Using default copy and move constructors. 
            MoneyTracker(const MoneyTracker& other) = default;
            MoneyTracker& operator=(const MoneyTracker& other) = default;
            MoneyTracker(MoneyTracker&& other) noexcept = default;
            MoneyTracker& operator=(MoneyTracker&& other) noexcept = default;        

    };

}//end namespace poker