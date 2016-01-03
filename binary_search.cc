#include <iostream>
#include <vector>
using namespace std;

class BinarySearch {
public:

	// Pre: The vector v is sorted in strictly increasing order. Moreover, we have 0 ≤ left ≤ v.size() and −1 ≤ right < v.size()
	int binary_search(const vector<int>& v, int key, int left, int right) {
		if (right < left) return -1;

	  	int mid = (left+right)/2;
	  	if (v[mid] > key) return binary_search(v, key, left, mid - 1);
	  	if (v[mid] < key) return binary_search(v, key, mid + 1, right);
	  	return mid;
	}
	
};

int main() {
	BinarySearch bs;
	vector<int> v = {5,7,10,12,15,20};
	cout << bs.binary_search(v, 5, 0, v.size()-1) << endl;
}