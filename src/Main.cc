#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include <vector>
#include <unordered_map>

using namespace std;

#include "Lz77.cc"

int main(int argc, char* argv[]) {
	cout << "prefix_match test" << endl;
	string pattern = "testando";
	string alphabet = "0123456789abcdefghijklmnopqrstuvwxyz";
	unsigned int pos, maxlen;
	prefix_match("aatesta", pattern, alphabet, pos, maxlen);
	cout << "pos: " << pos << endl;
	cout << "maxlen: " << maxlen << endl;

	cout << endl << "int_encode test" << endl;
	unsigned int x = 194;
	string code;
	int_encode(x, "01", code);
	cout << "bin: " << code << endl;
	int_encode(x, "01234567", code);
	cout << "oct: " << code << endl;
	int_encode(x, "0123456789ABCDEF", code);
	cout << "hex: " << code << endl;

	cout << endl << "l77 test" << endl;
	lz77_encode("abracadabra pe de cabra", 7, 5, alphabet, code);
	cout << "Code: " << code << endl;
	return 0;
}