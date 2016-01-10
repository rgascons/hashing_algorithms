#include <vector>
#include <math.h>
using namespace std;

//Constants
const double GOLDEN_RATIO = 1.61803398875;
const int DIVISION_METHOD = 0;
const int DIVISION_KNUTH  = 1;
const int MULT_METHOD 	  = 2;

// Post: 0 <= h(k) < table.size()
int divisionMethodHash(unsigned int k, unsigned int m) {
	return k%m;
}

// Post: 0 <= h(k) < table.size()
int knuthDivisionMethodHash(unsigned int k, unsigned int m) {
	return k*(k+3)%m;
}

// Post: 0 <= h(k) < table.size()
// It works with almost any A, but Knuth recommends that A must be the golden ratio
int multiplicationMethodHash(unsigned int k, unsigned int m) {
	double A = GOLDEN_RATIO;
	double s = fmod(k * A, 1.0);
	return floor(m*s);
}

int h(int f, unsigned int k, unsigned int m) {
	if (f == DIVISION_METHOD) return divisionMethodHash(k, m);
	if (f == DIVISION_KNUTH) return knuthDivisionMethodHash(k, m);
	/*if (f == MULT_METHOD) */
	return multiplicationMethodHash(k, m);
}