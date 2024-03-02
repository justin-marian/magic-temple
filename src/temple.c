#include "./include/utils.h"

int main(void) {
    int taskID;
    
    if (scanf("%d", &taskID) != 1) {
        printf("ERROR: Failed to read task ID...\n");
        return EXIT_FAILURE;
    }

    // Execute the task based on the provided task ID.
    switch (taskID) {
        case 1:
            Words();  // find path through magic temple
            break;
        case 2:
            Cipher(); // caesar, vigenere and addition
            break;
        case 3:
            Agram();  // 2-gram frequnecy
            break;
        default:
            printf("UNDEFINED TASK ID...\n"); // Handle undefined task IDs.
            return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
