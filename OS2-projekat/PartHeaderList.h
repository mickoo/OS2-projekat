#ifndef _PartHeaderList_h_
#define _PartHeaderList_h_

#include<iostream>
#include<cstring>
#include<list>
#include"PartHeader.h";
using namespace std;

class PartHeaderList
{
public: 
	static list<PartHeader*> lista;

	static void add(PartHeader* p);
	static void izbaci(char slovo);
	static void ispisi();
	static PartHeader* dohvati(char part);

};

#endif