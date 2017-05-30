#include "HashEntry.h"
#include "DeletedEntry.h"
#include <cstring>
#include "HashMap.h"

const int TABLE_SIZE = 128;

HashMap::HashMap() {
	table = new HashEntry*[TABLE_SIZE];
	for (int i = 0; i < TABLE_SIZE; i++)
		table[i] = NULL;
}

int HashMap::get(int key) {
		int hash = (key % TABLE_SIZE);
		int initialHash = -1;
		while ((hash != initialHash && table[hash] == (HashEntry*) DeletedEntry::getUniqueDeletedEntry()) || (table[hash] != NULL && table[hash]->getKey() != key)) {
			if (initialHash == -1)
				initialHash = hash;
			hash = (hash + 1) % TABLE_SIZE;
		}
		if (table[hash] == NULL || hash == initialHash)
			return -1;
		else
			return table[hash]->getValue();
	}

void HashMap::put(int key, int value) {
		int hash = (key % TABLE_SIZE);
		int initialHash = -1;
		int indexOfDeletedEntry = -1;
		while (((hash != initialHash ) && (table[hash] ==  DeletedEntry::getUniqueDeletedEntry())) || (table[hash] != NULL && table[hash]->getKey() != key)) {
			if (initialHash == -1)
				initialHash = hash;
			if (table[hash] == DeletedEntry::getUniqueDeletedEntry())
				indexOfDeletedEntry = hash;
			hash = (hash + 1) % TABLE_SIZE;
		}
		if ((table[hash] == NULL || hash == initialHash) && indexOfDeletedEntry
			!= -1)
			table[indexOfDeletedEntry] = new HashEntry(key, value);
        else if (initialHash != hash){
			if (table[hash] !=  DeletedEntry::getUniqueDeletedEntry()
				&& table[hash] != NULL && table[hash]->getKey() == key)
				table[hash]->setValue(value);
			else
				table[hash] = new HashEntry(key, value);
        }
}

void HashMap::remove(int key) {
		int hash = (key % TABLE_SIZE);
		int initialHash = -1;
		while (hash != initialHash && (table[hash]
			== DeletedEntry::getUniqueDeletedEntry() || (table[hash] != NULL
			&& table[hash]->getKey() != key))) {
			if (initialHash == -1)
				initialHash = hash;
			hash = (hash + 1) % TABLE_SIZE;
		}
		if (hash != initialHash && table[hash] != NULL) {
			delete table[hash];
			table[hash] = DeletedEntry::getUniqueDeletedEntry();
		}
	}

HashMap::~HashMap() {
		for (int i = 0; i < TABLE_SIZE; i++)
			if (table[i] != NULL && table[i]
				!= DeletedEntry::getUniqueDeletedEntry())
				delete table[i];
		delete[] table;
	}
