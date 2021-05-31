#ifndef LIBRARY_H_INCLUDED
#define LIBRARY_H_INCLUDED

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<conio.h>

#define MAX 100
struct Books
{
	char b_number[20];//书号
	char b_name[20];//书名
	char author[20];//著者
	int p_stock;//现存量
	int all_stock;//总存量
	struct Books* next;
};
#define len sizeof(struct Books)
void Main_oper();//主界面操作函数
void ad_oper();//管理者主操作函数
void addbooks();//图书进库函数
void delbooks();//清除库存函数
void search();//查询图书函数
void viewallbooks();//图书概览函数
void viewborrow();//借阅记录查询
#endif
