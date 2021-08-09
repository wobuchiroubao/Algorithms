#ifndef DEIKSTRA_ALG_H
#define DEIKSTRA_ALG_H

#include <stdio.h>

struct Sec_Node
{
	int num;
	int way_len;
	struct Sec_Node* next;
} typedef Sec_Node;

//------------------------

struct Fir_Node
{
	Sec_Node* head;
	int weight;
	int visit;
	int prev;
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
Bonds* Make_bonds(FILE* fp, int beg_node);
int Delete_bonds(Bonds* bonds);
int Put_weight_Find_prev(Bonds* bonds);
int Choose_cur_first_node(Bonds* bonds);
int Print_ways(Bonds* bonds, int beg_node);

#endif
