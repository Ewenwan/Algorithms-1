#ifndef __RBTREE_H__
#define __RBTREE_H__

#define BLACK 0
#define RED	1
#define grandparent parent->parent

struct rbtree_node
{
	int key;
	struct rbtree_node *left;
	struct rbtree_node *right;
	struct rbtree_node *parent;
	unsigned char color;

};

struct the_tree
{
	struct rbtree_node *root;
	struct rbtree_node *nil;
};


class rbtree{
private:
	struct the_tree *T;

public:
	rbtree();
	~rbtree();
	void rb_insert_node(struct the_tree *T, int key);
	void rb_left_rotate(struct the_tree *T, struct rbtree_node *object);
	void rb_right_rotate(struct the_tree *T, struct rbtree_node *object);
	void rb_insert_fixup(struct the_tree *T, struct rbtree_node *z);
    struct rbtree_node* rb_delete_node(struct the_tree *T, int key);
    void rb_delete_fixup(struct the_tree *T, struct rbtree_node *x);
    struct rbtree_node* rb_delete_node(struct the_tree *T, struct rbtree_node *z);
    struct rbtree_node* rb_search(int key);
    struct rbtree_node* rb_find_successor(struct rbtree_node *z);
};

#endif

