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
	
	PartHeader* p1 = new PartHeader('A', p->getNumOfClusters(), KernelFS::getN(p));
	PartHeader* p2 = new PartHeader('B', p->getNumOfClusters(), KernelFS::getN(p));
	PartHeader* p3 = new PartHeader('C', p->getNumOfClusters(), KernelFS::getN(p));
	PartHeaderList::add(p1);
	PartHeaderList::add(p2);
	PartHeaderList::add(p3);
	PartHeaderList::ispisi();
	PartHeaderList::izbaci('B');
	PartHeaderList::ispisi();
	
	
}