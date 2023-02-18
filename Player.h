// generic player class to be inherited by a spefic game player class (ex: blackJackPlayer)

#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include "CardDeck.h"
using namespace std;

struct summary {
	int round;
	int round_money;
	bool win_status;
};

class Player : public CardDeck {

private:

	int money;
	vector<summary> player_summary;

public:

	bool bust_status;

	Player();
	~Player();


	//void checkStatus(); // check if all money is lost
	int getHandValue(); // determines value of player's hand and returns it
	int getCardValue(int); // determine value of card at arg - 1 (index location of card)

	bool subtractMoney(int); // decreases money by bet amt; returns true if money is 0 or less
	void addMoney(int);
	void returnMoney(int); // give back the betted amount to player
	//void returnCards(); // returns all of player's cards to main deck for shuffling.

	// there will be an object called main deck that uses these functions
	void CallBackAllCards(Player::CardDeck&, Player::CardDeck&, Player::CardDeck&, Player::CardDeck&, Player::CardDeck&); // called by the player obj which acts as the main_deck // just dealer and player for now

	void CallBackCards(Player&); // called by the player obj which acts as the main_deck
	
	bool determineHit(); // for non-human players to determine where they will hit (true) or stand (false).

	void addSummary(int); // adds results of current match to vector
	void getSummary(); // iteratively extracts results and reports them neatly to screen

	int checkMoney(); // returns current value of player 

	int makeBet(); // for non-human players. randomly chooses a bet amount based on money availible.

	void determineResults(Player&, Player&, Player&, Player&, int, int, int, int); // compare different hands and determine results of round. Return an integer the reflects the scenario

};

Player::Player() {
	money = 100;
}

Player::~Player() {

}


int Player::checkMoney() {
	return money;
}

void Player::addMoney(int bet_amt) {
	money += bet_amt * 2;
}

bool Player::subtractMoney(int bet_amt) {
	money -= bet_amt;

	if (money <= 0) {
		return true;
	}
	else {
		return false;
	}

}

int Player::makeBet() {
	int bet_amt = 0;

	bet_amt = 1 + (rand() % 100);

	return bet_amt;
}

void Player::returnMoney(int original_bet) {
	money += original_bet;
}


int Player::getHandValue() {

	int hand_value = 0;
	// if a joker is detected in hand, return 21

	// check value of each card presently in hand and add them
	for (int i = 0; i < hand.size(); i++) {

		switch (hand[i].ID) {

		case 1:
			if (hand_value + 10 > 21) {
				hand_value += 1;
			}
			else {
				hand_value += 11;
			}
			break;

		case 2:
			hand_value += 2;
			break;

		case 3:
			hand_value += 3;
			break;

		case 4:
			hand_value += 4;
			break;

		case 5:
			hand_value += 5;
			break;

		case 6:
			hand_value += 6;
			break;

		case 7:
			hand_value += 7;
			break;

		case 8:
			hand_value += 8;
			break;

		case 9:
			hand_value += 9;
			break;

		case 10:
			hand_value += 10;
			break;

		case 11:
			hand_value += 10;
			break;

		case 12:
			hand_value += 10;
			break;

		case 13:
			hand_value += 10;
			break;

		case 14:
			//hand_value = 21 - hand_value; // resultant value is amt needed for a black jack
			return 21;
			break;
		}
	}

	

	return hand_value;
}


int Player::getCardValue(int card_choice) {
	
	int card_value = 0;
	
	// debug
	//cout << "debug" << endl;
	//cout << hand[card_choice - 1].name << " of " << hand[card_choice - 1].suite << endl;
	//cout << hand[card_choice - 1].ID << endl;

	switch (hand[card_choice - 1].ID) {

	case 1:
		if (card_value + 10 > 21) {
			card_value += 1;
		}
		else {
			card_value += 11;
		}
		break;

	case 2:
		card_value += 2;
		break;

	case 3:
		card_value += 3;
		break;

	case 4:
		card_value += 4;
		break;

	case 5:
		card_value += 5;
		break;

	case 6:
		card_value += 6;
		break;

	case 7:
		card_value += 7;
		break;

	case 8:
		card_value += 8;
		break;

	case 9:
		card_value += 9;
		break;

	case 10:
		card_value += 10;
		break;

	case 11:
		card_value += 10;
		break;

	case 12:
		card_value += 10;
		break;

	case 13:
		card_value += 10;
		break;

	case 14:
		card_value = 21 - card_value; // resultant value is amt needed for a black jack
		break;
	}

	return card_value;
}


