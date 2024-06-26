#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CODE_LINES 100
#define MAX_INSTRUCTION_LENGTH 50

typedef struct {
    char instruction[MAX_INSTRUCTION_LENGTH];
} MachineCode;

MachineCode machineCode[MAX_CODE_LINES];
int machineCodeLines = 0;

void generateMachineCode() {
    // Example: Generate machine code from intermediate code
    strcpy(machineCode[machineCodeLines++].instruction, "LOAD R1, A");
    strcpy(machineCode[machineCodeLines++].instruction, "LOAD R2, B");
    strcpy(machineCode[machineCodeLines++].instruction, "ADD R3, R1, R2");
    strcpy(machineCode[machineCodeLines++].instruction, "STORE R3, C");
}

void printMachineCode() {
    printf("Generated Machine Code:\n");
    for (int i = 0; i < machineCodeLines; i++) {
        printf("%s\n", machineCode[i].instruction);
    }
}

int main() {
    // Generate machine code from intermediate representation
    generateMachineCode();

    // Print the generated machine code
    printMachineCode();

    return 0;
}
