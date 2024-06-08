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
        board[y][x] = 'W'; // x�� ����, y�� ����
    }

    void b_turn(int x, int y) {
        board[y][x] = 'B'; // x�� ����, y�� ����
    }

    void enter_location() {
        cout << "x (0-" << N - 1 << "): ";
        cin >> x;
        cout << "y (0-" << N - 1 << "): ";
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
        //  dir[0] = �밢�� '\'
        //  dir[1] = �밢�� '/'
        //  dir[2] = ���� '|'
        //  dir[3] = ���� '--'

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
            if (dir[k] >= 5) return true; // ���ӵ� ���� 5�� �̻��� ��� �¸�
        }
        return false;
    }

    void print_board() {
        // �� ��ȣ ���
        cout << "   ";
        for (int i = 0; i < N; i++) {
            cout << (i % 10) << " ";
        }
        cout << endl;

        // �� ��ȣ�� ���� ���
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
        // ������ ������ �� �� ����
        cout << "������ ������ �� �� ����:\n";
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
            cout << "�� " << j << ": ������ " << blackCount << ", �� " << whiteCount << "\n";
        }

        // ������ ������ �� �� ����
        cout << "������ ������ �� �� ����:\n";
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
            cout << "�� " << i << ": ������ " << blackCount << ", �� " << whiteCount << "\n";
        }
    }

    void countConsecutiveStones() const {
        // ������ ������ �� �� ���� ����
        cout << "������ ������ �� �� ���� ����:\n";
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

            cout << "�� " << j << ":\n";
            cout << "  ������ �ִ� ���� (" << maxBlack << "): ";
            for (const auto& coord : maxBlackCoords) {
                for (int k = 0; k < maxBlack; ++k)
                    cout << "(" << coord.first << ", " << coord.second + k << ") ";
            }
            cout << "\n  �� �ִ� ���� (" << maxWhite << "): ";
            for (const auto& coord : maxWhiteCoords) {
                for (int k = 0; k < maxWhite; ++k)
                    cout << "(" << coord.first << ", " << coord.second + k << ") ";
            }
            cout << "\n";
        }

        // ������ ������ �� �� ���� ����
        cout << "������ ������ �� �� ���� ����:\n";
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

            cout << "�� " << i << ":\n";
            cout << "  ������ �ִ� ���� (" << maxBlack << "): ";
            for (const auto& coord : maxBlackCoords) {
                for (int k = 0; k < maxBlack; ++k)
                    cout << "(" << coord.first + k << ", " << coord.second << ") ";
            }
            cout << "\n  �� �ִ� ���� (" << maxWhite << "): ";
            for (const auto& coord : maxWhiteCoords) {
                for (int k = 0; k < maxWhite; ++k)
                    cout << "(" << coord.first + k << ", " << coord.second << ") ";
            }
            cout << "\n";
        }
    }
    void countDiagonalStones() const {
        // �� ���� �밢�� (�� �밢��)
        cout << "�� ���� �밢�� ������ �� �� ���� ����:\n";
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

            cout << "�밢�� (0, " << k << ") ����:\n";
            cout << "  ������ �ִ� ���� (" << maxBlack << "): ";
            for (const auto& coord : maxBlackCoords) {
                for (int l = 0; l < maxBlack; ++l)
                    cout << "(" << coord.first + l << ", " << coord.second + l << ") ";
            }
            cout << "\n  �� �ִ� ���� (" << maxWhite << "): ";
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

            cout << "�밢�� (" << k << ", 0) ����:\n";
            cout << "  ������ �ִ� ���� (" << maxBlack << "): ";
            for (const auto& coord : maxBlackCoords) {
                for (int l = 0; l < maxBlack; ++l)
                    cout << "(" << coord.first - l << ", " << coord.second + l << ") ";
            }
            cout << "\n  �� �ִ� ���� (" << maxWhite << "): ";
            for (const auto& coord : maxWhiteCoords) {
                for (int l = 0; l < maxWhite; ++l)
                    cout << "(" << coord.first - l << ", " << coord.second + l << ") ";
            }
            cout << "\n";
        }

        // �� ���� �밢�� (�� �밢��)
       /* cout << "�� ���� �밢�� ������ �� �� ���� ����:\n";
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

            cout << "�밢�� (" << 0 << ", " << N - 1 - k << ") ����:\n";
            cout << "  ������ �ִ� ���� (" << maxBlack << "): ";
            for (const auto& coord : maxBlackCoords) {
                for (int l = 0; l < maxBlack; ++l)
                    cout << "(" << coord.first + l << ", " << coord.second - l << ") ";
            }
            cout << "\n  �� �ִ� ���� (" << maxWhite << "): ";
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

            cout << "�밢�� (" << k << ", " << N - 1 << ") ����:\n";
            cout << "  ������ �ִ� ���� (" << maxBlack << "): ";
            for (const auto& coord : maxBlackCoords) {
                for (int l = 0; l < maxBlack; ++l)
                    cout << "(" << coord.first + l << ", " << coord.second - l << ") ";
            }
            cout << "\n  �� �ִ� ���� (" << maxWhite << "): ";
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

    // �������� 100���� ���� �δ� �Լ� ȣ��
    board.initializeRandomStones(100);
    board.print_board();
    //board.countStones(); // ������, ������ ���� ���� �Լ� ȣ��
    //board.countConsecutiveStones();
    board.countDiagonalStones(); // �밢�� ���� ���� �Լ� ȣ��

    while (k < N * N && !end) {
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
        board.countConsecutiveStones();
        board.countStones(); // ������, ������ ���� ���� �Լ� ȣ��
        board.countDiagonalStones(); // �밢�� ���� ���� �Լ� ȣ��

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
