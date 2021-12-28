#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdlib.h>
#include <time.h>

#define SIZE_RESOURCE_TYPE 5		 //系统提供的资源种类数量
#define SIZE_RESOURCR_NUMBER 120	 //系统每种资源的提供量
#define SIZE_PROCESS_NUMBER 10		 //系统提供的资源种类数量
#define SIZE_MAX_REASOURCE_NEED 60	 //进程最大资源需求量
#define MULTI_MAX_FIRST_ALLOCATE 0.7 //首次分配占所需资源的占比（最大值）
#define MULTI_MIN_FIRST_ALLOCATE 0.4 //首次分配占所需资源的占比（最小值）

void init(int process_resource_need[][SIZE_RESOURCE_TYPE], int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < SIZE_RESOURCE_TYPE; j++)
		{
			process_resource_need[i][j] = (rand() % SIZE_MAX_REASOURCE_NEED / 5 + 1) * 5;
		}
	}
}

void print_process(int process_resource_need[][SIZE_RESOURCE_TYPE], int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < SIZE_RESOURCE_TYPE; j++)
		{
			printf("%d\t", process_resource_need[i][j]);
		}
		printf("\n");
	}
}
void init_first_allocate(int process_resource_need[][SIZE_RESOURCE_TYPE], int process_resource_0[][SIZE_RESOURCE_TYPE], int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < SIZE_RESOURCE_TYPE; j++)
		{
			int a = (rand() % (int)(MULTI_MAX_FIRST_ALLOCATE * 100 - MULTI_MIN_FIRST_ALLOCATE * 100) + MULTI_MIN_FIRST_ALLOCATE * 100);
			process_resource_0[i][j] = (int)process_resource_need[i][j] * a / 100;
		}
	}
}

int main()
{
	int n = SIZE_PROCESS_NUMBER;
	// printf("请输入需要生成的进程数:");
	// scanf("%d", &n);

	int process_resource_need[SIZE_PROCESS_NUMBER][SIZE_RESOURCE_TYPE];
	int process_resource_0[SIZE_PROCESS_NUMBER][SIZE_RESOURCE_TYPE];

	srand((unsigned)time(NULL));
	init(process_resource_need, n);
	init_first_allocate(process_resource_need, process_resource_0, n);

	print_process(process_resource_need, n);
	printf("\n");
	print_process(process_resource_0, n);
}