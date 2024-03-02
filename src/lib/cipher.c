#include "../include/utils.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void         caesar           (char *code, int key);                                                  ////
static void         vigenere         (char *code, char *key);                                                ////
static char*        addnums          (char *str1, char *str2);                                               ////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* ----------------------------------------------UTILS------------------------------------------------------- */

/** 
 * @brief Reverse a string in place.
 * 
 * @param[in, out] code The string to be reversed.
 */
static void reverse(char *code) {
    if (!code) return;

    int len = strlen(code);

    for (int i = 0; i < len / 2; i++) {
        code[i] ^= code[len - i - 1];
        code[len - i - 1] ^= code[i];
        code[i] ^= code[len - i - 1];
    }
}

/**
 * @brief Handler for Caesar cipher command.
 * 
 * @return EXIT_SUCCESS on success, EXIT_FAILURE on failure.
 */
static u_int8_t Handler_Caesar(void) {
    int key;

    // Read the encryption/decryption key.
    if (scanf("%d", &key) != 1) {
        return EXIT_FAILURE;
    }

    char txt[BUFFER];

    // Read the input string.
    if (scanf("%s", txt) != 1) {
        return EXIT_FAILURE;
    }

    // Perform the Caesar cipher encryption/decryption.
    caesar(txt, key);

    printf("%s\n", txt);
    return EXIT_SUCCESS;
}

/**
 * @brief Handler for Vigenere cipher command.
 * 
 * @return EXIT_SUCCESS on success, EXIT_FAILURE on failure.
 */
static u_int8_t Handler_VIgenere(void) {
    char key[INIT_LEN];

    // Read the encryption/decryption key.
    if (scanf("%s", key) != 1) {
        return EXIT_FAILURE;
    }

    char txt[BUFFER];

    // Read the input string.
    if (scanf("%s", txt) != 1) {
        return EXIT_FAILURE;
    }

    // Perform the Vigenere cipher encryption/decryption.
    vigenere(txt, key);

    printf("%s\n", txt);
    return EXIT_SUCCESS;
}

/**
 * @brief Handler for addition command.
 * 
 * @return EXIT_SUCCESS on success, EXIT_FAILURE on failure.
 */
static u_int8_t Handler_AddNums(void) {
    int key;

    // Read the integer key.
    if (scanf("%d", &key) != 1) {
        return EXIT_FAILURE;
    }

    char num1[BUFFER], num2[BUFFER];

    // Read the two number strings.
    if (scanf("%s %s", num1, num2) != 2) {
        return EXIT_FAILURE;
    }

    // Perform the Caesar cipher transformation.
    caesar(num1, key % DIGITS);
    caesar(num2, key % DIGITS);
    // Reverse the transformed number strings.
    reverse(num1);
    reverse(num2);
    // Calculate the sum of the transformed numbers.
    char *sum = addnums(num1, num2);

    if (sum) {
        int trailZeros = 0;
        // Count and skip leading zeros in the result
        for (int i = 0; sum[i] == '0'; i++) {
            trailZeros++;
        }
        // Print the result without leading zeros
        printf("%s\n", sum + trailZeros);
        free(sum); // Sum is only printed!
    }

    return EXIT_SUCCESS;
}

/* ----------------------------------------------UTILS------------------------------------------------------- */

/** 
 * @brief Caesar cipher encryption/decryption.
 * 
 * @param[in, out] code The input string to be encoded/decoded.
 * @param[in] key       The encryption/decryption key.
 */
