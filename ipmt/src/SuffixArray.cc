#define suffix(text, i) (&text[i])

struct suffix_comparer {
	string text;
	bool operator() (unsigned int i, unsigned int j) {
		/* O metodo compare de strings retorna -1 ou 1 dependendo de qual valor for maior, porém ambos
		 * são considerados valores 'true' pelo sort. Então o XOR abaixo converte as saídas 1 para 0
		 * para que elas sejam tratadas como 'false'.
		 */
		return text.compare(i, text.size(), text, j, text.size()) < 0;
		//return string(suffix(text, i)).compare(suffix(text, j)) ^ 1;
	}
} compare_suffix;

// Generates the suffix array of a text
inline vector<unsigned int> gen_suffix_array(string& text) {
	vector<unsigned int> sa (text.size(), 0);
	cout << "building" << endl;
	for (unsigned int i = 0; i < sa.size(); i++)
		sa[i] = i;
	compare_suffix.text = text;
	cout << "sorting" << endl;
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
	unsigned int L = succ(txt, pat, sa);
	while (L < sa.size() && txt.compare(sa[L], pat.size(), pat) == 0) {
		matches.push(Match(line, sa[L], txt, pat.size()));
		L++;
	}
}

inline unsigned int sa_search(string& txt, string& pat, vector<unsigned int>& sa) {
	unsigned int output = 0;
	unsigned int L = succ(txt, pat, sa);
	while (L < sa.size() && txt.compare(sa[L], pat.size(), pat) == 0) {
		output++;
		L++;
	}
	return output;
}
