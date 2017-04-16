#ifndef __DELETEDENTRY__
#define __DELETEDENTRY__
#include <cstring>

class DeletedEntry : public HashEntry {
private:
	static DeletedEntry *entry;
	DeletedEntry();
public:
	static DeletedEntry *getUniqueDeletedEntry();
};
#endif