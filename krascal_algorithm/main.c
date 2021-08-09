#include <stdio.h>

#include "krascal_algoritm.h"

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

	Table* table = Init_table(fp);
	Table* spanning_tree = Init_spanning_tree(table);

	if (spanning_tree == NULL)
	{
		printf("Graph is disconnected, so spanning tree can\'t be found.\n");
		return -1;
	}

	Prt_spanning_tree(spanning_tree);

	fclose(fp);
	Delete_table(table);
	Delete_table(spanning_tree);

	return 0;
}
