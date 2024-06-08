#include<iostream>

class BadukBoard
{
private:
    char board[19][19];
    int blackStonesX[361], blackStonesY[361]; // ���� ���� x, y ��ǥ
    int whiteStonesX[361], whiteStonesY[361]; // �� ���� x, y ��ǥ
    int blackCount; // ���� ���� ����
    int whiteCount; // �� ���� ����
    char turn; // ���� ���� ����

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
        std::cout << "������ ����: " << blackCount << ", ���� ����: " << whiteCount << '\n';
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
        std::cout << "��ǥ�� �Է��ϼ���(ex 3 5), �����ڵ�(-1 -1): ";

        if (!(std::cin >> x >> y)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "���� ��ǥ�� �Է����ּ���.\n";
            continue;
        }

        if (x == -1 && y == -1) break; // ���� �ڵ�

        if (x < 0 || x > 18 || y < 0 || y > 18) {
            std::cout << "0 ~ 18 ������ ��ǥ�� �Է����ּ���.\n";
            continue;
        }

        if (!board.placeStone(x, y)) {
            std::cout << "�̹� ���� �����ֽ��ϴ�. �ٸ� ��ǥ�� �Է����ּ���.\n";
        }
    }
}
