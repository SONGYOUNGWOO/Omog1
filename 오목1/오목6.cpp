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

    bool placeStone(int x, int y) {
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

    void countDiagonalStones() {
        // Arrays to hold stone counts for each possible diagonal
        int diagMajorBlack[37] = { 0 }, diagMajorWhite[37] = { 0 };
        int diagMinorBlack[37] = { 0 }, diagMinorWhite[37] = { 0 };

        // Calculate stone counts for all diagonals
        for (int i = 0; i < 19; i++) {
            for (int j = 0; j < 19; j++) {
                if (board[j][i] == 'X') {
                    diagMajorBlack[i - j + 18]++;
                    diagMinorBlack[i + j]++;
                }
                else if (board[j][i] == 'O') {
                    diagMajorWhite[i - j + 18]++;
                    diagMinorWhite[i + j]++;
                }
            }
        }

        // Output the results
        std::cout << "Major Diagonals (↘):\n";
        for (int i = 0; i < 37; i++) {
            if (diagMajorBlack[i] > 0 || diagMajorWhite[i] > 0) {
                std::cout << "Diagonal " << i - 18 << ": Black " << diagMajorBlack[i] << ", White " << diagMajorWhite[i] << '\n';
            }
        }

        std::cout << "Minor Diagonals (↙):\n";
        for (int i = 0; i < 37; i++) {
            if (diagMinorBlack[i] > 0 || diagMinorWhite[i] > 0) {
                std::cout << "Diagonal " << i << ": Black " << diagMinorBlack[i] << ", White " << diagMinorWhite[i] << '\n';
            }
        }
    }
};

int main() {
    BadukBoard board;
    int x, y;
    while (true) {
        std::cout << "\n\n\n";
        board.printBoard();
        std::cout << "좌표를 입력하세요(ex 3 5), 종료코드(-1 -1): ";

        if (!(std::cin >> y >> x)) {
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
    board.countDiagonalStones();

}
