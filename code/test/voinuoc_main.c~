#include "syscall.h"
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
}*/
int main()
{	
	SpaceId a;
	OpenFileId fId,fId2,fId3;
  	int i = 0,n_time = 0;
  	char buffer[100];
	char temp[100];
	int numArr[100];
	fId = Open("input.txt",1); // chi doc
	fId2 = Open("info.txt",0);
	Read(buffer,100,fId);
	n_time = atoi(buffer,10);
	PrintInt(n_time);
	Create("output.txt");
	for(i;i<n_time;i++)
	{
		itoa(i+1,temp);
		Seek(0,fId2);
		Write("                                                                                 ",100,fId2);
		Seek(0,fId2);
		Write(temp,10,fId2);
		a = Exec("./test/sinhvien");
		Join(a);
		a= Exec("./test/voinuoc");
		Join(a);
	}
	Close(fId);
	Close(fId2);
	Close(fId3);
	Exit(0);
}
