#include <iostream>
#include <random>
#include <vector>
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
            cout << "다른 위치를 입력하십시오. 해당 위치는 이미 점유되어 있습니다." << endl;
            enter_location();
        }
    }

    bool check_end(int x, int y, char c) {
        int i, j;
        int dir[4] = { 0, 0, 0, 0 };
        //  dir[0] = 대각선 '\'
        //  dir[1] = 대각선 '/'
        //  dir[2] = 수직 '|'
        //  dir[3] = 수평 '--'

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
        // 열 번호 출력
        cout << "   ";
        for (int i = 0; i < N; i++) {
            cout << (i % 10) << " ";
        }
        cout << endl;

        // 행 번호와 보드 출력
        for (int i = 0; i < N; i++) {
            cout << i;
            if (i < 10) {
                cout << "  ";
            }
            else {
                cout << " ";
            }

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
        // 가로줄 검은돌 및 흰돌 개수
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
            cout << "행 " << j << ": 검은돌 " << blackCount << ", 흰돌 " << whiteCount << "\n";
        }

        // 세로줄 검은돌 및 흰돌 개수
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
            cout << "열 " << i << ": 검은돌 " << blackCount << ", 흰돌 " << whiteCount << "\n";
        }
    }

    void countConsecutiveStones() const {
        // 가로줄 검은돌 및 흰돌 연속 개수
        cout << "가로줄 검은돌 및 흰돌 연속 개수:\n";
        for (int j = 0; j < N; ++j) {
            int maxBlack = 0, maxWhite = 0;
            int currentBlack = 0, currentWhite = 0;
            vector<pair<int, int>> maxBlackCoords, maxWhiteCoords;

            for (int i = 0; i < N; ++i) {
                if (board[j][i] == 'B') {
                    currentBlack++;
                    currentWhite = 0;
                    if (currentBlack > maxBlack) {
                        maxBlack = currentBlack;
                        maxBlackCoords.clear();
                        maxBlackCoords.push_back({ j, i - currentBlack + 1 });
                    }
                    else if (currentBlack == maxBlack) {
                        maxBlackCoords.push_back({ j, i - currentBlack + 1 });
                    }
                }
                else if (board[j][i] == 'W') {
                    currentWhite++;
                    currentBlack = 0;
                    if (currentWhite > maxWhite) {
                        maxWhite = currentWhite;
                        maxWhiteCoords.clear();
                        maxWhiteCoords.push_back({ j, i - currentWhite + 1 });
                    }
                    else if (currentWhite == maxWhite) {
                        maxWhiteCoords.push_back({ j, i - currentWhite + 1 });
                    }
                }
                else {
                    currentBlack = 0;
                    currentWhite = 0;
                }
            }

            cout << "행 " << j << ":\n";
            cout << "  검은돌 최대 연속 (" << maxBlack << "): ";
            for (const auto& coord : maxBlackCoords) {
                for (int k = 0; k < maxBlack; ++k)
                    cout << "(" << coord.first << ", " << coord.second + k << ") ";
            }
            cout << "\n  흰돌 최대 연속 (" << maxWhite << "): ";
            for (const auto& coord : maxWhiteCoords) {
                for (int k = 0; k < maxWhite; ++k)
                    cout << "(" << coord.first << ", " << coord.second + k << ") ";
            }
            cout << "\n";
        }

        // 세로줄 검은돌 및 흰돌 연속 개수
        cout << "세로줄 검은돌 및 흰돌 연속 개수:\n";
        for (int i = 0; i < N; ++i) {
            int maxBlack = 0, maxWhite = 0;
            int currentBlack = 0, currentWhite = 0;
            vector<pair<int, int>> maxBlackCoords, maxWhiteCoords;

            for (int j = 0; j < N; ++j) {
                if (board[j][i] == 'B') {
                    currentBlack++;
                    currentWhite = 0;
                    if (currentBlack > maxBlack) {
                        maxBlack = currentBlack;
                        maxBlackCoords.clear();
                        maxBlackCoords.push_back({ j - currentBlack + 1, i });
                    }
                    else if (currentBlack == maxBlack) {
                        maxBlackCoords.push_back({ j - currentBlack + 1, i });
                    }
                }
                else if (board[j][i] == 'W') {
                    currentWhite++;
                    currentBlack = 0;
                    if (currentWhite > maxWhite) {
                        maxWhite = currentWhite;
                        maxWhiteCoords.clear();
                        maxWhiteCoords.push_back({ j - currentWhite + 1, i });
                    }
                    else if (currentWhite == maxWhite) {
                        maxWhiteCoords.push_back({ j - currentWhite + 1, i });
                    }
                }
                else {
                    currentBlack = 0;
                    currentWhite = 0;
                }
            }

            cout << "열 " << i << ":\n";
            cout << "  검은돌 최대 연속 (" << maxBlack << "): ";
            for (const auto& coord : maxBlackCoords) {
                for (int k = 0; k < maxBlack; ++k)
                    cout << "(" << coord.first + k << ", " << coord.second << ") ";
            }
            cout << "\n  흰돌 최대 연속 (" << maxWhite << "): ";
            for (const auto& coord : maxWhiteCoords) {
                for (int k = 0; k < maxWhite; ++k)
                    cout << "(" << coord.first + k << ", " << coord.second << ") ";
            }
            cout << "\n";
        }
    }
    void countDiagonalStones() const {
        // ↘ 방향 대각선 (주 대각선)
        cout << "↘ 방향 대각선 검은돌 및 흰돌 연속 개수:\n";
        for (int k = 0; k < N; ++k) {
            int maxBlack = 0, maxWhite = 0;
            int currentBlack = 0, currentWhite = 0;
            vector<pair<int, int>> maxBlackCoords, maxWhiteCoords;

            for (int i = 0; i < N - k; ++i) {
                if (board[i][i + k] == 'B') {
                    currentBlack++;
                    currentWhite = 0;
                    if (currentBlack > maxBlack) {
                        maxBlack = currentBlack;
                        maxBlackCoords.clear();
                        maxBlackCoords.push_back({ i, i + k });
                    }
                    else if (currentBlack == maxBlack) {
                        maxBlackCoords.push_back({ i, i + k });
                    }
                }
                else if (board[i][i + k] == 'W') {
                    currentWhite++;
                    currentBlack = 0;
                    if (currentWhite > maxWhite) {
                        maxWhite = currentWhite;
                        maxWhiteCoords.clear();
                        maxWhiteCoords.push_back({ i, i + k });
                    }
                    else if (currentWhite == maxWhite) {
                        maxWhiteCoords.push_back({ i, i + k });
                    }
                }
                else {
                    currentBlack = 0;
                    currentWhite = 0;
                }
            }

            cout << "대각선 (0, " << k << ") 시작:\n";
            cout << "  검은돌 최대 연속 (" << maxBlack << "): ";
            for (const auto& coord : maxBlackCoords) {
                for (int l = 0; l < maxBlack; ++l)
                    cout << "(" << coord.first + l << ", " << coord.second + l << ") ";
            }
            cout << "\n  흰돌 최대 연속 (" << maxWhite << "): ";
            for (const auto& coord : maxWhiteCoords) {
                for (int l = 0; l < maxWhite; ++l)
                    cout << "(" << coord.first + l << ", " << coord.second + l << ") ";
            }
            cout << "\n";
        }

        for (int k = 1; k < N; ++k) {
            int maxBlack = 0, maxWhite = 0;
            int currentBlack = 0, currentWhite = 0;
            vector<pair<int, int>> maxBlackCoords, maxWhiteCoords;

            for (int i = 0; i < N - k; ++i) {
                if (board[i + k][i] == 'B') {
                    currentBlack++;
                    currentWhite = 0;
                    if (currentBlack > maxBlack) {
                        maxBlack = currentBlack;
                        maxBlackCoords.clear();
                        maxBlackCoords.push_back({ i + k, i });
                    }
                    else if (currentBlack == maxBlack) {
                        maxBlackCoords.push_back({ i + k, i });
                    }
                }
                else if (board[i + k][i] == 'W') {
                    currentWhite++;
                    currentBlack = 0;
                    if (currentWhite > maxWhite) {
                        maxWhite = currentWhite;
                        maxWhiteCoords.clear();
                        maxWhiteCoords.push_back({ i + k, i });
                    }
                    else if (currentWhite == maxWhite) {
                        maxWhiteCoords.push_back({ i + k, i });
                    }
                }
                else {
                    currentBlack = 0;
                    currentWhite = 0;
                }
            }

            cout << "대각선 (" << k << ", 0) 시작:\n";
            cout << "  검은돌 최대 연속 (" << maxBlack << "): ";
            for (const auto& coord : maxBlackCoords) {
                for (int l = 0; l < maxBlack; ++l)
                    cout << "(" << coord.first - l << ", " << coord.second + l << ") ";
            }
            cout << "\n  흰돌 최대 연속 (" << maxWhite << "): ";
            for (const auto& coord : maxWhiteCoords) {
                for (int l = 0; l < maxWhite; ++l)
                    cout << "(" << coord.first - l << ", " << coord.second + l << ") ";
            }
            cout << "\n";
        }

        // ↙ 방향 대각선 (부 대각선)
       /* cout << "↙ 방향 대각선 검은돌 및 흰돌 연속 개수:\n";
        for (int k = 0; k < N; ++k) {
            int maxBlack = 0, maxWhite = 0;
            int currentBlack = 0, currentWhite = 0;
            vector<pair<int, int>> maxBlackCoords, maxWhiteCoords;

            for (int i = 0; i < N - k; ++i) {
                if (board[i][N - 1 - i - k] == 'B') {
                    currentBlack++;
                    currentWhite = 0;
                    if (currentBlack > maxBlack) {
                        maxBlack = currentBlack;
                        maxBlackCoords.clear();
                        maxBlackCoords.push_back({ i, N - 1 - i - k });
                    }
                    else if (currentBlack == maxBlack) {
                        maxBlackCoords.push_back({ i, N - 1 - i - k });
                    }
                }
                else if (board[i][N - 1 - i - k] == 'W') {
                    currentWhite++;
                    currentBlack = 0;
                    if (currentWhite > maxWhite) {
                        maxWhite = currentWhite;
                        maxWhiteCoords.clear();
                        maxWhiteCoords.push_back({ i, N - 1 - i - k });
                    }
                    else if (currentWhite == maxWhite) {
                        maxWhiteCoords.push_back({ i, N - 1 - i - k });
                    }
                }
                else {
                    currentBlack = 0;
                    currentWhite = 0;
                }
            }

            cout << "대각선 (" << 0 << ", " << N - 1 - k << ") 시작:\n";
            cout << "  검은돌 최대 연속 (" << maxBlack << "): ";
            for (const auto& coord : maxBlackCoords) {
                for (int l = 0; l < maxBlack; ++l)
                    cout << "(" << coord.first + l << ", " << coord.second - l << ") ";
            }
            cout << "\n  흰돌 최대 연속 (" << maxWhite << "): ";
            for (const auto& coord : maxWhiteCoords) {
                for (int l = 0; l < maxWhite; ++l)
                    cout << "(" << coord.first + l << ", " << coord.second - l << ") ";
            }
            cout << "\n";
        }

        for (int k = 1; k < N; ++k) {
            int maxBlack = 0, maxWhite = 0;
            int currentBlack = 0, currentWhite = 0;
            vector<pair<int, int>> maxBlackCoords, maxWhiteCoords;

            for (int i = 0; i < N - k; ++i) {
                if (board[i + k][N - 1 - i] == 'B') {
                    currentBlack++;
                    currentWhite = 0;
                    if (currentBlack > maxBlack) {
                        maxBlack = currentBlack;
                        maxBlackCoords.clear();
                        maxBlackCoords.push_back({ i + k, N - 1 - i });
                    }
                    else if (currentBlack == maxBlack) {
                        maxBlackCoords.push_back({ i + k, N - 1 - i });
                    }
                }
                else if (board[i + k][N - 1 - i] == 'W') {
                    currentWhite++;
                    currentBlack = 0;
                    if (currentWhite > maxWhite) {
                        maxWhite = currentWhite;
                        maxWhiteCoords.clear();
                        maxWhiteCoords.push_back({ i + k, N - 1 - i });
                    }
                    else if (currentWhite == maxWhite) {
                        maxWhiteCoords.push_back({ i + k, N - 1 - i });
                    }
                }
                else {
                    currentBlack = 0;
                    currentWhite = 0;
                }
            }

            cout << "대각선 (" << k << ", " << N - 1 << ") 시작:\n";
            cout << "  검은돌 최대 연속 (" << maxBlack << "): ";
            for (const auto& coord : maxBlackCoords) {
                for (int l = 0; l < maxBlack; ++l)
                    cout << "(" << coord.first + l << ", " << coord.second - l << ") ";
            }
            cout << "\n  흰돌 최대 연속 (" << maxWhite << "): ";
            for (const auto& coord : maxWhiteCoords) {
                for (int l = 0; l < maxWhite; ++l)
                    cout << "(" << coord.first + l << ", " << coord.second - l << ") ";
            }
            cout << "\n";
        }*/


    }
};

int main() {
    Checkboard board;
    int k = 0;
    bool end = false;

    // 랜덤으로 100개의 돌을 두는 함수 호출
    board.initializeRandomStones(100);
    board.print_board();
    //board.countStones(); // 가로줄, 세로줄 개수 세는 함수 호출
    //board.countConsecutiveStones();
    board.countDiagonalStones(); // 대각선 개수 세는 함수 호출

    while (k < N * N && !end) {
        if (k % 2 == 0) {
            cout << "검은돌 차례입니다!" << endl;
        }
        else {
            cout << "흰돌 차례입니다!" << endl;
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
        board.countConsecutiveStones();
        board.countStones(); // 가로줄, 세로줄 개수 세는 함수 호출
        board.countDiagonalStones(); // 대각선 개수 세는 함수 호출

        end = board.check_end(board.x, board.y, (k % 2 == 0) ? 'B' : 'W');
        if (end) {
            cout << ((k % 2 == 0) ? "검은돌" : "흰돌") << " 승리!" << endl;
            return 0;
        }
        k++;
    }

    cout << "무승부입니다!" << endl;
    return 0;
}
