#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include "db.h" // db deve estar declarado como extern sqlite3 *db;

// Agora retorna o novo ID do cliente
char* cadastrarCliente(sqlite3 *db, const char *nome, const char *sobrenome) {
    sqlite3_stmt *stmt;
    char *novoID = malloc(11); // Aloca para retorno

    const char *sqlUltimoID = "SELECT ID_Cliente_PK FROM tbl_Cliente ORDER BY ID_Cliente_PK DESC LIMIT 1;";
    if (sqlite3_prepare_v2(db, sqlUltimoID, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Erro ao preparar SELECT: %s\n", sqlite3_errmsg(db));
        free(novoID);
        return NULL;
    }

    int ultimoNumero = 0;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        const unsigned char *ultimoID = sqlite3_column_text(stmt, 0);
        if (ultimoID && strlen((const char *)ultimoID) >= 6) {
            ultimoNumero = atoi((const char *)ultimoID + 3); // Pula "CLI"
        }
    }
    sqlite3_finalize(stmt);

    // Gerando novo ID
    sprintf(novoID, "CLI%03d", ultimoNumero + 1);

    const char *sqlInsert = "INSERT INTO tbl_Cliente(ID_Cliente_PK, Nome, Sobrenome) VALUES (?, ?, ?)";
    if (sqlite3_prepare_v2(db, sqlInsert, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Erro ao preparar INSERT: %s\n", sqlite3_errmsg(db));
        free(novoID);
        return NULL;
    }

    sqlite3_bind_text(stmt, 1, novoID, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, nome, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, sobrenome, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        printf("Erro ao executar INSERT: %s\n", sqlite3_errmsg(db));
        free(novoID);
        novoID = NULL;
    } else {
        printf("Cliente cadastrado com ID: %s\n", novoID);
    }

    sqlite3_finalize(stmt);
    return novoID;
}

void addTelefoneCliente(sqlite3 *db, const char *id_cliente_pk, const char *num_telefone) {
    sqlite3_stmt *stmt;
    char novoID[11];

    const char *sqlUltimoID = "SELECT ID_Telefone_PK FROM tbl_Telefone_Cliente ORDER BY ID_Telefone_PK DESC LIMIT 1;";
    if (sqlite3_prepare_v2(db, sqlUltimoID, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Erro ao preparar SELECT: %s\n", sqlite3_errmsg(db));
        return;
    }

    int ultimoNumero = 0;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        const unsigned char *ultimoID = sqlite3_column_text(stmt, 0);
        if (ultimoID && strlen((const char *)ultimoID) >= 6) {
            ultimoNumero = atoi((const char *)ultimoID + 3);
        }
    }
    sqlite3_finalize(stmt);

    // Gerando novo ID
    sprintf(novoID, "TEL%03d", ultimoNumero + 1);

    const char *sqlInsert = "INSERT INTO tbl_Telefone_Cliente(ID_Telefone_PK, ID_Cliente_FK, Num_Telefone) VALUES (?, ?, ?)";
    if (sqlite3_prepare_v2(db, sqlInsert, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Erro ao preparar INSERT: %s\n", sqlite3_errmsg(db));
        return;
    }

    sqlite3_bind_text(stmt, 1, novoID, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, id_cliente_pk, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, num_telefone, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        printf("Erro ao executar INSERT: %s\n", sqlite3_errmsg(db));
    } else {
        printf("Telefone cadastrado com ID: %s\n", novoID);
    }

    sqlite3_finalize(stmt);
}

int main() {
    if (!conectar_banco("C:/Users/Murilo/Documents/Codezza/database/CODEZZA.db")) {
        return 1;
    }

    char nome[100], sobrenome[100], telefone[12];

    printf("Nome do cliente: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    printf("Sobrenome do cliente: ");
    fgets(sobrenome, sizeof(sobrenome), stdin);
    sobrenome[strcspn(sobrenome, "\n")] = '\0';

    printf("Telefone do cliente: ");
    fgets(telefone, sizeof(telefone), stdin);
    telefone[strcspn(telefone, "\n")] = '\0';

    char *id_cliente_pk = cadastrarCliente(db, nome, sobrenome);

    if (id_cliente_pk != NULL) {
        addTelefoneCliente(db, id_cliente_pk, telefone);
        free(id_cliente_pk);
    }

    sqlite3_close(db);
    return 0;
}