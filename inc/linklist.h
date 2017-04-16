#ifndef LINKLIST_H
#define LINKLIST_H
struct node{
	int data;
	struct node *next;
	struct node *prev;
};

class linklist
{
private:
	struct node *head;
public:
	linklist();
	~linklist();
	void do_insert(int data);
	struct node* do_search(int data);
	void do_delete(struct node *n);
	void do_delete_all(struct node *head);
	void do_dump_all(struct node *head);
	void do_dump_list(void);
	void do_delete_list(void);
};
#endif