#include <iostream>
#include <sstream> 
#include <vector> 

const int boardSize = 3;

void printBoard(char fields[boardSize][boardSize]) {
    int steps = boardSize * 3 + 2;
    int rowCount = 0;
    int columnCount = 0;

    for (int i=1; i <= steps; i++) {
        std::cout << "          ";
        for (int j=1; j <= steps; j++) {
            if (!(i % 4)) {
                std::cout << "—";
                continue;
            }
            if (!(j % 4)) {
                std::cout << "|";
                continue;
            }
            if (!(i % 2) && !(j % 2)) {
                std::cout << fields[rowCount][columnCount++];
                continue;
            }
            if (columnCount > 2) {
                rowCount++;
            }
            std::cout << " ";
        }
        columnCount = 0;
        std::cout << "\r\n";
    }
}

std::vector<int> splitInput(std::string input, char delimiter) {
    if (size(input) > 3) {
        return {0};
    }
    if (!isdigit(input[0]) || !isdigit(input[2]) || input[1] != '/') {
        return {0};
    }

    std::stringstream ss(input); 
    std::string token; 
    std::vector<int> tokens; 
  
    while (getline(ss, token, delimiter)) {
        tokens.push_back(atoi(token.c_str())); 
    }
    return tokens; 
}

bool winByRow(char row[boardSize], char player) {
    return row[0] == player && row[1] == player && row[2] == player;
}

bool winByColumn(char fields[boardSize][boardSize], char player, int index) {
    return fields[0][index] == player && fields[1][index] == player && fields[2][index] == player;
}

bool winByDiagonal(char fields[boardSize][boardSize], char player) {
    return fields[0][0] == player && fields[1][1] == player && fields[2][2] == player;
}

bool winByReverseDiagonal(char fields[boardSize][boardSize], char player) {
    return fields[0][2] == player && fields[1][1] == player && fields[2][0] == player;
}


char checkIfOver(char fields[boardSize][boardSize]) {
    char players[2] = {'X', 'O'};
    for (char player: players) {
        for (int i=0; i < boardSize; i++) {
            if (winByRow(fields[i], player) ||
                winByColumn(fields, player, i) ||
                winByDiagonal(fields, player) ||
                winByReverseDiagonal(fields, player)
            ) {
                return player;
            }
        }
    } 
    return '\0';
}

int main() {
    char winner = '\0';
    bool playsX = true;
    std::cout << "Program running...\r\n" << std::endl;
    char fields[boardSize][boardSize];
    for (int i=0; i < boardSize; i++) {
        std::fill(fields[i], fields[i] + boardSize, ' ');
    }

    while (!winner) {
        printBoard(fields);
        char player = playsX ? 'X' : 'O';
        std::cout << "\nPlayer " << player << " : Enter field code (row/column):\r\n" << std::endl;
        std::string input;
        std::cin >> input;
        std::vector<int> splittedInput = splitInput(input, '/');
        int x = splittedInput[0] - 1, y = splittedInput[1] - 1;
        if (x > boardSize || y > boardSize) {
            std::cout << "\nInvalid coordinates entered" << std::endl;
            continue;
        }
        if (fields[x][y] != ' ') {
            std::cout << "\nThis field is already taken" << std::endl;
            continue;
        }
        fields[x][y] = player;
        playsX = !playsX;
        char winner = checkIfOver(fields);
        if (winner) {
            printBoard(fields);
            std::cout << "\nWinner is: Player " << winner << "!" << std::endl;
            break;
        }
    }
}