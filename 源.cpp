#include<iostream>   
#include<string>     
#include<fstream>   
using namespace std;
//#define NULL 0 
unsigned int key;         //用来输入/输出文件流类
unsigned int key2;         //key和key2分别是用做了学号和姓名的关键字

int* p;
struct node //新建节点（用户姓名、地址、学号、指向下一个结点的指针 ）
{
	char name[8], address[20],phone[30];
	char num[11];
	node* next;
};
typedef node* pnode;
typedef node* mingzi; //声明了名字和学号两个指针
node** studynum;
node** nam;
node* a;

void hash1(char num[11]) //以学号为关键字建立哈希函数
{
	int i = 3;
	key = (int)num[2];

	while (num[i] != NULL)
	{
		key += (int)num[i];
		i++;
	}
	key = key % 20;
}
void hash2(char name[8])  //姓名为关键字建立哈希函数
{
	int i = 1;
	key2 = (int)name[0];

	while (name[i] != NULL)
	{
		key2 += (int)name[i];
		i++;
	}
	key2 = key2 % 20;
}
//强制类型转换，将用户名的每一个字母的ASCLL码值相加并且除以20后的余数
node* input()  //输入节点信息 ，建立结点，并将结点的next指针指空
{
	node* temp;
	temp = new node;
	temp->next = NULL;
	cout << "输入姓名：" << endl;
	cin >> temp->name;
	cout << "输入地址：" << endl;
	cin >> temp->address;
	cout << "输入学号：" << endl;
	cin >> temp->num;
	cout << "输入电话：" << endl;
	cin >> temp->phone;
	return temp;
}                   //对于指针类型返回的是地址

int apend() //添加节点 
{
	int m;
	cout << "请输入需要添加的人数：" << endl;
	cin >> m;
	for (int i = 0; i < m;i++) 
	{
		node* newnumber;
		node* newname;
		newnumber = input();
		newname = newnumber;
		newnumber->next = NULL;
		newname->next = NULL;
		hash1(newnumber->num);        //利用哈希函数计算出对应关键字的存储地址
		hash2(newname->name);
		newnumber->next = studynum[key]->next; //利用学号为关键字插入
		studynum[key]->next = newnumber;         //是采用链地址法，拉链法处理冲突的哈希表结构
		newname->next = nam[key2]->next;    //利用用户名为关键字插入
		nam[key2]->next = newname;
	}
	return 0;
}
void create() //新建节点 
{
	int i;
	studynum = new pnode[20];    //动态创建对象数组
	for (i = 0; i < 20; i++)
	{
		studynum[i] = new node;
		studynum[i]->next = NULL;

	}

}
void create2() //新建节点 
{
	int i;
	nam = new mingzi[20];
	for (i = 0; i < 20; i++)
	{
		nam[i] = new node;
		nam[i]->next = NULL;
	}

}
void list() //显示列表 
{
	int i;
	node* p;
	for (i = 0; i < 20; i++)
	{
		p = studynum[i]->next;
		while (p)
		{
			cout << p->name << '_' << p->address << '_' << p->num <<'_'<<p->phone<< endl;
			p = p->next;
		}
	}
}
void list2() //显示列表 
{
	int i;
	node* p;
	for (i = 0; i < 20; i++)
	{
		p = nam[i]->next;
		while (p)
		{
			cout << p->name << '_' << p->address << '_' << p->num <<'_'<<p->phone<< endl;
			p = p->next;
		}
	}
}
void find(char num[11])  //在以电话号码为关键字的哈希表中查找用户信息 
{
	hash2(num);
	node* q = studynum[key]->next;
	while (q != NULL)
	{
		if (strcmp(num, q->num) == 0)
			break;
		q = q->next;
	}
	if (q)
		cout << q->name << "_" << q->address << "_" << q->num << "_"<<q->phone<<endl;
	else cout << "无此记录" << endl;
}
void find2(char name[8])  //在以用户名为关键字的哈希表中查找用户信息 
{
	hash2(name);
	node* q = nam[key2]->next;
	while (q != NULL)
	{
		if (strcmp(name, q->name) == 0)
			break;
		q = q->next;
	}
	if (q)
		cout << q->name << "_" << q->address << "_" << q->num << "_" << q->phone << endl;
	else cout << "无此记录" << endl;
}
char find3(char num[11])
{
	hash1(num);//计算哈希函数的值
	int x = 1;
	while (num[key] != key)//解决冲突
	{
		if (x > 0)
		{
			key = (key % 19 + x * x + 20) % 20;
			x = -x;
		}
		else
		{
			key = (key % 19 + x * x + 20) % 20;
			x = -x;
			x++;
		}
	}
	return num[key];
}
void outout() 
{
	for (int i = 0; i < 200; i++)
	{
		node* q = nam[i]->next;
		if (q)
			cout << q->name << "_" << q->address << "_" << q->num << "_" << q->phone << endl;
	}
}

