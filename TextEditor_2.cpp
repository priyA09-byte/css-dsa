#include <stdio.h>
#include <string.h>

#define MAX_TEXT 1000
#define MAX_HISTORY 100

// Stack to store previous text states
typedef struct {
    char data[MAX_HISTORY][MAX_TEXT];
    int top;
} Stack;

// Initialize the stack
void initStack(Stack *s) {
    s->top = -1;
}

// Check whether the stack is empty
int isEmpty(Stack *s) {
    return s->top == -1;
}

// Push a text snapshot onto the stack
void push(Stack *s, const char *text) {
    if (s->top < MAX_HISTORY - 1) {
        s->top++;
        strcpy(s->data[s->top], text);
    } else {
        printf("History is full!\n");
    }
}

// Pop the most recent snapshot
int pop(Stack *s, char *text) {
    if (isEmpty(s))
        return 0;

    strcpy(text, s->data[s->top]);
    s->top--;
    return 1;
}

// Clear the redo history after a new edit
void clearStack(Stack *s) {
    s->top = -1;
}

int main() {
    char text[MAX_TEXT] = "";
    char temp[MAX_TEXT];
    char input[MAX_TEXT];
    int choice, n;

    Stack undoStack, redoStack;

    initStack(&undoStack);
    initStack(&redoStack);

    while (1) {
        printf("\n===== TEXT EDITOR =====\n");
        printf("1. Insert text\n");
        printf("2. Delete last characters\n");
        printf("3. Undo\n");
        printf("4. Redo\n");
        printf("5. Display text\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input!\n");
            break;
        }
        getchar(); // Remove newline after choice

        switch (choice) {

            case 1: //Insert text
                printf("Enter text to insert: ");
                if (!fgets(input, MAX_TEXT, stdin))
                    break;

                input[strcspn(input, "\n")] = '\0';

                if (strlen(text) + strlen(input) >= MAX_TEXT) {
                    printf("Text capacity exceeded!\n");
                    break;
                }

                push(&undoStack, text);
                strcat(text, input);
                clearStack(&redoStack);

                printf("Text inserted!\n");
                break;

            case 2: //Delete last characters
                printf("How many characters to delete? ");
                if (scanf("%d", &n) != 1) {
                    printf("Invalid number!\n");
                    break;
                }
                getchar();

                if (n < 0 || (size_t)n > strlen(text)) {
                    printf("Invalid deletion length!\n");
                    break;
                }

                if (n > 0) {
                    push(&undoStack, text);
                    text[strlen(text) - n] = '\0';
                    clearStack(&redoStack);
                    printf("Characters deleted!\n");
                }
                break;

            case 3: //Undo
                if (pop(&undoStack, temp)) {
                    push(&redoStack, text);
                    strcpy(text, temp);
                    printf("Undo successful!\n");
                } else {
                    printf("Nothing to undo!\n");
                }
                break;

            case 4: //Redo
                if (pop(&redoStack, temp)) {
                    push(&undoStack, text);
                    strcpy(text, temp);
                    printf("Redo successful!\n");
                } else {
                    printf("Nothing to redo!\n");
                }
                break;

            case 5://Display text
                printf("\nCurrent text: %s\n", text);
                break;

            case 6://Exit
                printf("Exiting editor. Goodbye!\n");
                return 0;

            default://Invalid choice
                printf("Invalid choice!\n");
        }
    }

    return 0;
}
