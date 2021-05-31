#include"Reader.h"
#include"Library.h"
#include"Allmenu.h"

void Readr_oper()//�û�ϵͳѡ���������
{
	system("cls");//��������
	Readermenu();//��ʾ�û������˵���
	getchar();//�����ʾ��Main_oper������Ľ�����һ���Ļس�
	int choice;
	scanf_s("%d", &choice);
	while (1)
	{
		while (choice < 1 || choice>5)//���û��Ƿ�����ʱ������ѭ��ֱ�������ʽ��ȷ
		{
			scanf_s("%*s");//�����������ʣ��Ĵ�������
			printf("����������������ȷ������\n");
			scanf_s("%d", &choice);
		}
		switch (choice)
		{
		case 1://����ͼ��
		{
			borrbooks();
			break;
		}
		case 2://�黹ͼ�� 
		{
			retbooks();
			break;
		}
		case 3://��ѯͼ��
		{
			search();
			system("cls");
			Readermenu();
			break;
		}
		case 4://������һ��
		{
			Mainmenu();
			break;
		}
		case 5://�˳�ϵͳ
		{
			system("cls");
			printf("  ���������ȫ�˳� ");
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
	FILE* fp1, * fp2;//fp1ָ��Library.txt, fp2ָ��Reader.txt 
	struct Books* head = NULL;
	struct Books* index = NULL;
	struct Books* p1, * p2;
	p1 = p2 = head;
	int flag = 0;
	char borrbname[20], borrbnum[20];
	char b_num1[20], b_name1[20], b_author1[20];
	int now_stock1 = 0, all_stock1 = 0, addstock1 = 0;
	
	if (NULL == (fp1 = fopen("Library.txt", "r")))//��ͼ�����ļ������fpΪ����˵����δ������ͼ��
	{
		printf("��ǰ������κ�ͼ�飬�޷�ִ�д˹���\n�밴���������\n");
		getch();
		system("cls");
		Readermenu();
		return;
	}
	printf("������������ĵ���ţ�\n");
	scanf("%s", borrbnum);
	printf("������������ĵ�������\n");
	scanf("%s", borrbname);

	//ͳ������ͼ��������,�� j ��¼
	int i = 1, j = 0, n = 0;
	for (j = 0; !feof(fp1); j++)
	{
		fscanf(fp1, "%s%s%s%d%d", b_num1, b_name1, b_author1, &now_stock1, &all_stock1);
	}
	rewind(fp1);//�ļ�ָ��ص���ͷ
	for (; i < j; i++)//��������洢ͼ������Ϣ
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
				index = p1;//�������д��ڴ��飬����indexָ���¼�˽��
			}
		}
	}
	//�����ƺ�
	if (1 != j)
	{
		p2->next = p1;
		p1->next = NULL;
	}
	
	fclose(fp1);
	if (NULL == index || index->p_stock <= 0)//��������û�д���,�˳����麯��
	{
		printf("�ܱ�Ǹ�������Ŀǰû�д���\n�밴���������\n");
		getch();
		system("cls");
		Readermenu();
		return;
	}
	//���������������ִ�������0���ѿ�����仯�����������ļ�
	fp1 = fopen("Library.txt", "w");
	p1 = head;
	index->p_stock--;//Ŀ�����ִ�����1
	for (; p1 != NULL;)
	{
		fprintf(fp1, "%-8s%-9s%-14s%-7d%-7d\n", p1->b_number, p1->b_name, p1->author, p1->p_stock, p1->all_stock);
		p1 = p1->next;
	}
	fclose(fp1);

	//����ɹ��󣬽����������޸�Reader.txt�ļ���ļ�¼
	fp2 = fopen("Reader.txt", "a");//���ļ������û���򴴽����ļ�
	int readernum = 0;
	char readername[20], date[20];
	printf("\n�밴���¸�ʽ���������Ϣ:\n ����֤�� ���� �黹���ڣ���ͬ�����ÿո������\n������:");//¼�������Ϣ
	scanf("%d %s %s", &readernum, readername, date);
	fprintf(fp2,"%-10d%-23s%-10s%-18s\n", readernum, readername, borrbname, date);
	fclose(fp2);
	printf("����ɹ�!�����������\n");
	getch();
	system("cls");
	Readermenu();
	return;
}

