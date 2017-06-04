#include "rbtree.h"
#include "common.h"

rbtree::rbtree()
{

	T = (the_tree*)calloc(1, sizeof(struct the_tree));
	T->nil = (rbtree_node*)calloc(1, sizeof(struct rbtree_node));
	T->root = T->nil;
	T->nil->color = WHITE;
	T->nil->key = -1;
}

rbtree::~rbtree()
{
	free(T->nil);
	free(T);
}

struct the_tree* rbtree::get_the_tree(void)
{
	return T;
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
	if (T->left_rotate_hook)
		T->left_rotate_hook(y);

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
	if (T->right_rotate_hook)
		T->right_rotate_hook(y);
	return;
}

void rbtree::rb_insert_node(int key)
{
	struct rbtree_node *x = T->root;
	struct rbtree_node *y = T->nil;
	struct rbtree_node *node;

	if (T->setup_a_cust_node)
		node = T->setup_a_cust_node(key, RED, 1, T, nullptr);
	else
	{
		node = (struct rbtree_node *)calloc(1, sizeof(rbtree_node));
		node->key = key;
		node->color = RED;
		node->left = T->nil;
		node->right = T->nil;
	}



	while (x != T->nil)
	{
		y = x;
		if (key > x->key)
			x = x->right;
		else
			x = x->left;

		if (T->insert_hook)
			T->insert_hook(y);
	}

	node->parent = y;
	if (y == T->nil)
		T->root = node;
	else if (key > y->key)
		y->right = node;
	else
		y->left = node;


	rb_insert_fixup(T,node);

}


void rbtree::rb_insert_node(int key, void *data)
{
	struct rbtree_node *x = T->root;
	struct rbtree_node *y = T->nil;
	struct rbtree_node *node;

	if (T->setup_a_cust_node)
		node = T->setup_a_cust_node(key, RED, 1, T, data);
	else
	{
		node = (struct rbtree_node *)calloc(1, sizeof(rbtree_node));
		node->key = key;
		node->color = RED;
		node->left = T->nil;
		node->right = T->nil;
	}



	while (x != T->nil)
	{
		y = x;
		if (key > x->key)
			x = x->right;
		else
			x = x->left;

		if (T->insert_hook)
			T->insert_hook(y);
	}

	node->parent = y;
	if (y == T->nil)
		T->root = node;
	else if (key > y->key)
		y->right = node;
	else
		y->left = node;

	rb_insert_fixup(T, node);
	if (T->insert_post_hook)
		T->insert_post_hook(node, T);


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
				z->grandparent->color = RED;
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

struct rbtree_node* rbtree::rb_delete_node(struct rbtree_node *z)
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
    
	if (T->delete_hook)
		T->delete_hook(y, T);

	if (y->color == BLACK){
		rb_delete_fixup(T, x);
#if RBTREE_DEBUG
		printf("x %d, %d\n",x->key,x->color);
		printf("y %d, %d\n", y->key, y->color);
#endif
	}
    
    return y;
    
}

struct rbtree_node* rbtree::rb_find_successor(struct rbtree_node *z)
{
    struct rbtree_node *parent = z->parent;
    struct rbtree_node *cur = z;
    
    if(z->right != T->nil)
        return rb_find_min(z->right);
    else
    {
        while(parent!=T->nil && parent->right ==cur)
        {
            cur = parent;
            parent = cur->parent;
        }
        if(parent == nullptr)
            return nullptr;
        else
            return parent;

    }
}


struct rbtree_node* rbtree::rb_find_min(struct rbtree_node *z)
{
    if(z->left == T->nil)
    {
        return z;
    }
    
    return rb_find_min(z->left);
}

static void attach_node_to_level(struct rbtree_node *n, unsigned int level, struct rbtree_node **level_array)
{
	struct rbtree_node *cur;
	struct rbtree_node *parent = nullptr;

	cur = level_array[level];
	n->level = level;

	while (cur != nullptr)
	{
		parent = cur;
		cur = cur->sibling;
	}

	if (parent == nullptr)
		level_array[level] = n;	
	else
		parent->sibling = n;

	n->sibling = nullptr;

}

static void setup_level_array(struct rbtree_node *n, struct rbtree_node *parent, struct the_tree *T, struct rbtree_node **level_array)
{
	struct rbtree_node *empty;

	if (n == T->root)
	{
		attach_node_to_level(n, 0, level_array);
	}
	else if (n == T->nil)
	{


		if (T->setup_a_cust_node)
		{
			empty = T->setup_a_cust_node(MAGIC_EMPTY_KEY, WHITE, 0, T, nullptr);
		}
		else
		{
			empty = (struct rbtree_node *)calloc(1, sizeof(struct rbtree_node));
			empty->key = MAGIC_EMPTY_KEY;
			empty->color = WHITE;
		}
		attach_node_to_level(empty, parent->level + 1, level_array);
		return;
	}
	else
	{
		attach_node_to_level(n, parent->level + 1, level_array);
	}
	setup_level_array(n->left, n, T, level_array);
	setup_level_array(n->right, n, T, level_array);
}

static void print_key(int key, unsigned char color)
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

	cout << key << " ";

}

static void dump_list(struct rbtree_node *node, struct the_tree *T)
{
	if (node != nullptr)
	{
		if (T->print_key_hook)
			T->print_key_hook(node->key , node->color, node->data);
		else
			print_key(node->key, node->color);
		dump_list(node->sibling, T);
	}
	return;
}


void rbtree::rbtree_dump(struct rbtree_node *root)
{
	int i = 0;
	level_array = (struct rbtree_node **)calloc(MAX_NODES, sizeof(struct rbtree_node*));
	setup_level_array(T->root, nullptr, T, level_array);

	printf("===rbtree dump===\n");
	while (level_array[i] != nullptr)
	{
		dump_list(level_array[i], this->T);
		cout << endl;
		i = i + 1;
	}
	printf("=======end=======\n\n");

	free(level_array);
	return ;
}

struct rbtree_node* rbtree::rb_search(int key)
{
	struct rbtree_node *cur;
	cur = T->root;
	while (cur != T->nil)
	{
		if (key > cur->key)
			cur = cur->right;
		else if (key < cur->key)
			cur = cur->left;
		else
			break;
	}

	return cur;
}

static void __inorder_dump(struct rbtree_node *n, struct the_tree *T)
{
	if (n == T->nil)
		return;

	__inorder_dump(n->left, T);
	printf("%d ", n->key);
	__inorder_dump(n->right, T);
	return;
}

void rbtree::inorder_dump(void)
{
	__inorder_dump(T->root, T);
	cout << endl;
}











