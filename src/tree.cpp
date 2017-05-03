#include "tree.hpp"
#include "common.h"


tree::tree():root(nullptr){
    return;
}

tree::~tree()
{
	return;
}

void tree::insert_node(int key){
    struct tree_node *new_node = nullptr;
    struct tree_node *parent = nullptr;
    struct tree_node *current = nullptr;
    
    new_node = (tree_node*) malloc(sizeof(tree_node));
    new_node->key = key;
    new_node->right=nullptr;
    new_node->left=nullptr;
    new_node->parent=nullptr;

    for(current = root; current!=nullptr;)
    {
        parent = current;
        if(new_node->key < current->key)
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
    }
    new_node->parent=parent;
    if(parent == nullptr)
    {
        root = new_node;
    }
    else
    {
        if(new_node->key < parent->key)
            parent->left = new_node;
        else
            parent->right = new_node;
    }
    return;
}

struct tree_node* tree::get_root(void)
{
	return this->root;
}



struct tree_node* tree::search_node(struct tree_node *subtree, int key)
{
	if (subtree->key == key || subtree == nullptr)
		return subtree;

	if (key > subtree->key)
		return search_node(subtree->right, key);
	else
		return search_node(subtree->left, key);

}

struct tree_node* tree::find_max(struct tree_node *subtree)
{
	if (subtree->right == nullptr)
		return subtree;
	return find_max(subtree->right);
}

struct tree_node* tree::find_min(struct tree_node *subtree)
{
	if (subtree->left == nullptr)
		return subtree;
	return find_min(subtree->left);
}

struct tree_node* tree::successor(struct tree_node *node)
{
	struct tree_node* current = node;
	struct tree_node* parent = node->parent;
	if (node->right != nullptr)
		return find_min(node->right);
	else
	{
		while (parent != 0 && current == parent->right)
		{
			current = parent;
			parent = parent->parent;
		}
		return parent;
	}
}



struct tree_node* tree::delete_node(struct tree_node *deleted_node)
{
    tree_node* abstract_node = nullptr;
    tree_node* child = nullptr;
    
    if(root->left == nullptr || root->right == nullptr)
    {
        abstract_node = deleted_node;
    }
    else
    {
        abstract_node = successor(deleted_node);
    }

    if(abstract_node ->left != nullptr)
    {
        child = abstract_node->left;
    }
    else
    {
        child = abstract_node->right;
    }
    
    if(child != nullptr)
    {
        child->parent = abstract_node->parent;
    }
    
    if(abstract_node->parent==nullptr)
    {
        root = child;
    }
    else{
        if(abstract_node == abstract_node->parent->left)
            abstract_node->parent->left = child;
        else
            abstract_node->parent->right= child;
    }
    if(abstract_node != deleted_node)
        deleted_node->key = abstract_node->key;
    
    return abstract_node;
}

void tree::inorder_visit(struct tree_node *subtree)
{

	if (subtree != nullptr)
	{
		inorder_visit(subtree->left);
		cout << subtree->key <<" ";
		inorder_visit(subtree->right);
	}

	return;
}
