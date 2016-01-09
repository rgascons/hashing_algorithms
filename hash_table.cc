#include <iostream>
#include <vector>
#include <list>
#include "hash_functions.cc"
using namespace std;


class HashTable {
public:

	// m -> mida *inicial* de la taula de hash
	HashTable(unsigned int m, double max_load, int f) {
		_m = m;
		_elements = 0;
		_max_load = max_load;
		method = f;
		table = vector<list<unsigned int>> (_m, list<unsigned int>());
	}

	bool find(unsigned int k) {
		int hash = h(method, k, _m);
		list<unsigned int> *entries = &table[hash];
		for (unsigned int& e : *entries) {
			if (e == k) return true;
		}
		return false;
	}

	void insert(unsigned int k) {
		if (not find(k)) {
			int hash = h(method, k, _m);
			table[hash].push_back(k);
			++_elements;
			if (load_factor() > _max_load) rehash();
		}
	}

	void rehash() {
		vector<list<unsigned int>> aux = table;
		_m *= 2;
		_elements = 0;
		table = vector<list<unsigned int>> (_m, list<unsigned int>());
		for (auto& entry_list : aux) {
			for (unsigned int& e : entry_list) {
				insert(e);
			}
		}
	}

	int size() {
		return _elements;
	}

	double load_factor() {
		return ((double)_elements)/((double)_m);
	}

private:
	int _m;
	int _elements;
	int method;
	double _max_load;
	vector<list<unsigned int> > table;
};

int main() {
	HashTable ht(10, 0.75, DIVISION_METHOD);
	ht.insert(123456);
	ht.insert(123556);
	ht.insert(4321);	
	cout << ht.find(4321) << endl;
	cout << ht.find(4322) << endl;
	cout << ht.find(123456) << endl;
	cout << ht.size() << endl; // expected: 3
}