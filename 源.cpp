#include<iostream>
#include<string.h>
#include<fstream>
#include<cstdlib>
using namespace std;

typedef struct node *pointer;//���ָ������
struct node//���ṹ
{
	int score;//�ɼ�
	int sno;//ѧ��ѧ��
	pointer next;//ָ����
};
typedef pointer hlist;//���������ͣ�ͷָ������
struct hmessage //��ҵ��Ϣ�ṹ��
{
	int hno;//��ҵ���
	char hcontent[50];//��ҵ����
	hlist h;//��ҵ�ɼ���ѧ�ŵ�ָ��
}hw[5];
struct student // ѧ����Ϣ�ṹ�壬�洢����ѧ������Ϣ
{
	char name[30];//ѧ������
	int sno;//ѧ��ѧ��
}stu[50];
int sn=0;//��ǰѧ������
int hn = 0;//��ǰ��ҵ������,ͬʱҲ����ҵ�ı�š�
void Boundary();
void Teacher_Menu();
void Teacher_StudentMessage();
void Teacher_HomeworkMessage();
hlist initlist();
hlist hscore();
void StudentScore();
void ModifyScore();
void Search_Menu();
void Student_Menu();
void NewStudent();


void SumScore(hlist head)
{ 
	int j = 0,sum=0;
	float avg = 0;
	while (head->next)
	{
		cout << "\t   " << head->next->sno << "\t\t  " << head->next->score << endl;
		j = head->next->score;
		sum = sum + j;
		head = head->next;
	}
	avg = (float)sum / sn;
	cout << "\t   ƽ���֣�" << avg;
}

hlist initlist()//��ʼ������
{
	pointer head;
	head = new node;
	head->next = NULL;
	return head;
}

int FindSnoScore(hlist head, int no)//����ָ��ѧ�ŵ����гɼ�
{
	int j,sc=0;
	pointer p;
	j = 0;
	p = head->next;
	while (p != NULL)
	{
		j++;
		if (p->sno == no)break;
		p = p->next;
	}
	if (p != NULL)
	{
		cout << p->score << endl;
		sc = p->score;
		return sc;
	}
	else
	{
		cout << "û�и�ѧ��!" << endl;
		return -1;
	}
}

void count()//����ƽ���ֺ��ܷ�
{
	int sno;
	int sum = 0;
	int j = 0;
	float avg;
	cout << "\t   ������ѧ�ţ�";
	cin >> sno;
	cout << "\n" << "\t------------------------��ѯ���-----------------------\t" << endl;
	for (int i = 0; i < hn; i++)
	{
		cout << "\t   ��ҵ�ţ�" << hw[i].hno << "\t";
		cout << "\t   �ɼ���";
		j = FindSnoScore(hw[i].h, sno);
		sum = j + sum;
	}
	avg = (float)sum / hn;
	if (sum == 0)
	{
		cout << "\t   û��ѧ����Ϣ��\n\n" << endl;
		Boundary();
	}
	if (sum<0 && avg<0)
	{
		cout << "\t   û�и�ѧ�ţ������²�ѯ��\n\n" << endl;
		count();
	}
	cout << "\t   �ܷ֣�" << sum << endl;
	cout << "\t   ƽ���֣�" << avg << endl;
	Student_Menu();
}

void StudentScore()//�鿴������ҵ�ɼ�
{
	int sno,c=0;
	cout << "\n\n" << "\t----------------------�鿴���гɼ�---------------------" << endl;
	cout << "\t   ������ѧ�ţ�";
	cin >> sno;
	cout << "\n" << "\t------------------------��ѯ���-----------------------\t" << endl;
	cout << "\t   ��ǰѧ�ţ�"<<sno<< endl;
	for (int i = 0; i < hn; i++)
	{
		cout << "\t   ��ҵ�ţ�" << hw[i].hno<<"\t";
		cout << "\t   �ɼ���";
		FindSnoScore(hw[i].h, sno);
		//cout << "\n";
		c = hw[i].hno;
	}
	if (c==0)
	{
		cout << "\t   ��ǰû����Ϣ����ѯʧ�ܣ�" << endl;
	}
	Student_Menu();
}

