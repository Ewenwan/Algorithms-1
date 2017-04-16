#include "common.h"
#include "linklist.h"

linklist::linklist(){
	head = NULL;
}
linklist::~linklist(){
	cout << "~linklist:" << endl;
	do_delete_all(this->head);
}

void linklist::do_insert(int data)
{
	struct node *new_node = (struct node *)malloc(sizeof(struct node));
	new_node->next = head;
	if (this->head != NULL)
		this->head->prev = new_node;
	new_node->data = data;
	new_node->prev = NULL;
	this->head = new_node;

}

void linklist::do_delete(struct node *n)
{
	if (n->prev != NULL)
		n->prev->next = n->next;
	else
		this->head = n->next;

	if (n->next != NULL)
		n->next->prev = n->prev;
}

struct node* linklist::do_search(int data)
{
	struct node *element = this->head;
	while (element != NULL && element->data != data)
		element = element->next;
	return element;
}


void linklist::do_delete_all(struct node *head)
{
	if (head != NULL)
	{
		do_delete_all(head->next);
	}
	else
	{
		cout << "Delete:";
		return;
	}
	cout << setw(3) << head->data;
	if (head->prev == NULL)
		cout << endl;
	delete head;
	head = NULL;
	return;
}

void linklist::do_delete_list(void)
{
	do_delete_all(this->head);
}


void linklist::do_dump_all(struct node *head)
{
	if (head == NULL)
	{
		cout << endl;
		return;
	}
	else
	{
		if (head->prev == NULL)
			cout << "List: ";
		cout << setw(3) << head->data;
		do_dump_all(head->next);
	}
}
void linklist::do_dump_list(void)
{
	do_dump_all(this->head);
}
