#include <iostream>
#include <limits>

class BadukBoard
{
private:
    char board[19][19];
    int blackStonesX[361], blackStonesY[361];
    int whiteStonesX[361], whiteStonesY[361];
    int blackCount, whiteCount;
    char turn;

public:
    BadukBoard() : turn('X'), blackCount(0), whiteCount(0) {
        for (int i = 0; i < 19; i++) {
            for (int j = 0; j < 19; j++) {
                board[j][i] = '.';
            }
        }
    }

    void printBoard() const {
        for (int i = 0; i < 19; i++) {
            for (int j = 0; j < 19; j++) {
                std::cout << board[j][i] << " ";
            }
            std::cout << '\n';
        }
        std::cout << "검은돌 개수: " << blackCount << ", 흰돌의 개수: " << whiteCount << '\n';
    }

    bool placeStone(int y, int x) { // Notice x and y are swapped here
        if (board[x][y] != '.') return false;

        board[x][y] = turn;
        if (turn == 'X') {
            blackStonesX[blackCount] = x;
            blackStonesY[blackCount] = y;
            blackCount++;
            turn = 'O';
        }
        else {
            whiteStonesX[whiteCount] = x;
            whiteStonesY[whiteCount] = y;
            whiteCount++;
            turn = 'X';
        }
        return true;
    }

    void countStones() {
        int rowBlack[19] = { 0 }, rowWhite[19] = { 0 };
        int colBlack[19] = { 0 }, colWhite[19] = { 0 };
        int diag1Black = 0, diag1White = 0; // Main diagonal
        int diag2Black = 0, diag2White = 0; // Anti diagonal

        for (int x = 0; x < 19; x++) {
            for (int y = 0; y < 19; y++) {
                char stone = board[x][y];
                if (stone == 'X') {
                    colBlack[x]++;
                    rowBlack[y]++;
                    if (x == y) diag1Black++;
                    if (x == 18 - y) diag2Black++;
                }
                else if (stone == 'O') {
                    colWhite[x]++;
                    rowWhite[y]++;
                    if (x == y) diag1White++;
                    if (x == 18 - y) diag2White++;
                }
            }
        }

        // Output the results
        std::cout << "Rows and Columns Stone Count:\n";
        for (int i = 0; i < 19; i++) {
            std::cout << "Row " << i << ": Black " << rowBlack[i] << ", White " << rowWhite[i] << '\n';
        }
        for (int i = 0; i < 19; i++) {
            std::cout << "Col " << i << ": Black " << colBlack[i] << ", White " << colWhite[i] << '\n';
        }
        std::cout << "Main diagonal: Black " << diag1Black << ", White " << diag1White << '\n';
        std::cout << "Anti diagonal: Black " << diag2Black << ", White " << diag2White << '\n';
    }
};

int main() {
    BadukBoard board;
    int x, y;
    while (true) {
        std::cout << "\n\n\n";
        board.printBoard();
        std::cout << "좌표를 입력하세요(ex 3 5), 종료코드(-1 -1): ";

        if (!(std::cin >> y >> x)) { // Notice x and y are swapped here
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "숫자 좌표를 입력해주세요.\n";
            continue;
        }

        if (x == -1 && y == -1) break;

        if (x < 0 || x > 18 || y < 0 || y > 18) {
            std::cout << "0 ~ 18 사이의 좌표를 입력해주세요.\n";
            continue;
        }

        if (!board.placeStone(y, x)) {
            std::cout << "이미 돌이 놓여있습니다. 다른 좌표를 입력해주세요.\n";
        }

    }
    board.countStones();

}