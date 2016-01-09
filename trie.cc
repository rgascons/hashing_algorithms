#include <iostream>
#include <string>
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
	}

	void insert(unsigned int k) {
		string word = to_string(k);
		Node *current = head;
		current -> prefix_count++;
		for (int i = 0; i < word.length(); ++i) {
			int digit = (int)word[i] - (int)'0';
			if (current -> child[digit] == NULL) {
				current ->child[digit] = new Node();
			}
			current -> child[digit] -> prefix_count++;
			current = current -> child[digit];
		}
		current -> is_end = true;
	}

	bool find(unsigned int k) {
		string word = to_string(k);
		Node *current = head;
		for (int i = 0; i < word.length(); ++i) {
			int digit = (int)word[i] - (int)'0';
			cout << digit << endl;
			if (current -> child[digit] == NULL) {
				return false;
			}
			current = current -> child[digit];
		}
		return current -> is_end;
	}

private:
	Node *head;
	int _elements;
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