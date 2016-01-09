#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class BinarySearch {

private:

	vector<unsigned int> v;

	// Number of comparisons of keys during the latest call to binarySearch(k)
	int numKeyComparisons;
	
	// Pre: The vector v is sorted in strictly increasing order. Moreover, we have 0 ≤ left ≤ v.size() and −1 ≤ right < v.size()
	int binarySearch(unsigned int key, int left, int right) {
		
		if (right < left) {
			++numKeyComparisons;
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
	  	return mid;
	}

public:

	BinarySearch() {
		this->numKeyComparisons = 0;
	}

	void setDictionary(vector<unsigned int> v) {
		sort(v.begin(), v.end());	// implement quick sort/radix sort?
		this->v = v;
	}

	int find(unsigned int k) {
		return binarySearch(k, 0, v.size()-1);
	}

	int getNumKeyComparisons() {
		return numKeyComparisons;
	}
	
};

int main() {
	BinarySearch bs;
	// vector<unsigned int> v = {5,7,10,12,15,20};
	vector<unsigned int> v = {7,5,20,12,10,15};
	bs.setDictionary(v);
	cout << bs.find(5) << ", " << bs.getNumKeyComparisons() << " comparisons" << endl;
	cout << bs.find(12) << ", " << bs.getNumKeyComparisons() << " comparisons" << endl;
	cout << bs.find(13) << ", " << bs.getNumKeyComparisons() << " comparisons" << endl;
	cout << bs.find(20) << ", " << bs.getNumKeyComparisons() << " comparisons" << endl;
}