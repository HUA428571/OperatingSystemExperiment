#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_PAGE_NUM 8 //最大页面号
#define ARRAY_LIST_LENGTH 20 //页面序列的数量

int t;		   //记录当前查找页面序号

int scan_page_position(int a, int page[])
{ //搜索当前页面之后，页面a在序列中最早出现的位置
	for (int i = t + 1; i < ARRAY_LIST_LENGTH; i++)
	{
		if (page[i] == a)
			return i;
	}
	return 99;
}

int scan_page_preposition(int a, int page[])
{ //搜索当前页面之前，页面a在序列中最后出现的位置
	for (int i = t - 1; i >= 0; i--)
	{
		if (page[i] == a)
			return i;
	}
	return -99;
}

int scan_block_position(int a, int block[], int BLOCK_SIZE)
{ //搜索页面a是否在物理块中,并返回位置
	for (int i = 0; i < BLOCK_SIZE; i++)
	{
		if (block[i] == a)
			return i;
	}
	return -1;
}

int max(int a[], int BLOCK_SIZE)
{ //返回数组a中最大元素的地址
	int temp = 0;
	for (int i = 1; i < BLOCK_SIZE; i++)
	{
		if (a[i] > a[temp])
			temp = i;
	}
	return temp;
}

int min(int a[], int BLOCK_SIZE)
{ //返回数组a中最小元素的地址
	int temp = 0;
	for (int i = 1; i < BLOCK_SIZE; i++)
	{
		if (a[i] < a[temp])
			temp = i;
	}
	return temp;
}

//最佳置换算法
int OPT(int BLOCK_SIZE, int page[])
{
	int block[BLOCK_SIZE];
	t = 0;
	for (int i = 0; i < BLOCK_SIZE; i++)
		block[i] = -1;
	printf("\n-----------------------OPT  物理块数=%d-----------------------\n", BLOCK_SIZE);
	int count = 0;	//缺页计数器
	int count2 = 0; //置换计数器
	while (t < ARRAY_LIST_LENGTH)
	{
		if (scan_block_position(page[t], block, BLOCK_SIZE) != -1)
		{
			printf("页面%d在物理块中,当前物理块为", page[t]); //在物理块中找到页面，无需置换
			for (int i = 0; i < BLOCK_SIZE; i++)
				printf("%d ", block[i]);
			printf("\n");
		}
		else
		{
			if (scan_block_position(-1, block, BLOCK_SIZE) != -1)
			{ //如果物理块中有空块，那么直接装入页面
				block[scan_block_position(-1, block, BLOCK_SIZE)] = page[t];
				count++;
				printf("装入页面%d,当前物理块为", page[t]);
				for (int i = 0; i < BLOCK_SIZE; i++)
					printf("%d ", block[i]);
				printf("\n");
			}
			else
			{
				int position[BLOCK_SIZE]; //置换算法，寻找未来最久未使用的页面，将其置换
				for (int i = 0; i < BLOCK_SIZE; i++)
					position[i] = scan_page_position(block[i], page);
				int temp = max(position, BLOCK_SIZE);
				printf("页面%d不在物理块中，将%d换出,", page[t], block[temp]);
				block[temp] = page[t];
				printf("当前物理块为");
				for (int i = 0; i < BLOCK_SIZE; i++)
					printf("%d ", block[i]);
				printf("\n");
				count++;
				count2++;
			}
		}
		t++;
	}
	printf("缺页次数为%d，缺页率为%.0f%%，置换率为%.0f%%\n", count, (float)count / ARRAY_LIST_LENGTH * 100, (float)count2 / ARRAY_LIST_LENGTH * 100);
	return count;
}

