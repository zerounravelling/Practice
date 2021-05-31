#ifndef READER_H_INCLUDED
#define READER_H_INCLUDED

struct Reader
{
	int r_num;//读者者证号
	char r_name[20];//读者名字
	char date[20];//借阅日期
	char z_name[20];//借阅书名
	struct Reader* next;
};
#define Len sizeof(struct Reader)
void Readr_oper();//用户系统主操作函数
void borrbooks();//借书函数
void retbooks();//归还图书函数
#endif
