#ifndef __STACK_H__
#define __STACK_H__
#define MAX_STACK 4

class stack
{
private:
	int top;
	int buffer[MAX_STACK];
public:
	stack();
	~stack();
	void push(int data);
	int pop();
};

#endif