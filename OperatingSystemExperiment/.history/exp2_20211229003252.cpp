#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define SIZE_RESOURCE_TYPE 5		 //ϵͳ�ṩ����Դ��������
#define SIZE_RESOURCR_NUMBER 120	 //ϵͳÿ����Դ���ṩ��
#define SIZE_PROCESS_NUMBER 10		 //ϵͳ�ṩ����Դ��������
#define SIZE_MAX_REASOURCE_NEED 60	 //���������Դ������
#define MULTI_MAX_FIRST_ALLOCATE 0.7 //�״η���ռ������Դ��ռ�ȣ����ֵ��
#define MULTI_MIN_FIRST_ALLOCATE 0.4 //�״η���ռ������Դ��ռ�ȣ���Сֵ��

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

int main()
{
	int n = SIZE_PROCESS_NUMBER;
	// printf("��������Ҫ���ɵĽ�����:");
	// scanf("%d", &n);

	int process_resource_need[SIZE_PROCESS_NUMBER][SIZE_RESOURCE_TYPE];
	int process_resource_0[SIZE_PROCESS_NUMBER][SIZE_RESOURCE_TYPE];
	bool process_finished[SIZE_PROCESS_NUMBER];
	memset(process_finished,false,SIZE_PROCESS_NUMBER);

	srand((unsigned)time(NULL));
	init(process_resource_need, n);
	init_first_allocate(process_resource_need, process_resource_0, n);

	print_process(process_resource_need, n);
	printf("\n");
	print_process(process_resource_0, n);
}