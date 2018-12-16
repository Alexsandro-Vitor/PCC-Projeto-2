#ifndef __LZ77_H_INCLUDED__
#define __LZ77_H_INCLUDED__

#include <climits>
#include <cmath>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

// Builds the finite state machine
vector< unordered_map<char, int> > build_fsm(string& pat) {
	vector< unordered_map<char, int> > delta(pat.size() + 1);
	for (unsigned short c = 0; c <= UCHAR_MAX; c++)
		delta[0][c] = 0;
	delta[0][pat[0]] = 1;
	int brd = 0;
	for (unsigned int i = 1; i <= pat.size(); i++) {
		for (unsigned short c = 0; c <= UCHAR_MAX; c++)
			delta[i][c] = delta[brd][c];
		delta[i][pat[i]] = i + 1;
		brd = delta[brd][pat[i]];
	}
	for (unsigned short c = 0; c <= UCHAR_MAX; c++)
		delta[pat.size()][c] = delta[brd][c];
	return delta;
}

//Prints the fsm
void print_fsm(string& pat, string& ab, vector< unordered_map<char, int> >& delta) {
	cout << "  ";
	for (unsigned int i = 0; i < ab.size(); i++) {
		cout << ab[i] << ' ';
	} cout << endl;
	for (unsigned int i = 0; i < pat.size(); i++) {
		cout << pat[i] << ' ';
		for (unsigned int j = 0; j < ab.size(); j++) {
			cout << delta[i][ab[j]] << ' ';
		} cout << endl;
	}
}

void prefix_match(string window, string pat, unsigned int& pos, unsigned int& maxlen) {
	vector< unordered_map<char, int> > fsm = build_fsm(pat);
	pos = maxlen = 0;
	unsigned int cur = 0, ls = window.size() - pat.size();
	for (unsigned int i = 0; i < window.size();) {
		cur = fsm[cur][window[i]];
		if (++i - cur < ls && cur > maxlen) {
			maxlen = cur;
			pos = i - cur;
		}
	}
	maxlen = min(maxlen, (unsigned int)pat.size() - 1);
}

const unsigned char BYTES_INT = 4;

// Essa versão do int_encode gera uma string de 4 caracteres que representa o inteiro de 4 bytes
string int_encode(unsigned int x) {
	string code = string(BYTES_INT, 0);
	for (unsigned int i = BYTES_INT - 1; x; i--) {
		unsigned int bit = x & UCHAR_MAX;
		code[i] = bit;
		x >>= CHAR_BIT;
	}
	return code;
}

// Encodes the string
string lz77_encode(string txt, unsigned int ls, unsigned int ll) {
	string W = string(ls, 0) + txt;
	string code;
	unsigned int p, l;
	for (unsigned int j = ls; j < W.size(); j += l + 1) {
		unsigned int tempindex = min((unsigned int)W.size(), j+ll);
		prefix_match(W.substr(j-ls, tempindex - (j-ls)), W.substr(j, tempindex - j), p, l);
		code += int_encode(p);
		code += int_encode(l);
		code += W[j+l];
	}
	return code;
}

unsigned int int_decode(string x) {
	unsigned int power = 1, val = 0, c = x.size();
	for (unsigned int i = 0; i < x.size(); i++) {
		val <<= CHAR_BIT;
		val += x[i];
	}
	return val;
}

// Decodes the string
string lz77_decode(string& code, unsigned int ls, unsigned int ll, string& ab) {
	string txt = string(ls, ab[0]);
	double logl = log(ab.size());
	unsigned int bs = (unsigned int)ceil(log(ls) / logl), bl = (unsigned int)ceil(log(ll) / logl);
	unsigned int j = 0, sb_init = 0;
	while (j < code.size()) {
		unsigned int p = int_decode(code.substr(j, bs));
		j += bs;
		unsigned int l = int_decode(code.substr(j, bl));
		j += bl;
		for (unsigned int i = 0; i < l; i++)
			txt += txt[sb_init + p + i];
		txt += code[j++];
		sb_init += l + 1;
	}
	return txt.erase(0, ls);
}

#endif