#include<stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdlib.h>
#include <time.h>

#define SIZE_RESOURCE_TYPE 5//ϵͳ�ṩ����Դ��������
#define SIZE_RESOURCR_NUMBER 120//ϵͳÿ����Դ���ṩ��
#define SIZE_MAX_REASOURCE_NEED 60//���������Դ������

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



int main()
{
	int n;
	printf("��������Ҫ���ɵĽ�����:");
	scanf("%d", &n);

    int process[n][5];

    int **process=(int**)malloc(sizeof(int)*n*SIZE_RESOURCE_TYPE);
    init(process,n);

}