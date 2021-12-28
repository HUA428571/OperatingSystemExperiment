#include<iostream>
using namespace std;

int n, m; //ϵͳ�н�������n����Դ��������m
int total[100]; //��Դ��������
int max_need[100][100];  //����������
int resource[100][100] = { 0 }; //��ǰ�������ÿ�����̵ĸ�����Դ����
int need[100][100];//��ǰÿ�����̻������ĸ�����Դ����
int resouce_to_allocate[100]; //��ǰ�ɷ������Դ
bool finish[100]; //�����Ƿ����

//��ʾ����
void show_function()
{
	cout << "\n\n�����б�" << endl;
	cout << "1.��ʾ��ǰ��Դ���" << endl;
	cout << "2.��ǰ״̬��ȫ���" << endl;
	cout << "3.������Դ����" << endl;
	cout << "4.�˳�����\n" << endl;
	return;
}

//��ʼ��
void initial()
{
	cout << "�������������" << endl;
	cin >> n;
	cout << "��������Դ����" << endl;
	cin >> m;
	cout << "���������������Դ������" << endl;
	for (int i = 0; i < m; i++)
	{
		cin >> total[i];
	}
	for (int i = 0; i < n; i++)
	{
		cout << "�������" << i << "�ĳ�ʼ��Ϣ" << endl;
		cout << "������ý����������Դ���������" << endl;
		for (int j = 0; j < m; j++)
		{
			cin >> max_need[i][j];
		}
		cout << "������ý����ѷ������Դ��������" << endl;
		for (int j = 0; j < m; j++)
		{
			cin >> resource[i][j];
		}
	}
	return;
}

//��ʾ��ǰ��Դ���
void show()
{

	cout << "\n***   ��ǰ��Դ�������   ***" << endl;
	cout << "����";
	for (int i = 0; i < m; i++)
	{
		cout << "\t��Դ" << i;
	}
	cout << endl;
	for (int i = 0; i < n; i++)
	{
		cout << i;
		for (int j = 0; j < m; j++)
		{
			cout << "\t" << resource[i][j];
		}
		cout << endl;
	}

	cout << "\n��ǰ��Դ���������" << endl;
	cout << "����";
	for (int i = 0; i < m; i++)
	{
		cout << "\t��Դ" << i;
	}
	cout << endl;
	for (int i = 0; i < n; i++)
	{
		cout << i;
		for (int j = 0; j < m; j++)
		{
			cout << "\t" << need[i][j];
		}
		cout << endl;
	}

	cout << "\n��ǰ��Դʣ�������" << endl;
	for (int i = 0; i < m; i++)
	{
		cout << "��Դ" << i << "\t";
	}
	cout << endl;
	for (int j = 0; j < m; j++)
	{
		cout << total[j] << "\t";
	}
	cout << endl;
	//�������ִ�����
	cout << "\n��ǰ����ִ�������" << endl;
	for (int i = 0; i < n; i++)
	{
		cout << "����" << i << "\t";
	}
	cout << endl;
	for (int j = 0; j < n; j++)
	{
		if (finish[j])
		{
			cout << "true" << "\t";
		}
		else
		{
			cout << "false" << "\t";
		}
	}
	cout << endl;
}

//�ж��Ƿ����н�����ִ�н���
bool judge_end(bool* finish)
{
	bool flag = 1;
	for (int i = 0; i < m; i++)
	{
		if (finish[i] != true)
		{
			flag = 0;
			break;
		}
	}
	return flag;
}

//��ȫ���
void safety(int* result)
{
	int ji = 1;
	//��ʼ��
	for (int i = 0; i < m; i++)
	{
		resouce_to_allocate[i] = total[i];
	}
	//��ʼ��finish��finish���ڱ��β����б���ǲ������н��̶�ִ����
	bool finish[100];
	for (int i = 0; i < n; i++)
	{
		finish[i] = finish[i];
	}
	int flag1 = 0;
	bool flag2 = 1;
	for (int i = 0; i < n; i++)
	{
		//��ѭ���¿�ʼʱ��������ѭ����ǰ��û�н����κν���
		if (i == 0)
			flag1 = 0;
		//�����Ѿ���ɵĽ���
		if (finish[i] == true)
			continue;
		//Work��Need�Ƚ�
		int flag3 = 1;
		for (int j = 0; j < m; j++)
		{
			if (resouce_to_allocate[j] < need[i][j])
			{
				flag3 = 0;
				break;
			}
		}
		//����Դ������������һ����
		if (flag3 != 1)
		{
			//�ǲ��Ǳ���ѭ������һ����û�ܽ���
			if (i == n - 1 && flag1 != 1)
			{
				//����һ����û�ܽ�����ԭ��
				//�ǲ���ȫ�������Ѿ���ִ������
				if (judge_end(finish))
					break;
				else
				{
					//����û�����Ľ��̵��޷�����
					flag2 = 0;
					break;
				}
			}
			continue;
		}
		else
		{
			//����Դ������ִ����ý��̣��ͷŸý���ռ�õ���Դ
			result[ji] = i;
			ji++;
			for (int j = 0; j < m; j++)
			{
				resouce_to_allocate[j] = resouce_to_allocate[j] + resource[i][j];
			}
			finish[i] = true;
			flag1 = 1;//�����һ���ҵ��˿���ִ����Ľ���
			i = -1;//��ͷ�ٿ�ʼ�������̼���
		}
	}
	result[0] = flag2;
	return;
}

