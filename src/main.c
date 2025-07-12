#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include "db.h"

void inserirCliente(sqlite3 *db, const char *nome, const char *sobrenome) {
    sqlite3_stmt *stmt;
    char novoID[11]; // Pega o Inicio do ID "CLI" + 3 digitos + '\0'

    // Busca o ultimo ID
    const char *sqlUltimoID = "SELECT ID_Cliente_PK FROM tbl_Cliente ORDER BY ID_Cliente_PK DESC LIMIT 1;";
    if (sqlite3_prepare_v2(db, sqlUltimoID, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Erro ao preparar SELECT: %s\n", sqlite3_errmsg(db));
        return;
}

int ultimoNumero = 0;
if (sqlite3_step(stmt) == SQLITE_ROW) {
    const unsigned char *ultimoID = sqlite3_column_text(stmt, 0);
    if (ultimoID != NULL && strlen((const char *)ultimoID) >= 6) {
        ultimoNumero = atoi((const char *)ultimoID + 3); // Pegando apenas os numeros depois do CLI
    }
}
sqlite3_finalize(stmt);

//Gerando no ID
sprintf(novoID, "CLI%03d", ultimoNumero + 1);

// Inserindo novo Cliente
const char *sqlInsert = "INSERT INTO tbl_Cliente(ID_Cliente_PK, Nome, Sobrenome) VALUES(?, ?, ?)";
if (sqlite3_prepare_v2(db, sqlInsert, -1, &stmt, NULL) != SQLITE_OK) {
    printf("Erro ao executar INSERT: %s\n", sqlite3_errmsg(db));
    return;
}

sqlite3_bind_text(stmt, 1, novoID, -1, SQLITE_STATIC);
sqlite3_bind_text(stmt, 2, nome, -1, SQLITE_STATIC);
sqlite3_bind_text(stmt, 3, sobrenome, -1, SQLITE_STATIC);

if (sqlite3_step(stmt) != SQLITE_DONE) {
    printf("Erro ao executar INSERT: %s\n", sqlite3_errmsg(db));
} else {
    printf("Cliente inserido com ID: %s\n", novoID);
}

sqlite3_finalize(stmt);


int main() {
    if (!conectar_banco("C:/Users/Murilo/Documents/Codezza/database/CODEZZA.db")) {
        return 1;
    }

    // 
    char *erro = 0;
    const char *sql = "SELECT * FROM tbl_Pedido;";

    if (sqlite3_exec(db, sql, callback, 0, &erro) != SQLITE_OK) {
        fprintf(stderr, "Erro na execução: %s\n", erro);
        sqlite3_free(erro);
    }

    sqlite3_close(db); // Fecha a conexão ao final
    return 0;
}
