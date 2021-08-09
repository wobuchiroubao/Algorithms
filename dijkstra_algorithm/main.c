#include <stdio.h>

#include "dijkstra_algorithm.h"

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

	printf("Please, enter the begining node:\n");
	int beg_node = 0;
	scanf("%d", &beg_node);

	Bonds* bonds = Make_bonds(fp, beg_node);
	Put_weight_Find_prev(bonds);
	Print_ways(bonds, beg_node);
	Delete_bonds(bonds);
	fclose(fp);

	return 0;
}