//先进先出置换算法
int FIFO(int BLOCK_SIZE, int page[])
{
	int block[BLOCK_SIZE];
	t = 0;
	for (int i = 0; i < BLOCK_SIZE; i++)
		block[i] = -1;
	printf("\n-----------------------FIFO  物理块数=%d-----------------------\n", BLOCK_SIZE);
	int temp = 0;	//数组代替队列，顺序置换
	int count = 0;	//缺页计数器
	int count2 = 0; //置换计数器
	while (t < ARRAY_LIST_LENGTH)
	{
		if (scan_block_position(page[t], block, BLOCK_SIZE) != -1)
		{
			printf("页面%d在物理块中,当前物理块为", page[t]); //在物理块中找到页面，无需置换
			for (int i = 0; i < BLOCK_SIZE; i++)
				printf("%d ", block[i]);
			printf("\n");
		}
		else
		{
			if (block[temp % BLOCK_SIZE] == -1)
			{
				block[temp % BLOCK_SIZE] = page[t];
				count++;
				temp++;
				printf("装入页面%d,当前物理块为", page[t]); //如果物理块中有空块，那么直接装入页面
				for (int i = 0; i < BLOCK_SIZE; i++)
					printf("%d ", block[i]);
				printf("\n");
			}
			else
			{
				printf("页面%d不在物理块中，将%d换出,", page[t], block[temp % BLOCK_SIZE]); //置换页面，将最早装入的页面置换
				block[temp % BLOCK_SIZE] = page[t];
				temp++;
				printf("当前物理块为");
				for (int i = 0; i < BLOCK_SIZE; i++)
					printf("%d ", block[i]);
				printf("\n");
				count++;
				count2++;
			}
		}
		t++;
	}
	printf("缺页次数为%d，缺页率为%.0f%%，置换率为%.0f%%\n", count, (float)count / ARRAY_LIST_LENGTH * 100, (float)count2 / ARRAY_LIST_LENGTH * 100);
	return count;
}

//最近最久未使用置换算法
int LRU(int BLOCK_SIZE, int page[])
{
	int block[BLOCK_SIZE];
	t = 0;
	for (int i = 0; i < BLOCK_SIZE; i++)
		block[i] = -1;
	printf("\n-----------------------LRU  物理块数=%d-----------------------\n", BLOCK_SIZE);
	int count = 0;	//缺页计数器
	int count2 = 0; //置换计数器
	while (t < ARRAY_LIST_LENGTH)
	{
		if (scan_block_position(page[t], block, BLOCK_SIZE) != -1)
		{
			printf("页面%d在物理块中,当前物理块为", page[t]); //在物理块中找到页面，无需置换
			for (int i = 0; i < BLOCK_SIZE; i++)
				printf("%d ", block[i]);
			printf("\n");
		}
		else
		{
			if (scan_block_position(-1, block, BLOCK_SIZE) != -1)
			{
				block[scan_block_position(-1, block, BLOCK_SIZE)] = page[t];
				count++;
				printf("装入页面%d,当前物理块为", page[t]); //如果物理块中有空块，那么直接装入页面
				for (int i = 0; i < BLOCK_SIZE; i++)
					printf("%d ", block[i]);
				printf("\n");
			}
			else
			{
				int position[BLOCK_SIZE]; //置换页面，寻找最近最久未使用的页面，将其置换
				for (int i = 0; i < BLOCK_SIZE; i++)
					position[i] = scan_page_preposition(block[i], page);
				int temp = min(position, BLOCK_SIZE);

				printf("页面%d不在物理块中，将%d换出,", page[t], block[temp]);
				block[temp] = page[t];
				printf("当前物理块为");
				for (int i = 0; i < BLOCK_SIZE; i++)
					printf("%d ", block[i]);
				printf("\n");
				count++;
				count2++;
			}
		}
		t++;
	}
	printf("缺页次数为%d，缺页率为%.0f%%，置换率为%.0f%%\n", count, (float)count / ARRAY_LIST_LENGTH * 100, (float)count2 / ARRAY_LIST_LENGTH * 100);
	return count;
}

