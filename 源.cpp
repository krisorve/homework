#include<iostream>
#include<string.h>
#include<fstream>
#include<cstdlib>
using namespace std;

typedef struct node *pointer;//结点指针类型
struct node//结点结构
{
	int score;//成绩
	int sno;//学生学号
	pointer next;//指针域
};
typedef pointer hlist;//单链表类型，头指针类型
struct hmessage //作业信息结构体
{
	int hno;//作业编号
	char hcontent[50];//作业内容
	hlist h;//作业成绩和学号的指针
}hw[5];
struct student // 学生信息结构体，存储所有学生的信息
{
	char name[30];//学生姓名
	int sno;//学生学号
}stu[50];
int sn=0;//当前学生人数
int hn = 0;//当前作业的数量,同时也是作业的编号。
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
	cout << "\t   平均分：" << avg;
}

hlist initlist()//初始化链表
{
	pointer head;
	head = new node;
	head->next = NULL;
	return head;
}

int FindSnoScore(hlist head, int no)//查找指定学号的所有成绩
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
		cout << "没有该学号!" << endl;
		return -1;
	}
}

void count()//计算平均分和总分
{
	int sno;
	int sum = 0;
	int j = 0;
	float avg;
	cout << "\t   请输入学号：";
	cin >> sno;
	cout << "\n" << "\t------------------------查询结果-----------------------\t" << endl;
	for (int i = 0; i < hn; i++)
	{
		cout << "\t   作业号：" << hw[i].hno << "\t";
		cout << "\t   成绩：";
		j = FindSnoScore(hw[i].h, sno);
		sum = j + sum;
	}
	avg = (float)sum / hn;
	if (sum == 0)
	{
		cout << "\t   没有学生信息！\n\n" << endl;
		Boundary();
	}
	if (sum<0 && avg<0)
	{
		cout << "\t   没有该学号！请重新查询！\n\n" << endl;
		count();
	}
	cout << "\t   总分：" << sum << endl;
	cout << "\t   平均分：" << avg << endl;
	Student_Menu();
}

void StudentScore()//查看所有作业成绩
{
	int sno,c=0;
	cout << "\n\n" << "\t----------------------查看所有成绩---------------------" << endl;
	cout << "\t   请输入学号：";
	cin >> sno;
	cout << "\n" << "\t------------------------查询结果-----------------------\t" << endl;
	cout << "\t   当前学号："<<sno<< endl;
	for (int i = 0; i < hn; i++)
	{
		cout << "\t   作业号：" << hw[i].hno<<"\t";
		cout << "\t   成绩：";
		FindSnoScore(hw[i].h, sno);
		//cout << "\n";
		c = hw[i].hno;
	}
	if (c==0)
	{
		cout << "\t   当前没有信息！查询失败！" << endl;
	}
	Student_Menu();
}

int check(hlist head, int no)//查找指定作业号和学号的学生成绩(学生)
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
		cout << "\t   学号：" << no;
		cout << "\t   成绩：";
		cout << p->score<<endl;
		return j;
	}
	else
	{
		cout << "\t   没有该学号!" << endl;
		return -1;
	}
}

void SearchScore()//查询指定作业的成绩(学生)
{
	int hno, no;
	int i = 0;
	cout << "\n" << "\t----------------------查询指定成绩---------------------\n" << endl;
	cout << "\t   请输入作业编号：";
	cin >> hno;
	while(i<hn)
	{
		if (hw[i].hno == hno)
		{
			cout << "\t   请输入学号：";
			cin >> no;
			cout << "\n" << "\t------------------------查询结果-----------------------\t" << endl;
			check(hw[i].h, no);
			cout << "\n\n";
			break;
		}
		i++;
	}
	if (i == hn)
	{
		cout << "\t   没有该作业编号，将返回学生界面！\n";
		Student_Menu();
	}
	Student_Menu();
}

void Display(hlist head)//显示链表中的所有信息
{
	while (head->next)
	{
		cout << "\t   " << head->next->sno << "\t\t  " << head->next->score << endl;
		head = head->next;
	}
}

void NoScoreSno(hlist head)//查找成绩为0的学生
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
	cout <<"\n\t   作业中没有成绩的学生有"<<num<<"人"<< endl;	
	//cout << "\t   作业中没有作业成绩为0的学生！" << endl;
	Search_Menu();
}

void NoScore()//查找指定作业编号成绩为0的学生
{
	int hno;
	int i = 0;
	cout << "\t   请输入作业编号：";
	cin >> hno;
	while (i<hn)
	{
		if (hw[i].hno == hno)
		{
			cout << "\t-------------------------------------------------------\t" << endl;
			cout << "\t   成绩为0的学号：" << endl;
			NoScoreSno(hw[i].h);
			cout << "\n\n";
			break;
		}
		i++;
	}
	if (i == hn)
	{
		cout << "\t   没有该作业编号，请重新输入！";
		NoScore();
	}
}

