#include "queue.h"
#include <iostream>
#include <stdlib.h>
#include <cerrno>
#include <iomanip>

using namespace std;
#define EMPTY_TOCKETN -1 

queue::queue() : head(0), tail(0), int_size(QUEUE_SIZE)
{
	buffer = (int *)malloc(QUEUE_SIZE << 2);
	memset(buffer, EMPTY_TOCKETN, this->int_size << 2);
}

queue::queue(int size) : head(0), tail(0), int_size(size)
{
	buffer = (int *)malloc(int_size << 2);
	memset(buffer, EMPTY_TOCKETN, this->int_size << 2);
}

int queue::enqueue(int data)
{
	if ((tail + 1) % this->int_size != head){
		buffer[tail] = data;
		tail = (tail + 1) % this->int_size;
		return 0;
	}
	else
	{
		return -1;
	}
}

int queue::dequeue(void)
{
	int data;
	if (head == tail){
		cout << "U" << endl;
		return -1;
	}
	else
	{
		data = buffer[head];
		buffer[head] = -1;
		head = (head + 1) % this->int_size;
		return data;
	}
}

void queue::dump(void){
	cout << "List : ";
	for (int index = 0; index < this->int_size; index++)
		cout << "[" << index << "] ";
	cout << endl;
	cout << setw(6) <<"";
	
	for (int index = 0; index < this->int_size; index++)
		cout << setw(4) << this->buffer[index];
	cout << endl;

	cout << "head: " << head << endl;
	cout << "tail: " << tail << endl;
}

queue::~queue()
{
	free(buffer);
}