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
	char b_number[20];//���
	char b_name[20];//����
	char author[20];//����
	int p_stock;//�ִ���
	int all_stock;//�ܴ���
	struct Books* next;
};
#define len sizeof(struct Books)
void Main_oper();//�������������
void ad_oper();//����������������
void addbooks();//ͼ����⺯��
void delbooks();//�����溯��
void search();//��ѯͼ�麯��
void viewallbooks();//ͼ���������
void viewborrow();//���ļ�¼��ѯ
#endif