void HnoScore()//显示指定作业编号中所以学生的成绩
{
	int hno;
	int i = 0;
	cout << "\t   请输入作业编号：";
	cin >> hno;
	while (i<hn)
	{
		if (hw[i].hno == hno)
		{
			cout <<"\n"<< "\t-------------------------------------------------------\t" << endl;
			cout << "\t   作业编号：" << hw[i].hno << endl;
			cout << "\t   作业内容：" << hw[i].hcontent << endl;
			cout << "\t   所有学生成绩：" << endl;
			cout << "\t   学号\t\t 成绩" << endl;
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
		cout << "\t   没有该作业编号，请重新输入！";
		HnoScore();
	}
	Search_Menu();
}

void AllScore()//显示所有作业的所有成绩
{
	cout << "\n\n" << "\t-----------------所有作业的所有学生成绩----------------" << endl;
	//cout << "所有作业的所有学生成绩" << endl;
	for (int i = 0; i < hn; i++)
	{
		cout << "\n" << "\t------------------------作业信息-----------------------" << endl;
		cout << "\t   作业编号：" << hw[i].hno<<endl;
		cout << "\t   作业内容：" << hw[i].hcontent<< endl;
		cout << "\t   所有学生成绩："<<endl;
		cout << "\t   学号\t\t 成绩" << endl;
		Display(hw[i].h);
		cout << "\n\n";
		cout << "\t-------------------------------------------------------\t" << endl;
	}
	Search_Menu();
}

void Search_Menu()//查询信息的菜单
{
	int key;
	cout << "\n\n" << "\t----------------------查询作业信息---------------------" << endl;
	cout << "\t   请输入查询的信息：  " << endl;
	cout << "\t\t\t  1：所有作业的所有学生成绩\n";
	cout << "\t\t\t  2：某次作业的所有学生成绩\n";
	cout << "\t\t\t  3：某次作业没有成绩的学生\n";
	cout << "\t\t\t  4：返回教师界面\n";
	cout << "\t\t\t  0：返回主菜单" << endl;
	cout << "\t-------------------------------------------------------\t" << endl;
	cout << "\t   输入编号： ";
	cin >> key;
	if (key<0 || key>4)
	{
		cout << "\t   输入不合法，请重新输入！\n" << endl;
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

int locate(hlist head, int no)//修改成绩时的定位操作
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
		cout << "\t   请输入要修改的成绩：";
		cin >> score;
		p->score = score;
		cout << "\t   成功修改成绩！" << endl;
		return j;
	}
	else
	{
		cout << "\t   作业中没有该学号,请重新输入!" << endl;
		ModifyScore();
		return 0;
	}
}

void ModifyScore()//根据作业号和学号，完成修改
{
	int hno,no;
	int i = 0;
	cout << "\n\n" << "\t----------------------修改作业信息---------------------" << endl;
	cout << "\t   请输入作业编号：";
	cin >> hno;
	while (i<hn)
	{
		if (hw[i].hno==hno)
		{
			cout << "\t   请输入学号：";
			cin >> no;
			locate(hw[i].h, no);
			break;
		}
		i++;
	}
	if(i == hn)
	{
		cout << "\t   没有该作业编号，请重新输入!";
		ModifyScore();
	}
	Teacher_HomeworkMessage();
}

hlist hscore()//将学生成绩输入到链表中
{
	hlist head;
	pointer s;
	head = new node;
	head->next = NULL;
	while (sn==0)
	{
		cout << "\n\t   当前没有学生信息，请添加！" << endl;
		Teacher_Menu();
	}
	for (int i = 0; i < sn; i++)
	{
		s = new node;
		s->sno = stu[i].sno;
		cout << "\t   学生学号为：" << s->sno << "\n";
		cout << "\t   请输入成绩：";
		cin >> s->score;
		while (s->score<0 || s->score>100)
		{
			cout << "\t   成绩无效，请重新输入！" << endl;
			cout << "\t   请输入成绩：";
			cin >> s->score;
		}
		s->next = head->next;
		head->next = s;
	}
	cout << "\t   成功输入" << sn << "名同学的成绩！\n" << endl;
	return head;
}

void AddHomeworkMessage()//添加新的作业
{
	cout << "\n\n" << "\t----------------------增加作业信息---------------------" << endl;
	hw[hn].hno = hn+1;
	cout << "\t   当前作业编号为：" << hw[hn].hno << endl;
	cout << "\t   作业内容为：";
	cin >> hw[hn].hcontent;
	cout << "\t   请输入学生的成绩：\n";
	hw[hn].h = hscore();
	hn+=1;
	//cout << hn;
	Teacher_HomeworkMessage();
}

void NewHomeworkMessage()//新建学生作业
{
	cout << "\n\n" << "\t----------------------新建作业信息---------------------" << endl;
	//hno = rand() % 100 + 100;
	hw[hn].hno = hn + 1;//因为表示的是作业的编号，所以需要加1，hn表示的是当前的作业数量，现在新建，所以初始数量为0
	cout << "\t   当前作业编号为：" << hw[hn].hno << endl;
	cout << "\t   作业内容为：";
	cin >> hw[hn].hcontent;
	cout << "\t   请输入学生的成绩：\n";
	hw[hn].h = hscore();
	hn+=1;
	Teacher_HomeworkMessage();
	//cout << hn;
}

void ModifyStudent()//修改学生信息
{
	int no,key;
	cout << "\n\n" << "\t----------------------修改学生信息---------------------" << endl;
	cout << "\n\t----------------------当前学生信息---------------------- \n";
	cout << "\n" << "\t\t学号 \t\t姓名" << endl;
	for (int i = 0; i < sn; i++)
	{
		cout << "\t\t" << stu[i].sno << "\t\t" << stu[i].name<<"\n";
	}
	cout << "\t-------------------------------------------------------\t" << endl;
	cout << "\n" << "\t   请选择想要修改的学号：";
	cin >> no;
	for (int k = 0; k < sn; k++)
	{
		if (stu[k].sno == no)
		{
			cout << "\t   请选择修改的信息：" << endl;
			cout << "\t\t\t    1：学号 \n";
			cout << "\t\t\t    2：姓名 \n";
			cout << "\t\t\t    0：返回学生信息界面 " << endl;
			cout << "\t-------------------------------------------------------\t" << endl;
			cout << "\t   输入权限： ";
			cin >> key;
			if (key<0 || key>2)
			{
				cout << "\t     输入不合法，请重新输入!\n" << endl;
				ModifyStudent();
			}
			switch (key)
			{
			case 0:
				Teacher_StudentMessage(); break;
			case 1:
				cout << "\t     请输入新的学号：";
				cin >> stu[k].sno;
				cout << "\t     修改学生学号成功！\n"<<endl;
				Teacher_StudentMessage();
				break;
			case 2:
				cout << "\t     请输入新的姓名：";
				cin >> stu[k].name;
				cout << "\n\t     修改学生姓名成功！\n"<<endl;
				Teacher_StudentMessage();
				break;
			}
		}
	}
	if (sn == 0)
	{
		cout << "\n\t     当前没有学生的信息！请重新新建！\n" << endl;
		NewStudent();
	}
}

void CheckStudent()//查询当前所有学生的信息
{
	cout << "\n\n" << "\t----------------------查询学生信息---------------------" << endl;
	/*int sno;
	char name[30];
	char buffer[256];
	ifstream f("student");
	if (!f)
	{
		cout << "\t   文件不能打开!" << endl;
	}
	else
	{
		cout << "\n\t----------------------当前学生信息---------------------- \n";
		cout <<"\n"<< "\t\t学号 \t\t姓名" << endl;
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
	cout << "\n\t----------------------当前学生信息---------------------- \n";
	cout << "\n" << "\t\t学号 \t\t姓名" << endl;
	for (int i = 0; i < sn; i++)
	{
	
		cout << "\t\t" << stu[i].sno << "\t\t" << stu[i].name << "\n";
	}	
	if (sn == 0)
	{
		cout << "\n\t   当前没有学生信息，请添加！" << endl;
	}
	cout << "\t-------------------------------------------------------\t" << endl;
	Teacher_StudentMessage();
}

void NewStudent()//新建学生信息表，并显示当前学生信息表
{
	cout << "\n\n" << "\t----------------------新建学生信息---------------------" << endl;
	ofstream f("student");
	int n;
	cout << "\n" << "\t   请输入学生人数(不得超过50人)： ";
	cin >> n;
	if (n>50)
	{
		cout << "\t   输入不合法，请重新输入!" << endl;
		NewStudent();
	}
	if (!f.is_open()) // 检查文件是否成功打开  
		cout << "\t   文件不能打开" << endl;
	cout << "\n" << "\t   请输入学生信息：" << endl;
	for (int i = 0; i < n; i++)
	{
		cout <<"\n"<< "\t    当前是第" << i + 1 << "个学生" << endl;
		cout << "\t   输入学号： ";
		cin >>stu[i].sno;
		cout << "\t   输入姓名： ";
		cin >>stu[i].name;
		f <<"\t\t "<< stu[i].sno << "\t\t  " << stu[i].name << endl;	
	}
	f.close();
	sn = n;
	cout << "\n\t\t 成功输入" << n << "个学生信息！\n\n";
	Teacher_StudentMessage();
}

void Teacher_HomeworkMessage()//教师对作业信息的操作
{
	int key;
	int n = NULL;
	cout << "\n" << "\t------------------------作业信息-----------------------" << endl;
	cout << "\t   请选择功能： " << endl;
	cout << "\t\t\t  1：新建作业信息\n";
	cout << "\t\t\t  2：增加作业信息\n";
	cout << "\t\t\t  3：修改作业成绩\n";
	cout << "\t\t\t  4：查看作业成绩\n";
	cout << "\t\t\t  5：返回教师界面\n";
	cout << "\t\t\t  0：返回主界面\n" << endl;
	cout << "\t-------------------------------------------------------\t" << endl;
	cout << "\t   输入编号： ";
	cin >> key;
	if (key<0 || key>5)
	{
		cout << "\t   输入不合法，请重新输入！\n" << endl;
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

void Teacher_StudentMessage()//教师对学生信息的操作
{
	int key;
	cout << "\n" << "\t------------------------学生信息-----------------------" << endl;
	cout << "\t   请选择功能： " << endl;
	cout << "\t\t\t  1：建立新学生信息表" << "\n";
	cout << "\t\t\t  2：查看当前学生信息表" << "\n";
	cout << "\t\t\t  3：修改学生信息表" << "\n";
	cout << "\t\t\t  4：返回教师权限界面" << "\n";
	cout << "\t\t\t  0：返回主界面" << endl;
	cout << "\t-------------------------------------------------------\t" << endl;
	cout << "\t   输入编号： ";
	cin >> key;
	if (key<0 || key>4)
	{
		cout << "\t   输入不合法，请重新输入！\n" << endl;
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

void Student_Menu()//学生权限后的菜单
{
	int key;
	cout << "\n"<<"\t----------------------同学，你好！---------------------" << endl;
	cout << "\t   请选择功能： " << endl;
	cout << "\t\t\t  1：查看所有作业成绩 \n";
	cout << "\t\t\t  2：查看指定作业成绩 \n";
	cout << "\t\t\t  3：查看作业总分和平均分 \n";
	cout << "\t\t\t  0：返回主菜单" << endl;
	cout << "\t-------------------------------------------------------\t" << endl;
	cout << "\t   输入编号： ";
	cin >> key;
	if (key<0 || key>3)
	{
		cout << "\t   输入不合法，重新输入！\n" << endl;
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

void Teacher_Menu()//进入教师权限后的菜单
{
	int key;
	cout << "\n"<<"\t---------------------教师，您好！----------------------\t\t\t" << endl;
	cout << " \t   请选择信息： " << endl;
	cout << " \t\t\t   1：学生信息 \n";
	cout << " \t\t\t   2：作业信息 \n";
	cout << " \t\t\t   0：返回主界面" << endl;
	cout << "\t-------------------------------------------------------\t" << endl;
	cout << "\t   输入编号： ";
	cin >> key;
	if (key<0 || key>2)
	{
		cout << "\t   输入不合法，重新输入！\n" << endl;
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

void Teacher_Boundary()//教师权限界面
{
	int password = 123456;
	int key;
	cout << "\n" << "\t-------------------进入教师权限认证--------------------\t" << endl;
	cout << "\t   请输入密码： ";
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
			cout << "\t     密码错误！请重新输入！还有" << j << "次机会" << endl;
			cout << "\t   请输入密码： ";
			cin >> key;
			if (password == key)
			{
				Teacher_Menu(); break;
			}
		}
		while (j = 1)
		{
			cout << "\t     认证失败，将返回主界面！\n\n" << endl;
			Boundary();
		}
	}
}

void Boundary()//一开始出现的权限界面
{
	int key;
	cout <<"\n"<< "\t---------------欢迎使用作业成绩管理系统----------------\t" << endl;
	cout << "\t   请选择用户权限：" << endl;
	cout << "\t\t\t    1：教师 \n";
	cout << "\t\t\t    2：学生 \n";
	cout << "\t\t\t    0：退出 " << endl;
	cout << "\t-------------------------------------------------------\t" << endl;
	cout << "\t   输入权限： ";
	cin >> key;
	if (key<0 || key>2)
	{
		cout << "\t     输入不合法，请重新输入!\n" << endl;
		Boundary();
	}
	switch (key)
	{
	case 0:
		cout << "\n" << "成功退出！ " << endl; break;
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