int check(hlist head, int no)//����ָ����ҵ�ź�ѧ�ŵ�ѧ���ɼ�(ѧ��)
{
	int j;
	pointer p;
	j = 0;
	p = head->next;
	while (p != NULL)
	{
		j++;
		if (p->sno == no)break;
		p = p->next;
	}
	if (p != NULL)
	{
		cout << "\t   ѧ�ţ�" << no;
		cout << "\t   �ɼ���";
		cout << p->score<<endl;
		return j;
	}
	else
	{
		cout << "\t   û�и�ѧ��!" << endl;
		return -1;
	}
}

void SearchScore()//��ѯָ����ҵ�ĳɼ�(ѧ��)
{
	int hno, no;
	int i = 0;
	cout << "\n" << "\t----------------------��ѯָ���ɼ�---------------------\n" << endl;
	cout << "\t   ��������ҵ��ţ�";
	cin >> hno;
	while(i<hn)
	{
		if (hw[i].hno == hno)
		{
			cout << "\t   ������ѧ�ţ�";
			cin >> no;
			cout << "\n" << "\t------------------------��ѯ���-----------------------\t" << endl;
			check(hw[i].h, no);
			cout << "\n\n";
			break;
		}
		i++;
	}
	if (i == hn)
	{
		cout << "\t   û�и���ҵ��ţ�������ѧ�����棡\n";
		Student_Menu();
	}
	Student_Menu();
}

void Display(hlist head)//��ʾ�����е�������Ϣ
{
	while (head->next)
	{
		cout << "\t   " << head->next->sno << "\t\t  " << head->next->score << endl;
		head = head->next;
	}
}

void NoScoreSno(hlist head)//���ҳɼ�Ϊ0��ѧ��
{
	int j;
	int num = 0;
	pointer p;
	j = 0;
	p = head->next;
	while(p != NULL)
	{
		j++;
		if(p->score == 0)
		{
			cout <<"\t     "<< p->sno << endl;
			num++;
		}
		p = p->next;
		
	}
	cout <<"\n\t   ��ҵ��û�гɼ���ѧ����"<<num<<"��"<< endl;	
	//cout << "\t   ��ҵ��û����ҵ�ɼ�Ϊ0��ѧ����" << endl;
	Search_Menu();
}

void NoScore()//����ָ����ҵ��ųɼ�Ϊ0��ѧ��
{
	int hno;
	int i = 0;
	cout << "\t   ��������ҵ��ţ�";
	cin >> hno;
	while (i<hn)
	{
		if (hw[i].hno == hno)
		{
			cout << "\t-------------------------------------------------------\t" << endl;
			cout << "\t   �ɼ�Ϊ0��ѧ�ţ�" << endl;
			NoScoreSno(hw[i].h);
			cout << "\n\n";
			break;
		}
		i++;
	}
	if (i == hn)
	{
		cout << "\t   û�и���ҵ��ţ����������룡";
		NoScore();
	}
}

void HnoScore()//��ʾָ����ҵ���������ѧ���ĳɼ�
{
	int hno;
	int i = 0;
	cout << "\t   ��������ҵ��ţ�";
	cin >> hno;
	while (i<hn)
	{
		if (hw[i].hno == hno)
		{
			cout <<"\n"<< "\t-------------------------------------------------------\t" << endl;
			cout << "\t   ��ҵ��ţ�" << hw[i].hno << endl;
			cout << "\t   ��ҵ���ݣ�" << hw[i].hcontent << endl;
			cout << "\t   ����ѧ���ɼ���" << endl;
			cout << "\t   ѧ��\t\t �ɼ�" << endl;
			//Display(hw[i].h);
			SumScore(hw[i].h);
			cout << "\n\n";
			cout << "\t-------------------------------------------------------\t" << endl;
			break;
		}
		i++;
	}
	if (i == hn)
	{
		cout << "\t   û�и���ҵ��ţ����������룡";
		HnoScore();
	}
	Search_Menu();
}

