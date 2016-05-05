#ifndef FILETABLE_H
#define FILETABLE_H

#include "bitmap.h"
#define  COUT 2
#define  CIN  3
#define  MAX  10
#define  WRFILE 0
#define  ROFILE 1

struct FileEntry{
	int type; //console hay file
	OpenFile *of;
};

class Filetable{
private:
	int usrsize;
	BitMap *bmap;
	FileEntry fTable[MAX];
public:
	Filetable(int size);
	~Filetable();

	int   fdWrite(int reg4,int reg5,int reg6);
	int   fdRead(int reg4,int reg5,int reg6);
	int   fdOpen(int reg4,int reg5,int reg6,OpenFile *of);
	int   fdClose(int reg4);
	int   fdSeek(int reg4,int reg5);
	int   GetMax();
	int   FindFreeSlot();
	bool  IsExist(int id);
	
};
#endif
