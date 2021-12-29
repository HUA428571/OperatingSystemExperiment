#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_PAGE_NUM 10		 //最大页面号
#define ARRAY_LIST_LENGTH 20 //页面序列的数量
#define PHYSICAL_BLOCK_NUM 5

int t; //记录当前查找页面序号

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

//扫描物理块，若有则返回位置，否则-1
int scan_block(int find, int block[])
{
	for (int i = 0; i < PHYSICAL_BLOCK_NUM; i++)
	{
		if (block[i] == -1)
		{
			block[i] = find;
			return i;
		}
		if (block[i] == find)
			return i;
	}
	return -1;
}
int find_far_use(int find_now, int block[], int list[])
{
	int far_counter = 0;	 //最长访问的时长
	int far_counter_now = 0; //当前计算的最长访问的时长
	int far = -1;			 //最长访问的时长的页号
	for (int i = 0; i < PHYSICAL_BLOCK_NUM; i++)
	{
		far_counter_now = 0;
		for (int j = find_now + 1; j < ARRAY_LIST_LENGTH; j++)
		{
			if (block[i] != list[j])
				far_counter_now++;
			else
				break;
		}
		if (far_counter_now > far_counter)
		{
			far_counter = far_counter_now;
			far = i;
		}
	}
	return far;
}
int find_early(int block_counter[])
{
	int small = 0;
	for (int i = 1; i < PHYSICAL_BLOCK_NUM; i++)
	{
		if (block_counter[small] < block_counter[i])
			small = i;
	}
	return small;
}

void print_block(int block[])
{
	for (int i = 0; i < PHYSICAL_BLOCK_NUM; i++)
	{
		if (block[i] == -1)
		{
			printf("N/A\t");
		}
		else
		{
			printf(" %d\t", block[i]);
		}
	}
}

//int max(int a[], int PHYSICAL_BLOCK_NUM)
//{ //返回数组a中最大元素的地址
//	int temp = 0;
//	for (int i = 1; i < PHYSICAL_BLOCK_NUM; i++)
//	{
//		if (a[i] > a[temp])
//			temp = i;
//	}
//	return temp;
//}
//
//int min(int a[], int PHYSICAL_BLOCK_NUM)
//{ //返回数组a中最小元素的地址
//	int temp = 0;
//	for (int i = 1; i < PHYSICAL_BLOCK_NUM; i++)
//	{
//		if (a[i] < a[temp])
//			temp = i;
//	}
//	return temp;
//}

//最佳置换算法
void OPT(int list[ARRAY_LIST_LENGTH])
{
	printf("访问页面\t");
	for (int i = 0; i < PHYSICAL_BLOCK_NUM; i++)
	{
		printf("块%d\t", i);
	}
	printf("\n");

	int block[PHYSICAL_BLOCK_NUM];
	//初始化物理块
	for (int i = 0; i < PHYSICAL_BLOCK_NUM; i++)
		block[i] = -1;
	int exchange_counter = 0; //置换计数器
	for (int i = 0; i < ARRAY_LIST_LENGTH; i++)
	{
		printf("   %d\t\t", list[i]); //当前查找页面
		int block_exchange = scan_block(list[i], block);
		if (block_exchange == -1)
		{
			exchange_counter++;
			block_exchange = find_far_use(i, block, list);
			block[block_exchange] = list[i];
			print_block(block);
			printf("置换块%d\n", block_exchange);
		}
		else
		{
			print_block(block);
			block[block_exchange] = list[i];
			printf("成功\n");
		}
		printf(" ");
	}
	printf("缺页次数为%d，置换率为%.0f%%\n", exchange_counter, ((float)exchange_counter / ARRAY_LIST_LENGTH) * 100);
	return;
}

