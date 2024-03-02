#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#define         DIRS                4
#define         DIGITS              10
#define         BASE10              10
#define         LETTERS             26

#define         LENGTH              150
#define         INIT_LEN            15

#define         WORDS               1000
#define         BUFFER              10000

#define         ISLOWER(c)          ((c >= 'a') && (c <= 'z'))
#define         ISDIGIT(c)          ((c >= '0') && (c <= '9'))
#define         ISALPHA(c)          (((c >= 'A') && (c <= 'Z')) || ((c >= 'a') && (c <= 'z')))

#define         MAX_WORD            32
#define         MAX_GROUP           64

u_int8_t        Words               (void);
u_int8_t        Cipher              (void);
u_int8_t        Agram               (void);