void AllScore()//��ʾ������ҵ�����гɼ�
{
	cout << "\n\n" << "\t-----------------������ҵ������ѧ���ɼ�----------------" << endl;
	//cout << "������ҵ������ѧ���ɼ�" << endl;
	for (int i = 0; i < hn; i++)
	{
		cout << "\n" << "\t------------------------��ҵ��Ϣ-----------------------" << endl;
		cout << "\t   ��ҵ��ţ�" << hw[i].hno<<endl;
		cout << "\t   ��ҵ���ݣ�" << hw[i].hcontent<< endl;
		cout << "\t   ����ѧ���ɼ���"<<endl;
		cout << "\t   ѧ��\t\t �ɼ�" << endl;
		Display(hw[i].h);
		cout << "\n\n";
		cout << "\t-------------------------------------------------------\t" << endl;
	}
	Search_Menu();
}

void Search_Menu()//��ѯ��Ϣ�Ĳ˵�
{
	int key;
	cout << "\n\n" << "\t----------------------��ѯ��ҵ��Ϣ---------------------" << endl;
	cout << "\t   �������ѯ����Ϣ��  " << endl;
	cout << "\t\t\t  1��������ҵ������ѧ���ɼ�\n";
	cout << "\t\t\t  2��ĳ����ҵ������ѧ���ɼ�\n";
	cout << "\t\t\t  3��ĳ����ҵû�гɼ���ѧ��\n";
	cout << "\t\t\t  4�����ؽ�ʦ����\n";
	cout << "\t\t\t  0���������˵�" << endl;
	cout << "\t-------------------------------------------------------\t" << endl;
	cout << "\t   �����ţ� ";
	cin >> key;
	if (key<0 || key>4)
	{
		cout << "\t   ���벻�Ϸ������������룡\n" << endl;
		Search_Menu();
	}
	switch (key)
	{
	case 0:
		Boundary(); break;
	case 1:
		AllScore(); break;
	case 2:
		HnoScore(); break;
	case 3:
		NoScore(); break;
	case 4:
		Teacher_Menu(); break;
	}
}

int locate(hlist head, int no)//�޸ĳɼ�ʱ�Ķ�λ����
{
	int j,score;
	pointer p;
	j = 0;
	p = head->next;
	while (p != NULL)
	{
		j++;
		if (p->sno == no)break;
		p = p->next;
	}
	if (p != NULL)
	{
		cout << "\t   ������Ҫ�޸ĵĳɼ���";
		cin >> score;
		p->score = score;
		cout << "\t   �ɹ��޸ĳɼ���" << endl;
		return j;
	}
	else
	{
		cout << "\t   ��ҵ��û�и�ѧ��,����������!" << endl;
		ModifyScore();
		return 0;
	}
}

void ModifyScore()//������ҵ�ź�ѧ�ţ�����޸�
{
	int hno,no;
	int i = 0;
	cout << "\n\n" << "\t----------------------�޸���ҵ��Ϣ---------------------" << endl;
	cout << "\t   ��������ҵ��ţ�";
	cin >> hno;
	while (i<hn)
	{
		if (hw[i].hno==hno)
		{
			cout << "\t   ������ѧ�ţ�";
			cin >> no;
			locate(hw[i].h, no);
			break;
		}
		i++;
	}
	if(i == hn)
	{
		cout << "\t   û�и���ҵ��ţ�����������!";
		ModifyScore();
	}
	Teacher_HomeworkMessage();
}

hlist hscore()//��ѧ���ɼ����뵽������
{
	hlist head;
	pointer s;
	head = new node;
	head->next = NULL;
	while (sn==0)
	{
		cout << "\n\t   ��ǰû��ѧ����Ϣ������ӣ�" << endl;
		Teacher_Menu();
	}
	for (int i = 0; i < sn; i++)
	{
		s = new node;
		s->sno = stu[i].sno;
		cout << "\t   ѧ��ѧ��Ϊ��" << s->sno << "\n";
		cout << "\t   ������ɼ���";
		cin >> s->score;
		while (s->score<0 || s->score>100)
		{
			cout << "\t   �ɼ���Ч�����������룡" << endl;
			cout << "\t   ������ɼ���";
			cin >> s->score;
		}
		s->next = head->next;
		head->next = s;
	}
	cout << "\t   �ɹ�����" << sn << "��ͬѧ�ĳɼ���\n" << endl;
	return head;
}

