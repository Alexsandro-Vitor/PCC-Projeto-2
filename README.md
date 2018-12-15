# PCC Projeto 2 - Indexed Pattern Matching Tool

Projeto realizado para a cadeia de Processamento de Cadeia de Caracteres 2018.2

**Autor:** Alexsandro Vítor Serafim de Carvalho - avsc

Este projeto consiste em um indexador que gera índices para busca de padrões e um buscador de padrões para os índices gerados pela funcionalidade anterior.

## Compilação
### Windows
* **Da raiz do projeto:** `src\make.bat`

### Linux
* **Na pasta src:** `make`
* **Da raiz do projeto:** `src/make.sh`

## Execução
* **Modo indexação:** `bin/ipmt index [opções] [arquivo]`
* **Modo busca:** `bin/ipmt search [opções] [padrão] [arquivo]`

opções (opcional): Ver "Opções Disponíveis".

padrão: A string a ser buscada.

arquivo: Arquivo a ser lido para gerar o arquivo índice ou para se fazer a busca nele.

## Opções Disponíveis
### Indexação
* `-a`, `--alphabet`: Define o alfabeto para a compressão.
Padrão: "0123456789abcdefghijklmnopqrstuvwxyz"
* `--ls`: Define o parâmetro ls para a compressão.
Padrão: 10
* `--ll`: Define o parâmetro ll para a compressão.
### Busca
Padrão: 5
* `-c`, `--count`: Apenas conta o nº de ocorrências. Não recebe argumentos.
