#include "OrderStaticTree.h"
#include "common.h"

static void left_rotate_hook(struct rbtree_node *n)
{
}
static void right_rotate_hook(struct rbtree_node *n)
{

}

static void insert_hook(struct rbtree_node *n)
{
	unsigned int *size;

	if (n->data == nullptr)
	{
		n->data = malloc(sizeof(int));
	}
	size = (unsigned int *)n->data;
	*size = *size + 1;
}

static void delete_hook(struct rbtree_node *n)
{

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

	T->root->data = 0;
}

os_tree::~os_tree()
{
	free(ostree);
}