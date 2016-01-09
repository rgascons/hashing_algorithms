HASH=hash_table
BLOOM=bloom_filter
BINARY=binary_search
CUCKOO=cuckoo
TRIE=trie

all:
	g++ -c -o hash_functions.o hash_functions.c
	g++ -c -o hash_table.o hash_table.cc -std=c++11
	g++ -c -o bloom.o bloom.cc -std=c++11
	g++ -c -o cuckoo.o cuckoo.cc -std=c++11
	g++ -c -o trie.o trie.cc -std=c++11
	g++ -o $(HASH) hash_table.o hash_functions.o
	g++ -o $(BLOOM) bloom.o hash_functions.o
	g++ -o $(BINARY) binary_search.cc -std=c++11
	g++ -o $(CUCKOO) cuckoo.o hash_functions.o
	g++ -o $(TRIE) trie.o

hash:
	g++ -c -o hash_functions.o hash_functions.c
	g++ -c -o hash_table.o hash_table.cc -std=c++11
	g++ -o $(HASH) hash_table.o hash_functions.o

bloom:
	g++ -c -o hash_functions.o hash_functions.c
	g++ -c -o bloom.o bloom.cc -std=c++11
	g++ -o $(BLOOM) bloom.o hash_functions.o

cuckoo:
	g++ -c -o hash_functions.o hash_functions.c
	g++ -c -o cuckoo.o cuckoo.cc -std=c++11
	g++ -o $(CUCKOO) cuckoo.o hash_functions.o

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