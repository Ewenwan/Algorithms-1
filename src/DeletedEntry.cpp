#include "HashEntry.h"
#include <cstring>
#include "DeletedEntry.h"

DeletedEntry *DeletedEntry::entry = NULL;
DeletedEntry::DeletedEntry() : HashEntry(-1, -1) {
}

DeletedEntry *DeletedEntry::getUniqueDeletedEntry() {
	if (entry == NULL)
		entry = new DeletedEntry();
	return entry;
	
}