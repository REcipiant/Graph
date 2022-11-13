#define _CRT_SECURE_NO_WARNINGS 1
#include "graph.h"
#include <stdio.h>
int main()
{
	Graph* G = GRAPH_creat();
	printf("DFS:\n");
	GRAPH_DFStrack(G);
	printf("\nBFS:\n");
	GRAPH_BFS(G);
	printf("\n");
	GRAPH_print(G);
	printf("\n");
	GRAPH_Dijkstra(G, 4);
	/*复制粘贴到命令行，输入格式
	*	ABCDE#
		AB6
		AD4
		AC5
		BA2
		BD3
		CA5
		CD9
		DB3
		DA4
		DC8
		##0
结果：ABDCE
***********************
*		ABCDEF#
		AB1
		AC1
		BA1
		BE1
		BD1
		EC1
		EB1
		ED1
		DB1
		DE1
		CA1
		CE1
		CF1
		FC1
		##0
结果：ABDECF
	ABCDEFGH#
	AB1
	AF1
	BC1
	BE1
	CD1
	CB1
	DC1
	DE1
	ED1
	EB1
	FA1
	FG1
	FH1
	GF1
	GH1
	HG1
	HF1
	##0
有向图：
ABCDE#
AB1
AC2
BD5
BE4
ED6
DA3
DC7
##0
	*/

	return 0;
}