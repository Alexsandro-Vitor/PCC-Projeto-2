#include <unordered_set>

class Arguments {
	public:
		static const string NAME_H;
		static const string NAME_HELP;
		static const string NAME_INDEX;
		static const string NAME_INDEX_ALPHABET;
		static const string NAME_INDEX_LS;
		static const string NAME_INDEX_LL;
		static const string NAME_SEARCH;
		static const string NAME_SEARCH_C;
		static const string NAME_SEARCH_COUNT;
		bool index_mode;
		string opt_alphabet = "0123456789abcdefghijklmnopqrstuvwxyz";
		unsigned int opt_ls = 10;
		unsigned int opt_ll = 5;
		bool opt_count = false;
		unordered_set<string> patterns;
		string filename;
		Arguments(int count, char** arguments);
		void init_index(int count, char** args);
		void init_search(int count, char** args);
		string getIndexName();
		friend ostream& operator<<(ostream& os, const Arguments& args);
};

const string Arguments::NAME_H = "-h";
const string Arguments::NAME_HELP = "--help";

const string Arguments::NAME_INDEX = "index";
const string Arguments::NAME_INDEX_ALPHABET = "--alphabet";
const string Arguments::NAME_INDEX_LS = "--ls";
const string Arguments::NAME_INDEX_LL = "--ll";

const string Arguments::NAME_SEARCH = "search";
const string Arguments::NAME_SEARCH_C = "-c";
const string Arguments::NAME_SEARCH_COUNT = "--count";

Arguments::Arguments(int count, char** args) {
	if (!NAME_INDEX.compare(args[1])) init_index(count, args);
	if (!NAME_SEARCH.compare(args[1])) init_search(count, args);
}

inline void Arguments::init_index(int count, char** args) {
	index_mode = true;
	unsigned int i = 2;
	// Options
	for (; i < count; i++) {
		if (args[i][0] != '-') break;

		if (!NAME_INDEX_ALPHABET.compare(args[i]))
			opt_alphabet = args[++i];
		else if (!NAME_INDEX_LS.compare(args[i]))
			opt_ls = stoi(args[++i]);
		else if (!NAME_INDEX_LL.compare(args[i]))
			opt_ll = stoi(args[++i]);
	}
	// Text file
	if (i >= count)
		cout << "ERROR: Text file is missing" << endl;
	else
		filename = args[i];
}

inline void Arguments::init_search(int count, char** args) {
	index_mode = false;
	unsigned int i = 2;
	// Options
	for (; i < count; i++) {
		if (args[i][0] != '-') break;

		if (!(NAME_SEARCH_C.compare(args[i]) || NAME_SEARCH_COUNT.compare(args[i])))
			opt_count = args[++i];
	}
	// Pattern
	if (i >= count)
		cout << "ERROR: Pattern is missing" << endl;
	else {
		// TODO patternfile
		patterns.insert(args[i++]);
		// Index file
		if (i >= count)
			cout << "ERROR: Index file is missing" << endl;
		else
			filename = args[i];
	}
}

inline string Arguments::getIndexName() {
	return filename.substr(0, filename.find_last_of(".")) + ".idx";
}

ostream& operator<<(ostream& os, const Arguments& args) {
	os << "Arguments(" << endl;
	os << "\tmode = " << (args.index_mode ? "INDEX" : "SEARCH") << "," << endl;
	if (args.index_mode) {
		os << "\topt_alphabet = \"" << args.opt_alphabet << "\"," << endl;
		os << "\topt_ls = " << args.opt_ls << ',' << endl;
		os << "\topt_ll = " << args.opt_ll << ',' << endl;
	} else {
		os << "\topt_count = " << args.opt_count << ',' << endl;
		os << "\tpatterns = \"[" << endl;
		for (const string pattern : args.patterns)
			os << "\t\t\"" << pattern << "\"," << endl;
		os << "\t]" << endl;
	}
	os << "\tfilename = \"" << args.filename << '"' << endl;
	os << ')';
	return os;  
}