HASH=hash_table
BLOOM=bloom
BINARY=binary_search
CUCKOO=cuckoo
TRIE=trie
MAIN=main

all: main trie

main:
	g++ -o $(MAIN) main.cc -std=c++11 -O3

hash:
	g++ -o $(HASH) hash_table.cc -std=c++11 -O3

bloom:
	g++ -o $(BLOOM) bloom.cc -std=c++11 -O3

cuckoo:
	g++ -o $(CUCKOO) cuckoo.cc -std=c++11 -O3

trie:
	g++ -o $(TRIE) trie.cc -std=c++11 -O3

binary:
	g++ -o $(BINARY) binary_search.cc -std=c++11 -O3

clean:
	rm -f main
	rm -f $(HASH)
	rm -f $(BLOOM)
	rm -f $(BINARY)
	rm -f $(CUCKOO)
	rm -f $(TRIE)
	rm -f $(MAIN)
	rm -f *.o