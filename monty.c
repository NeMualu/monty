#include <stdio.h>
#include <stdlib.h>

#define STACK_SIZE 1024

typedef struct {
    int stack[STACK_SIZE];
    int top;
} Stack;

Stack stack;

void push(int value) {
    if (stack.top == STACK_SIZE - 1) {
        fprintf(stderr, "Error: Stack overflow\n");
        exit(EXIT_FAILURE);
    }
    stack.stack[++stack.top] = value;
}

void pall() {
    int i;
    for (i = stack.top; i >= 0; i--) {
        printf("%d\n", stack.stack[i]);
    }
}

int main(int argc, char *argv[]) {
    FILE *file;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    file = fopen(argv[1], "r");
    if (!file) {
        perror("Error");
        exit(EXIT_FAILURE);
    }

    while ((read = getline(&line, &len, file)) != -1) {
        char *opcode;
        int value;

        opcode = strtok(line, " \n");
        if (opcode) {
            if (strcmp(opcode, "push") == 0) {
                char *num = strtok(NULL, " \n");
                if (num) {
                    value = atoi(num);
                    push(value);
                } else {
                    fprintf(stderr, "L%d: usage: push integer\n", linenumber);
                    exit(EXIT_FAILURE);
                }
            } else if (strcmp(opcode, "pall") == 0) {
                pall();
            }
        }
    }

    fclose(file);
    free(line);
    return 0;
}

