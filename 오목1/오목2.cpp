#include<iostream>

class BadukBoard
{
private:
    char board[19][19];
    int blackStonesX[361], blackStonesY[361];
    int whiteStonesX[361], whiteStonesY[361];
    int blackCount;
    int whiteCount;
    char turn;

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

    // Analyze lines for the number and sequence of stones
    void analyzeBoard() {
        for (int i = 0; i < 19; i++) {
            analyzeLine(i, true); // Analyze each row
            analyzeLine(i, false); // Analyze each column
        }

        // Analyze diagonals from both directions
        for (int i = -14; i <= 14; i++) {
            analyzeDiagonal(i, true);  // / diagonal
            analyzeDiagonal(i, false); // \ diagonal
        }
    }

    void analyzeLine(int index, bool isRow) {
        int blackCount = 0, whiteCount = 0, maxBlack = 0, maxWhite = 0;
        int blackSequence = 0, whiteSequence = 0;
        int startSeqX = 0, startSeqY = 0;
        char lastStone = '.';

        for (int i = 0; i < 19; i++) {
            int x = isRow ? index : i;
            int y = isRow ? i : index;
            char currentStone = board[x][y];

            if (currentStone == 'X') {
                blackCount++;
                if (lastStone == 'X') {
                    blackSequence++;
                }
                else {
                    blackSequence = 1;
                    startSeqX = x;
                    startSeqY = y;
                }
                if (blackSequence > maxBlack) {
                    maxBlack = blackSequence;
                }
            }
            else if (currentStone == 'O') {
                whiteCount++;
                if (lastStone == 'O') {
                    whiteSequence++;
                }
                else {
                    whiteSequence = 1;
                }
                if (whiteSequence > maxWhite) {
                    maxWhite = whiteSequence;
                }
            }
            else {
                blackSequence = 0;
                whiteSequence = 0;
            }

            lastStone = currentStone;
        }

        // Output the results for this line
        std::cout << (isRow ? "행 " : "열 ") << index
            << ": 검은 돌 = " << blackCount << ", 흰 돌 = " << whiteCount << '\n';
        std::cout << " 가장 긴 검은 돌 시퀀스 = " << maxBlack << ", 가장 긴 흰 돌 시퀀스 = " << maxWhite << '\n';
        if (isRow) { // If row, print the coordinates of the longest sequence of black stones
            std::cout << " 가장 긴 검은 돌 시퀀스의 시작 위치: (" << index << ", " << startSeqY << ")\n";
        }
    }

    void analyzeDiagonal(int start, bool isMain) {
        int blackCount = 0, whiteCount = 0, maxBlack = 0, maxWhite = 0;
        int blackSequence = 0, whiteSequence = 0;
        char lastStone = '.';
        int x = start >= 0 ? start : 0;
        int y = start >= 0 ? 0 : -start;
        int limit = 19 - std::max(x, y);

        for (int i = 0; i < limit; i++) {
            int currentX = isMain ? x + i : 18 - (x + i);
            int currentY = y + i;
            char currentStone = board[currentX][currentY];

            if (currentStone == 'X') {
                blackCount++;
                if (lastStone == 'X') {
                    blackSequence++;
                }
                else {
                    blackSequence = 1;
                }
                if (blackSequence > maxBlack) {
                    maxBlack = blackSequence;
                }
            }
            else if (currentStone == 'O') {
                whiteCount++;
                if (lastStone == 'O') {
                    whiteSequence++;
                }
                else {
                    whiteSequence = 1;
                }
                if (whiteSequence > maxWhite) {
                    maxWhite = whiteSequence;
                }
            }
            else {
                blackSequence = 0;
                whiteSequence = 0;
            }

            lastStone = currentStone;
        }

        // Output the results for this diagonal
        std::cout << "대각선 시작 위치 (" << x << ", " << y << ") " << (isMain ? "\\" : "/")
            << ": 검은 돌 = " << blackCount << ", 흰 돌 = " << whiteCount << '\n';
        std::cout << " 가장 긴 검은 돌 시퀀스 = " << maxBlack << ", 가장 긴 흰 돌 시퀀스 = " << maxWhite << '\n';
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

        if (!board.placeStone(x, y)) {
            std::cout << "이미 돌이 놓여있습니다. 다른 좌표를 입력해주세요.\n";
        }
    }

    // After game is over or stopped, analyze the board
    board.analyzeBoard();
}
