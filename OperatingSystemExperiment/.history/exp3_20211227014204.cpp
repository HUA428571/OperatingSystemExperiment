#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdlib.h>
#include <time.h>
#define TIME_SIZE 10			//时间片大小
#define MAX_TIME_USE 60	//最长作业所用时间
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
	int time_end;		//结束时间
	int time_left;	   //剩余运行时间	
	int time_turn;	   //周转时间
	float time_turn_w; //带权周转时间

	bool sign_finished = false; //是否已经完成
	bool sign_start_t = false;	//是否已经开始时间片轮转

	int number_t; //时间片轮次
};
struct PCB_q_node
{
	PCB_q_node *before; //队列中的下一个PCB
	PCB *p;				//PCB
	PCB_q_node *next;	//队列中的上一个PCB
};
struct PCB_q
{
	PCB_q_node *head;
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

// void queue_by_time(PCB p[], int n, PCB_q *q)
// {
// 	PCB_q_node *firstnode = (PCB_q_node *)malloc(sizeof(PCB_q_node));
// 	q->head = firstnode;
// 	firstnode->before = NULL;
// 	PCB_q_node *node_now = firstnode;
// 	for (int i = 0; i < n; i++)
// 	{
// 		node_now->p = &p[i];
// 		for (int j = i + 1; j < n; j++)
// 		{
// 			if (node_now->p->time_start > p[j].time_start)
// 			{
// 				/* code */
// 			}
// 		}
// 		PCB_q_node *node = (PCB_q_node *)malloc(sizeof(PCB_q_node));
// 	}
// }

void _FCFS(PCB p[], int n) //时间片轮转，基于先来先服务
{
	int time_now = 0;  //当前时间
	int t_now = 0;	   //当前时间片轮次
	int pcb_next = -1; //下一个需要执行的线程
	int number_go = 0; //序号

	int turn_flag=0;

	int* t_queue_current=(int*)malloc(sizeof(int)*n);
	int* t_queue_next=(int*)malloc(sizeof(int)*n);	

	//我们模拟时间的流逝
	while(true)
	{
		for (int i = 0; i < n; i++)
		{
			//当前轮转回次

			//获取下一个执行的进程
			pcb_next = -1;
			for (int i = 0; i < n; i++)
			{
				//判断该进程是否符合条件（当前时间已经载入且没有完成）
				if (p[i].time_arrive <= time_now && !p[i].sign_finished)
				{
					if (p[i].sign_start_t) //当前进程还未进入轮转
					{
						//分配当前的时间片轮次
						p[i].number_t = t_now;
						//进入轮转
						p[i].sign_start_t = true;
					}
					//该进程参与本次轮转,即其轮转次数与本轮相同
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
				}
			}
			//当前轮转没有符合条件的进程出现，时间继续，进入下一个轮转
			if (pcb_next == -1)
			{
				t_now++;
				time_now++;
				break;
			}
			else
			{
				//给予该进程时间片运行，并将其轮转轮数+1
				//首次执行该进程
				if (p[pcb_next].time_left == p[pcb_next].time_use)
				{
					p[pcb_next].time_start = time_now;
				}

				//p[pcb_next].sign_finished = true;
				//p[pcb_next].time_start = time_now;
				//p[pcb_next].number_go = number_go;

				//打印本次执行1
				number_go++;
				printf(" %d\t  %d\t", number_go + 1, time_now);

				//经过本次轮转，该进程执行完毕
				if (p[pcb_next].time_left < TIME_SIZE)
				{
					time_now += p[pcb_next].time_left;
					p[pcb_next].sign_finished = true;
					p[pcb_next].time_left = 0;
					p[pcb_next].time_end = time_now;
					p[pcb_next].time_turn = p[pcb_next].time_end - p[pcb_next].time_start;
					p[pcb_next].time_turn_w = (float)p[pcb_next].time_turn / p[pcb_next].time_use;
				}
				else
				{
					time_now += TIME_SIZE;
					p[pcb_next].time_left -= TIME_SIZE;
					//该进程进入下一次轮转
					p[pcb_next].number_t++;
				}
				//打印本次执行2
				printf("   %d\t\t   %d\t\t   %d\t\t   %d\t\t   %d\t\t   %d\n",
					   time_now, p[pcb_next].number, p[pcb_next].time_arrive, 
					   p[pcb_next].time_use, p[pcb_next].time_start, p[pcb_next].time_left);

				//p[pcb_next].time_turn = time_now - p[pcb_next].time_arrive + p[pcb_next].time_use;
				//p[pcb_next].time_turn_w = (float)p[pcb_next].time_turn / p[pcb_next].time_use;

				//time_now += p[pcb_next].time_use;
				//number_go++;
			}
		}
		t_now++;
	};
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
//void printPCB_turn()

int main()
{
	int n;
	printf("请输入需要生成的进程数:");
	scanf("%d", &n);

	PCB *p_FCFS = (PCB *)malloc(sizeof(PCB) * n);
	init(n, p_FCFS);

	printPCB(p_FCFS, n);

	printf("FCFS 先来先服务\n");
	printf("序号\t进程号\t到达时间\t所需时间\t开始时间\t结束时间\t剩余时间\n");
	_FCFS(p_FCFS, n);

	return 0;
}
