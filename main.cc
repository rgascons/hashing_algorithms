#include <iostream>
#include <fstream>
#include <cstdlib>
#include "binary_search.cc"
// #include "hash_table.cc"
# include "bloom.cc"
// #include "cuckoo.cc"
// #include "trie.cc"
using namespace std;

void bloomFilter(string dictFile, string queriesFile, int nRep, int m) {
	
	double numCallsH1H2				= 0;
	double numFoundElements 		= 0;
	double numNotFoundElements 		= 0;
	double numAlmostFoundElements	= 0;
	double timeFind 				= 0;
	double timeInsert				= 0;
	double nElements 				= 0;
	
	for (int i = 0; i < nRep; ++i) {	
		fstream dict(dictFile, ios_base::in);
		fstream queries(queriesFile, ios_base::in);

		BloomFilter bf(DIVISION_KNUTH, MULT_METHOD, m);
		vector<unsigned int> v;
	    unsigned int a;
	    while (dict >> a) bf.insert(a);
		while (queries >> a) bf.find(a);

		numCallsH1H2 		+= bf.numCallsH1H2;
		numFoundElements 	+= bf.numFoundElements;
		numNotFoundElements += bf.numNotFoundElements;
		numAlmostFoundElements    += bf.numAlmostFoundElements;
		timeFind += bf.timeFind;
		timeInsert += bf.timeInsert;
		nElements += bf.nElements;
	}

	numCallsH1H2 	/= (double) nRep;
	numFoundElements /= (double) nRep;
	numNotFoundElements  /= (double) nRep;
	numAlmostFoundElements    /= (double) nRep;
	timeFind /= (double) nRep;
	timeInsert /= double(nRep);
	nElements /= double(nRep);

	cout << endl << endl << "  ---- Bloom Filter ----" << endl << endl;
	cout << "find(k): average search time:\t" <<  double(timeFind)/(numFoundElements+numNotFoundElements) << endl;
	cout << "find(k): total search time:\t" <<  timeFind << endl;
	cout << "find(k): number of successful queries:\t" << numFoundElements << endl;
	cout << "find(k): number of unsuccessful queries:\t" << numNotFoundElements << endl;
	cout << "insert(k): average insertion time:\t" << double(timeInsert)/(nElements) << endl;
	cout << "insert(k): total insertion time:\t" <<  timeInsert << endl;
	cout << "insert(k): number of elements:\t" << nElements << endl;
	cout << "hash funcs: number of calls to hash functions:\t" << numCallsH1H2 << endl;	
}

void binarySearch(string dictFile, string queriesFile, int nRep) {
	
	double numFoundElements = 0;
	double numNotFoundElements = 0;
	double numSortComparisons  = 0;
	double numKeyCompFoundElements    = 0;
	double numKeyCompNotFoundElements = 0;
	double timeTotal = 0;
	
	for (int i = 0; i < nRep; ++i) {	
		fstream dict(dictFile, ios_base::in);
		fstream queries(queriesFile, ios_base::in);

		BinarySearch bs;
		vector<unsigned int> v;
	    unsigned int a;
	    while (dict >> a) v.push_back(a); 
		bs.setDictionary(v);
		while (queries >> a) bs.find(a);

		numFoundElements 	+= bs.numFoundElements;
		numNotFoundElements += bs.numNotFoundElements;
		numSortComparisons  += bs.numSortComparisons;
		numKeyCompFoundElements    += bs.numKeyCompFoundElements;
		numKeyCompNotFoundElements += bs.numKeyCompNotFoundElements;
		timeTotal += bs.timeTotal;
	}

	numFoundElements 	/= (double) nRep;
	numNotFoundElements /= (double) nRep;
	numSortComparisons  /= (double) nRep;
	numKeyCompFoundElements    /= (double) nRep;
	numKeyCompNotFoundElements /= (double) nRep;
	timeTotal /= double(nRep);

	cout << endl << "---- Binary Search ----" << endl;
	cout << "find(k): comparisons between keys:\t" <<  double(numKeyCompFoundElements+numKeyCompNotFoundElements)/(numFoundElements+numNotFoundElements) << endl;
	cout << "find(k): average search time:\t" <<  double(timeTotal)/(numFoundElements+numNotFoundElements) << endl;
	cout << "find(k): total search time:\t" <<  timeTotal << endl;
	cout << "find(k): number of successful queries:\t" << numFoundElements << endl;
	cout << "find(k): number of unsuccessful queries:\t" << numNotFoundElements << endl;
	cout << "setDictionary(v): sort comparisons:\t" << numSortComparisons << endl;
	cout << endl;
	cout << "   ** For found elements **" << endl;
	cout << "find(k): average comparisons between keys:\t" << (double) numKeyCompFoundElements/numFoundElements << endl;
	cout << endl;
	cout << "   ** For not found elements **" << endl;
	cout << "find(k): average comparisons between keys:\t" << (double) numKeyCompNotFoundElements/numNotFoundElements << endl;
}

void usage(string name) {
    cout << endl << "Usage: " << name << " dict_file queries_file n_rep bloomfilter_size" << endl << endl;
    cout << "  - dict_file: fitxer amb el conjunt de paraules a inserir a cada conjunt" << endl;
    cout << "  - queries_file: fitxer amb el conjunt de paraules a cercar al conjunt" << endl;
    cout << "  - n_rep: nombre de vegades que es repeteix cada execucio (com a resultats s'imprimeix la mitjana de les n_rep execucions)" << endl;
    cout << "  - bloomfilter_size: mida del filtre de bloom (nombre de caselles)" << endl;
    exit(-1);
}

int main(int argc, char* argv[]) {
	if (argc < 5) usage(argv[0]);

	string dictFile = argv[1];
	string queriesFile = argv[2];
	int nRep = atoi(argv[3]);
	int bloomFilterSize = atoi(argv[4]);
	binarySearch(dictFile, queriesFile, nRep);
	bloomFilter(dictFile, queriesFile, nRep, bloomFilterSize);
}