//
//  tree.hpp
//  algorithms
//
//  Created by Lucas on 2017/4/15.
//  Copyright © 2017年 Lucas. All rights reserved.
//

#ifndef tree_hpp
#define tree_hpp

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
    struct tree_node *successor(void);
    struct tree_node *preccessor(void);
    struct tree_node *search(int key);
    struct tree_node *find_max(void);
    struct tree_node *find_min(void);
    void inorder_visit(void);
};

#endif /* tree_hpp */
