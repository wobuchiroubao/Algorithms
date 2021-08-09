#ifndef STACK_H
#define STACK_H
#include <stdio.h>
#include <stdlib.h>

struct Stack
{
	int* buf_;
	size_t capacity_;
	size_t size_;
} typedef Stack;

Stack* Init_Stack(Stack* stk);
Stack* Init_Stack_Cap(Stack* stk, size_t capacity);
int Delete_Stack(Stack* stk);
int Push(Stack* stk, int x);
int Pop(Stack* stk);
int Top(Stack* stk);

#endif
