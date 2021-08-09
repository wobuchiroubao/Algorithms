#ifndef GREEDY_ALG_H
#define GREEDY_ALG_H

#include <stdio.h>

struct Lesson
{
	int beg;
	int end;
} typedef Lesson;

//++++++++++++++++++++++++

int Check_time(FILE* fp);
int Check_file(FILE* fp);
size_t Count_lessons(FILE* fp);
Lesson* Scan_Lessons_Data(FILE* fp);
int Sort(Lesson* less);
int Choose_Lessons(Lesson* less);
int Print_Time(int beg, int end);

#endif
