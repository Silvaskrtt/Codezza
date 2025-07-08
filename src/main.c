// Código principal (ex: `crm_PIZZA.c`)
#include <stdio.h>
#include <sqlite3.h>

int main() {
    sqlite3 *db;
    char *erro = 0;
    int rc;

    rc = sqlite3_open("CRM_PIZZA.db", &db);

}