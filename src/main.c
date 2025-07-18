#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include "db.h"

// Função auxiliar para gerar novos IDs
static char* gerar_novo_id(sqlite3 *db, const char *prefixo, const char *tabela, const char *coluna_id) {
    sqlite3_stmt *stmt;
    char *novoID = malloc(11); // CLI000 + null terminator
    
    char sql[100];
    snprintf(sql, sizeof(sql), "SELECT %s FROM %s ORDER BY %s DESC LIMIT 1;", 
             coluna_id, tabela, coluna_id);
    
    int ultimoNumero = 0;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            const unsigned char *ultimoID = sqlite3_column_text(stmt, 0);
            if (ultimoID && strlen((const char *)ultimoID) >= strlen(prefixo)) {
                ultimoNumero = atoi((const char *)ultimoID + strlen(prefixo));
            }
        }
        sqlite3_finalize(stmt);
    }
    
    sprintf(novoID, "%s%03d", prefixo, ultimoNumero + 1);
    return novoID;
}

char* cadastrarCliente(sqlite3 *db, const char *nome, const char *sobrenome) {
    if (!nome || !sobrenome) return NULL;

    char *novoID = gerar_novo_id(db, "CLI", "tbl_Cliente", "ID_Cliente_PK");
    if (!novoID) return NULL;

    sqlite3_stmt *stmt;
    const char *sql = "INSERT INTO tbl_Cliente(ID_Cliente_PK, Nome, Sobrenome) VALUES (?, ?, ?)";
    
    int resultado = SQLITE_ERROR;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, novoID, -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 2, nome, -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 3, sobrenome, -1, SQLITE_TRANSIENT);
        
        resultado = sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    }

    if (resultado != SQLITE_DONE) {
        fprintf(stderr, "Erro ao cadastrar cliente: %s\n", sqlite3_errmsg(db));
        free(novoID);
        return NULL;
    }

    printf("Cliente cadastrado com ID: %s\n", novoID);
    return novoID;
}

void addTelefoneCliente(sqlite3 *db, const char *id_cliente, const char *telefone) {
    if (!id_cliente || !telefone) return;

    char *novoID = gerar_novo_id(db, "TEL", "tbl_Telefone_Cliente", "ID_Telefone_PK");
    if (!novoID) return;

    sqlite3_stmt *stmt;
    const char *sql = "INSERT INTO tbl_Telefone_Cliente(ID_Telefone_PK, ID_Cliente_FK, Num_Telefone) VALUES (?, ?, ?)";
    
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, novoID, -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 2, id_cliente, -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 3, telefone, -1, SQLITE_TRANSIENT);
        
        if (sqlite3_step(stmt) != SQLITE_DONE) {
            fprintf(stderr, "Erro ao adicionar telefone: %s\n", sqlite3_errmsg(db));
        } else {
            printf("Telefone cadastrado com ID: %s\n", novoID);
        }
        sqlite3_finalize(stmt);
    }
    free(novoID);
}

char* addEnderecoCliente(sqlite3 *db, const char *id_cliente, const char *rua, 
                        const char *num_casa, const char *bairro, const char *cidade) {
    if (!id_cliente || !rua || !num_casa || !bairro || !cidade) return NULL;

    char *novoID = gerar_novo_id(db, "END", "tbl_Endereco_Cliente", "ID_Endereco_PK");
    if (!novoID) return NULL;

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

    int opcao;
    char id_busca[20];

    do {
        printf("\nMENU DE BUSCA\n");
        printf("1. Buscar cliente por ID\n");
        printf("2. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // Limpar buffer do teclado

        switch(opcao) {
            case 1:
                printf("\nDigite o ID do cliente (ex: CLI001): ");
                fgets(id_busca, sizeof(id_busca), stdin);
                id_busca[strcspn(id_busca, "\n")] = '\0'; // Remover quebra de linha
                
                buscarClientePorID_e_Imprimir(db, id_busca);
                break;
                
            case 2:
                printf("Saindo...\n");
                break;
                
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 2);

    sqlite3_close(db);
    return 0;
}