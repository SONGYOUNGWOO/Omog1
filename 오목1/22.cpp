#include <iostream>
#include <limits>

#define BOARD_SIZE 19

using namespace std;

class BadukBoard {
private:
    char board[BOARD_SIZE][BOARD_SIZE]; // �ٵ���
    char turn; // ���� ���� ����
    int blackStone, whiteStone; // ������, ��

public:
    BadukBoard() : turn('X'), blackStone(0), whiteStone(0) {
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                board[i][j] = '.'; // '+' ��� '.' ���� �׸�
            }
        }
    }

    void printBoard() const {
        cout << "   ";
        for (char c = 'A'; c < 'A' + BOARD_SIZE; ++c) {
            cout << c << " ";
        }
        cout << '\n';

        for (int i = 0; i < BOARD_SIZE; i++) {
            if (i + 1 < 10) cout << " " << i + 1 << " ";
            else cout << i + 1 << " ";
            for (int j = 0; j < BOARD_SIZE; j++) {
                cout << board[i][j] << " ";
            }
            cout << '\n';
        }
        // �ٵ��ǿ� ���� ���� ���� ������ ���� ���� ���
        cout << "������ ����: " << blackStone << " ���� ����: " << whiteStone << '\n';
    }

    bool placeStone(int x, int y) {
        if (board[x][y] != '.') return false;

        // �������� ���� ������ ���´�.
        board[x][y] = turn;

        if (turn == 'X') {
            ++blackStone;
            turn = 'O';
        }
        else {
            ++whiteStone;
            turn = 'X';
        }
        return true;
    }

    int checkWin(int position[], int size) {
        int model[5] = { turn, turn, turn, turn, turn }; // �¸� ����: 5���� ���ӵ� ��
        int empty_pos[2] = { -1, -1 };

        // ����, ����, �밢�� �˻�
        if (checkHorizontal(board, board, position, model, empty_pos, size) ||
            checkVertical(board, board, position, model, empty_pos, size) ||
            checkDiagonalSE(board, board, position, model, empty_pos, size) ||
            checkDiagonalSW(board, board, position, model, empty_pos, size)) {
            return 1; // �¸�
        }

        return 0; // �¸� ���� ������
    }
    int checkHorizontal(char target_board[][BOARD_SIZE], int position[], int model[], int empty_pos[], int size) {
        int cnt = 0;
        for (int i = 0; i < size; i++) {
            if (position[0] + i < BOARD_SIZE) {
                if (target_board[position[1]][position[0] + i] == model[i]) {
                    if (i != 0 && i != (size - 1) && model[i] == 0) {
                        empty_pos[1] = position[1];
                        empty_pos[0] = position[0] + i;
                    }
                    cnt++;
                }
                else {
                    break;
                }
            }
            else {
                break;
            }
        }
        if (cnt == size) {
            return 1;
        }

        cnt = 0;
        for (int i = 0; i < size; i++) {
            if (position[0] + i < BOARD_SIZE) {
                if (target_board[position[1]][position[0] + i] == model[(size - 1) - i]) {
                    if (i != 0 && i != (size - 1) && model[(size - 1) - i] == 0) {
                        empty_pos[1] = position[1];
                        empty_pos[0] = position[0] + i;
                    }
                    cnt++;
                }
                else {
                    break;
                }
            }
            else {
                break;
            }
        }
        if (cnt == size) {
            return 1;
        }

        return 0;
    }

    int checkVertical(char target_board[][BOARD_SIZE], int position[], int model[], int empty_pos[], int size) {
        int cnt = 0;
        for (int i = 0; i < size; i++) {
            if (position[1] + i < BOARD_SIZE) {
                if (target_board[position[1] + i][position[0]] == model[i]) {
                    if (i != 0 && i != (size - 1) && model[i] == 0) {
                        empty_pos[1] = position[1] + i;
                        empty_pos[0] = position[0];
                    }
                    cnt++;
                }
                else {
                    break;
                }
            }
            else {
                break;
            }
        }
        if (cnt == size) {
            return 1;
        }

        cnt = 0;
        for (int i = 0; i < size; i++) {
            if (position[1] + i < BOARD_SIZE) {
                if (target_board[position[1] + i][position[0]] == model[size - 1 - i]) {
                    if (i != 0 && i != (size - 1) && model[(size - 1) - i] == 0) {
                        empty_pos[1] = position[1] + i;
                        empty_pos[0] = position[0];
                    }
                    cnt++;
                }
                else {
                    break;
                }
            }
            else {
                break;
            }
        }
        if (cnt == size) {
            return 1;
        }

        return 0;
    }

    int checkDiagonalSE(char target_board[][BOARD_SIZE], int position[], int model[], int empty_pos[], int size) {
        int cnt = 0;
        for (int i = 0; i < size; i++) {
            if (position[0] + i < BOARD_SIZE && position[1] + i < BOARD_SIZE) {
                if (target_board[position[1] + i][position[0] + i] == model[i]) {
                    if (i != 0 && i != (size - 1) && model[i] == 0) {
                        empty_pos[1] = position[1] + i;
                        empty_pos[0] = position[0] + i;
                    }
                    cnt++;
                }
                else {
                    break;
                }
            }
            else {
                break;
            }
        }
        if (cnt == size) {
            return 1;
        }

        cnt = 0;
        for (int i = 0; i < size; i++) {
            if (position[0] + i < BOARD_SIZE && position[1] + i < BOARD_SIZE) {
                if (target_board[position[1] + i][position[0] + i] == model[size - 1 - i]) {
                    if (i != 0 && i != (size - 1) && model[(size - 1) - i] == 0) {
                        empty_pos[1] = position[1] + i;
                        empty_pos[0] = position[0] + i;
                    }
                    cnt++;
                }
                else {
                    break;
                }
            }
            else {
                break;
            }
        }
        if (cnt == size) {
            return 1;
        }

        return 0;
    }

    int checkDiagonalSW(char target_board[][BOARD_SIZE], int position[], int model[], int empty_pos[], int size) {
        int cnt = 0;
        for (int i = 0; i < size; i++) {
            if (position[0] + i < BOARD_SIZE && position[1] - i >= 0) {
                if (target_board[position[1] - i][position[0] + i] == model[i]) {
                    if (i != 0 && i != (size - 1) && model[i] == 0) {
                        empty_pos[1] = position[1] - i;
                        empty_pos[0] = position[0] + i;
                    }
                    cnt++;
                }
                else {
                    break;
                }
            }
            else {
                break;
            }
        }
        if (cnt == size) {
            return 1;
        }

        cnt = 0;
        for (int i = 0; i < size; i++) {
            if (position[0] + i < BOARD_SIZE && position[1] - i >= 0) {
                if (target_board[position[1] - i][position[0] + i] == model[size - 1 - i]) {
                    if (i != 0 && i != (size - 1) && model[(size - 1) - i] == 0) {
                        empty_pos[1] = position[1] - i;
                        empty_pos[0] = position[0] + i;
                    }
                    cnt++;
                }
                else {
                    break;
                }
            }
            else {
                break;
            }
        }
        if (cnt == size) {
            return 1;
        }

        return 0;
    }

};

