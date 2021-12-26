#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdlib.h>
#include <time.h>
#define MANE_SIZE 127
#define MAX_TIME_USE 120	//���ҵ����ʱ��
#define MAX_TIME_ARRIVE 240 //���ҵ��ʼʱ��
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

	float turntime;			//��תʱ��
	float average_turntime; //��Ȩ��תʱ��
	int sign;				//��־�����Ƿ����
	int remain_time;		//ʣ��ʱ��
	int priority;			//���ȼ�
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

void time_segment(int n) //ʱ��Ƭ��ת
{
	// int i, j;
	// int T;   //ʱ��Ƭ
	// int flag = 1;   //�����������Ƿ��н���
	// //int time=pcb[0].arrivetime;   //��ǰ��ʱ��
	// int time = 0;
	// int sum = 0;   //�Ѿ���ɵĽ�����

	// //�������̵�arrivetime������������
	// for (i = 1; i <= n; i++)
	// {
	// 	for (j = i + 1; j <= n; j++)
	// 	{
	// 		if (pcb[i].time_arrive > pcb[j].time_arrive)
	// 		{
	// 			pcb[0] = pcb[j];
	// 			pcb[j] = pcb[i];
	// 			pcb[i] = pcb[0];
	// 		}
	// 	}
	// }
	// //��ʼ��ʣ��ʱ��
	// for (i = 1; i <= n; i++)
	// {
	// 	pcb[i].remain_time = pcb[i].time_use;
	// }
	// //printf("output the sort result:\n");
	// //for(i=1;i<=n;i++)    //��������Ƿ���ȷ
	// //printf("%d\t",pcb[i].name);
	// printf("input the slicetime:\n");
	// scanf("%d", &T);

	// while (sum < n)
	// {
	// 	flag = 0;   //��ǰ����������û�н���
	// 	int i;
	// 	for (i = 1; i <= n; i++)
	// 	{
	// 		if (pcb[i].sign == 1) continue; //��ʾ�ý��������
	// 		else
	// 		{
	// 			if (time >= pcb[i].time_arrive)
	// 			{

	// 				//û����ɵĽ�����Ҫ��ʱ�����һ��ʱ��Ƭ
	// 				if (pcb[i].remain_time > T)
	// 				{
	// 					flag = 1;
	// 					time = time + T;
	// 					pcb[i].remain_time = pcb[i].remain_time - T;
	// 					//printf("%10d%16d%12d%12d%12d\n",pcb[i].name,time-T,T,pcb[i].remain_time,time);
	// 				}

	// 				//û����ɵĽ�����Ҫ��ʱ��С�ڻ����һ��ʱ��Ƭ
	// 				else if (pcb[i].remain_time <= T)
	// 				{
	// 					flag = 1;  //�����������
	// 					time = time + pcb[i].remain_time;
	// 					pcb[i].time_start = time;
	// 					pcb[i].sign = 1;
	// 					//printf("%10d%16d%12d%12d%12d\n",pcb[i].name,time-pcb[i].remain_time,pcb[i].servicetime,0,time);
	// 					pcb[i].remain_time = 0;
	// 				}

	// 				if (pcb[i].sign == 1) sum++;
	// 			}
	// 		}

	// 	}//for

	// 	if (flag == 0 && sum < n)   // ����ûִ�еĽ��̣���û����;�������
	// 	{
	// 		int i;
	// 		for (i = 1; i <= n; i++)
	// 			if (pcb[i].sign == 0) { time = pcb[i].time_arrive; break; }
	// 	}

	// }//while
	// //������ת�ʹ�Ȩ��ת
	// for (i = 1; i <= n; i++)
	// {
	// 	pcb[i].turntime = pcb[i].time_start - pcb[i].time_arrive;
	// 	pcb[i].average_turntime = pcb[i].turntime / pcb[i].time_use;
	// }
}
void print_time(int n) //ʱ��Ƭ��ת���
{
	// int i;
	// printf("\n name arrivetime servicetime fihishtime turntime averageturntime\n");
	// for (i = 1; i <= n; i++)
	// {
	// 	printf("%d\t%d\t%d\t%d\t%f\t%f", pcb[i].name, pcb[i].time_arrive, pcb[i].time_use, pcb[i].time_start, pcb[i].turntime, pcb[i].average_turntime);
	// 	printf("\n");
	// }
}

