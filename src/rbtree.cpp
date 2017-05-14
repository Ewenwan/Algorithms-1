#include "rbtree.h"
#include "common.h"

rbtree::rbtree()
{

	T = (the_tree*)calloc(1, sizeof(struct the_tree));
	T->nil = (rbtree_node*)calloc(1, sizeof(struct rbtree_node));
	T->root = T->nil;

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
	struct rbtree_node *x = T->root;
	struct rbtree_node *y = T->nil;
	struct rbtree_node *node = (struct rbtree_node *)malloc(sizeof(rbtree_node));

	while (x != T->nil)
	{
		y = x;
		if (key > x->key)
			x = x->right;
		else
			x = x->left;
	}
	node->parent = y;
	if (y == T->nil)
		T->root = node;
	else if (key > y->key)
		y->right = node;
	else
		y->left = node;

	node->key = key;
	node->color = RED;
	node->left = T->nil;
	node->right = T->nil;
	rb_insert_fixup(T,node);

}

void rbtree::rb_insert_fixup(struct the_tree *T, struct rbtree_node *z)
{
	struct rbtree_node *y = nullptr;

	while (z->parent->color == RED)
	{
		if (z->parent == z->grandparent->left)
		{
			y = z->grandparent->right;
			if (y->color == RED)   //why don't use y!=T.nil. need to tink
			{
				z->grandparent->left->color = BLACK;
				z->grandparent->right->color = BLACK;
				z->grandparent->color = RED;
				z = z->grandparent;
			}
			else
			{
				if (z == z->parent->right)
                {
					z = z->parent;
					rb_left_rotate(T, z);
				}
				z->parent->color = BLACK;
				z->grandparent->color = RED;
				rb_right_rotate(T,z->grandparent);
			}


		}
		else
		{
			y = z->grandparent->left;
			if (y->color == RED)
			{
				z->grandparent->left->color = BLACK;
				z->grandparent->right->color = BLACK;
				z->grandparent->color = RED;
				z = z->grandparent;
			}
			else
			{
				if (z == z->parent->left)
				{
					z = z->parent;
					rb_right_rotate(T, z);
				}
				z->parent->color = BLACK;
				z->grandparent->left->color = RED;
				rb_left_rotate(T, z->grandparent);
			}

		}
	}
	T->root->color = BLACK;
}

void rbtree::rb_delete_fixup(struct the_tree *T, struct rbtree_node *x)
{
    struct rbtree_node *w;
    
    while(x != T->root && x->color==BLACK)
    {
        if(x==x->parent->left)
        {
            w = x->parent->right;
            if(w->color == RED) //CASE 1
            {
                w->color = BLACK;
                x->parent->color = RED;
                rb_left_rotate(T,x->parent);
                w = x->parent->right;
            }
            else
            {
                if(w->right->color == BLACK && w->left->color== BLACK)
                {
                    w->color = RED;
                    x = x->parent;
                }
                else
                {
                    if(w->right->color == BLACK && w->left->color == RED)
                    {
                        w->color=RED;
                        w->left->color=BLACK;
                        rb_right_rotate(T,w);
                        w=x->parent->right;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->right->color=BLACK;
                    rb_left_rotate(T, w->parent);
                    x=T->root;
                }
            }
        }
        else
        {
            w = x->parent->left;
            if(w->color == RED)
            {
                w->color = BLACK;
                w->parent->color = RED;
                rb_right_rotate(T,x->parent);
                w = x->parent->left;
            }
            else if(w->left->color == BLACK && w->left->color == BLACK)
            {
                w->color = RED;
                x = x->parent;
            }
            else
            {
                if(w->left->color == BLACK)
                {
                    w->right->color = BLACK;
                    w->color = RED;
                    rb_left_rotate(T,w);
                    w = x->parent->left;
                }
                w->color = w->parent->color;
                w->parent->color = BLACK;
                w->left->color = BLACK;
                rb_right_rotate(T, w->parent);
                x = T->root;
            }
        }
    }
    x->color = BLACK;
}

struct rbtree_node* rbtree::rb_delete_node(struct the_tree *T, struct rbtree_node *z)
{
    struct rbtree_node *y;
    struct rbtree_node *x;
    
    if(z->left==T->nil || z->right == T->nil)
    {
        y = z;
    }
    else
    {
        y = rb_find_successor(z);
    }
    
    if(y->left != T->nil)
        x = y->left;
    else
        x = y->right;
    
    x->parent = y->parent;  //it means T->NIL may contains y's parent;
    
    if(y->parent == T->nil)
        T->root = x;
    else if(y == y->parent->left)
        y->parent->left= x;
    else
        y->parent->right = x;
    

    if(y != z)
        z->key = y->key;
    
    if(y->color == BLACK)
        rb_delete_fixup(T,x);
    
    return y;
    
}

struct rbtree_node* rbtree::rb_find_successor(struct rbtree_node *z)
{
    return z;
}


