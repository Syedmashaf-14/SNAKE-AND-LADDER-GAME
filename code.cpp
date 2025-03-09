#include <iostream>
#include <cassert>   // TO HANDLE ERROR HANDLING
#include <iomanip>   // TO MAKE THE TABLE AND CODE STYLISH.
#include <fstream>  // USED IN FILE HANDLING/
#include <ctime>     // TO CREATE RANDOM DICE VALUES.
#include <cstdlib>  
#include <windows.h>  // FOR ADDING COLOUR OF CONSOLE   


#define green   "\033[32m"   // FOR HAVING GREEN COLOR
#define red     "\033[31m"    // FOR HAVING RED COLOR
#define reset   "\033[0m"     

using namespace std;

const int board_size = 10;  //  the board size to 10x10
const int num_snakes = 3;
const int num_ladders = 3;
const int num_players = 4;

int snakestart[num_snakes] = { 16, 47, 49 };  // STARTING POSITION OF SNAKE START
int snakeend[num_snakes] = { 6, 26, 11 };     // AFTER DECREMENT VALUES
int ladderstart[num_ladders] = { 3, 20, 45 };
int ladderend[num_ladders] = { 22, 41, 68 };

void initializeboard(int board[][board_size])  // BOARD INIIALIZATION
{
    int counter = board_size * board_size;
    for (int i = 0; i < board_size; i++)
    {
        if (i % 2 != 0)
        {
            for (int j = board_size - 1; j >= 0; j--)
            {
                board[i][j] = counter--;
            }
        }
        else
        {
            for (int j = 0; j < board_size; j++)
            {
                board[i][j] = counter--;
            }
        }
    }
    for (int i = 0; i < num_snakes; i++)
    {
        int rowstart = board_size - 1 - (snakestart[i] - 1) / board_size;
        int colstart = (snakestart[i] - 1) % board_size;
        int rowend = board_size - 1 - (snakeend[i] - 1) / board_size;
        int colend = (snakeend[i] - 1) % board_size;

    }

    for (int i = 0; i < num_ladders; i++)
    {
        int rowstart = board_size - 1 - (ladderstart[i] - 1) / board_size;
        int colstart = (ladderstart[i] - 1) % board_size;
        int rowend = board_size - 1 - (ladderend[i] - 1) / board_size; //row_end
        int colend = (ladderend[i] - 1) % board_size; //col end

    }
}
void game_menu(); // Function definition.


void displayboard(const int board[][board_size], const int playerpositions[])
{
    for (int i = 0; i < board_size; i++)
    {
        for (int j = 0; j < board_size; j++)
        {
            bool playerhere = false;
            for (int k = 0; k < num_players; ++k)
            {
                int row = board_size - 1 - (playerpositions[k] - 1) / board_size; // calculate row position
                int col = (playerpositions[k] - 1) % board_size; // calculate column position
                if (row == i && col == j)
                {
                    cout << "| p" << (k + 1) << " ";  // HERE P IS THE PLAYER AND (k+1) REPRESENTS THE PLAYER NUMBER
                    playerhere = true;
                    break;
                }
            }
            if (!playerhere)
            {
                if (board[i][j] < 10)
                {
                    cout << "| 0" << board[i][j] << " ";
                }
                else {
                    cout << "| " << board[i][j] << " ";
                }
            }
        }
        cout << "|" << endl;
    }
}


void credit()
{
    system("cls"); // clear the screen.
    cout << "Created by:  SYED MASHAF  23F-0529   " << endl;
    Sleep(2000);
    system("cls");
}


void instruction()  // insturuction pop up menue.

{
    system("cls");
    cout << setw(30) << setfill('.') << "instruction" << setw(30) << setfill('.') << ".\n";
    cout << "1. Four Players will play the game and the player who reaches 100 first will win." << endl;
    cout << "2. Every Player will roll the dice once at a time." << endl;
    cout << "3. If a Player finds the letter ladder, they will get incremented to the point where the ladder ended." << endl;
    cout << "4. If a Player finds the letter snake, they will get decremented to the point where the snake tail ended." << endl;
    cout << "5. If a Player get 6 than the game will start else get sixer to start the game" << endl;
    cout << "6. If a Player get increment than he got message in green colour" << endl;
    cout << "7. If a Player get decrement than he got message in red colour" << endl;
    cout << "8. There will be 3 winners and one looser." << endl;
    cout << "Good Luck!" << endl;
    Sleep(3000);
    char Your_perspective;
    cout << "Press 1 FOR MENUE" << endl;
    cout << "Press 0 TO EXIT" << endl;
    cin >> Your_perspective;
    assert(Your_perspective != 1 || Your_perspective == 0);
    switch (Your_perspective)
    {
    case'1':
        game_menu();
        break;
    case'2':
        assert(Your_perspective != 0);
        break;
    default:
        cout << "invalid. " << endl;
        break;
    }
    system("cls");

}

