// Builds the finite state machine
void build_fsm(string pat, string ab, vector< unordered_map<char, int> >& delta) {
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
}

//Prints the fsm
void print_fsm(string pat, string ab, vector< unordered_map<char, int> >& delta) {
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

void prefix_match(string window, string pat, string ab, unsigned int& pos, unsigned int& maxlen) {
	vector< unordered_map<char, int> > fsm(pat.size() + 1);
	build_fsm(pat, ab, fsm);
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

void int_encode(unsigned int x, string ab, string& code) {
	code.clear();
	if (!x) code = ab[0];
	while (x) {
		unsigned int bit = x % ab.size();
		code = ab[bit] + code;
		x /= ab.size();
	}
}

void lz77_encode(string txt, unsigned int ls, unsigned int ll, string ab, string& code) {
	string W = string(ls, ab[0]) + txt;
	code.clear();
	unsigned int p, l;
	for (unsigned int j = ls; j < W.size(); j += l + 1) {
		unsigned int tempindex = min(W.size(), j+ll);
		cout << "window: " << W.substr(j-ls, tempindex - (j-ls)) << endl;
		cout << "pat: " << W.substr(j, tempindex - j) << endl;
		prefix_match(W.substr(j-ls, tempindex - (j-ls)), W.substr(j, tempindex - j), ab, p, l);
		string tempcode;
		int_encode(p, ab, tempcode);
		cout << "p = " << p << endl;
		cout << "int_encode(p) = " << tempcode << endl;
		code += tempcode;
		int_encode(l, ab, tempcode);
		cout << "l = " << l << endl;
		cout << "int_encode(l) = " << tempcode << endl;
		code += tempcode;
		cout << "W[j+l] = " << W[j+l] << endl;
		code += W[j+l];
	}
}

unsigned int int_decode(string x, string ab) {
	unsigned int power = 1, val = 0, c = x.size();
	do {
		c--;
		val += power * ab.find(x[c]);
		power *= ab.size();
	} while (c);
	return val;
}