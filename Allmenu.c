#include "Reader.h"
#include "Library.h"
#include "Allmenu.h"
void Mainmenu()
{
	system("cls");//清屏操作，使界面更加整洁
	printf("*********************************\n");
	printf("        1---管理员系统              \n");
	printf("        2---用户操作系统            \n");
	printf("        0---退出系统                \n");
	printf("*********************************\n");
	printf("请输入数字选择进入相应的系统:  ");
	Main_oper();//进入主界面操作函数
	return;
}

void admenu()
{
	printf("*********************************\n");
	printf("        1---采编入库              \n");
	printf("        2---库存清除              \n");
	printf("        3---查询图书               \n");
	printf("        4---图书总览               \n");
	printf("        5---借阅记录总览               \n");
	printf("        6---返回上一级               \n");
	printf("        7---退出系统               \n");
	printf("*********************************\n");
	printf("请输入数字选择进入相应的系统:  ");
	return;
}

void Readermenu()
{
	printf("*************************************\n");
	printf("            1--借阅图书              \n");
	printf("            2--归还图书              \n");
	printf("            3--查询图书              \n");
	printf("            4--返回上一级            \n");
	printf("            5--退出系统              \n");
	printf("*************************************\n");
	return;
}

//111
