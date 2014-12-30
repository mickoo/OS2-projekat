#include "KernelFS.h"
#include "part.h"
#include"PartHeader.h"
#include"PartHeaderList.h"
#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;

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
	PartHeader* header;
	int N;
	int indeks = -1;

	for (int i = 0; i < 26; i++)//trazim particiju sa zadatim slovom
		if (KernelFS::slova[i] == part){ indeks = i; break; }
	
	if (indeks < 0 || KernelFS::particije[indeks] == NULL) return '0';//proveravam da li je nadjena i da li postoji
	
	p = KernelFS::particije[indeks];//dohvatam particiju
	N = KernelFS::getN(p);//N je broj klastera za FAT32 i ROOT
	
	header = new PartHeader(KernelFS::slova[indeks],p->getNumOfClusters(),N,p);
	header->pisiFAT();
	PartHeaderList::add(header);

	
	
	
	
	return '1';
	
}

int KernelFS::getN(Partition* p)
{

	int velK = 2048;
	int n = 20 + 12 + 4 * p->getNumOfClusters();
	double rez =( n / velK);
	if (n%velK == 0)return rez;
	else return rez + 1;

}