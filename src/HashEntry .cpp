#include "HashEntry.h"

HashEntry::HashEntry(int key, int value) {
	this->key = key;
	this->value = value;
}

int HashEntry::getKey() {
	return key;
}

int HashEntry::getValue() {
	return value;
}

void HashEntry::setValue(int value) {
	this->value = value;
}
