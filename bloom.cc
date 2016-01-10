#include <iostream>
#include <bitset>
#include "hash_functions.cc"
#include <ctime>
#include <fstream>
#include <cstdlib>
using namespace std;

class BloomFilter {

// Atenció:
// Therefore, to maintain a fixed false positive probability, 
// the length of the Bloom table must grow linearly with n.
private:
	
	int method1;
	int method2;

	int numCallsH1H2;
	int numFoundElements;
	int numNotFoundElements;
	int numAlmostFoundElements;
	double timeFind;
	double timeInsert;
	int nElements;

public:
	
	BloomFilter(int f1, int f2, const int m) {
		T = vector<bool>(m, false);
		method1 = f1;
		method2 = f2;
		nElements = 0;
		numCallsH1H2 = 0;
		numFoundElements = 0;
		numNotFoundElements = 0;
		numAlmostFoundElements = 0;
		timeFind = timeInsert = 0.0;
	}

	bool find(unsigned int k) {
		numCallsH1H2 += 2;
		double t1 = clock();
		bool b1 = T[h(method1, k, T.size())];
		bool b2 = T[h(method2, k, T.size())];
		bool found = b1 and b2;
		double t2 = (clock() - t1)/double(CLOCKS_PER_SEC);
		timeFind += t2;
		if (found) ++numFoundElements;
		if (b1 != b2) ++numAlmostFoundElements;
		else ++numNotFoundElements;
		return found;
	}

	void insert(unsigned int k) {
		numCallsH1H2 += 2;
		++nElements;
		double t1 = clock();
		T[h(method1, k, T.size())];
		T[h(method2, k, T.size())];
		double t2 = (clock() - t1)/double(CLOCKS_PER_SEC);
		timeInsert += t2;
	}

	void printResults() {
		cout << endl << endl;
		cout << "find(k): average search time:\t" <<  double(timeFind)/(numFoundElements+numNotFoundElements) << endl;
		cout << "find(k): total search time:\t" <<  timeFind << endl;
		cout << "find(k): number of successful queries:\t" << numFoundElements << endl;
		cout << "find(k): number of unsuccessful queries:\t" << numNotFoundElements << endl;
		cout << "insert(k): average insertion time:\t" << double(timeInsert)/(nElements) << endl;
		cout << "insert(k): total insertion time:\t" <<  timeInsert << endl;
		cout << "insert(k): number of elements:\t" << nElements << endl;
		cout << "hash funcs: number of calls to hash functions:\t" << numCallsH1H2 << endl;
	}


private:
	vector<bool> T;
};

void usage(string name) {
    cout << endl << "Usage: " << name << " dictionary_file queries_file filter_size" << endl << endl;
    exit(-1);
}

int main(int argc, char* argv[]) {
	
	int filterSize;
	string dictFile, queriesFile;

	if (argc < 4) usage(argv[0]);
	
	dictFile = argv[1];
	queriesFile = argv[2];
	filterSize = atoi(argv[3]);

	BloomFilter bf(DIVISION_KNUTH, MULT_METHOD, filterSize);
	
	fstream dict(dictFile, ios_base::in);
	unsigned int a;
    while (dict >> a) bf.insert(a);
    fstream query(queriesFile, ios_base::in);
	while (query >> a) bf.find(a);
	bf.printResults();
}