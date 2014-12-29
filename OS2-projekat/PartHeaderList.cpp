#include"PartHeaderList.h"
#include<cstdlib>
#include<iterator>

list<PartHeader*> PartHeaderList::lista;


void PartHeaderList::add(PartHeader* p){

	PartHeaderList::lista.push_back(p);
}

void PartHeaderList::izbaci(char slovo)
{
	
	for (list<PartHeader*>::iterator tek = PartHeaderList::lista.begin(); tek != lista.end();     ){
		PartHeader* p = (*tek);
		if (p->slovo == slovo){lista.remove(p); break; }
		tek++;
	}
}

void PartHeaderList::ispisi()
{
	for (list<PartHeader*>::iterator it = lista.begin(); it != lista.end(); it++)
	{
		cout << "Particija: "<<(*it)->slovo << endl;
	}
}