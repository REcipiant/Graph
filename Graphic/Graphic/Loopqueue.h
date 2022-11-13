#pragma once
#ifndef __LOOPQUEUE_H__
#define __LOOPQUEUE_H__

typedef int Elemtype;
//循环队列的实现，顺序存储
typedef struct Lqueue
{
	Elemtype* data;//顺序存储，指向一端连续的空间

	int maxlen;//开辟连续空间的大小，即数值的元素个数，后续malloc会用到

	int rear;//对尾标识，用于加入新数据元素，即将元素插入队列中
	int front;//队首标识，用于出队列，即删除队列中的元素
	int avail;//可用空位，用于判断队列是空队列还是满队列

}Lqueue;

/*
	LQ_Init:初始化一个队列的结构体
	@maxlen:想要开辟的空间大小
	返回值：
			队列结构体指针
*/
Lqueue* LQ_Init(int maxlen);

/*
	LQ_Destroy：销毁队列
	@LQ：指向队列的结构体指针
	返回值：
			-1：失败
			0：成功
*/
int LQ_Destroy(Lqueue* LQ);

/*
	LQ_Clear:清空队列元素
	@LQ：指向队列的结构体指针
	返回值：
			-1：失败
			0：成功
*/
int LQ_Clear(Lqueue* LQ);

/*
	LQ_isempty:判断队列是否为空
	@LQ：指向队列的结构体指针
	返回值：
		-1：失败
		0：empty
		1:Not empty
*/
int LQ_isempty(Lqueue* LQ);

/*
	LQ_len:队列长度
	@LQ：指向队列的结构体指针
	返回值：
			-1：失败
			其他：队列长度
*/
int LQ_len(Lqueue* LQ);
/*
	LQ_input:入队
	@LQ：指向队列的结构体指针
	@Data:入队元素
	返回值：
		空
*/
int LQ_input(Lqueue* LQ, Elemtype Data);
/*
	LQ_out:出队
	@LQ：指向队列的结构体指针
	@p：保存出队数据
	返回值：
		空
*/
int LQ_out(Lqueue* LQ, Elemtype* p);






















#endif