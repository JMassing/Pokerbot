#pragma once

#include "Mapping.hpp"

	/** \defgroup shared
	* This modules contains classes that are shared between all modules.
 	* @{
	* @class BaseCard
	* @author Julian Massing (julimassing@gmail.com)
	* @brief Data structure representing a playing card
	*		
	* @version 1.0
	* @date 2020-11-22
	* 
	* @copyright Copyright (c) 2020
	* 
	*/
	/**@}*/
	struct BaseCard
	{
		int rank;
		int suit;

		bool operator==(const BaseCard& other) const
		{
			// if suit and rank are equal, the cards are the same cards, since there is only one copy of each card in the deck.
			return (this->rank == other.rank && this->suit == other.suit);
		};

		bool operator!=(const BaseCard& other) const
		{
			// if suit or rank are not equal, the cards are different cards, since there is only one copy of each card in the deck.
			return (this->rank != other.rank || this->suit != other.suit);
		};

		BaseCard() : rank(UNKNOWN), suit(UNKNOWN){};
		BaseCard(const int& rank, const int& suit) :rank(rank), suit(suit){};
		~BaseCard() {};

		BaseCard(const BaseCard& other) = default;	
		BaseCard& operator=(const BaseCard& other) = default;
		BaseCard(BaseCard&& other) noexcept = default;
		BaseCard& operator=(BaseCard&& other) noexcept = default;

		
	};