//��Դ����
bool allocate(int number, int* request)
{
	int flag = 1;
	for (int i = 0; i < m; i++)
	{
		if (request[i] > need[number][i])
		{
			flag = 0;
			break;
		}
	}
	if (flag == 0)
	{
		cout << "������ڸý���������Դ��" << endl;
		return 0;
	}
	flag = 1;
	for (int i = 0; i < m; i++)
	{
		if (request[i] > total[i])
		{
			flag = 0;
			break;
		}
	}
	if (flag == 0)
	{
		cout << "������ڵ�ǰϵͳʣ����Դ��" << endl;
		return 0;
	}

	// ���Է���
	for (int i = 0; i < m; i++)
	{
		need[number][i] = need[number][i] - request[i];
		resource[number][i] = resource[number][i] + request[i];
		total[i] = total[i] - request[i];
	}

	//��ȫ���ж�
	int* result = (int*)malloc(sizeof(int) * 101);
	memset(result, -1, sizeof(int) * 101);
	safety(result);
	if (result[0])
	{
		cout << "���ڰ�ȫ���У�";
		cout << result[1];
		for (int i = 2;; i++)
		{
			if (result[i] == -1)
			{
				break;
			}
			cout << " --> " << result[i];
		}
		cout << endl;
		return 1;
	}
	else
	{
		cout << "���η��䲻��ȫ" << endl;
		//��������
		for (int i = 0; i < m; i++)
		{
			need[number][i] = need[number][i] + request[i];
			resource[number][i] = resource[number][i] - request[i];
			total[i] = total[i] + request[i];
		}
		return 0;
	}
}

void end(int number)
{
	int flag = 1;
	for (int i = 0; i < m; i++)
	{
		if (need[number][i] != 0)
		{
			flag = 0;
			break;
		}
	}
	//�����������Ѿ�����Ҫ�ٷ�����Դ��
	//ִ����ý��̣��ͷ��ѷ�����Դ
	if (flag == 1)
	{
		cout << "����" << number << "�����" << endl;
		finish[number] = true;
		for (int i = 0; i < m; i++)
		{
			total[i] = total[i] + resource[number][i];
			resource[number][i] = 0;
		}
	}
}

int main()
{
	show_function();
	memset(finish, false, sizeof(finish));
	//��ʼ��������
	initial();
	//����Need�����ʣ��Ŀ���������ԴAvailable
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			need[i][j] = max_need[i][j] - resource[i][j];
			total[j] = total[j] - resource[i][j];
		}
	}


	int flag;
	while (true)
	{
		//����ѡ��
		show_function();
		cout << "��ѡ���ܣ�";
		cin >> flag;
		if (flag == 1)
		{
			//��ʾ��ǰ��Դ���
			//������ǰ��Դ�����������Դʣ�����
			show();
		}
		else if (flag == 2)
		{
			//��ǰ״̬��ȫ���
			int* result = (int*)malloc(sizeof(int) * 101);
			memset(result, -1, sizeof(int) * 101);
			safety(result);

			if (result[0] == 1)
			{
				cout << "���ڰ�ȫ���У�";
				cout << result[1];
				for (int i = 2;; i++)
				{
					if (result[i] == -1)
					{
						break;
					}
					cout << " --> " << result[i];
				}
				cout << endl;
				cout << "״̬��ȫ" << endl;

			}
			else
			{
				cout << "״̬����ȫ" << endl;
			}
		}
		else if (flag == 3)
		{
			//������Դ����
			int* request = (int*)malloc(sizeof(int) * 100);
			int number;
			cout << "�����뷢������Ľ��̣�";
			cin >> number;
			cout << "�������������Դ��������" << endl;
			for (int i = 0; i < m; i++)
			{
				cin >> request[i];
			}
			if (allocate(number, request))
			{
				cout << "���䰲ȫ��" << endl;
				//�ɹ�����Ľ��̣�����ɵľ���ɣ��ͷ�ռ�õ���Դ
				end(number);
			}
			else
			{
				cout << "����ʧ�ܣ�" << endl;
			}

		}
		else if (flag == 4)
		{
			//�˳�����
			cout << "���˳�" << endl;
			break;

		}
	}
	return 0;
}