#include <iostream>
#include <bitset>
#include "hash_functions.cc"
using namespace std;

class BloomFilter {

// Atenció:
// Therefore, to maintain a fixed false positive probability, 
// the length of the Bloom table must grow linearly with n.
private:
	
	int method1;
	int method2;

public:
	
	BloomFilter(int f1, int f2) {
		this->method1 = f1;
		this->method2 = f2;
	}

	bool find(unsigned int k) {
		return T[h(method1, k, T.size())] 
				and T[h(method2, k, T.size())];
	}

	void insert(unsigned int k) {
		T.set(h(method1, k, T.size()));
		T.set(h(method2, k, T.size()));
	}

	// Post: 0 <= h(k) < T.size()
	// Dumb hash function.
	//int h(unsigned int k) {
	//	return k%T.size();
	//}

	void print() {
		cout << T << endl;
	}

private:
	bitset<200> T;
};

int main() {
	BloomFilter bf(DIVISION_KNUTH, MULT_METHOD);
	bf.print();
	bf.insert(123456);
	bf.print();
	bf.insert(123556);
	bf.print();
	bf.insert(4321);	
	cout << bf.find(4321) << endl;
	cout << bf.find(4322) << endl;
	bf.print();
}