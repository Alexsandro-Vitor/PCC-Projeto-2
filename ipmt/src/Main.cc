#include <algorithm>
#include <chrono>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

#define uint unsigned int

#include "Arguments.cc"
#include "Help.cc"

#include "Lz77.cc"
#include "SuffixArray.cc"

ifstream input;
ofstream output;

void index_main(Arguments& args) {
	input.open(args.filename, ios::in);
	if (input.fail()) {
		cout << "ERROR: The file is not acessible" << endl;
		return;
	}
	cout << "Filename for index: " << args.getIndexName() << endl;
	output.open(args.getIndexName(), ios::out);
	output << args.opt_alphabet << endl;
	output << (char)args.opt_ls << ' ' << (char)args.opt_ll << endl;
	for (string text; getline(input, text);) {
		cout << text << endl;
		vector<unsigned int> sa = gen_suffix_array(text);
		for (const unsigned int i : sa)
			output << i << ' ';
		output << endl << lz77_encode(text, args.opt_ls, args.opt_ll, args.opt_alphabet) << endl;
	}
}

void search_main(Arguments& args) {
	cout << "TODO search" << endl;
}

int main(int argc, char* argv[]) {
	cout << boolalpha;

	if (argc == 1) {
		cout << "ERROR: No arguments" << endl;
		return -1;
	}
	if (!(Arguments::NAME_H.compare(argv[1]) && Arguments::NAME_HELP.compare(argv[1])))
		return show_help(argc, argv);
	
	/*string text = "abracadabra pe de cabra";
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
	output.close();*/
	Arguments args = Arguments(argc, argv);
	cout << args << endl;

	if (args.index_mode) index_main(args);
	else search_main(args);

	return 0;
}