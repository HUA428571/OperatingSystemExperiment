#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_PAGE_NUM 8		 //���ҳ���
#define ARRAY_LIST_LENGTH 50 //ҳ�����е�����
#define PHYSICAL_BLOCK_NUM 5

//ɨ������飬�����򷵻�λ�ã�����-1
int scan_block(int find, int block[])
{
	for (int i = 0; i < PHYSICAL_BLOCK_NUM; i++)
	{
		if (block[i] == -1)
		{
			block[i] = find;
			return i;
		}
		if (block[i] == find)
			return i;
	}
	return -1;
}
int find_far_use(int find_now, int block[], int list[])
{
	int far_counter = 0;	 //����ʵ�ʱ��
	int far_counter_now = 0; //��ǰ���������ʵ�ʱ��
	int far = -1;			 //����ʵ�ʱ����ҳ��
	for (int i = 0; i < PHYSICAL_BLOCK_NUM; i++)
	{
		far_counter_now = 0;
		for (int j = find_now + 1; j < ARRAY_LIST_LENGTH; j++)
		{
			if (block[i] != list[j])
				far_counter_now++;
			else
				break;
		}
		if (far_counter_now > far_counter)
		{
			far_counter = far_counter_now;
			far = i;
		}
	}
	return far;
}
int find_early(int block_counter[])
{
	int early = 0;
	for (int i = 1; i < PHYSICAL_BLOCK_NUM; i++)
	{
		if (block_counter[early] < block_counter[i])
			early = i;
	}
	return early;
}
int find_less_frequent(int block_counter[])
{
	int frequent = 0;
	for (int i = 1; i < PHYSICAL_BLOCK_NUM; i++)
	{
		if (block_counter[frequent] > block_counter[i])
			frequent = i;
	}
	return frequent;
}

void print_block(int block[])
{
	for (int i = 0; i < PHYSICAL_BLOCK_NUM; i++)
	{
		if (block[i] == -1)
		{
			printf("N/A\t");
		}
		else
		{
			printf(" %d\t", block[i]);
		}
	}
}

//int max(int a[], int PHYSICAL_BLOCK_NUM)
//{ //��������a�����Ԫ�صĵ�ַ
//	int temp = 0;
//	for (int i = 1; i < PHYSICAL_BLOCK_NUM; i++)
//	{
//		if (a[i] > a[temp])
//			temp = i;
//	}
//	return temp;
//}
//
//int min(int a[], int PHYSICAL_BLOCK_NUM)
//{ //��������a����СԪ�صĵ�ַ
//	int temp = 0;
//	for (int i = 1; i < PHYSICAL_BLOCK_NUM; i++)
//	{
//		if (a[i] < a[temp])
//			temp = i;
//	}
//	return temp;
//}

//����û��㷨
void OPT(int list[ARRAY_LIST_LENGTH])
{
	printf("����ҳ��\t");
	for (int i = 0; i < PHYSICAL_BLOCK_NUM; i++)
	{
		printf("��%d\t", i);
	}
	printf("\n");

	int block[PHYSICAL_BLOCK_NUM];
	//��ʼ�������
	for (int i = 0; i < PHYSICAL_BLOCK_NUM; i++)
		block[i] = -1;
	int exchange_counter = 0; //�û�������
	for (int i = 0; i < ARRAY_LIST_LENGTH; i++)
	{
		printf("   %d\t\t", list[i]); //��ǰ����ҳ��
		int block_exchange = scan_block(list[i], block);
		if (block_exchange == -1)
		{
			exchange_counter++;
			block_exchange = find_far_use(i, block, list);
			block[block_exchange] = list[i];
			print_block(block);
			printf("�û���%d\n", block_exchange);
		}
		else
		{
			print_block(block);
			block[block_exchange] = list[i];
			printf("�ɹ�\n");
		}
	}
	printf("ȱҳ����Ϊ%d���û���Ϊ%.0f%%\n", exchange_counter, ((float)exchange_counter / ARRAY_LIST_LENGTH) * 100);
	return;
}

//�Ƚ��ȳ��û��㷨
void FIFO(int list[ARRAY_LIST_LENGTH])
{
	printf("����ҳ��\t");
	for (int i = 0; i < PHYSICAL_BLOCK_NUM; i++)
	{
		printf("��%d\t", i);
	}
	printf("\n");

	int block[PHYSICAL_BLOCK_NUM];
	int block_counter[PHYSICAL_BLOCK_NUM];

	//��ʼ�������
	for (int i = 0; i < PHYSICAL_BLOCK_NUM; i++)
	{
		block[i] = -1;
		block_counter[i] = 0;
	}

	int exchange_counter = 0; //�û�������
	for (int i = 0; i < ARRAY_LIST_LENGTH; i++)
	{
		printf("   %d\t\t", list[i]); //��ǰ����ҳ��
		int block_exchange = scan_block(list[i], block);
		if (block_exchange == -1)
		{
			exchange_counter++;
			block_exchange = find_early(block_counter);
			for (int i = 0; i < PHYSICAL_BLOCK_NUM; i++)
			{
				block_counter[i]++;
			}
			block_counter[block_exchange] = 0;

			block[block_exchange] = list[i];
			print_block(block);
			printf("�û���%d\n", block_exchange);
		}
		else
		{
			for (int i = 0; i < PHYSICAL_BLOCK_NUM; i++)
			{
				block_counter[i]++;
			}
			//block_counter[block_exchange] = 0;

			print_block(block);
			block[block_exchange] = list[i];
			printf("�ɹ�\n");
		}
	}
	printf("ȱҳ����Ϊ%d���û���Ϊ%.0f%%\n", exchange_counter, ((float)exchange_counter / ARRAY_LIST_LENGTH) * 100);
	return;
}

