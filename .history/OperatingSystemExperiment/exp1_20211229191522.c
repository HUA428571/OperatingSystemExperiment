#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define PAGE_SIZE 10 //���ҳ���
#define PAGE_NUM 20 //ҳ�����е�����


int PAGE_NUM;  //ҳ�����е�����
int t;		   //��¼��ǰ����ҳ�����

int scan_page_position(int a, int page[])
{ //������ǰҳ��֮��ҳ��a��������������ֵ�λ��
	for (int i = t + 1; i < PAGE_NUM; i++)
	{
		if (page[i] == a)
			return i;
	}
	return 99;
}

int scan_page_preposition(int a, int page[])
{ //������ǰҳ��֮ǰ��ҳ��a�������������ֵ�λ��
	for (int i = t - 1; i >= 0; i--)
	{
		if (page[i] == a)
			return i;
	}
	return -99;
}

int scan_block_position(int a, int block[], int BLOCK_SIZE)
{ //����ҳ��a�Ƿ����������,������λ��
	for (int i = 0; i < BLOCK_SIZE; i++)
	{
		if (block[i] == a)
			return i;
	}
	return -1;
}

int max(int a[], int BLOCK_SIZE)
{ //��������a�����Ԫ�صĵ�ַ
	int temp = 0;
	for (int i = 1; i < BLOCK_SIZE; i++)
	{
		if (a[i] > a[temp])
			temp = i;
	}
	return temp;
}

int min(int a[], int BLOCK_SIZE)
{ //��������a����СԪ�صĵ�ַ
	int temp = 0;
	for (int i = 1; i < BLOCK_SIZE; i++)
	{
		if (a[i] < a[temp])
			temp = i;
	}
	return temp;
}

//����û��㷨
int OPT(int BLOCK_SIZE, int page[])
{
	int block[BLOCK_SIZE];
	t = 0;
	for (int i = 0; i < BLOCK_SIZE; i++)
		block[i] = -1;
	printf("\n-----------------------OPT  �������=%d-----------------------\n", BLOCK_SIZE);
	int count = 0;	//ȱҳ������
	int count2 = 0; //�û�������
	while (t < PAGE_NUM)
	{
		if (scan_block_position(page[t], block, BLOCK_SIZE) != -1)
		{
			printf("ҳ��%d���������,��ǰ�����Ϊ", page[t]); //����������ҵ�ҳ�棬�����û�
			for (int i = 0; i < BLOCK_SIZE; i++)
				printf("%d ", block[i]);
			printf("\n");
		}
		else
		{
			if (scan_block_position(-1, block, BLOCK_SIZE) != -1)
			{ //�����������пտ飬��ôֱ��װ��ҳ��
				block[scan_block_position(-1, block, BLOCK_SIZE)] = page[t];
				count++;
				printf("װ��ҳ��%d,��ǰ�����Ϊ", page[t]);
				for (int i = 0; i < BLOCK_SIZE; i++)
					printf("%d ", block[i]);
				printf("\n");
			}
			else
			{
				int position[BLOCK_SIZE]; //�û��㷨��Ѱ��δ�����δʹ�õ�ҳ�棬�����û�
				for (int i = 0; i < BLOCK_SIZE; i++)
					position[i] = scan_page_position(block[i], page);
				int temp = max(position, BLOCK_SIZE);
				printf("ҳ��%d����������У���%d����,", page[t], block[temp]);
				block[temp] = page[t];
				printf("��ǰ�����Ϊ");
				for (int i = 0; i < BLOCK_SIZE; i++)
					printf("%d ", block[i]);
				printf("\n");
				count++;
				count2++;
			}
		}
		t++;
	}
	printf("ȱҳ����Ϊ%d��ȱҳ��Ϊ%.0f%%���û���Ϊ%.0f%%\n", count, (float)count / PAGE_NUM * 100, (float)count2 / PAGE_NUM * 100);
	return count;
}

