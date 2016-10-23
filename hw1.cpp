/** insert description later*/

#include <iostream>
#include <vector>
#include <iomanip>
#include <stdio.h>
#include <algorithm>
#include "cards.h"

int main() {

	const double MAX_HAND_TOTAL = 7.5;
	const int MAX_DEALER_LOSSES = 900;
	Player player(100);
	Hand my_hand;
	Hand dealer_hand;
	int dealer_losses = 0;
	int bet = 0;


	newRound:

	while ((player.get_money() >= 0 && dealer_losses < MAX_DEALER_LOSSES)|| player.get_rounds() == 0){

		char another_card = 'y';

		do {
			std::cout << "You have $" << player.get_money() << ". Enter bet: ";
			std::cin >> bet;
			if (bet > player.get_money()) {
				std::cout << "You don't have $" << bet << " to bet. Try again." << std::endl;
				bet = 0;
			}
		}while (bet == 0);
		
		Card first_card;
		my_hand.push_back(first_card);
		my_hand.add_to_total(first_card.get_rank());

		while (another_card == 'y' && my_hand.get_total() <= MAX_HAND_TOTAL) {

			if (my_hand.get_cur_hand().size() != 1) {
				std::cout << "New card:" << std::endl;
				std::cout << std::setw(20)
					<< my_hand.get_cur_hand().back().get_spanish_rank() << " de " << my_hand.get_cur_hand().back().get_spanish_suit();
				std::cout << std::setw(20)
					<< "(" << my_hand.get_cur_hand().back().get_english_rank() << " of "
					<< my_hand.get_cur_hand().back().get_english_suit() << ")" << std::endl << std::endl;
				std::sort(my_hand.get_cur_hand().begin(), my_hand.get_cur_hand().end());
			}

			std::cout << "Your cards:" << std::endl;
			for (size_t pos = 0; pos != my_hand.get_cur_hand().size(); ++pos) {
				std::cout << std::setfill(' ') << std::setw(20);
				std::cout << my_hand.get_cur_hand()[pos].get_spanish_rank() << " de " << my_hand.get_cur_hand()[pos].get_spanish_suit();
				std::cout << std::setfill(' ') << std::setw(20);
				std::cout << "(" << my_hand.get_cur_hand()[pos].get_english_rank() << " of "
					<< my_hand.get_cur_hand()[pos].get_english_suit() << ")" << std::endl;
			}

			std::cout << "Your total is " << my_hand.get_total() << ". Do you want another card? (y/n) ";
			std::cin >> another_card;

			if (another_card == 'y') {
				Card* next_card = new Card;
				my_hand.push_back(*next_card);
				my_hand.add_to_total(next_card->get_rank());
				delete next_card;
			}
		}

		while (dealer_hand.get_total() <= MAX_HAND_TOTAL) {

			if (dealer_hand.get_total() > my_hand.get_total()) {
				std::cout << "Too bad. You lose $" << bet << std::endl << std::endl;
				player.subtract_bet(bet);
				player.increment_rounds();
				my_hand.reshuffle(); dealer_hand.reshuffle();
				goto newRound;
			}
			else if (dealer_hand.get_total() == my_hand.get_total()) {
				std::cout << "Nobody wins!" << std::endl << std::endl;
				player.increment_rounds();
				my_hand.reshuffle(); dealer_hand.reshuffle();
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
				std::sort(dealer_hand.get_cur_hand().begin(), dealer_hand.get_cur_hand().end());
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
				if (my_hand.get_total() <= MAX_HAND_TOTAL) {
					std::cout << "You win $" << bet << std::endl << std::endl;
					player.collect_prize(bet);
					dealer_losses += bet;
					player.increment_rounds();
					my_hand.reshuffle(); dealer_hand.reshuffle();
					goto newRound;
				}
				else if (my_hand.get_total() > MAX_HAND_TOTAL) {
					std::cout << "House advantage! Too bad. You lose $" << bet << std::endl << std::endl;
					player.subtract_bet(bet);
					player.increment_rounds();
					my_hand.reshuffle(); dealer_hand.reshuffle();
					goto newRound;
				}
			}
		}
	}

}
/*Contact GitHub API Training Shop Blog About
© 2016 GitHub, Inc.Terms Privacy Security Status Help*/
