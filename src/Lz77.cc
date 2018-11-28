// Builds the finite state machine
void build_fsm(string pat, string ab, vector< unordered_map<char, int> >& delta) {
	for (const char c : ab)
		delta[0][c] = 0;
	delta[0][pat[0]] = 1;
	int brd = 0;
	for (int i = 1; i <= pat.size(); i++) {
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
	for (int i = 0; i < ab.size(); i++) {
		cout << ab[i] << ' ';
	} cout << endl;
	for (int i = 0; i < pat.size(); i++) {
		cout << pat[i] << ' ';
		for (int j = 0; j < ab.size(); j++) {
			cout << delta[i][ab[j]] << ' ';
		} cout << endl;
	}
}

void prefix_match(string window, string pat, string ab, unsigned int& pos, unsigned int& maxlen) {
	vector< unordered_map<char, int> > fsm(pat.size() + 1);
	build_fsm(pat, ab, fsm);
	pos = maxlen = 0;
	int cur = 0, ls = window.size() - pat.size();
	for (int i = 0; i < window.size(); i++) {
		cur = fsm[cur][window[i]];
		if (cur > maxlen && i - cur + 1 < ls) {
			maxlen = cur;
			pos = i - cur + 1;
		}
	}
	maxlen = min(maxlen, pat.size() - 1);
}

void int_encode(int x, string ab, string& code) {
	code.clear();
	while (x) {
		int bit = x % ab.size();
		code = ab[bit] + code;
		x /= ab.size();
	}
}

void lz77_encode(string txt, int ls, int ll, string ab) {
	cout << "todo";
}