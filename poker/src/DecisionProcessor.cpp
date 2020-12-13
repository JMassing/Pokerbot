#include "DecisionProcessor.hpp" 

namespace poker{

    bool DecisionProcessor::haveAllPlayersDecided()
    {
        for(const auto& player: this->data_.players)
        {
            if(player.current_decision == NO_DECISION)
            {
                return false;
            }
        }
        return true;
    }

    bool DecisionProcessor::hasPlayerRaised()
    {
        return (this->data_.players.at(1).current_decision == HAS_RAISED || this->data_.players.at(1).current_decision == RAISE);
    }

    bool DecisionProcessor::hasRobotRaised()
    {
        return (this->data_.players.at(0).current_decision == HAS_RAISED || this->data_.players.at(0).current_decision == RAISE);
    }

    bool DecisionProcessor::wasRaised()
    {
        return (this->hasRobotRaised() || this->hasPlayerRaised());
    }

}// end namespace poker