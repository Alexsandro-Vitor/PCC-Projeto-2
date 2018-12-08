#include <unordered_set>

class Arguments {
	public:
		static const string NAME_H;
		static const string NAME_HELP;
		//string pattern;
		unordered_set<string> patterns;
		string textFile;
		Arguments(int count, char** arguments);
		friend ostream& operator<<(ostream& os, const Arguments& args);
};

const string Arguments::NAME_H = "-h";
const string Arguments::NAME_HELP = "--help";

Arguments::Arguments(int count, char** arguments) {
}

ostream& operator<<(ostream& os, const Arguments& args) {
	os << "Arguments()";
	return os;  
} 