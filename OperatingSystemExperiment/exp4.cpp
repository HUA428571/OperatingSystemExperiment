#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdlib.h>
#include <time.h>
#define MANE_SIZE 127
#define MAX_TIME_USE 90	//���ҵ����ʱ��
#define MAX_TIME_ARRIVE 90 //���ҵ��ʼʱ��
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
	float time_turn_w; //��Ȩ��תʱ��

	bool sign_finished = false; //�Ƿ��Ѿ����
};

void init(int n, PCB p[]) //��ʼ��
{
	srand((unsigned)time(NULL));
	for (int i = 0; i < n; i++)
	{
		p[i].number = i;
		p[i].time_use = (rand() % MAX_TIME_USE / 10 + 1) * 10; //����10-MAX_TIME_USE�������
		p[i].time_arrive = (rand() % MAX_TIME_ARRIVE / 5) * 5; //����0-MAX_TIME_ARRIVE�������
		p[i].sign_finished = false;
	}
}

void FCFS(PCB p[], int n) //�����ȷ���
{
	int time_now = 0;  //��ǰʱ��
	int pcb_next = -1; //��һ����Ҫִ�е��߳�
	int number_go = 0; //ִ�д���
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

void SJF(PCB p[], int n) //����ҵ����
{
	int time_now = 0;  //��ǰʱ��
	int pcb_next = -1; //��һ����Ҫִ�е��߳�
	int number_go = 0; //ִ�д���
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
					//�Ƚ��䳤��
					if (p[i].time_use < p[pcb_next].time_use)
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

void HRN(PCB p[], int n) //�����Ӧ������
{
	int time_now = 0;  //��ǰʱ��
	int pcb_next = -1; //��һ����Ҫִ�е��߳�
	int number_go = 0; //ִ�д���
	//����ģ��ʱ�������
	for (;;)
	{
		pcb_next = -1;
		float R_next; //��Ӧ��
		float R_now;  //��Ӧ�ȣ���ǰ���㣩
		for (int i = 0; i < n; i++)
		{
			//�жϸý����Ƿ������������ǰʱ���Ѿ�������û����ɣ�
			if (p[i].time_arrive <= time_now && !p[i].sign_finished)
			{
				//�׸������Ľ���
				if (pcb_next == -1)
				{
					pcb_next = i;
					R_next = (float)(time_now - p[i].time_arrive) / p[i].time_use;
				}
				else
				{
					R_now = (float)(time_now - p[i].time_arrive) / p[i].time_use;
					//�Ƚ���Ӧ��
					if (R_now > R_next)
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
	PCB *p_FCFS = (PCB *)malloc(sizeof(PCB) * n);
	init(n, p_FCFS);
	PCB *p_SJF = (PCB *)malloc(sizeof(PCB) * n);
	init(n, p_SJF);
	PCB *p_HRN = (PCB *)malloc(sizeof(PCB) * n);
	init(n, p_HRN);

	printPCB(p_FCFS, n);

	printf("FCFS �����ȷ���\n");
	FCFS(p_FCFS, n);
	//printResult(p_FCFS, n);

	printf("SJF ����ҵ����\n");
	SJF(p_SJF, n);
	//printResult(p_SJF, n);

	printf("HRN �����Ӧ��\n");
	HRN(p_HRN, n);
	//printResult(p_HRN, n);

	return 0;
}
