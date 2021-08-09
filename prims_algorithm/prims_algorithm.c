#include <stdlib.h>
#include <limits.h>

#include "prims_algorithm.h"

//----------------------

int Count_nodes(FILE* fp)
{
	char cur_char = getc(fp);
	int count = 0;
	int answ = 0;

	while (cur_char != '\n')
	{
		if (cur_char >= '0' && cur_char <= '9')
			++count;
		else
			count = 0;
		cur_char = getc(fp);
	}

	fseek(fp, - count - 1, SEEK_CUR);
	fscanf(fp, "%d", &answ);
	fseek(fp, 0, SEEK_SET);

	return answ;
}

//------------------------

Table* Init_table(FILE* fp)
{
	Table* table = (Table*) calloc(1, sizeof(Table));
	int length = Count_nodes(fp);
	table->len = length;
	table->node = (Node*) calloc(length, sizeof(Node));

	for (int i = 0; i < length; ++i)
	{
		fscanf(fp, "%*[^\n]%*d");
		table->node[i].dist = (int*) calloc(i, sizeof(int));
		for (int j = 0; j < i; ++j)
			if (fscanf(fp, "%d", &(table->node[i].dist[j])) == 0)
			{
				table->node[i].dist[j] = INT_MAX;
				fscanf(fp, "%*[-]");
			}
	}
	fseek(fp, 0, SEEK_SET);

	return table;
}
//------------------------

int Delete_table(Table* table)
{
	int length = table->len;
	for (int i = 0; i < length; ++i)
		free(table->node[i].dist);
	free(table->node);
	free(table);

	return 0;
}

//------------------------

Table* Make_spanning_tree(Table* table)
{
	int length = table->len;
	Table* spanning_tree = (Table*) calloc(1, sizeof(Table));
	spanning_tree->len = length;
	spanning_tree->node = (Node*) calloc(length, sizeof(Node));

	for (int i = 0; i < length; ++i)
	{
		spanning_tree->node[i].dist = (int*) calloc(i, sizeof(int));
		spanning_tree->node[i].link = 0;
		for (int j = 0; j < i; ++j)
			spanning_tree->node[i].dist[j] = INT_MAX;
	}

	spanning_tree->node[0].link = 1;

	return spanning_tree;
}

//------------------------

Table* Init_spanning_tree(Table* table)
{
	int length = table->len;
	Table* spanning_tree = Make_spanning_tree(table);

	int min = INT_MAX;
	int check = 0;
	int f_node = -1;
	int s_node = -1;

 	while (1)
	{
		++check;
		for (int i = 0; i < length; ++i)
		{
			if (spanning_tree->node[i].link == 1)
			{
				for (int j = 0; j < i; ++j)
				{
					if (table->node[i].dist[j] < min && spanning_tree->node[j].link == 0)
					{
						min = table->node[i].dist[j];
						f_node = i;
						s_node = j;
					}
				}
				for (int j = i + 1; j < length; ++j)
				{
					if (table->node[j].dist[i] < min && spanning_tree->node[j].link == 0)
					{
						min = table->node[j].dist[i];
						f_node = j;
						s_node = i;
					}
				}
			}
		}
		if (min == INT_MAX)
			break;
		spanning_tree->node[f_node].dist[s_node] = min;
		spanning_tree->node[f_node].link = 1;
		spanning_tree->node[s_node].link = 1;
		min = INT_MAX;
	}
	if (check != length)
		return NULL;

	return spanning_tree;
}

//------------------------

int Prt_spanning_tree(Table* spanning_tree)
{
	int length = spanning_tree->len;

	printf("   ");

	for (int i = 0; i < length; ++i)
		printf(" %d", i + 1);

	printf("\n    ");
	for (int i = 0; i < length; ++i)
		printf("--");
	printf("\n");

	for (int i = 0; i < length; ++i)
	{
		printf("%d |", i + 1);
		for (int j = 0; j < i; ++j)
		{
			if (spanning_tree->node[i].dist[j] == INT_MAX)
				printf(" -");
			else
				printf(" %d", spanning_tree->node[i].dist[j]);
		}
		printf(" 0\n");
	}

	return 0;
}
