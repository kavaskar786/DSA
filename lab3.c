#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

// Stack structure
struct Stack {
    int top;
    unsigned capacity;
    char* array;
};

// Function to initialize a stack
struct Stack* createStack(unsigned capacity) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->top = -1;
    stack->capacity = capacity;
    stack->array = (char*)malloc(stack->capacity * sizeof(char));
    return stack;
}

// Function to check if the stack is empty
int isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

// Function to push an element to the stack
void push(struct Stack* stack, char item) {
    stack->array[++stack->top] = item;
}

// Function to pop an element from the stack
char pop(struct Stack* stack) {
    if (!isEmpty(stack))
        return stack->array[stack->top--];
    return '$'; // '$' denotes an empty value
}

// Function to get the top element from the stack without popping it
char peek(struct Stack* stack) {
    return stack->array[stack->top];
}

// Function to check if a character is an operand
int isOperand(char ch) {
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

// Function to get the precedence of an operator
int precedence(char operator) {
    if (operator == '+' || operator == '-')
        return 1;
    else if (operator == '*' || operator == '/')
        return 2;
    else
        return 0; // Assuming '(' has the lowest precedence
}

// Function to convert infix expression to postfix
void infixToPostfix(char* expression) {
    int i, k;

    // Create a stack of capacity equal to the length of the expression
    struct Stack* stack = createStack(strlen(expression));

    for (i = 0, k = -1; expression[i]; ++i) {
        // If the scanned character is an operand, add it to the output
        if (isOperand(expression[i]))
            expression[++k] = expression[i];

        // If the scanned character is an '(', push it to the stack
        else if (expression[i] == '(')
            push(stack, expression[i]);

        // If the scanned character is an ')', pop and output from the stack
        // until an '(' is encountered
        else if (expression[i] == ')') {
            while (!isEmpty(stack) && peek(stack) != '(')
                expression[++k] = pop(stack);
            if (!isEmpty(stack) && peek(stack) != '(')
                return; // Invalid expression
            else
                pop(stack);
        }

        // If an operator is encountered
        else {
            while (!isEmpty(stack) && precedence(expression[i]) <= precedence(peek(stack)))
                expression[++k] = pop(stack);
            push(stack, expression[i]);
        }
    }

    // Pop all the remaining operators from the stack
    while (!isEmpty(stack))
        expression[++k] = pop(stack);

    // Null-terminate the output expression
    expression[++k] = '\0';

    // Print the postfix expression
    printf("Postfix expression: %s\n", expression);
}

// Function to display menu
void displayMenu() {
    printf("\nMenu:\n");
    printf("1. Convert infix to postfix\n");
    printf("2. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    char expression[MAX_SIZE];
    int choice;

    do {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // Input infix expression
                printf("Enter infix expression: ");
                scanf("%s", expression);

                // Convert infix to postfix and print the result
                infixToPostfix(expression);
                break;
            case 2:
                printf("Exiting program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }

    } while (choice != 2);

    return 0;
}