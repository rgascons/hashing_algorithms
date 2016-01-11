#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
using namespace std;

#define DIGITS_SIZE 10

struct Node {
	bool is_end;
	int prefix_count;
	struct Node* child[DIGITS_SIZE];

	Node() : prefix_count(0), is_end(false)
	{}
};

class Trie {
public:

	int _elements;

	int numFoundElements;
	int numNotFoundElements;

	double timeTotal;
	double timeInsert;
	double timeFind;

	Trie() {
		head = new Node();
		_elements = 0;
		numFoundElements = 0;
		numNotFoundElements = 0;
		timeTotal = 0.0;
		timeInsert = 0.0;
		timeTotal = 0.0;
	}

	bool find(unsigned int k) {
		double t1 = clock();
		bool f = find_trie(k);
		double t2 = (clock() - t1)/double(CLOCKS_PER_SEC);
		timeTotal += t2;
		timeFind += t2;

		return f;
	}

	void insert(unsigned int k) {
		double t1 = clock();
		insert_trie(k);
		double t2 = (clock() - t1)/double(CLOCKS_PER_SEC);
		timeTotal += t2;
		timeInsert += t2;
	}

	void printResults() {
		cout << endl << "  --- FI EXPERIMENT --- " << endl << endl;
		cout << "find(k): average search time:\t" <<  double(timeTotal)/(numFoundElements+numNotFoundElements) << endl;
		cout << "find(k): total search time:\t" <<  timeFind << endl;
		cout << "find(k): number of successful queries:\t" << numFoundElements << endl;
		cout << "find(k): number of unsuccessful queries:\t" << numNotFoundElements << endl;
		cout << "insert(k): average insertion time:\t" << double(timeTotal)/(_elements) << endl;
		cout << "insert(k): total insertion time:\t" <<  timeInsert << endl;
		cout << "insert(k): number of elements:\t" << _elements << endl;
	}

private:
	Node *head;
	
	void insert_trie(unsigned int k) {
		string word = to_string(k);
		Node *current = head;
		current -> prefix_count++;
		bool isNewElement = false;
		for (int i = 0; i < word.length(); ++i) {
			int digit = (int)word[i] - (int)'0';
			if (current -> child[digit] == NULL) {
				isNewElement = true;
				current -> child[digit] = new Node();
			}
			current -> child[digit] -> prefix_count++;
			current = current -> child[digit];
		}
		if (isNewElement) ++_elements;
		current -> is_end = true;
	}

	bool find_trie(unsigned int k) {
		string word = to_string(k);
		Node *current = head;
		for (int i = 0; i < word.length(); ++i) {
			int digit = (int)word[i] - (int)'0';
			if (current -> child[digit] == NULL) {
				++numNotFoundElements;
				return false;
			}
			current = current -> child[digit];
		}
		if (current -> is_end) ++numFoundElements;
		else ++numNotFoundElements;
		return current -> is_end;
	}
};

int main(int argc, char* argv[]) {
	string dict_file, query_file;

	cout << "Diccionari:\t" + dict_file 	 << endl;
	cout << "Queries:\t" + query_file << endl;

	if (argc != 3) {
		cout << "Usage: dict_file, query_file" << endl;
		return 0;
	} else {
		dict_file = argv[1];
		query_file = argv[2];
	}
	Trie t;
	fstream dict(dict_file, ios_base::in);
    unsigned int a;
    while (dict >> a) {
    	t.insert(a);
	}
	fstream query(query_file, ios_base::in);
	while (query >> a) {
		t.find(a);
	}
	t.printResults();
}