#include "../include/utils.h"

/* ----------------------------------------------UTILS------------------------------------------------------- */

/**
 * @brief Check if a number is prime.
 * 
 * @param num The number to check.
 * @return true if the number is prime, false otherwise.
 */
static bool isPrime(int num) {
    if (num <= 1) return false;
    if (num <= 3) return true;
    if (!(num % 2) || !(num % 3)) return false;
    for (int d = 5; d * d <= num; d += 6) {
        if (!(num % d) || !(num % (d + 2))) {
            return false;
        }
    }
    return true;
}

/**
 * @brief Check if a string is palindromic.
 * 
 * @param code   The string to check.
 * @param length The length of the string.
 * @return true if the string is palindromic, false otherwise.
 */
static bool isPalindrome(char *code, int length) {
    int newLine = (code[length - 1] == '\n');
    // Adjust for the new line character.
    int start = 1, end = length - 1 - newLine;

    while (start < end) {
        if (code[start] != code[end]) {
            return false;
        }
        start++, end--;
    }

    return true;
}

/* ----------------------------------------------UTILS------------------------------------------------------- */

/**
 * @brief Determine the direction of movement based on four integers.
 * 
 * @param x1, x2, x3, x4: Four integers to compare.
 * @return 'R' for right, 'U' for up, 'L' for left, 'D' for down, or 0 if no clear direction.
 */
static char moveA(int x1, int x2, int x3, int x4) {
    if (x1 > x2 && x1 > x3 && x1 > x4) return 'R';
    if (x2 > x1 && x2 > x3 && x2 > x4) return 'U';
    if (x3 > x1 && x3 > x2 && x3 > x4) return 'L';
    if (x4 > x1 && x4 > x2 && x4 > x3) return 'D';
    return '$';  // No clear direction.
}

/**
 * @brief Calculate the direction based on the input string and length.
 * 
 * @param code   The input string.
 * @param length The length of the string.
 * @return 'L', 'U', 'R', or 'D' based on the input string.
 */
static char moveB(char *code, int length) {
    int c1 = code[length - 2] - '0';
    int c2 = code[length - 1] - '0';
    int num = c1 * 10 + c2;

    int prime = isPrime(num);
    int palindrome = isPalindrome(code, length);

    return (palindrome ? (prime ? 'L' : 'R') : (prime ? 'U' : 'D'));
}

/**
 * @brief Calculate the direction based on the input string and length.
 * 
 * @param code The input string.
 * @return 'L', 'U', 'R', or 'D' based on the input string.
 */
static char moveC(char *code) {
    int len = code[1] - '0', mod = code[2] - '0';
    
    int sCircular = 0;
    // Calculate the circular sum.
    for (int i = 0; i < mod; i++) {
        int idx = ((mod * i) % len) + 3;
        sCircular += code[idx] - '0';
    }

    const char moves[] = {'L', 'U', 'R', 'D'};
    return moves[sCircular % DIRS];
}

/**
 * @brief Main function to solve MAGIC WORDS.
 * Reads a command and invokes the corresponding handler function.
 * 
 * @return EXIT_SUCCESS on success, EXIT_FAILURE on failure.
 */
u_int8_t Words(void) {
    int N, M;

    // Read input values N and M.
    if (scanf("%d %d\n", &N, &M) != 2) {
        printf("ERROR: read input size temple...\n");
        return EXIT_FAILURE;
    }

    char string[LENGTH];
    // Read input line command.
    if (!fgets(string, sizeof(string), stdin)) {
        printf("ERROR: read input moves...\n");
        return EXIT_FAILURE;
    }

    char temple[N][M];
    // Initialize the temple matrix with zeros.
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            temple[i][j] = 0;
        }
    }
    
    int k = 0;
    char dirs[INIT_LEN];

    // Tokenize the input command and process each token.
    char *code, *saveptr;
    code = strtok_r(string, " ", &saveptr); // Save state between calls.

    while (code) {
        int length = strlen(code);  //          x1       x2       x3       x4
        if (code[0] == 'a') dirs[k++] = moveA(code[1], code[2], code[3], code[4]);
        if (code[0] == 'b') dirs[k++] = moveB(code, length);
        if (code[0] == 'c') dirs[k++] = moveC(code);
        code = strtok_r(NULL, " ", &saveptr);
    }

    // Initialize an array of pointers to move within the temple matrix.
    char *move[INIT_LEN] = {0};
    move[0] = &(temple[0][0]);

    // Calculate new positions based on directions and assign values to the temple matrix.
    for (int i = 0; i <= k; i++) {
        if (dirs[i] == 'L') move[i + 1] = move[i] - 1;
        if (dirs[i] == 'U') move[i + 1] = move[i] - M;
        if (dirs[i] == 'R') move[i + 1] = move[i] + 1;
        if (dirs[i] == 'D') move[i + 1] = move[i] + M;
    }
    
    // Assign values to the temple matrix.
    for (int i = 0, mv = 1; i <= k; i++) *move[i] = (char)(mv++);

    // Print the resulting matrix temple path.
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            printf("%d ", temple[i][j]);
        }
        printf("\n");
    }

    return EXIT_SUCCESS;
}
