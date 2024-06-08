#include <iostream>
#include <random>
#include <string>

enum Stone {
    Black = 'X',
    White = 'O',
    Empty = '.'
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
        std::cout << "������ ����: " << blackCount << ", �� ����: " << whiteCount << '\n';
    }

    bool placeStone(char xChar, int y) {
        int x = tolower(xChar) - 'a';
        y--;
        if (x < 0 || x >= 19 || y < 0 || y >= 19 || board[x][y] != Empty) {
            std::cout << "�߸��� ��ġ�Դϴ�. a-s, 1-19 ������ ���� �Է����ּ���.\n";
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
    // 1
    void countLines() const {
        std::cout << "������ �� ����:\n";
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
            std::cout << j + 1 << ": ������ " << rowBlack << ", �� " << rowWhite << '\n';
        }

        std::cout << "������ �� ����:\n";
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
            std::cout << char('a' + i) << ": ������ " << colBlack << ", �� " << colWhite << '\n';
        }
    }
    // 2
    void countMaxConsecutiveStones() const {
        std::cout << "�����ٿ��� ���� �� ���� ��:\n";
        for (int j = 0; j < 19; ++j) {
            int maxBlack = 0, maxWhite = 0, currentCount = 0;
            char lastStone = '.';
            for (int i = 0; i < 19; ++i) {
                if (board[i][j] == lastStone)  currentCount++;

                else {
                    if (lastStone == Black)
                        maxBlack = std::max(maxBlack, currentCount);

                    else if (lastStone == White)
                        maxWhite = std::max(maxWhite, currentCount);

                    lastStone = board[i][j];
                    currentCount = 1;
                }
            }
            if (lastStone == Black)
                maxBlack = std::max(maxBlack, currentCount);

            else if (lastStone == White)
                maxWhite = std::max(maxWhite, currentCount);

            std::cout << "�� " << j + 1 << ": ������ " << maxBlack << ", �� " << maxWhite << '\n';
        }

        std::cout << "�����ٿ��� ���� �� ���� ��:\n";
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
            std::cout << "�� " << char('a' + i) << ": ������ " << maxBlack << ", �� " << maxWhite << '\n';
        }
    }

    //3
    void countMaxConsecutiveStonesDiagonals() const {
        std::cout << "�밢�� ���� �� (��, �� ����):\n";
        // �� ����
        for (int k = -18; k <= 18; ++k) {
            int maxBlack = 0, maxWhite = 0, countBlack = 0, countWhite = 0;
            for (int x = std::max(0, k), y = std::max(0, -k); x < 19 && y < 19; ++x, ++y) {
                countBlack = board[x][y] == Black ? countBlack + 1 : 0;
                countWhite = board[x][y] == White ? countWhite + 1 : 0;
                maxBlack = std::max(maxBlack, countBlack);
                maxWhite = std::max(maxWhite, countWhite);
            }
            if (maxBlack > 0 || maxWhite > 0) {
                std::cout << "�밢�� " << (k + 19) << " (��): ������ " << maxBlack << ", �� " << maxWhite << '\n';
            }
        }
        // �� ����
        for (int k = 0; k < 38; ++k) {
            int maxBlack = 0, maxWhite = 0, countBlack = 0, countWhite = 0;
            for (int x = std::min(k, 18), y = k - x; x >= 0 && y < 19; --x, ++y) {
                countBlack = board[x][y] == Black ? countBlack + 1 : 0;
                countWhite = board[x][y] == White ? countWhite + 1 : 0;
                maxBlack = std::max(maxBlack, countBlack);
                maxWhite = std::max(maxWhite, countWhite);
            }
            if (maxBlack > 0 || maxWhite > 0) {
                std::cout << "�밢�� " << (char)('a' + std::min(k, 18)) << " (��): ������ " << maxBlack << ", �� " << maxWhite << '\n';
            }
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
        std::cout << "��ǥ�� �Է��ϼ��� (��: h10), �����Ϸ��� -1, �������� r: ";
        std::getline(std::cin, input);

        if (input == "-1") break;
        if (input == "r") {
            board.placeRandomStone();
            board.printBoard();
            continue;
        }

        if (sscanf(input.c_str(), "%c%d", &xChar, &y) != 2 || !isalpha(xChar) || y < 1 || y > 19) {
            std::cout << "�߸��� ������ �Է��Դϴ�. �ùٸ� ���� ��: 'h10'\n";
            continue;
        }

        if (board.placeStone(xChar, y)) {
            board.printBoard();
        }
    }

    //board.countLines();
    //board.countMaxConsecutiveStones();
    board.countMaxConsecutiveStonesDiagonals();

    return 0;
}
