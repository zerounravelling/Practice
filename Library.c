#include"Reader.h"
#include"Library.h"
#include"Allmenu.h"

void Main_oper()//主界面选择操作函数
{
	int choice1, choice2;
	choice2 = scanf_s("%d", &choice1);
	while (1)
	{
		while (0 == choice2)
		{
			scanf_s("%*s");
			printf("输入有误，请重新输入：");
			choice2 = scanf_s("%d", &choice1);
		}
		if (choice1 >= 1 || choice1 <= 3)
		{
			switch (choice1)
			{
			case 1://管理员系统				
				ad_oper();
				break;
			case 2://用户系统
				Readr_oper();
				break;
			case 0://退出整个系统
				system("cls");
				printf("  请任意键安全退出 ");
				exit(0);
				break;
			default:
				break;
			}
		}
		
		choice2 = scanf_s("%d", &choice1);
	}
	return;
}




void ad_oper()//管理者系统主操作函数
{
	system("cls");//清屏操作
	admenu();//显示管理者操作菜单
	getchar();//清除显示出Main_oper函数后的进行下一步的回车
	int choice;
	scanf_s("%d", &choice);
	while (1)
	{
		while (choice < 1 || choice>7)//当用户非法输入时，进入循环直到输入格式正确
		{
			scanf_s("%*s");//清除缓冲区的剩余的错误数据
			printf("输入有误，请输入正确的数字\n");
			scanf_s("%d", &choice);
		}
		switch (choice)
		{
		case 1://采编入库
		{
			addbooks();
			break;
		}
		case 2://清除库存
		{
			delbooks();
			break;
		}
		case 3://查询图书
		{
			search();
			break;
		}
		case 4://图书概览
		{
			viewallbooks();
			break;
		}
		case 5://状态查询
		{
			viewborrow();
			break;
		}
		case 6://返回上一级
		{
			Mainmenu();
			break;
		}
		case 7:
		{
			system("cls");
			printf("  请任意键安全退出 ");
			exit(0);
		}
		default:
			break;
		}
		scanf_s("%d", &choice);
	}
}

void addbooks()
{
	FILE* fp;
	char b_num[20], b_name[20], b_author[20];
	char b_num1[20], b_name1[20], b_author1[20];
	int now_stock = 0, all_stock = 0, addstock = 0;
	int now_stock1 = 0, all_stock1 = 0, addstock1 = 0;
	int j = 0, flag = 0;
	struct Books* p1=NULL;
	struct Books* p2 = p1;
	struct Books* head = p1;
	system("cls");

	fp = fopen("Library.txt", "a+");//打开文件，如果没有则创建空文件

	printf("请输入即将入库的图书的信息：\n");
	printf("书号 书名 著者 进库量(不同数据之间用空格隔开)\n");
	scanf("%s %s %s %d",b_num,b_name,b_author,&addstock);

		//统计所有图书种类数,用 j 记录
	
		fp = fopen("Library.txt", "r");		
		while (!feof(fp))
		{
			j++;
			fscanf(fp, "%s%s%s%d%d\n", b_num1, b_name1, b_author1, &now_stock1, &all_stock1);			
		}
		fclose(fp);
		if (j == 0)
		{
			fp = fopen("Library.txt", "a+");
			fprintf(fp, "%-8s%-9s%-14s%-7d%-7d\n", b_num, b_name, b_author, addstock, addstock);
			fclose(fp);//关闭文件			
			printf("\n入库成功 \n按任意键返回上一层\n");
			getch();
			system("cls");
			admenu();
			return;
		}
	fp = fopen("Library.txt", "a+");
	int i = 1, n = 0;
	for (; i <= j; i++)//建立链表
	{
		fscanf(fp,"%s%s%s%d%d",b_num1,b_name1,b_author1,&now_stock1,&all_stock1);
		n++;
		if (1 == n)
		{
			p1 = p2 = (struct Books*)malloc(len);
			head = p1;
		}
		else
		{
			p2->next = p1;
			p2 = p1;
			p1 = (struct Books*)malloc(len);
		}
		strcpy(p1->b_number, b_num1);
		strcpy(p1->b_name, b_name1);
		strcpy(p1->author, b_author1);
		p1 -> p_stock = now_stock1;
		p1->all_stock = all_stock1;
		if (!(strcmp(p1->b_number, b_num)))
		{
			if (!(strcmp(p1->b_name, b_name)))
			{
				if (!(strcmp(p1->author, b_author)))
				{//如果这种书在库存中已有，则只将现存量和总库存量增加
					p1->p_stock += addstock;
					p1->all_stock += addstock;
					flag = 1;
				}
			}
		}
	}
	
	if (1 != flag)
	{
		p2->next = p1;
		p2 = p1;
		p1 = (struct Books*)malloc(len);
		strcpy(p1->b_number, b_num);
		strcpy(p1->b_name, b_name);
		strcpy(p1->author, b_author);
		p1->p_stock = addstock;
		p1->all_stock = addstock;
	}
		p2->next = p1;
		p1->next = NULL;
		fclose(fp);
		//再把链表内容写入txt文件中
		fp = fopen("Library.txt", "w");//清空文件，只写打开，然后关闭
		//fclose(fp);
		//fp = fopen("Library.txt", "a");//追加文件
		p1 = head;
		for (; p1 != NULL;)//把链表内容覆盖到文件
		{
			fprintf(fp, "%-8s%-9s%-14s%-7d%-7d\n", p1->b_number, p1->b_name, p1->author, p1->p_stock, p1->all_stock);
			p1 = p1->next;
		}

		fclose(fp);//关闭文件
		printf("\n入库成功 \n按任意键返回上一层\n");
		getch();
		system("cls");
		admenu();
		return;
}

