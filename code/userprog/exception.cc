// exception.cc 
//	Entry point into the Nachos kernel from user programs.
//	There are two kinds of things that can cause control to
//	transfer back to here from user code:
//
//	syscall -- The user code explicitly requests to call a procedure
//	in the Nachos kernel.  Right now, the only function we support is
//	"Halt".
//
//	exceptions -- The user code does something that the CPU can't handle.
//	For instance, accessing memory that doesn't exist, arithmetic errors,
//	etc.  
//
//	Interrupts (which can also cause control to transfer from user
//	code into the Nachos kernel) are handled elsewhere.
//
// For now, this only handles the Halt() system call.
// Everything else core dumps.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"
#include "syscall.h"
#include "stable.h"
#include "ptable.h"

//----------------------------------------------------------------------
// ExceptionHandler
// 	Entry point into the Nachos kernel.  Called when a user program
//	is executing, and either does a syscall, or generates an addressing
//	or arithmetic exception.
//
// 	For system calls, the following is the calling convention:
//
// 	system call code -- r2
//		arg1 -- r4
//		arg2 -- r5
//		arg3 -- r6
//		arg4 -- r7
//
//	The result of the system call, if any, must be put back into r2. 
//
// And don't forget to increment the pc before returning. (Or else you'll
// loop making the same system call forever!
//
//	"which" is the kind of exception.  The list of possible exceptions 
//	are in machine.h.
//----------------------------------------------------------------------

//
char* User2System(int virtAddr, int limit)
{
	int i;// index
	int oneChar;
	char* kernelBuf = NULL;
	kernelBuf = new char[limit + 1];//need for terminal string
	if (kernelBuf == NULL)
		return kernelBuf;
	memset(kernelBuf, 0, limit + 1);
	//printf("\n Filename u2s:");
	for (i = 0; i < limit; i++)
	{
		machine->ReadMem(virtAddr + i, 1, &oneChar);
		kernelBuf[i] = (char)oneChar;
		//printf("%c",kernelBuf[i]);
		if (oneChar == 0)
			break;
	}
	return kernelBuf;
}
/*
Input: - User space address (int)
- Limit of buffer (int)
- Buffer (char[])
Output:- Number of bytes copied (int)
Purpose: Copy buffer from System memory space to User memory space
*/
int System2User(int virtAddr, int len, char* buffer)
{
	if (len < 0) return -1;
	if (len == 0)return len;
	int i = 0;
	int oneChar = 0;
	do{
		oneChar = (int)buffer[i];
		machine->WriteMem(virtAddr + i, 1, oneChar);
		i++;
	} while (i < len && oneChar != 0);
	return i;
}



