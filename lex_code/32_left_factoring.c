#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RULES 100
#define MAX_SYMBOLS 100
#define MAX_LENGTH 100

typedef struct {
    char lhs;
    char rhs[MAX_RULES][MAX_LENGTH];
    int rhs_count;
} Rule;

void eliminate_left_factoring(Rule *rules, int rule_count) {
    for (int i = 0; i < rule_count; i++) {
        Rule *current_rule = &rules[i];

        // Find the longest common prefix among the RHS productions
        for (int j = 0; j < current_rule->rhs_count; j++) {
            for (int k = j + 1; k < current_rule->rhs_count; k++) {
                int m = 0;
                while (current_rule->rhs[j][m] && current_rule->rhs[j][m] == current_rule->rhs[k][m]) {
                    m++;
                }

                if (m > 0) {
                    // Found a common prefix
                    char common_prefix[MAX_LENGTH];
                    strncpy(common_prefix, current_rule->rhs[j], m);
                    common_prefix[m] = '\0';

                    // Create a new rule for the common prefix
                    char new_lhs = current_rule->lhs + '1';
                    Rule new_rule;
                    new_rule.lhs = new_lhs;
                    new_rule.rhs_count = 0;

                    for (int n = 0; n < current_rule->rhs_count; n++) {
                        if (strncmp(current_rule->rhs[n], common_prefix, m) == 0) {
                            // Add the suffix to the new rule
                            if (current_rule->rhs[n][m] == '\0') {
                                strcpy(new_rule.rhs[new_rule.rhs_count], "ε");  // epsilon represented by ε
                            } else {
                                strcpy(new_rule.rhs[new_rule.rhs_count], current_rule->rhs[n] + m);
                            }
                            new_rule.rhs_count++;

                            // Remove the original production
                            for (int p = n; p < current_rule->rhs_count - 1; p++) {
                                strcpy(current_rule->rhs[p], current_rule->rhs[p + 1]);
                            }
                            current_rule->rhs_count--;
                            n--;
                        }
                    }

                    // Add the new rule to the grammar
                    rules[rule_count] = new_rule;
                    rule_count++;

                    // Add the common prefix followed by the new non-terminal to the current rule
                    snprintf(current_rule->rhs[current_rule->rhs_count], MAX_LENGTH, "%s%c", common_prefix, new_lhs);
                    current_rule->rhs_count++;
                }
            }
        }
    }
}

int main() {
    FILE *file = fopen("compile1.txt", "r");
    if (!file) {
        fprintf(stderr, "Could not open file grammar.txt\n");
        return 1;
    }

    Rule rules[MAX_RULES];
    int rule_count = 0;

    char line[MAX_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        char *token = strtok(line, " ->|\n");
        rules[rule_count].lhs = token[0];
        rules[rule_count].rhs_count = 0;

        while ((token = strtok(NULL, " ->|\n")) != NULL) {
            strcpy(rules[rule_count].rhs[rules[rule_count].rhs_count], token);
            rules[rule_count].rhs_count++;
        }
        rule_count++;
    }
    fclose(file);

    eliminate_left_factoring(rules, rule_count);

    printf("Grammar after eliminating left factoring:\n");
    for (int i = 0; i < rule_count; i++) {
        printf("%c ->", rules[i].lhs);
        for (int j = 0; j < rules[i].rhs_count; j++) {
            printf(" %s", rules[i].rhs[j]);
            if (j < rules[i].rhs_count - 1) {
                printf(" |");
            }
        }
        printf("\n");
    }

    return 0;
}
