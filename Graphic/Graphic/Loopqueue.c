#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include "Loopqueue.h"

/*
	LQ_Init:初始化一个队列的结构体
	@maxlen:想要开辟的空间大小
	返回值：
			队列结构体指针
*/
Lqueue* LQ_Init(int maxlen)
{
	Lqueue* LQ = malloc(sizeof(*LQ));
	if (LQ == NULL)
	{
		return NULL;
	}
	LQ->data = malloc(sizeof(Elemtype) * maxlen);
	if (LQ->data == NULL)
	{
		perror("Init>>>LQ->data False");
		exit(1);
	}
	LQ->avail = maxlen;
	LQ->front = 0;
	LQ->rear = 0;
	LQ->maxlen = maxlen;
	return LQ;
}

/*
	LQ_Destroy：销毁队列
	@LQ：指向队列的结构体指针
	返回值：
			-1：失败
			0：成功
*/
int LQ_Destroy(Lqueue* LQ)
{
	if (LQ == NULL)
	{
		return -1;
	}
	LQ->avail = 0;
	LQ->front = 0;
	LQ->rear = 0;
	free(LQ->data);
	free(LQ);
	return 0;
}
/*
	LQ_Clear:清空队列元素
	@LQ：指向队列的结构体指针
	返回值：
			-1：失败
			0：成功
*/
int LQ_Clear(Lqueue* LQ)
{
	if (LQ == NULL)
	{
		return -1;
	}
	LQ->front = 0;
	LQ->rear = 0;
	LQ->avail = 0;
	return 0;
}
/*
	LQ_isempty:判断队列是否为空
	@LQ：指向队列的结构体指针
	返回值：
		-1：失败
		0：empty
		1:Not empty
*/
int LQ_isempty(Lqueue* LQ)
{
	if (LQ == NULL)
	{
		return -1;
	}
	if (LQ->avail == LQ->maxlen)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}
/*
	LQ_len:队列长度
	@LQ：指向队列的结构体指针
	返回值：
			-1：失败
			其他：队列长度
*/
int LQ_len(Lqueue* LQ)
{
	if (LQ == NULL)
	{
		return -1;
	}
	
	return (LQ->maxlen - LQ->avail);
}

/*
	LQ_input:入队
	@LQ：指向队列的结构体指针
	@Data:入队元素
	返回值：
		-1: 出错或溢出
		0:成功

*/
int LQ_input(Lqueue* LQ, Elemtype Data)
{

	if (LQ == NULL || LQ->avail == 0)
	{
		//printf("Full or Error\n");
		return -1;
	}
	LQ->data[LQ->rear] = Data;
	LQ->rear++;
	LQ->rear = LQ->rear % LQ->maxlen;
	LQ->avail--;
	return 0;
}

/*
	LQ_out:出队
	@LQ：指向队列的结构体指针
	@p：保存出队数据
	返回值：
		-1: 出错或栈已经为空
		0:成功
*/
int LQ_out(Lqueue* LQ, Elemtype* p)
{
	if (LQ == NULL || LQ->avail == LQ->maxlen)
	{
		//printf("%d ", *p);
		//printf("Empty or Error\n");
		return -1;
	}
	*p = LQ->data[LQ->front];
	LQ->front++;
	LQ->front = LQ->front % LQ->maxlen;
	LQ->avail++;
	//测试
	//printf("%d ", *(int*)p);

	return 0;
}



