#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdlib.h>
#include <time.h>
#define MANE_SIZE 127
#define MAX_TIME_USE 90	//最长作业所用时间
#define MAX_TIME_ARRIVE 90 //最长作业开始时间
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
	float time_turn_w; //带权周转时间

	bool sign_finished = false; //是否已经完成
};

void init(int n, PCB p[]) //初始化
{
	srand((unsigned)time(NULL));
	for (int i = 0; i < n; i++)
	{
		p[i].number = i;
		p[i].time_use = (rand() % MAX_TIME_USE / 10 + 1) * 10; //产生10-MAX_TIME_USE的随机数
		p[i].time_arrive = (rand() % MAX_TIME_ARRIVE / 5) * 5; //产生0-MAX_TIME_ARRIVE的随机数
		p[i].sign_finished = false;
	}
}

void FCFS(PCB p[], int n) //先来先服务
{
	int time_now = 0;  //当前时间
	int pcb_next = -1; //下一个需要执行的线程
	int number_go = 0; //执行次序
	//我们模拟时间的流逝
	for (;;)
	{
		pcb_next = -1;
		for (int i = 0; i < n; i++)
		{
			//判断该进程是否符合条件（当前时间已经载入且没有完成）
			if (p[i].time_arrive <= time_now && !p[i].sign_finished)
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

void SJF(PCB p[], int n) //短作业优先
{
	int time_now = 0;  //当前时间
	int pcb_next = -1; //下一个需要执行的线程
	int number_go = 0; //执行次序
	//我们模拟时间的流逝
	for (;;)
	{
		pcb_next = -1;
		for (int i = 0; i < n; i++)
		{
			//判断该进程是否符合条件（当前时间已经载入且没有完成）
			if (p[i].time_arrive <= time_now && !p[i].sign_finished)
			{
				//首个遇到的进程
				if (pcb_next == -1)
				{
					pcb_next = i;
				}
				else
				{
					//比较其长短
					if (p[i].time_use < p[pcb_next].time_use)
					{
						pcb_next = i;
					}
				}
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

void HRN(PCB p[], int n) //最高响应比优先
{
	int time_now = 0;  //当前时间
	int pcb_next = -1; //下一个需要执行的线程
	int number_go = 0; //执行次序
	//我们模拟时间的流逝
	for (;;)
	{
		pcb_next = -1;
		float R_next; //响应比
		float R_now;  //响应比（当前计算）
		for (int i = 0; i < n; i++)
		{
			//判断该进程是否符合条件（当前时间已经载入且没有完成）
			if (p[i].time_arrive <= time_now && !p[i].sign_finished)
			{
				//首个遇到的进程
				if (pcb_next == -1)
				{
					pcb_next = i;
					R_next = (float)(time_now - p[i].time_arrive) / p[i].time_use;
				}
				else
				{
					R_now = (float)(time_now - p[i].time_arrive) / p[i].time_use;
					//比较响应比
					if (R_now > R_next)
					{
						pcb_next = i;
					}
				}
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
	PCB *p_FCFS = (PCB *)malloc(sizeof(PCB) * n);
	init(n, p_FCFS);
	PCB *p_SJF = (PCB *)malloc(sizeof(PCB) * n);
	init(n, p_SJF);
	PCB *p_HRN = (PCB *)malloc(sizeof(PCB) * n);
	init(n, p_HRN);

	printPCB(p_FCFS, n);

	printf("FCFS 先来先服务\n");
	FCFS(p_FCFS, n);
	//printResult(p_FCFS, n);

	printf("SJF 短作业优先\n");
	SJF(p_SJF, n);
	//printResult(p_SJF, n);

	printf("HRN 最高响应比\n");
	HRN(p_HRN, n);
	//printResult(p_HRN, n);

	return 0;
}
