#ifndef __TUPLE_H_INCLUDED__
#define __TUPLE_H_INCLUDED__

#include <ostream>

using namespace std;

class Tuple {
	public:
		unsigned int p;
		unsigned int l;
		char c;
		Tuple();
		Tuple(unsigned int p, unsigned int l, char c);
		friend ostream& operator<<(ostream& os, const Tuple& args);
};

Tuple::Tuple() {
	this->p = 0;
	this->l = 0;
	this->c = 0;
}

Tuple::Tuple(unsigned int p, unsigned int l, char c) {
	this->p = p;
	this->l = l;
	this->c = c;
}

ostream& operator<<(ostream& os, const Tuple& tuple) {
	os << '(' << tuple.p << ", " << tuple.l << ", " << tuple.c << ")";
	return os;
}

#endif