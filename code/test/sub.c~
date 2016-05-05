#include "syscall.h"
#include "copyright.h"
#include "hamphu.h"
int main()
{
	/*int a,b,c;
	PrintString("Nhap so a:");
	a = ReadInt();
	PrintString("Nhap so b:");
	b = ReadInt();
	if(a != -9999999 && b != -9999999)
	{
	//-9999999 means this is not an int number, see SC "ReadInt for more details"
		c = Sub(a,b);
		PrintString("a - b = ");
		PrintInt(c);
	} 
	Halt();
	return 0;
	*/
	
// MSSV: 0712204 - 0712209 - 0712210 - 0712211
// Chuong trinh ung dung cac System call SC_Create, SC_Read, SC_Write, SC_Open, SC_Close:

 
  OpenFileId Id,Id2;
  int bytenum,i = 0,length = 0,n=0;
  char buf[100];
	char tmp[100];
	int numArr[100];
	char* kq;
  Id = Open("input.txt",1); // Mo file ch
Id2 = Open("output.txt",0);
bytenum = Read(buf,100,Id);
buf[bytenum] = '\0';
stoi(buf,bytenum,numArr);
while(numArr[i] != '\0')
{
	PrintInt(numArr[i]);
	PrintString(' ');
	i++;
}

Close(Id2);
	Halt();
	return 0;

}
