#include <stdio.h>
#include <string.h>

#define MATRIX_SIZE 2

void matrixMultiply(int key[MATRIX_SIZE][MATRIX_SIZE], int input[MATRIX_SIZE], int result[MATRIX_SIZE]) {
    for (int i = 0; i < MATRIX_SIZE; i++) {
        result[i] = 0;
        for (int j = 0; j < MATRIX_SIZE; j++) {
            result[i] += key[i][j] * input[j];
        }
        result[i] %= 26;
    }
}

void encrypt(char plaintext[], char ciphertext[], int key[MATRIX_SIZE][MATRIX_SIZE]) {
    int vector[MATRIX_SIZE];
    int encrypted[MATRIX_SIZE];

    for (int i = 0; i < strlen(plaintext); i += MATRIX_SIZE) {
        
        for (int j = 0; j < MATRIX_SIZE; j++) {
            vector[j] = plaintext[i + j] - 'A';
        }
        
        matrixMultiply(key, vector, encrypted);
        
        for (int j = 0; j < MATRIX_SIZE; j++) {
            ciphertext[i + j] = encrypted[j] + 'A';
        }
    }
    ciphertext[strlen(plaintext)] = '\0';
}

int main() {
    int key[MATRIX_SIZE][MATRIX_SIZE] = {{3, 3}, {2, 5}};
    char plaintext[] = "HELP";
    char ciphertext[50];

    printf("Plaintext: %s\n", plaintext);

    encrypt(plaintext, ciphertext, key);
    printf("Ciphertext: %s\n", ciphertext);
return 0;
}
