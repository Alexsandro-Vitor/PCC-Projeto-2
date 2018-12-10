#include <algorithm>
#include <chrono>
#include <cmath>
#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

#define uint unsigned int

#include "Formatting.cc"
#include "Arguments.cc"
#include "Help.cc"
#include "Match.cc"

#include "Lz77.cc"
#include "SuffixArray.cc"

ifstream input;
ofstream output;

void index_main(Arguments& args) {
	input.open(args.filename, ios::in);
	if (input.fail()) {
		cout << "ERROR: The file " << args.filename << " is not acessible" << endl;
		return;
	}

	output.open(args.getIndexName(), ios::out);
	output << (char)args.opt_ls << (char)args.opt_ll << args.opt_alphabet << endl;
	for (string text; getline(input, text);) {
		cout << text << endl;
		vector<unsigned int> sa = gen_suffix_array(text);
		output << int_encode(sa.size(), args.opt_alphabet) << endl;
		for (const unsigned int i : sa)
			output << int_encode(i, args.opt_alphabet) << endl;
		output << lz77_encode(text, args.opt_ls, args.opt_ll, args.opt_alphabet) << endl;
	}
}

inline bool gettrimline(ifstream& in, string& str) {
	bool out = (bool)getline(in, str);
	if (out) str.resize(str.size() - 1);
	return out;
}

void search_main(Arguments& args) {
	queue<Match> matches;			// Os matches encontrados vão pra cá

	input.open(args.filename, ifstream::binary);
	if (input.fail()) {
		cout << "ERROR: The file " << args.filename << " is not acessible" << endl;
		return;
	}

	char c;
	input.get(c);
	args.opt_ls = c;
	input.get(c);
	args.opt_ll = c;
	gettrimline(input, args.opt_alphabet);
	cout << args << endl;

	string line;
	for (unsigned int lineNumber = 0; gettrimline(input, line); lineNumber++) {
		cout << endl;
		unsigned int size = int_decode(line, args.opt_alphabet);
		vector<unsigned int> sa(size, 0);
		while (size) {
			gettrimline(input, line);
			sa[sa.size() - size--] = int_decode(line, args.opt_alphabet);
		}
		cout << "sa: ";
		for (const unsigned int i : sa) {
			cout << i << ' ';
		} cout << endl;
		gettrimline(input, line);
		string decoded = lz77_decode(line, args.opt_ls, args.opt_ll, args.opt_alphabet);
		cout << "Line: " << decoded << endl;
		sa_search(decoded, args.patterns, sa, lineNumber, matches);
	}

	//Imprime cada linha com o padrão
	if (matches.size())
		cout << FORMAT_PATH << args.filename << FORMAT_RESET << ": " << matches.size() << " matches" << endl;
	while (matches.size()) {
		Match temp = matches.front();
		if (!args.opt_count) cout << FORMAT_PATH << args.filename << FORMAT_RESET << ':' << temp << endl;

		matches.pop();
	}
}

int main(int argc, char* argv[]) {
	cout << boolalpha;

	if (argc == 1) {
		cout << "ERROR: No arguments" << endl;
		return -1;
	}
	if (!(Arguments::NAME_H.compare(argv[1]) && Arguments::NAME_HELP.compare(argv[1])))
		return show_help(argc, argv);

	Arguments args = Arguments(argc, argv);
	cout << args << endl;

	if (args.index_mode) index_main(args);
	else search_main(args);

	return 0;
}