#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdlib.h>
#include <time.h>
#define MANE_SIZE 127
#define MAX_TIME_USE 120    //���ҵ����ʱ��
#define MAX_TIME_ARRIVE 240 //���ҵ��ʼʱ��
#define max 50

struct PCB
{
    int number;           //���̺�
    char name[MANE_SIZE]; //������
    int time_arrive;      //����ʱ��
    int time_use;         //����ʱ��

    int number_go;     //ִ�д���
    int time_start;    //��ʼʱ��
    int time_turn;     //��תʱ��
    float time_turn_w; //��Ȩ��תʱ��

    bool sign_finished = false; //�Ƿ��Ѿ����

    float turntime;         //��תʱ��
    float average_turntime; //��Ȩ��תʱ��
    int sign;               //��־�����Ƿ����
    int remain_time;        //ʣ��ʱ��
    int priority;           //���ȼ�
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
    for (;;)
    {
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
                    //�Ƚ��䵽��ʱ��
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
    // printf("input the start time��\n");
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
void print_FCFS(int n) //�����ȷ���Ĵ�ӡ
{
    // printf("name arrivetime servicetime fihishtime turntime averageturntime\n");
    // int i;
    // for (i = 1; i <= n; i++)
    // {
    // 	printf("%d\t%d\t%d\t%d\t%f\t%f", pcb[i].name, pcb[i].time_arrive, pcb[i].time_use, pcb[i].time_start, pcb[i].turntime, pcb[i].average_turntime);
    // 	printf("\n");
    // }
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

void SJF(int n) //����ҵ�����㷨
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

void layout(int n) //ѡ��˿�
{
    // int ch = 0;
    // printf("\n\t\t************schedule algorithm************\n");
    // printf("\t\t1.FSFS\n");
    // printf("\t\t2.timesegment\n");
    // printf("\t\t3.priority\n");
    // printf("\t\t4.SJF\n");
    // printf(" choose the algorithm:\n");
    // //ѡ��˿�
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
    // 	//P:int���͵ı���,case���治Ҫ��''
    // }
}

void printPCB(PCB p[], int n)
{
    printf("����ʵ�����ɵĽ����У�\n");
    printf("���̺�\t����ʱ��\t����ʱ��\t��ʼʱ��\t����ʱ��\t��תʱ��\t��Ȩ��תʱ��\t\t\t\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t\t%d\n", p[i].number, p[i].time_arrive, p[i].time_use);
    }
}
void printResult(PCB p[], int n)
{
    printf("���д���\n");
    printf("����\t���̺�\t����ʱ��\t����ʱ��\t��ʼʱ��\t����ʱ��\t��תʱ��\t��Ȩ��תʱ��\t\t\t\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (p[j].number_go == i)
            {
                printf("%d\t%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%f\n",
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
    printf("��������Ҫ���ɵĽ�����:");
    scanf("%d", &n);
    PCB *p = (PCB *)malloc(sizeof(PCB) * n);
    init(n, p);
    printPCB(p, n);

    FCFS(p, n);
    printResult(p, n);

    // int n;
    // //����n
    // FILE* in1 = fopen("input1.txt", "r");
    // if (in1) {
    // 	fscanf(in1, "%d", &n);
    // 	fclose(in1);
    // }
    // else {
    // 	printf("��ʧ��");
    // }
    // printf("n�������,n=%d\n\n", n);
    // init(n);
    // creat(n);
    // layout(n);
    // system("pause");
}
