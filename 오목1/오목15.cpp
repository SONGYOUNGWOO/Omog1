#include <iostream>
#include <random>
#include <string>
enum Stone {
    Black = 'X',
    White = '0',
    Empty = '.',
    SBlack = 'x',
    SWhite = 'o',
};

class BadukBoard {
private:
    char board[19][19];
    int blackCount = 0, whiteCount = 0;
    Stone turn = Black;
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_int_distribution<> dis;

public:
    BadukBoard() : gen(rd()), dis(0, 18) {
        for (int i = 0; i < 19; ++i) {
            for (int j = 0; j < 19; ++j) {
                board[i][j] = Empty;
            }
        }
    }

    void printBoard() const {
        std::cout << "   ";
        for (char c = 'a'; c <= 's'; ++c) {
            std::cout << c << " ";
        }
        std::cout << '\n';

        for (int i = 0; i < 19; ++i) {
            std::cout << i + 1 << (i < 9 ? "  " : " ");
            for (int j = 0; j < 19; ++j) {
                std::cout << board[j][i] << ' ';
            }
            std::cout << '\n';
        }
        std::cout << "검은돌 개수: " << blackCount << ", 흰돌 개수: " << whiteCount << '\n';
    }

    bool placeStone(char xChar, int y) {
        int x = tolower(xChar) - 'a';
        y--;
        if (x < 0 || x >= 19 || y < 0 || y >= 19 || board[x][y] != Empty) {
            std::cout << "잘못된 위치입니다. a-s, 1-19 사이의 값을 입력해주세요.\n";
            return false;
        }
        board[x][y] = turn;
        if (turn == Black) {
            blackCount++;
            turn = White;
        }
        else {
            whiteCount++;
            turn = Black;
        }
        return true;
    }

    void placeRandomStone() {
        int x, y;
        do {
            x = dis(gen);
            y = dis(gen);
        } while (board[x][y] != Empty);
        board[x][y] = turn;
        if (turn == Black) {
            blackCount++;
            turn = White;
        }
        else {
            whiteCount++;
            turn = Black;
        }
    }
    void initializeRandomStones(int count) {
        for (int i = 0; i < count; ++i) {
            placeRandomStone();
        }
    }


    // 1
    void countLines() const {
        std::cout << "가로줄 돌 개수:\n";
        for (int j = 0; j < 19; ++j) {
            int rowBlack = 0, rowWhite = 0;
            for (int i = 0; i < 19; ++i) {
                if (board[i][j] == Black) {
                    rowBlack++;
                }
                else if (board[i][j] == White) {
                    rowWhite++;
                }
            }
            std::cout << j + 1 << ": 검은돌 " << rowBlack << ", 흰돌 " << rowWhite << '\n';
        }

        std::cout << "세로줄 돌 개수:\n";
        for (int i = 0; i < 19; ++i) {
            int colBlack = 0, colWhite = 0;
            for (int j = 0; j < 19; ++j) {
                if (board[i][j] == Black) {
                    colBlack++;
                }
                else if (board[i][j] == White) {
                    colWhite++;
                }
            }
            std::cout << char('a' + i) << ": 검은돌 " << colBlack << ", 흰돌 " << colWhite << '\n';
        }
    }
    // 2

    void countAndPrintMaxConsecutiveStonesCoordinates() const {
        std::cout << "가로줄에서 가장 긴 연속 돌의 좌표:\n";
        for (int j = 0; j < 19; ++j) {
            int maxBlack = 0, maxWhite = 0, currentCount = 0;
            char lastStone = '.';
            std::vector<std::pair<int, int>> maxBlackCoords;
            std::vector<std::pair<int, int>> maxWhiteCoords;

            for (int i = 0; i < 19; ++i) {
                if (board[i][j] == lastStone) {
                    currentCount++;
                }
                else {
                    if (lastStone == Black) {
                        if (currentCount > maxBlack) {
                            maxBlack = currentCount;
                            maxBlackCoords.clear();  // Clear previous coordinates
                            maxBlackCoords.push_back({ i - currentCount, j });  // Starting coordinate of the sequence
                        }
                        else if (currentCount == maxBlack) {
                            maxBlackCoords.push_back({ i - currentCount, j });
                        }
                    }
                    else if (lastStone == White) {
                        if (currentCount > maxWhite) {
                            maxWhite = currentCount;
                            maxWhiteCoords.clear();  // Clear previous coordinates
                            maxWhiteCoords.push_back({ i - currentCount, j });  // Starting coordinate of the sequence
                        }
                        else if (currentCount == maxWhite) {
                            maxWhiteCoords.push_back({ i - currentCount, j });
                        }
                    }

                    lastStone = board[i][j];
                    currentCount = 1;
                }
            }

            // Check the last sequence in the line
            if (lastStone == Black) {
                if (currentCount > maxBlack) {
                    maxBlack = currentCount;
                    maxBlackCoords.clear();
                    maxBlackCoords.push_back({ 19 - currentCount, j });
                }
                else if (currentCount == maxBlack) {
                    maxBlackCoords.push_back({ 19 - currentCount, j });
                }
            }
            else if (lastStone == White) {
                if (currentCount > maxWhite) {
                    maxWhite = currentCount;
                    maxWhiteCoords.clear();
                    maxWhiteCoords.push_back({ 19 - currentCount, j });
                }
                else if (currentCount == maxWhite) {
                    maxWhiteCoords.push_back({ 19 - currentCount, j });
                }
            }

            // Print the coordinates for the max consecutive stones
            std::cout << "행 " << j + 1 << ":\n";
            std::cout << "  검은돌 최대 연속 (" << maxBlack << "): ";
            for (const auto& coord : maxBlackCoords) {
                for (int k = 0; k < maxBlack; ++k)
                    std::cout << "(" << coord.first + k + 1 << ", " << char('a' + coord.second) << ") ";
            }
            std::cout << "\n  흰돌 최대 연속 (" << maxWhite << "): ";
            for (const auto& coord : maxWhiteCoords) {
                for (int k = 0; k < maxWhite; ++k)
                    std::cout << "(" << coord.first + k + 1 << ", " << char('a' + coord.second) << ") ";
            }
            std::cout << "\n";
        }


        std::cout << "세로줄에서 가장 긴 연속 돌:\n";
        for (int i = 0; i < 19; ++i) {
            int maxBlack = 0, maxWhite = 0, currentCount = 0;
            char lastStone = '.';
            for (int j = 0; j < 19; ++j) {
                if (board[i][j] == lastStone) {
                    currentCount++;
                }
                else {
                    if (lastStone == Black) {
                        maxBlack = std::max(maxBlack, currentCount);
                    }
                    else if (lastStone == White) {
                        maxWhite = std::max(maxWhite, currentCount);
                    }
                    lastStone = board[i][j];
                    currentCount = 1;
                }
            }
            if (lastStone == Black) {
                maxBlack = std::max(maxBlack, currentCount);
            }
            else if (lastStone == White) {
                maxWhite = std::max(maxWhite, currentCount);
            }
            std::cout << "열 " << char('a' + i) << ": 검은돌 " << maxBlack << ", 흰돌 " << maxWhite << '\n';
        }
    }

