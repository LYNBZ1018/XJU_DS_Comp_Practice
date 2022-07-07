#include <iostream>
#include<string>
#include<conio.h>
#include<Windows.h>
#include<cstdlib>
#include<fstream>

#define MAX 1000

using namespace std;

struct Person  // 联系人
{
	int no;  // 编号
	string name;  // 姓名
	int sex;  // 性别
	string tel;  // 电话
	string _qq;  // QQ
	string wechat;  // 微信号
	string addr;  // 通信地址
	string birth;  // 生日
	
	Person* next;
};

struct AddressBooks  // 通讯录
{
	Person* head;
	int cnt;
};

void show_Menu();  // 显示菜单  
void add_Person(AddressBooks* abs);  // 添加联系人
void show_Person(AddressBooks* abs);  // 显示联系人
int find_Person(AddressBooks* abs);  // 检测联系人存在
void delete_Person(AddressBooks* abs);  // 删除联系人
void lookUp_Peoson(AddressBooks* abs);  // 查找联系人
void modify_Peoson(AddressBooks* abs);  // 修改联系人
void clean_All_Peoson(AddressBooks* abs);  // 清空联系人


int main()
{
	int select = 0;
	AddressBooks abs;
	abs.cnt = 0;
	abs.head = new Person;
	abs.head->next = nullptr;
	
	while (true)
	{
		show_Menu();  // 显示菜单
		cout << "请输入选项:";
		cin >> select;
		switch (select)
		{
		case 1:  
			add_Person(&abs);  // 添加联系人
			break;
			
		case 2:  
			show_Person(&abs);  // 显示联系人
			break;
			
		case 3:  
			delete_Person(&abs);  // 删除联系人
			break;
			
		case 4: 
			lookUp_Peoson(&abs);  // 查找联系人
			break;
			
		case 5:
			modify_Peoson(&abs);  // 修改联系人
			break;
			
		case 6: 
			clean_All_Peoson(&abs);  // 清空联系人
			break;
			
		case 7:  //退出通讯录
			cout << "退出程序......" << endl;
			return 0;
			break;
			
		default :
			cout << "输入错误......" << endl<<"请输入(1、2、3..)";
		}
		system("cls");  // 清屏
	}

	return 0;
}


// 显示菜单
void show_Menu()
{
	cout << "+***************************+\n";
	cout << "|      1、增加联系人        |\n";
	cout << "|      2、显示联系人        |\n";
	cout << "|      3、删除联系人        |\n";
	cout << "|      4、查找联系人        |\n";
	cout << "|      5、修改联系人        |\n";
	cout << "|      6、清空联系人        |\n";
	cout << "|      7、退出程序          |\n";
	cout << "+***************************+\n";
	cout << "|    计算机20-1  刘宇诺     |\n";
	cout << "+***************************+\n";
}


// 添加联系人
void add_Person(AddressBooks* abs)
{
	//从文件中读取
	ofstream ofs;
	ofs.open("通讯录.txt", ios::out);
	
	Person* tmp = new Person;
	tmp->no = ++ abs->cnt;
	
	string name;
	cout << "请输入姓名:" << endl;
	cin >> name;
	ofs << name << "\t";
	tmp->name = name;
	
	int sex;
	while (true)
	{
		cout << "请输入性别:" << endl << "1:man" << endl << "2:woman" << endl;
		cin >> sex;
		if (sex == 1 || sex == 2)
	    {
			tmp->sex = sex;
			ofs << sex << "\t";
		    break;
	     }
	    else
	    {
			cout << "输入格式错误     请输入 \"1\" 或 \"2\" " << endl;
	    }
	}
	
	string tel;
	cout << "请输入电话:" << endl;
	cin >> tel;
	ofs << tel << "\t";
	tmp->tel = tel;
	
	string _qq;
	cout << "请输入QQ:"<<endl;
	cin >> _qq;
	tmp->_qq = _qq;
	ofs << _qq << "\t";
	
	string wechat;
	cout << "请输入微信号:"<<endl;
	cin >> wechat;
	tmp->wechat = wechat;
	ofs << wechat << "\t";
			
	string addr;
	cout << "请输入通信地址:"<<endl;
	cin >> addr;
	tmp->addr = addr;
	ofs << addr << "\t";
	
	string birth;
	cout << "请输入生日:"<<endl;
	cin >> birth;
	tmp->birth = birth;
	ofs << birth << "\t";
	
	tmp->next = nullptr;
	Person* p = abs->head;
	while (p->next) p = p->next;
	p->next = tmp;
	
	ofs.close();
	cout << "成功加入新联系人" << endl;
	cout << "按下 enter 键继续" << endl;
	_getch();
	system("cls");
	show_Menu();
}


// 显示联系人
void show_Person(AddressBooks* abs)
{
	if (abs->cnt == 0)
	{
		cout << "通讯录是空的" << endl;
		
		cout << "按下 enter 键继续" << endl;
		_getch();
		system("cls");
		show_Menu();
		return;
	}
	else
	{
		Person* p = abs->head->next;
		while (p)
		{
			cout << "No:  " << p->no << "\t";
			cout << "Name:  " << p->name << "\t";
			cout << "Sex:   " << (p->sex == 1 ?  "MAN":"WOMAN" ) << "\t";
			cout << "Tel:  " << p->tel << "\t";
			cout << "QQ:   " <<  p->_qq  << "\t";
			cout << "WeChat:   " << p->wechat << "\t";
			cout << "Address:   " << p->addr << "\t";
			cout << "Birth:  " << p->birth << endl;
			
			p = p->next;
		}
	}
	
	cout << "按下 enter 键继续" << endl;
	_getch();
	show_Menu();
}


