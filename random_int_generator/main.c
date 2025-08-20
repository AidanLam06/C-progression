#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <time.h>
#include <unistd.h>

int main(void) {
    char input_buffer[1024];
    char *endptr;
    const unsigned int seed = time(NULL) ^ getpid();

    printf("Enter the number of digits you want the random number to have: ");
    if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) { // first fgets() to parse the line of input
        printf("Error reading from stdin\n");
        return 1;
    }

    errno = 0;
    const long int num_digits = strtol(input_buffer, &endptr, 10); // then strtol() to convert the string input received from fget which was stored in input_buffer[]

    int err_val = 0;

    if (endptr == input_buffer) {
        printf("Error: Input must be a number.\n");
        err_val = 1;
    } else if (errno == ERANGE) {
        printf("Error: number cannot fit within a long int");
        err_val = 1;
    } else if (num_digits > INT_MAX || num_digits <= 0) {\
        printf("Error: number is either too large for an int or less/equal to 0");
        err_val = 1;
    } else if (num_digits > 10) {
        printf("Error: maximum supported length is 10");
        err_val = 1;
    } else {
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
            upper_bound = 2147483647;
            range = upper_bound - lower_bound + 1;
        }
        srand(seed);
        const int random_num = (rand() % range) + lower_bound;
        printf("The random number is %d", random_num);
        err_val = 0;
    }
    return err_val;
}
