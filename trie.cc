#include <iostream>
#include <string>
#include <ctime>
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
	Trie() {
		head = new Node();
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
		cout << endl << endl;
		cout << "find(k): average search time:\t" <<  double(timeTotal)/(numFoundElements+numNotFoundElements) << endl;
		cout << "find(k): total search time:\t" <<  timeFind << endl;
		cout << "find(k): number of successful queries:\t" << numFoundElements << endl;
		cout << "find(k): number of unsuccessful queries:\t" << numNotFoundElements << endl;
		cout << "insert(k): average insertion time:\t" << double(timeTotal)/(_elements) << endl;
		cout << "insert(k): total insertion time:\t" <<  timeInsert << endl;
	}

private:
	Node *head;
	int _elements;

	int numFoundElements;
	int numNotFoundElements;

	double timeTotal;
	double timeInsert;
	double timeFind;

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
		++numFoundElements;
		return current -> is_end;
	}
};

int main() {
	Trie t;
	t.insert(1234);
	cout << t.find(1234) << endl;
	cout << t.find(4321) << endl;
	t.insert(123456);
	cout << t.find(123456) << endl;
	cout << t.find(1234567) << endl;
}