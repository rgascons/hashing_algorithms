#include <iostream>
#include <vector>
#include <math.h>
#include <ctime>
#include "hash_functions.cc"
using namespace std;

class CuckooHash {
public:
	CuckooHash(unsigned int m, int f1, int f2) {
		m1 = m2 = m;
		max_loop = m*2;
		_elements = 0;
		method1 = f1;
		method2 = f2;
		t1 = vector<unsigned int> (m1, 0);
		t2 = vector<unsigned int> (m2, 0);
		numFoundElements = 0;
		numNotFoundElements = 0;
		numRehash = 0;
		numBounces = 0;
		timeTotal = 0.0;
		timeInsert = 0.0;
		timeFind = 0.0;
		rehashTime = 0.0;
	}

	bool find(unsigned int k) {
		double t1 = clock();
		bool f = find_cuckoo(k);
		double t2 = (clock() - t1)/double(CLOCKS_PER_SEC);
		timeTotal += t2;
		timeFind += t2;

		return f;
	}

	void insert(unsigned int k) {
		double t1 = clock();
		insert_cuckoo(k);
		double t2 = (clock() - t1)/double(CLOCKS_PER_SEC);
		timeTotal += t2;
		timeInsert += t2;
	}

	void rehash() {
		vector<unsigned int> aux1 = t1;
		vector<unsigned int> aux2 = t2;
		m1 = m2 = m1*2;
		t1 = vector<unsigned int> (m1, 0);
		t2 = vector<unsigned int> (m2, 0);
		_elements = 0;
		max_loop = m1*2;
		for (int i = 0; i < aux1.size(); ++i) {
			if (aux1[i] != 0) {
				insert_cuckoo(aux1[i]);
			}
		}
		for (int i = 0; i < aux2.size(); ++i) {
			if (aux2[i] != 0) {
				insert_cuckoo(aux2[i]);
			}
		}
	}

	int size() {
		return _elements;
	}

	void printResults() {
		cout << endl << endl;
		cout << "find(k): average search time:\t" <<  double(timeTotal)/(numFoundElements+numNotFoundElements) << endl;
		cout << "find(k): total search time:\t" <<  timeFind << endl;
		cout << "find(k): number of successful queries:\t" << numFoundElements << endl;
		cout << "find(k): number of unsuccessful queries:\t" << numNotFoundElements << endl;
		cout << "insert(k): average insertion time:\t" << double(timeTotal)/(_elements) << endl;
		cout << "insert(k): total insertion time:\t" <<  timeInsert << endl;
		cout << "insert(k): total number of bounces:\t" << numBounces << endl;
		cout << "rehash(): number of rehashes:\t" << numRehash << endl;
		cout << "rehash(): average time of each rehash:\t" << double(rehashTime)/(numRehash) << endl;
		cout << "rehash(): average time between each rehash:\t" << double(timeTotal-rehashTime)/(numRehash) << endl;
	}

private:
	int m1;
	int m2;
	int _elements;
	int max_loop;
	int method1;
	int method2;

	vector<unsigned int> t1;
	vector<unsigned int> t2;

	int numFoundElements;
	int numNotFoundElements;
	int numRehash;
	int numBounces;

	double timeTotal;
	double timeInsert;
	double timeFind;
	double rehashTime;

	void finish(bool found) {
		if (found) {
			++numFoundElements;
		}
		else {
			++numNotFoundElements;
		}
	}

	void insert_cuckoo(unsigned int k) {
		if (not find_cuckoo(k)) {
			for (int it = 0; it < max_loop; ++it) {
				int hash = h(method1, k, m1);
				if (t1[hash] == 0) {t1[hash] = k; ++_elements; return;}
				else {
					++numBounces;
					int e = t1[hash];
					t1[hash] = k;
					hash = h(method2, e, m2);
					if (t2[hash] == 0) {t2[hash] = e; ++_elements; return;}
					else {
						++numBounces;
						k = t2[hash];
						t2[hash] = e;
					}
				}
			}
			double t1 = clock();
			rehash();
			double t2 = (clock() - t1)/double(CLOCKS_PER_SEC);
			rehashTime += t2;
			insert_cuckoo(k);
		}
	}

	bool find_cuckoo(unsigned int k) {
		int hash1 = h(method1, k, m1);
		if (t1[hash1] == k) return true;
		int hash2 = h(method2, k, m2);
		if (t2[hash2] == k) return true;
		return false;
	}


};

int main() {
	CuckooHash c(10, DIVISION_KNUTH, MULT_METHOD);
	c.insert(5);
	cout << c.find(5) << endl;
	cout << c.find(10) << endl;
	c.insert(25);
	cout << c.size() << endl;
	cout << c.find(5) << " " << c.find(25) << endl;
	c.insert(125);
	cout << c.size() << endl;
	cout << c.find(5) << " " << c.find(25) << " " << c.find(125) << endl;
	c.insert(2);
	c.insert(4);
	c.insert(6);
	c.insert(8);
	c.insert(10);
	c.insert(12);
	c.insert(14);
	c.insert(16);
	cout << c.size() << endl; //expected = 11
}