#ifndef READER_H_INCLUDED
#define READER_H_INCLUDED

struct Reader
{
	int r_num;//������֤��
	char r_name[20];//��������
	char date[20];//��������
	char z_name[20];//��������
	struct Reader* next;
};
#define Len sizeof(struct Reader)
void Readr_oper();//�û�ϵͳ����������
void borrbooks();//���麯��
void retbooks();//�黹ͼ�麯��
#endif
