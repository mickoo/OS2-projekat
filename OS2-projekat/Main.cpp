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
	Partition *p2 = new Partition("p2.ini");
	KernelFS::mount(p);
	KernelFS::mount(p2);
	KernelFS::format('A');
	KernelFS::format('B');

	PartHeader* r = PartHeaderList::dohvati('B');
	r->pisiHeader();
	
	
}