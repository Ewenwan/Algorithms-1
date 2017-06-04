#include "common.h"
#include "int_tree.h"
#include "rbtree.h"

/*
 * Inorder to maintain the max value in rb-tree operations, 
 * for inseration, we only update the max filed for the structure change from rotation.(e.g. O(1))
 * and update the max value from insert node to the root later.(e.g. O(log n))
 *
 * for deletetion, we update the max field from the parent of delete node to the root
 * when the deletion complete.(e.g. O(log n)) and then update the max field only for structure change.(e.g. O(1))
*/

static void left_rotate_hook(struct rbtree_node *n)
{
	struct interval *n_i;
	struct interval *left_i;
	struct interval *right_i;
	struct interval *grand_left_i;
	struct interval *grand_right_i;

	n_i = (struct interval *)n->data;
	left_i = (struct interval *)n->left->data;
	right_i = (struct interval *)n->right->data;
	grand_left_i = (struct interval *)n->left->left->data;
	grand_right_i = (struct interval *)n->left->right->data;

	n_i->max = n_i->high;
	left_i->max = left_i->high;

	if (grand_left_i->max > left_i->max)
		left_i->max = grand_left_i->max;

	if (grand_right_i->max > left_i->max)
		left_i->max = grand_right_i->max;

	if (left_i->max > n_i->max)
		n_i->max = left_i->max;

	if (right_i->max > n_i->max)
		n_i->max = right_i->max;
	return;
}

static void right_rotate_hook(struct rbtree_node *n)
{
	struct interval *n_i;
	struct interval *left_i;
	struct interval *right_i;
	struct interval *grand_left_i;
	struct interval *grand_right_i;

	n_i = (struct interval *)n->data;
	left_i = (struct interval *)n->left->data;
	right_i = (struct interval *)n->right->data;
	grand_left_i = (struct interval *)n->left->left->data;
	grand_right_i = (struct interval *)n->left->right->data;

	n_i->max = n_i->high;
	right_i->max = right_i->high;

	if (grand_left_i->max > right_i->max)
		right_i->max = grand_left_i->max;

	if (grand_right_i->max > right_i->max)
		right_i->max = grand_right_i->max;

	if (left_i->max > n_i->max)
		n_i->max = left_i->max;

	if (right_i->max > n_i->max)
		n_i->max = right_i->max;
	return;

}

static void print_key_hook(int key, unsigned char color, void *data)
{
	struct interval* i;

	i = (struct interval*) data;

	if (color == RED)
	{
#if defined(_WIN32) || defined(_WIN64)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);
#endif
	}
	else if (color == BLACK)
	{
#if defined(_WIN32) || defined(_WIN64)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BLACK);
#endif
	}
	else if (color == WHITE)
	{
#if defined(_WIN32) || defined(_WIN64)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
#endif
	}
	else
	{
		cout << "unknow color" << endl;
		return;
	}
	cout << key <<"~"<< i->high << "|" << i->max << " ";
}

static void delete_hook(struct rbtree_node *n, struct the_tree *T)
{
	struct rbtree_node *cur = n->parent;

	while (cur != T->nil)
	{
		struct interval *i;
		struct interval *li;
		struct interval *ri;
		int max;
		i = (struct interval *)cur->data;
		li = (struct interval *)cur->left->data;
		ri = (struct interval *)cur->right->data;

		if (li->max > ri->max)
			max = li->max;
		else
			max = ri->max;

		if (max > i->max)
			i->max = max;
		else
			return;
		cur = cur->parent;
	}
}

static void insert_hook(struct rbtree_node *n, struct the_tree *T)
{
	struct rbtree_node *cur;
	cur = n;

	while (cur != T->nil)
	{
		struct interval *p_i;
		struct interval *i;
		i = (struct interval *)cur->data;
		p_i = (struct interval *)cur->parent->data;
		if (i->max > p_i->max)
		{
			p_i->max = i->max;
		}
		else
			return;
		cur = cur->parent;
	}
}



static void setup_interval(struct rbtree_node *n, struct interval *i)
{
	struct interval *int_data;

	if (n->data == nullptr)
		n->data = calloc(1, sizeof(struct interval));

	int_data = (struct interval *) n->data;
	if (i == nullptr)
	{
		int_data->low = INVALID_INTERVAL;
		int_data->high = INVALID_INTERVAL;
		int_data->max = INVALID_INTERVAL;
	}
	else
	{
		
		int_data->low = i->low;
		int_data->high = i->high;
		int_data->max = i->high;
	}
}

static rbtree_node* setup_a_cust_node(int key, unsigned char color, 
	unsigned int defsize, struct the_tree *T, void *data)
{
	struct rbtree_node *n;

	n = (struct rbtree_node *) calloc(1, sizeof(struct rbtree_node));
	n->key = key;
	n->color = color;
	setup_interval(n, (struct interval *) data);
	n->left = n->right = n->parent = T->nil;
	n->sibling = nullptr;

	return n;
}

int_tree::int_tree()
{
	int_rbtree = new rbtree();
	struct the_tree  *T= int_rbtree->get_the_tree();
	struct interval *int_data;

	T->left_rotate_hook = left_rotate_hook;
	T->right_rotate_hook = right_rotate_hook;
	T->print_key_hook = print_key_hook;
	T->delete_hook = delete_hook;
	T->insert_post_hook = insert_hook;
	T->setup_a_cust_node = setup_a_cust_node;
	T->nil->data = calloc(1,sizeof(struct interval));
	int_data = (struct interval *) T->nil->data;
	int_data->high = int_data->low = INVALID_INTERVAL;
}

int_tree::~int_tree()
{
	free(int_rbtree);
}

void int_tree::interval_insert(struct interval *i)
{
	int_rbtree->rb_insert_node(i->low, i);
}

static void print_interval(struct rbtree_node *s)
{
	struct interval* i;
	i = (struct interval*) s->data;
	printf("Hit node: %d, %d~%d,%d\n",s->key, i->low, i->high, i->max);
}

void int_tree::interval_delete(struct interval *i)
{
	struct rbtree_node *s;
	struct the_tree *T;

	T = int_rbtree->get_the_tree();
	s = interval_search(i);
	if (s != T->nil)
		int_rbtree->rb_delete_node(s);
	return;
}

static bool is_overlap(struct rbtree_node *x, struct interval *y)
{
	struct interval *x_i = (struct interval *)x->data;

	if (x_i->low <= y->high && x_i->high >= y->low)
		return true;
	else
		return false;
}

struct rbtree_node* int_tree::interval_search(struct interval *i)
{
	struct the_tree *T = int_rbtree->get_the_tree();
	struct rbtree_node *cur = T->root;
	struct interval *cur_i = (struct interval *)cur->data;

	printf("===search loop===\n");
	while (cur != T->nil && is_overlap(cur, i) == FALSE)
	{
		
		print_interval(cur);
		struct interval *left_i = (struct interval *)cur->left->data;
		if (cur->left != T->nil && left_i->max >= i->low)
		{
			cur = cur->left;
		}
		else
		{
			cur = cur->right;
		}

	}
	print_interval(cur);
	printf("===search end===\n");
	return  cur;
}
rbtree* int_tree::get_int_tree(void)
{
	return int_rbtree;
}

void alloc_a_interval(struct interval *i,int low, int high)
{
	i->low = low;
	i->max = high;
	i->high = high;
	return;
}
