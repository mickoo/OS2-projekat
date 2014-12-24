#ifndef _Kernel_FS_
#define _Kernel_FS_

#include "part.h"

class KernelFS{
	
public:

	static char slova[26];
	static Partition *particije[26];
	static int pop;
	static char* cluster;
	
	


	static char mount(Partition* p);
	static char unmount(char a);
	static char format(char part);
	static int getN(Partition *p);


};




#endif