//最少使用置换算法
int LFU(int BLOCK_SIZE, int page[])
{
	int block[BLOCK_SIZE];
	t = 0;
	for (int i = 0; i < BLOCK_SIZE; i++)
		block[i] = -1;
	printf("\n-----------------------LFU  物理块数=%d-----------------------\n", BLOCK_SIZE);
	int count = 0;		  //缺页计数器
	int count2 = 0;		  //置换计数器
	int usage[MAX_PAGE_NUM]; //最近使用次数计数器
	for (int i = 0; i < MAX_PAGE_NUM; i++)
		usage[i] = 0;
	while (t < ARRAY_LIST_LENGTH)
	{
		if (scan_block_position(page[t], block, BLOCK_SIZE) != -1)
		{
			printf("页面%d在物理块中,当前物理块为", page[t]); //在物理块中找到页面，无需置换
			for (int i = 0; i < BLOCK_SIZE; i++)
				printf("%d ", block[i]);
			printf("\n");
			usage[scan_block_position(page[t], block, BLOCK_SIZE)]++;
		}
		else
		{
			if (scan_block_position(-1, block, BLOCK_SIZE) != -1)
			{
				block[scan_block_position(-1, block, BLOCK_SIZE)] = page[t];
				usage[page[t]]++;
				count++;
				printf("装入页面%d,当前物理块为", page[t]); //如果物理块中有空块，那么直接装入页面
				for (int i = 0; i < BLOCK_SIZE; i++)
					printf("%d ", block[i]);
				printf("\n");
			}
			else
			{
				int num[BLOCK_SIZE]; //寻找最近使用次数最少的页面，将其置换
				for (int i = 0; i < BLOCK_SIZE; i++)
					num[i] = usage[block[i]];
				int temp = min(num, BLOCK_SIZE);

				printf("页面%d不在物理块中，将%d换出,", page[t], block[temp]);
				block[temp] = page[t];
				usage[page[t]]++;
				printf("当前物理块为");
				for (int i = 0; i < BLOCK_SIZE; i++)
					printf("%d ", block[i]);
				printf("\n");
				count++;
				count2++;
			}
		}
		t++;
	}
	printf("缺页次数为%d，缺页率为%.0f%%，置换率为%.0f%%\n", count, (float)count / ARRAY_LIST_LENGTH * 100, (float)count2 / ARRAY_LIST_LENGTH * 100);
	return count;
}

int draw(int point[], int ARRAY_LIST_LENGTH)
{ //绘制性能散点图
	char aa[ARRAY_LIST_LENGTH][28];
	for (int i = 2; i <= 8; i++)
		aa[ARRAY_LIST_LENGTH - point[i]][4 * (i - 1) - 1] = '*';
	printf("\n               性能散点图\n");
	printf(" 缺页次数\n");
	for (int i = 0; i < ARRAY_LIST_LENGTH; i++)
	{
		if (i <= ARRAY_LIST_LENGTH - 10)
			printf(" %d |", ARRAY_LIST_LENGTH - i);
		else
			printf("  %d |", ARRAY_LIST_LENGTH - i);
		for (int j = 0; j < 28; j++)
		{
			if (aa[i][j] == '*')
				printf("*");
			else
				printf(" ");
		}
		printf("\n");
	}
	printf("    ");
	for (int i = 0; i < 8; i++)
		printf("----");
	printf(" 物理块\n        ");
	for (int i = 2; i <= 8; i++)
		printf("%d   ", i);
	printf("\n");
}

void init(int list[ARRAY_LIST_LENGTH])
{
	srand((unsigned)time(NULL));
	for (int i = 0; i < ARRAY_LIST_LENGTH; i++)
	{
		list[i]=rand()%MAX_PAGE_NUM;
	}
	printf("生成了如下访问序列：\n");
	for (int i = 0; i < ARRAY_LIST_LENGTH; i++)
		printf("%d,", page[i]);
	printf("\n");
}

int main()
{
int list[ARRAY_LIST_LENGTH];
init(list);




	//模拟6种页面置换算法，每种算法从物理块大小2-8分别模拟，计算缺页率
	int lack_page_count[9]; //存储不同物理块的缺页次数，用于性能分析
	for (int i = 0; i < 9; i++)
		lack_page_count[i] = 0; //初始化

	for (int i = 2; i <= 8; i++)
		lack_page_count[i] = OPT(i, page);
	draw(lack_page_count, ARRAY_LIST_LENGTH);
	system("pause");

	for (int i = 2; i <= 8; i++)
		lack_page_count[i] = FIFO(i, page);
	draw(lack_page_count, ARRAY_LIST_LENGTH);
	system("pause");

	for (int i = 2; i <= 8; i++)
		lack_page_count[i] = LRU(i, page);
	draw(lack_page_count, ARRAY_LIST_LENGTH);
	system("pause");

	for (int i = 2; i <= 8; i++)
		lack_page_count[i] = LFU(i, page);
	draw(lack_page_count, ARRAY_LIST_LENGTH);
	system("pause");

	for (int i = 2; i <= 8; i++)
		lack_page_count[i] = CLOCK(i, page);
	draw(lack_page_count, ARRAY_LIST_LENGTH);
	system("pause");

	for (int i = 2; i <= 8; i++)
		lack_page_count[i] = CLOCK_advanced(i, page);
	draw(lack_page_count, ARRAY_LIST_LENGTH);
	system("pause");
}
