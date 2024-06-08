#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#define BLACK 1
#define WHITE 2
#define MAP 0

int map[19][19] = { MAP };

void crossGaro(int map[19][19])
{
	int whiteNow, blackNow = 0;
	int whiteMax, blackMax = 1;
	int i, j, count = 0;
	int x, y = 0; // �긦 �� �����...

	int Pcount = 0;
	int px[19] = { 0 };
	int py[19] = { 0 };
	int pz[19] = { 0 };
	int pa[19] = { 0 };
	int cal = 0;
	int result = 0;

	printf("============������ üũ\\n");

	for (i = 1; i < 20; i++)
	{
		int whiteNow = 0;
		int   blackNow = 0;
		int whiteMax = 0;
		int   blackMax = 0;
		int forcount = 0;

		for (j = 1; j < 20; j++)
		{
			if (map[i][j] == map[i][j - 1])
			{
				if (map[i][j] == WHITE)
				{
					whiteNow++;
					if (whiteNow > whiteMax)
					{
						forcount = j;
						whiteMax++;
					}
				}
				else if (map[i][j] == BLACK)
				{
					blackNow++;
					if (blackNow > blackMax)
					{
						forcount = j;
						blackMax++;
					}
				}
			}
			else
			{
				whiteNow = 0;
				blackNow = 0;
			}
		}

		if (whiteMax > blackMax)
		{
			printf("%d��° �� %dĭ �鵹�� �� ����, %d��\\n", i, forcount - 1, whiteMax + 1);
			px[Pcount] = i;
			py[Pcount] = forcount - 1;
			pz[Pcount] = whiteMax + 1;
			pa[Pcount] = 2;
		}
		else if (blackMax > whiteMax)
		{
			printf("%d��° �� %dĭ �浹�� �� ����, %d��\\n", i, forcount - 1, blackMax + 1);
			px[Pcount] = i;
			py[Pcount] = forcount - 1;
			pz[Pcount] = whiteMax + 1;
			pa[Pcount] = 1;
		}
		Pcount++;
	}

	for (i = 0; i < 19; i++)
	{
		if (pz[i] < pz[i + 1])
		{
			result = i + 1;
		}
	}
	px[1] = px[result];
	py[1] = py[result];
	pz[1] = pz[result];
	pa[1] = pa[result];

	printf("������ ���� ���� ���� %d, %d��ǥ�̸� %d���̰� ", px[result], py[result], pz[result] + 1);

	if (pa[result] == 1)
	{
		printf("���� �浹�Դϴ�.\\n");
	}
	else if (pa[result] == 2)
	{
		printf("���� �鵹�Դϴ�.\\n");
	}
	else
	{
		printf("\\n");
	}
	return;
}

void crossSero(int map[19][19])
{
	int whiteNow, blackNow = 0;
	int whiteMax, blackMax = 1;
	int i, j, count = 0;

	printf("==========������ üũ\\n");

	for (j = 1; j < 20; j++)
	{
		int whiteNow = 0;
		int   blackNow = 0;
		int whiteMax = 0;
		int   blackMax = 0;
		int forcount = 0;

		for (i = 1; i < 20; i++)
		{
			if (map[i][j] == map[i - 1][j])
			{
				if (map[i][j] == WHITE)
				{
					whiteNow++;
					if (whiteNow > whiteMax)
					{
						forcount = j;
						whiteMax++;
					}
				}
				else if (map[i][j] == BLACK)
				{
					blackNow++;
					if (blackNow > blackMax)
					{
						forcount = j;
						blackMax++;
					}
				}
			}
			else
			{
				whiteNow = 0;
				blackNow = 0;
			}
		}
		if (whiteMax > blackMax)
		{
			printf("%d��° �� �鵹�� �� ����, %d��\\n", j, whiteMax + 1);
		}
		else if (blackMax > whiteMax)
		{
			printf("%d��° �� �鵹�� �� ����, %d��\\n", j, blackMax + 1);
		}
	}
	return;
}

void eight(int mao[19][19])
{
	printf("-----8�ù��� �˻�-----\\n");
	int whiteNow = 0;
	int blackNow = 0;
	int whiteMax = 0;
	int blackMax = 0;
	int i, j = 0;
	int garo, sero = 1;
	int count = 0;

	count = 19;

	for (i = 1; i < 20; i++)
	{
		garo = i;
		sero = 1;
		whiteNow = 0;
		blackNow = 0;
		whiteMax = 0;
		blackMax = 0;
		for (j = count; j > 0; j--)
		{
			if (map[garo][sero] == map[garo - 1][sero - 1])
			{
				if (map[garo][sero] == BLACK)
				{
					blackNow++;
					if (blackNow > blackMax)
					{
						blackMax++;
					}
				}
				else if (map[garo][sero] == WHITE)
				{
					whiteNow++;
					if (whiteNow > whiteMax)
					{
						whiteMax++;
					}
				}
			}
			garo++;
			sero++;
		}
		if (blackMax > whiteMax)
		{
			printf("%d��° ���� �浹�� �� ���� %d���Դϴ�.\\n", i, blackMax + 1);
		}
		else if (whiteMax > blackMax)
		{
			printf("%d��° ���� �鵹�� �� ���� %d���Դϴ�.\\n", i, whiteMax + 1);
		}
		count--;
	}
}

