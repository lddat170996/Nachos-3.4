
#include "syscall.h"



int main()
{
	OpenFileId Id1,Id2;
	int length =0;
	char buf[100],tmp[100];
	int i = 0;
	Id1 = Open("hellocoba.txt",1); // 1 la thuoc tinh read only
	Id2 = Open("haoxiangni.txt",0); // o la thuoc tinh read & write
	length = Read(buf,100,Id1);
	Write(buf,length,Id2);
	Write("xin nhap 1 chuoi bat ki: ",100,ConsoleOutput);
	length = Read(tmp,10,ConsoleInput);
	Write("Chuoi ban vua nhap : ",100,ConsoleOutput);
	Write(tmp,length,ConsoleOutput);
	Write(tmp,length,Id2);
	Write("adu",2,Id2);
	Exit(0);
	
}
