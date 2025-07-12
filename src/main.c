#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <sqlite3.h>

int callback(void *NotUsed, int argc, char **argv, char **colName) {
    for (int i = 0; i < argc; i++) {
        printf("%s: %s\n", colName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("--------------\n");
    return 0;
}

int main() {
    // Configura o terminal para usar UTF-8
    SetConsoleOutputCP(CP_UTF8);

    // Estabelecendo conexão com o banco de dados
    sqlite3 *db;
    char *erro = 0;
    int rc;

    rc = sqlite3_open("C:/Users/Murilo/Documents/Codezza/database/CODEZZA.db", &db);
    if (rc) {
        fprintf(stderr, "Erro ao abrir o banco: %s\n", sqlite3_errmsg(db));
        return 1;
    } else {
        printf("Conexão com banco de dados estabelecida com sucesso!\n\n");
    }

    // Consulta de simples de Select

    //const char *sql = "SELECT * FROM tbl_Cliente;";
    const char *sql = 
        "SELECT c.ID_Cliente_PK, c.Nome, c.Sobrenome, "
        "t.Num_Telefone, "
        "e.Rua, e.Num_Casa, e.Bairro, e.Cidade "
        "FROM tbl_Cliente c "
        "LEFT JOIN tbl_Telefone_Cliente t ON c.ID_Cliente_PK = t.ID_Cliente_FK "
        "LEFT JOIN tbl_Endereco_Cliente e ON c.ID_Cliente_PK = e.ID_Cliente_FK "
        "ORDER BY c.ID_Cliente_PK;";

    rc = sqlite3_exec(db, sql, callback, 0, &erro);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erro ao executar SELECT: %s\n", erro);
        sqlite3_free(erro);
    }

    sqlite3_close(db);
    return 0;
}