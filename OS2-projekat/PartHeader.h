#ifndef _PartHeader_h_
#define _PartHeader_h_

#include"fs.h"
#include "KernelFS.h"


class PartHeader
{
	public:

	char slovo;//slovo particije
	Entry root;

	int slobodni;//broj ulaza prvog slobodnog klastera
	int sadrKor;//broj ulaza klastera u kojem je sadrzaj ROOT-a
	int brFAT32ulaza;//broj ulaza u FAT

	int N;//broj klastera za pocetne bajtove, FAT i ROOT

	int* FAT; //FAT tabela za datu particiju

	PartHeader(char sl, int brUl,int NN);
	~PartHeader();
	void initFAT();
	void initRootEntry();//ROOT Entry pocetni sadrzaj
	void pisiFAT();

};

#endif