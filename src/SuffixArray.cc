#define suffix(text, i) (&text[i])

struct suffix_comparer {
	string text;
	bool operator() (unsigned int i, unsigned int j) {
		/* O metodo compare de strings retorna -1 ou 1 dependendo de qual valor for maior, porém ambos
		 * são considerados valores 'true' pelo sort. Então o XOR abaixo converte as saídas 1 para 0
		 * para que elas sejam tratadas como 'false'.
		 */
		return string(suffix(text, i)).compare(suffix(text, j)) ^ 1;
	}
} compare_suffix;

// Finds the first string (lexicographic order) in the string array which is after the pattern.
int succ(string text, string pattern, vector<unsigned int>& sa) {
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
