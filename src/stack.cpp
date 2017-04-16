#include "common.h"
#include "stack.h"

stack::stack() :top(-1)
{
}

void stack::push(int data)
{
	if (top == MAX_STACK - 1)
	{
		cout << "overflow" << endl;
		return;
	}
	buffer[++top] = data;
}

int stack::pop()
{
	if (top == -1)
	{
		cout << "underflow" << endl;
		return -1;
	}
	return buffer[top--];
}
stack::~stack()
{
	return;
}