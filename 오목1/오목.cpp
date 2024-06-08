#include<iostream>

class BadukBoard
{
private:
    char board[19][19];
    int blackStonesX[361], blackStonesY[361]; // 검은 돌의 x, y 좌표
    int whiteStonesX[361], whiteStonesY[361]; // 흰 돌의 x, y 좌표
    int blackCount; // 검은 돌의 개수
    int whiteCount; // 흰 돌의 개수
    char turn; // 돌을 놓을 순서

public:
    BadukBoard() : turn('X'), blackCount(0), whiteCount(0) {
        for (int i = 0; i < 19; i++) {
            for (int j = 0; j < 19; j++) {
                board[i][j] = '.';
            }
        }
    }

    void printBoard() const {
        for (int i = 0; i < 19; i++) {
            for (int j = 0; j < 19; j++) {
                std::cout << board[i][j] << " ";
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
};

int main()
{
    BadukBoard board;
    int x, y;
    while (true)
    {
        std::cout << "\n\n\n";
        board.printBoard();
        std::cout << "좌표를 입력하세요(ex 3 5), 종료코드(-1 -1): ";

        if (!(std::cin >> x >> y)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "숫자 좌표를 입력해주세요.\n";
            continue;
        }

        if (x == -1 && y == -1) break; // 종료 코드

        if (x < 0 || x > 18 || y < 0 || y > 18) {
            std::cout << "0 ~ 18 사이의 좌표를 입력해주세요.\n";
            continue;
        }

        if (!board.placeStone(x, y)) {
            std::cout << "이미 돌이 놓여있습니다. 다른 좌표를 입력해주세요.\n";
        }
    }
}
