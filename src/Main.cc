#include <algorithm>
#include <chrono>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

#include "Lz77.cc"
#include "SuffixArray.cc"

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
	unsigned int ls = 10, ll = 5;
	lz77_encode("abracadabra pe de cabra", ls, ll, alphabet, code);
	cout << "Code: " << code << endl;

	cout << endl << "int_decode test" << endl;
	cout << "bin: " << int_decode("11000010", "01") << endl;
	cout << "oct: " << int_decode("302", "01234567") << endl;
	cout << "hex: " << int_decode("C2", "0123456789ABCDEF") << endl;

	cout << endl << "lz77_decode test" << endl;
	string decoded;
	lz77_decode(code, ls, ll, alphabet, decoded);
	cout << "Decoded: " << decoded << endl;

	cout << endl << "Suffix Array test" << endl;
	string text = "testando";
	vector<unsigned int> sa(text.size(), 0);
	for (int i = 0; i < sa.size(); i++) {
		sa[i] = i;
		cout << i << ':' << suffix(text, sa[i]) << ' ';
	} cout << endl;
	compare_suffix.text = text;
	sort(sa.begin(), sa.end(), compare_suffix);
	for (int i = 0; i < sa.size(); i++) {
		cout << i << ':' << suffix(text, sa[i]) << ' ';
	} cout << endl;
	cout << succ(text, "stand", sa);
	return 0;
}