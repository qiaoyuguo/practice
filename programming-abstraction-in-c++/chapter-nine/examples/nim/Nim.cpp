/*
 * =====================================================================================
 *
 * Filename:  Nim.cpp
 * This program simulates a simple variant of the game of Nim. in this 
 * version, the game starts with a pile of 13 coins on the table. Players 
 * then take turns removing 1, 2 or 3 coins from the pile. The player who
 * takes the last coin lose
 * =====================================================================================
 */

#include <iostream>
#include <string>
#include "error.h"
#include "simpio.h"
#include "strlib.h"

using namespace std;

/* Constants */
const int N_COINS = 13; /* Initial number of coins */
const int MAX_MOVE = 3; /* Number of coins a player may take */
const int NO_GOOD_MOVE = -1; /* Marker indicating there is no good moves */

/*
 * Type: Players
 * -----------------
 *  This enumerated type differenciates the human and computer players
 */
enum Player{ HUMAN, COMPUTER};

/*
 * Method: opponent
 * Usage: player other = opponent(player);
 * --------------------------------------
 *  Returns the opponent of the player. The opponent of the computer is the
 *  human player and vice versa.
 */
Player opponent(Player player) {
    return (player == HUMAN) ? COMPUTER : HUMAN;
}

/*
 * Constant: STARTING_PLAYER
 * --------------------------
 *  Indicates which player should start the game
 */
const Player STARTING_PLAYER = HUMAN;

/*
 * Class: SimpleNim
 * ----------------------
 *  The SimpleNim class implements the simple version of Nim.
 */

class SimpleNim{
    public:
        /* 
         * Method: play 
         * Usage: game.play();
         * --------------------------
         *  Plays one game of Nim with the human player.
         * */
        void play() {
            nCoins = N_COINS;
            whoseTurn = STARTING_PLAYER;
            while(nCoins > 1) {
                cout << "There are " << nCoins << " coins in the pile" << endl;
                if (whoseTurn == HUMAN){
                    nCoins -= getUserMove();
                }
                else{
                    int nTaken = getComputerMove();
                    cout << "I'll take " << nTaken << "." <<endl;
                    nCoins -= nTaken;
                }
                whoseTurn = opponent(whoseTurn);
            }
            announceResult();
        }

        /*
         * Method: printInstructions
         * Usage: game.printInstructions();
         * ------------------------------------
         *  This method explains the rules of the game to the user.
         */
        void printInstructions() {
            cout << "Welcome to the game of Nim!" << endl;
            cout << "In this game, we will start with a pile of" << endl;
            cout << N_COINS << " coins on the table. On each turn, you" << endl;
            cout << "and I will alternately take between 1 and" << endl;
            cout << MAX_MOVE << " coins from the table. The player who" << endl;
            cout << "takes the last coin lose." << endl << endl;
        }

    private:
        /*
         * Method: getComputerMove
         * Usage: int nTaken = getComputerMove();
         * --------------------------------------------
         *  Figures out what move is best for the computer player and 
         *  returns the number of coins taken. The method first calls 
         *  findGoodMove to see if a winning move exists. If none does, the
         *  program takes only one coin to give the human player more 
         *  chances to make a mistake.
         */
        int getComputerMove() {
            int nTaken = findGoodMove(nCoins);
            return (nTaken == NO_GOOD_MOVE) ? 1 : nTaken;
        }

        /*
         * Method: findGoodMove
         * Usage: int nTaken = findGoodMove(nCoins);
         * ----------------------------------------------
         *  This method looks for a winning move,given the specified number 
         *  of coins. If there is a winning move in that position, the 
         *  method returns the constant NO_GOOD_MOVE. This method depends 
         *  on the recursive insight that a good move is one that leaves 
         *  your opponent in a bad position and a bad position is one that
         *  offers no good moves.
         */
         int findGoodMove(int nCoins) {
             int limit = (nCoins < MAX_MOVE) ? nCoins : MAX_MOVE;
             for (int nTaken = 1; nTaken <= limit; nTaken++) {
                 if(isBadPosition(nCoins - nTaken)) return nTaken;
             }
             return NO_GOOD_MOVE;
         }

         /*
          * Method: isBadPosition
          * Usage: if (isBadPosition(nCoins)) . . .
          * ---------------------------------------
          * This method returns true if nCoins is a bad position.
          * A bad position is one in which there is no good move.
          * Being left with a single coin is clearly a bad position
          * and represents the simple case of the recursion.
          */
         bool isBadPosition(int nCoins) {
             if (nCoins == 1) return true;
             return findGoodMove(nCoins) == NO_GOOD_MOVE;
         }

         /*
          * Method: getUserMove
          * usage: int nTaken = getUserMove()
          * --------------------------------
          * Asks the user to enter a move and returns the number of coins 
          * taken. If the move is not legal, the user is asked to reenter a
          * valid move.
          */
         int getUserMove() {
             while(true) {
                 int nTaken = getInteger("How many would you likes? ");
                 int limit = (nCoins < MAX_MOVE) ? nCoins : MAX_MOVE;
                 if(nTaken > 0 && nTaken <= limit) return nTaken;
                 cout << "That's cheating! please choose a number";
                 cout << " between 1 and " << limit << "." << endl;
                 cout << "There are " << nCoins << " coins in the pile." << endl;
             }
         }
         /*
          * Method: announceResult
          * Usage: announceResult();
          * -------------------------
          *  This method announce the final result of the game.
          */

         void announceResult() {
             if (nCoins == 0) {
                 cout << "You took the last coin. You lose." << endl;
             } else {
                 cout << "There is only one coin left." << endl;
                 if( whoseTurn == HUMAN) {
                     cout << "I win." << endl;
                 } else {
                     cout << "I lose." << endl;
                 }
             }
         }

         /* Instance variables */
         int nCoins;
         Player whoseTurn;
};

int main() {
    SimpleNim game;
    game.printInstructions();
    game.play();

    return 0;
}
