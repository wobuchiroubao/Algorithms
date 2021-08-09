#include <stdlib.h>
#include <limits.h>

#include "floyd-warshall.h"

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
	table->shortest_dist = (int**) calloc(length, sizeof(int*));

	fscanf(fp, "%*[^\n]");

	for (int i = 0; i < length; ++i)
	{
		fscanf(fp, "%*d");
		table->shortest_dist[i] = (int*) calloc(length, sizeof(int));
		for (int j = 0; j < length; ++j)
			if (fscanf(fp, "%d", &(table->shortest_dist[i][j])) == 0)
			{
				table->shortest_dist[i][j] = INT_MAX;
				fscanf(fp, "%*[-]");
			}
	}

	size_t length_2 = length * length;
	table->way = (int**) calloc(length_2, sizeof(int*));
	for (size_t i = 0; i < length_2; ++i)
		table->way[i] = (int*) calloc(length, sizeof(int));

	return table;
}
//------------------------

int Delete_table(Table* table)
{
	int length = table->len;
	for (int i = 0; i < length; ++i)
		free(table->shortest_dist[i]);
	size_t length_2 = length * length;
	for (size_t i = 0; i < length_2; ++i)
		free(table->way[i]);

	free(table->shortest_dist);
	free(table->way);
	free(table);

	return 0;
}

//------------------------

int Find_ways(Table* table)
{
	int length = table->len;
	for (int k = 0; k < length; ++k)
	{
		for (int i = 0; i < length; ++i)
		{
			for (int j = 0; j < length; ++j)
			{
				if (
					table->shortest_dist[i][k] != INT_MAX &&\
					table->shortest_dist[k][j] != INT_MAX &&\
					table->shortest_dist[i][j] > table->shortest_dist[i][k] + table->shortest_dist[k][j]
				)
				{
					table->shortest_dist[i][j] = \
						table->shortest_dist[i][k] + table->shortest_dist[k][j];
					Change_way(
						length, table->way[i * length + j], table->way[i * length + k], k,
						table->way[k * length + j]
					);
				}
			}
		}
	}

	return 0;
}

//------------------------

int Change_way(
	int length, int* destptr, int* srcptr_1, int addition, int* srcptr_2
)
{
	int i = 0;
	for (i = 0; i < length && srcptr_1[i] != 0; ++i)
		destptr[i] = srcptr_1[i];
	destptr[i] = addition + 1;
	++i;
	for (int j = i; j < length && srcptr_2[j - i] != 0; ++j)
		destptr[j] = srcptr_2[j - i];

	return 0;
}

//------------------------

void Print_answ(Table* table)
{
	int length = table->len;
	for (int i = 0; i < length; ++i)
	{
		for (int j = 0; j < length; ++j)
		{
			if (table->shortest_dist[i][j] != INT_MAX)
			{
				printf(
					"#length of shortest way %d - %d = %d\n",
					i + 1, j + 1, table->shortest_dist[i][j]
				);
				printf("way: %d -> ", i + 1);
				for (int k = 0; k < length && table->way[i * length + j][k] != 0 ; ++k)
					printf("%d -> ", table->way[i * length + j][k]);
				printf("%d\n", j + 1);
			}
			else
			{
				printf("#way %d - %d doesn\'t exist\n", i + 1, j + 1);
				printf("way: -\n");
			}
		}
	}
}