void game_menu()  // GAME MENUE
{
    int* choice; // INTEGER TYPE POINTER
    int ch = 0;

    cout << setw(30) << setfill('.') << " WELCOME TO THE GAME OF MIND! " << setw(30) << setfill('.') << ".\n";
    cout << setw(10) << setfill(' ') << "Press 1  START GAME" << setw(10) << setfill(' ') << '\n';
    cout << setw(10) << setfill(' ') << "Press 2  INSTRUCTION" << setw(10) << setfill(' ') << '\n';
    cout << setw(10) << setfill(' ') << "Press 0  EXIT" << setw(10) << setfill(' ') << '\n';
   

    cout << "PRESS BUTTON" << endl;
    cin >> ch;
    assert(ch == 1 || ch == 2 || ch == 0);  // only work for these number rather the number be entered than i will not work and show an error on the console accordingly.


    choice = &ch;  // GIVING REFERENCE FOR INVALID ENTRY BY ANY USER .

    

    if (*choice == 1)
    {
        cout << "LOOKING FORWARD FOR OTHER PLAYER TO START..." << endl;
        PlaySound(TEXT("we"), NULL, SND_SYNC); // Adding the sound.
      
    }
    
    else if (*choice == 2)
    {
        instruction();
    }

    else if (*choice == 0)
    {
        cout << setw(15) << setfill('.') << "Exiting..." << setw(15) << setfill('.') << ".\n";
        exit(0);
    }
}


// File Handling/
void writeMovesToFile(int playerNumber, int moves[])
{
    ofstream write("moves.txt", ios::app);
    if (!write.is_open()) {
        cerr << "Error! Unable to open file for writing." << endl;
        return;
    }

    write << "Player: " << playerNumber << " No of moves: " << moves[playerNumber - 1] << endl;
    write.close();
}

int rolldice()  // for generating random values
{
    return rand() % 6 + 1;
}

