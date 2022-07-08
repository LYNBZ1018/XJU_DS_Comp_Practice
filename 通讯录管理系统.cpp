#include <iostream>
#include<string>
#include<conio.h>
#include<cstdlib>
#include<fstream>


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
void show(Person* p);  // 单个联系人显示
void add_Person(AddressBooks* abs);  // 添加联系人
void show_Person(AddressBooks* abs);  // 显示联系人
int find_Person(AddressBooks* abs);  // 检测联系人存在
void delete_Person(AddressBooks* abs);  // 删除联系人
void lookUp_Peoson_byName(AddressBooks* abs);  // 查找联系人 根据姓名
void lookUp_Peoson_bySex(AddressBooks* abs);  // 查找联系人 根据性别
void lookUp_Peoson_byBirth(AddressBooks* abs);  // 查找联系人 根据生日
void modify_Peoson(AddressBooks* abs);  // 修改联系人
void clean_All_Peoson(AddressBooks* abs);  // 清空联系人
void read_File(AddressBooks* abs);  // 读取文件


int main()
{
	int select = 0;
	AddressBooks abs;
	abs.cnt = 0;
	abs.head = new Person;
	abs.head->next = nullptr;
	
	show_Menu();  // 显示菜单
	while (true)
	{
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
			lookUp_Peoson_byName(&abs);  // 查找联系人 根据姓名
			break;
			
		case 5: 
			lookUp_Peoson_bySex(&abs);  // 查找联系人 根据性别
			break;
			
		case 6: 
			lookUp_Peoson_byBirth(&abs);  // 查找联系人 根据生日
			break;
			
		case 7:
			modify_Peoson(&abs);  // 修改联系人
			break;
			
		case 8: 
			clean_All_Peoson(&abs);  // 清空联系人
			break;
			
		case 9: 
			read_File(&abs);  // 读取文件
			break;
		
		case 10:
			show_Menu();  // 显示菜单
			break;
			
		case 0:  //退出通讯录
			cout << "退出程序......" << endl;
			return 0;
			break;
			
		default :
			cout << "输入错误......" << endl<<"请输入(1、2、3..)";
		}
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
	cout << "|      4、查找联系人(姓名)  |\n";
	cout << "|      5、查找联系人(性别)  |\n";
	cout << "|      6、查找联系人(生日)  |\n";
	cout << "|      7、修改联系人        |\n";
	cout << "|      8、清空联系人        |\n";
	cout << "|      9、读取文件          |\n";
	cout << "|     10、显示菜单          |\n";
	cout << "|      0、退出程序          |\n";
	cout << "+***************************+\n";
	cout << "|    计算机20-1  刘宇诺     |\n";
	cout << "+***************************+\n";
}


// 单个联系人显示
void show(Person* p)
{
	cout << "No:  " << p->no << "\t";
	cout << "Name:  " << p->name << "\t";
	cout << "Sex:   " << (p->sex == 1 ?  "MAN":"WOMAN" ) << "\t";
	cout << "Tel:  " << p->tel << "\t";
	cout << "QQ:   " <<  p->_qq  << "\t";
	cout << "WeChat:   " << p->wechat << "\t";
	cout << "Address:   " << p->addr << "\t";
	cout << "Birth:  " << p->birth << endl;
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
}


// 显示联系人
void show_Person(AddressBooks* abs)
{
	if (abs->cnt == 0)
	{
		cout << "通讯录是空的" << endl;
		return;
	}
	else
	{
		Person* p = abs->head->next;
		while (p)
		{
			show(p);
			p = p->next;
		}
	}
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
	}
	else
	{
		cout << "输入的姓名不存在与通讯录中" << endl;
	}
}


//查找联系人 根据姓名
void lookUp_Peoson_byName(AddressBooks* abs)
{
	cout << "请输入姓名:";
	int ans = find_Person(abs);
	if (ans != -1)
	{
		Person* p = abs->head;
		for (int i =0 ; i< ans; i ++ )
		{
			p = p->next;
		}
		
		show(p);
	}
	else
	{
		cout << "输入的姓名没有在通讯录中" << endl;
	}
}


// 查找联系人 根据性别
void lookUp_Peoson_bySex(AddressBooks* abs)
{
	int sex;
	cout << "请输入性别1:MAN,2:WOMAN,输入1 或 2:" << endl;
	cin >> sex;
	if (abs->cnt == 0)
	{
		cout << "通讯录为空" << endl;
		return;
	} 
	
	Person* p = abs->head;
	while(p->next)
	{
		if (p->next->sex == sex)
		{
			show(p->next);
		}
		p = p->next;
	}
} 


// 查找联系人 根据生日
void lookUp_Peoson_byBirth(AddressBooks* abs)
{
	string birth;
	cout << "请输入生日,格式2001.01.08:" << endl;
	cin >> birth;
	if (abs->cnt == 0)
	{
		cout << "通讯录为空" << endl;
		return;
	} 
	
	Person* p = abs->head;
	while(p->next)
	{
		if (p->next->birth == birth)
		{
			show(p->next);
		}
		p = p->next;
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
	}
	else
	{
		cout << "该姓名不在通讯录中" << endl;
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
		abs->head->next = nullptr;
		cout << "通讯录已经清空." << endl;
	}
	else
	{
		return;
	}
}

// 读取文件
void read_File(AddressBooks* abs)
{
	Person* p = abs->head;
	while (p->next) p = p->next;
	
	string new_file;
	cout << "请输入要读取的文件名：";
	cin >> new_file;
	fstream file;
	file.open(new_file.c_str(), ios::in);
	if (file.bad())
	{
		cout << "文件打开失败！" << endl;
		return;
	}
	int len = 0;
	file >> len;
	while (!len)
	{
		cout << "文件数据异常！" << endl;
		return;
	}

	file.get();
	while (len--)
	{
		Person* tmp = new Person;
		tmp->next = nullptr;
		file >> tmp->no;
		file >> tmp->name;
		file >> tmp->sex;
		file >> tmp->tel;
		file >> tmp->_qq;
		file >> tmp->wechat;
		file >> tmp->addr;
		file >> tmp->birth;
		p->next = tmp;
		abs->cnt ++ ;
		p = p->next;
	}
	file.close();
	cout << "文件读入成功！" << endl;
	return;
}
