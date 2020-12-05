#include <boost/filesystem.hpp>
#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <utility>

#include "CardBuffer.hpp"
#include "BaseCard.hpp"
#include "Card.hpp"
#include "Mapping.hpp"
#include "HelperFunctions.hpp"

namespace fs = boost::filesystem;

namespace UnitTest
{

	GTEST_TEST(TestCardBuffer, TestAll)
	{
		detect::CardBuffer<10> buffer(0);

		std::ifstream file;
		fs::path filename = fs::current_path() / "unit_tests" / "utilities" / "DetectCardlists" / "buffer.txt";
		// Read player hands from file
		file.open(filename.string());	
		std::string line;
		detect::Card detected_card;
		if(file.is_open())
		{
			while(std::getline(file, line))
			{
				std::vector<std::string> cont = split(line, ';');
				BaseCard result = convertToCard(cont[1]);
				std::vector<std::string> cards = split(cont[0], ' ');
				for(const auto& string_card: cards)
				{
					BaseCard base_card = convertToCard(string_card);
					detect::Card card(base_card.rank, base_card.suit);
					buffer.put(card, 0);					
				}
				buffer.getCard(detected_card);
				BaseCard detected_base_card = detected_card;
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