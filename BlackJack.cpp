// Author: Xavier Evans

#include <iostream>
#include "Player.h"
using namespace std;


void printDivide() {
    for (int i = 0; i < 30; i++) {
        cout << "*";
    }
    cout << endl << endl;
}

int main() {

    int choice;
    int rounds;
    int game_loop = 1;

    int dealer_card_value = 0;
    int user_card_value = 0;
    int player_two_card_value = 0;
    int player_three_card_value = 0;
    int player_four_card_value = 0;

    int user_bet = 0;
    int player_two_bet = 0;
    int player_three_bet = 0;
    int player_four_bet = 0;

    bool hit_status;

    
    cout << "Welcome to the best card game... BlckJack!" << endl;
    cout << "2022. Created by Xavier Evans." << endl << endl;

    cout << "Enter '1' to play 5 rounds. Enter '2' for 10 rounds." << endl;

    while (true) {
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore();
            cout << "Please enter numbers only: ";
        }
        else {
            if (choice < 1 || choice > 2) {
                cout << "Invalid choice. Try again: ";
            }
            else {
                (choice == 1) ? rounds = 5 : rounds = 10;
                break;
            }
        }
    }

    // Player init.
    Player main_deck;
    Player dealer;
    Player you;
    Player player_two;
    Player player_three;
    Player player_four;

    main_deck.initDeck(false);
    main_deck.shuffle();

    //GAME LOOP BEGIN
    while (game_loop != rounds + 1) {

        printDivide();

        // betting stage
        cout << "You have $" << you.checkMoney() << ".\nPlease type an amount to bet. (Min: 1 | Max: 100): ";
        
        while (true) {
            cin >> user_bet;

            if (cin.fail()) { // not a number
                cin.clear();
                cin.ignore();
                cout << "Please enter numbers only: ";
            }
            else { // invalid number
                if (user_bet < 1) {
                    cout << "Your bet was 0 or lower, please enter a valid bet (between 0 and 100): ";
                }
                else if (user_bet > 100) {
                    cout << "Your bet was greater than $100: ";
                }
                else if (user_bet > 0 && user_bet <= 100) {
                    break;
                }
                else {
                    cout << "Invalid entry; retype entry: ";
                }
            }
        }

        cout << "You bet $" << user_bet << endl << endl;
        you.subtractMoney(user_bet);


        srand(time(NULL));
        // player bets
        cout << "Player two has: $" << player_two.checkMoney() << endl;
        player_two_bet = player_two.makeBet();
        player_two.subtractMoney(player_two_bet);
        cout << "Player two bets: $" << player_two_bet << endl << endl;

        cout << "Player three has: $" << player_three.checkMoney() << endl;
        player_three_bet = player_three.makeBet();
        player_three.subtractMoney(player_three_bet);
        cout << "Player three bets: $" << player_three_bet << endl << endl;


        cout << "Player four has: $" << player_four.checkMoney() << endl;
        player_four_bet = player_four.makeBet();
        player_four.subtractMoney(player_four_bet);
        cout << "Player four bets: $" << player_four_bet << endl << endl;

        system("pause");
        printDivide();

        //main_deck deals cards; two passes
        for (int i = 0; i < 2; i++) {
            player_four.addToHand(main_deck.hand.back().name, main_deck.hand.back().suite, main_deck);
            player_three.addToHand(main_deck.hand.back().name, main_deck.hand.back().suite, main_deck);
            player_two.addToHand(main_deck.hand.back().name, main_deck.hand.back().suite, main_deck);
            you.addToHand(main_deck.hand.back().name, main_deck.hand.back().suite, main_deck);
            dealer.addToHand(main_deck.hand.back().name, main_deck.hand.back().suite, main_deck);
        }

        cout << "Dealer's Hand." << endl;
        cout << "Card 1:" << dealer.hand[0].name << " of " << dealer.hand[0].suite << "S" << endl;
        cout << "Card 2: Hidden" << endl;
        cout << "Value of dealer's hand excluding hidden card: " << dealer.getCardValue(1) << endl << endl;

        

        system("pause");
        printDivide();
        // Players begin determining whether they want to hit or stand.

        // player 4
        cout << "\nPlayer 4's hand" << endl;
        player_four.showHand();
        cout << "Value of player 4's hand: " << player_four.getHandValue() << endl;
        printDivide();

        while (true) {

            if (player_four.getHandValue() == 21) {
                cout << "Player 4 got a BlackJack!" << endl;
                cout << "Player 4's hand" << endl;
                player_four.showHand();
                cout << "Value of player 4's hand: " << player_four.getHandValue() << endl;
                break;
            }

            hit_status = player_four.determineHit();
            if (hit_status == true) {
                cout << "Player 4 chooses to hit!" << endl;

                player_four.addToHand(main_deck.hand.back().name, main_deck.hand.back().suite, main_deck);
                cout << "Player 4 recieved a " << player_four.hand.back().name << " of " << player_four.hand.back().suite << "S" << endl;

                if (player_four.getHandValue() > 21) {
                    printDivide();
                    cout << "Player 4's hand" << endl;
                    player_four.showHand();
                    cout << "Value of player 4's hand: " << player_four.getHandValue() << endl;

                    cout << "Player 4 busts!" << endl;
                    player_four.bust_status = true;
                    break;
                }
 
            }
            else {
                printDivide();
                cout << "Player 4 chooses to stand" << endl;
                cout << "Player 4's hand" << endl;
                player_four.showHand();
                cout << "Value of player 4's hand: " << player_four.getHandValue() << endl;
                break;
            }
        }

        system("pause");
        printDivide();
        //player 3
        cout << "\nPlayer 3's hand" << endl;
        player_three.showHand();
        cout << "Value of player 3's hand: " << player_three.getHandValue() << endl;
        printDivide();

        while (true) {

            if (player_three.getHandValue() == 21) {
                cout << "Player 3 got a BlackJack!" << endl;
                cout << "Player 3's hand" << endl;
                player_three.showHand();
                cout << "Value of player 3's hand: " << player_three.getHandValue() << endl;
                break;
            }

            hit_status = player_three.determineHit();

            if (hit_status == true) {
                cout << "Player 3 chooses to hit!" << endl;

                player_three.addToHand(main_deck.hand.back().name, main_deck.hand.back().suite, main_deck);
                cout << "Player 3 recieved a " << player_three.hand.back().name << " of " << player_three.hand.back().suite << "S" << endl;

                if (player_three.getHandValue() > 21) {
                    printDivide();
                    cout << "Player 3's hand" << endl;
                    player_three.showHand();
                    cout << "Value of player 3's hand: " << player_three.getHandValue() << endl;

                    cout << "Player 3 busts!" << endl;
                    player_three.bust_status = true;
                    break;
                }
  

            }
            else {
                printDivide();
                cout << "Player 3 chooses to stand" << endl;
                cout << "Player 3's hand" << endl;
                player_three.showHand();
                cout << "Value of player 3's hand: " << player_three.getHandValue() << endl;
                break;
            }
        }
        system("pause");
        printDivide();

        //player 2
        cout << "\nPlayer 2's hand" << endl;
        player_two.showHand();
        cout << "Value of player 2's hand: " << player_two.getHandValue() << endl;
        printDivide();

        while (true) {

            if (player_two.getHandValue() == 21) {
                cout << "Player 2 got a BlackJack!" << endl;
                cout << "Player 2's hand" << endl;
                player_two.showHand();
                cout << "Value of Player 2's hand: " << player_two.getHandValue() << endl;
                break;
            }

            hit_status = player_two.determineHit();
            if (hit_status == true) {
                cout << "Player 2 chooses to hit!" << endl;

                player_two.addToHand(main_deck.hand.back().name, main_deck.hand.back().suite, main_deck);
                cout << "Player 2 recieved a " << player_two.hand.back().name << " of " << player_two.hand.back().suite << "S" << endl;

                if (player_two.getHandValue() > 21) {
                    printDivide();
                    cout << "Player 2's hand" << endl;
                    player_two.showHand();
                    cout << "Value of player 2's hand: " << player_two.getHandValue() << endl;

                    cout << "Player 2 busts!" << endl;
                    player_two.bust_status = true;
                    break;
                }
 
            }
            else {
                printDivide();
                cout << "Player 2 chooses to stand" << endl;
                cout << "Player 2's hand" << endl;
                player_two.showHand();
                cout << "Value of player 2's hand: " << player_two.getHandValue() << endl;
                break;
            }
        }

        system("pause");
        printDivide();
        // show other players and dealer card values on screen again

        //user turn
        cout << "\nIt's your turn!" << endl;
        cout << "Your hand" << endl;
        you.showHand();
        cout << "Value of your hand: " << you.getHandValue() << endl;
        printDivide();

        // player turn
        while (true) {

            if (you.getHandValue() == 21) {
                cout << "You have a BlackJack!" << endl;
                cout << "Your hand" << endl;
                you.showHand();
                cout << "Value of your hand: " << you.getHandValue() << endl;
                break;
            }

            cout << "Hit (draw a card) or Stand (keep your hand as is)?" << endl;
            cout << "Enter 1 to hit. Enter 2 to stand." << endl;

            while (true) {
                cin >> choice;

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore();
                    cout << "Please enter numbers only: ";
                }
                else {
                    if (choice < 1 || choice > 2) {
                        cout << "Invalid choice. Try again: ";
                    }
                    else {
                        break;
                    }
                }
            }

            if (choice == 1) {
                cout << "You choose to hit!" << endl;
                you.addToHand(main_deck.hand.back().name, main_deck.hand.back().suite, main_deck);
                cout << "You recieved a " << you.hand.back().name << " of " << you.hand.back().suite << "S" << endl;
                cout << "Value of your hand: " << you.getHandValue() << endl;

                if (you.getHandValue() > 21) {
                    printDivide();
                    cout << "Your hand" << endl;
                    you.showHand();
                    cout << "Value of your hand: " << you.getHandValue() << endl;

                    cout << "You busted!" << endl;
                    you.bust_status = true;
                    break;
                }

                user_card_value = you.getHandValue();
            }
            else {
                printDivide();
                cout << "You choose to stand." << endl;
                cout << "Your hand" << endl;
                you.showHand();
                cout << "Value of your hand: " << you.getHandValue() << endl;
                break;
            }
        }

        system("pause");
        printDivide();

        // dealer turn
        cout << "\n\nDealer reveals their second card" << endl;
        // reveal second card. Enter loop if under 17
        dealer_card_value += dealer.getHandValue();

        dealer.showHand();

        cout << "Value of Dealer's hand: " << dealer.getHandValue() << endl;
        printDivide();
        if (dealer.getHandValue() < 17) {
            while (true) {
                hit_status = dealer.determineHit();
                if (hit_status == true) {

                    if (dealer.getHandValue() == 21) {
                        cout << "Dealer got a BlackJack!" << endl;
                        cout << "Dealer's hand" << endl;
                        dealer.showHand();
                        cout << "Value of Dealer's hand: " << dealer.getHandValue() << endl;
                        break;
                    }

                    cout << "Dealer chooses to hit!" << endl;

                    dealer.addToHand(main_deck.hand.back().name, main_deck.hand.back().suite, main_deck);
                    cout << "Dealer recieved a " << dealer.hand.back().name << " of " << dealer.hand.back().suite << "S" << endl;

                    if (dealer.getHandValue() > 21) {
                        printDivide();
                        cout << "Dealer hand" << endl;
                        dealer.showHand();
                        cout << "Value of Dealer's hand: " << dealer.getHandValue() << endl;

                        cout << "Dealer busts!" << endl;
                        dealer.bust_status = true;
                        break;
                    }
                }
                else {
                    printDivide();
                    cout << "Dealer chooses to stand." << endl;
                    cout << "Dealer's hand" << endl;
                    you.showHand();
                    cout << "Value of Dealer's hand: " << dealer.getHandValue() << endl;
                    break;
                }
            }
        }
        else {
            cout << "Dealer chooses to stand" << endl;
        }

        // determine results of round

        system("pause");
        printDivide();
        // call determineResults using dealer instance. take value returned from function and determine payout in case switch

        dealer.determineResults(you, player_two, player_three, player_four, user_bet, player_two_bet, player_three_bet, player_four_bet);
        /*
        if (you.checkMoney() <= 0) {
            cout << "You ran out of money... Game Over." << endl;

            // get final record
            you.addSummary(rounds);
            break;
        }*/

        // record round summary
        you.addSummary(game_loop);



        // reinitialize bust statuses
        you.bust_status = false;
        player_two.bust_status = false;
        player_three.bust_status = false;
        player_three.bust_status = false; 

        // return cards to main deck
        main_deck.CallBackAllCards(dealer, you, player_two, player_three, player_four);

        game_loop++;
    }

    // end message
    // show summary

    cout << "Results:" << endl;
    you.getSummary();

    system("pause");
    printDivide();

    cout << "\n\nThank you for playing!!" << endl;
    // option to play again To be added. need another loop. If sentinel no, game ends.

    return 0;
}
// Author: Xavier Evans