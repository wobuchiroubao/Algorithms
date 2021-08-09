#include <stdio.h>

#include "topological_sort.h"

int main(int argc, char** argv)
{
	if (argc == 1)
	{
		printf("You haven\'t pointed a file with graph.\n");
		return -1;
	}

	FILE* fp = fopen(argv[1], "r");

	if (fp == NULL)
	{
		printf("Incorrect filename.\n");
		return -1;
	}

	Bonds* bonds = Make_bonds(fp);
	if (Depth_first_search(bonds) == -1)
	{
		printf("Cycle\'s found, so topological sort can\'t be used.\n");
		return -1;
	}

	fclose(fp);
	Delete_bonds(bonds);

	return 0;
}
