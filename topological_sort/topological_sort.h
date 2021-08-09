#ifndef TOPOLOGICAL_SORT_H
#define TOPOLOGICAL_SORT_H

#include <stdio.h>

#include "../stack/stack.h"

struct Sec_Node
{
	int num;
	struct Sec_Node* next;
} typedef Sec_Node;

//------------------------

struct Fir_Node
{
	Sec_Node* head;
	char colour;
} typedef Fir_Node;

//------------------------

struct Bonds
{
	Fir_Node* buf;
	int len;
} typedef Bonds;

//------------------------

int Count_nodes(FILE* fp);
Sec_Node* Make_Sec_Node(FILE* fp);
Bonds* Make_bonds(FILE* fp);
int Delete_bonds(Bonds* bonds);
int Depth_first_search(Bonds* bonds);
int Dfs(Bonds* bonds, int new_f_node, Stack* stk);
int Ptf(int len, Stack* stk);

#endif
