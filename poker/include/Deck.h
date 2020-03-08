#pragma once

#include <array>
#include <sstream>
#include <memory>

#include "Card.h"
#include "Mapping.h"

namespace poker{

    class Deck{

    public:

        std::array<detect::Card,52> deck;
        std::array<detect::Card*,52> deck_ptr;

    public:

        Deck();
        ~Deck() {};
                
        // Using default copy and move constructors. 
		Deck(const Deck& other) = default;	
		Deck& operator=(const Deck& other) = default;
		Deck(Deck&& other) noexcept = default;
		Deck& operator=(Deck&& other) noexcept = default;

    };

}// end namespace poker