void AddHomeworkMessage()//����µ���ҵ
{
	cout << "\n\n" << "\t----------------------������ҵ��Ϣ---------------------" << endl;
	hw[hn].hno = hn+1;
	cout << "\t   ��ǰ��ҵ���Ϊ��" << hw[hn].hno << endl;
	cout << "\t   ��ҵ����Ϊ��";
	cin >> hw[hn].hcontent;
	cout << "\t   ������ѧ���ĳɼ���\n";
	hw[hn].h = hscore();
	hn+=1;
	//cout << hn;
	Teacher_HomeworkMessage();
}

void NewHomeworkMessage()//�½�ѧ����ҵ
{
	cout << "\n\n" << "\t----------------------�½���ҵ��Ϣ---------------------" << endl;
	//hno = rand() % 100 + 100;
	hw[hn].hno = hn + 1;//��Ϊ��ʾ������ҵ�ı�ţ�������Ҫ��1��hn��ʾ���ǵ�ǰ����ҵ�����������½������Գ�ʼ����Ϊ0
	cout << "\t   ��ǰ��ҵ���Ϊ��" << hw[hn].hno << endl;
	cout << "\t   ��ҵ����Ϊ��";
	cin >> hw[hn].hcontent;
	cout << "\t   ������ѧ���ĳɼ���\n";
	hw[hn].h = hscore();
	hn+=1;
	Teacher_HomeworkMessage();
	//cout << hn;
}

void ModifyStudent()//�޸�ѧ����Ϣ
{
	int no,key;
	cout << "\n\n" << "\t----------------------�޸�ѧ����Ϣ---------------------" << endl;
	cout << "\n\t----------------------��ǰѧ����Ϣ---------------------- \n";
	cout << "\n" << "\t\tѧ�� \t\t����" << endl;
	for (int i = 0; i < sn; i++)
	{
		cout << "\t\t" << stu[i].sno << "\t\t" << stu[i].name<<"\n";
	}
	cout << "\t-------------------------------------------------------\t" << endl;
	cout << "\n" << "\t   ��ѡ����Ҫ�޸ĵ�ѧ�ţ�";
	cin >> no;
	for (int k = 0; k < sn; k++)
	{
		if (stu[k].sno == no)
		{
			cout << "\t   ��ѡ���޸ĵ���Ϣ��" << endl;
			cout << "\t\t\t    1��ѧ�� \n";
			cout << "\t\t\t    2������ \n";
			cout << "\t\t\t    0������ѧ����Ϣ���� " << endl;
			cout << "\t-------------------------------------------------------\t" << endl;
			cout << "\t   ����Ȩ�ޣ� ";
			cin >> key;
			if (key<0 || key>2)
			{
				cout << "\t     ���벻�Ϸ�������������!\n" << endl;
				ModifyStudent();
			}
			switch (key)
			{
			case 0:
				Teacher_StudentMessage(); break;
			case 1:
				cout << "\t     �������µ�ѧ�ţ�";
				cin >> stu[k].sno;
				cout << "\t     �޸�ѧ��ѧ�ųɹ���\n"<<endl;
				Teacher_StudentMessage();
				break;
			case 2:
				cout << "\t     �������µ�������";
				cin >> stu[k].name;
				cout << "\n\t     �޸�ѧ�������ɹ���\n"<<endl;
				Teacher_StudentMessage();
				break;
			}
		}
	}
	if (sn == 0)
	{
		cout << "\n\t     ��ǰû��ѧ������Ϣ���������½���\n" << endl;
		NewStudent();
	}
}

void CheckStudent()//��ѯ��ǰ����ѧ������Ϣ
{
	cout << "\n\n" << "\t----------------------��ѯѧ����Ϣ---------------------" << endl;
	/*int sno;
	char name[30];
	char buffer[256];
	ifstream f("student");
	if (!f)
	{
		cout << "\t   �ļ����ܴ�!" << endl;
	}
	else
	{
		cout << "\n\t----------------------��ǰѧ����Ϣ---------------------- \n";
		cout <<"\n"<< "\t\tѧ�� \t\t����" << endl;
		for (int i = 0; i < sn; i++)
		{
			f >> stu[i].sno>> stu[i].name;
			cout << "\t\t" << stu[i].sno<< "\t\t" << stu[i].name;
		}
		while (!f.eof()) 
		{
			f.getline(buffer, 100);
			cout << buffer << endl;
		}
		cout << buffer;
		cout << "\t-------------------------------------------------------\t" << endl;
		f.close();
		Teacher_StudentMessage();
	}*/
	cout << "\n\t----------------------��ǰѧ����Ϣ---------------------- \n";
	cout << "\n" << "\t\tѧ�� \t\t����" << endl;
	for (int i = 0; i < sn; i++)
	{
	
		cout << "\t\t" << stu[i].sno << "\t\t" << stu[i].name << "\n";
	}	
	if (sn == 0)
	{
		cout << "\n\t   ��ǰû��ѧ����Ϣ������ӣ�" << endl;
	}
	cout << "\t-------------------------------------------------------\t" << endl;
	Teacher_StudentMessage();
}

