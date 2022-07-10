#include <cstdio>
#include <cstdlib>
#include <string.h>
#include <time.h>
#include <iostream>
#include <algorithm>
#include <stack>

#define M 20  // 校园景点数量
#define INF 0x3f3f3f3f  //int最大值

using namespace std;

typedef struct
{
    int num;  // 景点编号
    char name[20];  // 景点名称
    char introduction[300];  // 景点介绍
} Attractions;

typedef struct
{
    Attractions att[M];
    int edges[M][M];
    int Nodes_Num;  // 总结点数
	int edges_Num;  // 总边数
}Campus;

int check(int ch);   // 判断游客编号是否输入错误
void getCampus(Campus* g);  // 创建地图
void Search(Campus *g);  // 查看景点信息                                            
void shortPath(Campus *g);  // 求所有景点之间的最短路径长度及其路径
void Floyd_Print(Campus *g, int start, int end);  // 输出路径上的中间点
void print_shortPath(Campus *g);  //  打印最短路径
void print_AllPath(Campus *g);  // 输出所有路径
void DFS_AllPath(Campus* g ,int start, int end, int &top, int &count);  // 利用DFS求全路径
void bestPath(Campus *g);  // 最佳路径
 
void putMap();  // 输出校园平面图
int putMenu();  // 输出主菜单
void Exit();   // 系统退出界面

int main() {
	Campus g; 
	getCampus(&g);  // 从文件读取信息建立校园地图
	shortPath(&g);  // 通过Floyd求出distence表与path表
		while (true) {                                                          
			switch (putMenu()) {  // 打印主菜单
			case 1:system("cls"); putMap();break;   // 景点查询
			case 2:system("cls"); Search(&g); break;  // 景点信息查询
			case 3:system("cls"); putMap(); print_shortPath(&g); break; // 两景点间最短路径查询
			case 4:system("cls"); putMap(); print_AllPath(&g); break;  // 两景点间所有路线查询
			case 5:system("cls"); putMap(); bestPath(&g); break;  // 多景点间访问最优路线查询
			case 6:system("cls"); Exit(); break;   // 退出系统
			default:printf("             对不起！没有该选项对应的操作。\n\n");
			}
			system("pause");
			system("cls");  // 清屏
		}
	return 0;
}


// 判断游客编号是否输入错误
int check(int ch){
	if(ch < 0 || ch > 16)
	    {
	        printf("\n");
	        printf("您的输入有误，请输入0~12之间的数字！\n");
	        return 0;
	    }
    return 1;
}


// 创建地图
void getCampus(Campus* g)
{
    int ta, tb, tmp;  // 临时变量
    FILE *rf;
    rf = fopen("./map.txt", "r");  // 文件读取
    if(!rf)  // 如果文件读取失败，返回error！
	{
        printf("ERROR!\n");
        return;
    }  
    else if(rf)
    {
        fscanf(rf,"%d %d", &g->Nodes_Num, &g->edges_Num);  // 文件读取总结点数和总边数
        for(int i = 1; i <= g->Nodes_Num; i++)
        {
        	// 读取文件景点编号，景点名称，景点简介
            fscanf(rf,"%d %s %s",&g->att[i].num,g->att[i].name,g->att[i].introduction); 
        }
        // 地图初始化：除了自己，其他点都是不可达
        for(int i = 0;i <= g->Nodes_Num; i++)
        {
            for(int j = 0; j <= g->Nodes_Num; j++)
            {
                if(i==j) g->edges[i][j]=0;
                else g->edges[i][j]=INF;
            }
        }
        // 得到边信息
        for(int i = 1; i <= g->edges_Num; i++)
        {
            fscanf(rf,"%d %d %d",&ta,&tb,&tmp);
            g->edges[ta][tb]=g->edges[tb][ta]=tmp;
        }
        fclose(rf); // 文件关闭
    }
}


// 查看景点信息
void Search(Campus *g)
{
    int number;  // 编号
    while(true)
    {
    	putMap();
        printf("请问您想查看哪个景点（请输入景点编号,输入0结束）:");
        scanf("%d",&number);
        system("cls"); //清空屏幕
        if(check(number))
        {
        	if(number == 0)break;
        	printf("\n景点编号:%d\n",g->att[number].num);
            printf("\n景点名称:%s\n",g->att[number].name);
		    printf("\n景点介绍:%s\n",g->att[number].introduction);
		    printf("\n");      
        }
    }
    
}


