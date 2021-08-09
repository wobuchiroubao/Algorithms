//1) 2 - 10, 3 - 30, 4 - 50, 5 - 10;
//2) ;
//3) 5 - 10;
//4) 2 - 40, 3 - 20;
//5) 1 - 10, 3 - 10, 4 - 30;
#include <stdlib.h>
#include <limits.h>

#include "../stack/stack.h"
#include "deikstra_algoritm.h"

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
	int way_len = 0;
	if (fscanf(fp, "%d - %d", &num, &way_len) != 2)
		return NULL;
	Sec_Node* node = (Sec_Node*) calloc(1, sizeof(Sec_Node));
	node->num = num;
	node->way_len = way_len;
	node->next = NULL;

	return node;
}

//------------------------

Bonds* Make_bonds(FILE* fp, int beg_node)
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
		bonds->buf[i].weight = INT_MAX;
		bonds->buf[i].visit = 0;
		bonds->buf[i].prev = beg_node;
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
	bonds->buf[beg_node].weight = 0;
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

int Put_weight_Find_prev(Bonds* bonds)
{
	int cur_f_node = 0;
	Sec_Node* cur_s_node = NULL;

	while (1)
	{
		cur_f_node = Choose_cur_first_node(bonds);

		if (cur_f_node == 0)
			break;

		bonds->buf[cur_f_node].visit = 1;
		cur_s_node = bonds->buf[cur_f_node].head;
		while (cur_s_node != NULL)
		{
			if (bonds->buf[cur_s_node->num].weight > bonds->buf[cur_f_node].weight + \
					cur_s_node->way_len)
			{
				bonds->buf[cur_s_node->num].weight = bonds->buf[cur_f_node].weight + \
				cur_s_node->way_len;
				bonds->buf[cur_s_node->num].prev = cur_f_node;
			}

			cur_s_node = cur_s_node->next;
		}
	}

	return 0;
}

//------------------------

int Choose_cur_first_node(Bonds* bonds)
{
	int length = bonds->len;
	int min = INT_MAX;
	int new_f_node = 0;

	for (int i = 1; i <= length; ++i)
	{
		if (bonds->buf[i].weight < min && bonds->buf[i].visit == 0)
		{
			min = bonds->buf[i].weight;
			new_f_node = i;
		}
	}

	return new_f_node;
}

//------------------------

int Print_ways(Bonds* bonds, int beg_node)
{
	int length = bonds->len;
	Stack stk;
	Init_Stack(&stk);
	int previous = 0;

	printf("\n");
	for (int i = 1; i <= length; ++i)
	{
		previous = bonds->buf[i].prev;
		while (previous != beg_node)
		{
			Push(&stk, previous);
			previous = bonds->buf[previous].prev;
		}

		if (bonds->buf[i].weight < INT_MAX)
		{
			printf("length of way from %d to %d: %d\n", beg_node, i, bonds->buf[i].weight);
			printf("%d -> ", beg_node);
			while (stk.size_ > 0)
			{
				printf("%d -> ", (int) Pop(&stk));
			}
			printf("%d\n\n", i);
		}
		else
		printf("Way from node %d to %d doesn\'t exist\n\n", beg_node, i);
	}
	Delete_Stack(&stk);

	return 0;
}
