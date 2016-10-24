/**
Wes Hartmann - PIC 10C
Professor R. Salazar
24 October 2016

This is the main file of the implementation of the game 'Sieto y Medio'
It allows the user to place bets and request or deny new cards. The player
will place a bet, evaluate his or her hand and decide if another card is
neccessary. After the player denies a card or busts, the dealer will begin
collecting cards. The player wins by not busting and having a higher point
total than the dealer.

The player begins with $100
Gameplay continues until the player has $0, or the dealer loses $900.
*/

#include <iostream>
#include <vector>
#include <iomanip>
#include <stdio.h>
#include <algorithm>
#include <fstream>
#include "cards.h"

int main() {

	const double MAX_HAND_TOTAL = 7.5;
	const int MAX_DEALER_LOSSES = 900;
	Player player(100);
	Hand my_hand;
	Hand dealer_hand;
	//tracks how much money the dealer loses
	int dealer_losses = 0;
	int bet = 0;
	ofstream gamelog;

	gamelog.open("gamelog.txt");


newRound:
	//exacutes after the first round has finished
	//stores information about the most recent round in the file gamelog.txt
	if (player.get_rounds() != 0) {
		gamelog << "-----------------------------------------------" << std::endl << std::endl;
		gamelog << "Game number: " << player.get_rounds();
		gamelog << "          " << "Money left: $" << player.get_money()
			<< std::endl << std::endl;
		gamelog << "Your cards:" << std::endl;
		for (size_t pos = 0; pos != my_hand.get_cur_hand().size(); ++pos) {
			gamelog << "          "
				<< my_hand.get_cur_hand()[pos].get_spanish_rank() << " de " << my_hand.get_cur_hand()[pos].get_spanish_suit();
			gamelog << "          "
				<< "(" << my_hand.get_cur_hand()[pos].get_english_rank() << " of "
				<< my_hand.get_cur_hand()[pos].get_english_suit() << ")" << std::endl;
		}
		gamelog << "Your total: " << my_hand.get_total() << "." << std::endl << std::endl;

		gamelog << "Dealer's cards:" << std::endl;
		for (size_t pos = 0; pos != dealer_hand.get_cur_hand().size(); ++pos) {
			gamelog << "          "
				<< dealer_hand.get_cur_hand()[pos].get_spanish_rank() << " de " << dealer_hand.get_cur_hand()[pos].get_spanish_suit();
			gamelog << "          "
				<< "(" << dealer_hand.get_cur_hand()[pos].get_english_rank() << " of "
				<< dealer_hand.get_cur_hand()[pos].get_english_suit() << ")" << std::endl;
		}
		gamelog << "Dealer's total: " << dealer_hand.get_total() << "." << std::endl << std::endl;
	}
	
	//clears both hands and sets totals back to 0
	my_hand.reshuffle(); dealer_hand.reshuffle();

	while ((player.get_money() > 0 && dealer_losses < MAX_DEALER_LOSSES) || player.get_rounds() == 0) {

		char another_card = 'y';

		do {
			std::cout << "You have $" << player.get_money() << ". Enter bet: ";
			std::cin >> bet;
			//insures player does not bet more money than they have
			if (bet > player.get_money()) {
				std::cout << "You don't have $" << bet << " to bet. Try again." << std::endl;
				bet = 0;
			}
		} while (bet == 0);

		Card first_card;
		my_hand.push_back(first_card);
		my_hand.add_to_total(first_card.get_rank());
		
		//executes while player wants another card and has not breached 7.5 points
		while (another_card == 'y' && my_hand.get_total() <= MAX_HAND_TOTAL) {

			if (my_hand.get_cur_hand().size() != 1) {
				std::cout << "New card:" << std::endl;
				std::cout << std::setw(20)
					<< my_hand.get_cur_hand().back().get_spanish_rank() << " de " << my_hand.get_cur_hand().back().get_spanish_suit();
				std::cout << std::setw(20)
					<< "(" << my_hand.get_cur_hand().back().get_english_rank() << " of "
					<< my_hand.get_cur_hand().back().get_english_suit() << ")" << std::endl << std::endl;
				//left out the sort function because it caused program to fail
				//std::sort(my_hand.get_cur_hand().begin(), my_hand.get_cur_hand().end());
			}

			std::cout << "Your cards:" << std::endl;
			//prints to the screen the cards in the player's hand. Formatting errors
			for (size_t pos = 0; pos != my_hand.get_cur_hand().size(); ++pos) {
				std::cout << std::setfill(' ') << std::setw(20);
				std::cout << my_hand.get_cur_hand()[pos].get_spanish_rank() << " de " << my_hand.get_cur_hand()[pos].get_spanish_suit();
				std::cout << std::setfill(' ') << std::setw(20);
				std::cout << "(" << my_hand.get_cur_hand()[pos].get_english_rank() << " of "
					<< my_hand.get_cur_hand()[pos].get_english_suit() << ")" << std::endl;
			}

			std::cout << "Your total is " << my_hand.get_total() << ". Do you want another card? (y/n) ";
			std::cin >> another_card;
			
			//adds new card to the back of the hand
			if (another_card == 'y') {
				Card* next_card = new Card;
				my_hand.push_back(*next_card);
				my_hand.add_to_total(next_card->get_rank());
				delete next_card;
			}
		}
		
		//executes after player has full hand. Populates dealer's hand
		while (dealer_hand.get_total() <= MAX_HAND_TOTAL) {
			
			//executes if dealer's total surpasses player's total
			if (dealer_hand.get_total() > my_hand.get_total()) {
				std::cout << "Too bad. You lose $" << bet << std::endl << std::endl;
				player.subtract_bet(bet);
				player.increment_rounds();
				//begins a new round of play
				goto newRound;
			}
			//executes if the round is a draw
			else if (dealer_hand.get_total() == my_hand.get_total()) {
				std::cout << "Nobody wins!" << std::endl << std::endl;
				player.increment_rounds();
				goto newRound;
			}

			Card* next_card = new Card;
			dealer_hand.push_back(*next_card);
			dealer_hand.add_to_total(next_card->get_rank());
			delete next_card;

			if (dealer_hand.get_cur_hand().size() != 1) {
				std::cout << "New card:" << std::endl;
				std::cout << std::setw(20)
					<< dealer_hand.get_cur_hand().back().get_spanish_rank() << " de " << dealer_hand.get_cur_hand().back().get_spanish_suit();
				std::cout << std::setw(20)
					<< "(" << dealer_hand.get_cur_hand().back().get_english_rank() << " of "
					<< dealer_hand.get_cur_hand().back().get_english_suit() << ")" << std::endl << std::endl;
				//std::sort(dealer_hand.get_cur_hand().begin(), dealer_hand.get_cur_hand().end());
			}

			std::cout << "Dealer's cards:" << std::endl;
			for (size_t pos = 0; pos != dealer_hand.get_cur_hand().size(); ++pos) {
				std::cout << std::setfill(' ') << std::setw(20);
				std::cout << dealer_hand.get_cur_hand()[pos].get_spanish_rank() << " de " << dealer_hand.get_cur_hand()[pos].get_spanish_suit();
				std::cout << std::setfill(' ') << std::setw(20);
				std::cout << "(" << dealer_hand.get_cur_hand()[pos].get_english_rank() << " of "
					<< dealer_hand.get_cur_hand()[pos].get_english_suit() << ")" << std::endl;
			}

			std::cout << "The dealer's total is " << dealer_hand.get_total() << std::endl << std::endl;

			if (dealer_hand.get_total() > MAX_HAND_TOTAL) {
				//executes if dealer busts but player total remians under 7.5
				if (my_hand.get_total() <= MAX_HAND_TOTAL) {
					std::cout << "You win $" << bet << std::endl << std::endl;
					player.collect_prize(bet);
					dealer_losses += bet;
					player.increment_rounds();
					goto newRound;
				}
				//executes if both dealer and player bust
				else if (my_hand.get_total() > MAX_HAND_TOTAL) {
					std::cout << "House advantage! Too bad. You lose $" << bet << std::endl << std::endl;
					player.subtract_bet(bet);
					player.increment_rounds();
					goto newRound;
				}
			}
		}
	}
	
	//farewell messages will be printed to screen upon completion of a game of sieto y medio
	if (player.get_money() >= 0) {
		std::cout << "You have $0. GAME OVER!" << std::endl
			<< "Come back when you have more money." << std::endl << std::endl
			<< "Bye!" << std::endl;
	}
	else if (dealer_losses >= MAX_DEALER_LOSSES) {
		std::cout << "Congratulations! You beat the casino!" << std::endl << std::endl
			<< "Bye!" << std::endl;
	}
	//gamelog formatting
	gamelog << "-----------------------------------------------";
	gamelog.close();
}
