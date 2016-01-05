#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class BinarySearch {

private:
	
	vector<unsigned int> v;

	// Pre: The vector v is sorted in strictly increasing order. Moreover, we have 0 ≤ left ≤ v.size() and −1 ≤ right < v.size()
	int binarySearch(unsigned int key, int left, int right) {
		if (right < left) return -1;

	  	int mid = (left+right)/2;
	  	if (v[mid] > key) return binarySearch(key, left, mid - 1);
	  	if (v[mid] < key) return binarySearch(key, mid + 1, right);
	  	return mid;
	}

public:

	void setDictionary(vector<unsigned int> v) {
		sort(v.begin(), v.end());	// implement quick sort/radix sort?
		this->v = v;
	}

	int find(unsigned int k) {
		return binarySearch(k, 0, v.size()-1);
	}
	
};

int main() {
	BinarySearch bs;
	vector<unsigned int> v = {5,7,10,12,15,20};
	bs.setDictionary(v);
	cout << bs.find(5) << endl;
	cout << bs.find(12) << endl;
	cout << bs.find(20) << endl;
}