#include"Reader.h"
#include"Library.h"
#include"Allmenu.h"

void Readr_oper()//用户系统选择操作函数
{
	system("cls");//清屏操作
	Readermenu();//显示用户操作菜单栏
	getchar();//清除显示出Main_oper函数后的进行下一步的回车
	int choice;
	scanf_s("%d", &choice);
	while (1)
	{
		while (choice < 1 || choice>5)//当用户非法输入时，进入循环直到输入格式正确
		{
			scanf_s("%*s");//清除缓冲区的剩余的错误数据
			printf("输入有误，请输入正确的数字\n");
			scanf_s("%d", &choice);
		}
		switch (choice)
		{
		case 1://借阅图书
		{
			borrbooks();
			break;
		}
		case 2://归还图书 
		{
			retbooks();
			break;
		}
		case 3://查询图书
		{
			search();
			system("cls");
			Readermenu();
			break;
		}
		case 4://返回上一级
		{
			Mainmenu();
			break;
		}
		case 5://退出系统
		{
			system("cls");
			printf("  请任意键安全退出 ");
			exit(0);
			break;
		}
		default:
			break;
		}
		scanf_s("%d", &choice);
	}
}

void borrbooks()
{
	FILE* fp1, * fp2;//fp1指向Library.txt, fp2指向Reader.txt 
	struct Books* head = NULL;
	struct Books* index = NULL;
	struct Books* p1, * p2;
	p1 = p2 = head;
	int flag = 0;
	char borrbname[20], borrbnum[20];
	char b_num1[20], b_name1[20], b_author1[20];
	int now_stock1 = 0, all_stock1 = 0, addstock1 = 0;
	
	if (NULL == (fp1 = fopen("Library.txt", "r")))//打开图书库存文件，如果fp为空则说明还未入库如何图书
	{
		printf("当前库存无任何图书，无法执行此功能\n请按任意键返回\n");
		getch();
		system("cls");
		Readermenu();
		return;
	}
	printf("请输入所需借阅的书号：\n");
	scanf("%s", borrbnum);
	printf("请输入所需借阅的书名：\n");
	scanf("%s", borrbname);

	//统计所有图书种类数,用 j 记录
	int i = 1, j = 0, n = 0;
	for (j = 0; !feof(fp1); j++)
	{
		fscanf(fp1, "%s%s%s%d%d", b_num1, b_name1, b_author1, &now_stock1, &all_stock1);
	}
	rewind(fp1);//文件指针回到开头
	for (; i < j; i++)//建立链表存储图书库存信息
	{
		fscanf(fp1, "%s%s%s%d%d", b_num1, b_name1, b_author1, &now_stock1, &all_stock1);
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
		if (!strcmp(p1->b_number, borrbnum))
		{
			if (!strcmp(p1->b_name, borrbname))
			{
				index = p1;//如果存库中存在此书，则用index指针记录此结点
			}
		}
	}
	//链表善后
	if (1 != j)
	{
		p2->next = p1;
		p1->next = NULL;
	}
	
	fclose(fp1);
	if (NULL == index || index->p_stock <= 0)//如果库存中没有此书,退出借书函数
	{
		printf("很抱歉，库存中目前没有此书\n请按任意键返回\n");
		getch();
		system("cls");
		Readermenu();
		return;
	}
	//如果所借书存在且现存量大于0，把库存量变化后的链表存入文件
	fp1 = fopen("Library.txt", "w");
	p1 = head;
	index->p_stock--;//目标书现存量减1
	for (; p1 != NULL;)
	{
		fprintf(fp1, "%-8s%-9s%-14s%-7d%-7d\n", p1->b_number, p1->b_name, p1->author, p1->p_stock, p1->all_stock);
		p1 = p1->next;
	}
	fclose(fp1);

	//借书成功后，接着来操作修改Reader.txt文件里的记录
	fp2 = fopen("Reader.txt", "a");//打开文件，如果没有则创建空文件
	int readernum = 0;
	char readername[20], date[20];
	printf("\n请按以下格式输入读者信息:\n 读者证号 姓名 归还日期（不同数据用空格隔开）\n请输入:");//录入读者信息
	scanf("%d %s %s", &readernum, readername, date);
	fprintf(fp2,"%-10d%-23s%-10s%-18s\n", readernum, readername, borrbname, date);
	fclose(fp2);
	printf("借书成功!按任意键返回\n");
	getch();
	system("cls");
	Readermenu();
	return;
}

