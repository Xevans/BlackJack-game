# BlackJack-game

To Compile with g++:
    In termainal at location: g++ BlackJack.cpp -o BlackJack.exe.
    Executable created in same folder as a result.
    open it to run the game.



Running the game:
Game will first ask how many rounds the player wants to play.
    Type "1" followed by "Enter" key for 5 rounds (quicker game) or "2" for 10 rounds (longer game).

All players start with 100 money
    Enter an amount from 1 to 100.

As game events occur on screen, press enter (or any key) to proceed.

When prompted to hit or stand, you can either:
    Enter "1" to hit (draw a card from the main deck into your hand) 
    OR 
    Enter "2" to stand (do not draw any cards).

Game does not use jokers. (Planned feature to include them by choice).

Game displays a results screen at the end, showing how you did each round.



21 BlackJack Rules:
If you or another player (or dealer) result in a hand whose value is over 21, they will bust. resulting in them losing the round
When a round is lost, the money bet for the round is lost.

Goal is to have a hand whose value is greater than the dealer's but not over 21. It's a matter of luck and good judgement

Dealer will only hit until their hand value is 17, Dealer will stand.

Winners will recieved back, their bet x2

If the dealer's hand is 21, they automatically win and collect everyone's bet amount

See if you can reach the last round with more money than the other players!