void delbooks()
{
	FILE* fp;
	char delname[20];//需要清除的图书的书名
	char b_num1[20], b_name1[20], b_author1[20];
	int now_stock = 0, all_stock = 0, addstock = 0;
	int now_stock1 = 0, all_stock1 = 0, addstock1 = 0;
	struct Books* p1 = NULL;
	struct Books* p2 = p1;
	struct Books* head = p1;
	if (NULL == (fp = fopen("Library.txt", "r")))//打开图书库存文件，如果fp为空则说明还未入库如何图书
	{
		printf("当前库存无任何图书，无法执行此功能\n请按任意键返回\n");
		getch();
		system("cls");
		admenu();
		return;
	}
	else
	{
		printf("请输入需要清除的图书的书名：\n");
		scanf("%s", delname);
		
		int j = 0;
		while (!feof(fp))
		{
			j++;
			fscanf(fp, "%s%s%s%d%d\n", b_num1, b_name1, b_author1, &now_stock1, &all_stock1);
		}
		if (0 == j)//则说明还未入库如何图书
		{
			printf("当前库存无任何图书，无法执行此功能\n请按任意键返回\n");
			fclose(fp);
			getch();
			system("cls");
			admenu();
			return;
		}
		else
		{//建立链表
			int i = 1, n = 0;
			rewind(fp);//文件指针回到开头
			for (; i <= j; i++)//建立链表
			{
				fscanf(fp, "%s%s%s%d%d", b_num1, b_name1, b_author1, &now_stock1, &all_stock1);
				
				if(strcmp(delname,b_name1))//对比库存里每一本书的书名和需要删除的书名
				{//若名字不同，strcmp函数返回非0，执行下面语句建立链表
					n++;
					if (1 == n)
					{
						p1 = p2 = (struct Books*)malloc(len);
						head = p1;
					}
					else
					{
						p2->next = p1;
						p2 = p1;
						p1 = (struct Books*)malloc(len);
					}
					strcpy(p1->b_number, b_num1);
					strcpy(p1->b_name, b_name1);
					strcpy(p1->author, b_author1);
					p1->p_stock = now_stock1;
					p1->all_stock = all_stock1;
				}
				
			}
			
			fclose(fp);
			if (n == 0)//如果图书只有一项且这一项刚好和要删除的相同
			{
				fp = fopen("Library.txt", "w");//清空文件
				fclose(fp);//关闭文件
				printf("删除成功，按任意键返回上一级\n");
				getch();
				system("cls");
				admenu();
				return;
			}
			else//链表善后
			{
				p2->next = p1;
				p1->next = NULL;
			}
			
			fp = fopen("Library.txt", "w");//把链表内容写入文件中
			p1 = head;
			for (; p1 != NULL;)//把链表内容覆盖到文件
			{
				fprintf(fp, "%-8s%-9s%-14s%-7d%-7d\n", p1->b_number, p1->b_name, p1->author, p1->p_stock, p1->all_stock);
				p1 = p1->next;
			}

			fclose(fp);//关闭文件
			if (n == j )
			{
				printf("\n图书不存在，删除失败 \n按任意键返回上一层\n");
			}
			else
			{
				printf("\n删除成功 \n按任意键返回上一层\n");
			}			
			getch();
			system("cls");
			admenu();
			return;
		}
	}
}

