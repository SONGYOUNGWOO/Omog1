#include <iostream>
#include <random>
using namespace std;

#define BOARD_SIZE 19

class Checkboard {
public:
    char board[BOARD_SIZE][BOARD_SIZE];
    int x, y;
    int black_count;
    int white_count;

    Checkboard() : black_count(0), white_count(0) {
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                board[i][j] = '-';
            }
        }
    }

    void w_turn(int x, int y) {
        board[y][x] = 'W';
        white_count++; // 흰돌 개수 증가
    }

    void b_turn(int x, int y) {
        board[y][x] = 'B';
        black_count++; // 검은돌 개수 증가
    }

    void enter_location() {
        cout << "x (0-" << BOARD_SIZE - 1 << "): ";
        cin >> x;
        cout << "y (0-" << BOARD_SIZE - 1 << "): ";
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
        // dir[0] = 대각선 '\'
        // dir[1] = 대각선 '/'
        // dir[2] = 수직 '|'
        // dir[3] = 수평 '--'

        // Check \ diagonal
        i = x; j = y;
        while (i > 0 && j > 0 && board[j - 1][i - 1] == c) { --i; --j; }
        while (i < BOARD_SIZE && j < BOARD_SIZE && board[j][i] == c) { ++dir[0]; ++i; ++j; }

        // Check / diagonal
        i = x; j = y;
        while (i > 0 && j < BOARD_SIZE - 1 && board[j + 1][i - 1] == c) { --i; ++j; }
        while (i < BOARD_SIZE && j >= 0 && board[j][i] == c) { ++dir[1]; ++i; --j; }

        // Check vertical |
        i = x; j = y;
        while (j > 0 && board[j - 1][i] == c) { --j; }
        while (j < BOARD_SIZE && board[j][i] == c) { ++dir[2]; ++j; }

        // Check horizontal --
        i = x; j = y;
        while (i > 0 && board[j][i - 1] == c) { --i; }
        while (i < BOARD_SIZE && board[j][i] == c) { ++dir[3]; ++i; }

        for (int k = 0; k < 4; k++) {
            if (dir[k] >= 5) return true; // 연속된 돌이 5개 이상인 경우 승리
        }
        return false;
    }

    void print_board() {
        // 열 번호 출력
        cout << "   ";
        for (int i = 0; i < BOARD_SIZE; i++) {
            cout << (i % 10) << " ";
        }
        cout << endl;

        // 행 번호와 보드 출력
        for (int i = 0; i < BOARD_SIZE; i++) {
            cout << i;
            if (i < 10) {
                cout << "  ";
            }
            else {
                cout << " ";
            }

            for (int j = 0; j < BOARD_SIZE; j++) {
                cout << board[i][j] << " ";
            }
            cout << endl;
        }

        // 검은돌과 흰돌 개수 출력
        cout << "검은돌 개수: " << black_count << ", 흰돌 개수: " << white_count << endl;
    }

    void placeRandomStone() {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(0, BOARD_SIZE - 1);
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
        for (int j = 0; j < BOARD_SIZE; ++j) {
            int blackCount = 0, whiteCount = 0;
            for (int i = 0; i < BOARD_SIZE; ++i) {
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
        for (int i = 0; i < BOARD_SIZE; ++i) {
            int blackCount = 0, whiteCount = 0;
            for (int j = 0; j < BOARD_SIZE; ++j) {
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

    void checkConsecutive() {
        for (int y = 0; y < BOARD_SIZE; y++) {
            int maxBlackHorizontal = 0, maxWhiteHorizontal = 0;
            int currentBlackCount = 0, currentWhiteCount = 0;

            for (int x = 0; x < BOARD_SIZE; x++) {
                if (board[y][x] == 'B') {
                    currentBlackCount++;
                    maxBlackHorizontal = max(maxBlackHorizontal, currentBlackCount);
                    currentWhiteCount = 0;
                }
                else if (board[y][x] == 'W') {
                    currentWhiteCount++;
                    maxWhiteHorizontal = max(maxWhiteHorizontal, currentWhiteCount);
                    currentBlackCount = 0;
                }
                else {
                    currentBlackCount = 0;
                    currentWhiteCount = 0;
                }
            }
            cout << "행 " << y << " - 검은돌: " << maxBlackHorizontal << ", 흰돌: " << maxWhiteHorizontal << endl;
        }

        for (int x = 0; x < BOARD_SIZE; x++) {
            int maxBlackVertical = 0, maxWhiteVertical = 0;
            int currentBlackCount = 0, currentWhiteCount = 0;

            for (int y = 0; y < BOARD_SIZE; y++) {
                if (board[y][x] == 'B') {
                    currentBlackCount++;
                    maxBlackVertical = max(maxBlackVertical, currentBlackCount);
                    currentWhiteCount = 0;
                }
                else if (board[y][x] == 'W') {
                    currentWhiteCount++;
                    maxWhiteVertical = max(maxWhiteVertical, currentWhiteCount);
                    currentBlackCount = 0;
                }
                else {
                    currentBlackCount = 0;
                    currentWhiteCount = 0;
                }
            }
            cout << "열 " << x << " - 검은돌: " << maxBlackVertical << ", 흰돌: " << maxWhiteVertical << endl;
        }
    }

    //대각선 (SE) 방향 최대 연속 돌 개수 계산 함수:
    void checkDiagonalSEConsecutive() {
        // ↘ 방향 대각선 (주 대각선)
        for (int start = 0; start < BOARD_SIZE; ++start) {
            int maxBlack = 0, maxWhite = 0;
            int currentBlack = 0, currentWhite = 0;

            // 좌상단에서 출발하는 대각선
            for (int i = 0; i + start < BOARD_SIZE; ++i) {
                if (board[i][i + start] == 'B') {
                    currentBlack++;
                    maxBlack = max(maxBlack, currentBlack);
                    currentWhite = 0;
                }
                else if (board[i][i + start] == 'W') {
                    currentWhite++;
                    maxWhite = max(maxWhite, currentWhite);
                    currentBlack = 0;
                }
                else {
                    currentBlack = 0;
                    currentWhite = 0;
                }
            }
            cout << "대각선 SE 시작점 (" << start << ", " << 0 << ") - 검은돌: " << maxBlack << ", 흰돌: " << maxWhite << endl;

            // 우상단에서 출발하는 대각선
            if (start > 0) {
                maxBlack = 0;
                maxWhite = 0;
                currentBlack = 0;
                currentWhite = 0;
                for (int i = 0; i + start < BOARD_SIZE; ++i) {
                    if (board[i + start][i] == 'B') {
                        currentBlack++;
                        maxBlack = max(maxBlack, currentBlack);
                        currentWhite = 0;
                    }
                    else if (board[i + start][i] == 'W') {
                        currentWhite++;
                        maxWhite = max(maxWhite, currentWhite);
                        currentBlack = 0;
                    }
                    else {
                        currentBlack = 0;
                        currentWhite = 0;
                    }
                }
                cout << "대각선 SE 시작점 (" << 0 << ", " << start << ") - 검은돌: " << maxBlack << ", 흰돌: " << maxWhite << endl;
            }
        }
    }

    //대각선 (SW) 방향 최대 연속 돌 개수 계산 함수:
    void checkDiagonalSWConsecutive() {
        // ↙ 방향 대각선 (부 대각선)
        for (int start = 0; start < BOARD_SIZE; ++start) {
            int maxBlack = 0, maxWhite = 0;
            int currentBlack = 0, currentWhite = 0;

            // 우상단에서 출발하는 대각선
            for (int i = 0; i + start < BOARD_SIZE; ++i) {
                if (board[BOARD_SIZE - 1 - (start + i)][i] == 'B') {
                    currentBlack++;
                    maxBlack = max(maxBlack, currentBlack);
                    currentWhite = 0;
                }
                else if (board[BOARD_SIZE - 1 - (start + i)][i] == 'W') {
                    currentWhite++;
                    maxWhite = max(maxWhite, currentWhite);
                    currentBlack = 0;
                }
                else {
                    currentBlack = 0;
                    currentWhite = 0;
                }
            }
            cout << "대각선 SW 시작점 (" << BOARD_SIZE - 1 - start << ", " << 0 << ") - 검은돌: " << maxBlack << ", 흰돌: " << maxWhite << endl;

            // 좌하단에서 출발하는 대각선
            if (start > 0) {
                maxBlack = 0;
                maxWhite = 0;
                currentBlack = 0;
                currentWhite = 0;
                for (int i = 0; i + start < BOARD_SIZE; ++i) {
                    if (board[BOARD_SIZE - 1 - i][start + i] == 'B') {
                        currentBlack++;
                        maxBlack = max(maxBlack, currentBlack);
                        currentWhite = 0;
                    }
                    else if (board[BOARD_SIZE - 1 - i][start + i] == 'W') {
                        currentWhite++;
                        maxWhite = max(maxWhite, currentWhite);
                        currentBlack = 0;
                    }
                    else {
                        currentBlack = 0;
                        currentWhite = 0;
                    }
                }
                cout << "대각선 SW 시작점 (" << BOARD_SIZE - 1 << ", " << start << ") - 검은돌: " << maxBlack << ", 흰돌: " << maxWhite << endl;
            }
        }
    }



    int checkHorizontal(char target_board[][BOARD_SIZE], char opposite_board[][BOARD_SIZE], int position[], char model[], int empty_pos[], int size, int& maxCount, vector<pair<int, int>>& coords) {
        int cnt = 0;
        for (int i = 0; i < size; i++) {
            if (position[1] + i < BOARD_SIZE) {
                if (target_board[position[0]][position[1] + i] == model[i]) {
                    if (i != 0 && i != (size - 1) && model[i] == '-') {
                        empty_pos[1] = position[0];
                        empty_pos[0] = position[1] + i;
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
        if (cnt > maxCount) {
            maxCount = cnt;
            coords.clear();
            for (int i = 0; i < cnt; i++) {
                coords.push_back({ position[0], position[1] + i });
            }
        }

        cnt = 0;
        for (int i = 0; i < size; i++) {
            if (position[1] + i < BOARD_SIZE) {
                if (target_board[position[0]][position[1] + i] == model[(size - 1) - i]) {
                    if (i != 0 && i != (size - 1) && model[(size - 1) - i] == '-') {
                        empty_pos[1] = position[0];
                        empty_pos[0] = position[1] + i;
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
        if (cnt > maxCount) {
            maxCount = cnt;
            coords.clear();
            for (int i = 0; i < cnt; i++) {
                coords.push_back({ position[0], position[1] + (size - 1) - i });
            }
        }

        return cnt == size && (opposite_board[position[0]][position[1]] == '-' && opposite_board[position[0]][position[1] + (size - 1)] == '-');
    }

    int checkVertical(char target_board[][BOARD_SIZE], char opposite_board[][BOARD_SIZE], int position[], char model[], int empty_pos[], int size, int& maxCount, vector<pair<int, int>>& coords) {
        int cnt = 0;
        for (int i = 0; i < size; i++) {
            if (position[0] + i < BOARD_SIZE) {
                if (target_board[position[0] + i][position[1]] == model[i]) {
                    if (i != 0 && i != (size - 1) && model[i] == '-') {
                        empty_pos[1] = position[0] + i;
                        empty_pos[0] = position[1];
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
        if (cnt > maxCount) {
            maxCount = cnt;
            coords.clear();
            for (int i = 0; i < cnt; i++) {
                coords.push_back({ position[0] + i, position[1] });
            }
        }

        cnt = 0;
        for (int i = 0; i < size; i++) {
            if (position[0] + i < BOARD_SIZE) {
                if (target_board[position[0] + i][position[1]] == model[size - 1 - i]) {
                    if (i != 0 && i != (size - 1) && model[(size - 1) - i] == '-') {
                        empty_pos[1] = position[0] + i;
                        empty_pos[0] = position[1];
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
        if (cnt > maxCount) {
            maxCount = cnt;
            coords.clear();
            for (int i = 0; i < cnt; i++) {
                coords.push_back({ position[0] + (size - 1) - i, position[1] });
            }
        }

        return cnt == size && (opposite_board[position[0]][position[1]] == '-' && opposite_board[position[0] + (size - 1)][position[1]] == '-');
    }

    int checkDiagonalSE(char target_board[][BOARD_SIZE], char opposite_board[][BOARD_SIZE], int position[], char model[], int empty_pos[], int size, int& maxCount, vector<pair<int, int>>& coords) {
        int cnt = 0;
        for (int i = 0; i < size; i++) {
            if (position[0] + i < BOARD_SIZE && position[1] + i < BOARD_SIZE) {
                if (target_board[position[0] + i][position[1] + i] == model[i]) {
                    if (i != 0 && i != (size - 1) && model[i] == '-') {
                        empty_pos[1] = position[0] + i;
                        empty_pos[0] = position[1] + i;
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
        if (cnt > maxCount) {
            maxCount = cnt;
            coords.clear();
            for (int i = 0; i < cnt; i++) {
                coords.push_back({ position[0] + i, position[1] + i });
            }
        }

        cnt = 0;
        for (int i = 0; i < size; i++) {
            if (position[0] + i < BOARD_SIZE && position[1] + i < BOARD_SIZE) {
                if (target_board[position[0] + i][position[1] + i] == model[size - 1 - i]) {
                    if (i != 0 && i != (size - 1) && model[(size - 1) - i] == '-') {
                        empty_pos[1] = position[0] + i;
                        empty_pos[0] = position[1] + i;
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
        if (cnt > maxCount) {
            maxCount = cnt;
            coords.clear();
            for (int i = 0; i < cnt; i++) {
                coords.push_back({ position[0] + (size - 1) - i, position[1] + (size - 1) - i });
            }
        }

        return cnt == size && (opposite_board[position[0]][position[1]] == '-' && opposite_board[position[0] + (size - 1)][position[1] + (size - 1)] == '-');
    }

    int checkDiagonalSW(char target_board[][BOARD_SIZE], char opposite_board[][BOARD_SIZE], int position[], char model[], int empty_pos[], int size, int& maxCount, vector<pair<int, int>>& coords) {
        int cnt = 0;
        for (int i = 0; i < size; i++) {
            if (position[0] + i < BOARD_SIZE && position[1] - i >= 0) {
                if (target_board[position[0] + i][position[1] - i] == model[i]) {
                    if (i != 0 && i != (size - 1) && model[i] == '-') {
                        empty_pos[1] = position[0] + i;
                        empty_pos[0] = position[1] - i;
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
        if (cnt > maxCount) {
            maxCount = cnt;
            coords.clear();
            for (int i = 0; i < cnt; i++) {
                coords.push_back({ position[0] + i, position[1] - i });
            }
        }

        cnt = 0;
        for (int i = 0; i < size; i++) {
            if (position[0] + i < BOARD_SIZE && position[1] - i >= 0) {
                if (target_board[position[0] + i][position[1] - i] == model[size - 1 - i]) {
                    if (i != 0 && i != (size - 1) && model[(size - 1) - i] == '-') {
                        empty_pos[1] = position[0] + i;
                        empty_pos[0] = position[1] - i;
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
        if (cnt > maxCount) {
            maxCount = cnt;
            coords.clear();
            for (int i = 0; i < cnt; i++) {
                coords.push_back({ position[0] + (size - 1) - i, position[1] - (size - 1) + i });
            }
        }

        return cnt == size && (opposite_board[position[0]][position[1]] == '-' && opposite_board[position[0] + (size - 1)][position[1] - (size - 1)] == '-');
    }

    void initializeRandomStones(char stone, int count) {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(0, BOARD_SIZE - 1);

        for (int i = 0; i < count; ++i) {
            int x, y;
            do {
                x = dis(gen);
                y = dis(gen);
            } while (board[y][x] != '-');
            board[y][x] = stone;
            if (stone == 'B') {
                black_count++;
            }
            else {
                white_count++;
            }
        }
    }


};

int main() {
    Checkboard board;
    int k = 0;
    bool end = false;

    char choice;
    cout << "랜덤으로 돌을 배치하려면 'h'를 입력하세요: ";
    cin >> choice;
    if (choice == 'h') {
        board.initializeRandomStones('B', 50);
        board.initializeRandomStones('W', 50);
    }

    board.print_board();

    while (k < BOARD_SIZE * BOARD_SIZE && !end) {
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
        //board.countStones(); // 가로줄, 세로줄 개수 세는 함수 호출
        //board.checkConsecutive();
        board.checkDiagonalSEConsecutive();
        board.checkDiagonalSWConsecutive();

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
