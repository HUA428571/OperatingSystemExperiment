#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdlib.h>
#include <time.h>
#define TIME_SIZE 10		//ʱ��Ƭ��С
#define MAX_TIME_USE 60		//���ҵ����ʱ��
#define MAX_TIME_ARRIVE 180 //���ҵ��ʼʱ��
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
	int time_end;	   //����ʱ��
	int time_left;	   //ʣ������ʱ��
	int time_turn;	   //��תʱ��
	float time_turn_w; //��Ȩ��תʱ��

	bool sign_finished = false; //�Ƿ��Ѿ����
	bool sign_start_t = false;	//�Ƿ��Ѿ���ʼʱ��Ƭ��ת

	int number_t; //ʱ��Ƭ�ִ�
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
		p[i].sign_start_t = false;
	}
}

void _FCFS(PCB p[], int n) //ʱ��Ƭ��ת�����������ȷ���
{
	int time_now = 0;  //��ǰʱ��
	int t_now = 0;	   //��ǰʱ��Ƭ�ִ�
	int pcb_next = -1; //��һ����Ҫִ�е��߳�
	int number_go = 0; //���
	int number_finish = 0;

	int turn_flag = 0;

	int *t_queue_current = (int *)malloc(sizeof(int) * n);
	int *t_queue_next = (int *)malloc(sizeof(int) * n);

	//����ģ��ʱ�������
	while (true)
	{
		for (int i = 0; i < n; i++)
		{
			//��ǰ��ת�ش�
			//��ȡ��һ��ִ�еĽ���
			pcb_next = -1;
			for (int i = 0; i < n; i++)
			{
				//�жϸý����Ƿ������������ǰʱ���Ѿ�������û����ɣ�
				if (p[i].time_arrive <= time_now && !p[i].sign_finished)
				{
					if (!p[i].sign_start_t) //��ǰ���̻�δ������ת
					{
						//���䵱ǰ��ʱ��Ƭ�ִ�
						p[i].number_t = t_now;
						//������ת
						p[i].sign_start_t = true;
					}
					//�ý��̲��뱾����ת,������ת�����뱾����ͬ
					if (p[i].number_t == t_now)
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
			}
			//��ǰ��תû�з��������Ľ��̳��֣�ʱ�������������һ����ת
			if (pcb_next == -1)
			{
				if (i == 0)
					time_now++;
				break;
			}
			else
			{
				//����ý���ʱ��Ƭ���У���������ת����+1
				//�״�ִ�иý���
				if (p[pcb_next].time_left == p[pcb_next].time_use)
				{
					p[pcb_next].time_start = time_now;
				}

				//��ӡ����ִ��1
				number_go++;
				printf(" %d\t  %d\t\t", number_go, time_now);

				//����������ת���ý���ִ�����
				if (p[pcb_next].time_left <= TIME_SIZE)
				{
					time_now += p[pcb_next].time_left;
					p[pcb_next].sign_finished = true;
					p[pcb_next].time_left = 0;
					p[pcb_next].time_end = time_now;
					p[pcb_next].time_turn = p[pcb_next].time_end - p[pcb_next].time_start;
					p[pcb_next].time_turn_w = (float)p[pcb_next].time_turn / p[pcb_next].time_use;
					number_finish++;
				}
				else
				{
					time_now += TIME_SIZE;
					p[pcb_next].time_left -= TIME_SIZE;
					//�ý��̽�����һ����ת
					p[pcb_next].number_t += 1;
				}
				//��ӡ����ִ��2
				printf("   %d\t\t  %d\t   %d\t\t   %d\t\t   %d\t\t   %d\n",
					   time_now, p[pcb_next].number, p[pcb_next].time_arrive,
					   p[pcb_next].time_use, p[pcb_next].time_start, p[pcb_next].time_left);
			}
		}
		if (number_finish >= n)
			break;
		t_now++;
	};
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

int main()
{
	int n;
	printf("��������Ҫ���ɵĽ�����:");
	scanf("%d", &n);

	PCB *p_FCFS = (PCB *)malloc(sizeof(PCB) * n);
	init(n, p_FCFS);

	printPCB(p_FCFS, n);

	printf("ִ�д���\n");
	printf("---------------------------------------------------------------------------------------------------------------\n");
	printf("���\tʱ��Ƭ��ʼ\tʱ��Ƭ����\t���̺�\t����ʱ��\t����ʱ��\t��ʼʱ��\tʣ��ʱ��\n");
	_FCFS(p_FCFS, n);
	printf("---------------------------------------------------------------------------------------------------------------\n");

	int time_turn_average = 0;
	int time_turn_average_w = 0;
	for (int i = 0; i < n; i++)
	{
		time_turn_average += p_FCFS[i].time_turn;
		time_turn_average_w += p_FCFS[i].time_turn_w;
	}
	printf("ƽ����תʱ��%.2f,ƽ����Ȩ��תʱ��%.2f\n\n",
		   (float)time_turn_average / n, (float)time_turn_average_w / n);

	return 0;
}
