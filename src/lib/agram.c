#include "../include/utils.h"

/* ----------------------------- AGRAM ----------------------------- */

/**
 * Structure to hold information about a paragraph.
 */
typedef struct PARAGRAPH {
    char text[BUFFER];       /* Paragraph text */
    char token[MAX_WORD];    /* Token for splitting */
} Paragraph;

/**
 * Structure to hold information about words.
 */
typedef struct WORD {
    char word[MAX_WORD];    /* Word text */
} Word;

/**
 * Structure to hold information about two-grams.
 */
typedef struct TWOGRAM {
    char group[MAX_GROUP];  /* Two-gram group */
    int frequency;          /* Frequency count */
} TwoGram;

/* ----------------------------- AGRAM ----------------------------- */

/**
 * @brief Reads text from the standard input, breaking it into 
 * paragraphs using the specified token.
 * 
 * @param paragraph Pointer to the Paragraph structure.
 * @return EXIT_SUCCESS on success, EXIT_FAILURE on failure.
 */
static u_int8_t parseParagraphs(Paragraph *paragraph) {
    int strT = strlen(paragraph->token);
    int strP = strlen(paragraph->text);

    // Check if the combined length of the
    // paragraph's text and token exceeds the buffer size.
    if (strP + strT >= BUFFER) {
        printf("ERROR: Paragraph buffer is too small.\n");
        return EXIT_FAILURE;
    }

    // Read lines from stdin and append them to the paragraph.
    while (fgets(paragraph->text + strP, BUFFER - strP, stdin)) {
        char *newline = strchr(paragraph->text + strP, '\n');
        if (newline) *newline = ' ';

        strP += strlen(paragraph->text + strP);
        snprintf(paragraph->text + strP, BUFFER - strP, " %s", paragraph->token);
        strP += strlen(paragraph->token) + 1;
    }

    return EXIT_SUCCESS;
}

/**
 * @brief Process words by concatenating adjacent words with spaces.
 * 
 * @param words Pointer to the Word array.
 * @param total Total number of words.
 * @return EXIT_SUCCESS on success, EXIT_FAILURE on failure.
 */
static u_int8_t parseWords(Word *words, int total) {
    const char space[] = " ";
    int spaceLen = strlen(space);

    // Check if any word exceeds the buffer size.
    for (int i = 0; i < total; i++) {
        int wordLen = strlen(words[i].word);

        if (wordLen >= MAX_WORD) {
            printf("ERROR: Word buffer is too small...\n");
            return EXIT_FAILURE;
        }
    }

    // Concatenate words and append spaces.
    for (int i = 0; i < total - 1; i++) {
        int wordLen1 = strlen(words[i].word);
        int wordLen2 = strlen(words[i + 1].word);

        // Check if appending a space and the next word exceeds the buffer size.
        if (wordLen1 + spaceLen + wordLen2 >= MAX_WORD) {
            printf("ERROR: Word buffer is too small...\n");
            return EXIT_FAILURE;
        }

        // Append a space and the next word.
        snprintf(words[i].word + wordLen1, MAX_WORD - wordLen1, " %s", words[i + 1].word);
        // Append a space at the end of the current word.
        strncat(words[i].word, space, MAX_WORD - wordLen1 - 1);
    }

    return EXIT_SUCCESS;
}

/**
 * @brief Calculates the frequency of two-grams from an array of words and stores
 * the results in the provided TwoGram array. Two-grams are pairs of consecutive words.
 * 
 * @param words    Pointer to the Word array containing the words.
 * @param total    Total number of words in the array.
 * @param twoGrams Pointer to the TwoGram array to store the two-gram results.
 * @return EXIT_SUCCESS on success, EXIT_FAILURE on failure.
 */
