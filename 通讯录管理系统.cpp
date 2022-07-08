#include <iostream>
#include<string>
#include<conio.h>
#include<cstdlib>
#include<fstream>


using namespace std;

struct Person  // ��ϵ��
{
	int no;  // ���
	string name;  // ����
	int sex;  // �Ա�
	string tel;  // �绰
	string _qq;  // QQ
	string wechat;  // ΢�ź�
	string addr;  // ͨ�ŵ�ַ
	string birth;  // ����
	
	Person* next;
};

struct AddressBooks  // ͨѶ¼
{
	Person* head;
	int cnt;
};

void show_Menu();  // ��ʾ�˵�
void show(Person* p);  // ������ϵ����ʾ
void add_Person(AddressBooks* abs);  // �����ϵ��
void show_Person(AddressBooks* abs);  // ��ʾ��ϵ��
int find_Person(AddressBooks* abs);  // �����ϵ�˴���
void delete_Person(AddressBooks* abs);  // ɾ����ϵ��
void lookUp_Peoson_byName(AddressBooks* abs);  // ������ϵ�� ��������
void lookUp_Peoson_bySex(AddressBooks* abs);  // ������ϵ�� �����Ա�
void lookUp_Peoson_byBirth(AddressBooks* abs);  // ������ϵ�� ��������
void modify_Peoson(AddressBooks* abs);  // �޸���ϵ��
void clean_All_Peoson(AddressBooks* abs);  // �����ϵ��
void read_File(AddressBooks* abs);  // ��ȡ�ļ�


int main()
{
	int select = 0;
	AddressBooks abs;
	abs.cnt = 0;
	abs.head = new Person;
	abs.head->next = nullptr;
	
	show_Menu();  // ��ʾ�˵�
	while (true)
	{
		cout << "������ѡ��:";
		cin >> select;
		switch (select)
		{
		case 1:  
			add_Person(&abs);  // �����ϵ��
			break;
			
		case 2:  
			show_Person(&abs);  // ��ʾ��ϵ��
			break;
			
		case 3:  
			delete_Person(&abs);  // ɾ����ϵ��
			break;
			
		case 4: 
			lookUp_Peoson_byName(&abs);  // ������ϵ�� ��������
			break;
			
		case 5: 
			lookUp_Peoson_bySex(&abs);  // ������ϵ�� �����Ա�
			break;
			
		case 6: 
			lookUp_Peoson_byBirth(&abs);  // ������ϵ�� ��������
			break;
			
		case 7:
			modify_Peoson(&abs);  // �޸���ϵ��
			break;
			
		case 8: 
			clean_All_Peoson(&abs);  // �����ϵ��
			break;
			
		case 9: 
			read_File(&abs);  // ��ȡ�ļ�
			break;
		
		case 10:
			show_Menu();  // ��ʾ�˵�
			break;
			
		case 0:  //�˳�ͨѶ¼
			cout << "�˳�����......" << endl;
			return 0;
			break;
			
		default :
			cout << "�������......" << endl<<"������(1��2��3..)";
		}
	}

	return 0;
}


// ��ʾ�˵�
void show_Menu()
{
	cout << "+***************************+\n";
	cout << "|      1��������ϵ��        |\n";
	cout << "|      2����ʾ��ϵ��        |\n";
	cout << "|      3��ɾ����ϵ��        |\n";
	cout << "|      4��������ϵ��(����)  |\n";
	cout << "|      5��������ϵ��(�Ա�)  |\n";
	cout << "|      6��������ϵ��(����)  |\n";
	cout << "|      7���޸���ϵ��        |\n";
	cout << "|      8�������ϵ��        |\n";
	cout << "|      9����ȡ�ļ�          |\n";
	cout << "|     10����ʾ�˵�          |\n";
	cout << "|      0���˳�����          |\n";
	cout << "+***************************+\n";
	cout << "|    �����20-1  ����ŵ     |\n";
	cout << "+***************************+\n";
}


// ������ϵ����ʾ
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


