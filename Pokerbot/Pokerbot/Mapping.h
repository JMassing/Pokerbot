#pragma once

#include <boost/bimap/bimap.hpp>

namespace detect
{
	const enum Ranks { UNKNOWN_RANK = 0, ACE_LOW, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE };
	const enum Suits { UNKNOWN_SUIT = 0, DIAMONDS = 15, CLUBS = 16, HEARTS = 17, SPADES = 18 };

	struct Mapping
	{
		boost::bimaps::bimap<std::string, int> card_mappings;

		Mapping() { this->loadMapping(); }
		~Mapping() {};

		// Using default copy and move constructors. 
		Mapping(const Mapping& other) = default;
		Mapping& operator=(const Mapping& other) = default;
		Mapping(Mapping&& other) noexcept = default;
		Mapping& operator=(Mapping&& other) noexcept = default;

	private:
		void loadMapping()
		{
			this->card_mappings.insert(boost::bimaps::bimap<std::string, int>::value_type("Two", TWO));
			this->card_mappings.insert(boost::bimaps::bimap<std::string, int>::value_type("Three", THREE));
			this->card_mappings.insert(boost::bimaps::bimap<std::string, int>::value_type("Four", FOUR));
			this->card_mappings.insert(boost::bimaps::bimap<std::string, int>::value_type("Five", FIVE));
			this->card_mappings.insert(boost::bimaps::bimap<std::string, int>::value_type("Six", SIX));
			this->card_mappings.insert(boost::bimaps::bimap<std::string, int>::value_type("Seven", SEVEN));
			this->card_mappings.insert(boost::bimaps::bimap<std::string, int>::value_type("Eight", EIGHT));
			this->card_mappings.insert(boost::bimaps::bimap<std::string, int>::value_type("Nine", NINE));
			this->card_mappings.insert(boost::bimaps::bimap<std::string, int>::value_type("Ten", TEN));
			this->card_mappings.insert(boost::bimaps::bimap<std::string, int>::value_type("Jack", JACK));
			this->card_mappings.insert(boost::bimaps::bimap<std::string, int>::value_type("Queen", QUEEN));
			this->card_mappings.insert(boost::bimaps::bimap<std::string, int>::value_type("King", KING));
			this->card_mappings.insert(boost::bimaps::bimap<std::string, int>::value_type("Ace", ACE));

			this->card_mappings.insert(boost::bimaps::bimap<std::string, int>::value_type("Diamonds", DIAMONDS));
			this->card_mappings.insert(boost::bimaps::bimap<std::string, int>::value_type("Hearts", HEARTS));
			this->card_mappings.insert(boost::bimaps::bimap<std::string, int>::value_type("Clubs", CLUBS));
			this->card_mappings.insert(boost::bimaps::bimap<std::string, int>::value_type("Spades", SPADES));
		}
	};


} // namespace detect
