#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

class CuckooHash {
public:
	CuckooHash(unsigned int m) {
		m1 = m2 = m;
		max_loop = m*2;
		_elements = 0;
		t1 = vector<unsigned int> (m1, 0);
		t2 = vector<unsigned int> (m2, 0);
	}

	bool find (unsigned int k) {
		int hash1 = h1(k);
		if (t1[hash1] == k) return true;
		int hash2 = h2(k);
		if (t2[hash2] == k) return true;
		return false;
	}

	void insert(unsigned int k) {
		if (not find(k)) {
			for (int it = 0; it < max_loop; ++it) {
				int hash = h1(k);
				if (t1[hash] == 0) {t1[hash] = k; ++_elements; return;}
				else {
					int e = t1[hash];
					t1[hash] = k;
					hash = h2(e);
					if (t2[hash] == 0) {t2[hash] = e; ++_elements; return;}
					else {
						k = t2[hash];
						t2[hash] = e;
					}
				}
			}
			rehash();
			insert(k);
		}
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
				insert(aux1[i]);
			}
		}
		for (int i = 0; i < aux2.size(); ++i) {
			if (aux2[i] != 0) {
				insert(aux2[i]);
			}
		}
	}

	int size() {
		return _elements;
	}

	int h1(unsigned int k) {
		return k%m1;
	}

	int h2(unsigned int k) {
		double d = ((double)k)/((double)m2);
		return ((int)ceil(d))%m2;
	}

private:
	int m1;
	int m2;
	int _elements;
	int max_loop;

	vector<unsigned int> t1;
	vector<unsigned int> t2;


};

int main() {
	CuckooHash c(10);
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