/**
 * @file cat.c
 * @author Anthony Speicher
 * @date 11/1/2026
 * @brief implementation of the "cat" function
**/

#include <stdio.h>

int print_file(FILE* file, FILE* output);

int min(int a, int b) {
    return a > b ? a : b;
}

int main(int argc, const char *argv[]) {
    for (size_t i = 1; i < argc; i++) {
        FILE* file = fopen(argv[i], "r");

        if (print_file(file, stdout)) {
            return 1;
        } else {
            fclose(file);
        }
    }

    return 0;
}

int print_file(FILE* file, FILE* output) {
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    /// set length, define buffer
    fseek(file, 0, SEEK_END);
    long file_length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char buffer[1024];

    while(fread(buffer, 1, min(sizeof(buffer), ftell(file) - file_length), file)) {
        fprintf(output, "%s", buffer);
    }

    return 0;
}
