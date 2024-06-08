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
        white_count++; // �� ���� ����
    }

    void b_turn(int x, int y) {
        board[y][x] = 'B';
        black_count++; // ������ ���� ����
    }

    void enter_location() {
        cout << "x (0-" << BOARD_SIZE - 1 << "): ";
        cin >> x;
        cout << "y (0-" << BOARD_SIZE - 1 << "): ";
        cin >> y;
    }

    void check_overlap(int x, int y) {
        while (board[y][x] != '-') { // x�� ����, y�� ����
            cout << "�ٸ� ��ġ�� �Է��Ͻʽÿ�. �ش� ��ġ�� �̹� �����Ǿ� �ֽ��ϴ�." << endl;
            enter_location();
        }
    }

    bool check_end(int x, int y, char c) {
        int i, j;
        int dir[4] = { 0, 0, 0, 0 };
        // dir[0] = �밢�� '\'
        // dir[1] = �밢�� '/'
        // dir[2] = ���� '|'
        // dir[3] = ���� '--'

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
            if (dir[k] >= 5) return true; // ���ӵ� ���� 5�� �̻��� ��� �¸�
        }
        return false;
    }

    void print_board() {
        // �� ��ȣ ���
        cout << "   ";
        for (int i = 0; i < BOARD_SIZE; i++) {
            cout << (i % 10) << " ";
        }
        cout << endl;

        // �� ��ȣ�� ���� ���
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

        // �������� �� ���� ���
        cout << "������ ����: " << black_count << ", �� ����: " << white_count << endl;
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
        // ������ ������ �� �� ����
        cout << "������ ������ �� �� ����:\n";
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
            cout << "�� " << j << ": ������ " << blackCount << ", �� " << whiteCount << "\n";
        }

        // ������ ������ �� �� ����
        cout << "������ ������ �� �� ����:\n";
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
            cout << "�� " << i << ": ������ " << blackCount << ", �� " << whiteCount << "\n";
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
            cout << "�� " << y << " - ������: " << maxBlackHorizontal << ", ��: " << maxWhiteHorizontal << endl;
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
            cout << "�� " << x << " - ������: " << maxBlackVertical << ", ��: " << maxWhiteVertical << endl;
        }
    }

    //�밢�� (SE) ���� �ִ� ���� �� ���� ��� �Լ�:
    void checkDiagonalSEConsecutive() {
        // �� ���� �밢�� (�� �밢��)
        for (int start = 0; start < BOARD_SIZE; ++start) {
            int maxBlack = 0, maxWhite = 0;
            int currentBlack = 0, currentWhite = 0;

            // �»�ܿ��� ����ϴ� �밢��
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
            cout << "�밢�� SE ������ (" << start << ", " << 0 << ") - ������: " << maxBlack << ", ��: " << maxWhite << endl;

            // ���ܿ��� ����ϴ� �밢��
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
                cout << "�밢�� SE ������ (" << 0 << ", " << start << ") - ������: " << maxBlack << ", ��: " << maxWhite << endl;
            }
        }
    }

    //�밢�� (SW) ���� �ִ� ���� �� ���� ��� �Լ�:
    void checkDiagonalSWConsecutive() {
        // �� ���� �밢�� (�� �밢��)
        for (int start = 0; start < BOARD_SIZE; ++start) {
            int maxBlack = 0, maxWhite = 0;
            int currentBlack = 0, currentWhite = 0;

            // ���ܿ��� ����ϴ� �밢��
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
            cout << "�밢�� SW ������ (" << BOARD_SIZE - 1 - start << ", " << 0 << ") - ������: " << maxBlack << ", ��: " << maxWhite << endl;

            // ���ϴܿ��� ����ϴ� �밢��
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
                cout << "�밢�� SW ������ (" << BOARD_SIZE - 1 << ", " << start << ") - ������: " << maxBlack << ", ��: " << maxWhite << endl;
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
    cout << "�������� ���� ��ġ�Ϸ��� 'h'�� �Է��ϼ���: ";
    cin >> choice;
    if (choice == 'h') {
        board.initializeRandomStones('B', 50);
        board.initializeRandomStones('W', 50);
    }

    board.print_board();

    while (k < BOARD_SIZE * BOARD_SIZE && !end) {
        if (k % 2 == 0) {
            cout << "������ �����Դϴ�!" << endl;
        }
        else {
            cout << "�� �����Դϴ�!" << endl;
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
        //board.countStones(); // ������, ������ ���� ���� �Լ� ȣ��
        //board.checkConsecutive();
        board.checkDiagonalSEConsecutive();
        board.checkDiagonalSWConsecutive();

        end = board.check_end(board.x, board.y, (k % 2 == 0) ? 'B' : 'W');
        if (end) {
            cout << ((k % 2 == 0) ? "������" : "��") << " �¸�!" << endl;
            return 0;
        }
        k++;
    }

    cout << "���º��Դϴ�!" << endl;
    return 0;
}