    //3
    void countMaxConsecutiveStonesDiagonals() const {
        std::cout << "대각선 연속 돌 (↘ 방향):\n";

        // ↘ 방향 대각선 시작점 1 (a1, b1, c1, ..., s1)
        for (int row = 0; row < 19; ++row) {
            int maxBlack = 0, maxWhite = 0, countBlack = 0, countWhite = 0;
            for (int x = row, y = 0; x < 19 && y < 19; ++x, ++y) {
                countBlack = board[x][y] == Black ? countBlack + 1 : 0;
                countWhite = board[x][y] == White ? countWhite + 1 : 0;
                maxBlack = std::max(maxBlack, countBlack);
                maxWhite = std::max(maxWhite, countWhite);
            }

            std::cout << "대각선 시작 (" << (char)('a' + row) << "1): 검은돌 " << maxBlack << ", 흰돌 " << maxWhite << '\n';

        }

        // ↘ 방향 대각선 시작점 2 (a19, a18, a17, ..., a2)
        for (int col = 1; col < 19; ++col) {
            int maxBlack = 0, maxWhite = 0, countBlack = 0, countWhite = 0;
            for (int x = 0, y = col; x < 19 && y < 19; ++x, ++y) {
                countBlack = board[x][y] == Black ? countBlack + 1 : 0;
                countWhite = board[x][y] == White ? countWhite + 1 : 0;
                maxBlack = std::max(maxBlack, countBlack);
                maxWhite = std::max(maxWhite, countWhite);
            }

            std::cout << "대각선 시작 2 (a" << col + 1 << "): 검은돌 " << maxBlack << ", 흰돌 " << maxWhite << '\n';

        }
        std::cout << "대각선 연속 돌 (↙ 방향):\n";

        // ↙ 방향 대각선 시작점 1 (a1, b1, c1, ..., s1)
        for (int row = 0; row < 19; ++row) {
            int maxBlack = 0, maxWhite = 0, countBlack = 0, countWhite = 0;
            for (int x = row, y = 0; x >= 0 && x < 19 && y < 19; --x, ++y) {
                countBlack = board[x][y] == Black ? countBlack + 1 : 0;
                countWhite = board[x][y] == White ? countWhite + 1 : 0;
                maxBlack = std::max(maxBlack, countBlack);
                maxWhite = std::max(maxWhite, countWhite);
            }

            std::cout << "대각선 시작 (" << (char)('a' + row) << "1): 검은돌 " << maxBlack << ", 흰돌 " << maxWhite << '\n';
        }

        // ↙ 방향 대각선 시작점 2 (s2, s3, ..., s19)
        for (int col = 1; col < 19; ++col) {
            int maxBlack = 0, maxWhite = 0, countBlack = 0, countWhite = 0;
            for (int x = 18, y = col; x >= 0 && y < 19; --x, ++y) {
                countBlack = board[x][y] == Black ? countBlack + 1 : 0;
                countWhite = board[x][y] == White ? countWhite + 1 : 0;
                maxBlack = std::max(maxBlack, countBlack);
                maxWhite = std::max(maxWhite, countWhite);
            }

            std::cout << "대각선 시작 (" << "s" << col + 1 << "): 검은돌 " << maxBlack << ", 흰돌 " << maxWhite << '\n';
        }


    }

};

int main() {
    BadukBoard board;
    board.printBoard();
    std::string input;
    char xChar;
    int y;

    while (true) {
        std::cout << "좌표를 입력하세요 (예: h10), 종료하려면 -1, 무작위는 r: ,무작위100개 h:";
        std::getline(std::cin, input);

        if (input == "-1") break;
        if (input == "r") {
            board.placeRandomStone();
            board.printBoard();
            continue;
        }
        if (input == "h") {
            board.initializeRandomStones(100);
            board.printBoard();
            continue;
        }

        if (sscanf(input.c_str(), "%c%d", &xChar, &y) != 2 || !isalpha(xChar) || y < 1 || y > 19) {
            std::cout << "잘못된 형식의 입력입니다. 올바른 형식 예: 'h10'\n";
            continue;
        }

        if (board.placeStone(xChar, y)) {
            board.printBoard();
        }
    }

    //board.countLines();
    board.countAndPrintMaxConsecutiveStonesCoordinates();
    //board.countMaxConsecutiveStonesDiagonals();

    return 0;
}
