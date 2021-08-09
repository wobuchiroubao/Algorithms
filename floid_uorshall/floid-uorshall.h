#ifndef FLOID_UORSHALL_H
#define FLOID_UORSHALL_H

#include <stdio.h>

struct Table
{
	int len;
	int** shortest_dist;
	int** way;
}	typedef Table;

//----------------------

int Count_nodes(FILE* fp);
Table* Init_table(FILE* fp);
int Delete_table(Table* table);
int Find_ways(Table* table);
int Change_way(
	int length, int* destptr, int* srcptr_1, int addition, int* srcptr_2
);
void Print_answ(Table* table);

#endif
