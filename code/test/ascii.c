#include "syscall.h"
#include "copyright.h"
int main()
{
	char i = 33; // ascii chi hien thi duoc tu 33 > 127
	for (; i < 127; i++)
	{
		PrintInt(i);
		PrintString(" -> ");
		PrintChar(i);
		PrintChar('\n');
	}
	return 0;
}