void Priority(int n) //���ȼ����ȼ�С����������������Ӵ�ӡ
{
	// int i, j;
	// int time = pcb[1].time_arrive;
	// //�������̵�priority������������,���ȼ���ߵĽ�����ִ��
	// for (i = 2; i <= n; i++)
	// {
	// 	for (j = i + 1; j <= n; j++)
	// 	{
	// 		if (pcb[i].priority > pcb[j].priority)
	// 		{
	// 			pcb[0] = pcb[j];
	// 			pcb[j] = pcb[i];
	// 			pcb[i] = pcb[0];
	// 		}
	// 	}
	// }
	// //printf("output the sort result: \n"); //���������
	// //for(i=1;i<=n;i++)    //��������Ƿ���ȷ
	// //printf("%d\t",pcb[i].name);

	// printf("\n name arrivetime servicetime priority fihishtime turntime averageturntime\n");//������ ����ʱ��  ����ʱ��   ���ȼ�  ���ʱ��
	// //�ȵ���Ľ��̵�һ��ִ��
	// if (i = 1)
	// {
	// 	pcb[i].time_start = pcb[i].time_arrive + pcb[i].time_use;
	// 	time = pcb[i].time_arrive + pcb[i].time_use;
	// 	pcb[i].turntime = pcb[i].time_start - pcb[i].time_arrive;
	// 	pcb[i].average_turntime = pcb[i].turntime / pcb[i].time_use;
	// 	printf("%d\t%d\t%d\t%d\t%d\t%f\t%f", pcb[i].name, pcb[i].time_arrive, pcb[i].time_use, pcb[i].priority, pcb[i].time_start, pcb[i].turntime, pcb[i].average_turntime);
	// 	printf("\n");
	// 	//���Ե�һ�����������ȷ
	// 	/*	printf("output the first process:\n");//�����һ�������
	// 	printf("processID arrivetime finishtime\n");//����  ����ʱ��  ���ʱ��
	// 	printf("%4d%8d%8d",pcb[i].name,pcb[i].arrivetime,pcb[i].finishtime);
	// 	printf("\n"); */
	// 	i++;
	// }
	// for (i = 2; i <= n; i++)
	// {
	// 	time = time + pcb[i].time_use;
	// 	pcb[i].time_start = time;
	// 	pcb[i].turntime = pcb[i].time_start - pcb[i].time_arrive;
	// 	pcb[i].average_turntime = pcb[i].turntime / pcb[i].time_use;
	// 	printf("%d\t%d\t%d\t%d\t%d\t%f\t%f", pcb[i].name, pcb[i].time_arrive, pcb[i].time_use, pcb[i].priority, pcb[i].time_start, pcb[i].turntime, pcb[i].average_turntime);
	// 	printf("\n");
	// }//for

} //void

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

	// int i, j;
	// int time = pcb[1].time_arrive;
	// float t;
	// for (i = 2; i <= n; i++)
	// {
	// 	for (j = i + 1; j <= n; j++)
	// 	{
	// 		if (pcb[i].time_use > pcb[j].time_use)
	// 		{
	// 			pcb[0] = pcb[j];
	// 			pcb[j] = pcb[i];
	// 			pcb[i] = pcb[0];
	// 		}
	// 	}
	// }
	// printf("\n name arrivetime servicetime fihishtime turntime averageturntime\n");//������   ����ʱ��   ���ȼ�  ���ʱ��
	// if (i = 1)
	// {
	// 	pcb[i].time_start = pcb[i].time_arrive + pcb[i].time_use;
	// 	time = pcb[i].time_arrive + pcb[i].time_use;
	// 	pcb[i].turntime = pcb[i].time_start - pcb[i].time_arrive;
	// 	pcb[i].average_turntime = pcb[i].turntime / pcb[i].time_use;
	// 	printf("%d\t%d\t%d\t%d\t%f\t%f", pcb[i].name, pcb[i].time_arrive, pcb[i].time_use, pcb[i].time_start, pcb[i].turntime, pcb[i].average_turntime);
	// 	printf("\n");
	// 	i++;
	// }
	// for (i = 2; i <= n; i++)
	// {
	// 	time = time + pcb[i].time_use;
	// 	pcb[i].time_start = time;
	// 	pcb[i].turntime = pcb[i].time_start - pcb[i].time_arrive;
	// 	pcb[i].average_turntime = pcb[i].turntime / pcb[i].time_use;
	// 	printf("%d\t%d\t%d\t%d\t%f\t%f", pcb[i].name, pcb[i].time_arrive, pcb[i].time_use, pcb[i].time_start, pcb[i].turntime, pcb[i].average_turntime);
	// 	printf("\n");
	// }//for
}

void printPCB(PCB p[], int n)
{
	printf("\n\n");
	printf("����ʵ�����ɵĽ����У�\n");
	printf("���̺�\t����ʱ��\t����ʱ��\n");
	printf("-------------------------------------------\n");
	for (int i = 0; i < n; i++)
	{
		printf("%d\t%d\t\t%d\n",
			   p[i].number, p[i].time_arrive, p[i].time_use);
	}
	printf("-------------------------------------------\n");
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
				printf("%d\t %d\t  %d\t\t  %d\t\t  %d\t\t  %d\t\t  %d\t\t  %.2f\n",
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
	printf("ƽ����תʱ��%d,ƽ����Ȩ��תʱ��%.2f\n\n",
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

	printPCB(p_FCFS, n);

	printf("FCFS �����ȷ���\n");
	FCFS(p_FCFS, n);
	printResult(p_FCFS, n);

	printf("SJF ����ҵ����\n");
	SJF(p_SJF, n);
	printResult(p_SJF, n);
}
