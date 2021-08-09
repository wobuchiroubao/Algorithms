//1) 2, 3, 4, 5;
//2) ;
//3) 5;
//4) 2, 3;
//5) 1, 3, 4;
#include <stdlib.h>

#include "topological_sort.h"

//------------------------

int Count_nodes(FILE* fp)
{
	int num = 0;
	for (num = 0; fscanf(fp, "%*[^)]") != EOF; ++num)
		getc(fp);
	fseek(fp, 0, SEEK_SET);

	return --num;
}

//------------------------

Sec_Node* Make_Sec_Node(FILE* fp)
{
	int num = 0;
	if (fscanf(fp, "%d", &num) != 1)
		return NULL;
	Sec_Node* node = (Sec_Node*) calloc(1, sizeof(Sec_Node));
	node->num = num;
	node->next = NULL;

	return node;
}

//------------------------

Bonds* Make_bonds(FILE* fp)
{
	Bonds* bonds = (Bonds*) calloc(1, sizeof(Bonds));
	int length = Count_nodes(fp);
	bonds->len = length;
	bonds->buf = (Fir_Node*) calloc(length + 1, sizeof(Fir_Node));

	Sec_Node* new_s_node = NULL;
	Sec_Node* cur_s_node = NULL;

	for (int i = 1; i <= length; ++i)
	{
		fscanf(fp, "%*[^)])");
		bonds->buf[i].colour = 'w';
		bonds->buf[i].head = Make_Sec_Node(fp);
		cur_s_node = bonds->buf[i].head;
		if (cur_s_node == NULL)
			continue;
		while (getc(fp) != ';')
		{
			new_s_node = Make_Sec_Node(fp);
			cur_s_node->next = new_s_node;
			cur_s_node = new_s_node;
		}
	}
	fseek(fp, 0, SEEK_SET);

	return bonds;
}

//------------------------

int Delete_bonds(Bonds* bonds)
{
	Sec_Node* cur_s_node = NULL;
	Sec_Node* del_s_node = NULL;
	int length = bonds->len;

	for (int i = 1; i <= length; ++i)
	{
		cur_s_node = bonds->buf[i].head;
		while (cur_s_node != NULL)
		{
			del_s_node = cur_s_node;
			cur_s_node = cur_s_node->next;
			free(del_s_node);
		}
	}
	free(bonds->buf);
	free(bonds);

	return 0;
}

//------------------------

int Depth_first_search(Bonds* bonds)
{
	Stack stk;
	Init_Stack(&stk);
	int length = bonds->len;
	Sec_Node* cur_s_node = NULL;
	for (int f_node = length; f_node >= 1; --f_node)
	{
		if (bonds->buf[f_node].colour == 'g')
			return -1;
		if (bonds->buf[f_node].colour == 'w' && Dfs(bonds, f_node, &stk) == -1)
			return -1;
	}
	Ptf(bonds->len, &stk);
	Delete_Stack(&stk);

	return 0;
}

//------------------------

int Dfs(Bonds* bonds, int new_f_node, Stack* stk)
{
	Sec_Node* cur_s_node = NULL;

	bonds->buf[new_f_node].colour = 'g';
	cur_s_node = bonds->buf[new_f_node].head;
	while (cur_s_node != NULL)
	{
		if (bonds->buf[cur_s_node->num].colour == 'g')
			return -1;
		else if (bonds->buf[cur_s_node->num].colour == 'w')
		{
			if (Dfs(bonds, cur_s_node->num, stk) == -1)
				return -1;
		}

		cur_s_node = cur_s_node->next;
	}
	Push(stk, new_f_node);
	bonds->buf[new_f_node].colour = 'b';

	return 0;
}

//------------------------

int Ptf(int len, Stack* stk)
{
	for (int i = 1; i <= len; ++i)
		printf("%d change to %d\n", (int) Pop(stk), i);

	return 0;
}