// Floyd算法求两景点间的一条最短的路径
int distence[M][M];  // 距离向量
int path[M][M];  // 路径向量
void shortPath(Campus *g) 
{
	for (int i = 1; i <= g->Nodes_Num; i ++ )  // 初始化距离向量矩阵与路径向量矩阵
		for (int j = 1; j <= g->Nodes_Num; j ++ ) 
		{
			distence[i][j] = g->edges[i][j];
			if (i != j && distence[i][j] != INF) path[i][j] = i;  //表示如果i和j相邻，i到j需要经过i
			else path[i][j] = -1;  // 否则用 -1代表当前两点不可达
		}

	for (int k = 1; k <= g->Nodes_Num; k ++ )  //递推求解每两景点的最短路径
		for (int i = 1; i <= g->Nodes_Num; i ++ )
			for (int j = 1; j <= g->Nodes_Num; j++)  // 更新distence[i][j]的值
				if (distence[i][j] > (distence[i][k] + distence[k][j]))  // 如果发现引入k点可以使得路径更短
				{ 
					distence[i][j] = distence[i][k] + distence[k][j];  // 更新最短路径长度
					path[i][j] = k;  // 更新最短路径上的经结点
				}
}


// 输出路径上的中间点
void Floyd_Print(Campus *g, int start, int end) 
{
	// 如果两点相邻或者两点不可达，结束递归
	if (path[start][end] == -1 || path[start][end] == end || path[start][end] == start)
		return;
	else {
		Floyd_Print(g, start, path[start][end]);  // 将中间点作为终点继续打印路径
		printf("%s->", g->att[path[start][end]].name); // 打印中间景点名字
		Floyd_Print(g, path[start][end], end);  // 将中间点作为起点继续打印路径
	}
}


/*输出并打印两点间的最短路径*/
void print_shortPath(Campus *g) {
	int start, end;  //起点编号，终点编号
	do {
		printf("         请输入起点编号：");
		scanf("%d", &start);
	} while (!check(start));
	do {
		printf("         请输入终点编号：");
		scanf("%d", &end);
	} while (!check(end));
	printf("             %s到%s的最短距离是：%dm\n", g->att[start].name, g->att[end].name, distence[start][end]);
	printf("             最佳游览路线：");
	printf("%s->", g->att[start].name);  // 输出路径上的起点
	Floyd_Print(g, start, end);  // 输出路径上的中间点
	printf("%s\n", g->att[end].name);  // 输出路径上的终点
}

int pathStack[M];//路径栈
int visited[M]; //判断是否已经经过
void print_AllPath(Campus *g)
{
    int flag=0;
    int start;  // 起点
    int end;  // 终点
    memset(pathStack, 0, sizeof(pathStack));  // 路径栈初始化
	memset(visited, 0, sizeof(visited));  // 标记数组初始化 
	int top = 0;   //初始化栈顶
	int count = 1; //初始化路径条数
    while(true)
    {
        printf("\n");
        printf("                请输入起点编号:");
        scanf("%d", &start);
        if(check(start))
        {
           flag = 1;
           if(1==flag) break;
        }
    }
    flag=0;  // flag重新置0
    while(true)
    {
        printf("\n");
        printf("                请输入终点编号:");
        scanf("%d", &end);
        if(check(end))
        {
            flag=1;
            if(1==flag)break;
        }
    }
    printf("\n");
    DFS_AllPath(g, start, end, top, count);
    printf("\n");
}