//������δʹ���û��㷨
void LRU(int list[ARRAY_LIST_LENGTH])
{
	printf("����ҳ��\t");
	for (int i = 0; i < PHYSICAL_BLOCK_NUM; i++)
	{
		printf("��%d\t", i);
	}
	printf("\n");

	int block[PHYSICAL_BLOCK_NUM];
	int block_counter[PHYSICAL_BLOCK_NUM];

	//��ʼ�������
	for (int i = 0; i < PHYSICAL_BLOCK_NUM; i++)
	{
		block[i] = -1;
		block_counter[i] = 0;
	}

	int exchange_counter = 0; //�û�������
	for (int i = 0; i < ARRAY_LIST_LENGTH; i++)
	{
		printf("   %d\t\t", list[i]); //��ǰ����ҳ��
		int block_exchange = scan_block(list[i], block);
		if (block_exchange == -1)
		{
			exchange_counter++;
			block_exchange = find_early(block_counter);
			for (int i = 0; i < PHYSICAL_BLOCK_NUM; i++)
			{
				block_counter[i]++;
			}
			block_counter[block_exchange] = 0;

			block[block_exchange] = list[i];
			print_block(block);
			printf("�û���%d\n", block_exchange);
		}
		else
		{
			for (int i = 0; i < PHYSICAL_BLOCK_NUM; i++)
			{
				block_counter[i]++;
			}
			block_counter[block_exchange] = 0;

			print_block(block);
			block[block_exchange] = list[i];
			printf("�ɹ�\n");
		}
	}
	printf("ȱҳ����Ϊ%d���û���Ϊ%.0f%%\n", exchange_counter, ((float)exchange_counter / ARRAY_LIST_LENGTH) * 100);
	return;
}

//����ʹ���û��㷨
void LFU(int list[ARRAY_LIST_LENGTH])
{
	printf("����ҳ��\t");
	for (int i = 0; i < PHYSICAL_BLOCK_NUM; i++)
	{
		printf("��%d\t", i);
	}
	printf("\n");

	int block[PHYSICAL_BLOCK_NUM];
	int block_counter[PHYSICAL_BLOCK_NUM];

	//��ʼ�������
	for (int i = 0; i < PHYSICAL_BLOCK_NUM; i++)
	{
		block[i] = -1;
		block_counter[i] = 0;
	}

	int exchange_counter = 0; //�û�������
	for (int i = 0; i < ARRAY_LIST_LENGTH; i++)
	{
		printf("   %d\t\t", list[i]); //��ǰ����ҳ��
		int block_exchange = scan_block(list[i], block);
		if (block_exchange == -1)
		{
			exchange_counter++;
			block_exchange = find_less_frequent(block_counter);
			for (int i = 0; i < PHYSICAL_BLOCK_NUM; i++)
			{
				block_counter[i] = 0;
			}
			block_counter[block_exchange]++;

			block[block_exchange] = list[i];
			print_block(block);
			printf("�û���%d\n", block_exchange);
		}
		else
		{
			for (int i = 0; i < PHYSICAL_BLOCK_NUM; i++)
			{
				block_counter[i] = 0;
			}
			block_counter[block_exchange]++;

			print_block(block);
			block[block_exchange] = list[i];
			printf("�ɹ�\n");
		}
	}
	printf("ȱҳ����Ϊ%d���û���Ϊ%.0f%%\n", exchange_counter, ((float)exchange_counter / ARRAY_LIST_LENGTH) * 100);
	return;
}

void init(int list[ARRAY_LIST_LENGTH])
{
	srand((unsigned)time(NULL));
	for (int i = 0; i < ARRAY_LIST_LENGTH; i++)
	{
		list[i] = rand() % MAX_PAGE_NUM;
	}
	printf("���������·������У�\n");
	for (int i = 0; i < ARRAY_LIST_LENGTH; i++)
		printf("%d,", list[i]);
	printf("\n");
}

int main()
{
	int list[ARRAY_LIST_LENGTH];
	init(list);

	printf("OPT ����û��㷨\n");
	printf("-----------------------------------------------------------------------\n");
	OPT(list);
	printf("\n");

	printf("FIFO �Ƚ��ȳ��û��㷨\n");
	printf("-----------------------------------------------------------------------\n");
	FIFO(list);
	printf("\n");

	printf("LRU ������δʹ���û��㷨\n");
	printf("-----------------------------------------------------------------------\n");
	LRU(list);
	printf("\n");

	printf("LFU ����ʹ���û��㷨\n");
	printf("-----------------------------------------------------------------------\n");
	LFU(list);
	printf("\n");
}
