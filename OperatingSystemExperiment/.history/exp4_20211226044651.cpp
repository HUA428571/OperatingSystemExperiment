#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdlib.h>
#include <time.h>
#define MANE_SIZE 127
#define MAX_TIME_USE 120    //最长作业所用时间
#define MAX_TIME_ARRIVE 240 //最长作业开始时间
#define max 50

struct PCB
{
    int number;           //进程号
    char name[MANE_SIZE]; //进程名
    int time_arrive;      //到达时间
    int time_use;         //所需时间

    int number_go;     //执行次序
    int time_start;    //开始时间
    int time_turn;     //周转时间
    float time_turn_w; //带权周转时间

    bool sign_finished = false; //是否已经完成

    float turntime;         //周转时间
    float average_turntime; //带权周转时间
    int sign;               //标志进程是否完成
    int remain_time;        //剩余时间
    int priority;           //优先级
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
    for (;;)
    {
        pcb_next = -1;
        for (int i = 0; i < n; i++)
        {
            if (p[i].time_arrive <= time_now && !p[i].sign_finished)
            {
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
        if (pcb_next == -1)
        {
            time_now++;
        }
        else
        {
            p[pcb_next].sign_finished = true;
            p[pcb_next].time_start = time_now;
            p[pcb_next].number_go = number_go;
            p[pcb_next].time_turn = time_now - p[pcb_next].time_arrive + p[pcb_next].time_use;
            p[pcb_next].time_turn_w = p[pcb_next].time_turn / p[pcb_next].time_use;

            time_now += p[pcb_next].time_use;
            number_go++;
        }
        if (number_go == n)
            break;
    }

    // int starttime;
    // printf("input the start time：\n");
    // scanf("%d", &starttime);
    // if (starttime >= pcb[1].time_arrive)
    // {
    //     pcb[1].time_start = pcb[1].time_use + starttime;
    // }
    // else
    // {
    //     pcb[1].time_start = pcb[1].time_arrive + pcb[1].time_use;
    // }
    // int i;
    // for (i = 2; i <= n; i++)
    // {
    //     if (pcb[i - 1].time_start > pcb[i].time_arrive)
    //         pcb[i].time_start = pcb[i - 1].time_start + pcb[i].time_use;
    //     else
    //         pcb[i].time_start = pcb[i].time_arrive + pcb[i].time_use;
    //     pcb[i].turntime = pcb[i].time_start - pcb[i].time_arrive;
    //     pcb[i].average_turntime = pcb[i].turntime / pcb[i].time_use;
    // }
}
void print_FCFS(int n) //先来先服务的打印
{
    // printf("name arrivetime servicetime fihishtime turntime averageturntime\n");
    // int i;
    // for (i = 1; i <= n; i++)
    // {
    // 	printf("%d\t%d\t%d\t%d\t%f\t%f", pcb[i].name, pcb[i].time_arrive, pcb[i].time_use, pcb[i].time_start, pcb[i].turntime, pcb[i].average_turntime);
    // 	printf("\n");
    // }
}

void time_segment(int n) //时间片轮转
{
    // int i, j;
    // int T;   //时间片
    // int flag = 1;   //就绪队列中是否还有进程
    // //int time=pcb[0].arrivetime;   //当前的时间
    // int time = 0;
    // int sum = 0;   //已经完成的进程数

    // //按各进程的arrivetime进行升序排列
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
    // //初始化剩余时间
    // for (i = 1; i <= n; i++)
    // {
    // 	pcb[i].remain_time = pcb[i].time_use;
    // }
    // //printf("output the sort result:\n");
    // //for(i=1;i<=n;i++)    //检查排序是否正确
    // //printf("%d\t",pcb[i].name);
    // printf("input the slicetime:\n");
    // scanf("%d", &T);

    // while (sum < n)
    // {
    // 	flag = 0;   //当前就绪队列中没有进程
    // 	int i;
    // 	for (i = 1; i <= n; i++)
    // 	{
    // 		if (pcb[i].sign == 1) continue; //表示该进程已完成
    // 		else
    // 		{
    // 			if (time >= pcb[i].time_arrive)
    // 			{

    // 				//没有完成的进程需要的时间大于一个时间片
    // 				if (pcb[i].remain_time > T)
    // 				{
    // 					flag = 1;
    // 					time = time + T;
    // 					pcb[i].remain_time = pcb[i].remain_time - T;
    // 					//printf("%10d%16d%12d%12d%12d\n",pcb[i].name,time-T,T,pcb[i].remain_time,time);
    // 				}

    // 				//没有完成的进程需要的时间小于或等于一个时间片
    // 				else if (pcb[i].remain_time <= T)
    // 				{
    // 					flag = 1;  //加入就绪队列
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

    // 	if (flag == 0 && sum < n)   // 还有没执行的进程，且没进入就就绪队列
    // 	{
    // 		int i;
    // 		for (i = 1; i <= n; i++)
    // 			if (pcb[i].sign == 0) { time = pcb[i].time_arrive; break; }
    // 	}

    // }//while
    // //计算周转和带权周转
    // for (i = 1; i <= n; i++)
    // {
    // 	pcb[i].turntime = pcb[i].time_start - pcb[i].time_arrive;
    // 	pcb[i].average_turntime = pcb[i].turntime / pcb[i].time_use;
    // }
}
void print_time(int n) //时间片轮转输出
{
    // int i;
    // printf("\n name arrivetime servicetime fihishtime turntime averageturntime\n");
    // for (i = 1; i <= n; i++)
    // {
    // 	printf("%d\t%d\t%d\t%d\t%f\t%f", pcb[i].name, pcb[i].time_arrive, pcb[i].time_use, pcb[i].time_start, pcb[i].turntime, pcb[i].average_turntime);
    // 	printf("\n");
    // }
}

void Priority(int n) //优先级优先级小的先输出，排序计算加打印
{
    // int i, j;
    // int time = pcb[1].time_arrive;
    // //按各进程的priority进行升序排列,优先级最高的进程先执行
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
    // //printf("output the sort result: \n"); //输出排序结果
    // //for(i=1;i<=n;i++)    //检查排序是否正确
    // //printf("%d\t",pcb[i].name);

    // printf("\n name arrivetime servicetime priority fihishtime turntime averageturntime\n");//进程名 到达时间  服务时间   优先级  完成时间
    // //先到达的进程第一个执行
    // if (i = 1)
    // {
    // 	pcb[i].time_start = pcb[i].time_arrive + pcb[i].time_use;
    // 	time = pcb[i].time_arrive + pcb[i].time_use;
    // 	pcb[i].turntime = pcb[i].time_start - pcb[i].time_arrive;
    // 	pcb[i].average_turntime = pcb[i].turntime / pcb[i].time_use;
    // 	printf("%d\t%d\t%d\t%d\t%d\t%f\t%f", pcb[i].name, pcb[i].time_arrive, pcb[i].time_use, pcb[i].priority, pcb[i].time_start, pcb[i].turntime, pcb[i].average_turntime);
    // 	printf("\n");
    // 	//测试第一个进程输出正确
    // 	/*	printf("output the first process:\n");//输出第一个程序的
    // 	printf("processID arrivetime finishtime\n");//名称  到达时间  完成时间
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

void SJF(int n) //短作业优先算法
{
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
    // printf("\n name arrivetime servicetime fihishtime turntime averageturntime\n");//进程名   服务时间   优先级  完成时间
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

void layout(int n) //选择端口
{
    // int ch = 0;
    // printf("\n\t\t************schedule algorithm************\n");
    // printf("\t\t1.FSFS\n");
    // printf("\t\t2.timesegment\n");
    // printf("\t\t3.priority\n");
    // printf("\t\t4.SJF\n");
    // printf(" choose the algorithm:\n");
    // //选择端口
    // scanf("%10d", &ch);
    // switch (ch)
    // {
    // case 1:
    // 	FCFS(n);
    // 	print_FCFS(n); break;
    // case 2:
    // 	time_segment(n);
    // 	print_time(n); break;
    // case 3:
    // 	Priority(n); break;
    // case 4:
    // 	SJF(n); break;
    // default:printf("enter error data!\n");
    // 	//P:int类型的变量,case后面不要加''
    // }
}

void printPCB(PCB p[], int n)
{
    printf("本次实验生成的进程有：\n");
    printf("进程号\t进入时间\t运行时间\t开始时间\t结束时间\t周转时间\t带权周转时间\t\t\t\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t\t%d\n", p[i].number, p[i].time_arrive, p[i].time_use);
    }
}
void printResult(PCB p[], int n)
{
    printf("运行次序：\n");
    printf("次序\t进程号\t进入时间\t运行时间\t开始时间\t结束时间\t周转时间\t带权周转时间\t\t\t\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (p[j].number_go == i)
            {
                printf("%d\t%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%f\n",
                       i+1, p[j].number, p[j].time_arrive, p[j].time_use, p[j].time_start,
                       p[j].time_start + p[j].time_use, p[j].time_turn, p[j].time_turn_w);
            }
            else
            {
                continue;
            }
        }
    }
}

int main()
{
    int n;
    printf("请输入需要生成的进程数:");
    scanf("%d", &n);
    PCB *p = (PCB *)malloc(sizeof(PCB) * n);
    init(n, p);
    printPCB(p, n);

    FCFS(p, n);
    printResult(p, n);

    // int n;
    // //填上n
    // FILE* in1 = fopen("input1.txt", "r");
    // if (in1) {
    // 	fscanf(in1, "%d", &n);
    // 	fclose(in1);
    // }
    // else {
    // 	printf("打开失败");
    // }
    // printf("n输入完成,n=%d\n\n", n);
    // init(n);
    // creat(n);
    // layout(n);
    // system("pause");
}
