#include "cards.h"
#include <cstdlib>
#include <iostream>

/*
You might or might not need these two extra libraries
#include <iomanip>
#include <algorithm>
*/


/* *************************************************
Card class
************************************************* */

/*
Default constructor for the Card class.
It could give repeated cards. This is OK.
Most variations of Blackjack are played with
several decks of cards at the same time.
*/
Card::Card() {
	int r = 1 + rand() % 4;
	switch (r) {
	case 1: suit = OROS; break;
	case 2: suit = COPAS; break;
	case 3: suit = ESPADAS; break;
	case 4: suit = BASTOS; break;
	default: break;
	}

	r = 1 + rand() % 10;
	switch (r) {
	case  1: rank = AS; break;
	case  2: rank = DOS; break;
	case  3: rank = TRES; break;
	case  4: rank = CUATRO; break;
	case  5: rank = CINCO; break;
	case  6: rank = SEIS; break;
	case  7: rank = SIETE; break;
	case  8: rank = SOTA; break;
	case  9: rank = CABALLO; break;
	case 10: rank = REY; break;
	default: break;
	}
}

// Accessor: returns a string with the suit of the card in Spanish 
string Card::get_spanish_suit() const {
	string suitName;
	switch (suit) {
	case OROS:
		suitName = "oros";
		break;
	case COPAS:
		suitName = "copas";
		break;
	case ESPADAS:
		suitName = "espadas";
		break;
	case BASTOS:
		suitName = "bastos";
		break;
	default: break;
	}
	return suitName;
}

// Accessor: returns a string with the rank of the card in Spanish 
string Card::get_spanish_rank() const {
	string rankName;
	switch (rank) {
	case AS:
		rankName = "As";
		break;
	case DOS:
		rankName = "Dos";
		break;
	case TRES:
		rankName = "Tres";
		break;
	case CUATRO:
		rankName = "Cuatro";
		break;
	case CINCO:
		rankName = "Cinco";
		break;
	case SEIS:
		rankName = "Seis";
		break;
	case SIETE:
		rankName = "Siete";
		break;
	case SOTA:
		rankName = "Sota";
		break;
	case CABALLO:
		rankName = "Caballo";
		break;
	case REY:
		rankName = "Rey";
		break;
	default: break;
	}
	return rankName;
}



// Accessor: returns a string with the suit of the card in English 
// This is just a stub! Modify it to your liking.
string Card::get_english_suit() const {
	string suitName;
	switch (suit) {
	case OROS:
		suitName = "golds";
		break;
	case COPAS:
		suitName = "cups";
		break;
	case ESPADAS:
		suitName = "swords";
		break;
	case BASTOS:
		suitName = "clubs";
		break;
	default: break;
	}
	return suitName;
}

// Accessor: returns a string with the rank of the card in English 
// This is just a stub! Modify it to your liking.
string Card::get_english_rank() const {
	string rankName;
	switch (rank) {
	case AS:
		rankName = "Ace";
		break;
	case DOS:
		rankName = "Two";
		break;
	case TRES:
		rankName = "Three";
		break;
	case CUATRO:
		rankName = "Four";
		break;
	case CINCO:
		rankName = "Five";
		break;
	case SEIS:
		rankName = "Six";
		break;
	case SIETE:
		rankName = "Seven";
		break;
	case SOTA:
		rankName = "Jack";
		break;
	case CABALLO:
		rankName = "Knight";
		break;
	case REY:
		rankName = "King";
		break;
	default: break;
	}
	return rankName;
}



// Assigns a numerical value to card based on rank.
// AS=1, DOS=2, ..., SIETE=7, SOTA=10, CABALLO=11, REY=12
double Card::get_rank() const {
	double value;
	switch (rank) {
	case AS:
		value = 1;
		break;
	case DOS:
		value = 2;
		break;
	case TRES:
		value = 3;
		break;
	case CUATRO:
		value = 4;
		break;
	case CINCO:
		value = 5;
		break;
	case SEIS:
		value = 6;
		break;
	case SIETE:
		value = 7;
		break;
	case SOTA:
		value = 0.5;
		break;
	case CABALLO:
		value = 0.5;
		break;
	case REY:
		value = 0.5;
		break;
	default: break;
	}
	return value;
}

// Comparison operator for cards
// Returns TRUE if card1 < card2
bool Card::operator < (Card card2) const {
	return rank < card2.rank;
}



/* *************************************************
Hand class
************************************************* */
//Constructor: constructs Hand object with an empty vector of Card objects
Hand::Hand() {
	cur_hand.clear();
}

//Accessor: pushes Card c to the back of cur_hand
void Hand::push_back(Card c) {
	cur_hand.push_back(c);
}

//Accessor: clears the hand and resets total
void Hand::reshuffle() {
	cur_hand.clear();
	total = 0;
}

//Accessor: returns the current hand as a vector of Card objects
vector<Card> Hand::get_cur_hand() {
	return cur_hand;
}

//Accessor: returns the point total of the hand 
double Hand::get_total() {
	return total;
}

//Accessor: adds 'add' to the total point value
void Hand::add_to_total(double add) {
	total += add;
}

//Accessor: resets the point toal to 0
	void Hand::reset_total(){
		total = 0;
}



/* *************************************************
Player class
************************************************* */

//Constructor: constructs a Player object with money = int m
Player::Player(int m) {
		money = m;
	}
//Accessor: returns player's money
int Player::get_money() {
		return money;
	}

//Accessor: deducts the bet from player's total money
	void Player::subtract_bet(int bet) {
		money -= bet;
	}

//Accessor: rewards the bet to player's total money
	void Player::collect_prize(int prize) {
		money += prize;
	}

//Accessor: returns the number of rounds played so far
	int Player::get_rounds() {
		return rounds;
	}

//Accessor: adds one to the current # of rouCommented nds
	void Player::increment_rounds() {
		++rounds;
	}
