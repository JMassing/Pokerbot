#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <fstream>
#include <utility>

#include "CardBuffer.hpp"
#include "BaseCard.hpp"
#include "Card.hpp"
#include "Mapping.hpp"
#include "HelperFunctions.hpp"

namespace UnitTest
{

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
				detect::BaseCard result = convertToCard(cont[1]);
				std::vector<std::string> cards = split(cont[0], ' ');
				for(const auto& string_card: cards)
				{
					detect::BaseCard base_card = convertToCard(string_card);
					detect::Card card(base_card.rank, base_card.suit);
					buffer.put(card, 0);					
				}
				buffer.getCard(detected_card);
				detect::BaseCard detected_base_card = detected_card;
				EXPECT_EQ(result, detected_base_card);
			}

			file.close();
		}
		else
		{
			std::cerr << "Could not open file" << std::endl;
		}
	}

} // end namespace unit test