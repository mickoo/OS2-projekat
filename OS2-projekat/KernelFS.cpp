#include "KernelFS.h"
#include "part.h"
#include <iostream>
#include <cstdlib>


char KernelFS::slova[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
Partition* KernelFS::particije[]={ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL };
int KernelFS::pop = 0;


char KernelFS::mount(Partition* p)
{
	if (pop == 26)return '0';
	else
	{
		for (int i = 0; i < 26; i++)
		{
			if (particije[i] == NULL){
				particije[i] = p;
				pop++;
				return slova[i];
			}
		}
	}

}

char KernelFS::unmount(char a)
{
	int indeks = -1;
	for (int i = 0; i < 26; i++)
		if (KernelFS::slova[i] == a){ indeks = i; break; }

	if (indeks < 0 || particije[indeks] == NULL)return 0;
	else {
		particije[indeks] = NULL;
		return 1;
	}
}

char KernelFS::format(char part)
{
	Partition *p;
	int N;
	int indeks = -1;

	for (int i = 0; i < 26; i++)
		if (KernelFS::slova[i] == part){ indeks = i; break; }

	if (indeks < 0 || KernelFS::particije[indeks] == NULL) return 0;
	
	p = KernelFS::particije[indeks];
	N = KernelFS::getN(p);

	




	
}

int KernelFS::getN(Partition* p)
{

	int velK = 2048;
	int n = 12 + 4 * p->getNumOfClusters();
	double rez =( n / velK)+1;
	return rez;

}