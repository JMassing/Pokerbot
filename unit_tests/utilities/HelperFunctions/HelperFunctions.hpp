#pragma once

#include<vector>
#include<string>
#include<windows.h>
#include<iostream> 

#include <boost/filesystem.hpp>

#include "Hand.hpp"
#include "BaseCard.hpp"
#include "Mapping.hpp"

namespace UnitTest
{

	// Split String
	std::vector<std::string> split(std::string line, char delim=' ')
	{ 
		std::size_t current, previous = 0;
		std::vector<std::string> cont;
		current = line.find(delim);
		while (current != std::string::npos) {
			cont.push_back(line.substr(previous, current - previous));
			previous = current + 1;
			current = line.find(delim, previous);
		}
		cont.push_back(line.substr(previous, current - previous));
		return cont;
	}

	// Converts String to card. Examplary String: 3S
	BaseCard convertToCard(std::string string_card)
	{
		Mapping mapping;
				
		// Convert string to cards and add cards to hand
		std::string rank(1, string_card.at(0) );
		std::string suit(1, string_card.at(1) );
		BaseCard card(
			mapping.text_mappings.left.at(rank), 
			mapping.text_mappings.left.at(suit) 
			);

		return card;
	}

    // Converts String read from file to class hand. Examplary String: 3S 9D AS JC 4D 9H 10H
	poker::Hand convertToHand(std::string string_hand)
	{
		poker::Hand hand;
		std::vector<std::string> cont = split(string_hand); 
		
		// Convert string to cards and add cards to hand
		for(const auto& card: cont)
		{
			hand.addToHand(convertToCard(card));
		}
		return hand;
	}

}// end namespace UnitTest