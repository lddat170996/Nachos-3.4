#include "syscall.h"
#include "copyright.h"
#include "hamphu.h"
/*int atoi(char buf[],int length)
{
	int tmpnum = 0;
	int i =0;
	if(buf[0] == '-' )
		i++;
	for(i;i<length;i++)
	{
		if(buf[i] >= '0' && buf[i] <='9')
		{
			tmpnum = tmpnum*10 + (buf[i]&0XF);
		}
		else{
		if(buf[i] == '\0' || buf[i] == ' ' || buf[i] == '\n')
			break;
		else 
			return -10000;
		}
		
		
	}
	if(buf[0] == '-')
		return -tmpnum;
	else
		return tmpnum;
}

int count_digit(int n)
{
	int rs =0;
	while(n>0)
	{
		rs++;
		n=n/10;
	}
	return rs;
}*/
int main()
{
	OpenFileId Id,Id2;
	int num_line =0,i=0,j=0;
	int seek_beg = 0,seek_end= 0;
	char buf[100];
	char tmp[100];
	Id = Open("info.txt",0);
	Id2 = Open("input.txt",1);
	Read(buf,10,Id);
	num_line = atoi(buf,10);
	Read(tmp,100,Id2);
	PrintInt(num_line);
	while(i <= num_line)
	{
		if(tmp[seek_end] == '\n')
		{
			if(i < num_line){
			i++;
			seek_beg = seek_end+1;
			}
			else
			i++;
		}
		seek_end++;
	}
	PrintInt(seek_beg);
	PrintInt(seek_end);
	Seek(seek_beg,Id2);
	Read(buf,seek_end-seek_beg,Id2);
	Seek(0,Id);
	Write(buf,seek_end-seek_beg,Id);
	Close(Id);
	Close(Id2);
	Exit(0);
}
