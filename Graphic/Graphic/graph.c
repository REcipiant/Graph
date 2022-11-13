#define _CRT_SECURE_NO_WARNINGS 1
#include "graph.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Loopqueue.h"
/*
	find_V:�����±�
	@arr��������
	@len�����鳤��
	@Data�����ҵ�����
	����ֵ��
			Ԫ���±�
			-1:����
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
	GRAPH_creat:����ͼ
	���β�
	����ֵ��
			�ṹ��ָ��
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
		if (temp == '#')//�涨��#��Ϊ��������
		{
			break;
		}
		gra->Data[i] = temp;
		gra->V_num++;
		i++;
	}
	getchar();//��ȡ�س�����\n

	for (i = 0; i < gra->V_num; i++)
	{
		for (int j = 0; j < gra->V_num; j++)
		{
			gra->Weight[i][j] = INVALID;// ��ʼ��ʹ�õĴ�С4X4
		}
	}
	char start, terminal;//��ֹ�����
	int num = 0;
	int V_start = 0, V_terminal = 0;
	while (1)
	{
		scanf("%c%c%d", &start, &terminal, &num);
		if (start == '#' && terminal == '#' && num == 0)//End with '##0'
		{
			break;
		}
		
		V_start = find_V(gra->Data, gra->V_num, start);//��ȡ��ʵ��������
		V_terminal = find_V(gra->Data, gra->V_num, terminal);//��ȡ�յ�����
		getchar();//��ȡ�߻س���\n
		if (-1 == V_start || -1 == V_terminal)//�����ˣ�����������
		{
			//����
			printf("-Fail!-\n");
			continue;
		}
		gra->Weight[V_start][V_terminal] = num;//��Ȩֵ�����ٶ�Ӧ��������
	}


	return gra;
}
/*
	GRAPH_print:ͼ�Ĵ�ӡ
	@gra��ͼ�Ľṹ��ָ��
	����ֵ��
			��
*/

