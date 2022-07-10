#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <stack>

using namespace std;

struct BiTreeNode 
{
    char data;  // 存储数据
    BiTreeNode* left;  // 左子树
    BiTreeNode* right;  // 右子树
};

void show_Menu();  // 显示菜单
BiTreeNode* CreatBiTree(char* s, int &i, int len);  // 先序遍历创建二叉树
void InOrder(BiTreeNode* root);  // 中序遍历
void PreOrder(BiTreeNode* root);  // 先序遍历
void PostOrder(BiTreeNode* root);  // 后序遍历
bool getPathToTarget(BiTreeNode* root, char ch, stack<BiTreeNode*>& path);  // 获得从根节点到指定节点的路径
void printPath(stack<BiTreeNode*> path);  // 打印路径

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
			cout << "请输入选项:";
			cin >> select;
			switch (select)
			{
			case 1:  
				cout << "请输入先序遍历顺序,在叶子节点后输入#标记,比如(ABC#):";
				scanf("%s", str);  // 读取先序结果创建二叉树
				len = int(strlen(str));
				root = CreatBiTree(str, i, len);
				break;
				
			case 2:  
				InOrder(root);  // 中序遍历
				cout << endl;
				break;
				
			case 3:  
				PreOrder(root);  // 先序遍历
				cout << endl;
				break;
				
			case 4: 
				PostOrder(root);  // 后序遍历
				cout << endl;
				break;
				
			case 5: 
				cout << "请输入目标节点的值:" ;
				cin >> ch;
				while (!path.empty()) path.pop();
				getPathToTarget(root, ch, path);  // 获得从根节点到指定节点的路径
				printPath(path);
				break;
		
			case 6:
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
	cout << "+***************************************+\n";
	cout << "|      1、先序遍历创建二叉树            |\n";
	cout << "|      2、中序遍历                      |\n";
	cout << "|      3、先序遍历                      |\n";
	cout << "|      4、后序遍历                      |\n";
	cout << "|      5、获得从根节点到指定节点的路径  |\n";
	cout << "|      6、显示菜单                      |\n";
	cout << "|      0、退出程序                      |\n";
	cout << "+***************************************+\n";
	cout << "|         计算机20-1  刘宇诺            |\n";
	cout << "+***************************************+\n";
}

// 用先序遍历创建二叉树
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


// 中序遍历
void InOrder(BiTreeNode* root)
{
    if (root)
    {
        InOrder(root->left);
        printf("%c", root->data);
        InOrder(root->right);
    }

}


// 先序遍历
void PreOrder(BiTreeNode* root)
{
    if (root)
    {
        printf("%c", root->data);
        PreOrder(root->left);
        PreOrder(root->right);
    }
}


// 后序遍历
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
