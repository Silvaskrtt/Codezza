// Código principal
#include <stdio.h>
#include <sqlite3.h>

int main() {

    //Estabelencendo uma conexão com banco de dados
    sqlite3 *db;
    char *erro = 0;
    int rc;

    // abrindo o banco de dados
    rc = sqlite3_open("C:/Users/Murilo/Documents/Projeto_CRM_PIZZA/database/CRM_PIZZA.db", &db);
    // Verificando se a conexão deu certo
    if (rc) {
        fprintf(stderr, "Erro ao abrir o banco: %s\n", sqlite3_errmsg(db));
        return 1;
    } else {
        printf("Conexao com banco de dados estabelecida com sucesso!\n");
    }
}