from __future__ import print_function
import random
import sys

UINT_MAX = (2**32) -1

def generate_random():
	f = open(OUTPUT_FILE, 'w')
	f.truncate()
	for i in range(0, numbers):
		print(random.randint(1, UINT_MAX), file=f)

def generate_random_set(words, chance_old_words):
	f = open(OUTPUT_FILE, 'w')
	f.truncate()
	for i in range(0, numbers):
		randnum = random.randint(0, 100)
		if randnum < chance_old_words:
			print(random.choice(words), file=f)
		else:
			print(random.randint(1, UINT_MAX), file=f)

	

if len(sys.argv) < 3:
	#sys.exit("Usage: enter how many numbers you want to generate and the name of the output file [and the change of appearance from the previous output and the file from a previous output]")
	print("Usage:")
	print("   Dictionary:\t" + sys.argv[0] + " output_file number_elements")
	print("   Queries:\t" + sys.argv[0] + " dict_file output_file number_queries chance_of_belonging")
	sys.exit()


if len(sys.argv) == 3:
	OUTPUT_FILE = sys.argv[1]
	numbers = int(sys.argv[2])
	generate_random()
elif len(sys.argv) == 5:
	filename = sys.argv[1]
	OUTPUT_FILE = sys.argv[2]
	numbers = int(sys.argv[3])
	chance_old_words = int(sys.argv[4])
	words = list(line.strip() for line in open(filename))
	generate_random_set(words, chance_old_words)
else:
	sys.exit("Wrong parameters")

