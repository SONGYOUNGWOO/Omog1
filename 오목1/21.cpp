#include<iostream>

class BadukBoard
{
private:
	char board[19][19]; //바둑판
	char turn; //돌을 놓을 순서
	int blackStone, whiteStone; // 검은돌 , 흰돌
public:
	BadukBoard() : turn('X'), blackStone(0), whiteStone(0) {
		for (int i = 0; i < 19; i++) {
			for (int j = 0; j < 19; j++) {
				board[i][j] = '.'; // '+ '대신 '.' 으로 그림
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
		//5. 바둑판에 놓인 검은 돌의 개수와 흰돌의 개수 출력
		std::cout << "검은돌 개수: " << blackStone << "흰돌의 개수: " << whiteStone << '\n';
	}

	bool placeStone(int x, int y) {
		if (board[x][y] != '.') return false;

		//4.검은돌과 흰돌을 번갈아 놓는다.
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
		//1.화면에 바둑판을 그려라
		board.printBoard();
		std::cout << "좌표를 입력하세요(ex 3 5),종료코드(-1 -1): ";

		//2.좌표를 입력받아 돌을 놓는다
		if (!(std::cin >> x >> y)) {
			if (std::cin.eof()) break;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "==================================================================\n";
			std::cout << "숫자좌표를 입력해주세요\n";
			std::cout << "==================================================================\n";
			continue;
		}

		if (x == -1 && y == -1)break; //종료코드


		if (x < 0 || x>18 || y < 0 || y>18) { // 0~ 18 사이의 좌표 
			std::cout << "==================================================================\n";
			std::cout << " 0 ~ 18 사이의 좌표를 입력해주세요\n";
			std::cout << "==================================================================\n";
			continue;
		}

		//3.입력된 좌표위치에 이미 돌이 놓여 있는 경우
		if (!board.placeStone(x, y)) {
			std::cout << "==================================================================\n";
			std::cout << "이미 돌이 놓여있습니다. 다른 좌표를 입력해주세요\n";
			std::cout << "==================================================================\n";
		}

	}
}