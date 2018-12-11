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
	cout << args << endl;

	output.open(args.getIndexName(), ios::out);
	output << args.opt_alphabet << endl;
	output << int_encode(args.opt_ls, args.opt_alphabet) << endl;
	output << int_encode(args.opt_ll, args.opt_alphabet) << endl;
	for (string text; getline(input, text);) {
		cout << text << endl;
		vector<unsigned int> sa = gen_suffix_array(text);
		cout << "Printing sa" << endl;
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
	cout << "search" << endl;
	queue<Match> matches;	// Os matches encontrados vão pra cá
	unsigned int count = 0;	// Se não for para imprimir, eles são contados aqui

	input.open(args.filename, ifstream::binary);
	if (input.fail()) {
		cout << "ERROR: The file " << args.filename << " is not acessible" << endl;
		return;
	}

	// Parâmetros da compressão
	cout << "params" << endl;
	gettrimline(input, args.opt_alphabet);
	string line;
	gettrimline(input, line);
	args.opt_ls = int_decode(line, args.opt_alphabet);
	gettrimline(input, line);
	args.opt_ll = int_decode(line, args.opt_alphabet);
	cout << args << endl;

	for (unsigned int lineNumber = 0; gettrimline(input, line); lineNumber++) {
		unsigned int size = int_decode(line, args.opt_alphabet);
		vector<unsigned int> sa(size, 0);
		while (size) {
			gettrimline(input, line);
			sa[sa.size() - size--] = int_decode(line, args.opt_alphabet);
		}

		gettrimline(input, line);
		string decoded = lz77_decode(line, args.opt_ls, args.opt_ll, args.opt_alphabet);
		if (args.opt_count)
			count += sa_search(decoded, args.patterns, sa);
		else
			sa_search(decoded, args.patterns, sa, lineNumber, matches);
	}

	// Imprime apenas a quantidade de matches
	if (args.opt_count) {
		cout << FORMAT_PATH << args.filename << FORMAT_RESET << ": " << count << " matches" << endl;
		return;
	}

	// Imprime cada linha com o padrão
	cout << FORMAT_PATH << args.filename << FORMAT_RESET << ": " << matches.size() << " matches" << endl;
	while (matches.size()) {
		Match temp = matches.front();
		if (!args.opt_count) cout << FORMAT_PATH << args.filename << FORMAT_RESET << ':' << temp << endl;

		matches.pop();
	}
}

int main(int argc, char* argv[]) {
	// Configuring output
	cout << boolalpha;
	ios_base::sync_with_stdio(false);

	if (argc == 1) {
		cout << "ERROR: No arguments" << endl;
		return -1;
	}
	if (!(Arguments::NAME_H.compare(argv[1]) && Arguments::NAME_HELP.compare(argv[1])))
		return show_help(argc, argv);
	
	auto tStart = chrono::high_resolution_clock::now();

	Arguments args = Arguments(argc, argv);
	if (args.index_mode) index_main(args);
	else search_main(args);

	auto tEnd = chrono::high_resolution_clock::now();
	chrono::duration<double> elapsed = tEnd - tStart;
	cout << "Execution time: " << elapsed.count() << endl;

	return 0;
}