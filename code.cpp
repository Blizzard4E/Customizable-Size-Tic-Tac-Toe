//? Customizable Tic Tac Toe
//? You can customize the players' letter, grid's size, and the length to win
//! By Ear Choung Pheng / Blizzard4E

#include <iostream>
#include <string>

using namespace std;

//! Function to print a whole line of something from it's size
void PrintRow(string text, int size) {
    cout << "   ";
    for(int i=0;i<size;i++) {
        cout << text;
    }
    cout << "|" << endl;
}

//! Function to print out the entire grid
void PrintGrid(char grid[],int size) {
    system("CLS"); //? Clear out the text

    //? String variables for types of line
    string emptyLine = "|         "; 
    string line = "|---------";

    //! Print out the numbering for columns
    cout << "   ";
    for(int i=1;i<=size;i++) {
        if(i>99) {
            cout << "    " << i << "   ";
        }
        else if(i>9) {
            cout << "     " << i << "   ";
        }
        else {
            cout << "     " << i << "    ";
        }
    }
    cout << endl;

    //! Print out a line for the top of the grid
    PrintRow(line, size);
    
    int index = 0; //? keeping track of array index instead of using 'row-1'
    //! Loop for every rows
    for(int row=1; row<=size; row++) {

        PrintRow(emptyLine, size); //? Empty lines so grid looks better

        //! Print out numbering for rows
        if(row>99) {
            cout << row;
        }
        else if(row>9) {
            cout << row << " ";
        }
        else {
            cout << row << "  ";
        }

        //! Print out the columns line with infomation attached
        for(int col=1;col<=size;col++) {
            cout << "|    " << grid[index]  << "    ";
            index++;
        }
        cout << "|" << endl;

        PrintRow(emptyLine, size); //? Empty lines so grid looks better
        PrintRow(line, size); //? Line at end the row 
    }
}

