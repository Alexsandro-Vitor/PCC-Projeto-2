#include <chrono>
#include <fstream>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

#define uint unsigned int

#include "Formatting.h"
#include "Arguments.h"
#include "Help.h"
#include "Match.h"
#include "Tuple.h"

#include "Lz77.h"
#include "SuffixArray.h"

ifstream input;
ofstream output;

void index_main(Arguments& args) {
	input.open(args.filename, ios::in);
	if (input.fail()) {
		cout << "ERROR: The file " << args.filename << " is not acessible" << endl;
		return;
	}
	cout << args << endl;

	output.open(args.getIndexName(), ios::out | ios::binary);
	output << int_encode(args.opt_ls) << int_encode(args.opt_ll);
	unsigned int lineNum = 0;
	for (string text; ((lineNum < args.opt_lines) || !args.opt_lines) && getline(input, text);) {
		vector<unsigned int> sa = gen_suffix_array(text);
		output << int_encode(sa.size());
		for (const unsigned int i : sa) {
			output << int_encode(i);
		}
		string encoded = lz77_encode(text, args.opt_ls, args.opt_ll);
		output << int_encode(encoded.size()) << encoded;

		cout << "\r" << ++lineNum;
		if (args.opt_lines)
			cout << '/' << args.opt_lines;
		cout << " lines indexed" << flush;
	} cout << endl;
}

char intBuffer[4];
string intString;
inline bool readInt() {
	bool out = (bool)input.read(intBuffer, 4);
	intString = string(intBuffer, 4);
	return out;
}

void search_main(Arguments& args) {
	queue<Match> matches;	// Os matches encontrados vão pra cá
	unsigned int count = 0;	// Se não for para imprimir, eles são contados aqui

	input.open(args.filename, ios::in | ios::binary);
	if (input.fail()) {
		cout << "ERROR: The file " << args.filename << " is not acessible" << endl;
		return;
	}

	// Parâmetros da compressão
	readInt();
	args.opt_ls = int_decode(intString);
	readInt();
	args.opt_ll = int_decode(intString);
	cout << args << endl;

	for (unsigned int lineNum = 1; ((lineNum <= args.opt_lines) || !args.opt_lines) && readInt();) {
		unsigned int lineSize = int_decode(intString);
		vector<unsigned int> sa(lineSize, 0);
		for (unsigned int i = 0; i < lineSize; i++) {
			readInt();
			sa[i] = int_decode(intString);
		}

		readInt();
		lineSize = int_decode(intString);
		vector<Tuple> line(lineSize / 9, Tuple());
		for (unsigned int i = 0; i < line.size(); i++) {
			readInt();
			line[i].p = int_decode(intString);
			readInt();
			line[i].l = int_decode(intString);
			input.get(line[i].c);
		}
		string decoded = lz77_decode(line, args.opt_ls, args.opt_ll);

		if (args.opt_count)
			count += sa_search(decoded, args.patterns, sa);
		else
			sa_search(decoded, args.patterns, sa, lineNum, matches);

		cout << "\r" << lineNum++;
		if (args.opt_lines)
			cout << '/' << args.opt_lines;
		cout << " lines searched" << flush;
	} cout << endl;

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

	try {
		Arguments args = Arguments(argc, argv);
		if (args.index_mode) index_main(args);
		else search_main(args);
	} catch (int error) {
		cout << "ERROR: This mode is invalid" << endl;
		return error;
	}

	auto tEnd = chrono::high_resolution_clock::now();
	chrono::duration<double> elapsed = tEnd - tStart;
	cout << "Execution time: " << elapsed.count() << endl;

	return 0;
}