int main() {
    BadukBoard board;
    int x, y;
    char col;
    while (true) {
        cout << "\n\n\n";
        // ȭ�鿡 �ٵ����� �׷���
        board.printBoard();
        cout << "��ǥ�� �Է��ϼ���(ex A 5), �����ڵ�(Q 0): ";

        // ��ǥ�� �Է¹޾� ���� ���´�
        cin >> col >> y;
        if (col == 'Q' && y == 0) break; // �����ڵ�

        x = col - 'A';
        y -= 1;

        if (x < 0 || x > 18 || y < 0 || y > 18) { // 0~18 ������ ��ǥ
            cout << "==================================================================\n";
            cout << " A ~ S ������ ���ڿ� 1 ~ 19 ������ ���ڸ� �Է����ּ���\n";
            cout << "==================================================================\n";
            continue;
        }

        // �Էµ� ��ǥ��ġ�� �̹� ���� ���� �ִ� ���
        if (!board.placeStone(x, y)) {
            cout << "==================================================================\n";
            cout << "�̹� ���� �����ֽ��ϴ�. �ٸ� ��ǥ�� �Է����ּ���\n";
            cout << "==================================================================\n";
            continue;
        }

        // �¸� ���� �˻�
        int position[2] = { x, y };
        if (board.checkWin(position, 5)) {
            board.printBoard();
            cout << (board.turn == 'O' ? "������" : "��") << "��(��) �¸��߽��ϴ�!" << endl;
            break;
        }
    }

    return 0;
}
