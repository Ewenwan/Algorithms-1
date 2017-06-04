#ifndef __RBTREE_H__
#define __RBTREE_H__

#define BLACK 8
#define RED	12
#define WHITE 7
#define grandparent parent->parent
#define MAX_NODES 100
#define MAGIC_EMPTY_KEY -1
struct rbtree_node
{
	int key;
	struct rbtree_node *left;
	struct rbtree_node *right;
	struct rbtree_node *parent;
	unsigned char color;
	unsigned int level;
	struct rbtree_node *sibling;
	void *data;
};


struct the_tree
{
	struct rbtree_node *root;
	struct rbtree_node *nil;
	void (*insert_hook)(struct rbtree_node *n);
	void(*insert_post_hook)(struct rbtree_node *n, struct the_tree *T);
	void(*delete_hook)(struct rbtree_node *n, struct the_tree *T);
	void (*left_rotate_hook)(struct rbtree_node *n);
	void (*right_rotate_hook)(struct rbtree_node *n);
	void(*print_key_hook)(int key, unsigned char color, void *data);
	struct rbtree_node* (*setup_a_cust_node)(int key, unsigned char color, unsigned int defsize, struct the_tree *T, void *data);
};


class rbtree{
private:
	struct the_tree *T;
	struct rbtree_node **level_array;

public:
	rbtree();
	~rbtree();
	struct the_tree* get_the_tree(void);
	void rb_insert_node(int key);
	void rb_insert_node(int key, void *data);
	void rb_left_rotate(struct the_tree *T, struct rbtree_node *object);
	void rb_right_rotate(struct the_tree *T, struct rbtree_node *object);
	void rb_insert_fixup(struct the_tree *T, struct rbtree_node *z);
    void rb_delete_fixup(struct the_tree *T, struct rbtree_node *x);
    struct rbtree_node* rb_delete_node(struct rbtree_node *z);
    struct rbtree_node* rb_search(int key);
    struct rbtree_node* rb_find_successor(struct rbtree_node *z);
    struct rbtree_node* rb_find_min(struct rbtree_node  *z);
	void rbtree_dump(struct rbtree_node *root);
	void inorder_dump(void);
};
#define RBTREE_DEBUG 0
#endif