//先进先出置换算法
void OPT(int list[ARRAY_LIST_LENGTH])
{
	printf("访问页面\t");
	for (int i = 0; i < PHYSICAL_BLOCK_NUM; i++)
	{
		printf("块%d\t", i);
	}
	printf("\n");

	int block[PHYSICAL_BLOCK_NUM];
	int block_counter[PHYSICAL_BLOCK_NUM];

	//初始化物理块
	for (int i = 0; i < PHYSICAL_BLOCK_NUM; i++)
	{
		block[i] = -1;
		block_counter[i] = 0;
	}

	int exchange_counter = 0; //置换计数器
	for (int i = 0; i < ARRAY_LIST_LENGTH; i++)
	{
		printf("   %d\t\t", list[i]); //当前查找页面
		int block_exchange = scan_block(list[i], block);
		if (block_exchange == -1)
		{
			exchange_counter++;
			block_exchange = find_early(block_counter);
			for (int i = 0; i < PHYSICAL_BLOCK_NUM; i++)
			{
				block_counter[i]++;
			}
			block_counter[block_exchange] = 0;

			block[block_exchange] = list[i];
			print_block(block);
			printf("置换块%d\n", block_exchange);
		}
		else
		{
			for (int i = 0; i < PHYSICAL_BLOCK_NUM; i++)
			{
				block_counter[i]++;
			}
			block_counter[block_exchange] = 0;

			print_block(block);
			block[block_exchange] = list[i];
			printf("成功\n");
		}
		printf(" ");
	}
	printf("缺页次数为%d，置换率为%.0f%%\n", exchange_counter, ((float)exchange_counter / ARRAY_LIST_LENGTH) * 100);
	return;
}

