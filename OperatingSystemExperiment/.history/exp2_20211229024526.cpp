#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define SIZE_RESOURCE_TYPE 5		 //ϵͳ�ṩ����Դ��������
#define SIZE_RESOURCR_NUMBER 360	 //ϵͳÿ����Դ���ṩ��
#define SIZE_PROCESS_NUMBER 10		 //ϵͳ�ṩ����Դ��������
#define SIZE_MAX_REASOURCE_NEED 60	 //���������Դ������
#define MULTI_MAX_FIRST_ALLOCATE 0.7 //�״η���ռ������Դ��ռ�ȣ����ֵ��
#define MULTI_MIN_FIRST_ALLOCATE 0.4 //�״η���ռ������Դ��ռ�ȣ���Сֵ��

void init(int process_resource_need[][SIZE_RESOURCE_TYPE],
		  int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < SIZE_RESOURCE_TYPE; j++)
		{
			process_resource_need[i][j] = (rand() % SIZE_MAX_REASOURCE_NEED / 5 + 1) * 5;
		}
	}
}
void init_first_allocate(int process_resource_need[][SIZE_RESOURCE_TYPE],
						 int process_resource_0[][SIZE_RESOURCE_TYPE],
						 int n)
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
int init_system_resource_left(int process_resource_need[][SIZE_RESOURCE_TYPE],
							  int system_resource_left[SIZE_RESOURCE_TYPE],
							  int n)
{
	for (int i = 0; i < SIZE_PROCESS_NUMBER; i++)
	{
		for (int j = 0; j < SIZE_RESOURCE_TYPE; j++)
		{
			system_resource_left[j] -= process_resource_need[i][j];
		}
	}
	for (int i = 0; i < SIZE_RESOURCE_TYPE; i++)
	{
		if (system_resource_left[i] <= 0)
			return -1; //��ǰ������ɵĲ���������
	}
	return 1;
}

void print_process(int process_resource_need[][SIZE_RESOURCE_TYPE],
				   int n)
{
	printf("-------------------------------------------------\n");
	printf("���̺�\t");
	for (int i = 0; i < SIZE_RESOURCE_TYPE; i++)
	{
		printf("��Դ%c\t", i + 65);
	}
	printf("\n");
	for (int i = 0; i < n; i++)
	{
		printf("  %d\t", i + 1);
		for (int j = 0; j < SIZE_RESOURCE_TYPE; j++)
		{
			printf(" %d\t", process_resource_need[i][j]);
		}
		printf("\n");
	}
	printf("-------------------------------------------------\n");
}

void check(int process_resource_need[][SIZE_RESOURCE_TYPE],
		   int process_resource_0[][SIZE_RESOURCE_TYPE],
		   int system_resource_left[SIZE_RESOURCE_TYPE],
		   bool process_finished[SIZE_PROCESS_NUMBER],
		   int n)
{
	int available_next = 0;
	bool flag_available = true;
	bool process_is_available_next[SIZE_PROCESS_NUMBER];
	int finished = 0;
	for (int i = 0; i < SIZE_PROCESS_NUMBER; i++)
	{
		if (process_finished[i] == false)
		{
			for (int j = 0; j < SIZE_RESOURCE_TYPE; j++)
			{
				if ((process_resource_need[i][j] - process_resource_0[i][j]) > system_resource_left[j])
				{
					flag_available = false;
					break;
				}
			}
		}
		if (flag_available)
		{
			process_is_available_next[i] = true;
			available_next++;
		}
	}
	if (available_next > 0)
	{
		printf("��ǰ��Դ�������ִ�У���һ������ִ�еĽ����У�\n");
		printf("-------------------------------------------------\n");
		printf("���̺�\t");
		for (int i = 0; i < SIZE_RESOURCE_TYPE; i++)
		{
			printf("��Դ%c\t", i + 65);
		}
		printf("\n");
		for (int i = 0; i < SIZE_PROCESS_NUMBER; i++)
		{
			if (process_is_available_next[i] == true)
			{
				printf("  %d\t", i + 1);
				for (int j = 0; j < SIZE_RESOURCE_TYPE; j++)
				{
					printf(" %d\t", process_resource_need[i][j] - process_resource_0[i][j]);
				}
				printf("\n");
			}
		}
		printf("-------------------------------------------------\n");
	}
	else
	{
		printf("��ǰ��Դ���䲻��ȫ���������˳���\n");
		return;
	}
}

int main()
{
	int n = SIZE_PROCESS_NUMBER;

	int process_resource_need[SIZE_PROCESS_NUMBER][SIZE_RESOURCE_TYPE]; //ÿ�����̵���Դ������
	int process_resource_0[SIZE_PROCESS_NUMBER][SIZE_RESOURCE_TYPE];	//ÿ�������Ѿ��������Դ��
	int system_resource_left[SIZE_RESOURCE_TYPE];						//ϵͳ��ʣ�����Դ��
	for (int i = 0; i < SIZE_RESOURCE_TYPE; i++)
	{
		system_resource_left[i] = SIZE_RESOURCR_NUMBER;
	}
	//memset(system_resource_left,SIZE_RESOURCR_NUMBER,SIZE_RESOURCE_TYPE);
	bool process_finished[SIZE_PROCESS_NUMBER];
	memset(process_finished, false, SIZE_PROCESS_NUMBER);

	srand((unsigned)time(NULL));
	while (1)
	{
		init(process_resource_need, n);
		init_first_allocate(process_resource_need, process_resource_0, n);
		if (init_system_resource_left(process_resource_need, system_resource_left, n) > 0)
			break;
		for (int i = 0; i < SIZE_RESOURCE_TYPE; i++)
		{
			system_resource_left[i] = SIZE_RESOURCR_NUMBER;
		}
		//memset(system_resource_left, SIZE_RESOURCR_NUMBER, SIZE_RESOURCE_TYPE);
	}
	printf("�Զ�����%d�����̣�����������Դ�����£�", SIZE_PROCESS_NUMBER);
	print_process(process_resource_need, n);
	printf("\n");

	printf("���Ѿ��������Դ�����£�");
	print_process(process_resource_0, n);
	printf("\n");

	printf("ϵͳʣ����Դ��\n");
	printf("-------------------------------------------------\n");

	for (int i = 0; i < SIZE_RESOURCE_TYPE; i++)
	{
		printf("��Դ%c\t", i + 65);
	}
	printf("\n");
	for (int i = 0; i < SIZE_RESOURCE_TYPE; i++)
	{
		printf("%d\t", system_resource_left[i]);
	}
	printf("\n");
	printf("-------------------------------------------------\n");
	printf("\n");

	check(process_resource_need, process_resource_0, system_resource_left, process_finished, n);
}