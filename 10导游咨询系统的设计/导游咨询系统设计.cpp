#include <cstdio>
#include <cstdlib>
#include <string.h>
#include <time.h>
#include <iostream>
#include <algorithm>
#include <stack>

#define M 20  // У԰��������
#define INF 0x3f3f3f3f  //int���ֵ

using namespace std;

typedef struct
{
    int num;  // ������
    char name[20];  // ��������
    char introduction[300];  // �������
} Attractions;

typedef struct
{
    Attractions att[M];
    int edges[M][M];
    int Nodes_Num;  // �ܽ����
	int edges_Num;  // �ܱ���
}Campus;

int check(int ch);   // �ж��οͱ���Ƿ��������
void getCampus(Campus* g);  // ������ͼ
void Search(Campus *g);  // �鿴������Ϣ                                            
void shortPath(Campus *g);  // �����о���֮������·�����ȼ���·��
void Floyd_Print(Campus *g, int start, int end);  // ���·���ϵ��м��
void print_shortPath(Campus *g);  //  ��ӡ���·��
void print_AllPath(Campus *g);  // �������·��
void DFS_AllPath(Campus* g ,int start, int end, int &top, int &count);  // ����DFS��ȫ·��
void bestPath(Campus *g);  // ���·��
 
void putMap();  // ���У԰ƽ��ͼ
int putMenu();  // ������˵�
void Exit();   // ϵͳ�˳�����

int main() {
	Campus g; 
	getCampus(&g);  // ���ļ���ȡ��Ϣ����У԰��ͼ
	shortPath(&g);  // ͨ��Floyd���distence����path��
		while (true) {                                                          
			switch (putMenu()) {  // ��ӡ���˵�
			case 1:system("cls"); putMap();break;   // �����ѯ
			case 2:system("cls"); Search(&g); break;  // ������Ϣ��ѯ
			case 3:system("cls"); putMap(); print_shortPath(&g); break; // ����������·����ѯ
			case 4:system("cls"); putMap(); print_AllPath(&g); break;  // �����������·�߲�ѯ
			case 5:system("cls"); putMap(); bestPath(&g); break;  // �ྰ����������·�߲�ѯ
			case 6:system("cls"); Exit(); break;   // �˳�ϵͳ
			default:printf("             �Բ���û�и�ѡ���Ӧ�Ĳ�����\n\n");
			}
			system("pause");
			system("cls");  // ����
		}
	return 0;
}


// �ж��οͱ���Ƿ��������
int check(int ch){
	if(ch < 0 || ch > 16)
	    {
	        printf("\n");
	        printf("������������������0~12֮������֣�\n");
	        return 0;
	    }
    return 1;
}


// ������ͼ
void getCampus(Campus* g)
{
    int ta, tb, tmp;  // ��ʱ����
    FILE *rf;
    rf = fopen("./map.txt", "r");  // �ļ���ȡ
    if(!rf)  // ����ļ���ȡʧ�ܣ�����error��
	{
        printf("ERROR!\n");
        return;
    }  
    else if(rf)
    {
        fscanf(rf,"%d %d", &g->Nodes_Num, &g->edges_Num);  // �ļ���ȡ�ܽ�������ܱ���
        for(int i = 1; i <= g->Nodes_Num; i++)
        {
        	// ��ȡ�ļ������ţ��������ƣ�������
            fscanf(rf,"%d %s %s",&g->att[i].num,g->att[i].name,g->att[i].introduction); 
        }
        // ��ͼ��ʼ���������Լ��������㶼�ǲ��ɴ�
        for(int i = 0;i <= g->Nodes_Num; i++)
        {
            for(int j = 0; j <= g->Nodes_Num; j++)
            {
                if(i==j) g->edges[i][j]=0;
                else g->edges[i][j]=INF;
            }
        }
        // �õ�����Ϣ
        for(int i = 1; i <= g->edges_Num; i++)
        {
            fscanf(rf,"%d %d %d",&ta,&tb,&tmp);
            g->edges[ta][tb]=g->edges[tb][ta]=tmp;
        }
        fclose(rf); // �ļ��ر�
    }
}


