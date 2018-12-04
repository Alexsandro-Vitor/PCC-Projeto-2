// Todo o código da ajuda ao usuário vai aqui

// Constantes


// Exibe o texto de ajuda
int show_help(int argc, char* argv[]) {
	if (argc == 2) {
		cout << "Esta aplicação possui 2 modos: indexação e busca." << endl;
		cout << "Na indexação será gerado um arquivo índice"
		" que será usado pelo modo de busca depois." << endl;
		cout << "Já o modo de busca realiza a busca de um padrão no arquivo índice dado." << endl;
		cout << "Execução:" << endl;
		cout << "Indexação: ipmt index [opções] [arquivo]" << endl;
		cout << "Busca    : ipmt search [padrão] [arquivo]" << endl;
		cout << "Argumentos:" << endl;
		cout << "opções  : Opções do programa. Mais detalhes em 'Opções'." << endl;
		cout << "padrão  : Padrão a ser buscado (se não for usado um arquivo para isso)." << endl;
		cout << "arquivos: Arquivo a ser lido para gerar o arquivo índice"
		" (modo indexação) ou para se realizar a busca nele (modo busca)." << endl;
		cout << "Opções: (TODO)" << endl;
	} else {

	}
}