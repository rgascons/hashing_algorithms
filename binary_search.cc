#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
using namespace std;

class BinarySearch {

private:

	vector<unsigned int> v;

	// Number of comparisons of keys during the latest call to binarySearch(k)
	int numKeyComparisons;

	void quicksort(vector<unsigned int>& v) {
		quicksort(v, 0, v.size() - 1);	
	}

	void quicksort(vector<unsigned int>& v, int l, int r) {
		if (l < r) {
			int q = partition(v, l, r);
			quicksort(v, l, q);
			quicksort(v, q+1, r);
		}
	}

	int partition(vector<unsigned int>& v, int l, int r) {
		unsigned int x = v[l];
		int i = l-1;
		int j = r+1;
		for (;;) {
			while (x < v[--j]) ++numSortComparisons;
			while (v[++i] < x) ++numSortComparisons;
			++numSortComparisons;
			if (i >= j) return j;
			unsigned int aux = v[i];
			v[i] = v[j];
			v[j] = aux;
		}
	}
	// Pre: The vector v is sorted in strictly increasing order. Moreover, we have 0 ≤ left ≤ v.size() and −1 ≤ right < v.size()
	int binarySearch(unsigned int key, int left, int right) {
		
		if (right < left) {
			++numKeyComparisons;
			finish(0);
			return -1;
		}

		int mid = (left+right)/2;
		if (v[mid] > key) {
			++numKeyComparisons;
			return binarySearch(key, left, mid - 1);
		}
		if (v[mid] < key) {
			++numKeyComparisons;
			return binarySearch(key, mid + 1, right);
		}
		finish(1);
		return mid;
	}

	void finish(bool found) {
		if (found) {
			++numFoundElements;
			numKeyCompFoundElements  += numKeyComparisons;
		}
		else {
			++numNotFoundElements;
			numKeyCompNotFoundElements  += numKeyComparisons;
		}
	}

public:
	int numSortComparisons;
	int numFoundElements;
	int numNotFoundElements;
	int numKeyCompFoundElements;
	int numKeyCompNotFoundElements;
	double timeTotal;

	BinarySearch() {
		this->numKeyComparisons  = 0;
		this->numSortComparisons = 0;

		this->numFoundElements		= 0;
		this->numNotFoundElements	= 0;
		
		this->numKeyCompFoundElements		= 0;
		this->numKeyCompNotFoundElements	= 0;
		this->timeTotal = 0.0;
	}

	void setDictionary(vector<unsigned int> v) {
		//sort(v.begin(), v.end());	// implement quick sort/radix sort?
		numSortComparisons = 0;
		quicksort(v);
		this->v = v;
	}

	int find(unsigned int k) {
		double t1 = clock();
		int sol = binarySearch(k, 0, v.size()-1);
		this->numKeyComparisons = 0;
		double t2 = (clock() - t1)/double(CLOCKS_PER_SEC);
		timeTotal += t2;
		return sol;
	}

	int getNumKeyComparisons() {
		return numKeyComparisons;
	}
	int getNumSortComparisons() {
		return numSortComparisons;
	}
	void printResults() {
		cout << endl << endl;
		cout << "find(k): comparisons between keys:\t" <<  double(numKeyCompFoundElements+numKeyCompNotFoundElements)/(numFoundElements+numNotFoundElements) << endl;
		cout << "find(k): average search time:\t" <<  double(timeTotal)/(numFoundElements+numNotFoundElements) << endl;
		cout << "setDictionary(v): sort comparisons:\t" << numSortComparisons << endl;
		cout << endl;
		cout << "   ** For found elements **" << endl;
		cout << "find(k): average comparisons between keys:\t" << (double) numKeyCompFoundElements/numFoundElements << endl;
		cout << endl;
		cout << "   ** For not found elements **" << endl;
		cout << "find(k): average comparisons between keys:\t" << (double) numKeyCompNotFoundElements/numNotFoundElements << endl;
	}
	
};

int hi() {
	BinarySearch bs;
	// vector<unsigned int> v = {5,7,10,12,15,20};
	vector<unsigned int> v = {7,5,20,12,10,15};
	bs.setDictionary(v);
	cout << bs.find(5) << ", " << bs.getNumKeyComparisons() << " comparisons" << endl;
	cout << bs.find(12) << ", " << bs.getNumKeyComparisons() << " comparisons" << endl;
	cout << bs.find(13) << ", " << bs.getNumKeyComparisons() << " comparisons" << endl;
	cout << bs.find(20) << ", " << bs.getNumKeyComparisons() << " comparisons" << endl;

	bs.printResults();
}