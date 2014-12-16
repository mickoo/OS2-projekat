#ifndef _Kernel_FS_
#define _Kernel_FS_

#include "part.h"

class KernelFS{
	
public:

	static char slova[26];
	static Partition *particije[26];
	static int pop;


	static char mount(Partition* p);

};




#endif