void game()
{
    int board[board_size][board_size];  // 2d array initialization
    initializeboard(board);
    int playerpositions[num_players] = { 1, 1, 1, 1 };
    int moves[num_players] = { 0 };
    int players = 1;
    int sixercount = 1;
    bool winner_found = false;
    bool player_selection = false;
    int user_choice = 0;
    int playerwon = 0;
    int win = 0;
    int winnerscount = 0;
    int loserscount = 0;
    int winners[num_players] = { 0 };
    int loser = -1;
    bool playeractive[num_players] = { true, true, true, true }; // initial position of every player and he can get increment and decrement depend upon values.

    srand(time(0));
    while (win < 3  )  // Continue the game until three players win
    {
        for (int i = 0; i < num_players; ++i)
        {
            if (!playeractive[i])  // skip player if inactive.
                continue;

            displayboard(board, playerpositions); // calling the function

            cout << "Now its the turn of player:  " << i + 1 << endl;
            int diceroll = rolldice();
            cout << "You rolled :  " << diceroll << "." << endl;

            
            bool equal_state = false;  // used here to check that whether two player are not at their same pos.
            for (int j = 0; j < num_players; ++j)
            {
                if (i != j && playerpositions[i] + diceroll == playerpositions[j] && playerpositions[i+1]+diceroll==playerpositions[j+1])
                {
                    cout << "Player " << (j + 1) << " is already at position " << playerpositions[j] << "." << endl;
                    cout << "Player " << (i + 1) << " moves back to the initial position." << endl;
                    playerpositions[i]-= rolldice() ;
                    equal_state = true;
                    break;
                }
                
            }

            if (equal_state)
                continue;

            if (playerpositions[i] == 1 && diceroll != 6) // implemnenting the condition to check whether the player 6 to start the game or not
            {
                cout << "You need to roll down a sixer to start the game." << endl;
                continue;
            }
            if (playerpositions[i] + diceroll > board_size * board_size) // Implementing condition that player not cross the board if value are higher
            {
                cout << "You need " << (board_size * board_size - playerpositions[i]) << " to reach the end." << endl;
                continue;
            }



            playerpositions[i] += diceroll;

            cout << "The position of player " << i + 1 << " is at " << playerpositions[i] << endl;
            moves[i]++; // incrementing the no of moves of every player

            int consecutivessixescount = 0;
            if (diceroll == 6) // implemnting the handling of sixer .
            {
                consecutivessixescount = 1; // check whether the players not get 3 sixes consecutively.

                cout << "You got sixer!.You are given another turn." << endl;
                int another_turn = rolldice();
                cout << "You got : " << another_turn  << endl;
                playerpositions[i] += another_turn;
                cout << "The current position after turn is:   " << playerpositions[i] << endl;
                consecutivessixescount++;
                if (playerpositions[i] + diceroll > board_size * board_size)
                {
                    playerpositions[i] -= rolldice();
                    cout << "The size of board cannot be exceeded. " << endl;
                    cout << "The position of Player : " << i + 1 << " due to higher roll than the board size is still at: " << playerpositions[i] << endl;
                }


                if (another_turn == 6)
                {
                    cout << "You  got six another time wow! " << endl;
                    cout << "You are given one more turn.But if you get six this time than your position will be void." << endl;
                    another_turn = rolldice();
                    cout << "you got " << another_turn << endl;

                    

                    if (another_turn == 6)
                    {
                        cout << "Oh! You got 3 sixes consecutively." << endl;
                        playerpositions[i] -= 18; // IT WILL MAKE THE POSITION OF THE PLAYER AS VOID
                        cout << "Your player still remain at position " << playerpositions[i] << endl;
                    }
                    

                    else
                    {
                        playerpositions[i] += another_turn;
                        cout << "You current position after another turn is:  " << playerpositions[i] << endl;
                    }

                }

            }
            else

                consecutivessixescount = 0;

            for (int m = 0; m < num_snakes; m++) // implemnting the condtion for snake bite.
            {
                if (playerpositions[i] == snakestart[m])
                {
                    playerpositions[i] = snakeend[m];
                    cout << red<<"Oh no! you landed on a snake. You got decremented to position : " << snakeend[m] << "." << reset << endl;
                    PlaySound(TEXT("looser"), NULL, SND_SYNC);

                }
            }
            for (int k = 0; k < num_ladders; k++) // implemneting the condition for ladders
            {
                if (playerpositions[i] == ladderstart[k])
                {
                    playerpositions[i] = ladderend[k];
                    cout  << "WOW! you landed on a ladder. you got incremented to position : " << ladderend[k] << "." << endl;
                   
                    PlaySound(TEXT("wow"), NULL, SND_SYNC);
                }
            }

           

            if (playerpositions[i] >= board_size * board_size) // finally implemnting the sceneriio after player won the game
            {

                win++;
                cout << "Player " << (i + 1) << " wins!" << endl;
                cout << "Congratulation player : " << i + 1 << endl;

                PlaySound(TEXT("BEEP"), NULL, SND_SYNC); // sound track of the winners.
                cout << "Moves of Player:  " << (i + 1) << ": " << moves[i] << endl;
                playerpositions[i] = board_size * board_size;
                // Set playeractive to false to indicate that this player has won
                playeractive[i] = false;
              
                 

                if (win < 2)
                {
                    int giftplayer;
                    cout << "You can gift moves to any active player of your choice. Enter the player number (1-4): ";
                    cin >> giftplayer;

                    while (giftplayer < 1 || giftplayer > 4 || !playeractive[giftplayer - 1]) // condition for gift 
                    {
                        cout << "Invalid player number! Enter a valid active player number (1-4): ";
                        cin >> giftplayer;
                    }

                    moves[giftplayer - 1] += 6;
                    cout << "Player " << (i + 1) << " gifted 6 moves to player ." << giftplayer << "." << endl;
                    writeMovesToFile(i + 1, moves);

                }
            }

        }
    }
}

int main()
{
    int playerpositions[num_players] = { 0 };
    int currentplayer = 0;
    game_menu();
    credit();
    game();
    system("pause");
    return 0;
