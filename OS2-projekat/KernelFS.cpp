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

