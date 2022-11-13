#define _CRT_SECURE_NO_WARNINGS 1
#include "graph.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Loopqueue.h"
/*
	find_V:查找下标
	@arr：数组名
	@len：数组长度
	@Data：查找的数据
	返回值：
			元素下标
			-1:出错
*/
static int find_V(char arr[], int len, char Data)
{
	for (int i = 0; i < len; i++)
	{
		if (arr[i] == Data)
		{
			return i;
		}
	}
	return -1;
}

/*
	GRAPH_creat:创建图
	无形参
	返回值：
			结构体指针
*/
Graph* GRAPH_creat(void)
{
	Graph* gra = malloc(sizeof(*gra));
	int i = 0;
	char temp;
	if (NULL == gra)
	{
		return NULL;
	}
	gra->V_num = 0;
	while (1)
	{
		scanf("%c", &temp);
		if (temp == '#')//规定以#作为结束符号
		{
			break;
		}
		gra->Data[i] = temp;
		gra->V_num++;
		i++;
	}
	getchar();//获取回车符号\n

	for (i = 0; i < gra->V_num; i++)
	{
		for (int j = 0; j < gra->V_num; j++)
		{
			gra->Weight[i][j] = INVALID;// 初始化使用的大小4X4
		}
	}
	char start, terminal;//终止，起点
	int num = 0;
	int V_start = 0, V_terminal = 0;
	while (1)
	{
		scanf("%c%c%d", &start, &terminal, &num);
		if (start == '#' && terminal == '#' && num == 0)//End with '##0'
		{
			break;
		}
		
		V_start = find_V(gra->Data, gra->V_num, start);//获取其实顶点坐标
		V_terminal = find_V(gra->Data, gra->V_num, terminal);//获取终点坐标
		getchar();//再取走回车符\n
		if (-1 == V_start || -1 == V_terminal)//出错了，就重新输入
		{
			//测试
			printf("-Fail!-\n");
			continue;
		}
		gra->Weight[V_start][V_terminal] = num;//将权值保存再对应的坐标下
	}


	return gra;
}
/*
	GRAPH_print:图的打印
	@gra：图的结构体指针
	返回值：
			空
*/

