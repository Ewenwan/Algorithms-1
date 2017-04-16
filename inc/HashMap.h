#ifndef __HASHMAP__
#define __HASHMAP__
#include "HashEntry.h"

class HashMap{
	private:
		HashEntry **table;
	public:
		HashMap();
		~HashMap();
		int get(int key);
		void put(int key, int value);
		void remove(int key);

};
#endif