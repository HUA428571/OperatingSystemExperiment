#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdlib.h>
#include <time.h>

#define SIZE_RESOURCE_TYPE 5//系统提供的资源种类数量
#define SIZE_RESOURCR_NUMBER 120//系统每种资源的提供量
#define SIZE_PROCESS_NUMBER 10//系统提供的资源种类数量
#define SIZE_MAX_REASOURCE_NEED 60//进程最大资源需求量

void init(int process[][SIZE_RESOURCE_TYPE],int n)
{
    srand((unsigned)time(NULL));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < SIZE_RESOURCE_TYPE; j++)
        {
            process[i][j] = (rand() % SIZE_MAX_REASOURCE_NEED / 5 + 1) * 5;
        }
    }
}


void print_process(int process[][SIZE_RESOURCE_TYPE],int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < SIZE_RESOURCE_TYPE; j++)
        {
            printf("%d\t",process[i][j]);
        }
        printf("\n");
    }
    
}

int main()
{
	int n=SIZE_PROCESS_NUMBER;
	// printf("请输入需要生成的进程数:");
	// scanf("%d", &n);

    int process[SIZE_PROCESS_NUMBER][SIZE_RESOURCE_TYPE];

    init(process,n);


}