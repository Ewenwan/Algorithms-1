#ifndef __INT_TREE_H
#define __INT_TREE_H
#include "rbtree.h"

#define INVALID_INTERVAL -1

struct interval
{
	int low;
	int high;
	int max;
};

class int_tree
{
private:
	rbtree *int_rbtree;
public:
	int_tree();
	~int_tree();
	struct rbtree_node* interval_search(struct interval *i);
	void interval_insert(struct interval *i);
	void interval_delete(struct interval *i);
	rbtree* get_int_tree(void);
};

void alloc_a_interval(struct interval *i, int low, int high);


#endif