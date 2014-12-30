#include"PartHeader.h"
#include <iostream>
#include<cstring>
#include<cstdlib>
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

void PartHeader::pisiFAT()
{
	
	int j;
	for (int i = 0; i < 80; i = i + 4){
		memcpy(&j, &clusters[0][i], 4);
		cout << j << endl;
	}

	cout << "Slobodni= " << slobodni << endl;
	cout << "brFatUlaza= " << brFAT32ulaza << endl;
	cout << "sadrzaj Korena= " << sadrKor << endl;
	cout << "Broj ulaza Korena= " << brojROOTulaza << endl;
	
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

	upisiKlastere(0, N);

}