void retbooks()
{
	FILE* fp1, * fp2;//fp1指向Library.txt, fp2指向Reader.txt 
	struct Books* head = NULL;
	struct Books* index = NULL;
	struct Books* p1, * p2;
	p1 = p2 = head;
	struct Reader* head1 = NULL;
	struct Reader* p3, * p4;
	p3 = p4 = head1;
	int flag = 0,  change = 0;
	char borrbname[20];
	char b_num1[20], b_name1[20], b_author1[20];
	int now_stock1 = 0, all_stock1 = 0, addstock1 = 0;
	int readernum = 0, readernum1 = 0;
	char readername1[20], borrbname1[20], date1[20];
	if (NULL == (fp1 = fopen("Library.txt", "r")))//打开图书库存文件，如果fp为空则说明还未入库如何图书
	{
		printf("系统暂无借书记录，无法执行此功能\n请按任意键返回\n");
		getch();
		system("cls");
		Readermenu();
		return;
	}
	if (NULL == (fp2 = fopen("Reader.txt", "r"))) // 打开读者借阅记录文件
	{
		printf("系统中暂无借书记录，无法执行此功能\n请按任意键返回\n");
		getch();
		system("cls");
		Readermenu();
		return;
	}
	printf("请输入您的读者证号：\n");
	scanf("%d", &readernum);
	printf("请输入借阅的书名：\n");
	scanf("%s", borrbname);
	int i = 0, j = 0, n = 0;
	
	for (; !feof(fp2); j++)
	{	
			fscanf(fp2, "%d%s%s%s\n", &readernum1, readername1, borrbname1, date1);

			if (readernum1 == readernum)//若有匹配的记录，执行下列语句
			{
				if (!strcmp(borrbname1, borrbname))
				{
					flag = 1;
				}
			}
	}
	if (0 == j || 0 == flag)//如果记录文件存在但没有匹配的记录
	{
		printf("系统中暂无此借书记录，无法执行此功能\n请按任意键返回\n");
		fclose(fp2);
		getch();
		system("cls");
		Readermenu();
		return;
	}
	else//借阅记录存在，建立链表
	{
		rewind(fp2);
		for (; i < j; i++)
		{
			fscanf(fp2, "%d%s%s%s\n", &readernum1, readername1, borrbname1, date1);
			if (readernum == readernum1)
			{
				if (!strcmp(borrbname, borrbname1))
				{
					change++;
					continue;//如果找到匹配的借书记录，则循环中跳过该记录，再继续建立链表以达到删除该记录的目的
				}
			}
			n++;
			if (1 == n)
			{
				p3 = p4 = (struct Reader*)malloc(Len);
				head1 = p3;
			}
			else
			{
				p4->next = p3;
				p4 = p3;
				p3 = (struct Reader*)malloc(Len);
			}
			p3->r_num = readernum1;//复制读者证号
			strcpy(p3->r_name, readername1);//复制读者名字
			strcpy(p3->z_name, borrbname1);//复制所借书名
			strcpy(p3->date, date1);//复制归还日期
		}
		fclose(fp2);
		if (NULL == head1)
		{
			change = 1;
			fp2 = fopen("Reader.txt", "w");//清空文件
			fclose(fp2);//关闭文件
		}
		else//链表收尾
		{
			p4->next = p3;
			p3->next = NULL;
			//再把链表内容写入Reader.txt文件中
			fp2 = fopen("Reader.txt", "w");
			p3 = head1;
			for (; p3 != NULL;)
			{
				fprintf(fp2, "%-10d%-23s%-10s%-18s\n", p3->r_num, p3->r_name, p3->z_name, p3->date);
				p3 = p3->next;
			}
			fclose(fp2);
		}
		

		//还书后,还要再把该书的库存量加一
		i = 1; j = 0, n = 0;
		for (j = 0; !feof(fp1); j++)
		{
			fscanf(fp1, "%s%s%s%d%d", b_num1, b_name1, b_author1, &now_stock1, &all_stock1);
		}
		if (1 == j)//如果库存记录为空
		{
			printf("系统记录出错\n按任意键返回\n");
			fclose(fp1);
			getch();
			system("cls");
			Readermenu();
			return;
		}
		rewind(fp1);//文件指针回到开头
		for (; i < j; i++)//建立链表存储图书库存信息
		{
			fscanf(fp1, "%s%s%s%d%d", b_num1, b_name1, b_author1, &now_stock1, &all_stock1);
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
			
			if (!strcmp(p1->b_name, borrbname))
			{
				index = p1;//如果存库中存在此书，则用index指针记录此结点
			}		
		}
		//链表善后	
		p2->next = p1;
		p1->next = NULL;
		index->p_stock+=change;
		fclose(fp1);//关闭文件
		
		//再把链表内容重新写入库存记录文件中
		fp1 = fopen("Library.txt", "w");//把链表内容写入文件中
		p1 = head;
		for (; p1 != NULL;)//把链表内容覆盖到文件
		{
			fprintf(fp1, "%-8s%-9s%-14s%-7d%-7d\n", p1->b_number, p1->b_name, p1->author, p1->p_stock, p1->all_stock);
			p1 = p1->next;
		}
		fclose(fp1);//关闭文件
		printf("还书成功!\n按任意键返回\n");
		getch();//返回
		system("cls");
		Readermenu();
		return;
	}
}