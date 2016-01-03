HASH=hash_table
BLOOM=bloom_filter
BINARY=binary_search

all:
	g++ -c -o hash_functions.o hash_functions.c
	g++ -c -o hash_table.o hash_table.cc -std=c++0x
	g++ -c -o bloom.o bloom.cc -std=c++0x
	g++ -o $(HASH) hash_table.o hash_functions.o
	g++ -o $(BLOOM) bloom.o hash_functions.o
	g++ -o $(BINARY) binary_search.cc -std=c++0x

hash:
	g++ -c -o hash_functions.o hash_functions.c
	g++ -c -o hash_table.o hash_table.cc -std=c++0x
	g++ -o $(HASH) hash_table.o hash_functions.o

bloom:
	g++ -c -o hash_functions.o hash_functions.c
	g++ -c -o bloom.o bloom.cc -std=c++0x
	g++ -o $(BLOOM) bloom.o hash_functions.o

binary:
	g++ -o $(BINARY) binary_search.cc -std=c++0x

clean:
	rm -f $(HASH)
	rm -f $(BLOOM)
	rm -f $(BINARY)
	rm -f *.o