#include <iostream>
#include <cstdlib>
#include <Windows.h>

#define BLACK 1
#define WHITE 2
#define MAP 0

int map[19][19] = { MAP };

void crossGaro()
{
    std::cout << "============������ üũ\n";
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
            std::cout << i + 1 << "��° �� �鵹�� �� ����, " << whiteMax << "��\n";
        else if (blackMax > whiteMax)
            std::cout << i + 1 << "��° �� �浹�� �� ����, " << blackMax << "��\n";
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
                    std::cout << "��";
                else if (map[i][j] == BLACK)
                {
                    std::cout << "��";
                    countBlack++;
                }
                else
                {
                    std::cout << "��";
                    countWhite++;
                }
            }
            std::cout << "\n";
        }

        std::cout << "�鵹 : " << countWhite << "\t�浹 : " << countBlack << "\n";

        crossGaro();
        // Call other functions here if needed

        if (turn % 2 == 1)
            std::cout << "�鵹�� �����Դϴ� ";
        else
            std::cout << "�浹�� �����Դϴ� ";

        std::cout << "���� ���� ���� : ";
        std::cin >> inputB >> inputA;

        if (inputA > 19 || inputA < 1 || inputB > 19 || inputB < 1)
        {
            std::cout << "�̻��� ���� ���� ���� ���ÿ�.\n";
            system("pause");
            continue;
        }

        if (map[inputA - 1][inputB - 1] != MAP)
        {
            std::cout << "�̹� ���� �ֽ��ϴ�.\n";
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
