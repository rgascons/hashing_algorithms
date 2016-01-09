HASH=hash_table
BLOOM=bloom_filter
BINARY=binary_search
CUCKOO=cuckoo
TRIE=trie

all:
	g++ -c -o hash_table.o hash_table.cc -std=c++11
	g++ -c -o bloom.o bloom.cc -std=c++11
	g++ -c -o cuckoo.o cuckoo.cc -std=c++11
	g++ -c -o trie.o trie.cc -std=c++11
	g++ -o $(HASH) hash_table.o
	g++ -o $(BLOOM) bloom.o
	g++ -o $(BINARY) binary_search.cc -std=c++11
	g++ -o $(CUCKOO) cuckoo.o
	g++ -o $(TRIE) trie.o

hash:
	g++ -c -o hash_table.o hash_table.cc -std=c++11
	g++ -o $(HASH) hash_table.o

bloom:
	g++ -c -o bloom.o bloom.cc -std=c++11
	g++ -o $(BLOOM) bloom.o

cuckoo:
	g++ -c -o cuckoo.o cuckoo.cc -std=c++11
	g++ -o $(CUCKOO) cuckoo.o

trie:
	g++ -c -o trie.o trie.cc -std=c++11
	g++ -o $(TRIE) trie.o

binary:
	g++ -o $(BINARY) binary_search.cc -std=c++11

clean:
	rm -f $(HASH)
	rm -f $(BLOOM)
	rm -f $(BINARY)
	rm -f $(CUCKOO)
	rm -f $(TRIE)
	rm -f *.o