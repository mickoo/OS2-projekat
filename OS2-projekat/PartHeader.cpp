#include"PartHeader.h"
#include <iostream>
using namespace std;

PartHeader::PartHeader(char sl, int brUl,int NN)
{
	PartHeader::slovo = sl;
	PartHeader::brFAT32ulaza = brUl;
	PartHeader::slobodni = NN;
	PartHeader::sadrKor = NN;
	PartHeader::N = NN;

	PartHeader::initFAT();
	PartHeader::initRootEntry();

}

PartHeader::~PartHeader(){ delete[] FAT; }

void PartHeader::initFAT()
{
	PartHeader::FAT = new int[PartHeader::brFAT32ulaza];
	int init = 1;

	for (int i = 0; i < PartHeader::brFAT32ulaza; i++){
		PartHeader::FAT[i] = init++;//postavljam svaki ulaz da pokazuje na sledeci slobodan (svi su slobodni)
	}

	PartHeader::FAT[PartHeader::brFAT32ulaza - 1] = 0;//poslednji slobodan ulaz ne pokazuje na sledeci slobodan jer ga nema
	PartHeader::FAT[PartHeader::N - 1] = 0;//poslednji klaster koji zauzima FAT ne pokazuje na sledeci zauzeti
}

void PartHeader::initRootEntry(){
	PartHeader::root.name[0] = PartHeader::slovo;
	PartHeader::root.name[1] = ':';
	PartHeader::root.name[2] = 92;//ASCII kod za znak '\'

	PartHeader::root.firstCluster = 0;
	PartHeader::root.size = 0;
	
}

void PartHeader::pisiFAT()
{
	for (int i = 0; i < 50; i++)
		cout <<i<<":"<< PartHeader::FAT[i] << endl;
	cout << "Prvi slobodan ulaz :" << PartHeader::slobodni << endl;
	cout << "Sadrzaj ROOT-a :" << PartHeader::sadrKor << endl;
	cout << "Broj ulaza u FAT :" << PartHeader::brFAT32ulaza << endl;
	cout << PartHeader::root.ext <<endl;
}