//int FIFO(int PHYSICAL_BLOCK_NUM, int page[])
//{
//	int block[PHYSICAL_BLOCK_NUM];
//	t = 0;
//	for (int i = 0; i < PHYSICAL_BLOCK_NUM; i++)
//		block[i] = -1;
//	printf("\n-----------------------FIFO  物理块数=%d-----------------------\n", PHYSICAL_BLOCK_NUM);
//	int temp = 0;	//数组代替队列，顺序置换
//	int count = 0;	//缺页计数器
//	int exchange_counter = 0; //置换计数器
//	while (t < ARRAY_LIST_LENGTH)
//	{
//		if (scan_block_position(page[t], block, PHYSICAL_BLOCK_NUM) != -1)
//		{
//			printf("页面%d在物理块中,当前物理块为", page[t]); //在物理块中找到页面，无需置换
//			for (int i = 0; i < PHYSICAL_BLOCK_NUM; i++)
//				printf("%d ", block[i]);
//			printf("\n");
//		}
//		else
//		{
//			if (block[temp % PHYSICAL_BLOCK_NUM] == -1)
//			{
//				block[temp % PHYSICAL_BLOCK_NUM] = page[t];
//				count++;
//				temp++;
//				printf("装入页面%d,当前物理块为", page[t]); //如果物理块中有空块，那么直接装入页面
//				for (int i = 0; i < PHYSICAL_BLOCK_NUM; i++)
//					printf("%d ", block[i]);
//				printf("\n");
//			}
//			else
//			{
//				printf("页面%d不在物理块中，将%d换出,", page[t], block[temp % PHYSICAL_BLOCK_NUM]); //置换页面，将最早装入的页面置换
//				block[temp % PHYSICAL_BLOCK_NUM] = page[t];
//				temp++;
//				printf("当前物理块为");
//				for (int i = 0; i < PHYSICAL_BLOCK_NUM; i++)
//					printf("%d ", block[i]);
//				printf("\n");
//				count++;
//				count2++;
//			}
//		}
//		t++;
//	}
//	printf("缺页次数为%d，缺页率为%.0f%%，置换率为%.0f%%\n", count, (float)count / ARRAY_LIST_LENGTH * 100, (float)count2 / ARRAY_LIST_LENGTH * 100);
//	return count;
//}
//
////最近最久未使用置换算法
//int LRU(int PHYSICAL_BLOCK_NUM, int page[])
//{
//	int block[PHYSICAL_BLOCK_NUM];
//	t = 0;
//	for (int i = 0; i < PHYSICAL_BLOCK_NUM; i++)
//		block[i] = -1;
//	printf("\n-----------------------LRU  物理块数=%d-----------------------\n", PHYSICAL_BLOCK_NUM);
//	int count = 0;	//缺页计数器
//	int exchange_counter = 0; //置换计数器
//	while (t < ARRAY_LIST_LENGTH)
//	{
//		if (scan_block_position(page[t], block, PHYSICAL_BLOCK_NUM) != -1)
//		{
//			printf("页面%d在物理块中,当前物理块为", page[t]); //在物理块中找到页面，无需置换
//			for (int i = 0; i < PHYSICAL_BLOCK_NUM; i++)
//				printf("%d ", block[i]);
//			printf("\n");
//		}
//		else
//		{
//			if (scan_block_position(-1, block, PHYSICAL_BLOCK_NUM) != -1)
//			{
//				block[scan_block_position(-1, block, PHYSICAL_BLOCK_NUM)] = page[t];
//				count++;
//				printf("装入页面%d,当前物理块为", page[t]); //如果物理块中有空块，那么直接装入页面
//				for (int i = 0; i < PHYSICAL_BLOCK_NUM; i++)
//					printf("%d ", block[i]);
//				printf("\n");
//			}
//			else
//			{
//				int position[PHYSICAL_BLOCK_NUM]; //置换页面，寻找最近最久未使用的页面，将其置换
//				for (int i = 0; i < PHYSICAL_BLOCK_NUM; i++)
//					position[i] = scan_page_preposition(block[i], page);
//				int temp = min(position, PHYSICAL_BLOCK_NUM);
//
//				printf("页面%d不在物理块中，将%d换出,", page[t], block[temp]);
//				block[temp] = page[t];
//				printf("当前物理块为");
//				for (int i = 0; i < PHYSICAL_BLOCK_NUM; i++)
//					printf("%d ", block[i]);
//				printf("\n");
//				count++;
//				count2++;
//			}
//		}
//		t++;
//	}
//	printf("缺页次数为%d，缺页率为%.0f%%，置换率为%.0f%%\n", count, (float)count / ARRAY_LIST_LENGTH * 100, (float)count2 / ARRAY_LIST_LENGTH * 100);
//	return count;
//}
//
////最少使用置换算法
//int LFU(int PHYSICAL_BLOCK_NUM, int page[])
//{
//	int block[PHYSICAL_BLOCK_NUM];
//	t = 0;
//	for (int i = 0; i < PHYSICAL_BLOCK_NUM; i++)
//		block[i] = -1;
//	printf("\n-----------------------LFU  物理块数=%d-----------------------\n", PHYSICAL_BLOCK_NUM);
//	int count = 0;		  //缺页计数器
//	int exchange_counter = 0;		  //置换计数器
//	int usage[MAX_PAGE_NUM]; //最近使用次数计数器
//	for (int i = 0; i < MAX_PAGE_NUM; i++)
//		usage[i] = 0;
//	while (t < ARRAY_LIST_LENGTH)
//	{
//		if (scan_block_position(page[t], block, PHYSICAL_BLOCK_NUM) != -1)
//		{
//			printf("页面%d在物理块中,当前物理块为", page[t]); //在物理块中找到页面，无需置换
//			for (int i = 0; i < PHYSICAL_BLOCK_NUM; i++)
//				printf("%d ", block[i]);
//			printf("\n");
//			usage[scan_block_position(page[t], block, PHYSICAL_BLOCK_NUM)]++;
//		}
//		else
//		{
//			if (scan_block_position(-1, block, PHYSICAL_BLOCK_NUM) != -1)
//			{
//				block[scan_block_position(-1, block, PHYSICAL_BLOCK_NUM)] = page[t];
//				usage[page[t]]++;
//				count++;
//				printf("装入页面%d,当前物理块为", page[t]); //如果物理块中有空块，那么直接装入页面
//				for (int i = 0; i < PHYSICAL_BLOCK_NUM; i++)
//					printf("%d ", block[i]);
//				printf("\n");
//			}
//			else
//			{
//				int num[PHYSICAL_BLOCK_NUM]; //寻找最近使用次数最少的页面，将其置换
//				for (int i = 0; i < PHYSICAL_BLOCK_NUM; i++)
//					num[i] = usage[block[i]];
//				int temp = min(num, PHYSICAL_BLOCK_NUM);
//
//				printf("页面%d不在物理块中，将%d换出,", page[t], block[temp]);
//				block[temp] = page[t];
//				usage[page[t]]++;
//				printf("当前物理块为");
//				for (int i = 0; i < PHYSICAL_BLOCK_NUM; i++)
//					printf("%d ", block[i]);
//				printf("\n");
//				count++;
//				count2++;
//			}
//		}
//		t++;
//	}
//	printf("缺页次数为%d，缺页率为%.0f%%，置换率为%.0f%%\n", count, (float)count / ARRAY_LIST_LENGTH * 100, (float)count2 / ARRAY_LIST_LENGTH * 100);
//	return count;
//}
//
//int draw(int point[], int ARRAY_LIST_LENGTH)
//{ //绘制性能散点图
//	char aa[ARRAY_LIST_LENGTH][28];
//	for (int i = 2; i <= 8; i++)
//		aa[ARRAY_LIST_LENGTH - point[i]][4 * (i - 1) - 1] = '*';
//	printf("\n               性能散点图\n");
//	printf(" 缺页次数\n");
//	for (int i = 0; i < ARRAY_LIST_LENGTH; i++)
//	{
//		if (i <= ARRAY_LIST_LENGTH - 10)
//			printf(" %d |", ARRAY_LIST_LENGTH - i);
//		else
//			printf("  %d |", ARRAY_LIST_LENGTH - i);
//		for (int j = 0; j < 28; j++)
//		{
//			if (aa[i][j] == '*')
//				printf("*");
//			else
//				printf(" ");
//		}
//		printf("\n");
//	}
//	printf("    ");
//	for (int i = 0; i < 8; i++)
//		printf("----");
//	printf(" 物理块\n        ");
//	for (int i = 2; i <= 8; i++)
//		printf("%d   ", i);
//	printf("\n");
//}

