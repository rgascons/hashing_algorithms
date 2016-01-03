#include <vector>
#include <math.h>
#include "hash_functions.h"
using namespace std;

//Constants

const double GOLDEN_RATIO = 1.61803398875;

//Funcions

// Post: 0 <= h(k) < table.size()
int division_method(unsigned int k, unsigned int m) {
	return k%m;
}

int knuth_division_method(unsigned int k, unsigned int m) {
	return k*(k+3)%m;
}

int multiplication_method(unsigned int k, unsigned int m) {
	double A = GOLDEN_RATIO;
	double s = k * A;
	double x = s - ((int)s);
	return floor(m*x);
}