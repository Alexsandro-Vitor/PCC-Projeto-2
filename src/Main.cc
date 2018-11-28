#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include <vector>
#include <unordered_map>

using namespace std;

#include "Lz77.cc"

int main(int argc, char* argv[]) {
	string pattern = "test";
	string alphabet = "aeiostu";
	vector< unordered_map<char, int> > delta(pattern.size() + 1);
	build_fsm(pattern, alphabet, delta);
	print_fsm(pattern, alphabet, delta);
	return 0;
}