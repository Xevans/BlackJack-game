// Card Deck class for card related operations
// can be inherited by a player class to access card operations and use its player functions (ex: hit, stand, pass, bet...etc)


#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <ctime>

//#include "PlayerBJ.h" // For BlackJack players // Cant do thia

using namespace std;

#define DECK 54

struct card {
	string name;
	string suite;
	int value; // not given by default
	int ID;
};

class CardDeck {

private:
	const string J = "JOKER";
	const string S = "SPADE";
	const string H = "HEART";
	const string D = "DIAMOND";
	const string C = "CLOVER";






public:

	vector<card> hand;
	vector<card> shuffle_hand;

	CardDeck();
	~CardDeck();

	void initDeck(bool); // if true, creates a deck with jokers. If false, creats one without.
	void createSuite(string);

	void showHand(); // show all card instances in vector to screen.

	void removeFromHand(string, string); // recieves the name and suite of a card, then removes it
	void addToHand(string, string, CardDeck&); // send card from other hand to this CardDeck hand
	void playCard(string, string, CardDeck&); // sends card to another hand; takes another CardDeck obj, accesses its add to hand member and copies the recieving card; calls remove from hand

	void shuffle(); // split cards in half between two vectors and shuffle cards between either side
	void swap();

	int checkHand(string, string); // checks hand for a card with members that match the arguments. if card is found returns index, else returns -1
	//void checkHandValue(); // check value of hand. NOTE: ALL VALUES MUST BE ESTABLISHED


};

CardDeck::CardDeck() {

}

CardDeck::~CardDeck() {

}

void CardDeck::initDeck(bool option) {
	// generate cards and push into a vector
	createSuite(S);
	createSuite(H);
	createSuite(D);
	createSuite(C);

	if (option == true) {
		// 2 jokers
		card n;
		n.name = J;
		n.suite = J;
		n.ID = 14;
		hand.push_back(n);
		hand.push_back(n);
	}
}

void CardDeck::createSuite(string suite) {

	card n;


	for (int i = 1; i <= 13; i++) {

		switch (i) {

		case 1:
			n.name = "ACE";
			n.ID = 1;
			break;

		case 2:
			n.name = "TWO";
			n.ID = 2;
			break;

		case 3:
			n.name = "THREE";
			n.ID = 3;
			break;

		case 4:
			n.name = "FOUR";
			n.ID = 4;
			break;

		case 5:
			n.name = "FIVE";
			n.ID = 5;
			break;

		case 6:
			n.name = "SIX";
			n.ID = 6;
			break;

		case 7:
			n.name = "SEVEN";
			n.ID = 7;
			break;

		case 8:
			n.name = "EIGHT";
			n.ID = 8;
			break;

		case 9:
			n.name = "NINE";
			n.ID = 9;
			break;

		case 10:
			n.name = "TEN";
			n.ID = 10;
			break;

		case 11:
			n.name = "JACK";
			n.ID = 11;
			break;

		case 12:
			n.name = "QUEEN";
			n.ID = 12;
			break;

		case 13:
			n.name = "KING";
			n.ID = 13;
			break;
		}

		n.suite = suite;
		hand.push_back(n);
	}
}

void CardDeck::showHand() {
	//cout << endl;
	for (int i = 0; i < hand.size(); i++) {
		cout << "Card " << i + 1 << ": " << hand[i].name << " of " << hand[i].suite << "S" << endl;
	}
	cout << endl << endl;
}

void CardDeck::addToHand(string name, string suite, CardDeck& other_hand) {

	int card_to_add = other_hand.checkHand(name, suite); // check other hand

	hand.push_back(other_hand.hand[card_to_add]); // push card from other hand to this hand

	other_hand.removeFromHand(name, suite); // remove card from other hand

}

void CardDeck::playCard(string name, string suite, CardDeck& other_hand) {

	int card_to_play = checkHand(name, suite); // look at your hand for the card you want to play

	// puch card from hand to other hand
	other_hand.hand.push_back(hand[card_to_play]); // take the card and place it in the other deck

	// remove card from hand
	removeFromHand(name, suite);
}


void CardDeck::removeFromHand(string name, string suite) {
	int card_to_remove = checkHand(name, suite);

	if (card_to_remove != -1) {
		hand.erase(hand.begin() + card_to_remove); // remove specific element from vector.
	}
	else {
		cout << "A" << name << " of " << suite << "s " << "does not exist in this hand..." << endl;
	}
}


int CardDeck::checkHand(string card_name, string card_suite) {
	for (int i = 0; i < hand.size(); i++) {
		if (hand[i].name == card_name && hand[i].suite == card_suite) {
			return i; // return location of card in hand
		}
	}

	return -1;
}

// does not account for odd number decks
void CardDeck::shuffle() {
	// check to see if there are cards in hand
	if (hand.size() == 0) {
		cout << "Cant shuffle without cards!" << endl;
		return;
	}

	int half_deck = hand.size() / 2;
	int full_deck = hand.size();

	for (int i = full_deck - 1; i > half_deck - 1; i--) {
		// transfer card in index of hand to shuffle_hand
		shuffle_hand.push_back(hand[i]);
		hand.erase(hand.begin() + i);
	}

	//showHand(); // debug

	srand(time(NULL));


	for (int i = 0; i < 100; i++) {
		// swap operation
		swap();
	}

	//showHand(); // debug

	// return cards to original deck
	for (int i = 0; i < shuffle_hand.size(); i++) {
		hand.push_back(shuffle_hand[i]);
	}

	shuffle_hand.clear();
}

void CardDeck::swap() {

	int pick1 = 0;
	int pick2 = 0;

	card sub1;
	card sub2;

	// random index in deck range
	pick1 = 1 + (rand() % hand.size());
	pick2 = 1 + (rand() % shuffle_hand.size());

	// temp card 1
	sub1.name = hand[pick1 - 1].name;
	sub1.suite = hand[pick1 - 1].suite;
	sub1.ID = hand[pick1 - 1].ID;

	// temp card 2
	sub2.name = shuffle_hand[pick2 - 1].name;
	sub2.suite = shuffle_hand[pick2 - 1].suite;
	sub2.ID = shuffle_hand[pick2 - 1].ID;

	// copy card from shuffle deck to hand
	hand[pick1 - 1].name = sub2.name;
	hand[pick1 - 1].suite = sub2.suite;
	hand[pick1 - 1].ID = sub2.ID;

	// copy card from hand to shuffle deck
	shuffle_hand[pick2 - 1].name = sub1.name;
	shuffle_hand[pick2 - 1].suite = sub1.suite;
	shuffle_hand[pick2 - 1].ID = sub1.ID;
}