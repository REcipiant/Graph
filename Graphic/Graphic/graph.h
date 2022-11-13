#pragma once
#ifndef __GRAPH_H__
#define __GRAPH_H__
//���ݽṹ��ͼ
/*
ͼ�Ĵ洢��ʽ��1.�ڽӾ��� -> ����洢
			  2.�ڽӱ� -> ������ķ�ʽ�洢
���������õĽ�Ƶ�������������ķ������磺ʮ�������ڽӶ��ر��
*/

//���²����ڽӾ���ʵ��ͼ�Ĵ洢�Լ�һ�д洢�ṹ�Ļ�������������ɾ���ġ���

//��һ����ͼ�������һ���ṹ��
#define MAX 100//�������Ԫ�ش洢����
#define INVALID '&'//��ЧȨֵ
typedef char Graphic_V;//ͼ���������ͣ��ٶ�Ϊchar����

typedef int Graphic_W;//ͼ�ĸ�������֮���Ȩֵ
//�����õ���������ͼ���д洢������߼���ϵ�����ٿ��ǣ���һ�������ĵ�ַ�ռ�
typedef struct 
{
	//����Ԫ�صĴ洢
	Graphic_V Data[MAX];//������ķ�ʽ��������Ԫ�صĴ洢
	Graphic_W Weight[MAX][MAX];//�����洢������֮���Ȩֵ����������֮��ľ���

	int V_num;//������¼Data����������

}Graph;

/*
	GRAPH_creat:����ͼ
	���β�
	����ֵ��
			�ṹ��ָ��
*/
Graph* GRAPH_creat(void);
/*
	GRAPH_print:ͼ�Ĵ�ӡ
	@G��ͼ�Ľṹ��ָ��
	����ֵ��
			��
*/

void GRAPH_print(Graph* gra);
/*
	GRAPH_DFS:������ȱ���
	@gra��ͼ�Ľṹ��ָ��
	@V_data:���ݽ���±꣨���ڱ���Ƿ��Ѿ������ʣ�
	����ֵ��
			��
*/
void GRAPH_DFS(Graph* gra, int V_data);

/*
	GRAPH_DFStrack:��֤���µ������Ҳ�ܱ����ʵ�
	@gra:ͼָ��
	����ֵ��
			��
*/
void GRAPH_DFStrack(Graph* gra);
/*
	GRAPH_BFS:������ȱ���
	@gra��ͼָ��
	����ֵ��
			��
*/

void GRAPH_BFS(Graph* gra);

/*
	ͼ�����·���㷨��
	Dijkstra
	@gra��ͼָ��
	@begin����ʼ����
	����ֵ��
			��
*/

void GRAPH_Dijkstra(Graph* gra, int begin);













#endif
