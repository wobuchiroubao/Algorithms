#include <stdio.h>
#include <stdlib.h>

#include "greedy_algoritm.h"

int main(int argc, char** argv)
{
	if (argc == 1)
	{
		printf("You haven\'t pointed a file with lesson\'s times.\n");
		return -1;
	}

	FILE* fp = fopen(argv[1], "r");

	if (fp == NULL)
	{
		printf("Incorrect filename.\n");
		return -1;
	}

	Lesson* less = Scan_Lessons_Data(fp);

	if (less == NULL)
	{
		printf("Incorrect format of data in file: %s\n", argv[1]);
		return -1;
	}

	Choose_Lessons(less);
	free(less);
	fclose(fp);

	return 0;
}
