#include <iostream>
#include <vector>
#include <list>
#include "hash_functions.h"
using namespace std;


class HashTable {
public:

	// m -> mida *inicial* de la taula de hash
	HashTable(unsigned int m) {
		_m = m;
		_elements = 0;
		table = vector<list<unsigned int> > (_m, list<unsigned int>());
	}

	bool find(unsigned int k) {
		int hash = h(k);
		list<unsigned int> *entries = &table[hash];
		for (unsigned int& e : *entries) {
			if (e == k) return true;
		}
		return false;
	}

	void insert(unsigned int k) {
		if (not find(k)) {
			int hash = h(k);
			table[hash].push_back(k);
			++_elements;
		}
	}

	int size() {
		return _elements;
	}

	int load_factor() {
		return _elements/_m;
	}

	int h(unsigned int k) {
		return division_method(k, _m);
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