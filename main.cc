#include <iostream>
#include <fstream>
#include <cstdlib>
#include "binary_search.cc"
#include "hash_table.cc"
#include "bloom.cc"
#include "cuckoo.cc"
#include "trie.cc"
using namespace std;

void trie(string dictFile, string queriesFile, int nRep) {

	double _elements 				= 0;
	double timeInsert 				= 0;
	double timeFind					= 0;
	double timeTotal 				= 0;
	double numFoundElements 		= 0;
	double numNotFoundElements 		= 0;

	for (int i = 0; i < nRep; ++i) {	
		fstream dict(dictFile, ios_base::in);
		fstream queries(queriesFile, ios_base::in);

		Trie t;
	    unsigned int a;
	    while (dict >> a) {
	    	t.insert(a);
		}
		while (queries >> a) {
			t.find(a);
		}

		timeInsert += t.timeInsert;
		timeFind  += t.timeFind;
		timeTotal += t.timeTotal;
		numFoundElements += t.numFoundElements;
		numNotFoundElements += t.numNotFoundElements;
		_elements  += t._elements;
	}

	timeTotal /= nRep;
	timeInsert /= nRep;
	timeFind  /= nRep;
	numFoundElements /= nRep;
	numNotFoundElements /= nRep;
	_elements  /= nRep;
	
	cout << endl << endl << "  ---- Trie Results ----" << endl << endl;
	cout << "find(k): average search time:\t" <<  double(timeTotal)/(numFoundElements+numNotFoundElements) << endl;
	cout << "find(k): total search time:\t" <<  timeFind << endl;
	cout << "find(k): number of successful queries:\t" << numFoundElements << endl;
	cout << "find(k): number of unsuccessful queries:\t" << numNotFoundElements << endl;
	cout << "insert(k): average insertion time:\t" << double(timeTotal)/(_elements) << endl;
	cout << "insert(k): total insertion time:\t" <<  timeInsert << endl;
	cout << "insert(k): number of elements:\t" << _elements << endl;
}


void cuckoo(string dictFile, string queriesFile, int nRep, int m) {

	double timeTotal 				= 0;
	double numFoundElements 		= 0;
	double numNotFoundElements 		= 0;
	double _elements 				= 0;
	double timeFind					= 0;
	double timeInsert 				= 0;
	double numRehash 				= 0;
	double rehashTime 				= 0;
	double numCallsHashFunction1 	= 0;
	double numCallsHashFunction2 	= 0;
	double numBounces			 	= 0;

	for (int i = 0; i < nRep; ++i) {	
		fstream dict(dictFile, ios_base::in);
		fstream queries(queriesFile, ios_base::in);

		CuckooHash c(m, DIVISION_KNUTH, MULT_METHOD);
	    unsigned int a;
	    while (dict >> a) {
	    	c.insert(a);
		}
		while (queries >> a) {
			c.find(a);
		}

		timeTotal += c.timeTotal;
		timeFind  += c.timeFind;
		numFoundElements += c.numFoundElements;
		numNotFoundElements += c.numNotFoundElements;
		_elements  += c._elements;
		timeInsert += c.timeInsert;
		numRehash  += c.numRehash;
		rehashTime += c.rehashTime;
		numCallsHashFunction1 += c.numCallsHashFunction1;
		numCallsHashFunction2 += c.numCallsHashFunction2;
		numBounces += c.numBounces;

	}

	timeTotal /= nRep;
	timeFind  /= nRep;
	numFoundElements /= nRep;
	numNotFoundElements /= nRep;
	_elements  /= nRep;
	timeInsert /= nRep;
	numRehash  /= nRep;
	rehashTime /= nRep;
	numCallsHashFunction1 /= nRep;
	numCallsHashFunction2 /= nRep;
	numBounces /= nRep;
	
	cout << endl << endl << "  ---- Cuckoo Results ----" << endl << endl;
	cout << "find(k): average search time:\t" <<  double(timeFind)/(numFoundElements+numNotFoundElements) << endl;
	cout << "find(k): total search time:\t" <<  timeFind << endl;
	cout << "find(k): number of successful queries:\t" << numFoundElements << endl;
	cout << "find(k): number of unsuccessful queries:\t" << numNotFoundElements << endl;
	cout << "insert(k): average insertion time:\t" << double(timeInsert)/(_elements) << endl;
	cout << "insert(k): total insertion time:\t" <<  timeInsert << endl;
	cout << "insert(k): total number of bounces:\t" << numBounces << endl;
	cout << "insert(k): number of elements:\t" << _elements << endl;
	cout << "rehash(): number of rehashes:\t" << numRehash << endl;
	cout << "rehash(): average time of each rehash:\t" << double(rehashTime)/(numRehash) << endl;
	cout << "rehash(): average time between each rehash:\t" << double(timeTotal-rehashTime)/(numRehash) << endl;
	cout << "		 : number of calls to hash1:\t" << numCallsHashFunction1 << endl;
	cout << "		 : number of calls to hash2:\t" << numCallsHashFunction2 << endl;
}

