#include"Reader.h"
#include"Library.h"
#include"Allmenu.h"

void Main_oper()//������ѡ���������
{
	int choice1, choice2;
	choice2 = scanf_s("%d", &choice1);
	while (1)
	{
		while (0 == choice2)
		{
			scanf_s("%*s");
			printf("�����������������룺");
			choice2 = scanf_s("%d", &choice1);
		}
		if (choice1 >= 1 || choice1 <= 3)
		{
			switch (choice1)
			{
			case 1://����Աϵͳ				
				ad_oper();
				break;
			case 2://�û�ϵͳ
				Readr_oper();
				break;
			case 0://�˳�����ϵͳ
				system("cls");
				printf("  ���������ȫ�˳� ");
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




void ad_oper()//������ϵͳ����������
{
	system("cls");//��������
	admenu();//��ʾ�����߲����˵�
	getchar();//�����ʾ��Main_oper������Ľ�����һ���Ļس�
	int choice;
	scanf_s("%d", &choice);
	while (1)
	{
		while (choice < 1 || choice>7)//���û��Ƿ�����ʱ������ѭ��ֱ�������ʽ��ȷ
		{
			scanf_s("%*s");//�����������ʣ��Ĵ�������
			printf("����������������ȷ������\n");
			scanf_s("%d", &choice);
		}
		switch (choice)
		{
		case 1://�ɱ����
		{
			addbooks();
			break;
		}
		case 2://������
		{
			delbooks();
			break;
		}
		case 3://��ѯͼ��
		{
			search();
			break;
		}
		case 4://ͼ�����
		{
			viewallbooks();
			break;
		}
		case 5://״̬��ѯ
		{
			viewborrow();
			break;
		}
		case 6://������һ��
		{
			Mainmenu();
			break;
		}
		case 7:
		{
			system("cls");
			printf("  ���������ȫ�˳� ");
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

	fp = fopen("Library.txt", "a+");//���ļ������û���򴴽����ļ�

	printf("�����뼴������ͼ�����Ϣ��\n");
	printf("��� ���� ���� ������(��ͬ����֮���ÿո����)\n");
	scanf("%s %s %s %d",b_num,b_name,b_author,&addstock);

		//ͳ������ͼ��������,�� j ��¼
	
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
			fclose(fp);//�ر��ļ�			
			printf("\n���ɹ� \n�������������һ��\n");
			getch();
			system("cls");
			admenu();
			return;
		}
	fp = fopen("Library.txt", "a+");
	int i = 1, n = 0;
	for (; i <= j; i++)//��������
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
				{//����������ڿ�������У���ֻ���ִ������ܿ��������
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
		//�ٰ���������д��txt�ļ���
		fp = fopen("Library.txt", "w");//����ļ���ֻд�򿪣�Ȼ��ر�
		//fclose(fp);
		//fp = fopen("Library.txt", "a");//׷���ļ�
		p1 = head;
		for (; p1 != NULL;)//���������ݸ��ǵ��ļ�
		{
			fprintf(fp, "%-8s%-9s%-14s%-7d%-7d\n", p1->b_number, p1->b_name, p1->author, p1->p_stock, p1->all_stock);
			p1 = p1->next;
		}

		fclose(fp);//�ر��ļ�
		printf("\n���ɹ� \n�������������һ��\n");
		getch();
		system("cls");
		admenu();
		return;
}

void delbooks()
{
	FILE* fp;
	char delname[20];//��Ҫ�����ͼ�������
	char b_num1[20], b_name1[20], b_author1[20];
	int now_stock = 0, all_stock = 0, addstock = 0;
	int now_stock1 = 0, all_stock1 = 0, addstock1 = 0;
	struct Books* p1 = NULL;
	struct Books* p2 = p1;
	struct Books* head = p1;
	if (NULL == (fp = fopen("Library.txt", "r")))//��ͼ�����ļ������fpΪ����˵����δ������ͼ��
	{
		printf("��ǰ������κ�ͼ�飬�޷�ִ�д˹���\n�밴���������\n");
		getch();
		system("cls");
		admenu();
		return;
	}
	else
	{
		printf("��������Ҫ�����ͼ���������\n");
		scanf("%s", delname);
		
		int j = 0;
		while (!feof(fp))
		{
			j++;
			fscanf(fp, "%s%s%s%d%d\n", b_num1, b_name1, b_author1, &now_stock1, &all_stock1);
		}
		if (0 == j)//��˵����δ������ͼ��
		{
			printf("��ǰ������κ�ͼ�飬�޷�ִ�д˹���\n�밴���������\n");
			fclose(fp);
			getch();
			system("cls");
			admenu();
			return;
		}
		else
		{//��������
			int i = 1, n = 0;
			rewind(fp);//�ļ�ָ��ص���ͷ
			for (; i <= j; i++)//��������
			{
				fscanf(fp, "%s%s%s%d%d", b_num1, b_name1, b_author1, &now_stock1, &all_stock1);
				
				if(strcmp(delname,b_name1))//�Աȿ����ÿһ�������������Ҫɾ��������
				{//�����ֲ�ͬ��strcmp�������ط�0��ִ��������佨������
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
			if (n == 0)//���ͼ��ֻ��һ������һ��պú�Ҫɾ������ͬ
			{
				fp = fopen("Library.txt", "w");//����ļ�
				fclose(fp);//�ر��ļ�
				printf("ɾ���ɹ����������������һ��\n");
				getch();
				system("cls");
				admenu();
				return;
			}
			else//�����ƺ�
			{
				p2->next = p1;
				p1->next = NULL;
			}
			
			fp = fopen("Library.txt", "w");//����������д���ļ���
			p1 = head;
			for (; p1 != NULL;)//���������ݸ��ǵ��ļ�
			{
				fprintf(fp, "%-8s%-9s%-14s%-7d%-7d\n", p1->b_number, p1->b_name, p1->author, p1->p_stock, p1->all_stock);
				p1 = p1->next;
			}

			fclose(fp);//�ر��ļ�
			if (n == j )
			{
				printf("\nͼ�鲻���ڣ�ɾ��ʧ�� \n�������������һ��\n");
			}
			else
			{
				printf("\nɾ���ɹ� \n�������������һ��\n");
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
	char seanum[20];//��Ҫ��ѯ��ͼ������
	char seaname[20];//��Ҫ��ѯ��ͼ�������
	char seaauth[20];//��Ҫ��ѯ��ͼ�������
	int seastock;//��Ҫ��ѯ��ͼ����ִ���
	char b_num1[20], b_name1[20], b_author1[20];	
	int now_stock1 = 0, all_stock1 = 0, addstock1 = 0;
	if (NULL == (fp = fopen("Library.txt", "r")))//��ͼ�����ļ������fpΪ����˵����δ����κ�ͼ��
	{
		printf("��ǰ������κ�ͼ�飬�޷�ִ�д˹���\n�밴���������\n");
		getch();
		system("cls");
		admenu();
		return;
	}
	else
	{
		int choice1 = 0;
		int choice2 = 0;
		printf("����������ѡ����Ӧ�Ĳ�ѯ������\n");
		printf("1----������Ų�ѯ        2----����������ѯ\n");
		printf("3----�������߲�ѯ        4----�����ִ�����ѯ\n\n");
		choice2 = scanf_s("%d", &choice1);
		while (0 == choice2 || choice1 < 1 || choice1>4)//��ֹ�û��Ƿ�����
		{
			scanf_s("%*s");
			printf("�����������������룺");
			choice2 = scanf_s("%d", &choice1);
		}
		
		switch (choice1)
		{
		case 1:
		{
			printf("��������Ҫ��ѯ��ͼ������:\n");
			scanf("%s", seanum);
			break;
		}
		case 2:
		{
			printf("��������Ҫ��ѯ��ͼ���������\n");
			scanf("%s", seaname);
			break;
		}
		case 3:
		{
			printf("��������Ҫ��ѯ��ͼ������ߣ�\n");
			scanf("%s", seaauth);
			break;
		}
		case 4:
		{
			printf("��������Ҫ��ѯ��ͼ����ִ���,����ʾ�����ִ������ڵ�ǰ������ִ�����ͼ�飺\n");
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
		if (1 == j)//��˵����δ������ͼ��
		{
			printf("��ǰ������κ�ͼ�飬�޷�ִ�д˹���\n�밴���������\n");
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
				if (1 == choice1)//����û�ѡ�������Ų�ѯ
				{
					if (!strcmp(seanum, b_num1))
					{
						n++;
						printf("��ѯ���:\n\n");
						printf("���\t����\t ����\t    �ִ���  �ܴ���\n");
						printf("%-8s%-9s%-14s%-7d%-7d\n", b_num1, b_name1, b_author1, now_stock1, all_stock1);
					}
				}
				if (2 == choice1)//����û�ѡ�����������ѯ
				{
					if (!strcmp(seaname, b_name1))
					{
						n++;
						printf("��ѯ���:\n\n");
						printf("���\t����\t ����\t    �ִ���  �ܴ���\n");
						printf("%-8s%-9s%-14s%-7d%-7d\n", b_num1, b_name1, b_author1, now_stock1, all_stock1);
					}
				}
				if (3 == choice1)//����û�ѡ��������߲�ѯ
				{
					if (!strcmp(seaauth, b_author1))
					{
						n++;
						printf("��ѯ���:\n\n");
						printf("���\t����\t ����\t    �ִ���  �ܴ���\n");
						printf("%-8s%-9s%-14s%-7d%-7d\n", b_num1, b_name1, b_author1, now_stock1, all_stock1);
					}
				}
				if (4 == choice1)//����û�ѡ������ִ�����ѯ
				{
					if (now_stock1 > seastock)
					{
						n++;
						printf("��ѯ���:\n\n");
						printf("���\t����\t ����\t    �ִ���  �ܴ���\n");
						printf("%-8s%-9s%-14s%-7d%-7d\n", b_num1, b_name1, b_author1, now_stock1, all_stock1);
					}
				}
			}

			if (n == 0)//��������ڴ���
			{
				printf("�����ڿ�����޼�¼\n");
			}
			fclose(fp);//�ر��ļ�
			printf("\n�밴���������\n");
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
	if (NULL == (fp = fopen("Library.txt", "r")))//��ͼ�����ļ������fpΪ����˵����δ����κ�ͼ��
	{
		printf("��ǰ������κ�ͼ��\n�밴���������\n");
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
		if (1 == j)//��˵����δ������ͼ��
		{
			printf("��ǰ������κ�ͼ�飬�޷�ִ�д˹���\n�밴���������\n");
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
			printf("��ѯ���:\n\n");
			printf("���\t����\t ����\t    �ִ���  �ܴ���\n");
			for (; i < j; i++)//ѭ����ӡ����ļ������Ϣ
			{
				fscanf(fp, "%s%s%s%d%d", b_num1, b_name1, b_author1, &now_stock1, &all_stock1);									
				printf("%-8s%-9s%-14s%-7d%-7d\n", b_num1, b_name1, b_author1, now_stock1, all_stock1);			
			}

			fclose(fp);//�ر��ļ�
			printf("\n�밴���������\n");
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
	if (NULL == (fp2 = fopen("Reader.txt", "r"))) // �򿪶��߽��ļ�¼�ļ�
	{
		printf("ϵͳ�����޽����¼���޷�ִ�д˹���\n�밴���������\n");
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
	
	if ( -1 == c)//�����¼�ļ����ڵ���¼Ϊ��
	{
		printf("ϵͳ�н����¼\n�밴���������\n");
		fclose(fp2);
		getch();
		system("cls");
		admenu();
		return;
	}
	else
	{
		rewind(fp2);
		printf("��ѯ���:\n\n");
		printf("����֤��  ������\t ��������\t�黹����\n");
		for (; i < j; i++)//ѭ����ӡ����ļ������Ϣ
		{
			fscanf(fp2,"%d%s%s%s", &readernum1, readername1, borrbname1, date1);
			printf("%-10d%-15s%-16s%-18s\n", readernum1, readername1, borrbname1, date1);
		}

		fclose(fp2);//�ر��ļ�
		printf("\n�밴���������\n");
		getch();
		system("cls");
		admenu();
		return;
	}
}