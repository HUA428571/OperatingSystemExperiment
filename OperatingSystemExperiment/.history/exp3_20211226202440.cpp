#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdlib.h>
#include <time.h>
#define TIME_SIZE 5			//ʱ��Ƭ��С
#define MAX_TIME_USE 120	//���ҵ����ʱ��
#define MAX_TIME_ARRIVE 240 //���ҵ��ʼʱ��
#define MANE_SIZE 127
#define max 50

struct PCB
{
	int number;			  //���̺�
	char name[MANE_SIZE]; //������
	int time_arrive;	  //����ʱ��
	int time_use;		  //����ʱ��

	int number_go;	   //ִ�д���
	int time_start;	   //��ʼʱ��
	int time_turn;	   //��תʱ��
	int time_left;		//ʣ������ʱ��
	float time_turn_w; //��Ȩ��תʱ��

	bool sign_finished = false; //�Ƿ��Ѿ����
	bool sign_start_t = false;	//�Ƿ��Ѿ���ʼʱ��Ƭ��ת

	int number_t;		//ʱ��Ƭ�ִ�
};

void init(int n, PCB p[]) //��ʼ��
{
	srand((unsigned)time(NULL));
	for (int i = 0; i < n; i++)
	{
		p[i].number = i;
		p[i].time_use = (rand() % MAX_TIME_USE / 10 + 1) * 10; //����10-MAX_TIME_USE�������
		p[i].time_left = p[i].time_use;
		p[i].time_arrive = (rand() % MAX_TIME_ARRIVE / 5) * 5; //����0-MAX_TIME_ARRIVE�������
		p[i].sign_finished = false;
	}
}

void _FCFS(PCB p[], int n) //ʱ��Ƭ��ת�����������ȷ���
{
	int time_now = 0;	//��ǰʱ��
	int t_now = 0;		//��ǰʱ��Ƭ�ִ�	
	int pcb_next = -1;	//��һ����Ҫִ�е��߳�
	int number_go = 0;	//ִ�д���
	//����ģ��ʱ�������
	for (;;)
	{
		pcb_next = -1;
		for (int i = 0; i < n; i++)
		{
			//�жϸý����Ƿ������������ǰʱ���Ѿ�������û����ɣ�
			if (p[i].time_arrive <= time_now && !p[i].sign_finished)
			{
				//�׸������Ľ���
				if (pcb_next == -1)
				{
					pcb_next = i;
				}
				else
				{
					//�Ƚ��䵽��ʱ��
					if (p[i].time_arrive < p[pcb_next].time_arrive)
					{
						pcb_next = i;
					}
				}
			}
		}
		//��ǰʱ��û�з��������Ľ��̳���
		if (pcb_next == -1)
		{
			time_now++;
		}
		else
		{
			//���¸ý��̵���Ϣ��ʱ�䣨ֱ�������ý�����ɣ�
			p[pcb_next].sign_finished = true;
			p[pcb_next].time_start = time_now;
			p[pcb_next].number_go = number_go;
			p[pcb_next].time_turn = time_now - p[pcb_next].time_arrive + p[pcb_next].time_use;
			p[pcb_next].time_turn_w = (float)p[pcb_next].time_turn / p[pcb_next].time_use;

			time_now += p[pcb_next].time_use;
			number_go++;
		}
		//���н��̾������
		if (number_go == n)
			break;
	}
}

void printPCB(PCB p[], int n)
{
	printf("\n");
	printf("����ʵ�����ɵĽ����У�\n");
	printf("���̺�\t����ʱ��\t����ʱ��\n");
	printf("--------------------------------------\n");
	for (int i = 0; i < n; i++)
	{
		printf(" %d\t  %d\t\t  %d\n",
			p[i].number, p[i].time_arrive, p[i].time_use);
	}
	printf("--------------------------------------\n");
	printf("\n");
}
void printResult(PCB p[], int n)
{
	printf("���д���\n");
	printf("����\t���̺�\t����ʱ��\t����ʱ��\t��ʼʱ��\t����ʱ��\t��תʱ��\t��Ȩ��תʱ��\n");
	printf("---------------------------------------------------------------------------------------------------------------\n");
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (p[j].number_go == i)
			{
				printf(" %d\t  %d\t   %d\t\t   %d\t\t   %d\t\t   %d\t\t   %d\t\t    %.2f\n",
					i + 1, p[j].number, p[j].time_arrive, p[j].time_use, p[j].time_start,
					p[j].time_start + p[j].time_use, p[j].time_turn, p[j].time_turn_w);
			}
			else
			{
				continue;
			}
		}
	}
	printf("---------------------------------------------------------------------------------------------------------------\n");
	int time_turn_average = 0;
	int time_turn_average_w = 0;
	for (int i = 0; i < n; i++)
	{
		time_turn_average += p[i].time_turn;
		time_turn_average_w += p[i].time_turn_w;
	}
	printf("ƽ����תʱ��%.2f,ƽ����Ȩ��תʱ��%.2f\n\n",
		(float)time_turn_average / n, (float)time_turn_average_w / n);
}