void Player::CallBackCards(Player& player) {
	//cout << "!!!!!!" << player.hand.size() << endl; // debug
	int initial_deck_size = player.hand.size();
	for (int i = 0; i < initial_deck_size; i++) {
		addToHand(player.hand.back().name, player.hand.back().suite, player);
	}
}

void Player::CallBackAllCards(Player::CardDeck& hand_one, Player::CardDeck& hand_two, Player::CardDeck& hand_three, Player::CardDeck& hand_four, Player::CardDeck& hand_five) {

	int initial_deck_size1 = hand_one.hand.size();
	int initial_deck_size2 = hand_two.hand.size();
	int initial_deck_size3 = hand_three.hand.size();
	int initial_deck_size4 = hand_four.hand.size();
	int initial_deck_size5 = hand_five.hand.size();

	// hand 1
	for (int i = 0; i < initial_deck_size1; i++) {
		addToHand(hand_one.hand.back().name, hand_one.hand.back().suite, hand_one);
	}

	// hand 2
	for (int i = 0; i < initial_deck_size2; i++) {
		addToHand(hand_two.hand.back().name, hand_two.hand.back().suite, hand_two);
	}

	for (int i = 0; i < initial_deck_size3; i++) {
		addToHand(hand_three.hand.back().name, hand_three.hand.back().suite, hand_three);
	}

	for (int i = 0; i < initial_deck_size4; i++) {
		addToHand(hand_four.hand.back().name, hand_four.hand.back().suite, hand_four);
	}

	for (int i = 0; i < initial_deck_size5; i++) {
		addToHand(hand_five.hand.back().name, hand_five.hand.back().suite, hand_five);
	}

	shuffle();
}

bool Player::determineHit() {

	if (getHandValue() >= 17) {
		return false; // stand
	}
	else if (getHandValue() < 17) {
		return true; // hit
	}
}



void Player::addSummary(int current_round) {
	summary s;
	s.round = current_round;
	s.round_money = money;
	s.win_status = bust_status;

	player_summary.push_back(s);
}


void Player::getSummary() {

	cout << "\nPlayer Summary" << endl;
	cout << "**********************************" << endl;

	for (int i = 0; i < player_summary.size(); i++) {
		cout << "Round " << player_summary[i].round << ": ";
		if (player_summary[i].win_status == false) {
			cout << "Win" << endl;
		}
		else {
			cout << "Loss" << endl;
		}
		cout << "\nTotal money: $" << player_summary[i].round_money << endl;
		cout << "**********************************" << endl;
	}
}

