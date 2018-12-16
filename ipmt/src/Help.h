// Todo o código da ajuda ao usuário vai aqui
#ifndef __HELP_H_INCLUDED__
#define __HELP_H_INCLUDED__

#include <iostream>
#include <string>
#include "Arguments.h"

using namespace std;

// Constantes
const string HELP_LINES =	"-l, --lines:\n"
							"	Define a quantidade de linhas a ser indexada / buscada.\n"
							"	Padrão: 0 (indexar / buscar em todo o arquivo)\n";
const string HELP_LS =	"--ls:\n"
						"	Define o parâmetro ls para a compressão.\n"
						"	Padrão: 256\n";
const string HELP_LL =	"--ll:\n"
						"	Define o parâmetro ll para a compressão.\n"
						"	Padrão: 128\n";
const string HELP_C =	"-c, --count:\n"
						"	Apenas conta o nº de ocorrências. Não recebe argumentos.\n";

// Exibe o texto de ajuda
int show_help(int argc, char* argv[]) {
	if (argc == 2) {
		cout << "Esta aplicação possui 2 modos: indexação e busca." << endl;
		cout << "Na indexação será gerado um arquivo índice"
		" que será usado pelo modo de busca depois." << endl;
		cout << "Já o modo de busca realiza a busca de um padrão no arquivo índice dado." << endl;
		cout << "Execução:" << endl;
		cout << "Indexação: ipmt index [opções] [arquivo]" << endl;
		cout << "Busca    : ipmt search [opções] [padrão] [arquivo]" << endl;
		cout << "Argumentos:" << endl;
		cout << "opções  : Opções do programa. Mais detalhes em 'Opções'." << endl;
		cout << "padrão  : Padrão a ser buscado." << endl;
		cout << "arquivo : Arquivo a ser lido para gerar o arquivo índice"
		" (modo indexação) ou para se realizar a busca nele (modo busca)." << endl;
		cout << "Opções (Geral):" << endl;
		cout << HELP_LINES << endl;
		cout << "Opções (Indexação):" << endl;
		cout << HELP_LS << HELP_LL;
		cout << "Opções (Busca):" << endl;
		cout << HELP_C;
		cout << "Adicionando uma das opções após -h ou --help, é possível receber informação apenas sobre ela." << endl;
	} else {
		if (!(Arguments::NAME_L.compare(argv[2]) && Arguments::NAME_LINES.compare(argv[2])))
			cout << HELP_LINES;
		if (!Arguments::NAME_INDEX_LS.compare(argv[2]))
			cout << HELP_LS;
		if (!Arguments::NAME_INDEX_LL.compare(argv[2]))
			cout << HELP_LS;
		if (!Arguments::NAME_SEARCH_C.compare(argv[2]))
			cout << HELP_C;
	}
}

#endif