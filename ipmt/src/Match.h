#ifndef __MATCH_H_INCLUDED__
#define __MATCH_H_INCLUDED__

#include <ostream>
#include <string>
#include "Formatting.h"

using namespace std;

class Match {
	public:
		int line;
		int column;
		string text;
		Match(int line, int column, string text, int patternSize);
		friend ostream& operator<<(ostream& os, const Match& args);
};

Match::Match(int line, int column, string text, int patternSize) {
	this->line = line;
	this->column = column;
	this->text = text;
	this->text.insert(column + patternSize, FORMAT_RESET);
	this->text.insert(column, FORMAT_MATCH);
}

ostream& operator<<(ostream& os, const Match& match) {
	os << FORMAT_POS << match.line << FORMAT_RESET << ":"
		<< FORMAT_POS << match.column << FORMAT_RESET << ":" << match.text;
	return os;  
}

#endif