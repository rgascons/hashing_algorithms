#include <iostream>
#include <vector>
#include <list>
#include <ctime>
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
		numFoundElements = 0;
		numNotFoundElements = 0;
		numRehash = 0;
		timeTotal = 0.0;
		timeInsert = 0.0;
		timeFind = 0.0;
		rehashTime = 0.0;
		table = vector<list<unsigned int>> (_m, list<unsigned int>());
	}

	bool find(unsigned int k) {
		double t1 = clock();
		bool f = find_hash(k);
		double t2 = (clock() - t1)/double(CLOCKS_PER_SEC);
		timeTotal += t2;
		timeFind += t2;

		return f;
	}

	void insert(unsigned int k) {
		double t1 = clock();
		insert_hash(k);
		double t2 = (clock() - t1)/double(CLOCKS_PER_SEC);
		timeTotal += t2;
		timeInsert += t2;
	}

	void rehash() {
		++numRehash;
		vector<list<unsigned int>> aux = table;
		_m *= 2;
		_elements = 0;
		table = vector<list<unsigned int>> (_m, list<unsigned int>());
		for (auto& entry_list : aux) {
			for (unsigned int& e : entry_list) {
				insert_hash(e);
			}
		}
	}

	int size() {
		return _elements;
	}

	double load_factor() {
		return ((double)_elements)/((double)_m);
	}

	void printResults() {
		cout << endl << endl;
		cout << "find(k): average search time:\t" <<  double(timeTotal)/(numFoundElements+numNotFoundElements) << endl;
		cout << "find(k): total search time:\t" <<  timeFind << endl;
		cout << "find(k): number of successful queries:\t" << numFoundElements << endl;
		cout << "find(k): number of unsuccessful queries:\t" << numNotFoundElements << endl;
		cout << "insert(k): average insertion time:\t" << double(timeTotal)/(_elements) << endl;
		cout << "insert(k): total insertion time:\t" <<  timeInsert << endl;
		cout << "rehash(): number of rehashes:\t" << numRehash << endl;
		cout << "rehash(): average time of each rehash:\t" << double(rehashTime)/(numRehash) << endl;
		cout << "rehash(): average time between each rehash:\t" << double(timeTotal-rehashTime)/(numRehash) << endl;
	}

private:
	int _m;
	int _elements;
	int method;
	double _max_load;
	vector<list<unsigned int> > table;

	int numFoundElements;
	int numNotFoundElements;
	int numRehash;

	double timeTotal;
	double timeInsert;
	double timeFind;
	double rehashTime;

	bool find_hash(unsigned int k) {
		int hash = h(method, k, _m);
		list<unsigned int> *entries = &table[hash];
		for (unsigned int& e : *entries) {
			if (e == k) {
				finish(1);
				return true;
			}
		}
		finish(0);
		return false;
	}

	void insert_hash(unsigned int k) {
		if (not find_hash(k)) {
			int hash = h(method, k, _m);
			table[hash].push_back(k);
			++_elements;
			if (load_factor() > _max_load) {
				double t1 = clock();
				rehash();
				double t2 = (clock() - t1)/double(CLOCKS_PER_SEC);
				rehashTime += t2;
			}
		}
	}

	void finish(bool found) {
		if (found) {
			++numFoundElements;
		}
		else {
			++numNotFoundElements;
		}
	}
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