void
ExceptionHandler(ExceptionType which)
{
	int type = machine->ReadRegister(2);

	switch (which){

	case NoException:
		return;

	case SyscallException:
		switch (type){

		case SC_Halt:
			DEBUG('a', "\n Shutdown, initiated by user program.");
			printf("\n\n test, initiated by user program");
			interrupt->Halt();
			break;
		case SC_Sub:
		{
					   int op1 = machine->ReadRegister(4);
					   int op2 = machine->ReadRegister(5);
					   int result = op1 - op2;
					   machine->WriteRegister(2, result);
					   break;
		}

		case SC_Create:
		{
						  int virtAddr;
						  char* filename;

						  DEBUG('a', "\n SC_Create call ...");
						  DEBUG('a', "\n Reading virtual address of filename");
						  // check for exception
						  virtAddr = machine->ReadRegister(4);
						  DEBUG('a', "\n Reading filename.");
						  filename = User2System(virtAddr, 32 + 1); // MaxFileLength là = 32
						  if (filename == NULL)
						  {
							  printf("\n Not enough memory in system");
							  DEBUG('a', "\n Not enough memory in system");
							  machine->WriteRegister(2, -1); // trả về lỗi cho chương trình người dùng
							  delete filename;
							 
						  }
						  DEBUG('a', "\n Finish reading filename.");
						  //DEBUG(dbgFile,"\n File name : '"<<filename<<"'");
						  // Create file with size = 0
						  // Dùng đối tượng fileSystem của lớp OpenFile để tạo file, việc tạo file này là sử dụng các
						  // thủ tục tạo file của hệ điều hành Linux, chúng ta không quản ly trực tiếp các block trên
						  // đĩa cứng cấp phát cho file, việc quản ly các block của file trên ổ đĩa là một đồ án khác
						  if (!fileSystem->Create(filename, 0))
						  {
							  printf("\n Error create file '%s'", filename);
							  machine->WriteRegister(2, -1);
							  delete filename;
							  
						  }
						  machine->WriteRegister(2, 0); // trả về cho chương trình người dùng thành công
						  delete filename;
						  break;
		}
		case SC_PrintInt:
		{
							int val = machine->ReadRegister(4);
							char s[MAX_INT_LENGTH], result[MAX_INT_LENGTH];
							int tmpDigit;
							int i = 0, size, j = 0;
							if (val < 0)
							{
								result[0] = '-';
								j++;
								val = -val;
							}
							while (val > 0)
							{
								tmpDigit = val % 10;
								s[i] = tmpDigit + '0'; // ép kiểu
								i++;
								val = val / 10;
							}
							size = i;
							//đảo lại số cho đúng
							while (i > 0)
							{
								result[j] = s[i - 1];
								i--;
								j++;
							}
							result[j] = '\0';
							gSynchConsole->Write(result, size + 1);
							break;
		}
		case SC_ReadInt:
		{
						   unsigned int number = 0; // su dụng int để có thể kiểm tra xem input có > INT_MAX hay không
						   int n = 0;
						   int i = 0;
						   char* bufer = new char[1000000]; // bufer chỉ nhận 1000000 kí tự 
						   n = gSynchConsole->Read(bufer, 1000000);
						   if (bufer[0] == '-')
						   {
							   i++; //nếu kí tự đầu là - thì tăng biến đếm
						   }
						   while (bufer[i] == '0') // nếu số đầu =0 thì tăng biến đếm lên
						   {
							   i++;
						   }
						   if (n == 1000000 || n - i > MAX_INT_LENGTH)
						   {
							   printf("\n Your input are too long,auto change to 0 ");
							   DEBUG('a', "\n Your input are too long ");
							   machine->WriteRegister(2, 0); // trả về lỗi cho chương trình người dùng
							   return;
						   }
						   if (bufer[i] < '0' || bufer[i] > '9')
						   {
							   printf("\n There is not an integer number , auto change to -9999999");
							   DEBUG('a', "\n there is not an integer number,auto change to -9999999");
							   machine->WriteRegister(2, -9999999); // trả về lỗi cho chương trình người dùng
							   return;
						   }
						   for (; i < n; i++)
						   {
							   number = number * 10 + int(bufer[i] & 0XF); // OXF để lọc ra 1 byte => 1 chữ số
						   }
						   if (bufer[0] != '-' && number >= INT_MAX || bufer[0] == '-' && number >= INT_MAX + 1)
						   {
							   printf("\n Your input is out of the integer range, auto change to 0 ");
							   DEBUG('a', "\n Your input is out of the integer range, auto change to 0 ");
							   machine->WriteRegister(2, 0); // trả về lỗi cho chương trình người dùng
							   return;
						   }
						   if (bufer[0] == '-')
							   number = -number;


						   machine->WriteRegister(2, int(number));
						   delete[]bufer;
		}
			break;
		case SC_PrintString:
		{
							   int bufAddr = machine->ReadRegister(4);
							   int i = 0;
							   char *buf = new char[LIMIT];
							   buf = User2System(bufAddr, LIMIT);
							   gSynchConsole->Write(buf, LIMIT);
							   delete[] buf;
		}
			break;
		case SC_ReadString:
		{
							  char *buf = new char[LIMIT];
							  if (buf == 0) break;
							  int bufAddrUser = machine->ReadRegister(4);
							  int length = machine->ReadRegister(5);
							  int n = gSynchConsole->Read(buf, length);
							  System2User(bufAddrUser, n, buf);
							  delete[] buf;
		}
			break;
		case SC_Exec:
		{
						int addr = machine->ReadRegister(4);
						char* name = User2System(addr, MaxFileLength + 1);
						OpenFile *ob = fileSystem->Open(name);
						if (ob == NULL)
						{
							printf("\nKhong mo duoc file");
							machine->WriteRegister(2, -1);
							return;
						}
						delete ob;
						//pTab la l the hien cua lop PTable
						//tra ve id cua tien trinh con
						int id = pTab->ExecUpdate(name);

						machine->WriteRegister(2, id);

		}
			break;
		case SC_Join:
		{
						
						int id = machine->ReadRegister(4);
						int kq = pTab->JoinUpdate(id);
						machine->WriteRegister(2, kq);
						
		}
			break;
		case SC_Exit:
		{
						DEBUG('a', "\n\n Calling SC_Exit.");

						int exitStatus = machine->ReadRegister(4);
						int pid = currentThread->processID; //pid la cua tien trinh can thoat

						// if process exited with error, print error
						if (exitStatus != 0)
							printf("\nProcess %s exited with error level %d", currentThread->getName(), exitStatus);

						pTab->ExitUpdate(exitStatus);

						currentThread->FreeSpace(); // tra lai vung free space cho he thong
						currentThread->Finish();
		}
			break;
		case SC_CreateSemaphore:
		{
						int addr = machine->ReadRegister(4);
						int semval = machine->ReadRegister(5);
						char *name = User2System(addr, 32);
						if (name == NULL)
						{
							printf("\n Name == NUll");
							machine->WriteRegister(2, -1);
							return;
						}
						int kq = semTab->Create(name, semval);
						if (kq < 0)
						{
							printf("\nSC_CreateSemaphore :: Can't create semaphore : %s", name);
							machine->WriteRegister(2, -1);
							return;
						}
						machine->WriteRegister(2, 0);
		}
			break;
		case SC_Up:
		{
					  int addr = machine->ReadRegister(4);
					  char *name = User2System(addr, 32);
					  if (name == NULL)
					  {
						  printf("\nname = NULL");
						  machine->WriteRegister(2, -1);
						  return;
					  }
					  int kq = semTab->Signal(name);
					  if (kq < 0)
					  {
						  printf("\nCan't signal semaphore : %s", name);
						  machine->WriteRegister(2, -1);
						  return;
					  }
					  machine->WriteRegister(2, 0);
		}
			break;
		case SC_Down:
		{
						int addr = machine->ReadRegister(4);
						char *name = User2System(addr, 32);
						if (name == NULL)
						{
							printf("\nSC_Wait :: name = NULL");
							machine->WriteRegister(2, -1);
							return;
						}
						int kq = semTab->Wait(name);
						if (kq < 0)
						{
							printf("\nSC_Wait :: Can't wait semaphore : %s", name);
							machine->WriteRegister(2, -1);
							return;
						}
						machine->WriteRegister(2, 0);
		}
			break;
		case SC_Open:
		{
					  //  printf("\n Calling SC_Open.");
		  int virtAddr = machine->ReadRegister(4);
		  int type = machine->ReadRegister(5);

		  if (type < 0 || type > 2)
			{
			  printf("\n SC_OpenError: unexpected file type: %d",type);
			  machine->WriteRegister(2, -1);
			  break;
			}
		  
		  int id = currentThread->fTab->FindFreeSlot(); //tim id file trong
		  if (id < 0) // het vung id trong
			{
			  printf("\n SC_OpenError: No free slot.");
			  machine->WriteRegister(2, -1);
			  break;
			}

		  char *filename = User2System(virtAddr,MaxFileLength+1);

		  if (filename == NULL)
			{
			  printf("\n Not enough memory in system");
			  DEBUG('a',"\n Not enough memory in system");
			  machine->WriteRegister(2,-1);
			  delete filename;
			  break;
			}

		  if (strlen(filename) == 0 || (strlen(filename) >= MaxFileLength+1))
			{
			  printf("\n Too many characters in filename: %s",filename);
			  DEBUG('a',"\n Too many characters in filename");
			  machine->WriteRegister(2,-1);
			  delete filename;
			 
			  break;
			}

		  OpenFile* of = fileSystem->Open(filename);

		  if (of == NULL){
			printf("\n Error opening file:  %s",filename);
			DEBUG('a',"\n Error opening file.");
			machine->WriteRegister(2,-1);
			delete filename;
			
			  break;
		  }

		  int rs = currentThread->fTab->fdOpen(virtAddr,type,id,of);
		  
		  machine->WriteRegister(2,rs);

		  break;
		}
		break;
		case SC_Write:
		{
						//  printf("\n Calling SC_Write.");
			  int virtAddr = machine->ReadRegister(4);
			  int size = machine->ReadRegister(5);
			  int id = machine->ReadRegister(6);
			char* name = User2System(virtAddr,size);

			  if (size < 0)
				{
				  printf("\nSC_WriteError: unexpected buffer size: %d",size);
				  machine->WriteRegister(2, -1);
			  break;
				}
			  else if (size == 0)
			  {machine->WriteRegister(2, 0);
			  break;
			  }

			  if (id < 0 || id >= currentThread->fTab->GetMax())
				{
				  printf("\n WriteError: Unexpected file id: %d",id);
				  machine->WriteRegister(2, -1);
				break;
				}
			  if (!currentThread->fTab->IsExist(id)){
				printf("\n WriteError: writing file id %d is not opened",id);
				machine->WriteRegister(2, -1);
			  break;
			  }

			  int rs = currentThread->fTab->fdWrite(virtAddr,size,id);
			  
			  machine->WriteRegister(2,rs);

			  break;
		}
		break;
		case SC_Read:
		{
					//  printf("\n Calling SC_Read.");
		  int virtAddr = machine->ReadRegister(4);

		  int size = machine->ReadRegister(5);
		  int id = machine->ReadRegister(6);
		char* name = User2System(virtAddr,size);
		  
		  if (size <= 0)
			{
			  printf("\nSC_ReadError: unexpected buffer size: %d",size);
			  machine->WriteRegister(2, -1);
			  break;
			}

		  if (id < 0 || id >= currentThread->fTab->GetMax())
			{
			  printf("\n ReadError: Unexpected file id: %d",id);
			  machine->WriteRegister(2, -1);
			  break;
			}
		  if (!currentThread->fTab->IsExist(id)){
			printf("\n ReadError: reading file id %d is not opened",id);
			machine->WriteRegister(2, -1);
			  break;
		  }

		  int rs = currentThread->fTab->fdRead(virtAddr,size,id);
		  
		  machine->WriteRegister(2,rs);

		  break;
		}
		break;
		case SC_Close:
		{
					 int id = machine->ReadRegister(4);
		  if (id < 0 || id >= currentThread->fTab->GetMax())
			{
			  printf("\n CloseError: Unexpected file id: %d",id);
			  machine->WriteRegister(2, -1);
			  break;
			}
		  if (!currentThread->fTab->IsExist(id)){
			printf("\n CloseError: closing file id %d is not opened",id);
			machine->WriteRegister(2, -1);
			  break;
		  }

		  //currentThread->
		  currentThread->fTab->fdClose(id);
		  machine->WriteRegister(2, 0);
			  break;
		}
		case SC_Seek:
		{
			int id = machine->ReadRegister(5);
		  if (id < 0 || id >= currentThread->fTab->GetMax())
			{
			  printf("id not found \n");
			    machine->WriteRegister(2, -1);
			  return ;
			}
		  if (!currentThread->fTab->IsExist(id)){
			printf("\n File is not opening ");
			  machine->WriteRegister(2, -1);
			return ;
		  }

		  int offset = machine->ReadRegister(4);
		  currentThread->fTab->fdSeek(offset,id);
		    machine->WriteRegister(2, 0);
		}
		
		}
		machine->registers[PrevPCReg] = machine->registers[PCReg];	// for debugging, in case we// are jumping into lala-land
		machine->registers[PCReg] = machine->registers[NextPCReg];
		machine->registers[NextPCReg] += 4;
		break;

	}
}