void Player::determineResults(Player& user, Player& p2, Player& p3, Player& p4, int user_bet, int p2_bet, int p3_bet, int p4_bet) {
	if (bust_status == true) { // dealer bust scenario

		// nothing done with player bust scenarios

		// user
		if (user.bust_status == false) {
			// user doesn't bust

			cout << "You beat the dealer and earned: $ " << user_bet * 2 << endl;
			user.addMoney(user_bet);
			cout << "Your money: " << user.checkMoney() << endl;
		}

		// p2
		if (user.bust_status == false) {
			cout << "Player 2 beat the dealer and earned: $" << user_bet * 2 << endl;
			p2.addMoney(user_bet);
			cout << "Player 2' money: " << p2.checkMoney() << endl;
		}

		// p3
		if (p3.bust_status == false) {
			cout << "PLayer 3 beat the dealer and earned: $" << p3_bet * 2 << endl;
			p3.addMoney(p3_bet);
			cout << "Player 3's money: " << p3.checkMoney() << endl;
		}

		// p4
		if (p4.bust_status == false) {
			cout << "Player 4 beat the dealer and earned: $" << p4_bet * 2 << endl;
			p4.addMoney(p4_bet);
			cout << "Player 4's money: " << p4.checkMoney() << endl;
		}
	}
	else { // dealer doesn't bust scenario

		// user
		if(user.bust_status != true && user.getHandValue() > getHandValue()) {
			// scenario where user doesn't bust and hand is more powerful than dealer's
			// player wins
			cout << "You beat the dealer and earned: $" << user_bet * 2 << endl;
			user.addMoney(user_bet);
			cout << "Your money: " << user.checkMoney() << endl;
		}
		else if (user.bust_status != true && user.getHandValue() == getHandValue()) {
			// tie with dealer scenario
			// return bet
			cout << "You tied with the dealer and regained your bet of: $" << user_bet << endl;
			user.returnMoney(user_bet);
			cout << "Your money: " << user.checkMoney() << endl;
		}
		else { // player loses. Dealer had a more powerful hand
			cout << "You lost to the dealer and lost a bet of: $" << user_bet << endl;
			cout << "Your money: " << user.checkMoney() << endl;
		}

		// p2
		if (p2.bust_status != true && p2.getHandValue() > getHandValue()) {
			cout << "Player 2 beat the dealer and earned: $" << p2_bet * 2 << endl;
			p2.addMoney(p2_bet);
			cout << "Player 2's money: " << p2.checkMoney() << endl;
		}
		else if (p2.bust_status != true && p2.getHandValue() == getHandValue()) {
			// tie with dealer scenario
			// return bet
			cout << "Player 2 tied with the dealer and regained a bet of: $" << p2_bet << endl;
			p2.returnMoney(p2_bet);
			cout << "Player 2's money: " << p2.checkMoney() << endl;
		}
		else { // player loses. Dealer had a more powerful hand
			cout << "Player 2 lost to the dealer and lost a bet of: $" << p2_bet << endl;
			cout << "Player 2's money: " << p2.checkMoney() << endl;
		}

		// p3
		if (p3.bust_status != true && p3.getHandValue() > getHandValue()) {
			cout << "Player 3 beat the dealer and earned: $" << p3_bet * 2 << endl;
			p3.addMoney(p3_bet);
			cout << "Player 3' money: " << p3.checkMoney() << endl;
		}
		else if (p3.bust_status != true && p3.getHandValue() == getHandValue()) {
			// tie with dealer scenario
			// return bet
			cout << "Player 3 tied with the dealer and regained a bet of: $" << p3_bet << endl;
			p3.returnMoney(p3_bet);
			cout << "Player 3's money: " << p3.checkMoney() << endl;
		}
		else { // player loses. Dealer had a more powerful hand
			cout << "Player 3 lost to the dealer and lost a bet of: $" << p3_bet << endl;
			cout << "Player 3's money: " << p3.checkMoney() << endl;
		}

		// p4
		if (p4.bust_status != true && p4.getHandValue() > getHandValue()) {
			cout << "Player 4 beat the dealer and earned: $" << p4_bet * 2 << endl;
			p4.addMoney(p4_bet);
			cout << "Player 4's money: " << p4.checkMoney() << endl;
		}
		else if (p4.bust_status != true && p4.getHandValue() == getHandValue()) {
			// tie with dealer scenario
			// return bet
			cout << "Player 4 tied with the dealer and regained a bet of: $" << p4_bet << endl;
			p4.returnMoney(p4_bet);
			cout << "Player 4's money: " << p4.checkMoney() << endl;
		}
		else { // player loses. Dealer had a more powerful hand
			cout << "Player 4 lost to the dealer and lost a bet of: $" << p4_bet << endl;
			cout << "Player 4's money: " << p4.checkMoney() << endl;
		}
	}
}