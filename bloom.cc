#include <iostream>
#include <bitset>
using namespace std;

class BloomFilter {

// Atenció:
// Therefore, to maintain a fixed false positive probability, 
// the length of the Bloom table must grow linearly with n.

public:
	
	// Inicialitzar T segons els parametres donats
	// BloomFilter(int m, int k) {
		// m -> mida de la taula de bloom (nombre de bits)
		// k -> quantitat de funcions de hash a usar
		// 		(entre 1 i 3-4-les que siguin). 
		//  	S'hauria de poder triar quines usar?

	// }

	bool find(unsigned int k) {
		return T[h(k)];
	}

	void insert(unsigned int k) {
		T.set(h(k));
	}

	// Post: 0 <= h(k) < T.size()
	// Dumb hash function.
	int h(unsigned int k) {
		return k%T.size();
	}

	void print() {
		cout << T << endl;
	}

private:
	bitset<31> T;
};

int main() {
	BloomFilter bf;
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