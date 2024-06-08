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
	int x, y = 0; // 얘를 왜 썼더라...

	int Pcount = 0;
	int px[19] = { 0 };
	int py[19] = { 0 };
	int pz[19] = { 0 };
	int pa[19] = { 0 };
	int cal = 0;
	int result = 0;

	printf("============가로줄 체크\\n");

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
			printf("%d번째 줄 %d칸 백돌이 더 많고, %d개\\n", i, forcount - 1, whiteMax + 1);
			px[Pcount] = i;
			py[Pcount] = forcount - 1;
			pz[Pcount] = whiteMax + 1;
			pa[Pcount] = 2;
		}
		else if (blackMax > whiteMax)
		{
			printf("%d번째 줄 %d칸 흑돌이 더 많고, %d개\\n", i, forcount - 1, blackMax + 1);
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

	printf("가로줄 가장 많은 곳은 %d, %d좌표이며 %d개이고 ", px[result], py[result], pz[result] + 1);

	if (pa[result] == 1)
	{
		printf("돌은 흑돌입니다.\\n");
	}
	else if (pa[result] == 2)
	{
		printf("돌은 백돌입니다.\\n");
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

	printf("==========세로줄 체크\\n");

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
			printf("%d번째 줄 백돌이 더 많고, %d개\\n", j, whiteMax + 1);
		}
		else if (blackMax > whiteMax)
		{
			printf("%d번째 줄 백돌이 더 많고, %d개\\n", j, blackMax + 1);
		}
	}
	return;
}

void eight(int mao[19][19])
{
	printf("-----8시방향 검사-----\\n");
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
			printf("%d번째 줄은 흑돌이 더 많고 %d개입니다.\\n", i, blackMax + 1);
		}
		else if (whiteMax > blackMax)
		{
			printf("%d번째 줄은 백돌이 더 많고 %d개입니다.\\n", i, whiteMax + 1);
		}
		count--;
	}
}

void two(int mao[19][19])
{
	printf("-----2시방향 검사-----\\n");
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
			printf("%d번째 줄은 흑돌이 더 많고 %d개입니다.\\n", i, blackMax + 1);
		}
		else if (whiteMax > blackMax)
		{
			printf("%d번째 줄은 백돌이 더 많고 %d개입니다.\\n", i, whiteMax + 1);
		}
		count--;
	}
}

void ten(int mao[19][19])
{
	printf("-----10시방향 검사-----\\n");
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
			printf("%d번째 줄은 흑돌이 더 많고 %d개입니다.\\n", i, blackMax + 1);
		}
		else if (whiteMax > blackMax)
		{
			printf("%d번째 줄은 백돌이 더 많고 %d개입니다.\\n", i, whiteMax + 1);
		}
		count--;
	}
}

void four(int mao[19][19])
{
	printf("-----4시방향 검사-----\\n");
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
			printf("%d번째 줄은 흑돌이 더 많고 %d개입니다.\\n", i, blackMax + 1);
		}
		else if (whiteMax > blackMax)
		{
			printf("%d번째 줄은 백돌이 더 많고 %d개입니다.\\n", i, whiteMax + 1);
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
					printf("┼");
				}
				else if (map[i][j] == BLACK)
				{
					printf("●");
					countBlack++;
				}
				else
				{
					printf("○");
					countWhite++;
				}
			}
			printf("\\n");
		}

		printf("백돌 : %d\\t흑돌 : %d\\n", countWhite, countBlack);

		////////////////////여기에요 판정 넣는거
		crossGaro(map);
		crossSero(map);
		eight(map);
		two(map);
		ten(map);
		four(map);

		if (turn % 2 == 1)
		{
			printf("백돌의 차례입니다 ");
		}
		else if (turn % 2 == 0)
		{
			printf("흑돌의 차례입니다 ");
		}

		printf("돌을 놓을 차리 : ");
		scanf("%d %d", &inputB, &inputA);




		if (inputA > 19 || inputA < 1 || inputB > 19 || inputB < 1)
		{
			printf("이상한 곳에 돌을 놓지 마시오.\\n");
			system("pause");
			continue;
		}

		if (map[inputA][inputB] != MAP)
		{
			printf("이미 돌이 있습니다.\\n");
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