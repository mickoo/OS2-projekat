#include <iostream>
#include <cstdlib>
#include <string>

#include "part.h"
#include "KernelFS.h"

using namespace std;


void main()
{
	Partition *p = new Partition("p1.ini");
	KernelFS::mount(p);
	
	cout << KernelFS::getN(p)<<endl;
	
}