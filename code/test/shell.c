#include "syscall.h"
int
main()
{
    /*SpaceId newProc;
    OpenFileId input = ConsoleInput;
    OpenFileId output = ConsoleOutput;
    char prompt[2], ch, buffer[60];
    int i;

    prompt[0] = '-';
    prompt[1] = '-';

    while( 1 )
    {
	Write(prompt, 2, output);

	i = 0;
	
	do {
	
	    Read(&buffer[i], 1, input); 

	} while( buffer[i++] != 'q' );

	buffer[--i] = '\0';

	if( i > 0 ) {
		newProc = Exec(buffer);
		Join(newProc);
	}
	Write("test da chuong de \n",100,output);
    }
*/
SpaceId newProc,Proc2;
 OpenFileId input = ConsoleInput;
    OpenFileId output = ConsoleOutput;
	newProc = Exec("./test/voinuoc_main");
	Join(newProc);
	newProc = Exec("./test/sinhvien");
Join(newProc);
	
	
Exit(0);
}