void init(int list[ARRAY_LIST_LENGTH])
{
	srand((unsigned)time(NULL));
	for (int i = 0; i < ARRAY_LIST_LENGTH; i++)
	{
		list[i] = rand() % MAX_PAGE_NUM;
	}
	printf("生成了如下访问序列：\n");
	for (int i = 0; i < ARRAY_LIST_LENGTH; i++)
		printf("%d,", list[i]);
	printf("\n");
}

int main()
{
	int list[ARRAY_LIST_LENGTH];
	init(list);

	OPT(list);



	////模拟6种页面置换算法，每种算法从物理块大小2-8分别模拟，计算缺页率
	//int lack_page_count[9]; //存储不同物理块的缺页次数，用于性能分析
	//for (int i = 0; i < 9; i++)
	//	lack_page_count[i] = 0; //初始化

	//for (int i = 2; i <= 8; i++)
	//	lack_page_count[i] = OPT(i, page);
	//draw(lack_page_count, ARRAY_LIST_LENGTH);
	//system("pause");

	//for (int i = 2; i <= 8; i++)
	//	lack_page_count[i] = FIFO(i, page);
	//draw(lack_page_count, ARRAY_LIST_LENGTH);
	//system("pause");

	//for (int i = 2; i <= 8; i++)
	//	lack_page_count[i] = LRU(i, page);
	//draw(lack_page_count, ARRAY_LIST_LENGTH);
	//system("pause");

	//for (int i = 2; i <= 8; i++)
	//	lack_page_count[i] = LFU(i, page);
	//draw(lack_page_count, ARRAY_LIST_LENGTH);
	//system("pause");

	//for (int i = 2; i <= 8; i++)
	//	lack_page_count[i] = CLOCK(i, page);
	//draw(lack_page_count, ARRAY_LIST_LENGTH);
	//system("pause");

	//for (int i = 2; i <= 8; i++)
	//	lack_page_count[i] = CLOCK_advanced(i, page);
	//draw(lack_page_count, ARRAY_LIST_LENGTH);
	//system("pause");
}
