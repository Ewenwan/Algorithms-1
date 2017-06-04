#include "common.h"
#include "queue.h"
#include "linklist.h"
#include "stack.h"
#include "tree.hpp"
#include "rbtree.h"
#include "OrderStaticTree.h"
#include "int_tree.h"
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

void rbtree_test(void)
{
	rbtree my_tree;
	struct the_tree *T;
	struct rbtree_node *tmp;


	T = my_tree.get_the_tree();
	my_tree.rb_insert_node(7);
	my_tree.rb_insert_node(6);
	my_tree.rb_insert_node(5);
	my_tree.rb_insert_node(4);
	my_tree.rbtree_dump(T->root);
	printf("delete 5 \n");
	tmp = my_tree.rb_search(5);
	if (tmp == T->nil)
		printf("search 5 failed \n");
	my_tree.rb_delete_node(tmp);
	my_tree.rbtree_dump(T->root);
	printf("insert 20 \n");
	my_tree.rb_insert_node(20);
	my_tree.rbtree_dump(T->root);
	printf("insert 21 \n");
	my_tree.rb_insert_node(21);
	my_tree.rbtree_dump(T->root);
	printf("insert 22 \n");
	my_tree.rb_insert_node(22);
	my_tree.rbtree_dump(T->root);
	printf("insert 23 \n");
	my_tree.rb_insert_node(23);
	my_tree.rbtree_dump(T->root);
	printf("insert 24 \n");
	my_tree.rb_insert_node(24);
	my_tree.rbtree_dump(T->root);
	printf("delete 22 \n");
	tmp = my_tree.rb_search(22);
	if (tmp == T->nil)
		printf("search 22 failed \n");
	my_tree.rb_delete_node(tmp);
	my_tree.rbtree_dump(T->root);

	return;
}
void ostree_test(void)
{
	os_tree my_ostree;
	rbtree *my_tree = my_ostree.get_the_os_tree();
	struct the_tree *T;
	struct rbtree_node *tmp;


	T = my_tree->get_the_tree();


	my_tree->rb_insert_node(7);
	my_tree->rbtree_dump(T->root);
	my_tree->rb_insert_node(6);
	my_tree->rbtree_dump(T->root);
	my_tree->rb_insert_node(5);
	my_tree->rbtree_dump(T->root);
	my_tree->rb_insert_node(4);
	my_tree->rbtree_dump(T->root);
	my_tree->rbtree_dump(T->root);
	printf("delete 5 \n");
	tmp = my_tree->rb_search(5);
	if (tmp == T->nil)
		printf("search 5 failed \n");
	my_tree->rb_delete_node(tmp);
	my_tree->rbtree_dump(T->root);
	printf("insert 20 \n");
	my_tree->rb_insert_node(20);
	my_tree->rbtree_dump(T->root);
	printf("insert 21 \n");
	my_tree->rb_insert_node(21);
	my_tree->rbtree_dump(T->root);
	printf("insert 22 \n");
	my_tree->rb_insert_node(22);
	my_tree->rbtree_dump(T->root);
	printf("insert 23 \n");
	my_tree->rb_insert_node(23);
	my_tree->rbtree_dump(T->root);
	printf("insert 24 \n");
	my_tree->rb_insert_node(24);
	my_tree->rbtree_dump(T->root);
	printf("delete 22 \n");
	tmp = my_tree->rb_search(22);
	if (tmp == T->nil)
		printf("search 22 failed \n");
	my_tree->rb_delete_node(tmp);
	my_tree->rbtree_dump(T->root);

	printf("inorder\n");
	my_tree->rbtree_dump(T->root);
	my_tree->inorder_dump();
	printf("find 3thd node\n");
	tmp = my_ostree.os_select(T->root, 3);
	printf("3th key = %d\n", tmp->key);
	printf("%d's ranks is %d\n", tmp->key, my_ostree.os_rank(tmp));
	

	return;
}
void examin_color(void)
{
	int i;
	for (i = 0; i < 255; i++)
	{
        #if defined(_WIN32) || defined(_WIN64)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), i);
        #endif
		printf("hello %d\n", i);
	}
}

void inttree_test(void)
{
	int_tree my_int_tree;
	rbtree *my_tree = my_int_tree.get_int_tree();
	struct the_tree *T;
	struct interval tmp;

	T = my_tree->get_the_tree();

	printf("insert 15-20 \n");
	alloc_a_interval(&tmp, 15, 20);
	my_int_tree.interval_insert(&tmp);
	my_tree->rbtree_dump(T->root);

	printf("insert 9 - 11\n");
	alloc_a_interval(&tmp, 9, 11);
	my_int_tree.interval_insert(&tmp);
	my_tree->rbtree_dump(T->root);

	printf("insert 23 - 28\n");
	alloc_a_interval(&tmp, 23, 28);
	my_int_tree.interval_insert(&tmp);
	my_tree->rbtree_dump(T->root);


	printf("insert 29- 31\n");
	alloc_a_interval(&tmp, 29, 31);
	my_int_tree.interval_insert(&tmp);
	my_tree->rbtree_dump(T->root);

	printf("delete 29 - 31\n");
	alloc_a_interval(&tmp, 29, 31);
	my_int_tree.interval_delete(&tmp);
	my_tree->rbtree_dump(T->root);


	return;
}



int main(void)
{
	//queue_test();
	//link_list_test();
	//stack_test();
	//tree_test();
	//rbtree_test();
	//ostree_test();
	inttree_test();
	system("pause");
}
