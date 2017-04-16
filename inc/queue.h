#ifndef QUEUE_H
#define QUEUE_H

#define QUEUE_SIZE 4
#define MAXQUEUE_INPUT_SIZE 12

class queue
{
private:
	int head;
	int tail;
	int *buffer;
	int int_size;
public:
	queue();
	queue(int size);
	int enqueue(int data);
	int dequeue(void);
	void dump(void);
	~queue();
};
#endif