void NewStudent()//�½�ѧ����Ϣ������ʾ��ǰѧ����Ϣ��
{
	cout << "\n\n" << "\t----------------------�½�ѧ����Ϣ---------------------" << endl;
	ofstream f("student");
	int n;
	cout << "\n" << "\t   ������ѧ������(���ó���50��)�� ";
	cin >> n;
	if (n>50)
	{
		cout << "\t   ���벻�Ϸ�������������!" << endl;
		NewStudent();
	}
	if (!f.is_open()) // ����ļ��Ƿ�ɹ���  
		cout << "\t   �ļ����ܴ�" << endl;
	cout << "\n" << "\t   ������ѧ����Ϣ��" << endl;
	for (int i = 0; i < n; i++)
	{
		cout <<"\n"<< "\t    ��ǰ�ǵ�" << i + 1 << "��ѧ��" << endl;
		cout << "\t   ����ѧ�ţ� ";
		cin >>stu[i].sno;
		cout << "\t   ���������� ";
		cin >>stu[i].name;
		f <<"\t\t "<< stu[i].sno << "\t\t  " << stu[i].name << endl;	
	}
	f.close();
	sn = n;
	cout << "\n\t\t �ɹ�����" << n << "��ѧ����Ϣ��\n\n";
	Teacher_StudentMessage();
}

void Teacher_HomeworkMessage()//��ʦ����ҵ��Ϣ�Ĳ���
{
	int key;
	int n = NULL;
	cout << "\n" << "\t------------------------��ҵ��Ϣ-----------------------" << endl;
	cout << "\t   ��ѡ���ܣ� " << endl;
	cout << "\t\t\t  1���½���ҵ��Ϣ\n";
	cout << "\t\t\t  2��������ҵ��Ϣ\n";
	cout << "\t\t\t  3���޸���ҵ�ɼ�\n";
	cout << "\t\t\t  4���鿴��ҵ�ɼ�\n";
	cout << "\t\t\t  5�����ؽ�ʦ����\n";
	cout << "\t\t\t  0������������\n" << endl;
	cout << "\t-------------------------------------------------------\t" << endl;
	cout << "\t   �����ţ� ";
	cin >> key;
	if (key<0 || key>5)
	{
		cout << "\t   ���벻�Ϸ������������룡\n" << endl;
		Teacher_HomeworkMessage();
	}
	switch (key)
	{
	case 0:
		Boundary(); break;
	case 1:
		NewHomeworkMessage(); break;
	case 2:
		AddHomeworkMessage(); break;
	case 3:
		ModifyScore(); break;
	case 4:
		Search_Menu(); break;
	case 5:
		Teacher_Menu(); break;
	}
}

void Teacher_StudentMessage()//��ʦ��ѧ����Ϣ�Ĳ���
{
	int key;
	cout << "\n" << "\t------------------------ѧ����Ϣ-----------------------" << endl;
	cout << "\t   ��ѡ���ܣ� " << endl;
	cout << "\t\t\t  1��������ѧ����Ϣ��" << "\n";
	cout << "\t\t\t  2���鿴��ǰѧ����Ϣ��" << "\n";
	cout << "\t\t\t  3���޸�ѧ����Ϣ��" << "\n";
	cout << "\t\t\t  4�����ؽ�ʦȨ�޽���" << "\n";
	cout << "\t\t\t  0������������" << endl;
	cout << "\t-------------------------------------------------------\t" << endl;
	cout << "\t   �����ţ� ";
	cin >> key;
	if (key<0 || key>4)
	{
		cout << "\t   ���벻�Ϸ������������룡\n" << endl;
		Teacher_StudentMessage();
	}
	switch (key)
	{
	case 0:
		Boundary(); break;
	case 1:
		NewStudent(); break;
	case 2:
		CheckStudent(); break;
	case 3: 
		ModifyStudent(); break;
	case 4:
		Teacher_Menu(); break;
	}
}