void retbooks()
{
	FILE* fp1, * fp2;//fp1ָ��Library.txt, fp2ָ��Reader.txt 
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
	if (NULL == (fp1 = fopen("Library.txt", "r")))//��ͼ�����ļ������fpΪ����˵����δ������ͼ��
	{
		printf("ϵͳ���޽����¼���޷�ִ�д˹���\n�밴���������\n");
		getch();
		system("cls");
		Readermenu();
		return;
	}
	if (NULL == (fp2 = fopen("Reader.txt", "r"))) // �򿪶��߽��ļ�¼�ļ�
	{
		printf("ϵͳ�����޽����¼���޷�ִ�д˹���\n�밴���������\n");
		getch();
		system("cls");
		Readermenu();
		return;
	}
	printf("���������Ķ���֤�ţ�\n");
	scanf("%d", &readernum);
	printf("��������ĵ�������\n");
	scanf("%s", borrbname);
	int i = 0, j = 0, n = 0;
	
	for (; !feof(fp2); j++)
	{	
			fscanf(fp2, "%d%s%s%s\n", &readernum1, readername1, borrbname1, date1);

			if (readernum1 == readernum)//����ƥ��ļ�¼��ִ���������
			{
				if (!strcmp(borrbname1, borrbname))
				{
					flag = 1;
				}
			}
	}
	if (0 == j || 0 == flag)//�����¼�ļ����ڵ�û��ƥ��ļ�¼
	{
		printf("ϵͳ�����޴˽����¼���޷�ִ�д˹���\n�밴���������\n");
		fclose(fp2);
		getch();
		system("cls");
		Readermenu();
		return;
	}
	else//���ļ�¼���ڣ���������
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
					continue;//����ҵ�ƥ��Ľ����¼����ѭ���������ü�¼���ټ������������Դﵽɾ���ü�¼��Ŀ��
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
			p3->r_num = readernum1;//���ƶ���֤��
			strcpy(p3->r_name, readername1);//���ƶ�������
			strcpy(p3->z_name, borrbname1);//������������
			strcpy(p3->date, date1);//���ƹ黹����
		}
		fclose(fp2);
		if (NULL == head1)
		{
			change = 1;
			fp2 = fopen("Reader.txt", "w");//����ļ�
			fclose(fp2);//�ر��ļ�
		}
		else//������β
		{
			p4->next = p3;
			p3->next = NULL;
			//�ٰ���������д��Reader.txt�ļ���
			fp2 = fopen("Reader.txt", "w");
			p3 = head1;
			for (; p3 != NULL;)
			{
				fprintf(fp2, "%-10d%-23s%-10s%-18s\n", p3->r_num, p3->r_name, p3->z_name, p3->date);
				p3 = p3->next;
			}
			fclose(fp2);
		}
		

		//�����,��Ҫ�ٰѸ���Ŀ������һ
		i = 1; j = 0, n = 0;
		for (j = 0; !feof(fp1); j++)
		{
			fscanf(fp1, "%s%s%s%d%d", b_num1, b_name1, b_author1, &now_stock1, &all_stock1);
		}
		if (1 == j)//�������¼Ϊ��
		{
			printf("ϵͳ��¼����\n�����������\n");
			fclose(fp1);
			getch();
			system("cls");
			Readermenu();
			return;
		}
		rewind(fp1);//�ļ�ָ��ص���ͷ
		for (; i < j; i++)//��������洢ͼ������Ϣ
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
				index = p1;//�������д��ڴ��飬����indexָ���¼�˽��
			}		
		}
		//�����ƺ�	
		p2->next = p1;
		p1->next = NULL;
		index->p_stock+=change;
		fclose(fp1);//�ر��ļ�
		
		//�ٰ�������������д�����¼�ļ���
		fp1 = fopen("Library.txt", "w");//����������д���ļ���
		p1 = head;
		for (; p1 != NULL;)//���������ݸ��ǵ��ļ�
		{
			fprintf(fp1, "%-8s%-9s%-14s%-7d%-7d\n", p1->b_number, p1->b_name, p1->author, p1->p_stock, p1->all_stock);
			p1 = p1->next;
		}
		fclose(fp1);//�ر��ļ�
		printf("����ɹ�!\n�����������\n");
		getch();//����
		system("cls");
		Readermenu();
		return;
	}
}