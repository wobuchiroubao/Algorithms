#include "stack.h"

Stack* Init_Stack(Stack* stk)
{
	stk->buf_ = (int*) calloc(10, sizeof(int));
	stk->capacity_ = 10;
	stk->size_ = 0;

	return stk;
}

//---------------------

Stack* Init_Stack_Cap(Stack* stk, size_t capacity)
{
	stk->buf_ = (int*) calloc(capacity, sizeof(int));
	stk->capacity_ = capacity;
	stk->size_ = 0;

	return stk;
}

//---------------------

int Delete_Stack(Stack* stk)
{
	free(stk->buf_);

	return 0;
}

//---------------------

int Push(Stack* stk, int x)
{
	int* change_buf = NULL;
	if (stk->size_ == stk->capacity_)
	{
		change_buf = (int*) realloc(stk->buf_, sizeof(int) * 2 * stk->capacity_);

		if (change_buf == NULL)
			return -1;

		stk->buf_ = change_buf;
		stk->capacity_ *= 2;
	}

	stk->buf_[(stk->size_)++] = x;

	return 0;
}

//---------------------

int Pop(Stack* stk)
{
	if (stk->size_ * 2 == stk->capacity_ && stk->capacity_ >= 20)
	{
		stk->capacity_ /= 2;
		stk->buf_ = (int*) realloc(stk->buf_, sizeof(int) * stk->capacity_);
	}

	if (stk->size_ > 0)
		return stk->buf_[--(stk->size_)];
	else
		return -1;
}

//---------------------

int Top(Stack* stk)
{
	if (stk->size_ > 0)
		return stk->buf_[stk->size_ - 1];
	else
		return -1;
}