void Student_Menu()//ѧ��Ȩ�޺�Ĳ˵�
{
	int key;
	cout << "\n"<<"\t----------------------ͬѧ����ã�---------------------" << endl;
	cout << "\t   ��ѡ���ܣ� " << endl;
	cout << "\t\t\t  1���鿴������ҵ�ɼ� \n";
	cout << "\t\t\t  2���鿴ָ����ҵ�ɼ� \n";
	cout << "\t\t\t  3���鿴��ҵ�ֺܷ�ƽ���� \n";
	cout << "\t\t\t  0���������˵�" << endl;
	cout << "\t-------------------------------------------------------\t" << endl;
	cout << "\t   �����ţ� ";
	cin >> key;
	if (key<0 || key>3)
	{
		cout << "\t   ���벻�Ϸ����������룡\n" << endl;
		Student_Menu();
	}
	switch (key)
	{
	case 0:
		Boundary(); break;
	case 1:
		StudentScore(); break;
	case 2:
		SearchScore(); break;
	case 3:
		count(); break;
	}
}

void Teacher_Menu()//�����ʦȨ�޺�Ĳ˵�
{
	int key;
	cout << "\n"<<"\t---------------------��ʦ�����ã�----------------------\t\t\t" << endl;
	cout << " \t   ��ѡ����Ϣ�� " << endl;
	cout << " \t\t\t   1��ѧ����Ϣ \n";
	cout << " \t\t\t   2����ҵ��Ϣ \n";
	cout << " \t\t\t   0������������" << endl;
	cout << "\t-------------------------------------------------------\t" << endl;
	cout << "\t   �����ţ� ";
	cin >> key;
	if (key<0 || key>2)
	{
		cout << "\t   ���벻�Ϸ����������룡\n" << endl;
		Teacher_Menu();
	}
	switch (key)
	{
	case 0:
		Boundary(); break;
	case 1:
		Teacher_StudentMessage(); break;
	case 2:
		Teacher_HomeworkMessage(); break;
	}
}

void Teacher_Boundary()//��ʦȨ�޽���
{
	int password = 123456;
	int key;
	cout << "\n" << "\t-------------------�����ʦȨ����֤--------------------\t" << endl;
	cout << "\t   ���������룺 ";
	cin >> key;
	if (password == key)
	{
		Teacher_Menu();
	}
	if (password != key)
	{
		int j;
		for (j = 3; j > 0; j--)
		{
			cout << "\t     ����������������룡����" << j << "�λ���" << endl;
			cout << "\t   ���������룺 ";
			cin >> key;
			if (password == key)
			{
				Teacher_Menu(); break;
			}
		}
		while (j = 1)
		{
			cout << "\t     ��֤ʧ�ܣ������������棡\n\n" << endl;
			Boundary();
		}
	}
}

void Boundary()//һ��ʼ���ֵ�Ȩ�޽���
{
	int key;
	cout <<"\n"<< "\t---------------��ӭʹ����ҵ�ɼ�����ϵͳ----------------\t" << endl;
	cout << "\t   ��ѡ���û�Ȩ�ޣ�" << endl;
	cout << "\t\t\t    1����ʦ \n";
	cout << "\t\t\t    2��ѧ�� \n";
	cout << "\t\t\t    0���˳� " << endl;
	cout << "\t-------------------------------------------------------\t" << endl;
	cout << "\t   ����Ȩ�ޣ� ";
	cin >> key;
	if (key<0 || key>2)
	{
		cout << "\t     ���벻�Ϸ�������������!\n" << endl;
		Boundary();
	}
	switch (key)
	{
	case 0:
		cout << "\n" << "�ɹ��˳��� " << endl; break;
	case 1:
		Teacher_Boundary(); break;
	case 2:
		Student_Menu(); break;
	}
}

int main()
{
	Boundary();
	return 0;
}