void hashTable(string dictFile, string queriesFile, int nRep, int m, double maxLoadFactor) {

	double timeTotal 				= 0;
	double numFoundElements 		= 0;
	double numNotFoundElements 		= 0;
	double _elements 				= 0;
	double timeFind					= 0;
	double timeInsert 				= 0;
	double numRehash 				= 0;
	double rehashTime 				= 0;
	double numCallsHashFunction 	= 0;

	for (int i = 0; i < nRep; ++i) {	
		fstream dict(dictFile, ios_base::in);
		fstream queries(queriesFile, ios_base::in);

		HashTable ht(m, maxLoadFactor, DIVISION_METHOD);
	    unsigned int a;
	    while (dict >> a) {
	    	ht.insert(a);
		}
		while (queries >> a) {
			ht.find(a);
		}

		timeTotal += ht.timeTotal;
		timeFind  += ht.timeFind;
		numFoundElements += ht.numFoundElements;
		numNotFoundElements += ht.numNotFoundElements;
		_elements  += ht._elements;
		timeInsert += ht.timeInsert;
		numRehash  += ht.numRehash;
		rehashTime += ht.rehashTime;
		numCallsHashFunction += ht.numCallsHashFunction;

	}

	timeTotal /= nRep;
	timeFind  /= nRep;
	numFoundElements /= nRep;
	numNotFoundElements /= nRep;
	_elements  /= nRep;
	timeInsert /= nRep;
	numRehash  /= nRep;
	rehashTime /= nRep;
	numCallsHashFunction /= nRep;
	
	cout << endl << endl << "  ---- Hash Table Results ----" << endl << endl;
	cout << "find(k): average search time:\t" <<  double(timeTotal)/(numFoundElements+numNotFoundElements) << endl;
	cout << "find(k): total search time:\t" <<  timeFind << endl;
	cout << "find(k): number of successful queries:\t" << numFoundElements << endl;
	cout << "find(k): number of unsuccessful queries:\t" << numNotFoundElements << endl;
	cout << "insert(k): average insertion time:\t" << double(timeTotal)/(_elements) << endl;
	cout << "insert(k): total insertion time:\t" <<  timeInsert << endl;
	cout << "insert(k): number of elements:\t" << _elements << endl;
	cout << "rehash(): number of rehashes:\t" << numRehash << endl;
	cout << "rehash(): average time of each rehash:\t" << double(rehashTime)/(numRehash) << endl;
	cout << "rehash(): average time between each rehash:\t" << double(timeTotal-rehashTime)/(numRehash) << endl;
	cout << "		 : number of calls to hash:\t" << numCallsHashFunction << endl;
}

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

	cout << endl << endl << "  ---- Bloom Filter Results ----" << endl << endl;
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

	cout << endl << "---- Binary Search Results ----" << endl;
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
    cout << endl << "Usage: " << name << " dict_file queries_file n_rep hashtable_size bloomfilter_size max_loadFactor cuckoo_size" << endl << endl;
    cout << "  - dict_file: fitxer amb el conjunt de paraules a inserir a cada conjunt" << endl;
    cout << "  - queries_file: fitxer amb el conjunt de paraules a cercar al conjunt" << endl;
    cout << "  - n_rep: nombre de vegades que es repeteix cada execucio (com a resultats s'imprimeix la mitjana de les n_rep execucions)" << endl;
    cout << "  - hashtable_size: mida de la taula de hash (nombre de caselles)" << endl;
    cout << "  - bloomfilter_size: mida del filtre de bloom (nombre de caselles)" << endl;
    cout << "  - max_loadFactor: factor de carrega a partir del qual es fara rehash de la taula de hash" << endl;
    cout << "  - cuckoo_size: size of each table of cuckoo hashing structure" << endl;
    exit(-1);
}

int main(int argc, char* argv[]) {
	if (argc < 8) usage(argv[0]);

	string dictFile 	= argv[1];
	string queriesFile 	= argv[2];
	int nRep 			= atoi(argv[3]);
	int hashTableSize 	= atoi(argv[4]);
	int bloomFilterSize = atoi(argv[5]);
	double maxLoadFactor= double(atof(argv[6]));
	int cuckooSize 		= atoi(argv[7]);

	cout << "Diccionari:\t" + dictFile 	 << endl;
	cout << "Queries:\t" + queriesFile << endl;
	
	cerr << endl << "binary search ..." << endl;
	binarySearch(dictFile, queriesFile, nRep);
	
	cerr << endl << "filtre de bloom ..." << endl;
	bloomFilter(dictFile, queriesFile, nRep, bloomFilterSize);
	
	cerr << endl << "taula de hash ..." << endl;
	hashTable(dictFile, queriesFile, nRep, hashTableSize, maxLoadFactor);
	
	cerr << endl << "cuckoo ..." << endl;
	cuckoo(dictFile, queriesFile, nRep, hashTableSize);

	//cerr << endl << "trie ..." << endl;
	//trie(dictFile, queriesFile, nRep);

	cout << endl << "  --- FI EXPERIMENT --- " << endl << endl;
}