void GRAPH_print(Graph* gra)
{
	Graph* G_print = gra;
	for (int i = 0; i < G_print->V_num; i++)
	{
		printf("%c ", G_print->Data[i]);
	}
	printf("\n");
	//打印权值
	for (int i = 0; i < gra->V_num; i++)
	{
		for (int j = 0; j < gra->V_num; j++)
		{
			if (gra->Weight[i][j] == INVALID)
				printf("%c ", gra->Weight[i][j]);
			else
				printf("%d ", gra->Weight[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
//***************************************************************
/*
	深度优先遍历
*/
int visit[MAX] = { 0 };//用于标记被访问的结点，初始化为0，表示都未被访问

/*
	Find_next_Weight:下一个不为INVALID -> (一个宏"&")的结点
	@gra：图指针
	@V_data:某一行开始找
	@begin：从第V_data行的begin列开始找下一个不为INVALID的结点
	返回值：
		成功：该节点的下标
		-1：没找到
*/
static int Find_next_Weight(Graph* gra,int V_data,int begin)
{
	for (int i = begin; i < gra->V_num; i++)//从begin列开始找
	{
		if (gra->Weight[V_data][i] != INVALID)
		{
			return i;//找到返回下标
		}
	}
	return -1;//没找到
}

/*
	GRAPH_DFS:深度优先遍历
	@gra：图的结构体指针
	@V_data:数据结点下标（用于标记是否已经被访问）
	返回值：
			空
*/
void GRAPH_DFS(Graph* gra, int V_data)
{
	printf("%c ",gra->Data[V_data]);//访问下标为V_data的结点
	visit[V_data] = 1;//标记该节点

	for (int i = Find_next_Weight(gra,V_data,0); i >= 0; i = Find_next_Weight(gra, V_data, i+1))
	{
		if (visit[i] == 0)//通过递归进行回溯
		{
			GRAPH_DFS(gra,i);//继续深度遍历
		}
	}
}
/*
	GRAPH_DFStrack:保证“孤岛”结点也能被访问到
	@gra:图指针
	返回值：
			空
*/
void GRAPH_DFStrack(Graph* gra)
{
	for (int i = 0; i < gra->V_num; i++)
	{
		visit[i] = 0;
	}
	for (int j = 0; j < gra->V_num; j++)
	{
		if (visit[j] == 0)//访问每一个未被访问的结点，遍历一遍visit[]数组
		{
			GRAPH_DFS(gra, j);
		}
	}
}
/*
	GRAPH_BFS:广度优先遍历
	@gra：图指针
	返回值：
			空
*/

void GRAPH_BFS(Graph* gra)
{
	for (int i = 0; i < gra->V_num; i++)
	{//与BFS类似，用数组标记未访问的结点
		visit[i] = 0;
	}
	//通过队列来实现图的每个顶点的访问（类似树的层次遍历）
	int V0 = 0;//用于遍历“孤岛”顶点，即没有被任何顶点连通的点
	Lqueue* LQ = LQ_Init(MAX);//创建队列
	//访问V0的每一个邻接点，然后使其依次入队再出队
	//访问V0的邻接点操作与DFS完全相同
	int flag;
	for (V0 = 0; V0 < gra->V_num; V0++)//遍历所有顶点，包括“孤立点”
	{
		if (visit[V0] != 0)//如果被访问了，则继续下一次循环
		{
			continue;
		}
		else//否则入队
		{
			LQ_input(LQ, V0);//V0入队
		}


		//以下是对一个连通图的BFS算法，若输入的有两个连通图，且两个连通图均不相连通，才需要加外层大循环
		//不然对于一个连通图，只需要给出入口顶点就能访问整个连通图
		while (LQ_isempty(LQ) != 0)//边出边入，直到出完为止
		{
			LQ_out(LQ, &flag);//出队
			printf("%c ", gra->Data[flag]);
			if (visit[flag] == 0)//如果没被标记，就标记它，若已经标记则去让它的邻接点入队
			{
				visit[flag] = 1;//标记元素
			}
			for (int i = Find_next_Weight(gra, flag, 0); i >= 0; i = Find_next_Weight(gra, flag, i + 1))//访问二维矩阵第flag行值不为INVALID的下标
			{
				if (visit[i] != 0)//flag的邻接点是否被访问，若是则继续找，若不是则入队
				{
					continue;
				}
				LQ_input(LQ, i);//找到了就入队
				visit[i] = 1;//并且标记入队元素
			}

		}

	}
	LQ_Destroy(LQ);//销毁队列
}
//*****************************************************************
//求数组中最小的元素
//static int fine_min(int arr[], int len)
//{
//	int temp = arr[0];
//	int j = 0;
//	for (int i = 0; i < len; i++)
//	{
//		if (temp > arr[i])
//		{
//			j = i;
//			temp = arr[i];
//		}
//	}
//	return j;
//}
//判断数组是否有给定的值
//static int fine_arr_x(int arr[],int len, int x)
//{
//	for (int i = 0; i < len; i++)
//	{
//		if (arr[i] == 0)
//		{
//			return 0;
//		}
//	}
//	return 1;
//}
//三个向量组
int s[MAX];//用于记录已经被加入到S集合中的结点，类似bool类型
int dist[MAX];//用于记录最短路径
char path[MAX][MAX];//用于记录最短路径所经过的所有顶点

static void arr_Init(Graph* gra,int begin)
{
	//初始化S[]数组，0表示未加入到S集合中，1表示已经加入且加入后就是已经求出了最短路径，不然不会加入
	for (int i = 0; i < gra->V_num; i++)
	{
		if (i == begin)
		{
			s[i] = 1;
		}
		else
		{
			s[i] = 0;
		}
	}
	//初始化Path数组，path的第一行即为开始结点
	for (int i = 0; i < gra->V_num; i++)
	{
		path[i][0] = gra->Data[begin];
	}

	//初始化dist[]数组，值为begin行的所有权值

	for (int i = 0; i < gra->V_num; i++)
	{
		if (gra->Weight[begin][i] == INVALID)
		{
			dist[i] = 99999;//尽量大，因为这个值不是顶点之间的权值，最好设置的取不到
			path[i][1] = '\0';

		}
		else
		{
			dist[i] = gra->Weight[begin][i];//将该列的权值赋值给dist数组
			path[i][1] = gra->Data[i];
			path[i][2] = '\0';

		}
	}
	//*

}
/*
	图的最短路径算法：
	Dijkstra
	@gra：图指针
	@begin：起始顶点
	返回值：
			空
*/

void GRAPH_Dijkstra(Graph* gra, int begin)
{

	arr_Init(gra, begin);//初始化辅助数组
	int n = 1;
	while (n++ < gra->V_num)//最多做元素总个数次循环
	{
		int W_col;
		int min = 99999;

		//找出尚未求出最短路径中的最小dist以及其对应的下标
		for (int i = 0; i < gra->V_num; i++)
		{
			if (s[i] == 0)
			{
				if (min > dist[i])
				{
					min = dist[i];
					W_col = i;
				}
			}
		}					
		s[W_col] = 1;

		//gra->[begin]到gra->[W_col]的最短距离已经求出

		//步骤二,更新
		for (int i = 0; i < gra->V_num; i++)
		{
			if (s[i] == 0)//尚未求出来的最短路径
			{
				if (min + gra->Weight[W_col][i] < dist[i])//比较原来的路径与加入新结点后路径
				{
					dist[i] = min + gra->Weight[W_col][i];//新路径小则更新对应dist的内容

					strcpy(path[i], path[W_col]);//将新增加的下标为W_col的数据加入到更新的path路径下

					int len = strlen(path[i]);

					path[i][len] = gra->Data[i];//不改变结束结点
					path[i][len + 1] = '\0';//方便打印

				}
			}
		}
	}


	//打印出来所有最短路径
	for (int i = 0; i < gra->V_num; i++)
	{
		if (dist[i] == 99999)
		{
			printf("%c->%c:&:%s\n", gra->Data[begin], gra->Data[i],path[i]);
		}
		else
			printf("%c->%c:%d:%s\n", gra->Data[begin], gra->Data[i], dist[i], path[i]);
	}


}

