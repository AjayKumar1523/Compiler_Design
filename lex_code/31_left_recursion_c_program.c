#include <stdio.h>
#include <string.h>

#define MAX_RULES 10
#define MAX_RULE_LENGTH 100

void eliminateLeftRecursion(char rules[MAX_RULES][MAX_RULE_LENGTH], int ruleCount);

int main() {
    char rules[MAX_RULES][MAX_RULE_LENGTH];
    int ruleCount;

    printf("Enter the number of rules: ");
    scanf("%d", &ruleCount);

    printf("Enter the grammar rules (A -> Aalpha | beta format):\n");
    for (int i = 0; i < ruleCount; i++) {
        printf("Rule %d: ", i + 1);
        scanf("%s", rules[i]);
    }

    eliminateLeftRecursion(rules, ruleCount);

    return 0;
}

void eliminateLeftRecursion(char rules[MAX_RULES][MAX_RULE_LENGTH], int ruleCount) {
    for (int i = 0; i < ruleCount; i++) {
        char *rule = rules[i];
        char nonTerminal = rule[0];
        char *production = strstr(rule, "->") + 2;

        char alpha[MAX_RULE_LENGTH], beta[MAX_RULE_LENGTH];
        int hasLeftRecursion = 0;

        char *token = strtok(production, "|");
        while (token != NULL) {
            if (token[0] == nonTerminal) {
                hasLeftRecursion = 1;
                strcpy(alpha, token + 1);
            } else {
                strcpy(beta, token);
            }
            token = strtok(NULL, "|");
        }

        if (hasLeftRecursion) {
            printf("%c -> %s%c'\n", nonTerminal, beta, nonTerminal);
            printf("%c' -> %s%c' | epsilon\n", nonTerminal, alpha, nonTerminal);
        } else {
            printf("%s\n", rule);
        }
    }
}
