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
}

void addTelefoneCliente(sqlite3 *db, const char *id_cliente_fk, const char *num_telefone) {
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
    sqlite3_bind_text(stmt, 2, id_cliente_fk, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, num_telefone, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        printf("Erro ao executar INSERT: %s\n", sqlite3_errmsg(db));
    } else {
        printf("Telefone cadastrado com ID: %s\n", novoID);
    }

    sqlite3_finalize(stmt);
}

char* addEnderecoCliente(sqlite3 *db, const char *rua, const char *num_casa, const char *bairro, const char *cidade, const char *id_cliente_fk) {
    sqlite3_stmt *stmt;
    char novoID[11];

    const char *sqlUltimoID = "SELECT ID_Endereco_PK FROM tbl_Endereco_Cliente ORDER BY ID_Endereco_PK DESC LIMIT 1;";
    if (sqlite3_prepare_v2(db, sqlUltimoID, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Erro ao preparar SELECT: %s\n", sqlite3_errmsg(db));
        return NULL;
}

    int ultimoNumero = 0;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        const unsigned char *ultimoID = sqlite3_column_text(stmt, 0);
        if (ultimoID && strlen((const char*)ultimoID) >= 6) {
            ultimoNumero = atoi((const char *)ultimoID + 3);
        }
    }
    sqlite3_finalize(stmt);

    // Gerando novo ID
    sprintf(novoID, "END%03d", ultimoNumero + 1);

    const char *sqlInsert = "INSERT INTO tbl_Endereco_Cliente(ID_Endereco_PK, Rua, Num_Casa, Bairro, Cidade, ID_Cliente_FK) VALUES (?, ?, ?, ?, ?, ?)";
    if (sqlite3_prepare16_v2(db, sqlInsert, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Erro ao preparar INSERT: %s\n", sqlite3_errmsg(db));
        return NULL;
    }

    sqlite3_bind_text(stmt, 1, novoID, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, id_cliente_fk, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, rua, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, num_casa, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, bairro, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 6, cidade, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        printf("Erro ao executar INSERT: %s\n", sqlite3_errmsg(db));
    } else {
        printf("Endereço cadastrado com ID: %s\n", novoID);
    }
    
    sqlite3_finalize(stmt);
}

int main() {
    if (!conectar_banco("C:/Users/Murilo/Documents/Codezza/database/CODEZZA.db")) {
        return 1;
    }

    char nome[100], sobrenome[100], telefone[12], rua[50], num_casa[10], bairro[50], cidade[50];

    printf("Nome do cliente: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    printf("Sobrenome do cliente: ");
    fgets(sobrenome, sizeof(sobrenome), stdin);
    sobrenome[strcspn(sobrenome, "\n")] = '\0';

    printf("Telefone do cliente: ");
    fgets(telefone, sizeof(telefone), stdin);
    telefone[strcspn(telefone, "\n")] = '\0';

    printf("Rua: ");
    fgets(rua, sizeof(rua), stdin);
    rua[strcspn(rua, "\n")] = '\0';

    printf("Numero da Casa: ");
    fgets(num_casa, sizeof(num_casa), stdin);
    num_casa[strcspn(num_casa, "\n")] = '\0';

    printf("Bairro: ");
    fgets(bairro, sizeof(bairro), stdin);
    bairro[strcspn(bairro, "\n")] = '\0';

    printf("Cidade: ");
    fgets(cidade, sizeof(cidade), stdin);
    cidade[strcspn(cidade, "\n")] = '\0';

    char *id_cliente_pk = cadastrarCliente(db, nome, sobrenome);

    if (id_cliente_pk != NULL) {
        addTelefoneCliente(db, id_cliente_pk, telefone);
        addEnderecoCliente(db, id_cliente_pk, rua, num_casa, bairro, cidade);
        free(id_cliente_pk);
    }

    sqlite3_close(db);
    return 0;
}