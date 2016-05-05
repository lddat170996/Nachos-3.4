#include "syscall.h"
#include "copyright.h"


int stoi(char buf[],int length,int numArr[])
{
	int i=0,j=0;
	int tmpnum =0;
	for(i;i<length;i++)
	{
		if(buf[i] >= '0' && buf[i] <='9')
		{
			tmpnum = tmpnum*10 + (buf[i]&0XF);
		}
		if(buf[i] == ' ' || buf[i] == '\0')
		{
			if(tmpnum > 0)
			{numArr[j] = tmpnum;
			j++;
			tmpnum = 0;
			}
			
		}
	}
	return j;
}

int atoi(char buf[],int length)
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
void itoa(int n,char *buf)
{

	char tmp[10];
	int i =0,j=0,mod =0;
	if(n == 0)
	{
		buf[0] = '0';
		buf[1] = '\0';
		return;
	}
	while(n>0)
	{
		mod = n%10;
		tmp[i] = mod + 48;
		n = n/10;
		i++;
	}
	i--;
	while(i >=0)
	{
		buf[j]= tmp[i];
		j++;
		i--;
	}
	buf[j] = '\0';
	return;
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
}

