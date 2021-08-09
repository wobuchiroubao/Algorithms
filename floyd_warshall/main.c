#include <stdio.h>

#include "floyd-warshall.h"

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
	Find_ways(table);
	Print_answ(table);
	Delete_table(table);
	fclose(fp);

	return 0;
}
