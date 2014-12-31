#ifndef _PartHeader_h_
#define _PartHeader_h_

#include"fs.h"
#include "KernelFS.h"
#include "part.h"

const unsigned int MAX=50000;

class PartHeader
{
	public:

	char slovo;//slovo particije
	Entry root;
	int ROOTbrK, ROOTindeks;

	int slobodni;//broj ulaza prvog slobodnog klastera
	int sadrKor;//broj ulaza klastera u kojem je sadrzaj ROOT-a
	int brojROOTulaza;//broj Entry-a u Korenom direktorijumu
	int brFAT32ulaza;//broj ulaza u FAT

	int N;//broj klastera za pocetne bajtove, FAT i ROOT

	int* FAT; //FAT tabela za datu particiju

	int brojKlastera;
	char** clusters;
	Partition* part;

	PartHeader(char sl, int brUl,int NN,Partition* p);
	~PartHeader();
	void initFAT();
	void initRootEntry();//ROOT Entry pocetni sadrzaj
	void pisiHeader();
	void initClusters();
	void procitajSveKlastereSaDiska();
	void upisiSveKlastereNaDisk();

	void procitajKlastere(int min, int max);//min-donja granica,a max-gornja granica
	void upisiKlastere(int min, int max);
	void upisiHeaderNaDisk();
	void upisiROOTEntryUclusters();

};

#endif