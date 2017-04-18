#include "common.h"
#include "queue.h"
#include "linklist.h"
#include "stack.h"
#include "tree.hpp"

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

void tree_test(void)
{
	tree my_tree;
	struct tree_node *root = nullptr;
	struct tree_node *temp_node = nullptr;
	int index;
	int input[] = { 15, 6, 3, 7, 2, 4, 13, 9, 18, 17, 20 };
		
	printf("[BST] insert inputs\n");
	for(index = 0; index < sizeof(input) / sizeof(input[0]); index++)
	{
		my_tree.insert_node(input[index]);
	}
	root = my_tree.get_root();
	printf("Inorder: ");
	my_tree.inorder_visit(root);
	printf("\n");

	temp_node = my_tree.search_node(root, 13);
	temp_node = my_tree.successor(temp_node);
	printf("Successor(13) = %d\n",temp_node->key);

	temp_node = my_tree.find_max(root);
	printf("Max(root): %d\n",temp_node->key);

	temp_node = my_tree.find_min(root);
	printf("Min(root): %d\n", temp_node->key);

	temp_node = my_tree.search_node(root, 15);
	temp_node = my_tree.delete_node(temp_node);
	printf("Delete 15 but free %d\n", temp_node->key);
	free(temp_node);

	printf("Inorder: ");
	my_tree.inorder_visit(root);
	printf("\n");


	

	return;
}


int main(void)
{
	//queue_test();
	//link_list_test();
	//stack_test();

	tree_test();

	system("pause");
}