void search()
{
	FILE* fp;
	char seanum[20];//需要查询的图书的书号
	char seaname[20];//需要查询的图书的名字
	char seaauth[20];//需要查询的图书的著者
	int seastock;//需要查询的图书的现存量
	char b_num1[20], b_name1[20], b_author1[20];	
	int now_stock1 = 0, all_stock1 = 0, addstock1 = 0;
	if (NULL == (fp = fopen("Library.txt", "r")))//打开图书库存文件，如果fp为空则说明还未入库任何图书
	{
		printf("当前库存无任何图书，无法执行此功能\n请按任意键返回\n");
		getch();
		system("cls");
		admenu();
		return;
	}
	else
	{
		int choice1 = 0;
		int choice2 = 0;
		printf("请输入数字选择相应的查询方法：\n");
		printf("1----根据书号查询        2----根据书名查询\n");
		printf("3----根据著者查询        4----根据现存量查询\n\n");
		choice2 = scanf_s("%d", &choice1);
		while (0 == choice2 || choice1 < 1 || choice1>4)//防止用户非法输入
		{
			scanf_s("%*s");
			printf("输入有误，请重新输入：");
			choice2 = scanf_s("%d", &choice1);
		}
		
		switch (choice1)
		{
		case 1:
		{
			printf("请输入需要查询的图书的书号:\n");
			scanf("%s", seanum);
			break;
		}
		case 2:
		{
			printf("请输入需要查询的图书的书名：\n");
			scanf("%s", seaname);
			break;
		}
		case 3:
		{
			printf("请输入需要查询的图书的著者：\n");
			scanf("%s", seaauth);
			break;
		}
		case 4:
		{
			printf("请输入需要查询的图书的现存量,将显示所有现存量大于当前输入的现存量的图书：\n");
			scanf("%d", &seastock);
			break;
		}
		default:
		{
			break;
		}			
		}
		

		int j = 0;
		for (j = 0; !feof(fp); j++)
		{
			fscanf(fp, "%s%s%s%d%d", b_num1, b_name1, b_author1, &now_stock1, &all_stock1);
		}
		if (1 == j)//则说明还未入库如何图书
		{
			printf("当前库存无任何图书，无法执行此功能\n请按任意键返回\n");
			fclose(fp);
			getch();
			system("cls");
			admenu();
			return;
		}
		else
		{
			int i = 1, n = 0;
			rewind(fp);
			for (; i < j; i++)
			{
				fscanf(fp, "%s%s%s%d%d", b_num1, b_name1, b_author1, &now_stock1, &all_stock1);
				if (1 == choice1)//如果用户选择根据书号查询
				{
					if (!strcmp(seanum, b_num1))
					{
						n++;
						printf("查询结果:\n\n");
						printf("书号\t书名\t 作者\t    现存量  总存量\n");
						printf("%-8s%-9s%-14s%-7d%-7d\n", b_num1, b_name1, b_author1, now_stock1, all_stock1);
					}
				}
				if (2 == choice1)//如果用户选择根据书名查询
				{
					if (!strcmp(seaname, b_name1))
					{
						n++;
						printf("查询结果:\n\n");
						printf("书号\t书名\t 作者\t    现存量  总存量\n");
						printf("%-8s%-9s%-14s%-7d%-7d\n", b_num1, b_name1, b_author1, now_stock1, all_stock1);
					}
				}
				if (3 == choice1)//如果用户选择根据著者查询
				{
					if (!strcmp(seaauth, b_author1))
					{
						n++;
						printf("查询结果:\n\n");
						printf("书号\t书名\t 作者\t    现存量  总存量\n");
						printf("%-8s%-9s%-14s%-7d%-7d\n", b_num1, b_name1, b_author1, now_stock1, all_stock1);
					}
				}
				if (4 == choice1)//如果用户选择根据现存量查询
				{
					if (now_stock1 > seastock)
					{
						n++;
						printf("查询结果:\n\n");
						printf("书号\t书名\t 作者\t    现存量  总存量\n");
						printf("%-8s%-9s%-14s%-7d%-7d\n", b_num1, b_name1, b_author1, now_stock1, all_stock1);
					}
				}
			}

			if (n == 0)//如果不存在此书
			{
				printf("该书在库存中无记录\n");
			}
			fclose(fp);//关闭文件
			printf("\n请按任意键返回\n");
			getch();
			system("cls");
			admenu();
			return;
		}
	}
}

