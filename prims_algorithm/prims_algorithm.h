#ifndef PRIMS_ALG_H
#define PRIMS_ALG_H

#include <stdio.h>

struct Node
{
	int* dist;
	int link;
} typedef Node;

//-----------------------

struct Table
{
	int len;
	Node* node;
}	typedef Table;

//----------------------

int Count_nodes(FILE* fp);
Table* Init_table(FILE* fp);
int Delete_table(Table* table);
Table* Make_spanning_tree(Table* table);
Table* Init_spanning_tree(Table* table);
int Prt_spanning_tree(Table* spanning_tree);

#endif