void two(int mao[19][19])
{
	printf("-----2�ù��� �˻�-----\\n");
	int whiteNow = 0;
	int blackNow = 0;
	int whiteMax = 0;
	int blackMax = 0;
	int i, j = 0;
	int garo, sero = 1;
	int count = 0;

	count = 19;

	for (i = 1; i < 20; i++)
	{
		garo = 1;
		sero = i;
		whiteNow = 0;
		blackNow = 0;
		whiteMax = 0;
		blackMax = 0;
		for (j = count; j > 0; j--)
		{
			if (map[garo][sero] == map[garo - 1][sero - 1])
			{
				if (map[garo][sero] == BLACK)
				{
					blackNow++;
					if (blackNow > blackMax)
					{
						blackMax++;
					}
				}
				else if (map[garo][sero] == WHITE)
				{
					whiteNow++;
					if (whiteNow > whiteMax)
					{
						whiteMax++;
					}
				}
			}
			garo++;
			sero++;
		}
		if (blackMax > whiteMax)
		{
			printf("%d��° ���� �浹�� �� ���� %d���Դϴ�.\\n", i, blackMax + 1);
		}
		else if (whiteMax > blackMax)
		{
			printf("%d��° ���� �鵹�� �� ���� %d���Դϴ�.\\n", i, whiteMax + 1);
		}
		count--;
	}
}

void ten(int mao[19][19])
{
	printf("-----10�ù��� �˻�-----\\n");
	int whiteNow = 0;
	int blackNow = 0;
	int whiteMax = 0;
	int blackMax = 0;
	int i, j = 0;
	int garo, sero = 1;
	int count = 0;

	count = 19;

	for (i = 19; i > 0; i--)
	{
		garo = 1;
		sero = i;
		whiteNow = 0;
		blackNow = 0;
		whiteMax = 0;
		blackMax = 0;
		for (j = count; j > 0; j--)
		{
			if (map[garo][sero] == map[garo + 1][sero - 1])
			{
				if (map[garo][sero] == BLACK)
				{
					blackNow++;
					if (blackNow > blackMax)
					{
						blackMax++;
					}
				}
				else if (map[garo][sero] == WHITE)
				{
					whiteNow++;
					if (whiteNow > whiteMax)
					{
						whiteMax++;
					}
				}
			}
			garo++;
			sero++;
		}
		if (blackMax > whiteMax)
		{
			printf("%d��° ���� �浹�� �� ���� %d���Դϴ�.\\n", i, blackMax + 1);
		}
		else if (whiteMax > blackMax)
		{
			printf("%d��° ���� �鵹�� �� ���� %d���Դϴ�.\\n", i, whiteMax + 1);
		}
		count--;
	}
}

void four(int mao[19][19])
{
	printf("-----4�ù��� �˻�-----\\n");
	int whiteNow = 0;
	int blackNow = 0;
	int whiteMax = 0;
	int blackMax = 0;
	int i, j = 0;
	int garo, sero = 1;
	int count = 0;

	count = 19;

	for (i = 0; i < 19; i++)
	{
		garo = i;
		sero = 19;
		whiteNow = 0;
		blackNow = 0;
		whiteMax = 0;
		blackMax = 0;
		for (j = count; j > 0; j--)
		{
			if (map[garo][sero] == map[garo + 1][sero - 1])
			{
				if (map[garo][sero] == BLACK)
				{
					blackNow++;
					if (blackNow > blackMax)
					{
						blackMax++;
					}
				}
				else if (map[garo][sero] == WHITE)
				{
					whiteNow++;
					if (whiteNow > whiteMax)
					{
						whiteMax++;
					}
				}
			}
			garo++;
			sero++;
		}
		if (blackMax > whiteMax)
		{
			printf("%d��° ���� �浹�� �� ���� %d���Դϴ�.\\n", i, blackMax + 1);
		}
		else if (whiteMax > blackMax)
		{
			printf("%d��° ���� �鵹�� �� ���� %d���Դϴ�.\\n", i, whiteMax + 1);
		}
		count--;
	}
}

int main()
{
	int i, j = 0;
	int countBlack, countWhite = 0;
	int turn = 1;
	int inputA, inputB = 0;

	while (1)
	{
		system("cls");

		countBlack = 0;
		countWhite = 0;

		for (i = 1; i < 20; i++)
		{
			for (j = 1; j < 20; j++)
			{
				if (map[i][j] == MAP)
				{
					printf("��");
				}
				else if (map[i][j] == BLACK)
				{
					printf("��");
					countBlack++;
				}
				else
				{
					printf("��");
					countWhite++;
				}
			}
			printf("\\n");
		}

		printf("�鵹 : %d\\t�浹 : %d\\n", countWhite, countBlack);

		////////////////////���⿡�� ���� �ִ°�
		crossGaro(map);
		crossSero(map);
		eight(map);
		two(map);
		ten(map);
		four(map);

		if (turn % 2 == 1)
		{
			printf("�鵹�� �����Դϴ� ");
		}
		else if (turn % 2 == 0)
		{
			printf("�浹�� �����Դϴ� ");
		}

		printf("���� ���� ���� : ");
		scanf("%d %d", &inputB, &inputA);




		if (inputA > 19 || inputA < 1 || inputB > 19 || inputB < 1)
		{
			printf("�̻��� ���� ���� ���� ���ÿ�.\\n");
			system("pause");
			continue;
		}

		if (map[inputA][inputB] != MAP)
		{
			printf("�̹� ���� �ֽ��ϴ�.\\n");
			system("pause");
			continue;
		}
		else
		{
			if (turn % 2 == 1)
			{
				map[inputA][inputB] = WHITE;
			}
			else if (turn % 2 == 0)
			{
				map[inputA][inputB] = BLACK;
			}
		}
		turn++;
	}
	return 0;
}