void GRAPH_print(Graph* gra)
{
	Graph* G_print = gra;
	for (int i = 0; i < G_print->V_num; i++)
	{
		printf("%c ", G_print->Data[i]);
	}
	printf("\n");
	//��ӡȨֵ
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
	������ȱ���
*/
int visit[MAX] = { 0 };//���ڱ�Ǳ����ʵĽ�㣬��ʼ��Ϊ0����ʾ��δ������

/*
	Find_next_Weight:��һ����ΪINVALID -> (һ����"&")�Ľ��
	@gra��ͼָ��
	@V_data:ĳһ�п�ʼ��
	@begin���ӵ�V_data�е�begin�п�ʼ����һ����ΪINVALID�Ľ��
	����ֵ��
		�ɹ����ýڵ���±�
		-1��û�ҵ�
*/
static int Find_next_Weight(Graph* gra,int V_data,int begin)
{
	for (int i = begin; i < gra->V_num; i++)//��begin�п�ʼ��
	{
		if (gra->Weight[V_data][i] != INVALID)
		{
			return i;//�ҵ������±�
		}
	}
	return -1;//û�ҵ�
}

/*
	GRAPH_DFS:������ȱ���
	@gra��ͼ�Ľṹ��ָ��
	@V_data:���ݽ���±꣨���ڱ���Ƿ��Ѿ������ʣ�
	����ֵ��
			��
*/
void GRAPH_DFS(Graph* gra, int V_data)
{
	printf("%c ",gra->Data[V_data]);//�����±�ΪV_data�Ľ��
	visit[V_data] = 1;//��Ǹýڵ�

	for (int i = Find_next_Weight(gra,V_data,0); i >= 0; i = Find_next_Weight(gra, V_data, i+1))
	{
		if (visit[i] == 0)//ͨ���ݹ���л���
		{
			GRAPH_DFS(gra,i);//������ȱ���
		}
	}
}
/*
	GRAPH_DFStrack:��֤���µ������Ҳ�ܱ����ʵ�
	@gra:ͼָ��
	����ֵ��
			��
*/
void GRAPH_DFStrack(Graph* gra)
{
	for (int i = 0; i < gra->V_num; i++)
	{
		visit[i] = 0;
	}
	for (int j = 0; j < gra->V_num; j++)
	{
		if (visit[j] == 0)//����ÿһ��δ�����ʵĽ�㣬����һ��visit[]����
		{
			GRAPH_DFS(gra, j);
		}
	}
}
/*
	GRAPH_BFS:������ȱ���
	@gra��ͼָ��
	����ֵ��
			��
*/

void GRAPH_BFS(Graph* gra)
{
	for (int i = 0; i < gra->V_num; i++)
	{//��BFS���ƣ���������δ���ʵĽ��
		visit[i] = 0;
	}
	//ͨ��������ʵ��ͼ��ÿ������ķ��ʣ��������Ĳ�α�����
	int V0 = 0;//���ڱ������µ������㣬��û�б��κζ�����ͨ�ĵ�
	Lqueue* LQ = LQ_Init(MAX);//��������
	//����V0��ÿһ���ڽӵ㣬Ȼ��ʹ����������ٳ���
	//����V0���ڽӵ������DFS��ȫ��ͬ
	int flag;
	for (V0 = 0; V0 < gra->V_num; V0++)//�������ж��㣬�����������㡱
	{
		if (visit[V0] != 0)//����������ˣ��������һ��ѭ��
		{
			continue;
		}
		else//�������
		{
			LQ_input(LQ, V0);//V0���
		}


		//�����Ƕ�һ����ͨͼ��BFS�㷨�����������������ͨͼ����������ͨͼ��������ͨ������Ҫ������ѭ��
		//��Ȼ����һ����ͨͼ��ֻ��Ҫ������ڶ�����ܷ���������ͨͼ
		while (LQ_isempty(LQ) != 0)//�߳����룬ֱ������Ϊֹ
		{
			LQ_out(LQ, &flag);//����
			printf("%c ", gra->Data[flag]);
			if (visit[flag] == 0)//���û����ǣ��ͱ���������Ѿ������ȥ�������ڽӵ����
			{
				visit[flag] = 1;//���Ԫ��
			}
			for (int i = Find_next_Weight(gra, flag, 0); i >= 0; i = Find_next_Weight(gra, flag, i + 1))//���ʶ�ά�����flag��ֵ��ΪINVALID���±�
			{
				if (visit[i] != 0)//flag���ڽӵ��Ƿ񱻷��ʣ�����������ң������������
				{
					continue;
				}
				LQ_input(LQ, i);//�ҵ��˾����
				visit[i] = 1;//���ұ�����Ԫ��
			}

		}

	}
	LQ_Destroy(LQ);//���ٶ���
}
//*****************************************************************
//����������С��Ԫ��
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
//�ж������Ƿ��и�����ֵ
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
//����������
int s[MAX];//���ڼ�¼�Ѿ������뵽S�����еĽ�㣬����bool����
int dist[MAX];//���ڼ�¼���·��
char path[MAX][MAX];//���ڼ�¼���·�������������ж���

static void arr_Init(Graph* gra,int begin)
{
	//��ʼ��S[]���飬0��ʾδ���뵽S�����У�1��ʾ�Ѿ������Ҽ��������Ѿ���������·������Ȼ�������
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
	//��ʼ��Path���飬path�ĵ�һ�м�Ϊ��ʼ���
	for (int i = 0; i < gra->V_num; i++)
	{
		path[i][0] = gra->Data[begin];
	}

	//��ʼ��dist[]���飬ֵΪbegin�е�����Ȩֵ

	for (int i = 0; i < gra->V_num; i++)
	{
		if (gra->Weight[begin][i] == INVALID)
		{
			dist[i] = 99999;//��������Ϊ���ֵ���Ƕ���֮���Ȩֵ��������õ�ȡ����
			path[i][1] = '\0';

		}
		else
		{
			dist[i] = gra->Weight[begin][i];//�����е�Ȩֵ��ֵ��dist����
			path[i][1] = gra->Data[i];
			path[i][2] = '\0';

		}
	}
	//*

}
/*
	ͼ�����·���㷨��
	Dijkstra
	@gra��ͼָ��
	@begin����ʼ����
	����ֵ��
			��
*/

void GRAPH_Dijkstra(Graph* gra, int begin)
{

	arr_Init(gra, begin);//��ʼ����������
	int n = 1;
	while (n++ < gra->V_num)//�����Ԫ���ܸ�����ѭ��
	{
		int W_col;
		int min = 99999;

		//�ҳ���δ������·���е���Сdist�Լ����Ӧ���±�
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

		//gra->[begin]��gra->[W_col]����̾����Ѿ����

		//�����,����
		for (int i = 0; i < gra->V_num; i++)
		{
			if (s[i] == 0)//��δ����������·��
			{
				if (min + gra->Weight[W_col][i] < dist[i])//�Ƚ�ԭ����·��������½���·��
				{
					dist[i] = min + gra->Weight[W_col][i];//��·��С����¶�Ӧdist������

					strcpy(path[i], path[W_col]);//�������ӵ��±�ΪW_col�����ݼ��뵽���µ�path·����

					int len = strlen(path[i]);

					path[i][len] = gra->Data[i];//���ı�������
					path[i][len + 1] = '\0';//�����ӡ

				}
			}
		}
	}


	//��ӡ�����������·��
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

