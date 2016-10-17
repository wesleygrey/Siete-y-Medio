/** insert description later*/

#include <iostream>
#include <vector>
#include <iomanip>

int main(){
  
  const double MAX_HAND_TOTAL = 7.5;
  Player player(100);
  Hand my_hand;
  Hand dealer_hand;
  char another_card = 'y';
  int bet = 0;
  
  std::cout << "You have $" << player.get_money() << ". Enter bet: ";
  std::cin >> bet;
  
  Card first_card;
  my_hand.hand.push_back(first_card);
  
  while(another_card = 'y' && my_hand.total <= MAX_HAND_TOTAL){
    
    if(my_hand.hand.size() != 1){
    std::cout << "New card:" << std::endl;
      std::cout << "        " << std::setw(20) << std::left() 
      << my_hand.back().get_spansih_rank() << " de " << my_hand.back().get_spanish_suit();
    std::cout << std::setw(20) << std::left() 
      << my_hand.back().get_english_rank() << " of " << my_hand.back().get_english_suit()
      <<std::endl;
    }
    
    std::cout << "Your cards:" << std::endl;
   for(size_t pos = 0; pos != my_hand.hand.size(); ++pos){
    std::cout << std::endl << "        " << std::setw(20) << std::left() 
      << my_hand[pos].get_spansih_rank() << " de " << my_hand[pos].get_spanish_suit();
    std::cout << std::setw(20) << std::left() 
      << my_hand[pos].get_english_rank() << " of " << my_hand[pos].get_english_suit()
      <<std::endl;
   }
    
  }
  
}
