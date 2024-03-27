// Writtent by Aamina Bokhari
//tik tac toe game AI
//CODSOFT
#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include<iomanip>
#include<string>

using namespace std;

char gameboard[3][3]; // i am creating a 3x3 matrix...

// i am checking if any row has a winning combo in this function....
bool rowcheck() {
    for (int i = 0; i < 3; i++) {
        if (gameboard[i][0] == gameboard[i][1] && gameboard[i][1] == gameboard[i][2] && gameboard[i][0] != ' ')
            return true;//this function checks if all three cells in that row are equal and not empty
    }
    return false;
}

//same checking for columns here...
bool columncheck() {
    for (int i = 0; i < 3; i++) {
        if (gameboard[0][i] == gameboard[1][i] && gameboard[1][i] == gameboard[2][i] && gameboard[0][i] != ' ')
            return true;
    }
    return false;
}

// same check for diagonal....
bool diagonalcheck() {
    if (gameboard[0][0] ==gameboard[1][1] && gameboard[1][1] == gameboard[2][2] && gameboard[0][0] != ' ')//dig 1
        return true;
    if (gameboard[0][2] == gameboard[1][1] && gameboard[1][1] == gameboard[2][0] && gameboard[0][2] != ' ')//dig 2
        return true;
    return false;
}

// this function checks if winner is found
bool checkwinner() {
    return rowcheck() || columncheck() || diagonalcheck();
}

// vheck if game is a draw
bool checkdraw() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (gameboard[i][j] == ' ')
                return false;
    return true;
}

// handling user turn here... user is X and Comp is O
void usermove() {
    cout << endl;
    cout << "User Turn.........>" << endl;
    int x, y;
    cout << "Enter your move (row and then column): ";
    cin >> x >> y;
    x--; y--;//because array start from 0
    if (gameboard[x][y] != ' ') {
        cout << "wrong move, try again." << endl;//IF the space is already occupied
        usermove();
    }
    else {
        gameboard[x][y] = 'X';
    }
}

// Minimax function algo here...

int minimax(char board[3][3], int depth, bool isMaximizing) {
    // If the game has a winner, return -1 for minimizing player and 1 for maximizing player
    if (checkwinner()) {
        return isMaximizing ? -1 : 1;
    }
    // If the game is a draw, return 0
    if (checkdraw()) {
        return 0;
    }

    // Maximizing player,here i am trying to find the maximum score possible
    if (isMaximizing) {
        int best= -9999993; // Initialize  this to a very low value...
        // Iteate...
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                // Check if acell is empty
                if (gameboard[i][j] == ' ') {
                    // Make the move
                    gameboard[i][j] = 'O';
                    // Call minimax recursively, increasing depth and switching to min player
                    int score = minimax(gameboard, depth + 1, false);
                    // Undo the move
                    gameboard[i][j] = ' ';
                    // i am replace the best score if current score is higher
                    best = max(score, best);
                }
            }
        }
      
        return best;
    }
    //  i am trying to find the minimum score possible
    else {
        int best = 9999; // Initialize to a very high value
        // Iterate......
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                // Cif cell is empty
                if (gameboard[i][j] == ' ') {
                    // do move
                    gameboard[i][j] = 'X';
                    // Call minimax recursively, increasing depth and switching to maximizing player
                    int score = minimax(gameboard, depth + 1, true);
                    // Undo the move
                    gameboard[i][j] = ' ';
                    // Update the best score if current score is lower
                    best = min(score, best);
                }
            }
        }
       
        return best;
    }
}


// do  computer's move using Minimax
void computermove() {
    cout << endl;
    cout << " Computer Turn.........> " << endl<<endl;
    int bestScore = -109999;
    int move[2] = { -1, -1 };
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (gameboard[i][j] == ' ') {
                gameboard[i][j] = 'O';
                int score = minimax(gameboard, 0, false);
                gameboard[i][j] = ' ';
                if (score > bestScore) {
                    bestScore = score;
                    move[0] = i;
                    move[1] = j;
                }
            }
        }
    }
    gameboard[move[0]][move[1]] = 'O';
}

// Function to display the tic-tac-toe board
void display() {
    cout << "  1 2 3 \n";
    for (int i = 0; i < 3; i++) {
        cout << i + 1 << " ";
        for (int j = 0; j < 3; j++) {
            cout << gameboard[i][j] << " ";
        }
        cout << "\n";
    }
}
//This is main for demo....
int main() {
    cout << "<<<<<<< TIC TAC TOE >>>>>>> " << endl<<endl;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            gameboard[i][j] = ' ';
    display();
    while (true) {
        usermove();
        display();
        if (checkwinner()) {
            cout << "Congrats!!!! You win!\n";
            break;
        }
        if (checkdraw()) {
            cout << "It's a draw.\n";
            break;
        }
        computermove();
        display();
        if (checkwinner()) {
            cout << "Oh no,Computer wins!\n";
            break;
        }
        if (checkdraw()) {
            cout << "It's a draw.\n";
            break;
        }
    }
    return 0;
}
