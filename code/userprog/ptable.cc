// ptable.cpp: implementation of the ptable class.
//
//////////////////////////////////////////////////////////////////////

#include "ptable.h"
#include "system.h"

PTable::PTable(int size)
{
	int i = 0;
	this->psize = size;
	this->bm = new BitMap(size);
	this->bmsem = new Semaphore("bmsem",1);
		
	for(i = 0 ; i < MAX_PROCESS ; ++i)
		pcb[i] = NULL;
	bm->Mark(0);
	pcb[0] = new PCB(0);
	pcb[0]->SetFileName("./test/shell");
	pcb[0]->parentID = -1;
}

PTable::~PTable()
{
	int i = 0;
	if( bm != NULL )
		delete []bm;
	for( ; i < psize ; ++i)
		if(pcb[i] != NULL)
			delete pcb[i];
	if( bmsem != NULL)
		delete bmsem;
}

//////////////////////////////////////////////////////////////////////////

int PTable::ExecUpdate(char* name)
{
	bmsem->P();
	
	//kiem tra chuong trinh duoc goi co ton tai trong may ko?
	if(name == NULL)
	{
		printf("\nPTable::Exec : Can't not exec Name is NULL");
		bmsem->V();
		return -1;
	}

	//kiem tra chuong trinh duoc goi la chinh no hay ko ?
	if( strcmp(name,"./test/shell") == 0 )
	{
		printf("\nPTable::Exec : Can't not exec itself");		
		bmsem->V();
		return -1;
	}

	if( strcmp(name,currentThread->getName()) == 0 )
	{
		printf("\nPTable::Exec : Can't not exec itself");		
		bmsem->V();
		return -1;
	}
		
	//kiem tra con slot trong ko?
	int ID = this->GetFreeSlot();
	if(ID < 0)
	{
		printf("\nPTable::Exec : Khong con khe ID rong\n");
		bmsem->V();
		return -1;//ko con khe trong
	}

	pcb[ID] = new PCB(ID);
	pcb[ID]->SetFileName(name);
//*************************************
	int pid = pcb[ID]->Exec(name,ID);
	bmsem->V();

	return pid;
}

/*
----------------------------------------------------------
input : id : id cua tien trinh con
ouput : tra ve exitcode
		=  0 : success
		!= 0 : error
----------------------------------------------------------
*/
int PTable::JoinUpdate(int id)
{
	if(id < 0)
	{
		printf("\nPTable::JoinUpdate : id = %d",id);
		return -1;
	}

	//kiem tra tien trinh dang chay la cha cua thang can join hay ko
	if(currentThread->processID != pcb[id]->parentID)
	{
		printf("\nPTable::JoinUpdate : Ko duoc phep join vao tien trinh khong phai cha cua no");
		return -1;
	}
	//id cua thang con dang chay
	pcb[pcb[id]->parentID]->IncNumWait();
	pcb[id]->boolBG = 1;
	

	pcb[id]->JoinWait(); //doi den khi tien trinh con ket thuc
	//printf("\nJoinUpdate::I come back\n");
	//o day phai dam bao thang con exit truoc
	//.....nhan ma exitcode de xu ly can thiet roi??????????????????
	int ec = pcb[id]->GetExitCode();


	pcb[id]->ExitRelease();//de cho phep tien trinh con ket thuc

	return ec;//success

}

/*
----------------------------------------------------------
input : ec : exitcode = 0 : success / != 0 : error
ouput : tra ve exitcode 
----------------------------------------------------------
*/
int PTable::ExitUpdate(int ec)
{

	//id cua thang con dang chay?
	int id = currentThread->processID;
	if(id == 0)
	{
		interrupt->Halt();
		return 0;
	}
	
	//kiem tra co chay background hay ko ?
	if(pcb[id]->boolBG == 0)
	{
		Remove(id);
		return 0;
	}

	//kiem tra id co ton tai ko
	if(IsExist(id) == false)
	{
		printf("\nPTable::ExitUpdate : ID %d khong ton tai ",id);
		return -1;
	}
	
	pcb[id]->SetExitCode(ec);
	pcb[pcb[id]->parentID]->DecNumWait();

//	printf("\n--2 JoinRelease");
	pcb[id]->JoinRelease();
//	printf("\n--3 ExitWait");
	pcb[id]->ExitWait();

	Remove(id);
	return ec;
}

//tim free slot de luu thong tin cho tien trinh moi
int PTable::GetFreeSlot()
{
	return bm->Find();
}

//kiem tra ton tai Process ID nay ko
bool PTable::IsExist(int pid)
{
	return bm->Test(pid);
		
}

//xoa 1 proccess ID ra khoi mang quan ly cua no, khi ma tien trinh nay ket thuc
void PTable::Remove(int pid)
{
	bm->Clear(pid);
	if(pcb[pid] != NULL)
		delete pcb[pid];
}

///////////////////////////////////////////////////////////////////
char* PTable::GetFileName(int id)
{
	return (pcb[id]->GetFileName());
}
