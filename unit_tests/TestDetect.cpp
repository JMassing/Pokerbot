#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <fstream>
#include <utility>

#include "CardBuffer.h"
#include "Card.h"
#include "Mapping.h"

namespace UnitTest{

	// Split string_hand
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

	// Converts String read from file to class hand. Examplary String: 3S 9D AS JC 4D 9H 10H
	detect::Card convertToCard(std::string string_card)
	{
		detect::Mapping mapping;
				
		// Convert string to cards and add cards to hand
		std::string rank(1, string_card.at(0) );
		std::string suit(1, string_card.at(1) );
		detect::Card card(mapping.text_mappings.left.at(rank), mapping.text_mappings.left.at(suit) );

		return card;
	}

	TEST(TestDetect,TestCardBuffer)
	{
		detect::CardBuffer<10> buffer(0);

		std::ifstream file;
		// Read player hands from file
		file.open("C:\\Users\\julim\\Desktop\\Projects\\Pokerbot\\unit_tests\\utilities\\DetectCardlists\\buffer.txt");	
		std::string line;
		detect::Card detected_card;
		if(file.is_open())
		{
			while(std::getline(file, line))
			{
				std::vector<std::string> cont = split(line, ';');
				detect::Card result = convertToCard(cont[1]);
				std::vector<std::string> cards = split(cont[0], ' ');
				for(const auto& string_card: cards)
				{
					detect::Card card = convertToCard(string_card);
					buffer.put(card, 0);					
				}
				buffer.getCard(detected_card);
				EXPECT_EQ(result, detected_card);
			}

			file.close();
		}
		else
		{
			std::cerr << "Could not open file" << std::endl;
		}
	}

} // end namespace unit test