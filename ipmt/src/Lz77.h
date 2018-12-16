#ifndef __LZ77_H_INCLUDED__
#define __LZ77_H_INCLUDED__

#include <climits>
#include <cmath>
#include <iostream>
#include <vector>
#include "Tuple.h"

using namespace std;

// Builds the finite state machine
vector< vector<unsigned int> > build_fsm(string& pat) {
	vector< vector<unsigned int> > delta(pat.size() + 1, vector<unsigned int>(256, 0));
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
void print_fsm(string& pat, vector< vector<unsigned int> >& delta) {
	cout << "  ";
	for (unsigned int i = 0; i <= UCHAR_MAX; i++) {
		cout << i << ' ';
	} cout << endl;
	for (unsigned int i = 0; i < pat.size(); i++) {
		cout << pat[i] << ' ';
		for (unsigned int j = 0; j <= UCHAR_MAX; j++) {
			cout << delta[i][j] << ' ';
		} cout << endl;
	}
}

void prefix_match(string window, string pat, unsigned int& pos, unsigned int& maxlen) {
	vector< vector<unsigned int> > fsm = build_fsm(pat);
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
	string code = string(txt.size() * 9, 0);
	unsigned int p, l, i = 0;
	for (unsigned int j = ls; j < W.size(); j += l + 1) {
		unsigned int tempindex = min((unsigned int)W.size(), j+ll);
		prefix_match(W.substr(j-ls, tempindex - (j-ls)), W.substr(j, tempindex - j), p, l);
		string temp = int_encode(p);
		for (unsigned int k = 0; k < 4; k++) {
			code[i + k] = temp[k];
		}
		i += 4;
		temp = int_encode(l);
		for (unsigned int k = 0; k < 4; k++) {
			code[i + k] = temp[k];
		}
		i += 4;
		code[i] = W[j+l];
		i++;
	}
	code.resize(i);
	return code;
}

// Decodes an unsigned int encoded as a string
unsigned int int_decode(string x) {
	unsigned int power = 1, val = 0, c = x.size();
	for (unsigned int i = 0; i < x.size(); i++)
		val = (val << CHAR_BIT) + (unsigned char)x[i];
	return val;
}

// Decodes the string
string lz77_decode(vector<Tuple>& code, unsigned int ls, unsigned int ll) {
	string txt = string(ls, 0);
	unsigned int sb_init = 0;
	for (unsigned int i = 0; i < code.size(); i++) {
		for (unsigned int j = 0; j < code[i].l; j++)
			txt += txt[sb_init + code[i].p + j];
		txt += code[i].c;
		sb_init += code[i].l + 1;
	}
	return txt.erase(0, ls);
}

#endif