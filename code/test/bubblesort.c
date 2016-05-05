#include "syscall.h"
#include "copyright.h"
int main()
{
	int n, i, j, tmp;
	int option;
	int arr[200];
	PrintString("Nhap so phan tu cua mang (<100):");
	n = ReadInt();
	
	for (i = 0; i < n; i++) {
		PrintString("a[i] = ");
		arr[i] = ReadInt();
	} 
	
	do{
	PrintString("  Sap xep tang dan (1)\n  sap xep giam dan (2)\n Lua chon: ");
	option = ReadInt();
	}while(option < 1 || option > 2);
	
	for (i = 0; i < n-1; i++) {
		for (j = i+1; j < n; j++) {
			if (option == 1 && arr[j] < arr[i] || option == 2 && arr[i] < arr[j])
			{
				tmp = arr[j];
				arr[j] = arr[i];
				arr[i] = tmp;
			}
		}
	}
	PrintString("Sau khi sap xep \n");
	for (i = 0; i < n; i++) {
		PrintInt(arr[i]);
		PrintString(' ');
	}
	return 0;
}
