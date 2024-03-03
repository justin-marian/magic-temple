# Magic Temple

## Overview

The `Magic Temple` project consists of a series of string problems based on:

- **navigating** a character through a mystical temple
- **encrypting** cryptographic operations
- **predicting** word sequences.

### Magical Words

Navigating through a temple represented as a matrix, with a magic code dictating the path. The code consists of magical words of three types, each indicating a direction to move in the matrix:

- `'a'`: Words starting with `'a'`, indicating a single step based on the **largest digit**.
- `'b'`: Words starting with `'b'`, with movement based on properties of **palindromes and prime numbers**.
- `'c'`: Words starting with `'c'`, where the movement is determined by the **sum of certain digits** and **its remainder when divided by 4**.

### Strange Voice

Upon exiting the maze, you encounter encrypted messages from a strange voice. This problem involves deciphering these messages using **Caesar and Vigenère** ciphers and performing **addition on large numbers**.

- `Caesar`**:** shifts each letter and digit in the plaintext by a fixed number determined by a key, wrapping around the alphabet and number set.
- `Vigenère`**:** applies a series of Caesar shifts varying per letter, based on the corresponding letter's position in the keyword.
- `Addition`**:** sums two large numbers represented as strings, digit by digit, from right to left, accounting for any carry-over.

### Help Prediction

The final task is to complete an algorithm that predicts the next words in a sentence based on the **[frequency of 2-grams](https://web.archive.org/web/20220127122755/https://en.wikipedia.org/wiki/N-gram)** in a given text. For the word prediction algorithm, you'll be enhancing a text analysis tool that computes the frequency of `2-grams—pairs of consecutive words`, assists in predicting word sequences.

This task involves reading and processing text to identify these word pairs, calculating how often each pair occurs, and using that information to predict what might come next in a sentence. This feature is case-sensitive and disregards punctuation, focusing solely on the words as they appear in the text.

## Build the Project

1. Navigate to the `build` directory.
2. Run the `make` command to build the executable.

The `Makefile` provided will compile the source files and link them with the necessary libraries.

```bash
    cd ./build
    make
```

## Run The Project

After building the project, you can run the program with the shell script `temple_run.sh` to execute the program. This script sets up the necessary environment and arguments for the program to run the test suite.

```bash
    ./temple_run.sh
    ..........................MAGIC WORDS..............................
    Test 0.......................................................passed
    Test 1.......................................................passed
    Test 2.......................................................passed
    Test 3.......................................................passed
    Test 4.......................................................passed
    
    ............................MAGIC CIPHER...........................
    ...............................CAESAR..............................
    Test 0.......................................................passed
    Test 1.......................................................passed
    Test 2.......................................................passed
    Test 3.......................................................passed
    Test 4.......................................................passed
    ..............................VIGENERE.............................
    Test 0.......................................................passed
    Test 1.......................................................passed
    Test 2.......................................................passed
    Test 3.......................................................passed
    Test 4.......................................................passed
    ..............................ADDITION.............................
    Test 0.......................................................passed
    Test 1.......................................................passed
    Test 2.......................................................passed
    Test 3.......................................................passed
    Test 4.......................................................passed

    .............................TWO GRAMS.............................
    Test 0.......................................................passed
    Test 1.......................................................passed
    Test 2.......................................................passed
    Test 3.......................................................passed
    Test 4.......................................................passed
```
