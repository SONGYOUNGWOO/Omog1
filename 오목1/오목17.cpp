#include <iostream>
#include <random>
using namespace std;

#define N 19

class Checkboard {
public:
    char board[N][N];
    int x, y;

    Checkboard() {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                board[i][j] = '-';
            }
        }
    }

    void w_turn(int x, int y) {
        board[y][x] = 'W'; // x는 가로, y는 세로
    }

    void b_turn(int x, int y) {
        board[y][x] = 'B'; // x는 가로, y는 세로
    }

    void enter_location() {
        cout << "x (0-" << N - 1 << "): ";
        cin >> x;
        cout << "y (0-" << N - 1 << "): ";
        cin >> y;
    }

    void check_overlap(int x, int y) {
        while (board[y][x] != '-') { // x는 가로, y는 세로
            cout << "Enter other location. The spot is already taken." << endl;
            enter_location();
        }
    }

    bool check_end(int x, int y, char c) {
        int i, j;
        int dir[4] = { 0, 0, 0, 0 };
        //  dir[0] = diagonal '\'
        //  dir[1] = diagonal '/'
        //  dir[2] = vertical '|'
        //  dir[3] = horizontal '--'

        // Check \ diagonal
        i = x; j = y;
        while (i > 0 && j > 0 && board[j - 1][i - 1] == c) { --i; --j; }
        while (i < N && j < N && board[j][i] == c) { ++dir[0]; ++i; ++j; }

        // Check / diagonal
        i = x; j = y;
        while (i > 0 && j < N - 1 && board[j + 1][i - 1] == c) { --i; ++j; }
        while (i < N && j >= 0 && board[j][i] == c) { ++dir[1]; ++i; --j; }

        // Check vertical |
        i = x; j = y;
        while (j > 0 && board[j - 1][i] == c) { --j; }
        while (j < N && board[j][i] == c) { ++dir[2]; ++j; }

        // Check horizontal --
        i = x; j = y;
        while (i > 0 && board[j][i - 1] == c) { --i; }
        while (i < N && board[j][i] == c) { ++dir[3]; ++i; }

        for (int k = 0; k < 4; k++) {
            if (dir[k] >= 5) return true; // 연속된 돌이 5개 이상인 경우 승리
        }
        return false;
    }

    void print_board() {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cout << board[i][j] << " ";
            }
            cout << endl;
        }
    }

    void placeRandomStone() {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(0, N - 1);
        int x, y;
        do {
            x = dis(gen);
            y = dis(gen);
        } while (board[y][x] != '-');
        board[y][x] = (gen() % 2 == 0) ? 'B' : 'W';
    }

    void initializeRandomStones(int count) {
        for (int i = 0; i < count; ++i) {
            placeRandomStone();
        }
    }

    void countStones() const {
        cout << "가로줄 검은돌 및 흰돌 개수:\n";
        for (int j = 0; j < N; ++j) {
            int blackCount = 0, whiteCount = 0;
            for (int i = 0; i < N; ++i) {
                if (board[j][i] == 'B') {
                    blackCount++;
                }
                else if (board[j][i] == 'W') {
                    whiteCount++;
                }
            }
            cout << "행 " << j + 1 << ": 검은돌 " << blackCount << ", 흰돌 " << whiteCount << '\n';
        }

        cout << "세로줄 검은돌 및 흰돌 개수:\n";
        for (int i = 0; i < N; ++i) {
            int blackCount = 0, whiteCount = 0;
            for (int j = 0; j < N; ++j) {
                if (board[j][i] == 'B') {
                    blackCount++;
                }
                else if (board[j][i] == 'W') {
                    whiteCount++;
                }
            }
            cout << "열 " << char('a' + i) << ": 검은돌 " << blackCount << ", 흰돌 " << whiteCount << '\n';
        }
    }
};

int main() {
    Checkboard board;
    int k = 0;
    bool end = false;

    // 랜덤으로 100개의 돌을 두는 함수 호출
    board.initializeRandomStones(100);
    board.print_board();
    board.countStones();

    while (k < N * N && !end) {
        if (k % 2 == 0) {
            cout << "It's Black's turn!" << endl;
        }
        else {
            cout << "It's White's turn!" << endl;
        }
        board.enter_location();
        board.check_overlap(board.x, board.y);

        if (k % 2 == 0) {
            board.b_turn(board.x, board.y);
        }
        else {
            board.w_turn(board.x, board.y);
        }

        board.print_board();
        board.countStones();

        end = board.check_end(board.x, board.y, (k % 2 == 0) ? 'B' : 'W');
        if (end) {
            cout << ((k % 2 == 0) ? "Black" : "White") << " Wins!" << endl;
            return 0;
        }
        k++;
    }

    cout << "It's a draw!" << endl;
    return 0;
}