/*int HandleCollision(HashTable table, int key)
{
	Czy = 1; //从2,3,4,5,....... 
	while (1) {
		Czy++; //从2,3,4,5,....... 
		if (Czy % 2 == 0) {
			if (table->data[(key + (Czy / 2) * (Czy / 2)) % MAXSIZE].Name[0] == 0)
				return (key + (Czy / 2) * (Czy / 2)) % MAXSIZE;
		}
		else if (Czy % 2 != 0) {
			if ((key - (Czy / 2) * (Czy / 2)) < 0) continue;//由于是减法，要注意负数不能取模 
			if (table->data[(key - (Czy / 2) * (Czy / 2)) % MAXSIZE].Name[0] == 0)
				return (key - (Czy / 2) * (Czy / 2)) % MAXSIZE;
		}
	}
	//return -1;
}*/
void save() //保存用户信息 
{
	int i;
	node* p;
	for (i = 0; i < 20; i++)
	{
		p = studynum[i]->next;
		while (p)
		{
			fstream iiout("out.txt", ios::out); //创建一个文件流对象：iiout
			iiout << p->name << "_" << p->address << "_" << p->num << "_" << p->phone << endl;  //将信息存如文件
			p = p->next;
		}
	}

}

void menu() //菜单 
{
	cout << "                                     哈希表通讯录" << endl;
	cout << "                                     0.添加记录" << endl;
	cout << "                                     2.姓名哈希" << endl;
	cout << "                                     3.查找记录" << endl;
	cout << "                                     4.学号哈希" << endl;
	cout << "                                     5.清空记录" << endl;
	cout << "                                     6.保存记录" << endl;
	cout << "                                     7.退出系统" << endl;
	cout << "                                     8.浏览记录" << endl;
}

int main()
{

	char num[11];
	char name[8];

	create();
	create2();

	int sel;
	while (1)
	{
		menu();
		cin >> sel;
		if (sel == 3)
		{
			cout << "8姓名查询" << endl; cout << "9学号查询" << endl;
			int b;
			cin >> b;
			if (b == 9)
			{
				cout << "请输入学号:" << endl;
				cin >> num;
				cout << "输出查找的信息:" << endl;
				find(num);
			}
			else
			{
				cout << "请输入姓名:" << endl;
				cin >> name;
				cout << "输出查找的信息:" << endl;
				find2(name);
			}
		}
		if (sel == 2)
		{
			cout << "姓名哈希结果:" << endl;
			list2();
		}

		if (sel == 0)
		{
			//cout << "请输入要添加的内容:" << endl;
			apend();
		}
		if (sel == 4)
		{
			cout << "学号哈希结果:" << endl;
			list();
		}
		if (sel == 5)
		{
			cout << "列表已清空:" << endl;
			create(); create2();
		}
		if (sel == 6)
		{
			cout << "通信录已保存:" << endl;
			save();
		}
		if (sel == 8)
		{
			cout << "通信录浏览:" << endl;
			outout();
		}
		if (sel == 7) return 0;


	}

	return 0;

}