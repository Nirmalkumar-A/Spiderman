#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

char playfairMatrix[SIZE][SIZE] = {
    {'M', 'F', 'H', 'I', 'J'},
    {'K', 'U', 'N', 'O', 'P'},
    {'Q', 'Z', 'V', 'W', 'X'},
    {'Y', 'E', 'L', 'A', 'R'},
    {'G', 'D', 'S', 'T', 'B'}
};

void findPosition(char letter, int *row, int *col) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (playfairMatrix[i][j] == letter) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

void processText(char *text) {
    int len = strlen(text);
    int index = 0;

    for (int i = 0; i < len; i++) {
        if (isalpha(text[i])) {
            text[index++] = toupper(text[i]);
        }
    }
    text[index] = '\0';

    len = strlen(text);
    for (int i = 0; i < len - 1; i += 2) {
        if (text[i] == text[i + 1]) {
            memmove(&text[i + 2], &text[i + 1], len - i);
            text[i + 1] = 'X';
            len++;
        }
    }
    if (len % 2 != 0) {
        text[len++] = 'X';
        text[len] = '\0';
    }
}

void encrypt(char *plaintext, char *ciphertext) {
    int row1, col1, row2, col2;
    for (int i = 0; plaintext[i] != '\0'; i += 2) {
        findPosition(plaintext[i], &row1, &col1);
        findPosition(plaintext[i + 1], &row2, &col2);

        if (row1 == row2) {
        
            ciphertext[i] = playfairMatrix[row1][(col1 + 1) % SIZE];
            ciphertext[i + 1] = playfairMatrix[row2][(col2 + 1) % SIZE];
        } else if (col1 == col2) {
        
            ciphertext[i] = playfairMatrix[(row1 + 1) % SIZE][col1];
            ciphertext[i + 1] = playfairMatrix[(row2 + 1) % SIZE][col2];
        } else {
        
            ciphertext[i] = playfairMatrix[row1][col2];
            ciphertext[i + 1] = playfairMatrix[row2][col1];
        }
    }
    ciphertext[strlen(plaintext)] = '\0';
}

int main() {
    char plaintext[100] = "Must see you over Cadogan West. Coming at once.";
    char ciphertext[100];

    printf("Original plaintext: %s\n", plaintext);


    processText(plaintext);
    printf("Processed plaintext: %s\n", plaintext);


    encrypt(plaintext, ciphertext);
    printf("Ciphertext: %s\n", ciphertext);
    return 0;
}
