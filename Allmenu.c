#include "Reader.h"
#include "Library.h"
#include "Allmenu.h"
void Mainmenu()
{
	system("cls");//����������ʹ�����������
	printf("*********************************\n");
	printf("        1---����Աϵͳ              \n");
	printf("        2---�û�����ϵͳ            \n");
	printf("        0---�˳�ϵͳ                \n");
	printf("*********************************\n");
	printf("����������ѡ�������Ӧ��ϵͳ:  ");
	Main_oper();//�����������������
	return;
}

void admenu()
{
	printf("*********************************\n");
	printf("        1---�ɱ����              \n");
	printf("        2---������              \n");
	printf("        3---��ѯͼ��               \n");
	printf("        4---ͼ������               \n");
	printf("        5---���ļ�¼����               \n");
	printf("        6---������һ��               \n");
	printf("        7---�˳�ϵͳ               \n");
	printf("*********************************\n");
	printf("����������ѡ�������Ӧ��ϵͳ:  ");
	return;
}

void Readermenu()
{
	printf("*************************************\n");
	printf("            1--����ͼ��              \n");
	printf("            2--�黹ͼ��              \n");
	printf("            3--��ѯͼ��              \n");
	printf("            4--������һ��            \n");
	printf("            5--�˳�ϵͳ              \n");
	printf("*************************************\n");
	return;
}