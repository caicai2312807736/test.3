#include<iostream>   
#include<string>     
#include<fstream>   
using namespace std;
//#define NULL 0 
unsigned int key;         //��������/����ļ�����
unsigned int key2;         //key��key2�ֱ���������ѧ�ź������Ĺؼ���

int* p;
struct node //�½��ڵ㣨�û���������ַ��ѧ�š�ָ����һ������ָ�� ��
{
	char name[8], address[20],phone[30];
	char num[11];
	node* next;
};
typedef node* pnode;
typedef node* mingzi; //���������ֺ�ѧ������ָ��
node** studynum;
node** nam;
node* a;

void hash1(char num[11]) //��ѧ��Ϊ�ؼ��ֽ�����ϣ����
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
void hash2(char name[8])  //����Ϊ�ؼ��ֽ�����ϣ����
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
//ǿ������ת�������û�����ÿһ����ĸ��ASCLL��ֵ��Ӳ��ҳ���20�������
node* input()  //����ڵ���Ϣ ��������㣬��������nextָ��ָ��
{
	node* temp;
	temp = new node;
	temp->next = NULL;
	cout << "����������" << endl;
	cin >> temp->name;
	cout << "�����ַ��" << endl;
	cin >> temp->address;
	cout << "����ѧ�ţ�" << endl;
	cin >> temp->num;
	cout << "����绰��" << endl;
	cin >> temp->phone;
	return temp;
}                   //����ָ�����ͷ��ص��ǵ�ַ

int apend() //��ӽڵ� 
{
	int m;
	cout << "��������Ҫ��ӵ�������" << endl;
	cin >> m;
	for (int i = 0; i < m;i++) 
	{
		node* newnumber;
		node* newname;
		newnumber = input();
		newname = newnumber;
		newnumber->next = NULL;
		newname->next = NULL;
		hash1(newnumber->num);        //���ù�ϣ�����������Ӧ�ؼ��ֵĴ洢��ַ
		hash2(newname->name);
		newnumber->next = studynum[key]->next; //����ѧ��Ϊ�ؼ��ֲ���
		studynum[key]->next = newnumber;         //�ǲ�������ַ���������������ͻ�Ĺ�ϣ��ṹ
		newname->next = nam[key2]->next;    //�����û���Ϊ�ؼ��ֲ���
		nam[key2]->next = newname;
	}
	return 0;
}
void create() //�½��ڵ� 
{
	int i;
	studynum = new pnode[20];    //��̬������������
	for (i = 0; i < 20; i++)
	{
		studynum[i] = new node;
		studynum[i]->next = NULL;

	}

}
void create2() //�½��ڵ� 
{
	int i;
	nam = new mingzi[20];
	for (i = 0; i < 20; i++)
	{
		nam[i] = new node;
		nam[i]->next = NULL;
	}

}
void list() //��ʾ�б� 
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
void list2() //��ʾ�б� 
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
void find(char num[11])  //���Ե绰����Ϊ�ؼ��ֵĹ�ϣ���в����û���Ϣ 
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
	else cout << "�޴˼�¼" << endl;
}
void find2(char name[8])  //�����û���Ϊ�ؼ��ֵĹ�ϣ���в����û���Ϣ 
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
	else cout << "�޴˼�¼" << endl;
}
char find3(char num[11])
{
	hash1(num);//�����ϣ������ֵ
	int x = 1;
	while (num[key] != key)//�����ͻ
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
	Czy = 1; //��2,3,4,5,....... 
	while (1) {
		Czy++; //��2,3,4,5,....... 
		if (Czy % 2 == 0) {
			if (table->data[(key + (Czy / 2) * (Czy / 2)) % MAXSIZE].Name[0] == 0)
				return (key + (Czy / 2) * (Czy / 2)) % MAXSIZE;
		}
		else if (Czy % 2 != 0) {
			if ((key - (Czy / 2) * (Czy / 2)) < 0) continue;//�����Ǽ�����Ҫע�⸺������ȡģ 
			if (table->data[(key - (Czy / 2) * (Czy / 2)) % MAXSIZE].Name[0] == 0)
				return (key - (Czy / 2) * (Czy / 2)) % MAXSIZE;
		}
	}
	//return -1;
}*/
void save() //�����û���Ϣ 
{
	int i;
	node* p;
	for (i = 0; i < 20; i++)
	{
		p = studynum[i]->next;
		while (p)
		{
			fstream iiout("out.txt", ios::out); //����һ���ļ�������iiout
			iiout << p->name << "_" << p->address << "_" << p->num << "_" << p->phone << endl;  //����Ϣ�����ļ�
			p = p->next;
		}
	}

}

void menu() //�˵� 
{
	cout << "                                     ��ϣ��ͨѶ¼" << endl;
	cout << "                                     0.��Ӽ�¼" << endl;
	cout << "                                     2.������ϣ" << endl;
	cout << "                                     3.���Ҽ�¼" << endl;
	cout << "                                     4.ѧ�Ź�ϣ" << endl;
	cout << "                                     5.��ռ�¼" << endl;
	cout << "                                     6.�����¼" << endl;
	cout << "                                     7.�˳�ϵͳ" << endl;
	cout << "                                     8.�����¼" << endl;
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
			cout << "8������ѯ" << endl; cout << "9ѧ�Ų�ѯ" << endl;
			int b;
			cin >> b;
			if (b == 9)
			{
				cout << "������ѧ��:" << endl;
				cin >> num;
				cout << "������ҵ���Ϣ:" << endl;
				find(num);
			}
			else
			{
				cout << "����������:" << endl;
				cin >> name;
				cout << "������ҵ���Ϣ:" << endl;
				find2(name);
			}
		}
		if (sel == 2)
		{
			cout << "������ϣ���:" << endl;
			list2();
		}

		if (sel == 0)
		{
			//cout << "������Ҫ��ӵ�����:" << endl;
			apend();
		}
		if (sel == 4)
		{
			cout << "ѧ�Ź�ϣ���:" << endl;
			list();
		}
		if (sel == 5)
		{
			cout << "�б������:" << endl;
			create(); create2();
		}
		if (sel == 6)
		{
			cout << "ͨ��¼�ѱ���:" << endl;
			save();
		}
		if (sel == 8)
		{
			cout << "ͨ��¼���:" << endl;
			outout();
		}
		if (sel == 7) return 0;


	}

	return 0;

}