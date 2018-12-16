#ifndef __SUFFIXARRAY_H_INCLUDED__
#define __SUFFIXARRAY_H_INCLUDED__

#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include "Match.h"

using namespace std;

#define suffix(text, i) (&text[i])

struct suffix_comparer {
	string text;
	bool operator() (unsigned int i, unsigned int j) {
		return text.compare(i, text.size(), text, j, text.size()) < 0;
	}
} compare_suffix;

// Generates the suffix array of a text
inline vector<unsigned int> gen_suffix_array(string& text) {
	vector<unsigned int> sa (text.size(), 0);
	for (unsigned int i = 0; i < sa.size(); i++)
		sa[i] = i;
	compare_suffix.text = text;
	sort(sa.begin(), sa.end(), compare_suffix);
	return sa;
}

// Finds the first string (lexicographic order) in the string array which succedes the pattern.
unsigned int succ(string& text, string& pattern, vector<unsigned int>& sa) {
	if (pattern.compare(suffix(text, sa[text.size()-1])) > 0)
		return text.size();
	else if (pattern.compare(suffix(text, sa[0])) <= 0)
		return 0;
	else {
		unsigned int l = 0, r = text.size() - 1;
		while (r - l > 1) {
			unsigned int h = (l + r) >> 1;
			if (pattern.compare(suffix(text, sa[h])) <= 0)
				r = h;
			else
				l = h;
		}
		return r;
	}
}

inline void sa_search(string& txt, string& pat, vector<unsigned int>& sa,
		unsigned int line, queue<Match>& matches) {
	if (!sa.size()) return;
	unsigned int L = succ(txt, pat, sa);
	while (L < sa.size() && txt.compare(sa[L], pat.size(), pat) == 0) {
		matches.push(Match(line, sa[L], txt, pat.size()));
		L++;
	}
}

inline unsigned int sa_search(string& txt, string& pat, vector<unsigned int>& sa) {
	if (!sa.size()) return 0;
	unsigned int output = 0;
	unsigned int L = succ(txt, pat, sa);
	while (L < sa.size() && txt.compare(sa[L], pat.size(), pat) == 0) {
		output++;
		L++;
	}
	return output;
}

#endif