static u_int8_t findTwoGrams(Word *words, int total, TwoGram *twoGrams) {
    // Calculate frequencies of two-grams.
    for (int i = 0; i < total; i++) {
        int len = strlen(words[i].word);

        if (len >= MAX_GROUP) {
            printf("Error: Buffer too small to store the group...\n");
            return EXIT_FAILURE;
        }

        // Copy the current word as the group for the two-gram.
        strncpy(twoGrams[i].group, words[i].word, MAX_GROUP - 1);
        twoGrams[i].group[MAX_GROUP - 1] = '\0';
        twoGrams[i].frequency = 1;

        // Count the frequency of the two-gram by comparing with subsequent words.
        for (int j = i + 1; j < total; j++) {
            if (!strcmp(words[i].word, words[j].word)) {
                twoGrams[i].frequency++;
            }
        }
    }

    // Eliminate duplicate two-grams in the array.
    for (int i = 0; i < total; i++) {
        for (int j = i + 1; j < total; j++) {
            if (!strcmp(twoGrams[i].group, twoGrams[j].group)) {
                twoGrams[j].frequency = 0;
            }
        }
    }

    return EXIT_SUCCESS;
}

/**
 * @brief Tokenizes a given paragraph's text using the specified token
 * and stores the resulting words in the provided Word array. The total number
 * of words found is stored in the 'total' parameter.
 * 
 * @param paragraph Pointer to the Paragraph structure containing the text to tokenize.
 * @param words Pointer to the Word array to store the tokenized words.
 * @param total Pointer to an integer to store the total number of words found.
 * @return EXIT_SUCCESS on success, EXIT_FAILURE on failure.
 */
static u_int8_t tokenizeWords(Paragraph *paragraph, Word *words, int *total) {
    char *token = strtok(paragraph->text, paragraph->token);

    while (token) {
        // Handle the case where the 'words' array is too small.
        if (*total >= WORDS) {
            printf("ERROR: Words array is too small.\n");
            return EXIT_FAILURE;
        }

        // Copy the tokenized word into the Word array.
        strncpy(words[*total].word, token, MAX_WORD - 1);
        words[*total].word[MAX_WORD - 1] = '\0'; // Ensure null-termination.
        (*total)++;
        token = strtok(NULL, paragraph->token);
    }

    return EXIT_SUCCESS;
}

/**
 *
 * @brief Counts the number of unique two-grams and prints the count
 * along with each unique two-gram and its frequency.
 * 
 * @param twoGrams Pointer to the TwoGram array.
 * @param total Total number of two-grams.
 */
static void outputTwoGrams(TwoGram *twoGrams, int total) {
    int uniqueTwoGrams = 0;

    // Count the number of unique two-grams.
    for (int i = 0; i < total; i++) {
        if (twoGrams[i].frequency > 0) {
            uniqueTwoGrams++;
        }
    }

    // Print the total number of unique two-grams.
    printf("%d\n", uniqueTwoGrams);

    // Print each unique two-gram and its frequency.
    for (int i = 0; i < total; i++) {
        if (twoGrams[i].frequency > 0) {
            printf("%s %d\n", twoGrams[i].group, twoGrams[i].frequency);
        }
    }
}

/**
 * @brief Main function for Agram.
 * Reads a command and invokes the corresponding handler function.
 * 
 * @return EXIT_SUCCESS on success, EXIT_FAILURE on failure.
 */
u_int8_t Agram(void) {
    Paragraph paragraph;
    strcpy(paragraph.token, " ,.;!\n");
    memset(paragraph.text, 0, sizeof(paragraph.text));

    if (parseParagraphs(&paragraph)) {
        return EXIT_FAILURE;
    }

    Word words[WORDS];
    int total = 0; // Total number of words.

    // Tokenize the paragraph and store words in the 'words' array.
    if (tokenizeWords(&paragraph, words, &total)) {
        return EXIT_FAILURE;
    }

    // Process the words to concatenate adjacent words.
    if (parseWords(words, total)) {
        return EXIT_FAILURE;
    }

    // Check if the total number of words is divisible by 3 and 5.
    if (total % 3 || total % 5) total--;

    // Check if the last pair has a single term.
    TwoGram twoGrams[WORDS];

    // Find and count two-grams.
    if (findTwoGrams(words, total, twoGrams)) {
        return EXIT_FAILURE;
    }

    // Output the two-grams.
    outputTwoGrams(twoGrams, total);

    return EXIT_SUCCESS;
}
