// Builds the finite state machine
vector< unordered_map<char, int> > build_fsm(string& pat, string& ab) {
	vector< unordered_map<char, int> > delta(pat.size() + 1);
	for (const char c : ab)
		delta[0][c] = 0;
	delta[0][pat[0]] = 1;
	int brd = 0;
	for (unsigned int i = 1; i <= pat.size(); i++) {
		for (const char a : ab)
			delta[i][a] = delta[brd][a];
		delta[i][pat[i]] = i + 1;
		brd = delta[brd][pat[i]];
	}
	for (const char a : ab)
		delta[pat.size()][a] = delta[brd][a];
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

void prefix_match(string window, string pat, string& ab, unsigned int& pos, unsigned int& maxlen) {
	vector< unordered_map<char, int> > fsm = build_fsm(pat, ab);
	pos = maxlen = 0;
	unsigned int cur = 0, ls = window.size() - pat.size();
	for (unsigned int i = 0; i < window.size();) {
		cur = fsm[cur][window[i]];
		if (++i - cur < ls && cur > maxlen) {
			maxlen = cur;
			pos = i - cur;
		}
	}
	maxlen = min(maxlen, pat.size() - 1);
}

string int_encode(unsigned int x, string& ab) {
	if (!x) return string(1, ab[0]);
	string code;
	while (x) {
		unsigned int bit = x % ab.size();
		code = ab[bit] + code;
		x /= ab.size();
	}
	return code;
}

// Encodes the string
string lz77_encode(string txt, unsigned int ls, unsigned int ll, string ab) {
	string W = string(ls, ab[0]) + txt;
	string code;
	unsigned int p, l;
	for (unsigned int j = ls; j < W.size(); j += l + 1) {
		unsigned int tempindex = min(W.size(), j+ll);
		prefix_match(W.substr(j-ls, tempindex - (j-ls)), W.substr(j, tempindex - j), ab, p, l);
		code += int_encode(p, ab);
		code += int_encode(l, ab);
		code += W[j+l];
	}
	return code;
}

unsigned int int_decode(string x, string& ab) {
	unsigned int power = 1, val = 0, c = x.size();
	do {
		c--;
		//cout << c << ' ' << x[c] << ' ' << ab.find(x[c]) << endl;
		val += power * ab.find(x[c]);
		power *= ab.size();
	} while (c);
	return val;
}

// Decodes the string
string lz77_decode(string& code, unsigned int ls, unsigned int ll, string& ab) {
	string txt = string(ls, ab[0]);
	double logl = log(ab.size());
	unsigned int bs = (unsigned int)ceil(log(ls) / logl), bl = (unsigned int)ceil(log(ll) / logl);
	unsigned int j = 0, sb_init = 0;
	while (j < code.size()) {
		unsigned int p = int_decode(code.substr(j, bs), ab);
		j += bs;
		unsigned int l = int_decode(code.substr(j, bl), ab);
		j += bl;
		for (unsigned int i = 0; i < l; i++)
			txt += txt[sb_init + p + i];
		txt += code[j++];
		sb_init += l + 1;
	}
	return txt.erase(0, ls);
}