#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include "db.h"

// Função auxiliar para gerar novos IDs
char* gerar_novo_id(sqlite3 *db, const char *prefixo, const char *tabela, const char *coluna_id) {
    if (!db || !prefixo || !tabela || !coluna_id) {
        fprintf(stderr, "Parâmetros inválidos para gerar_novo_id\n");
        return NULL;
    }

    sqlite3_stmt *stmt = NULL;
    char *novoID = malloc(11); // Aloca espaço para o ID + null terminator
    if (!novoID) {
        fprintf(stderr, "Erro ao alocar memória para novo ID\n");
        return NULL;
    }
    memset(novoID, 0, 11); // Inicializa com zeros

    char sql[256];
    snprintf(sql, sizeof(sql), "SELECT %s FROM %s ORDER BY %s DESC LIMIT 1;", 
             coluna_id, tabela, coluna_id);
    
    int ultimoNumero = 0;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            const unsigned char *ultimoID = sqlite3_column_text(stmt, 0);
            if (ultimoID) {
                const char *ptr_numero = (const char *)ultimoID + strlen(prefixo);
                if (strlen(ptr_numero) > 0) {
                    ultimoNumero = atoi(ptr_numero);
                }
            }
        }
        sqlite3_finalize(stmt);
    } else {
        fprintf(stderr, "Erro ao buscar último ID: %s\n", sqlite3_errmsg(db));
        free(novoID);
        return NULL;
    }
    
    // Formata o novo ID com o prefixo e número sequencial
    snprintf(novoID, 11, "%s%03d", prefixo, ultimoNumero + 1);
    return novoID;
}

char* cadastrarCliente(sqlite3 *db, const char *nome, const char *sobrenome) {
    if (!db || !nome || !sobrenome || strlen(nome) == 0 || strlen(sobrenome) == 0) {
        fprintf(stderr, "Parâmetros inválidos para cadastrarCliente\n");
        return NULL;
    }

    char *novoID = gerar_novo_id(db, "CLI", "tbl_Cliente", "ID_Cliente_PK");
    if (!novoID) {
        fprintf(stderr, "Erro ao gerar novo ID para cliente\n");
        return NULL;
    }

    sqlite3_stmt *stmt;
    const char *sql = "INSERT INTO tbl_Cliente(ID_Cliente_PK, Nome, Sobrenome) VALUES (?, ?, ?)";
    
    int resultado = SQLITE_ERROR;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, novoID, -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 2, nome, -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 3, sobrenome, -1, SQLITE_TRANSIENT);
        
        resultado = sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    } else {
        fprintf(stderr, "Erro ao preparar statement: %s\n", sqlite3_errmsg(db));
        free(novoID);
        return NULL;
    }

    if (resultado != SQLITE_DONE) {
        fprintf(stderr, "Erro ao cadastrar cliente: %s\n", sqlite3_errmsg(db));
        free(novoID);
        return NULL;
    }

    printf("Cliente cadastrado com ID: %s\n", novoID);
    return novoID;
}

int addTelefoneCliente(sqlite3 *db, const char *id_cliente, const char *telefone) {
    if (!db || !id_cliente || !telefone || strlen(id_cliente) == 0 || strlen(telefone) == 0) {
        fprintf(stderr, "Parâmetros inválidos para addTelefoneCliente\n");
        return 0;
    }

    char *novoID = gerar_novo_id(db, "TEL", "tbl_Telefone_Cliente", "ID_Telefone_PK");
    if (!novoID) {
        fprintf(stderr, "Erro ao gerar novo ID para telefone\n");
        return 0;
    }

    sqlite3_stmt *stmt;
    const char *sql = "INSERT INTO tbl_Telefone_Cliente(ID_Telefone_PK, ID_Cliente_FK, Num_Telefone) VALUES (?, ?, ?)";
    
    int sucesso = 0;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, novoID, -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 2, id_cliente, -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 3, telefone, -1, SQLITE_TRANSIENT);
        
        if (sqlite3_step(stmt) == SQLITE_DONE) {
            printf("Telefone cadastrado com ID: %s\n", novoID);
            sucesso = 1;
        } else {
            fprintf(stderr, "Erro ao adicionar telefone: %s\n", sqlite3_errmsg(db));
        }
        sqlite3_finalize(stmt);
    } else {
        fprintf(stderr, "Erro ao preparar statement: %s\n", sqlite3_errmsg(db));
    }
    
    free(novoID);
    return sucesso;
}

