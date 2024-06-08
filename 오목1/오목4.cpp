#include <iostream>
#include <cstdlib>
#include <Windows.h>

#define BLACK 1
#define WHITE 2
#define MAP 0

int map[19][19] = { MAP };

void crossGaro()
{
    std::cout << "============가로줄 체크\n";
    for (int i = 0; i < 19; i++)
    {
        int whiteNow = 0, blackNow = 0;
        int whiteMax = 0, blackMax = 0;
        for (int j = 1; j < 19; j++)
        {
            if (map[i][j] == map[i][j - 1])
            {
                if (map[i][j] == WHITE)
                    whiteNow++;
                else if (map[i][j] == BLACK)
                    blackNow++;
            }
            else
            {
                whiteNow = 0;
                blackNow = 0;
            }

            whiteMax = std::max(whiteMax, whiteNow);
            blackMax = std::max(blackMax, blackNow);
        }
        if (whiteMax > blackMax)
            std::cout << i + 1 << "번째 줄 백돌이 더 많고, " << whiteMax << "개\n";
        else if (blackMax > whiteMax)
            std::cout << i + 1 << "번째 줄 흑돌이 더 많고, " << blackMax << "개\n";
    }
}

// You will have to apply similar transformations to other functions like crossSero, etc.

int main()
{
    int turn = 1, inputA, inputB;

    while (true)
    {
        system("cls");

        int countBlack = 0, countWhite = 0;

        for (int i = 0; i < 19; i++)
        {
            for (int j = 0; j < 19; j++)
            {
                if (map[i][j] == MAP)
                    std::cout << "┼";
                else if (map[i][j] == BLACK)
                {
                    std::cout << "●";
                    countBlack++;
                }
                else
                {
                    std::cout << "○";
                    countWhite++;
                }
            }
            std::cout << "\n";
        }

        std::cout << "백돌 : " << countWhite << "\t흑돌 : " << countBlack << "\n";

        crossGaro();
        // Call other functions here if needed

        if (turn % 2 == 1)
            std::cout << "백돌의 차례입니다 ";
        else
            std::cout << "흑돌의 차례입니다 ";

        std::cout << "돌을 놓을 차리 : ";
        std::cin >> inputB >> inputA;

        if (inputA > 19 || inputA < 1 || inputB > 19 || inputB < 1)
        {
            std::cout << "이상한 곳에 돌을 놓지 마시오.\n";
            system("pause");
            continue;
        }

        if (map[inputA - 1][inputB - 1] != MAP)
        {
            std::cout << "이미 돌이 있습니다.\n";
            system("pause");
            continue;
        }
        else
        {
            if (turn % 2 == 1)
                map[inputA - 1][inputB - 1] = WHITE;
            else
                map[inputA - 1][inputB - 1] = BLACK;
        }
        turn++;
    }
    return 0;
}
