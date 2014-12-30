#include <iostream>
#include <cstdlib>
#include <string>

#include "part.h"
#include "KernelFS.h"
#include "PartHeader.h"
#include "PartHeaderList.h"

using namespace std;


void main()
{
	Partition *p = new Partition("p1.ini");
	KernelFS::mount(p);
	KernelFS::format('A');

	PartHeaderList::ispisi();
	
}