#include "OrderStaticTree.h"
#include "common.h"

static void left_rotate_hook(struct rbtree_node *n)
{
	*((unsigned int *)n->data) = *((unsigned int *)n->left->data);
	*((unsigned int *)n->left->data) = *((unsigned int *)n->left->left->data) + *((unsigned int *)n->left->right->data) + 1;
}
static void right_rotate_hook(struct rbtree_node *n)
{
	*((unsigned int *)n->data) = *((unsigned int *)n->right->data);
	*((unsigned int *)n->right->data) = *((unsigned int *)n->right->left->data) + *((unsigned int *)n->right->right->data) + 1;
}

static void insert_hook(struct rbtree_node *n)
{
	unsigned int *size;

	if (n->data == nullptr)
	{
		n->data = calloc(1, sizeof(unsigned int));

	}
	size = (unsigned int *)n->data;
	*size = *size + 1;
}

static void delete_hook(struct rbtree_node *n, struct the_tree *T)
{
	struct rbtree_node *p;
	p = n->parent;
	while (p != T->nil)
	{
		unsigned int *size;
		size = (unsigned int *)p->data;
		*size = *size - 1;
		p = p->parent;
	}
}

static void print_key_hook(int key, unsigned char color, void *data)
{
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
	cout << key << "|" << *(unsigned int *)data <<" ";

}

static struct rbtree_node* setup_os_node(int key, unsigned char color, unsigned int defsize, struct the_tree *T, void *data)
{
	struct rbtree_node* node = (struct rbtree_node *) calloc(1, sizeof(rbtree_node));
	node->left = node->right = node->parent = T->nil;
	node->sibling = nullptr;
	node->color = color;
	node->level = 0;
	node->key = key;
	node->data = calloc(1, sizeof(unsigned int));
	*(unsigned int *)(node->data) = defsize;
	return node;
}


rbtree* os_tree::get_the_os_tree(void)
{
	return this->ostree;
}

struct rbtree_node* os_tree::os_select(struct rbtree_node *root, unsigned int rank)
{
	unsigned int r;
	r = *(unsigned int *)root->left->data + 1;

	if (rank == r)
	{
		return root;
	}
	else 
	{
		if (rank > r)
			return os_select(root->right, rank - r);
		else
			return os_select(root->left, rank);
	}
}

unsigned int os_tree::os_rank(struct rbtree_node *s)
{
	unsigned int r;
	struct the_tree *T;

	T = ostree->get_the_tree();
	
	r = *(unsigned int *)s->left->data + 1;
	while (s->parent != T->nil)
	{
		if (s == s->parent->right)
			r = r + *(unsigned int *)s->parent->left->data + 1;
		s = s->parent;
	}
	return r;
}


os_tree::os_tree()
{
	struct the_tree* T;
	ostree = new rbtree();
	T = ostree->get_the_tree();
	T->insert_hook = insert_hook;
	T->delete_hook = delete_hook;
	T->left_rotate_hook = left_rotate_hook;
	T->right_rotate_hook = right_rotate_hook;
	T->print_key_hook = print_key_hook;
	T->root->data = calloc(1, sizeof(int));
	T->nil->data = calloc(1, sizeof(int));
	T->setup_a_cust_node = setup_os_node;
	*(unsigned int *)(T->root->data) = 0;
	*(unsigned int *)(T->nil->data) = 0;
}

os_tree::~os_tree()
{
	free(ostree);
}
