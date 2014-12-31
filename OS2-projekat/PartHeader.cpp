#include"PartHeader.h"
#include <iostream>
#include<cstring>
#include<cstdlib>
#include<fstream>
using namespace std;

PartHeader::PartHeader(char sl, int brUl,int NN,Partition* p)
{
	
	PartHeader::part = p;
	PartHeader::brojROOTulaza = 0;
	PartHeader::slovo = sl;
	PartHeader::brFAT32ulaza = brUl;
	PartHeader::slobodni = NN;
	PartHeader::sadrKor = NN;
	PartHeader::N = NN;
	if (part->getNumOfClusters() > MAX)brojKlastera = MAX;
	else brojKlastera = part->getNumOfClusters();

	PartHeader::ROOTbrK = N - 1;
	PartHeader::ROOTindeks = (4 * part->getNumOfClusters() + 16) % 2048;

	PartHeader::initFAT();
	PartHeader::initRootEntry();
	PartHeader::initClusters();
	PartHeader::procitajSveKlastereSaDiska();
	
	
}

PartHeader::~PartHeader(){
	delete[] FAT;
	
		for (int i = 0; i < brojKlastera; i++)delete clusters[i];
		delete[] clusters;

}

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

void PartHeader::pisiHeader()
{
	
	ofstream izlaz;
	int k = -4;
	izlaz.open("C:\\Users\\MyAsus\\Desktop\\OS2-izlaz\\izlaz.txt");
	izlaz <<"Header particije: "<< slovo << endl;
	for (int i = 0; i <N; i++)
		for (int j = 0; j < 2048; j = j + 4){
		int br;
		memcpy(&br, &clusters[i][j], 4);
		izlaz <<k++<<": "<< br << endl;
		}

	char n[8];
	char e[3];
	int pr,br;
	memcpy(&n, &clusters[ROOTbrK][ROOTindeks], 8);
	memcpy(&e, &clusters[ROOTbrK][ROOTindeks+8], 3);
	memcpy(&pr, &clusters[ROOTbrK][ROOTindeks+12], 4);
	memcpy(&br, &clusters[ROOTbrK][ROOTindeks+16], 4);
	izlaz << ((ROOTbrK) * 2048 + ROOTindeks)/4-4 << ": " << n << endl;
	izlaz << e << endl;
	izlaz << pr << endl;
	izlaz << br << endl;
	izlaz.close();
	
}

void PartHeader::initClusters()//pravi niz klastera velicine do MAX(50 000) koji se kesiraju
{

		clusters = new char*[brojKlastera];
		for (int i = 0; i < brojKlastera; i++)clusters[i] = new char[2048];
	
}

void PartHeader::procitajSveKlastereSaDiska()
{
	for (int i = 0; i < brojKlastera; i++)
	{
		part->readCluster(i, clusters[i]);
	}
}

void PartHeader::upisiSveKlastereNaDisk()
{
	for (int i = 0; i < brojKlastera; i++)
	{
		part->writeCluster(i, clusters[i]);
	}
}

void PartHeader::procitajKlastere(int min, int max)
{
	for (int i = min; i <= max; i++)
		part->readCluster(i, clusters[i]);
}

void PartHeader::upisiKlastere(int min, int max)
{
	for (int i = min; i <= max; i++)
		part->writeCluster(i, clusters[i]);
}

void PartHeader::upisiHeaderNaDisk()
{
	int k = 0;
	for (int i = 0; i < N && k<brFAT32ulaza; i++)
		for (int j = 0; j < 2048 && k<brFAT32ulaza; j=j+4)
		{
		if (i == 0 && j == 0){ memcpy(&clusters[0][0], &slobodni, 4); }
		if (i == 0 && j == 4)memcpy(&clusters[0][4], &brFAT32ulaza, 4);
		if (i == 0 && j == 8)memcpy(&clusters[0][8], &sadrKor, 4);
		if (i == 0 && j == 12)memcpy(&clusters[0][12], &brojROOTulaza, 4);
	
		if (i != 0 || (j != 0 && j != 4 && j != 8 && j != 12)){
			memcpy(&clusters[i][j], &FAT[k], 4);
			k++;

	
		}
		}
	PartHeader::upisiROOTEntryUclusters();

	upisiKlastere(0, N-1);

}

void PartHeader::upisiROOTEntryUclusters()
{
	memcpy(&clusters[ROOTbrK][ROOTindeks], &root, 20);
}