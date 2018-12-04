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
	return 0;
}