static void caesar(char *code, int key) {
    // Check if the input is valid.
    if (!code) return;

    for (int i = 0; code[i] != '\0'; i++) {
        char symbol = code[i];

        if (ISALPHA(symbol)) {
            // Alphabet base lower/upper letter.
            char base = ISLOWER(symbol) ? 'a' : 'A';
            // Offset of the new alphabet letters.
            int offset = (symbol - base - (key) + LETTERS) % LETTERS;
            // Replace with the encrypted/decrypted character.
            code[i] = (offset + LETTERS) % LETTERS + base;
        } else if (ISDIGIT(symbol)) {
            // Offset of the new digit.
            int offset = (symbol - '0' - (key) + DIGITS) % DIGITS;
            // Replace with the encrypted/decrypted character.
            code[i] = (offset + DIGITS) % DIGITS + '0';
        }
    }
}

/** 
 * @brief Vigenere cipher encryption/decryption.
 * 
 * @param[in, out] code The input string to be encoded/decoded.
 * @param[in] key       The encryption/decryption key.
 */
static void vigenere(char *code, char *key) {
    // Check if the input is valid.
    if (!code || !key) return;

    int len = strlen(key);

    for (int i = 0; code[i] != '\0'; i++) {
        char symbol = code[i], keyC = key[i % len];

        if (ISALPHA(symbol)) {
            // Alphabet base lower/upper letter.
            char base = ISLOWER(symbol) ? 'a' : 'A';
            // Offset of the new alphabet letters.
            int offset = (symbol - base - (keyC - 'A') + LETTERS) % LETTERS;
            // Replace with the encrypted/decrypted character.
            code[i] = (offset + LETTERS) % LETTERS + base;
        } else if (ISDIGIT(symbol)) {
            // Offset of the new digit.
            int offset = (symbol - '0' - (keyC - 'A') + DIGITS) % DIGITS;
            // Replace with the encrypted/decrypted character.
            code[i] = (offset + DIGITS) % DIGITS + '0';
        }
    }
}

/** @brief Addition of two strings representing numbers.
 * Adds two strings representing numbers and returns the result.
 * 
 * @param[in] str1 The first number string.
 * @param[in] str2 The second number string.
 * @return A dynamically allocated string representing the sum of str1 and str2.
 */
static char* addnums(char *str1, char *str2) {
    // Check if the input is valid.
    if (!str1 || !str2) return NULL;

    int len1 = strlen(str1);
    int len2 = strlen(str2);
    int max = (len1 > len2) ? len1 : len2;
    int min = (len1 > len2) ? len2 : len1;

    // Alocate memory for the result.
    char *add = (char*)malloc(max + 1);
    if (!add) return NULL;

    int carry = 0;
    int i = 0;

    while (i < max) {
        int sum = carry;

        // Add corresponding digits.
        if (i < min) {
            sum += (str1[i] - '0') + (str2[i] - '0');
        } else if (len1 > len2) {
            sum += (str1[i] - '0');
        } else {
            sum += (str2[i] - '0');
        }

        // Digit after the addition.
        add[i] = (sum % 10) + '0';
        // Carry for the next digits addition.
        carry = sum / 10;
        i++;
    }

    // Add the Most Significant Digit, carry exists.
    if (carry > 0)
        add[i++] = carry + '0';

    add[i] = '\0';
    reverse(add);
    return add;
}

/**
 * @brief Main function to solve MAGIC CIPHER.
 * Reads a command and invokes the corresponding handler function.
 * 
 * @return EXIT_SUCCESS on success, EXIT_FAILURE on failure.
 */
u_int8_t Cipher(void) {
    char CMD[BUFFER];

    if (scanf("%s", CMD) != 1) {
        fprintf(stderr, "ERROR: INVALID COMMAND...\n");
        exit(EXIT_FAILURE);
    }

    if (!strcmp(CMD, "caesar")) {
        if (Handler_Caesar()) return EXIT_FAILURE;
    } else if (!strcmp(CMD, "vigenere")) {
        if (Handler_VIgenere()) return EXIT_FAILURE;
    } else if (!strcmp(CMD, "addition")) {
        if (Handler_AddNums()) return EXIT_FAILURE;
    } else {
        fprintf(stderr, "UNKNOWN COMMAND: %s\n", CMD);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}