#include <iostream>
#include <vector>
#include <list>
using namespace std;


class HashTable {
public:

	// m -> mida *inicial* de la taula de hash
	HashTable(unsigned int m) {
		_m = m;
		_elements = 0;
		table = vector<list<int> > (_m, list<int>());
	}

	bool find(unsigned int value) {
		int hash = h(value);
		list<int> *entries = &table[hash];
		for (int& e : *entries) {
			if (e == value) return true;
		}
		return false;
	}

	void insert(unsigned int value) {
		if (not find(value)) {
			int hash = h(value);
			table[hash].push_back(value);
			++_elements;
		}
	}

	int size() {
		return _elements;
	}

	// Post: 0 <= h(k) < table.size()
	// Dumb hash function.
	int h(unsigned int value) {
		return value%table.size();
	}

private:
	int _m;
	int _elements;
	vector<list<int> > table;
};

int main() {
	HashTable ht(10);
	ht.insert(123456);
	ht.insert(123556);
	ht.insert(4321);	
	cout << ht.find(4321) << endl;
	cout << ht.find(4322) << endl;
	cout << ht.find(123456) << endl;
	cout << ht.size() << endl; // expected: 3
}