void viewallbooks()
{
	FILE* fp;
	char b_num1[20], b_name1[20], b_author1[20];
	int now_stock1 = 0, all_stock1 = 0, addstock1 = 0;
	if (NULL == (fp = fopen("Library.txt", "r")))//打开图书库存文件，如果fp为空则说明还未入库任何图书
	{
		printf("当前库存无任何图书\n请按任意键返回\n");
		getch();
		system("cls");
		admenu();
		return;
	} 
	else
	{
		int j = 0;
		for (j = 0; !feof(fp); j++)
		{
			fscanf(fp, "%s%s%s%d%d", b_num1, b_name1, b_author1, &now_stock1, &all_stock1);
		}
		if (1 == j)//则说明还未入库如何图书
		{
			printf("当前库存无任何图书，无法执行此功能\n请按任意键返回\n");
			fclose(fp);
			getch();
			system("cls");
			admenu();
			return;
		}
		else
		{
			int i = 1;
			rewind(fp);
			printf("查询结果:\n\n");
			printf("书号\t书名\t 作者\t    现存量  总存量\n");
			for (; i < j; i++)//循环打印库存文件里的信息
			{
				fscanf(fp, "%s%s%s%d%d", b_num1, b_name1, b_author1, &now_stock1, &all_stock1);									
				printf("%-8s%-9s%-14s%-7d%-7d\n", b_num1, b_name1, b_author1, now_stock1, all_stock1);			
			}

			fclose(fp);//关闭文件
			printf("\n请按任意键返回\n");
			getch();
			system("cls");
			admenu();
			return;
		}

	}
}

void viewborrow()
{
	FILE* fp2;
	struct Reader* head1 = NULL;
	struct Reader* p3, * p4;
	p3 = p4 = head1;
	int readernum = 0, readernum1 = 0;
	char readername1[20], borrbname1[20], date1[20];
	if (NULL == (fp2 = fopen("Reader.txt", "r"))) // 打开读者借阅记录文件
	{
		printf("系统中暂无借书记录，无法执行此功能\n请按任意键返回\n");
		getch();
		system("cls");
		admenu();
		return;
	}
	
	int i = 0, j = 0, c = 0;
	for (; !feof(fp2); )
	{
		c = fscanf(fp2, "%d%s%s%s\n", &readernum1, readername1, borrbname1, date1);
		j++;
	}
	
	if ( -1 == c)//如果记录文件存在但记录为空
	{
		printf("系统中借书记录\n请按任意键返回\n");
		fclose(fp2);
		getch();
		system("cls");
		admenu();
		return;
	}
	else
	{
		rewind(fp2);
		printf("查询结果:\n\n");
		printf("读者证号  读者名\t 借阅书名\t归还日期\n");
		for (; i < j; i++)//循环打印库存文件里的信息
		{
			fscanf(fp2,"%d%s%s%s", &readernum1, readername1, borrbname1, date1);
			printf("%-10d%-15s%-16s%-18s\n", readernum1, readername1, borrbname1, date1);
		}

		fclose(fp2);//关闭文件
		printf("\n请按任意键返回\n");
		getch();
		system("cls");
		admenu();
		return;
	}
}