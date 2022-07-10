#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <stack>

using namespace std;

struct BiTreeNode 
{
    char data;  // �洢����
    BiTreeNode* left;  // ������
    BiTreeNode* right;  // ������
};

void show_Menu();  // ��ʾ�˵�
BiTreeNode* CreatBiTree(char* s, int &i, int len);  // �����������������
void InOrder(BiTreeNode* root);  // �������
void PreOrder(BiTreeNode* root);  // �������
void PostOrder(BiTreeNode* root);  // �������
bool getPathToTarget(BiTreeNode* root, char ch, stack<BiTreeNode*>& path);  // ��ôӸ��ڵ㵽ָ���ڵ��·��
void printPath(stack<BiTreeNode*> path);  // ��ӡ·��

int main() 
{
	char ch;
	int i = 0, len = 0;
	char str[200];
	stack<BiTreeNode*> path;
	BiTreeNode* root;
	int select;
	show_Menu();
	
	while (true)
		{
			cout << "������ѡ��:";
			cin >> select;
			switch (select)
			{
			case 1:  
				cout << "�������������˳��,��Ҷ�ӽڵ������#���,����(ABC#):";
				scanf("%s", str);  // ��ȡ����������������
				len = int(strlen(str));
				root = CreatBiTree(str, i, len);
				break;
				
			case 2:  
				InOrder(root);  // �������
				cout << endl;
				break;
				
			case 3:  
				PreOrder(root);  // �������
				cout << endl;
				break;
				
			case 4: 
				PostOrder(root);  // �������
				cout << endl;
				break;
				
			case 5: 
				cout << "������Ŀ��ڵ��ֵ:" ;
				cin >> ch;
				while (!path.empty()) path.pop();
				getPathToTarget(root, ch, path);  // ��ôӸ��ڵ㵽ָ���ڵ��·��
				printPath(path);
				break;
		
			case 6:
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
	cout << "+***************************************+\n";
	cout << "|      1�������������������            |\n";
	cout << "|      2���������                      |\n";
	cout << "|      3���������                      |\n";
	cout << "|      4���������                      |\n";
	cout << "|      5����ôӸ��ڵ㵽ָ���ڵ��·��  |\n";
	cout << "|      6����ʾ�˵�                      |\n";
	cout << "|      0���˳�����                      |\n";
	cout << "+***************************************+\n";
	cout << "|         �����20-1  ����ŵ            |\n";
	cout << "+***************************************+\n";
}

// �������������������
BiTreeNode* CreatBiTree(char* s, int &i, int len)
{
    BiTreeNode* root = (BiTreeNode*)malloc(sizeof(BiTreeNode));
    char tmp = s[i ++ ];
    if (i >= len || tmp == '#')
    {
        root = NULL;     
    }
    else 
    {   
        root->data = tmp;
        root->left = CreatBiTree(s, i, len);
        root->right = CreatBiTree(s, i, len);
    }
    return root;
}


// �������
void InOrder(BiTreeNode* root)
{
    if (root)
    {
        InOrder(root->left);
        printf("%c", root->data);
        InOrder(root->right);
    }

}


// �������
void PreOrder(BiTreeNode* root)
{
    if (root)
    {
        printf("%c", root->data);
        PreOrder(root->left);
        PreOrder(root->right);
    }
}


// �������
void PostOrder(BiTreeNode* root)
{
    if (root)
    {
        PostOrder(root->left);
        PostOrder(root->right);
        printf("%c", root->data);
    }

}

bool getPathToTarget(BiTreeNode* root, char ch, stack<BiTreeNode*>& path) 
{
    if (root == NULL) 
        return false;

    path.push(root);

    if (root->data == ch)
        return true;
    if (getPathToTarget(root->left, ch, path)) 
        return true; 
    if (getPathToTarget(root->right, ch, path))
        return true;

    path.pop();
    return false;
}

void printPath(stack<BiTreeNode*> path) 
{
	int len = path.size();
	char res[100];
	for (int i = len; i != 0; i -- )
	{
		BiTreeNode* tmp = path.top();
		path.pop();
		res[i] = tmp->data;
	}
	for (int i = 1; i <= len; i ++ )
	{
		cout << res[i] << ' ';
	}
	cout << endl;
}
