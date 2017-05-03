#ifndef __TREE_H__
#define __TREE_H__

#include <stdio.h>

struct tree_node
{
    int key;
    struct tree_node *left;
    struct tree_node *right;
    struct tree_node *parent;
    
};

class tree{
private:
    struct tree_node *root;
public:
    tree();
    ~tree();
    void insert_node(int key);
    struct tree_node *delete_node(struct tree_node *deleted_node);
	struct tree_node *search_node(struct tree_node *subtree, int key);
    struct tree_node *successor(struct tree_node *node);
    struct tree_node *find_max(struct tree_node *subtree);
    struct tree_node *find_min(struct tree_node *subtree);
    void inorder_visit(struct tree_node *subtree);
	struct tree_node *get_root(void);

};

#endif /* tree_hpp */
