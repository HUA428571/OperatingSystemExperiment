#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//#define PRINT_DETAIL
#define MAX_PAGE_NUM 100		 //最大页面号
#define ARRAY_LIST_LENGTH 10000 //页面序列的数量
#define PHYSICAL_BLOCK_NUM 90

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
	int far = 0;			 //最长访问的时长的页号
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
	int early = 0;
	for (int i = 1; i < PHYSICAL_BLOCK_NUM; i++)
	{
		if (block_counter[early] < block_counter[i])
			early = i;
	}
	return early;
}
int find_less_frequent(int block_counter[])
{
	int frequent = 0;
	for (int i = 1; i < PHYSICAL_BLOCK_NUM; i++)
	{
		if (block_counter[frequent] > block_counter[i])
			frequent = i;
	}
	return frequent;
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

//最佳置换算法
void OPT(int list[ARRAY_LIST_LENGTH])
{
#ifdef PRINT_DETAIL
	printf("访问页面\t");
	for (int i = 0; i < PHYSICAL_BLOCK_NUM; i++)
	{
		printf("块%d\t", i);
	}
	printf("\n");
#endif

	int block[PHYSICAL_BLOCK_NUM];
	//初始化物理块
	for (int i = 0; i < PHYSICAL_BLOCK_NUM; i++)
		block[i] = -1;
	int exchange_counter = 0; //置换计数器
	for (int i = 0; i < ARRAY_LIST_LENGTH; i++)
	{
#ifdef PRINT_DETAIL
		printf("   %d\t\t", list[i]); //当前查找页面
#endif
		int block_exchange = scan_block(list[i], block);
		if (block_exchange == -1)
		{
			exchange_counter++;
			block_exchange = find_far_use(i, block, list);
			block[block_exchange] = list[i];
#ifdef PRINT_DETAIL
			print_block(block);
			printf("置换块%d\n", block_exchange);
#endif
		}
		else
		{
#ifdef PRINT_DETAIL
			print_block(block);
			printf("成功\n");
#endif
			block[block_exchange] = list[i];
		}
	}
	printf("缺页次数为%d，置换率为%.2f%%\n", exchange_counter, ((float)exchange_counter / ARRAY_LIST_LENGTH) * 100);
	return;
}

//先进先出置换算法
void FIFO(int list[ARRAY_LIST_LENGTH])
{
#ifdef PRINT_DETAIL
	printf("访问页面\t");
	for (int i = 0; i < PHYSICAL_BLOCK_NUM; i++)
	{
		printf("块%d\t", i);
	}
	printf("\n");
#endif

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
#ifdef PRINT_DETAIL
		printf("   %d\t\t", list[i]); //当前查找页面
#endif
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
#ifdef PRINT_DETAIL
			print_block(block);
			printf("置换块%d\n", block_exchange);
#endif
		}
		else
		{
			for (int i = 0; i < PHYSICAL_BLOCK_NUM; i++)
			{
				block_counter[i]++;
			}
			//block_counter[block_exchange] = 0;

#ifdef PRINT_DETAIL
			print_block(block);
			printf("成功\n");
#endif
			block[block_exchange] = list[i];
		}
	}
	printf("缺页次数为%d，置换率为%.2f%%\n", exchange_counter, ((float)exchange_counter / ARRAY_LIST_LENGTH) * 100);
	return;
}

//最近最久未使用置换算法
void LRU(int list[ARRAY_LIST_LENGTH])
{
#ifdef PRINT_DETAIL
	printf("访问页面\t");
	for (int i = 0; i < PHYSICAL_BLOCK_NUM; i++)
	{
		printf("块%d\t", i);
	}
	printf("\n");
#endif

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
#ifdef PRINT_DETAIL
		printf("   %d\t\t", list[i]); //当前查找页面
#endif
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
#ifdef PRINT_DETAIL
			print_block(block);
			printf("置换块%d\n", block_exchange);
#endif
		}
		else
		{
			for (int i = 0; i < PHYSICAL_BLOCK_NUM; i++)
			{
				block_counter[i]++;
			}
			block_counter[block_exchange] = 0;

#ifdef PRINT_DETAIL
			print_block(block);
			printf("成功\n");
#endif
			block[block_exchange] = list[i];
		}
	}
	printf("缺页次数为%d，置换率为%.2f%%\n", exchange_counter, ((float)exchange_counter / ARRAY_LIST_LENGTH) * 100);
	return;
}

//最少使用置换算法
void LFU(int list[ARRAY_LIST_LENGTH])
{
#ifdef PRINT_DETAIL
	printf("访问页面\t");
	for (int i = 0; i < PHYSICAL_BLOCK_NUM; i++)
	{
		printf("块%d\t", i);
	}
	printf("\n");
#endif

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
#ifdef PRINT_DETAIL
		printf("   %d\t\t", list[i]); //当前查找页面
#endif
		int block_exchange = scan_block(list[i], block);
		if (block_exchange == -1)
		{
			exchange_counter++;
			block_exchange = find_less_frequent(block_counter);
			for (int i = 0; i < PHYSICAL_BLOCK_NUM; i++)
			{
				block_counter[i] = 0;
			}
			block_counter[block_exchange]++;

			block[block_exchange] = list[i];
#ifdef PRINT_DETAIL
			print_block(block);
			printf("置换块%d\n", block_exchange);
#endif
		}
		else
		{
			block_counter[block_exchange]++;

#ifdef PRINT_DETAIL
			print_block(block);
			printf("成功\n");
#endif
			block[block_exchange] = list[i];
		}
	}
	printf("缺页次数为%d，置换率为%.2f%%\n", exchange_counter, ((float)exchange_counter / ARRAY_LIST_LENGTH) * 100);
	return;
}

void init(int list[ARRAY_LIST_LENGTH])
{
	srand((unsigned)time(NULL));
	for (int i = 0; i < ARRAY_LIST_LENGTH; i++)
	{
		list[i] = rand() % MAX_PAGE_NUM;
	}
#ifdef PRINT_DETAIL
	printf("生成了如下访问序列：\n");
	for (int i = 0; i < ARRAY_LIST_LENGTH; i++)
		printf("%d,", list[i]);
	printf("\n\n");
#endif // PRINT_DETAIL
}

int main()
{
	int list[ARRAY_LIST_LENGTH];
	init(list);

	printf("OPT 最佳置换算法\n");
	printf("-----------------------------------------------------------------------\n");
	OPT(list);
	printf("\n");

	printf("FIFO 先进先出置换算法\n");
	printf("-----------------------------------------------------------------------\n");
	FIFO(list);
	printf("\n");

	printf("LRU 最近最久未使用置换算法\n");
	printf("-----------------------------------------------------------------------\n");
	LRU(list);
	printf("\n");

	printf("LFU 最少使用置换算法\n");
	printf("-----------------------------------------------------------------------\n");
	LFU(list);
	printf("\n");
}
