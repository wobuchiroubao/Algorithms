#include <stdlib.h>
#include <limits.h>

#include "krascal_algoritm.h"

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
	table->dist = (int**) calloc(length, sizeof(int*));

	for (int i = 0; i < length; ++i)
	{
		fscanf(fp, "%*[^\n]%*d");
		table->dist[i] = (int*) calloc(i, sizeof(int));
		for (int j = 0; j < i; ++j)
			if (fscanf(fp, "%d", &(table->dist[i][j])) == 0)
			{
				table->dist[i][j] = INT_MAX;
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
		free(table->dist[i]);
	free(table->dist);
	free(table);

	return 0;
}

//------------------------

Table* Make_spanning_tree(Table* table)
{
	int length = table->len;
	Table* spanning_tree = (Table*) calloc(1, sizeof(Table));
	spanning_tree->len = length;
	spanning_tree->dist = (int**) calloc(length, sizeof(int*));

	for (int i = 0; i < length; ++i)
	{
		spanning_tree->dist[i] = (int*) calloc(i, sizeof(int));
		for (int j = 0; j < i; ++j)
			spanning_tree->dist[i][j] = INT_MAX;
	}

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
			for (int j = 0; j < i; ++j)
			{
				if (table->dist[i][j] < min && spanning_tree->dist[i][j] == INT_MAX \
				&& Find_cycle(spanning_tree, i, j) == 0)
				{
					min = table->dist[i][j];
					f_node = i;
					s_node = j;
				}
			}
		}
		if (min == INT_MAX)
			break;
		spanning_tree->dist[f_node][s_node] = min;
		min = INT_MAX;
	}
	if (check != length)
		return NULL;

	return spanning_tree;
}

//------------------------

int Find_cycle(Table* spanning_tree, int f_node, int s_node)
{
	spanning_tree->dist[f_node][s_node] = 1;
	int ret = Dfs(spanning_tree, f_node, f_node, f_node);
	spanning_tree->dist[f_node][s_node] = INT_MAX;

	return ret;
}

//------------------------

int Dfs(Table* spanning_tree, int standart, int cur, int prev)
{
	int length = spanning_tree->len;

	for (int j = 0; j < cur; ++j)
	{
		if (j == standart && j != prev && spanning_tree->dist[cur][j] < INT_MAX)
			return -1;
		if (j != prev && spanning_tree->dist[cur][j] < INT_MAX)
		{
			if (Dfs(spanning_tree, standart, j, cur) == -1)
				return -1;
		}
	}
	for (int j = cur + 1; j < length; ++j)
	{
		if (j == standart && j != prev && spanning_tree->dist[j][cur] < INT_MAX)
			return -1;
		if (j != prev && spanning_tree->dist[j][cur] < INT_MAX)
		{
			if (Dfs(spanning_tree, standart, j, cur) == -1)
				return -1;
		}
	}

	return 0;
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
			if (spanning_tree->dist[i][j] == INT_MAX)
				printf(" -");
			else
				printf(" %d", spanning_tree->dist[i][j]);
		}
		printf(" 0\n");
	}

	return 0;
}
