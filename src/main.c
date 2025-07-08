// Código principal (ex: `crm_PIZZA.c`)
#include <stdio.h>
#include <sqlite3.h>

int main() {
    sqlite3 *db;
    char *erro = 0;
    int rc;

    rc = sqlite3_open("CRM_PIZZA.db", &db);

    if (rc) {
        fprintf(stderr, "Erro ao abrir o banco: %s\n", sqlite3_errmsg(db));
        return 1;
    } else {
        printf("Conexao com banco de dadis estabelecida com sucesso!\n");
    }

}