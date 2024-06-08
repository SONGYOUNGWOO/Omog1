#include <iostream>
#include <limits>

#define BOARD_SIZE 19

using namespace std;

class BadukBoard {
private:
    char board[BOARD_SIZE][BOARD_SIZE]; // 바둑판
    char turn; // 돌을 놓을 순서
    int blackStone, whiteStone; // 검은돌, 흰돌

public:
    BadukBoard() : turn('X'), blackStone(0), whiteStone(0) {
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                board[i][j] = '.'; // '+' 대신 '.' 으로 그림
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
        // 바둑판에 놓인 검은 돌의 개수와 흰돌의 개수 출력
        cout << "검은돌 개수: " << blackStone << " 흰돌의 개수: " << whiteStone << '\n';
    }

    bool placeStone(int x, int y) {
        if (board[x][y] != '.') return false;

        // 검은돌과 흰돌을 번갈아 놓는다.
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
        int model[5] = { turn, turn, turn, turn, turn }; // 승리 조건: 5개의 연속된 돌
        int empty_pos[2] = { -1, -1 };

        // 가로, 세로, 대각선 검사
        if (checkHorizontal(board, board, position, model, empty_pos, size) ||
            checkVertical(board, board, position, model, empty_pos, size) ||
            checkDiagonalSE(board, board, position, model, empty_pos, size) ||
            checkDiagonalSW(board, board, position, model, empty_pos, size)) {
            return 1; // 승리
        }

        return 0; // 승리 조건 불충족
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
        // 화면에 바둑판을 그려라
        board.printBoard();
        cout << "좌표를 입력하세요(ex A 5), 종료코드(Q 0): ";

        // 좌표를 입력받아 돌을 놓는다
        cin >> col >> y;
        if (col == 'Q' && y == 0) break; // 종료코드

        x = col - 'A';
        y -= 1;

        if (x < 0 || x > 18 || y < 0 || y > 18) { // 0~18 사이의 좌표
            cout << "==================================================================\n";
            cout << " A ~ S 사이의 문자와 1 ~ 19 사이의 숫자를 입력해주세요\n";
            cout << "==================================================================\n";
            continue;
        }

        // 입력된 좌표위치에 이미 돌이 놓여 있는 경우
        if (!board.placeStone(x, y)) {
            cout << "==================================================================\n";
            cout << "이미 돌이 놓여있습니다. 다른 좌표를 입력해주세요\n";
            cout << "==================================================================\n";
            continue;
        }

        // 승리 조건 검사
        int position[2] = { x, y };
        if (board.checkWin(position, 5)) {
            board.printBoard();
            cout << (board.turn == 'O' ? "검은돌" : "흰돌") << "이(가) 승리했습니다!" << endl;
            break;
        }
    }

    return 0;
}
