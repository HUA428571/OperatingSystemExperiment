#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdlib.h>
#include <time.h>

#define SIZE_RESOURCE_TYPE 5//ϵͳ�ṩ����Դ��������
#define SIZE_RESOURCR_NUMBER 120//ϵͳÿ����Դ���ṩ��
#define SIZE_MAX_REASOURCE_NEED 60//���������Դ������

void init(int **process,int n)
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


void print_process(int **process,int n)
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
	int n;
	printf("��������Ҫ���ɵĽ�����:");
	scanf("%d", &n);

    int **process=(int**)malloc(sizeof(int)*n*SIZE_RESOURCE_TYPE);
    init(process,n);


}