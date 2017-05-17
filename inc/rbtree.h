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
};


struct the_tree
{
	struct rbtree_node *root;
	struct rbtree_node *nil;
};

static void setup_level_array(struct rbtree_node *n, struct rbtree_node *parent, struct the_tree *T, struct rbtree_node **level_array);
static void attach_node_to_level(struct rbtree_node *n, unsigned int level, struct rbtree_node **level_array);
static void dump_level_node(struct rbtree_node **level_array, unsigned int level);
static void dump_list(struct rbtree_node *node);
static void print_key(int key, unsigned char color);

class rbtree{
private:
	struct the_tree *T;
	struct rbtree_node **level_array;

public:
	rbtree();
	~rbtree();
	struct the_tree* get_the_tree(void);
	void rb_insert_node(int key);
	void rb_left_rotate(struct the_tree *T, struct rbtree_node *object);
	void rb_right_rotate(struct the_tree *T, struct rbtree_node *object);
	void rb_insert_fixup(struct the_tree *T, struct rbtree_node *z);
    struct rbtree_node* rb_delete_node(int key);
    void rb_delete_fixup(struct the_tree *T, struct rbtree_node *x);
    struct rbtree_node* rb_delete_node(struct rbtree_node *z);
    struct rbtree_node* rb_search(int key);
    struct rbtree_node* rb_find_successor(struct rbtree_node *z);
    struct rbtree_node* rb_find_min(struct rbtree_node  *z);
    void rbtree_dump(struct rbtree_node *root);
};
#define RBTREE_DEBUG 0
#endif

