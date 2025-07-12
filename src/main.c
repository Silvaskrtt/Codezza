#include <stdio.h>
#include "db.h"

int main() {
    if (!conectar_banco("C:/Users/Murilo/Documents/Codezza/database/CODEZZA.db")) {
        return 1;
    }

    // Exemplo de SELECT usando callback
    char *erro = 0;
    const char *sql = "SELECT * FROM tbl_Pedido;";

    if (sqlite3_exec(db, sql, callback, 0, &erro) != SQLITE_OK) {
        fprintf(stderr, "Erro na execução: %s\n", erro);
        sqlite3_free(erro);
    }

    sqlite3_close(db); // Fecha a conexão ao final
    return 0;
}
