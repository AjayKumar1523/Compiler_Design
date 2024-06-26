#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 100
#define NAME_SIZE 50

typedef struct {
    char name[NAME_SIZE];
    char type[NAME_SIZE];
    int scope;
} Symbol;

typedef struct {
    Symbol symbols[TABLE_SIZE];
    int count;
} SymbolTable;

SymbolTable symbolTable;

void initializeSymbolTable() {
    symbolTable.count = 0;
}

int insertSymbol(char *name, char *type, int scope) {
    if (symbolTable.count >= TABLE_SIZE) {
        printf("Symbol table is full\n");
        return -1;
    }
    
    for (int i = 0; i < symbolTable.count; i++) {
        if (strcmp(symbolTable.symbols[i].name, name) == 0) {
            printf("Symbol %s already exists\n", name);
            return -1;
        }
    }

    Symbol newSymbol;
    strncpy(newSymbol.name, name, NAME_SIZE - 1);
    strncpy(newSymbol.type, type, NAME_SIZE - 1);
    newSymbol.scope = scope;

    symbolTable.symbols[symbolTable.count++] = newSymbol;
    return 0;
}

Symbol* lookupSymbol(char *name) {
    for (int i = 0; i < symbolTable.count; i++) {
        if (strcmp(symbolTable.symbols[i].name, name) == 0) {
            return &symbolTable.symbols[i];
        }
    }
    return NULL;
}

void displaySymbolTable() {
    printf("Symbol Table:\n");
    printf("%-20s %-20s %-10s\n", "Name", "Type", "Scope");
    printf("----------------------------------------------------------\n");

    for (int i = 0; i < symbolTable.count; i++) {
        printf("%-20s %-20s %-10d\n", symbolTable.symbols[i].name, symbolTable.symbols[i].type, symbolTable.symbols[i].scope);
    }
}

int main() {
    initializeSymbolTable();

    int choice;
    char name[NAME_SIZE], type[NAME_SIZE];
    int scope;
    Symbol *symbol; // Declare the variable outside the switch statement

    while (1) {
        printf("\nSymbol Table Operations:\n");
        printf("1. Insert Symbol\n");
        printf("2. Lookup Symbol\n");
        printf("3. Display Symbol Table\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter name: ");
                scanf("%s", name);
                printf("Enter type: ");
                scanf("%s", type);
                printf("Enter scope: ");
                scanf("%d", &scope);
                insertSymbol(name, type, scope);
                break;
            case 2:
                printf("Enter name to lookup: ");
                scanf("%s", name);
                symbol = lookupSymbol(name); // Assign the variable inside the case
                if (symbol) {
                    printf("Symbol found: Name=%s, Type=%s, Scope=%d\n", symbol->name, symbol->type, symbol->scope);
                } else {
                    printf("Symbol not found\n");
                }
                break;
            case 3:
                displaySymbolTable();
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}