// 检测联系人存在
int find_Person(AddressBooks* abs)
{
	int i = 0;
	string name;
	cin >> name;
	Person* p = abs->head->next;
	while (p != nullptr)
	{
		i ++ ;
		if (p->name == name)
			return i;
		p = p->next;
	}
	
	return -1;
}


//删除联系人
void delete_Person(AddressBooks* abs)
{
	cout << "请输入要删除的联系人的姓名:" << endl;
	int ans = find_Person(abs);
	if (ans!=-1)
	{
		Person* p = abs->head;
		for (int i = 0; i < ans - 1; i ++ )
		{
			p = p->next;
		}
		Person* q = p->next;
		p->next = q->next;
		delete q;
		abs->cnt --;
		cout << "成功删除" << endl;
		
		cout << "按下 enter 键继续" << endl;
		_getch();
		system("cls");
		show_Menu();
	}
	else
	{
		cout << "输入的姓名不存在与通讯录中" << endl;
		
		cout << "按下 enter 键继续" << endl;
		_getch();
		system("cls");
		show_Menu();
	}
}


//查找联系人
void lookUp_Peoson(AddressBooks* abs)
{
	cout << "Please input the name you want to look up: ";
	int ans = find_Person(abs);
	if (ans != -1)
	{
		Person* p = abs->head;
		for (int i =0 ; i< ans; i ++ )
		{
			p = p->next;
		}
		cout << "No:  " << p->no << "\t";
		cout << "Name:  " << p->name << "\t";
		cout << "Sex:   " << (p->sex == 1 ?  "MAN":"WOMAN" ) << "\t";
		cout << "Tel:  " << p->tel << "\t";
		cout << "QQ:   " <<  p->_qq  << "\t";
		cout << "WeChat:   " << p->wechat << "\t";
		cout << "Address:   " << p->addr << "\t";
		cout << "Birth:  " << p->birth << endl;
		
		cout << "按下 enter 键继续" << endl;
		_getch();
		system("cls");
		show_Menu();
	}
	else
	{
		cout << "输入的姓名没有在通讯录中" << endl;
		
		cout << "按下 enter 键继续" << endl;
		_getch();
		system("cls");
		show_Menu();
	}
}


// 修改联系人
void modify_Peoson(AddressBooks* abs)
{
	cout << "请输入要修改的联系人姓名:";
	int ans = find_Person(abs);
	if (ans != -1)
	{
		Person* p = abs->head;
		for (int i =0 ; i< ans; i ++ )
		{
			p = p->next;
		}
		
		cout << "No:  " << p->no << "\t";
		cout << "Name:  " << p->name << "\t";
		cout << "Sex:   " << (p->sex == 1 ?  "MAN":"WOMAN" ) << "\t";
		cout << "Tel:  " << p->tel << "\t";
		cout << "QQ:   " <<  p->_qq  << "\t";
		cout << "WeChat:   " << p->wechat << "\t";
		cout << "Address:   " << p->addr << "\t";
		cout << "Birth:  " << p->birth << endl;
		
		string name;
		cout << "请输入姓名:" << endl;
		cin >> name;
		p->name = name;
		
		int sex;
		while (true)
		{
			cout << "请输入性别:" << endl << "1:man" << endl << "2:woman" << endl;
			cin >> sex;
			if (sex == 1 || sex == 2)
		    {
				p->sex = sex;
			    break;
		     }
		    else
		    {
				cout << "输入格式错误     请输入 \"1\" 或 \"2\" " << endl;
		    }
		}
		
		string tel;
		cout << "请输入电话:" << endl;
		cin >> tel;
		p->tel = tel;
		
		string _qq;
		cout << "请输入QQ:"<<endl;
		cin >> _qq;
		p->_qq = _qq;
		
		string wechat;
		cout << "请输入微信号:"<<endl;
		cin >> wechat;
		p->wechat = wechat;
				
		string addr;
		cout << "请输入通信地址:"<<endl;
		cin >> addr;
		p->addr = addr;
		
		string birth;
		cout << "请输入生日:"<<endl;
		cin >> birth;
		p->birth = birth;
		
		cout << "修改成功" << endl;
		
		cout << "按下 enter 键继续" << endl;
		_getch();
		system("cls");
		show_Menu();
	}
	else
	{
		cout << "该姓名不在通讯录中" << endl;
		
		cout << "按下 enter 键继续" << endl;
		_getch();
		system("cls");
		show_Menu();
	}
}


//清空联系人
void clean_All_Peoson(AddressBooks* abs)
{
	char choice;
	cout << "确定要删除所有联系人吗?     (Y/N)" << endl;
	cin >> choice;
	if (choice =='Y')
	{
		abs->cnt = 0;
		Person* p = abs->head->next;
		while(p != nullptr)
		{
			Person* q = p;
			p = p->next;
			delete q;
		}
		cout << "通讯录已经清空." << endl;
		
		cout << "按下 enter 键继续" << endl;
		_getch();
		system("cls");
		show_Menu();
	}
	else
	{
		return;
	}
}