void DFS_AllPath(Campus *g, int start, int end, int &top, int &count)
{
    int dis=0;  //总 距离
    pathStack[top ++ ] = start; // 将起点入栈
    visited[start] = 1; //表示该点已经访问过
    for(int i = 1; i <= g->Nodes_Num; i ++ )  // 遍历与这个结点相邻的结点
    {
        if(g->edges[start][i] > 0 && g->edges[start][i] != INF && !visited[i])  // 如果与i不是自己并且这个点有可达路径并且未被访问过
        {
            if(i == end)  // 如果已经到达目的地
            {
                printf("             第%d条道路:", count ++ );  // 将该路径输出
                for(int j = 0; j < top; j ++ )
                {
                    printf("%s->",g->att[pathStack[j]].name);  // 输出该景点
                    if(j < top - 1)
                        dis = dis + g->edges[pathStack[j]][pathStack[j+1]]; 
                }
                dis = dis + g->edges[pathStack[top-1]][end];  // 计算最后一个边长1
                printf("%s\n",g->att[end].name);
                printf("             总长度为: %dm\n\n", dis);
            }
            else //如果还未达到
            {
                DFS_AllPath(g, i, end, top, count);  // 递归遍历
                top --  ;  // 出栈
                visited[i]=0;  // 释放该节点
            }
        }
    }
}


/*多景点间求最佳路径*/
void bestPath(Campus *g) {
	int vNum[M] = { 0 }, count = 1;  // 记录用户输入的编号信息
	int dis = 0;   // 统计全程路径总长
	printf("             请输入你要游览的第%d个景点的编号（输入0结束输入）：", count);
	scanf("%d", &vNum[count]);
	while (vNum[count] != 0 && count <= 12) {
		while (!check(vNum[count])) {
			printf("     请输入你要游览的第%d个景点编号：", count);
			scanf("%d", &vNum[count]);
		}
		if (vNum[count] == 0) break;
		printf("         请输入你要游览的第%d个景点编号：", ++count);
		scanf("%d", &vNum[count]);
	}
	printf("             已为您挑选最佳访问路径：");
	for (int i = 1; vNum[i] > 0 && vNum[i + 1] > 0; i++)  // 遍历所有输入的景点
	{       
		printf("%s->", g->att[vNum[i]].name);   // 输出路径上的起点
		Floyd_Print(g, vNum[i],vNum[i + 1]);   // 利用Floyd算法得到这两点之间的最短路径
		dis += distence[vNum[i]][vNum[i + 1]];  //算出最短路长度
	}
	printf("%s\n\n", g->att[vNum[count - 1]].name);  // 输出路径上的终点
	printf("             全程总长为：%dm\n\n", dis);
}


void putMap()
{
    printf("+***********************************************************************************+\n");                  
    printf("|                                 新疆大学导游图                                    |\n");
    printf("|***********************************************************************************|\n");
    printf("|                      1 正门                2 行政楼                               |\n");
    printf("|                      3 1号教学楼           4 交流中心                             |\n");
    printf("|                      5 图书馆              6 11号教学楼                           |\n"); 
    printf("|                      7 10号教学楼          8 三二一餐厅                           |\n");
    printf("|                      9 逸夫楼             10 小操场                               |\n");   
    printf("|                     11 体育馆             12 大操场                               |\n");
    printf("|                     13 汉餐第一食堂       14 科技楼                               |\n");     
    printf("|                      15 红湖               16 新园市场                            |\n");   
    printf("+***********************************************************************************+\n");

}


int putMenu()
{
	int op;
    printf("       +***********************************************************************************+\n");
    printf("       |                         欢迎使用新疆大学校园导航咨询系统                          |\n");
    printf("       |***********************************************************************************|\n");
    printf("       |                                   请选择服务:                                     |\n");
    printf("       |                                                                                   |\n");
    printf("       |             1.学校地图                      2.查看景点信息                        |\n");
    printf("       |                                                                                   |\n");
    printf("       |             3.寻找两景点之间的最短路径      4.寻找两景点之间所有路径              |\n");
    printf("       |                                                                                   |\n");
    printf("       |             5.路径规划                      6. 退出系统                           |\n");
    printf("       |                                                                                   |\n");
    printf("       +***********************************************************************************+\n");
    printf("\n\n");
    printf("             请根据你的需求选择操作：");
	scanf("%d", &op);
    return op;
}


void putEdge(Campus* g){
	for(int i = 1;  i <= g->Nodes_Num ; i++){
    	for(int j  = 1 ; j <= g->Nodes_Num ; j++){
    		if(g->edges[i][j] == INF)
    			printf("INF ");
    		else
    			printf("%d ",g->edges[i][j]);
    	}
    	printf("\n");
    }
}


void Exit()
{
printf("                                                                     \n");
printf("                                               期待您的下一次使用！！！\n");
exit(0);
}
