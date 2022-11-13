#pragma once
#ifndef __GRAPH_H__
#define __GRAPH_H__
//数据结构：图
/*
图的存储方式：1.邻接矩阵法 -> 数组存储
			  2.邻接表 -> 用链表的方式存储
以上两种用的较频繁，还有其他的方法，如：十字链表、邻接多重表等
*/

//以下采用邻接矩阵法实现图的存储以及一切存储结构的基本操作：增、删、改、查

//将一个“图”抽象成一个结构体
#define MAX 100//最大数据元素存储个数
#define INVALID '&'//无效权值
typedef char Graphic_V;//图的数据类型，假定为char类型

typedef int Graphic_W;//图的各个顶点之间的权值
//由于用的数组来对图进行存储，因此逻辑关系不必再考虑，是一端连续的地址空间
typedef struct 
{
	//数据元素的存储
	Graphic_V Data[MAX];//以数组的方式进行数据元素的存储
	Graphic_W Weight[MAX][MAX];//用来存储各顶点之间的权值，类似两地之间的距离

	int V_num;//用来记录Data的输入数量

}Graph;

/*
	GRAPH_creat:创建图
	无形参
	返回值：
			结构体指针
*/
Graph* GRAPH_creat(void);
/*
	GRAPH_print:图的打印
	@G：图的结构体指针
	返回值：
			空
*/

void GRAPH_print(Graph* gra);
/*
	GRAPH_DFS:深度优先遍历
	@gra：图的结构体指针
	@V_data:数据结点下标（用于标记是否已经被访问）
	返回值：
			空
*/
void GRAPH_DFS(Graph* gra, int V_data);

/*
	GRAPH_DFStrack:保证“孤岛”结点也能被访问到
	@gra:图指针
	返回值：
			空
*/
void GRAPH_DFStrack(Graph* gra);
/*
	GRAPH_BFS:广度优先遍历
	@gra：图指针
	返回值：
			空
*/

void GRAPH_BFS(Graph* gra);

/*
	图的最短路径算法：
	Dijkstra
	@gra：图指针
	@begin：起始顶点
	返回值：
			空
*/

void GRAPH_Dijkstra(Graph* gra, int begin);













#endif