// �鿴������Ϣ
void Search(Campus *g)
{
    int number;  // ���
    while(true)
    {
    	putMap();
        printf("��������鿴�ĸ����㣨�����뾰����,����0������:");
        scanf("%d",&number);
        system("cls"); //�����Ļ
        if(check(number))
        {
        	if(number == 0)break;
        	printf("\n������:%d\n",g->att[number].num);
            printf("\n��������:%s\n",g->att[number].name);
		    printf("\n�������:%s\n",g->att[number].introduction);
		    printf("\n");      
        }
    }
    
}


// Floyd�㷨����������һ����̵�·��
int distence[M][M];  // ��������
int path[M][M];  // ·������
void shortPath(Campus *g) 
{
	for (int i = 1; i <= g->Nodes_Num; i ++ )  // ��ʼ����������������·����������
		for (int j = 1; j <= g->Nodes_Num; j ++ ) 
		{
			distence[i][j] = g->edges[i][j];
			if (i != j && distence[i][j] != INF) path[i][j] = i;  //��ʾ���i��j���ڣ�i��j��Ҫ����i
			else path[i][j] = -1;  // ������ -1����ǰ���㲻�ɴ�
		}

	for (int k = 1; k <= g->Nodes_Num; k ++ )  //�������ÿ����������·��
		for (int i = 1; i <= g->Nodes_Num; i ++ )
			for (int j = 1; j <= g->Nodes_Num; j++)  // ����distence[i][j]��ֵ
				if (distence[i][j] > (distence[i][k] + distence[k][j]))  // �����������k�����ʹ��·������
				{ 
					distence[i][j] = distence[i][k] + distence[k][j];  // �������·������
					path[i][j] = k;  // �������·���ϵľ����
				}
}


// ���·���ϵ��м��
void Floyd_Print(Campus *g, int start, int end) 
{
	// ����������ڻ������㲻�ɴ�����ݹ�
	if (path[start][end] == -1 || path[start][end] == end || path[start][end] == start)
		return;
	else {
		Floyd_Print(g, start, path[start][end]);  // ���м����Ϊ�յ������ӡ·��
		printf("%s->", g->att[path[start][end]].name); // ��ӡ�м侰������
		Floyd_Print(g, path[start][end], end);  // ���м����Ϊ��������ӡ·��
	}
}


/*�������ӡ���������·��*/
void print_shortPath(Campus *g) {
	int start, end;  //����ţ��յ���
	do {
		printf("         ����������ţ�");
		scanf("%d", &start);
	} while (!check(start));
	do {
		printf("         �������յ��ţ�");
		scanf("%d", &end);
	} while (!check(end));
	printf("             %s��%s����̾����ǣ�%dm\n", g->att[start].name, g->att[end].name, distence[start][end]);
	printf("             �������·�ߣ�");
	printf("%s->", g->att[start].name);  // ���·���ϵ����
	Floyd_Print(g, start, end);  // ���·���ϵ��м��
	printf("%s\n", g->att[end].name);  // ���·���ϵ��յ�
}

