#pragma once

#include <boost/bimap/bimap.hpp>

namespace detect
{
	const enum Cards { UNKNOWN = 0, ACE_LOW, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE, DIAMONDS, CLUBS, HEARTS, SPADES };
	const enum Hands { HIGH_CARD, PAIR, TWO_PAIR, THREE_OF_A_KIND, STRAIGHT, FLUSH, FULL_HOUSE, FOUR_OF_A_KIND, STRAIGHT_FLUSH};

	class Mapping
	{
	
		private:
			void loadImageMapping()
			{
				this->image_mappings.insert(boost::bimaps::bimap<std::string, int>::value_type("?", UNKNOWN));
				this->image_mappings.insert(boost::bimaps::bimap<std::string, int>::value_type("Ace_Low", ACE_LOW));
				this->image_mappings.insert(boost::bimaps::bimap<std::string, int>::value_type("Two", TWO));
				this->image_mappings.insert(boost::bimaps::bimap<std::string, int>::value_type("Three", THREE));
				this->image_mappings.insert(boost::bimaps::bimap<std::string, int>::value_type("Four", FOUR));
				this->image_mappings.insert(boost::bimaps::bimap<std::string, int>::value_type("Five", FIVE));
				this->image_mappings.insert(boost::bimaps::bimap<std::string, int>::value_type("Six", SIX));
				this->image_mappings.insert(boost::bimaps::bimap<std::string, int>::value_type("Seven", SEVEN));
				this->image_mappings.insert(boost::bimaps::bimap<std::string, int>::value_type("Eight", EIGHT));
				this->image_mappings.insert(boost::bimaps::bimap<std::string, int>::value_type("Nine", NINE));
				this->image_mappings.insert(boost::bimaps::bimap<std::string, int>::value_type("Ten", TEN));
				this->image_mappings.insert(boost::bimaps::bimap<std::string, int>::value_type("Jack", JACK));
				this->image_mappings.insert(boost::bimaps::bimap<std::string, int>::value_type("Queen", QUEEN));
				this->image_mappings.insert(boost::bimaps::bimap<std::string, int>::value_type("King", KING));
				this->image_mappings.insert(boost::bimaps::bimap<std::string, int>::value_type("Ace", ACE));

				this->image_mappings.insert(boost::bimaps::bimap<std::string, int>::value_type("Diamonds", DIAMONDS));
				this->image_mappings.insert(boost::bimaps::bimap<std::string, int>::value_type("Hearts", HEARTS));
				this->image_mappings.insert(boost::bimaps::bimap<std::string, int>::value_type("Clubs", CLUBS));
				this->image_mappings.insert(boost::bimaps::bimap<std::string, int>::value_type("Spades", SPADES));
			}

			void loadTextMapping()
			{
				this->text_mappings.insert(boost::bimaps::bimap<std::string, int>::value_type("?", UNKNOWN));
				this->text_mappings.insert(boost::bimaps::bimap<std::string, int>::value_type("1", ACE_LOW));
				this->text_mappings.insert(boost::bimaps::bimap<std::string, int>::value_type("2", TWO));
				this->text_mappings.insert(boost::bimaps::bimap<std::string, int>::value_type("3", THREE));
				this->text_mappings.insert(boost::bimaps::bimap<std::string, int>::value_type("4", FOUR));
				this->text_mappings.insert(boost::bimaps::bimap<std::string, int>::value_type("5", FIVE));
				this->text_mappings.insert(boost::bimaps::bimap<std::string, int>::value_type("6", SIX));
				this->text_mappings.insert(boost::bimaps::bimap<std::string, int>::value_type("7", SEVEN));
				this->text_mappings.insert(boost::bimaps::bimap<std::string, int>::value_type("8", EIGHT));
				this->text_mappings.insert(boost::bimaps::bimap<std::string, int>::value_type("9", NINE));
				this->text_mappings.insert(boost::bimaps::bimap<std::string, int>::value_type("0", TEN));
				this->text_mappings.insert(boost::bimaps::bimap<std::string, int>::value_type("J", JACK));
				this->text_mappings.insert(boost::bimaps::bimap<std::string, int>::value_type("Q", QUEEN));
				this->text_mappings.insert(boost::bimaps::bimap<std::string, int>::value_type("K", KING));
				this->text_mappings.insert(boost::bimaps::bimap<std::string, int>::value_type("A", ACE));

				this->text_mappings.insert(boost::bimaps::bimap<std::string, int>::value_type("D", DIAMONDS));
				this->text_mappings.insert(boost::bimaps::bimap<std::string, int>::value_type("H", HEARTS));
				this->text_mappings.insert(boost::bimaps::bimap<std::string, int>::value_type("C", CLUBS));
				this->text_mappings.insert(boost::bimaps::bimap<std::string, int>::value_type("S", SPADES));
			}
			
		public:
			boost::bimaps::bimap<std::string, int> image_mappings;
			boost::bimaps::bimap<std::string, int> text_mappings;


			Mapping() {
				this->loadImageMapping(); 
				this->loadTextMapping();
				}
			~Mapping() {};

			// Using default copy and move constructors. 
			Mapping(const Mapping& other) = default;
			Mapping& operator=(const Mapping& other) = default;
			Mapping(Mapping&& other) noexcept = default;
			Mapping& operator=(Mapping&& other) noexcept = default;

		};


} // namespace detect
