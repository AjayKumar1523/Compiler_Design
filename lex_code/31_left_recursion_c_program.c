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

void eliminate_left_recursion(Rule *rules, int rule_count) {
    for (int i = 0; i < rule_count; i++) {
        char lhs = rules[i].lhs;
        Rule *current_rule = &rules[i];

        // Process indirect left recursion
        for (int j = 0; j < i; j++) {
            char prev_lhs = rules[j].lhs;
            Rule *prev_rule = &rules[j];

            for (int k = 0; k < current_rule->rhs_count; k++) {
                if (current_rule->rhs[k][0] == prev_lhs) {
                    char temp[MAX_RULES][MAX_LENGTH];
                    int temp_count = 0;

                    for (int l = 0; l < prev_rule->rhs_count; l++) {
                        strcpy(temp[temp_count], prev_rule->rhs[l]);
                        strcat(temp[temp_count], current_rule->rhs[k] + 1);
                        temp_count++;
                    }

                    for (int l = k; l < current_rule->rhs_count - 1; l++) {
                        strcpy(current_rule->rhs[l], current_rule->rhs[l + 1]);
                    }

                    current_rule->rhs_count--;

                    for (int l = 0; l < temp_count; l++) {
                        strcpy(current_rule->rhs[current_rule->rhs_count], temp[l]);
                        current_rule->rhs_count++;
                    }
                    k--;
                }
            }
        }

        // Process immediate left recursion
        char alpha[MAX_RULES][MAX_LENGTH];
        char beta[MAX_RULES][MAX_LENGTH];
        int alpha_count = 0;
        int beta_count = 0;

        for (int j = 0; j < current_rule->rhs_count; j++) {
            if (current_rule->rhs[j][0] == lhs) {
                strcpy(alpha[alpha_count], current_rule->rhs[j] + 1);
                alpha_count++;
            } else {
                strcpy(beta[beta_count], current_rule->rhs[j]);
                beta_count++;
            }
        }

        if (alpha_count > 0) {
            char new_lhs = lhs + '1';
            current_rule->rhs_count = 0;

            for (int j = 0; j < beta_count; j++) {
                snprintf(current_rule->rhs[current_rule->rhs_count], MAX_LENGTH, "%s%c", beta[j], new_lhs);
                current_rule->rhs_count++;
            }

            Rule new_rule;
            new_rule.lhs = new_lhs;
            new_rule.rhs_count = 0;

            for (int j = 0; j < alpha_count; j++) {
                snprintf(new_rule.rhs[new_rule.rhs_count], MAX_LENGTH, "%s%c", alpha[j], new_lhs);
                new_rule.rhs_count++;
            }

            snprintf(new_rule.rhs[new_rule.rhs_count], MAX_LENGTH, "%c", '#');  // epsilon represented by #
            new_rule.rhs_count++;

            rules[rule_count] = new_rule;
            rule_count++;
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

        while (token = strtok(NULL, " ->|\n")) {
            strcpy(rules[rule_count].rhs[rules[rule_count].rhs_count], token);
            rules[rule_count].rhs_count++;
        }
        rule_count++;
    }
    fclose(file);

    eliminate_left_recursion(rules, rule_count);

    printf("Grammar after eliminating left recursion:\n");
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
