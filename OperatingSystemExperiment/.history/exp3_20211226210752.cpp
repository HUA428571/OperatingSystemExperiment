#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdlib.h>
#include <time.h>
#define TIME_SIZE 5			//时间片大小
#define MAX_TIME_USE 120	//最长作业所用时间
#define MAX_TIME_ARRIVE 240 //最长作业开始时间
#define MANE_SIZE 127
#define max 50

struct PCB
{
	int number;			  //进程号
	char name[MANE_SIZE]; //进程名
	int time_arrive;	  //到达时间
	int time_use;		  //所需时间

	int number_go;	   //执行次序
	int time_start;	   //开始时间
	int time_turn;	   //周转时间
	int time_left;		//剩余运行时间
	float time_turn_w; //带权周转时间

	bool sign_finished = false; //是否已经完成
	bool sign_start_t = false;	//是否已经开始时间片轮转

	int number_t;		//时间片轮次
};
struct PCB_q_node
{
	PCB_q_node *before; //队列中的下一个PCB
	PCB *p;		   //PCB
	PCB_q_node *next;   //队列中的上一个PCB
};
struct PCB_q
{
	PCB_q_node* head;
};


void init(int n, PCB p[]) //初始化
{
	srand((unsigned)time(NULL));
	for (int i = 0; i < n; i++)
	{
		p[i].number = i;
		p[i].time_use = (rand() % MAX_TIME_USE / 10 + 1) * 10; //产生10-MAX_TIME_USE的随机数
		p[i].time_left = p[i].time_use;
		p[i].time_arrive = (rand() % MAX_TIME_ARRIVE / 5) * 5; //产生0-MAX_TIME_ARRIVE的随机数
		p[i].sign_finished = false;
	}
}

void queue_by_time(PCB p[], int n,PCB_q*q)
{
	PCB_q_node *firstnode = (PCB_q_node *)malloc(sizeof(PCB_q_node));
	q->head = firstnode;
	firstnode->before=NULL;
	PCB_q_node *node_now=firstnode;
	for (int i = 0; i < n; i++)
	{
		node_now->p=&p[i];
		for (int j = i + 1; j < n; j++)
		{
			if (node_now->p->time_start>p[j].time_start)
			{
				/* code */
			}
			
		}
		PCB_q_node *node = (PCB_q_node *)malloc(sizeof(PCB_q_node));
	}
}

void _FCFS(PCB p[], int n) //时间片轮转，基于先来先服务
{
	int time_now = 0;	//当前时间
	int t_now = 0;		//当前时间片轮次	
	int pcb_next = -1;	//下一个需要执行的线程
	int number_go = 0;	//执行次序
	//我们模拟时间的流逝
	for (;;)
	{
		pcb_next = -1;
		for (int i = 0; i < n; i++)
		{
			//判断该进程是否符合条件（当前时间已经载入且没有完成）
			if (p[i].time_arrive <= time_now && !p[i].sign_finished)
			{
				if (p[i].sign_start_t)//当前进程还未进入轮转
				{
					//分配当前的时间片轮次
					p[i].number_t=t_now;
					p[i].sign_start_t=true;
				}
				// else
				// {
				if (p[i].number_t == t_now)
				{
					//首个遇到的进程
					if (pcb_next == -1)
					{
						pcb_next = i;
					}
					else
					{
						//比较其到达时间
						if (p[i].time_arrive < p[pcb_next].time_arrive)
						{
							pcb_next = i;
						}
					}
				}

//				}
			}
		}
		//当前时间没有符合条件的进程出现
		if (pcb_next == -1)
		{
			time_now++;
		}
		else
		{
			//更新该进程的信息和时间（直接跳到该进程完成）
			p[pcb_next].sign_finished = true;
			p[pcb_next].time_start = time_now;
			p[pcb_next].number_go = number_go;
			p[pcb_next].time_turn = time_now - p[pcb_next].time_arrive + p[pcb_next].time_use;
			p[pcb_next].time_turn_w = (float)p[pcb_next].time_turn / p[pcb_next].time_use;

			time_now += p[pcb_next].time_use;
			number_go++;
		}
		//所有进程均已完成
		if (number_go == n)
			break;
	}
}

void printPCB(PCB p[], int n)
{
	printf("\n");
	printf("本次实验生成的进程有：\n");
	printf("进程号\t进入时间\t运行时间\n");
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
	printf("运行次序：\n");
	printf("次序\t进程号\t进入时间\t运行时间\t开始时间\t结束时间\t周转时间\t带权周转时间\n");
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
	printf("平均周转时间%.2f,平均带权周转时间%.2f\n\n",
		(float)time_turn_average / n, (float)time_turn_average_w / n);
}

int main()
{
	int n;
	printf("请输入需要生成的进程数:");
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
	printf("当前测试次数%d\n\n", TEST_TIME);

	printf("FCFS 先来先服务\n");
	printf("平均周转时间%.2f,平均带权周转时间%.2f\n\n",
		(float)time_turn_FCFS_use / TEST_TIME, (float)time_turn_w_FCFS_use / TEST_TIME);

	printf("SJF 短作业优先\n");
	printf("平均周转时间%.2f,平均带权周转时间%.2f\n\n",
		(float)time_turn_SJF_use / TEST_TIME, (float)time_turn_w_SJF_use / TEST_TIME);

	printf("HRN 最高响应比\n");
	printf("平均周转时间%.2f,平均带权周转时间%.2f\n\n",
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

	printf("FCFS 先来先服务\n");
	_FCFS(p_FCFS, n);
	printResult(p_FCFS, n);

#endif // !MULTITEST
	return 0;
}
