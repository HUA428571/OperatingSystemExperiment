#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdlib.h>
#include <time.h>

#define SIZE_RESOURCE_TYPE 5//ϵͳ�ṩ����Դ��������
#define SIZE_RESOURCR_NUMBER 120//ϵͳÿ����Դ���ṩ��
#define SIZE_PROCESS_NUMBER 10//ϵͳ�ṩ����Դ��������
#define SIZE_MAX_REASOURCE_NEED 60//���������Դ������
#define MULTI_MAX_FIRST_ALLOCATE 0.7//�״η���ռ������Դ��ռ�ȣ����ֵ��
#define MULTI_MIN_FIRST_ALLOCATE 0.4//�״η���ռ������Դ��ռ�ȣ���Сֵ��


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
void init_first_allocate(int process[][SIZE_RESOURCE_TYPE],int n)
{


}

int main()
{
	int n=SIZE_PROCESS_NUMBER;
	// printf("��������Ҫ���ɵĽ�����:");
	// scanf("%d", &n);

    int process[SIZE_PROCESS_NUMBER][SIZE_RESOURCE_TYPE];

    init(process,n);

    print_process(process, n);

}