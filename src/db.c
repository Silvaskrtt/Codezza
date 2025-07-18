#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <sqlite3.h>
#include "db.h"

sqlite3 *db = NULL; // Variável global do banco, acessível em outros arquivos

int conectar_banco(const char *caminho) {
    SetConsoleOutputCP(CP_UTF8); // Suporte a UTF-8 no terminal do Windows

    int rc = sqlite3_open(caminho, &db); // Atenção: passa o endereço de db
    if (rc) {
        fprintf(stderr, "Erro ao abrir o banco: %s\n", sqlite3_errmsg(db));
        return 0; // Falha
    } else {
        printf("Conexão com banco de dados estabelecida com sucesso!\n\n");
        return 1; // Sucesso
    }
}

int callback(void *NotUsed, int argc, char **argv, char **colName) {
    for (int i = 0; i < argc; i++) {
        printf("%s: %s\n", colName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("--------------\n");
    return 0;
}

char* gerar_novo_id(sqlite3 *db, const char *prefixo, const char *tabela, const char *coluna_id);