int main()
{
	int n;
	printf("��������Ҫ���ɵĽ�����:");
	scanf("%d", &n);

#ifdef MULTI_TEST
	float time_turn_FCFS_use = 0;
	float time_turn_SJF_use = 0;
	float time_turn_HRN_use = 0;
	float time_turn_w_FCFS_use = 0;
	float time_turn_w_SJF_use = 0;
	float time_turn_w_HRN_use = 0;

	for (int i = 0; i < TEST_TIME; i++)
	{
		PCB* p_FCFS = (PCB*)malloc(sizeof(PCB) * n);
		init(n, p_FCFS);
		PCB* p_SJF = (PCB*)malloc(sizeof(PCB) * n);
		init(n, p_SJF);
		PCB* p_HRN = (PCB*)malloc(sizeof(PCB) * n);
		init(n, p_HRN);

		int time_turn_average = 0;
		int time_turn_average_w = 0;

		FCFS(p_FCFS, n);
		for (int i = 0; i < n; i++)
		{
			time_turn_average += p_FCFS[i].time_turn;
			time_turn_average_w += p_FCFS[i].time_turn_w;
		}
		time_turn_FCFS_use += (float)time_turn_average / n;
		time_turn_w_FCFS_use += (float)time_turn_average_w / n;

		time_turn_average = 0;
		time_turn_average_w = 0;
		SJF(p_SJF, n);
		for (int i = 0; i < n; i++)
		{
			time_turn_average += p_SJF[i].time_turn;
			time_turn_average_w += p_SJF[i].time_turn_w;
		}
		time_turn_SJF_use += (float)time_turn_average / n;
		time_turn_w_SJF_use += (float)time_turn_average_w / n;

		time_turn_average = 0;
		time_turn_average_w = 0;
		HRN(p_HRN, n);
		for (int i = 0; i < n; i++)
		{
			time_turn_average += p_HRN[i].time_turn;
			time_turn_average_w += p_HRN[i].time_turn_w;
		}
		time_turn_HRN_use += (float)time_turn_average / n;
		time_turn_w_HRN_use += (float)time_turn_average_w / n;

		delete p_FCFS, p_SJF, p_HRN;
	}
	printf("��ǰ���Դ���%d\n\n", TEST_TIME);

	printf("FCFS �����ȷ���\n");
	printf("ƽ����תʱ��%.2f,ƽ����Ȩ��תʱ��%.2f\n\n",
		(float)time_turn_FCFS_use / TEST_TIME, (float)time_turn_w_FCFS_use / TEST_TIME);

	printf("SJF ����ҵ����\n");
	printf("ƽ����תʱ��%.2f,ƽ����Ȩ��תʱ��%.2f\n\n",
		(float)time_turn_SJF_use / TEST_TIME, (float)time_turn_w_SJF_use / TEST_TIME);

	printf("HRN �����Ӧ��\n");
	printf("ƽ����תʱ��%.2f,ƽ����Ȩ��תʱ��%.2f\n\n",
		(float)time_turn_HRN_use / TEST_TIME, (float)time_turn_w_HRN_use / TEST_TIME);
#endif // MULTI_TEST

#ifndef MULTI_TEST
	PCB* p_FCFS = (PCB*)malloc(sizeof(PCB) * n);
	init(n, p_FCFS);
	PCB* p_SJF = (PCB*)malloc(sizeof(PCB) * n);
	init(n, p_SJF);
	PCB* p_HRN = (PCB*)malloc(sizeof(PCB) * n);
	init(n, p_HRN);

	printPCB(p_FCFS, n);

	printf("FCFS �����ȷ���\n");
	FCFS(p_FCFS, n);
	printResult(p_FCFS, n);

	printf("SJF ����ҵ����\n");
	SJF(p_SJF, n);
	printResult(p_SJF, n);

	printf("HRN �����Ӧ��\n");
	HRN(p_HRN, n);
	printResult(p_HRN, n);
#endif // !MULTITEST
	return 0;
}
