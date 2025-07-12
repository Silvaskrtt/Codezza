#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include "db.h" // Aqui já vem o db global

void inserirCliente(sqlite3 *db, const char *nome, const char *sobrenome) {
    sqlite3_stmt *stmt;
    char novoID[11]; // Pega o início do ID "CLI" + 3 dígitos

    // Busca o último ID
    const char *sqlUltimoID = "SELECT ID_Cliente_PK FROM tbl_Cliente ORDER BY ID_Cliente_PK DESC LIMIT 1;";
    if (sqlite3_prepare_v2(db, sqlUltimoID, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Erro ao preparar SELECT: %s\n", sqlite3_errmsg(db));
        return;
    }

    int ultimoNumero = 0;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        const unsigned char *ultimoID = sqlite3_column_text(stmt, 0);
        if (ultimoID != NULL && strlen((const char *)ultimoID) >= 6) {
            ultimoNumero = atoi((const char *)ultimoID + 3); // Pula "CLI"
        }
    }
    sqlite3_finalize(stmt);

    // Gera novo ID
    sprintf(novoID, "CLI%03d", ultimoNumero + 1);

    // Inserindo novo cliente
    const char *sqlInsert = "INSERT INTO tbl_Cliente(ID_Cliente_PK, Nome, Sobrenome) VALUES (?, ?, ?)";
    if (sqlite3_prepare_v2(db, sqlInsert, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Erro ao preparar INSERT: %s\n", sqlite3_errmsg(db));
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
}

int main() {
    if (!conectar_banco("C:/Users/Murilo/Documents/Codezza/database/CODEZZA.db")) {
        return 1;
    }

    char nome[100];
    char sobrenome[100];

    printf("Nome do cliente: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0'; // Remove o \n

    printf("Sobrenome do cliente: ");
    fgets(sobrenome, sizeof(sobrenome), stdin);
    sobrenome[strcspn(sobrenome, "\n")] = '\0';

    inserirCliente(db, nome, sobrenome);

    sqlite3_close(db); // Fecha a conexão ao final
    return 0;
}