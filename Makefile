HASH=hash_table
BLOOM=bloom
BINARY=binary_search
CUCKOO=cuckoo
TRIE=trie

all: hash bloom cuckoo trie binary

hash:
	g++ -o $(HASH) hash_table.cc -std=c++11

bloom:
	g++ -o $(BLOOM) bloom.cc -std=c++11

cuckoo:
	g++ -o $(CUCKOO) cuckoo.cc -std=c++11

trie:
	g++ -o $(TRIE) trie.cc -std=c++11

binary:
	g++ -o $(BINARY) binary_search.cc -std=c++11

clean:
	rm -f $(HASH)
	rm -f $(BLOOM)
	rm -f $(BINARY)
	rm -f $(CUCKOO)
	rm -f $(TRIE)
	rm -f *.o