#include "CardBuffer.h"

namespace detect
{

    void CardBuffer::addCard(Card& card)
    {
        if(this->pos_tracker_ == 0)
        {
            this->buffer_.at(pos_tracker_) = card;
            this->center_point_=card.center_point;
            card.id=this->id_;
            ++pos_tracker_;
        }
        else
        {
            this->buffer_.at(pos_tracker_) = card;
            ++pos_tracker_;
        }
        
    }

} // end namespace detect