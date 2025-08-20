#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <windows.h>
#include <bcrypt.h>
#pragma comment(lib, "bcrypt.lib")

unsigned int get_random_int();

int main(void) {
    char input_buffer[1024];
    char *endptr;

    printf("Enter the number of digits you want the random number to have: ");
    if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) { // first fgets() to parse the line of input
        printf("Error reading from stdin\n");
        return 1;
    }

    errno = 0;
    const long int num_digits = strtol(input_buffer, &endptr, 10); // then strtol() to convert the string input received from fget which was stored in input_buffer[] ::: Also the 10 there is meant to be the type of number, 10 being decimal, 16 would be hex, 2 binary, and so on

    if (endptr == input_buffer) {
        printf("Error: Input must be a number.\n");
        return 1;
    }if (errno == ERANGE) {
        printf("Error: number cannot fit within a long int");
        return 1;
    }if (num_digits > INT_MAX || num_digits <= 0) {\
        printf("Error: number is either too large for an int or less/equal to 0");
        return 1;
    }if (num_digits > 10) {
        printf("Error: maximum supported length is 10");
        return 1;
    }

    int upper_bound;
    int range;
    int lower_bound = 1;
    for (int i = 1; i < num_digits; i++) {
        lower_bound *= 10;
    }
    if (num_digits != 10) {
        upper_bound = lower_bound * 10 - 1; // lower_bound * 10 if lower_bound = 1000 for example would equal 10000, but I only would want 4 digits, so I add -1
        range = upper_bound - lower_bound + 1;
    } else {
        upper_bound = UINT_MAX;
        range = upper_bound - lower_bound + 1;
    }
    const unsigned int random_gen = get_random_int();
    const unsigned int random_num = (random_gen % range) + lower_bound;
    printf("The random number is %u", random_num);

    return 0;
}

unsigned int get_random_int() { // unsigned so that the program only generates positive numbers
    unsigned int value;
    if (BCryptGenRandom(NULL, (PUCHAR)&value, sizeof(value), BCRYPT_USE_SYSTEM_PREFERRED_RNG) != 0) {
        fprintf(stderr, "BCryptGenRandom() failed\n");
        exit(1);
    }
    return value;
}