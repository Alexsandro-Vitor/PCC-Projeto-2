#include <algorithm>
#include <chrono>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

#include "Arguments.cc"
#include "Help.cc"

#include "Lz77.cc"
#include "SuffixArray.cc"

int main(int argc, char* argv[]) {
	if (argc == 1) {
		cout << "ERROR: No arguments" << endl;
		return -1;
	}
	if (!(Arguments::NAME_H.compare(argv[1]) && Arguments::NAME_HELP.compare(argv[1])))
		return show_help(argc, argv);
	
	string text = "abracadabra pe de cabra";
	string alphabet = "0123456789abcdefghijklmnopqrstuvwxyz";
	unsigned int ls = 10, ll = 5;
	ofstream output ("test.txt", ios::out);
	output << alphabet << endl;
	output << "LZ77" << ' ' << ls << ' ' << ll << endl;
	vector<unsigned int> sa = gen_suffix_array(text);
	for (unsigned int i = 0; i < sa.size(); i++)
		output << sa[i] << ' ';
	string encoded = lz77_encode(text, ls, ll, alphabet);
	output << endl << encoded << endl;

	output << endl;
	output << lz77_decode(encoded, ls, ll, alphabet) << endl;
	output.close();

	return 0;
}