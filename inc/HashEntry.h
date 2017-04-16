#ifndef __HASHENTRY__
#define __HASHENTRY__
class HashEntry{
	private:
		int key;
		int value;
	public:
		HashEntry(int key, int value);
		int getKey();
		int getValue();
		void setValue(int value);
};

#endif