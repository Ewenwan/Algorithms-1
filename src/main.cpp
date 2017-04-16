#include "common.h"
#include "queue.h"
#include "linklist.h"
#include "stack.h"

int get_random_value(void)
{
	default_random_engine generator;
	uniform_int_distribution<int> distribution(1, 100);
	auto dice = std::bind(distribution, generator);
	return dice();
}

void queue_test(void)
{
	queue test_queue(10);
	default_random_engine generator;
	uniform_int_distribution<int> distribution(1, 100);
	auto dice = std::bind(distribution, generator);
	int random_data;
	int ret;

	cout << "Initial queue" << endl;
	test_queue.dump();
	cout << endl;

	cout << "Enqueue:";
	for (int loop = 0; loop < MAXQUEUE_INPUT_SIZE; loop++)
	{
		random_data = dice();
		cout << setw(3) << random_data;
		ret = test_queue.enqueue(random_data);

	}
	cout << endl;
	test_queue.dump();
	cout << endl;

	for (int loop = 0; loop < 3; loop++)
	{
		ret = test_queue.dequeue();
		cout << "Dequeue:" << ret << endl;
		test_queue.dump();
		cout << endl;
	}
	
	for (int loop = 0; loop < MAXQUEUE_INPUT_SIZE; loop++)
	{
		cout << "Enqueue:";
		random_data = dice();
		cout << setw(2) << random_data << endl;
		ret = test_queue.enqueue(random_data);
		test_queue.dump();
		cout << endl;
	}
	
}

void stack_test(void)
{
	int data;
	default_random_engine generator;
	uniform_int_distribution<int> distribution(1, 100);
	auto dice = std::bind(distribution, generator);
	stack my_stack;
	my_stack.push(dice());
	my_stack.push(dice());
	my_stack.push(dice());
	my_stack.push(dice());
	my_stack.push(dice());

	do {
		data = my_stack.pop();
		if (data !=-1)
			cout << data << endl;
	} while (data != -1);

}

void link_list_test(void)
{
	linklist test_list;
	test_list.do_insert(5);
	test_list.do_dump_list();
#if 1
	test_list.do_delete(test_list.do_search(5));
	test_list.do_dump_list();
#endif
}

int main(void)
{
	//queue_test();
	//link_list_test();
	stack_test();
	system("pause");
}