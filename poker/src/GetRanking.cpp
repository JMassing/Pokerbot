#include "GetRanking.h"

namespace poker {

 //@brief checks if we have a AceLowStreet
    bool GetRanking::isAceLowStreet(Hand& hand)
    {
        if(!hand.containsRank(detect::ACE) || !hand.containsRank(detect::TWO) || !hand.containsRank(detect::THREE) || !hand.containsRank(detect::FOUR) || !hand.containsRank(detect::FIVE))
        {
            return false;
        }
        else
        {
            return true;
        }
    }

}//end namespace poker