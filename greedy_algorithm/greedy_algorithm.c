// format of file's data: [beg; end)\n
// example: [20:30; 21:00)
#include <stdlib.h>

#include "greedy_algorithm.h"

//++++++++++++++++++++++++

int Check_time(FILE* fp)
{
	char check = '\0';

	check = getc(fp);
	if (check < '0' || check > '9')
		return -1;
	check = getc(fp);
	if (check < '0' || check > '9')
		return -1;
	check = getc(fp);
	if (check != ':')
		return -1;
	check = getc(fp);
	if (check < '0' || check > '9')
		return -1;
	check = getc(fp);
	if (check < '0' || check > '9')
		return -1;

	return 0;
}

//++++++++++++++++++++++++

int Check_file(FILE* fp)
{
	char check = '\0';

	while (1)
	{
		fscanf(fp, "%*[^[]");
		check = getc(fp);
		if (check == EOF)
			break;
		if (Check_time(fp) == -1)
			return -1;
		check = getc(fp);
		if (check != ';')
			return -1;

		check = getc(fp);
		if (check != ' ')
			return -1;
		if (Check_time(fp) == -1)
			return -1;
		check = getc(fp);
		if (check != ')')
			return -1;
	}

	fseek(fp, 0, SEEK_SET);
	return 0;
}

//++++++++++++++++++++++++

size_t Count_lessons(FILE* fp)
{
	size_t num = 0;

	for (num = 0; 1; ++num)
	{
		fscanf(fp, "%*[^[]");
		if (getc(fp) == EOF)
			break;
	}
	fseek(fp, 0, SEEK_SET);
	return num;
}

//++++++++++++++++++++++++

Lesson* Scan_Lessons_Data(FILE* fp)
{
	if (Check_file(fp) == -1)
		return NULL;

	size_t num = Count_lessons(fp);

	Lesson* less = (Lesson*) calloc(num + 1, sizeof(Lesson));

	int hours = 0;
	int minutes = 0;

	for (size_t i = 0; i < num; ++i)
	{
		fscanf(fp, "%*[^[]");
		fscanf(fp, "[%d:%d;", &hours, &minutes);
		less[i].beg = 60 * hours + minutes;
		fscanf(fp, "%d:%d)", &hours, &minutes);
		less[i].end = 60 * hours + minutes;
	}
	less[num].beg = -1;

	return less;
}

//++++++++++++++++++++++++

int Sort(Lesson* less)
{
	for (size_t i = 0; less[i].beg != -1; ++i)
	{
		for (size_t j = 0; less[j + 1].beg != -1; ++j)
		{
			if (less[j + 1].end < less[j].end)
			{
				less[j].beg += less[j + 1].beg;
				less[j + 1].beg = less[j].beg - less[j + 1].beg;
				less[j].beg -= less[j + 1].beg;

				less[j].end += less[j + 1].end;
				less[j + 1].end = less[j].end - less[j + 1].end;
				less[j].end -= less[j + 1].end;
			}
		}
	}
	return 0;
}

//++++++++++++++++++++++++

 int Choose_Lessons(Lesson* less)
{
	Sort(less);

	int ending = 0;
	for (size_t i = 0; less[i].beg != -1; ++i)
	{
		if (less[i].beg >= ending)
		{
			Print_Time(less[i].beg, less[i].end);
			ending = less[i].end;
		}
	}
	return 0;
}

//++++++++++++++++++++++++

int Print_Time(int beg, int end)
{
	int hours = beg / 60;
	int minutes = beg % 60;

	printf("[%02d:%02d; ", hours, minutes);

	hours = end / 60;
	minutes = end % 60;

	printf("%02d:%02d)\n", hours, minutes);

	return 0;
}