char* addEnderecoCliente(sqlite3 *db, const char *id_cliente, const char *rua, 
                        const char *num_casa, const char *bairro, const char *cidade) {
    if (!db || !id_cliente || !rua || !num_casa || !bairro || !cidade ||
        strlen(id_cliente) == 0 || strlen(rua) == 0 || strlen(num_casa) == 0 ||
        strlen(bairro) == 0 || strlen(cidade) == 0) {
        fprintf(stderr, "Parâmetros inválidos para addEnderecoCliente\n");
        return NULL;
    }

    char *novoID = gerar_novo_id(db, "END", "tbl_Endereco_Cliente", "ID_Endereco_PK");
    if (!novoID) {
        fprintf(stderr, "Erro ao gerar novo ID para endereço\n");
        return NULL;
    }

    sqlite3_stmt *stmt;
    const char *sql = "INSERT INTO tbl_Endereco_Cliente(ID_Endereco_PK, Rua, Num_Casa, Bairro, Cidade, ID_Cliente_FK) "
                     "VALUES (?, ?, ?, ?, ?, ?)";
    
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, novoID, -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 2, rua, -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 3, num_casa, -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 4, bairro, -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 5, cidade, -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 6, id_cliente, -1, SQLITE_TRANSIENT);
        
        if (sqlite3_step(stmt) != SQLITE_DONE) {
            fprintf(stderr, "Erro ao adicionar endereço: %s\n", sqlite3_errmsg(db));
            free(novoID);
            novoID = NULL;
        } else {
            printf("Endereço cadastrado com ID: %s\n", novoID);
        }
        sqlite3_finalize(stmt);
    } else {
        fprintf(stderr, "Erro ao preparar statement: %s\n", sqlite3_errmsg(db));
        free(novoID);
        novoID = NULL;
    }
    
    return novoID;
}

// Função para buscar cliente por ID e imprimir seus dados
void buscarClientePorID_e_Imprimir(sqlite3 *db, const char *id_cliente) {
    if (!id_cliente) {
        printf("ID do cliente inválido.\n");
        return;
    }

    sqlite3_stmt *stmt;
    const char *sql = "SELECT c.ID_Cliente_PK, c.nome, c.sobrenome, "
                     "t.Num_Telefone, e.Rua, e.Num_Casa, e.Bairro, e.Cidade "
                     "FROM tbl_Cliente c "
                     "LEFT JOIN tbl_Telefone_Cliente t ON c.ID_Cliente_PK = t.ID_Cliente_FK "
                     "LEFT JOIN tbl_Endereco_Cliente e ON c.ID_Cliente_PK = e.ID_Cliente_FK "
                     "WHERE c.ID_Cliente_PK = ?;";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Erro ao preparar busca: %s\n", sqlite3_errmsg(db));
        return;
    }

    sqlite3_bind_text(stmt, 1, id_cliente, -1, SQLITE_STATIC);

    printf("\n=== BUSCA POR ID ===\n");
    
    int encontrado = 0;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        encontrado = 1;
        printf("ID: %s\n", sqlite3_column_text(stmt, 0));
        printf("Nome: %s %s\n", sqlite3_column_text(stmt, 1), sqlite3_column_text(stmt, 2));
        
        const unsigned char *telefone = sqlite3_column_text(stmt, 3);
        printf("Telefone: %s\n", telefone ? (const char*)telefone : "Não cadastrado");
        
        printf("Endereço:\n");
        printf("  Rua: %s, %s\n", 
               sqlite3_column_text(stmt, 4) ? (const char*)sqlite3_column_text(stmt, 4) : "Não informado",
               sqlite3_column_text(stmt, 5) ? (const char*)sqlite3_column_text(stmt, 5) : "S/N");
        printf("  Bairro: %s\n", sqlite3_column_text(stmt, 6) ? (const char*)sqlite3_column_text(stmt, 6) : "Não informado");
        printf("  Cidade: %s\n", sqlite3_column_text(stmt, 7) ? (const char*)sqlite3_column_text(stmt, 7) : "Não informado");
        printf("==================\n");
    }

    if (!encontrado) {
        printf("Nenhum cliente encontrado com o ID: %s\n", id_cliente);
    }

    sqlite3_finalize(stmt);

}

int main() {
    // Conectar ao banco de dados
    if (!conectar_banco("C:/Users/Murilo/Documents/Codezza/database/CODEZZA.db")) {
        fprintf(stderr, "Erro ao conectar ao banco de dados\n");
        return 1;
    }

    sqlite3_close(db);
    return 0;
}