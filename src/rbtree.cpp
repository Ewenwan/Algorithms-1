#include "rbtree.h"
#include "common.h"

rbtree::rbtree()
{

	T = (the_tree*)calloc(1, sizeof(struct the_tree));
	T->nil = (rbtree_node*)calloc(1, sizeof(struct rbtree_node));

}


void rbtree::rb_left_rotate(struct the_tree *T, struct rbtree_node *object)
{
	struct rbtree_node *x = object;
	struct rbtree_node *y = x->right;

	x->right = y->left;
	if (y->left != T->nil)
	{
		y->left->parent = x;
	}
	y->parent = x->parent;

	if (x->parent == T->nil)
		T->root = y;
	else if (x == x->parent->left)
	{
		x->parent->left = y;
	}
	else
	{
		x->parent->right = y;
	}
	y->left = x;
	x->parent = y;


	return;
}

void rbtree::rb_right_rotate(struct the_tree *T, struct rbtree_node *object)
{
	struct rbtree_node *x = object;
	struct rbtree_node *y = x->left;

	x->left = y->right;
	if (y->right != T->nil)
		y->right->parent = x;

	y->parent = x->parent;

	if (x->parent == T->nil)
		T->root = y;
	else if (x == x->parent->left)
		x->parent->left = y;
	else
		x->parent->right = y;

	y->right = x;
	x->parent = y;

	return;
}

void rbtree::rb_insert_node(struct the_tree *T, int key)
{

}