#include "filetable.h"

extern char* User2System(int virtAddr, int limit);
extern int System2User(int virtAddr, int len, char* buffer);
Filetable:: Filetable(int size)
{
	bmap = NULL;
	bmap = new BitMap(size);
	usrsize = size;
	
	
	//ftable[0] = cin ,ftable[1] = cout
	
	fTable[0].type = CIN;  //danh dau file table 0 la CIN |1 la COUT
	fTable[1].type = COUT;
 	for (int i =0 ; i < size; i++)
    	{
      		fTable[i].of = NULL;
    	}	
	bmap->Mark(0); // bmap->Mark la danh dau file da open
	bmap->Mark(1);
	
};
	Filetable::~Filetable()
	{
		for(int i =0;i<usrsize;i++)
		{
			if(bmap->Test(i) == true)
			{	
				delete fTable[i].of;
				fTable[i].of = NULL;
			}
			
		}
		delete bmap;
		usrsize = 0;
		
	};
	int   Filetable::fdWrite(int reg4,int reg5,int reg6)
	{
		int kq;
		int virtAddr = reg4;
		int size = reg5;
		int id = reg6;
		if (size < 0){
		printf("\n size can not be lower than zero ");
		return -1;
		}
		if(size == 0)
			return 0;
		char *buf = User2System(virtAddr,size);
		if(buf == NULL)
		{
			printf("\n cant convert user 2 system");
			return -1;
		}
		switch(fTable[id].type)
		{
			case COUT:
			{
				kq = gSynchConsole->Write(buf,strlen(buf));
				if(kq < 0)
					printf("\n FDCOUT WRITE FAILS ");
				break;
			}
			case WRFILE:
			{
				int kq = fTable[id].of->Write(buf,strlen(buf));
				if(kq < 0)
					printf("\n RWFILE WRITE FAILS ");
				break;
			}
			default:
			{
				printf("\n CIN or ROFILE cant write");
				return -1;
			}
		}
		
		delete buf;
		return kq;
			
		
	};
	int   Filetable::fdRead(int reg4,int reg5,int reg6)
	{
		int kq = 0;
		int virtAddr = reg4;
		int size = reg5;
		int id = reg6;
		char *buf = new char[size +1];
		
		switch(fTable[id].type)
		{
			case CIN:
			{
				int tmp = gSynchConsole->Read(buf,size);
				kq = System2User(virtAddr,tmp,buf);
				if(tmp < 0)
				{
					printf("\n gSynchConsole->read fail ");
					delete buf;
					return -1;
				}
				break;
			}
			case COUT:
			{
				 printf("\n COUT CANT READ");
				return -1;// can't read
			}
			break;
			default: //rwfile && rfile
			{
				int tmp = fTable[id].of->Read(buf,size);
				if(tmp < 0)
				{
					printf("\n file->read fail ");
					delete buf;
					return -1;
				}
				if(tmp == 0)
				{
					delete buf;
					return -1;
				}
				kq = System2User(virtAddr,tmp,buf);
				delete buf;
				return kq;
	
			}
		}
			
	};
	int   Filetable::fdOpen(int reg4,int reg5,int reg6,OpenFile *of)
	{
		int virtAddr = reg4;
		int type = reg5;
		int id = reg6;
		bmap->Mark(id);
		switch(type)
		{
			case WRFILE:
			{
				fTable[id].type = WRFILE;
				fTable[id].of = of;
				
				break;
			}
			case ROFILE:
			{
				fTable[id].type = ROFILE;
				fTable[id].of = of;
				
				break;
			}
		}
		return id;
		
	};
	int   Filetable::fdClose(int reg4)
	{
		int id = reg4;
		int kq;
		switch(fTable[id].type)
		{
			case WRFILE:
			{
				fTable[id].of = NULL;
				kq = 0;
			}
			break;
			case ROFILE:
			{
				fTable[id].of = NULL;
				kq = 0;
			}
			break;
			default:
			kq = -1;
		}
		if (id >= 2 && id < usrsize)
			bmap->Clear(id);
		return kq;
	};
	int   Filetable::GetMax()
	{
		return usrsize;
	};
	int   Filetable::FindFreeSlot()
	{
		return bmap->Find();
	};
	bool  Filetable::IsExist(int id)
	{
		return bmap->Test(id);
	};
	int  Filetable::fdSeek(int reg4,int reg5)
	{
	  int id = reg5;
	  int offset = reg4;
	  int pos =0;
	  if(fTable[id].type == WRFILE || fTable[id].type == ROFILE)
	  {
		   if (offset < -1 || offset >= fTable[id].of->Length() )
		   {
			printf("\n offset type error, check again ");
		   return -1;
		   }
			pos = fTable[id].of->Seek(offset);
	  }

	  machine->WriteRegister(2,pos);

	  return pos;
	}
	