//�Ƚ��ȳ��û��㷨
int FIFO(int BLOCK_SIZE, int page[])
{
	int block[BLOCK_SIZE];
	t = 0;
	for (int i = 0; i < BLOCK_SIZE; i++)
		block[i] = -1;
	printf("\n-----------------------FIFO  �������=%d-----------------------\n", BLOCK_SIZE);
	int temp = 0;	//���������У�˳���û�
	int count = 0;	//ȱҳ������
	int count2 = 0; //�û�������
	while (t < PAGE_NUM)
	{
		if (scan_block_position(page[t], block, BLOCK_SIZE) != -1)
		{
			printf("ҳ��%d���������,��ǰ�����Ϊ", page[t]); //����������ҵ�ҳ�棬�����û�
			for (int i = 0; i < BLOCK_SIZE; i++)
				printf("%d ", block[i]);
			printf("\n");
		}
		else
		{
			if (block[temp % BLOCK_SIZE] == -1)
			{
				block[temp % BLOCK_SIZE] = page[t];
				count++;
				temp++;
				printf("װ��ҳ��%d,��ǰ�����Ϊ", page[t]); //�����������пտ飬��ôֱ��װ��ҳ��
				for (int i = 0; i < BLOCK_SIZE; i++)
					printf("%d ", block[i]);
				printf("\n");
			}
			else
			{
				printf("ҳ��%d����������У���%d����,", page[t], block[temp % BLOCK_SIZE]); //�û�ҳ�棬������װ���ҳ���û�
				block[temp % BLOCK_SIZE] = page[t];
				temp++;
				printf("��ǰ�����Ϊ");
				for (int i = 0; i < BLOCK_SIZE; i++)
					printf("%d ", block[i]);
				printf("\n");
				count++;
				count2++;
			}
		}
		t++;
	}
	printf("ȱҳ����Ϊ%d��ȱҳ��Ϊ%.0f%%���û���Ϊ%.0f%%\n", count, (float)count / PAGE_NUM * 100, (float)count2 / PAGE_NUM * 100);
	return count;
}

//������δʹ���û��㷨
int LRU(int BLOCK_SIZE, int page[])
{
	int block[BLOCK_SIZE];
	t = 0;
	for (int i = 0; i < BLOCK_SIZE; i++)
		block[i] = -1;
	printf("\n-----------------------LRU  �������=%d-----------------------\n", BLOCK_SIZE);
	int count = 0;	//ȱҳ������
	int count2 = 0; //�û�������
	while (t < PAGE_NUM)
	{
		if (scan_block_position(page[t], block, BLOCK_SIZE) != -1)
		{
			printf("ҳ��%d���������,��ǰ�����Ϊ", page[t]); //����������ҵ�ҳ�棬�����û�
			for (int i = 0; i < BLOCK_SIZE; i++)
				printf("%d ", block[i]);
			printf("\n");
		}
		else
		{
			if (scan_block_position(-1, block, BLOCK_SIZE) != -1)
			{
				block[scan_block_position(-1, block, BLOCK_SIZE)] = page[t];
				count++;
				printf("װ��ҳ��%d,��ǰ�����Ϊ", page[t]); //�����������пտ飬��ôֱ��װ��ҳ��
				for (int i = 0; i < BLOCK_SIZE; i++)
					printf("%d ", block[i]);
				printf("\n");
			}
			else
			{
				int position[BLOCK_SIZE]; //�û�ҳ�棬Ѱ��������δʹ�õ�ҳ�棬�����û�
				for (int i = 0; i < BLOCK_SIZE; i++)
					position[i] = scan_page_preposition(block[i], page);
				int temp = min(position, BLOCK_SIZE);

				printf("ҳ��%d����������У���%d����,", page[t], block[temp]);
				block[temp] = page[t];
				printf("��ǰ�����Ϊ");
				for (int i = 0; i < BLOCK_SIZE; i++)
					printf("%d ", block[i]);
				printf("\n");
				count++;
				count2++;
			}
		}
		t++;
	}
	printf("ȱҳ����Ϊ%d��ȱҳ��Ϊ%.0f%%���û���Ϊ%.0f%%\n", count, (float)count / PAGE_NUM * 100, (float)count2 / PAGE_NUM * 100);
	return count;
}

