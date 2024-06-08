#include<iostream>

class BadukBoard
{
private:
	char board[19][19]; //�ٵ���
	char turn; //���� ���� ����
	int blackStone, whiteStone; // ������ , ��
public:
	BadukBoard() : turn('X'), blackStone(0), whiteStone(0) {
		for (int i = 0; i < 19; i++) {
			for (int j = 0; j < 19; j++) {
				board[i][j] = '.'; // '+ '��� '.' ���� �׸�
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
		//5. �ٵ��ǿ� ���� ���� ���� ������ ���� ���� ���
		std::cout << "������ ����: " << blackStone << "���� ����: " << whiteStone << '\n';
	}

	bool placeStone(int x, int y) {
		if (board[x][y] != '.') return false;

		//4.�������� ���� ������ ���´�.
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
};
int main()
{
	BadukBoard board;
	int x, y;
	while (true)
	{
		std::cout << "\n\n\n";
		//1.ȭ�鿡 �ٵ����� �׷���
		board.printBoard();
		std::cout << "��ǥ�� �Է��ϼ���(ex 3 5),�����ڵ�(-1 -1): ";

		//2.��ǥ�� �Է¹޾� ���� ���´�
		if (!(std::cin >> x >> y)) {
			if (std::cin.eof()) break;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "==================================================================\n";
			std::cout << "������ǥ�� �Է����ּ���\n";
			std::cout << "==================================================================\n";
			continue;
		}

		if (x == -1 && y == -1)break; //�����ڵ�


		if (x < 0 || x>18 || y < 0 || y>18) { // 0~ 18 ������ ��ǥ 
			std::cout << "==================================================================\n";
			std::cout << " 0 ~ 18 ������ ��ǥ�� �Է����ּ���\n";
			std::cout << "==================================================================\n";
			continue;
		}

		//3.�Էµ� ��ǥ��ġ�� �̹� ���� ���� �ִ� ���
		if (!board.placeStone(x, y)) {
			std::cout << "==================================================================\n";
			std::cout << "�̹� ���� �����ֽ��ϴ�. �ٸ� ��ǥ�� �Է����ּ���\n";
			std::cout << "==================================================================\n";
		}

	}
}