// �����ϵ��
void add_Person(AddressBooks* abs)
{
	//���ļ��ж�ȡ
	ofstream ofs;
	ofs.open("ͨѶ¼.txt", ios::out);
	
	Person* tmp = new Person;
	tmp->no = ++ abs->cnt;
	
	string name;
	cout << "����������:" << endl;
	cin >> name;
	ofs << name << "\t";
	tmp->name = name;
	
	int sex;
	while (true)
	{
		cout << "�������Ա�:" << endl << "1:man" << endl << "2:woman" << endl;
		cin >> sex;
		if (sex == 1 || sex == 2)
	    {
			tmp->sex = sex;
			ofs << sex << "\t";
		    break;
	     }
	    else
	    {
			cout << "�����ʽ����     ������ \"1\" �� \"2\" " << endl;
	    }
	}
	
	string tel;
	cout << "������绰:" << endl;
	cin >> tel;
	ofs << tel << "\t";
	tmp->tel = tel;
	
	string _qq;
	cout << "������QQ:"<<endl;
	cin >> _qq;
	tmp->_qq = _qq;
	ofs << _qq << "\t";
	
	string wechat;
	cout << "������΢�ź�:"<<endl;
	cin >> wechat;
	tmp->wechat = wechat;
	ofs << wechat << "\t";
			
	string addr;
	cout << "������ͨ�ŵ�ַ:"<<endl;
	cin >> addr;
	tmp->addr = addr;
	ofs << addr << "\t";
	
	string birth;
	cout << "����������:"<<endl;
	cin >> birth;
	tmp->birth = birth;
	ofs << birth << "\t";
	
	tmp->next = nullptr;
	Person* p = abs->head;
	while (p->next) p = p->next;
	p->next = tmp;
	
	ofs.close();
}


// ��ʾ��ϵ��
void show_Person(AddressBooks* abs)
{
	if (abs->cnt == 0)
	{
		cout << "ͨѶ¼�ǿյ�" << endl;
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


// �����ϵ�˴���
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


//ɾ����ϵ��
void delete_Person(AddressBooks* abs)
{
	cout << "������Ҫɾ������ϵ�˵�����:" << endl;
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
		cout << "�ɹ�ɾ��" << endl;
	}
	else
	{
		cout << "�����������������ͨѶ¼��" << endl;
	}
}


//������ϵ�� ��������
void lookUp_Peoson_byName(AddressBooks* abs)
{
	cout << "����������:";
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
		cout << "���������û����ͨѶ¼��" << endl;
	}
}


// ������ϵ�� �����Ա�
void lookUp_Peoson_bySex(AddressBooks* abs)
{
	int sex;
	cout << "�������Ա�1:MAN,2:WOMAN,����1 �� 2:" << endl;
	cin >> sex;
	if (abs->cnt == 0)
	{
		cout << "ͨѶ¼Ϊ��" << endl;
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


// ������ϵ�� ��������
void lookUp_Peoson_byBirth(AddressBooks* abs)
{
	string birth;
	cout << "����������,��ʽ2001.01.08:" << endl;
	cin >> birth;
	if (abs->cnt == 0)
	{
		cout << "ͨѶ¼Ϊ��" << endl;
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

// �޸���ϵ��
void modify_Peoson(AddressBooks* abs)
{
	cout << "������Ҫ�޸ĵ���ϵ������:";
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
		cout << "����������:" << endl;
		cin >> name;
		p->name = name;
		
		int sex;
		while (true)
		{
			cout << "�������Ա�:" << endl << "1:man" << endl << "2:woman" << endl;
			cin >> sex;
			if (sex == 1 || sex == 2)
		    {
				p->sex = sex;
			    break;
		     }
		    else
		    {
				cout << "�����ʽ����     ������ \"1\" �� \"2\" " << endl;
		    }
		}
		
		string tel;
		cout << "������绰:" << endl;
		cin >> tel;
		p->tel = tel;
		
		string _qq;
		cout << "������QQ:"<<endl;
		cin >> _qq;
		p->_qq = _qq;
		
		string wechat;
		cout << "������΢�ź�:"<<endl;
		cin >> wechat;
		p->wechat = wechat;
				
		string addr;
		cout << "������ͨ�ŵ�ַ:"<<endl;
		cin >> addr;
		p->addr = addr;
		
		string birth;
		cout << "����������:"<<endl;
		cin >> birth;
		p->birth = birth;
		
		cout << "�޸ĳɹ�" << endl;
	}
	else
	{
		cout << "����������ͨѶ¼��" << endl;
	}
}


//�����ϵ��
void clean_All_Peoson(AddressBooks* abs)
{
	char choice;
	cout << "ȷ��Ҫɾ��������ϵ����?     (Y/N)" << endl;
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
		cout << "ͨѶ¼�Ѿ����." << endl;
	}
	else
	{
		return;
	}
}

// ��ȡ�ļ�
void read_File(AddressBooks* abs)
{
	Person* p = abs->head;
	while (p->next) p = p->next;
	
	string new_file;
	cout << "������Ҫ��ȡ���ļ�����";
	cin >> new_file;
	fstream file;
	file.open(new_file.c_str(), ios::in);
	if (file.bad())
	{
		cout << "�ļ���ʧ�ܣ�" << endl;
		return;
	}
	int len = 0;
	file >> len;
	while (!len)
	{
		cout << "�ļ������쳣��" << endl;
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
	cout << "�ļ�����ɹ���" << endl;
	return;
}
