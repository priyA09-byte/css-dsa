#include <stdio.h>
#include <string.h>

#define SIZE 100

char text[SIZE] = "";
char undo[SIZE][SIZE], redo[SIZE][SIZE];
int topUndo = -1, topRedo = -1;

int main() {
    int choice;
    char temp[SIZE], input[SIZE];

    while (1) {
        printf("\nText Editor\n===========\n1.Insert  \n2.Undo  \n3.Redo  \n4.Display  \n5.Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {

            case 1: //Insert
                printf("Enter text: ");
                fgets(input, SIZE, stdin);
                input[strcspn(input, "\n")] = '\0';

                strcpy(undo[++topUndo], text);
                strcat(text, input);
                topRedo = -1;

                break;

            case 2: //Undo
                if (topUndo == -1) {
                    printf("Nothing to undo!\n");
                } else {
                    strcpy(redo[++topRedo], text);
                    strcpy(text, undo[topUndo--]);
                    printf("Undo successful!\n");
                }
                break;

            case 3: //Redo
                if (topRedo == -1) {
                    printf("Nothing to redo!\n");
                } else {
                    strcpy(undo[++topUndo], text);
                    strcpy(text, redo[topRedo--]);
                    printf("Redo successful!\n");
                }
                break;

            case 4: //Display
                printf("Text: %s\n", text);
                break;

            case 5: //Exit
				printf("Exiting...\n");
                return 0;

            default:
                printf("Invalid choice!\n");
        }
    }
}