int pathStack[M];//·��ջ
int visited[M]; //�ж��Ƿ��Ѿ�����
void print_AllPath(Campus *g)
{
    int flag=0;
    int start;  // ���
    int end;  // �յ�
    memset(pathStack, 0, sizeof(pathStack));  // ·��ջ��ʼ��
	memset(visited, 0, sizeof(visited));  // ��������ʼ�� 
	int top = 0;   //��ʼ��ջ��
	int count = 1; //��ʼ��·������
    while(true)
    {
        printf("\n");
        printf("                �����������:");
        scanf("%d", &start);
        if(check(start))
        {
           flag = 1;
           if(1==flag) break;
        }
    }
    flag=0;  // flag������0
    while(true)
    {
        printf("\n");
        printf("                �������յ���:");
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
    int dis=0;  //�� ����
    pathStack[top ++ ] = start; // �������ջ
    visited[start] = 1; //��ʾ�õ��Ѿ����ʹ�
    for(int i = 1; i <= g->Nodes_Num; i ++ )  // ���������������ڵĽ��
    {
        if(g->edges[start][i] > 0 && g->edges[start][i] != INF && !visited[i])  // �����i�����Լ�����������пɴ�·������δ�����ʹ�
        {
            if(i == end)  // ����Ѿ�����Ŀ�ĵ�
            {
                printf("             ��%d����·:", count ++ );  // ����·�����
                for(int j = 0; j < top; j ++ )
                {
                    printf("%s->",g->att[pathStack[j]].name);  // ����þ���
                    if(j < top - 1)
                        dis = dis + g->edges[pathStack[j]][pathStack[j+1]]; 
                }
                dis = dis + g->edges[pathStack[top-1]][end];  // �������һ���߳�1
                printf("%s\n",g->att[end].name);
                printf("             �ܳ���Ϊ: %dm\n\n", dis);
            }
            else //�����δ�ﵽ
            {
                DFS_AllPath(g, i, end, top, count);  // �ݹ����
                top --  ;  // ��ջ
                visited[i]=0;  // �ͷŸýڵ�
            }
        }
    }
}


/*�ྰ��������·��*/
void bestPath(Campus *g) {
	int vNum[M] = { 0 }, count = 1;  // ��¼�û�����ı����Ϣ
	int dis = 0;   // ͳ��ȫ��·���ܳ�
	printf("             ��������Ҫ�����ĵ�%d������ı�ţ�����0�������룩��", count);
	scanf("%d", &vNum[count]);
	while (vNum[count] != 0 && count <= 12) {
		while (!check(vNum[count])) {
			printf("     ��������Ҫ�����ĵ�%d�������ţ�", count);
			scanf("%d", &vNum[count]);
		}
		if (vNum[count] == 0) break;
		printf("         ��������Ҫ�����ĵ�%d�������ţ�", ++count);
		scanf("%d", &vNum[count]);
	}
	printf("             ��Ϊ����ѡ��ѷ���·����");
	for (int i = 1; vNum[i] > 0 && vNum[i + 1] > 0; i++)  // ������������ľ���
	{       
		printf("%s->", g->att[vNum[i]].name);   // ���·���ϵ����
		Floyd_Print(g, vNum[i],vNum[i + 1]);   // ����Floyd�㷨�õ�������֮������·��
		dis += distence[vNum[i]][vNum[i + 1]];  //������·����
	}
	printf("%s\n\n", g->att[vNum[count - 1]].name);  // ���·���ϵ��յ�
	printf("             ȫ���ܳ�Ϊ��%dm\n\n", dis);
}


void putMap()
{
    printf("+***********************************************************************************+\n");                  
    printf("|                                 �½���ѧ����ͼ                                    |\n");
    printf("|***********************************************************************************|\n");
    printf("|                      1 ����                2 ����¥                               |\n");
    printf("|                      3 1�Ž�ѧ¥           4 ��������                             |\n");
    printf("|                      5 ͼ���              6 11�Ž�ѧ¥                           |\n"); 
    printf("|                      7 10�Ž�ѧ¥          8 ����һ����                           |\n");
    printf("|                      9 �ݷ�¥             10 С�ٳ�                               |\n");   
    printf("|                     11 ������             12 ��ٳ�                               |\n");
    printf("|                     13 ���͵�һʳ��       14 �Ƽ�¥                               |\n");     
    printf("|                      15 ���               16 ��԰�г�                            |\n");   
    printf("+***********************************************************************************+\n");

}


int putMenu()
{
	int op;
    printf("       +***********************************************************************************+\n");
    printf("       |                         ��ӭʹ���½���ѧУ԰������ѯϵͳ                          |\n");
    printf("       |***********************************************************************************|\n");
    printf("       |                                   ��ѡ�����:                                     |\n");
    printf("       |                                                                                   |\n");
    printf("       |             1.ѧУ��ͼ                      2.�鿴������Ϣ                        |\n");
    printf("       |                                                                                   |\n");
    printf("       |             3.Ѱ��������֮������·��      4.Ѱ��������֮������·��              |\n");
    printf("       |                                                                                   |\n");
    printf("       |             5.·���滮                      6. �˳�ϵͳ                           |\n");
    printf("       |                                                                                   |\n");
    printf("       +***********************************************************************************+\n");
    printf("\n\n");
    printf("             ������������ѡ�������");
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
printf("                                               �ڴ�������һ��ʹ�ã�����\n");
exit(0);
}
