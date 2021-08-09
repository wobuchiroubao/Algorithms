#ifndef KRASCAL_ALG_H
#define KRASCAL_ALG_H

#include <stdio.h>

struct Table
{
	int len;
	int** dist;
}	typedef Table;

//----------------------

int Count_nodes(FILE* fp);
Table* Init_table(FILE* fp);
int Delete_table(Table* table);
Table* Make_spanning_tree(Table* table);
Table* Init_spanning_tree(Table* table);
int Find_cycle(Table* spanning_tree, int f_node, int s_node);
int Dfs(Table* spanning_tree, int standart, int cur, int prev);
int Prt_spanning_tree(Table* spanning_tree);

#endif
