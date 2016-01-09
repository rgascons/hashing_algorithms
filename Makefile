HASH=hash_table
BLOOM=bloom_filter
BINARY=binary_search
CUCKOO=cuckoo

all:
	g++ -c -o hash_functions.o hash_functions.c
	g++ -c -o hash_table.o hash_table.cc -std=c++0x
	g++ -c -o bloom.o bloom.cc -std=c++0x
	g++ -c -o cuckoo.o cuckoo.cc -std=c++0x
	g++ -o $(HASH) hash_table.o hash_functions.o
	g++ -o $(BLOOM) bloom.o hash_functions.o
	g++ -o $(BINARY) binary_search.cc -std=c++0x
	g++ -o $(CUCKOO) cuckoo.o hash_functions.o

hash:
	g++ -c -o hash_functions.o hash_functions.c
	g++ -c -o hash_table.o hash_table.cc -std=c++0x
	g++ -o $(HASH) hash_table.o hash_functions.o

bloom:
	g++ -c -o hash_functions.o hash_functions.c
	g++ -c -o bloom.o bloom.cc -std=c++0x
	g++ -o $(BLOOM) bloom.o hash_functions.o

cuckoo:
	g++ -c -o hash_functions.o hash_functions.c
	g++ -c -o cuckoo.o cuckoo.cc -std=c++0x
	g++ -o $(CUCKOO) cuckoo.o hash_functions.o

binary:
	g++ -o $(BINARY) binary_search.cc -std=c++0x

clean:
	rm -f $(HASH)
	rm -f $(BLOOM)
	rm -f $(BINARY)
	rm -f $(CUCKOO)
	rm -f *.o