int main() {
    int size = 0;
    int winSize = 0;

    //! Getting info from players
    while(true) {

        //? Get Input
        cout << "Please enter your grid size: ";
        cin >> size;

        //? Validation
        if(!cin) {
            cout << "Grid size must be a positive integer and not a zero.\n";
            cin.clear();
            cin.ignore(100, '\n');
            continue;
        }
        else if(size < 1) {
            cout << "Grid size must be a positive integer and not a zero.\n";
            cin.clear();
            cin.ignore(100, '\n');
            continue;
        }

        //? Get Input
        cout << "Please enter your winning length: ";
        cin >> winSize;

        //? Validation
        if(!cin) {
            cout << "Winning length must be a positive integer and not a zero.\n";
            cin.clear();
            cin.ignore(100, '\n');
            continue;
        }
        else if(winSize > size) {
            cout << "Winning length must not be longer than grid size.\n";
            cin.clear();
            cin.ignore(100, '\n');
            continue;
        }
        else { 
            break;
        }
    }

    char *grid = new char[size*size]; //? Create a grid array from the size given

    //! Filling the array with empty space
    for(int i=0; i<size*size; i++) {
        grid[i] = ' ';
    }

    bool playing = true;
    bool isPlayer1 = true;
    char player1Letter;
    char player2Letter;

    //! Get players' letters
    while(true) {
        cout << "Choose the letter for PLAYER 1: ";
        cin >> player1Letter;
        cin.ignore(100, '\n');
        cout << "Choose the letter for PLAYER 2: ";
        cin >> player2Letter;

        //? Validation
        if(player1Letter == player2Letter) {
            cout << "Both players can not have the same letter.\n";
        }
        else {
            break;
        }
    }
    
    //! Start the game
    while(playing) {
        PrintGrid(grid, size); //! Print out a new grid

        int rowPos;
        int colPos;
        char letter;

        //! Asking player's turn and set the correct letter
        if(isPlayer1) {
            cout << "Place your '" << player1Letter << "' at";
            letter = player1Letter;
        }
        else {
            cout << "Place your '" << player2Letter << "' at";
            letter = player2Letter;
        }

        //! Get row and column info from players
        while(true) {
            cout << "\nRow: ";
            cin >> rowPos;

            //? Validate
            if(!cin) { 
                cout << "Row must be a positive integer and not a zero.";
                cin.clear();
                cin.ignore(100, '\n');
                continue;
            }
            else if(rowPos < 1) {
                cout << "Row must be a positive integer and not a zero.";
                cin.clear();
                cin.ignore(100, '\n');
                continue;
            }
            else if(rowPos > size) {
                cout << "Row cannot exceed the grid size.";
                cin.clear();
                cin.ignore(100, '\n');
                continue;
            }
            else {
                break;
            }
        }
        while(true) {
            cout << "Column: ";
            cin >> colPos;

            //? Validate
            if(!cin) {
                cout << "Column must be a positive integer and not a zero.\n";
                cin.clear();
                cin.ignore(100, '\n');
                continue;
            }
            else if(colPos < 1) {
                cout << "Column must be a positive integer and not a zero.\n";
                cin.clear();
                cin.ignore(100, '\n');
                continue;
            }
            else if(colPos > size) {
                cout << "Column cannot exceed the grid size.\n";
                cin.clear();
                cin.ignore(100, '\n');
                continue;
            }
            else {
                break;
            }
        }
        
        //! Check if given position is already occupied
        if(grid[size*(rowPos-1) + colPos - 1] == player1Letter || grid[size*(rowPos-1) + colPos - 1] == player2Letter) {
            continue;
        }

        //! Putting the player's letter in the given postionn
        grid[ size*(rowPos-1) + colPos - 1] = letter;

        //! Cross Right Checking
        for(int cross=0;cross<size*size; cross++) {
            int countX = 0;
            int countO = 0;

            int rightCrossIndex = cross;
            for(int i=0;i<size;i++) {
                if(rightCrossIndex >= size*size) break;

                if(grid[rightCrossIndex] == ' ') {
                    countX = 0;
                    countO = 0;
                }
                else if(grid[rightCrossIndex] == player1Letter) {
                    countX++;
                    countO = 0;
                }
                else if(grid[rightCrossIndex] == player2Letter) {
                    countO++;
                    countX = 0;
                }
                rightCrossIndex += size + 1;
                if(countX == winSize) {
                    PrintGrid(grid, size); //! Print out a new grid
                    playing = false;
                    break;
                }
                else if(countO == winSize) {
                    PrintGrid(grid, size); //! Print out a new grid
                    playing = false;
                    break;
                }
            }
        }

        //! Cross Left Checking
        for(int cross=0;cross<size*size; cross++) {
            int countX = 0;
            int countO = 0;

            int rightCrossIndex = cross;
            for(int i=0;i<size;i++) {
                if(rightCrossIndex >= size*size || rightCrossIndex < 0) break;

                if(grid[rightCrossIndex] == ' ') {
                    countX = 0;
                    countO = 0;
                }
                else if(grid[rightCrossIndex] == player1Letter) {
                    countX++;
                    countO = 0;
                }
                else if(grid[rightCrossIndex] == player2Letter) {
                    countO++;
                    countX = 0;
                }
                rightCrossIndex += size - 1;
                if(countX == winSize) {
                    PrintGrid(grid, size); //! Print out a new grid
                    playing = false;
                    break;
                }
                else if(countO == winSize) {
                    PrintGrid(grid, size); //! Print out a new grid
                    playing = false;
                    break;
                }
            }
        }

        //! Horizontal Checking
        int horizontalIndex = 0;
        for(int row=1; row<=size; row++) {
            int countX = 0;
            int countO = 0;
            for(int col=1;col<=size;col++) {
                if(grid[horizontalIndex] == ' ') {
                    countX = 0;
                    countO = 0;
                }
                else if(grid[horizontalIndex] == player1Letter) {
                    countX++;
                    countO = 0;
                }
                else if(grid[horizontalIndex] == player2Letter) {
                    countO++;
                    countX = 0;
                }
                horizontalIndex++;
                if(countX == winSize) {
                    PrintGrid(grid, size); //! Print out a new grid
                    playing = false;
                    break;
                }
                else if(countO == winSize) {
                    PrintGrid(grid, size); //! Print out a new grid
                    playing = false;
                    break;
                }
            }
        }

        //! Vertical Checking
        for(int col=0; col<size; col++) {
            int countX = 0;
            int countO = 0;

            int verticalIndex = col;
            for(int row=1;row<=size;row++) {
                if(grid[verticalIndex] == ' ') {
                    countX = 0;
                    countO = 0;
                }
                else if(grid[verticalIndex] == player1Letter) {
                    countX++;
                    countO = 0;
                }
                else if(grid[verticalIndex] == player2Letter) {
                    countO++;
                    countX = 0;
                }
                verticalIndex += size;
                if(countX == winSize) {
                    PrintGrid(grid, size); //! Print out a new grid
                    playing = false;
                    break;
                }
                else if(countO == winSize) {
                    PrintGrid(grid, size); //! Print out a new grid
                    playing = false;
                    break;
                }
            }
        }
        if(playing) {
            isPlayer1 = !isPlayer1;
        }
        else {
            cout << "   Player '" << letter << "' has won.\n";
        }
    }
    
    return 0;
}