//����ʹ���û��㷨
int LFU(int BLOCK_SIZE, int page[])
{
	int block[BLOCK_SIZE];
	t = 0;
	for (int i = 0; i < BLOCK_SIZE; i++)
		block[i] = -1;
	printf("\n-----------------------LFU  �������=%d-----------------------\n", BLOCK_SIZE);
	int count = 0;		  //ȱҳ������
	int count2 = 0;		  //�û�������
	int usage[PAGE_SIZE]; //���ʹ�ô���������
	for (int i = 0; i < PAGE_SIZE; i++)
		usage[i] = 0;
	while (t < PAGE_NUM)
	{
		if (scan_block_position(page[t], block, BLOCK_SIZE) != -1)
		{
			printf("ҳ��%d���������,��ǰ�����Ϊ", page[t]); //����������ҵ�ҳ�棬�����û�
			for (int i = 0; i < BLOCK_SIZE; i++)
				printf("%d ", block[i]);
			printf("\n");
			usage[scan_block_position(page[t], block, BLOCK_SIZE)]++;
		}
		else
		{
			if (scan_block_position(-1, block, BLOCK_SIZE) != -1)
			{
				block[scan_block_position(-1, block, BLOCK_SIZE)] = page[t];
				usage[page[t]]++;
				count++;
				printf("װ��ҳ��%d,��ǰ�����Ϊ", page[t]); //�����������пտ飬��ôֱ��װ��ҳ��
				for (int i = 0; i < BLOCK_SIZE; i++)
					printf("%d ", block[i]);
				printf("\n");
			}
			else
			{
				int num[BLOCK_SIZE]; //Ѱ�����ʹ�ô������ٵ�ҳ�棬�����û�
				for (int i = 0; i < BLOCK_SIZE; i++)
					num[i] = usage[block[i]];
				int temp = min(num, BLOCK_SIZE);

				printf("ҳ��%d����������У���%d����,", page[t], block[temp]);
				block[temp] = page[t];
				usage[page[t]]++;
				printf("��ǰ�����Ϊ");
				for (int i = 0; i < BLOCK_SIZE; i++)
					printf("%d ", block[i]);
				printf("\n");
				count++;
				count2++;
			}
		}
		t++;
	}
	printf("ȱҳ����Ϊ%d��ȱҳ��Ϊ%.0f%%���û���Ϊ%.0f%%\n", count, (float)count / PAGE_NUM * 100, (float)count2 / PAGE_NUM * 100);
	return count;
}

int draw(int point[], int PAGE_NUM)
{ //��������ɢ��ͼ
	char aa[PAGE_NUM][28];
	for (int i = 2; i <= 8; i++)
		aa[PAGE_NUM - point[i]][4 * (i - 1) - 1] = '*';
	printf("\n               ����ɢ��ͼ\n");
	printf(" ȱҳ����\n");
	for (int i = 0; i < PAGE_NUM; i++)
	{
		if (i <= PAGE_NUM - 10)
			printf(" %d |", PAGE_NUM - i);
		else
			printf("  %d |", PAGE_NUM - i);
		for (int j = 0; j < 28; j++)
		{
			if (aa[i][j] == '*')
				printf("*");
			else
				printf(" ");
		}
		printf("\n");
	}
	printf("    ");
	for (int i = 0; i < 8; i++)
		printf("----");
	printf(" �����\n        ");
	for (int i = 2; i <= 8; i++)
		printf("%d   ", i);
	printf("\n");
}

int main()
{
	srand((int)time(0)); //Ϊ�˱�֤��������������������
	printf("������ҳ��Ŵ�С:");
	scanf("%d", &PAGE_SIZE);
	printf("������ҳ����������:");
	scanf("%d", &PAGE_NUM);
	int page[PAGE_NUM];
	for (int i = 0; i < PAGE_NUM; i++)
		page[i] = rand() % PAGE_SIZE; //�������ҳ������
	printf("\n������ɵ�ҳ������Ϊ"); //��ӡҳ������
	for (int i = 0; i < PAGE_NUM; i++)
		printf("%d ", page[i]);
	printf("\n");
	//ģ��6��ҳ���û��㷨��ÿ���㷨��������С2-8�ֱ�ģ�⣬����ȱҳ��
	int lack_page_count[9]; //�洢��ͬ������ȱҳ�������������ܷ���
	for (int i = 0; i < 9; i++)
		lack_page_count[i] = 0; //��ʼ��

	for (int i = 2; i <= 8; i++)
		lack_page_count[i] = OPT(i, page);
	draw(lack_page_count, PAGE_NUM);
	system("pause");

	for (int i = 2; i <= 8; i++)
		lack_page_count[i] = FIFO(i, page);
	draw(lack_page_count, PAGE_NUM);
	system("pause");

	for (int i = 2; i <= 8; i++)
		lack_page_count[i] = LRU(i, page);
	draw(lack_page_count, PAGE_NUM);
	system("pause");

	for (int i = 2; i <= 8; i++)
		lack_page_count[i] = LFU(i, page);
	draw(lack_page_count, PAGE_NUM);
	system("pause");

	for (int i = 2; i <= 8; i++)
		lack_page_count[i] = CLOCK(i, page);
	draw(lack_page_count, PAGE_NUM);
	system("pause");

	for (int i = 2; i <= 8; i++)
		lack_page_count[i] = CLOCK_advanced(i, page);
	draw(lack_page_count, PAGE_NUM);
	system("pause");
}
