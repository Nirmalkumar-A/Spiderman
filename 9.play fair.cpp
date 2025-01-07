#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

void generateKeyMatrix(char key[], char matrix[SIZE][SIZE]) {
    int used[26] = {0};
    int index = 0;

    for (int i = 0; key[i] != '\0'; i++) {
        char ch = toupper(key[i]);
        if (ch == 'J') ch = 'I';
        if (!used[ch - 'A']) {
            matrix[index / SIZE][index % SIZE] = ch;
            used[ch - 'A'] = 1;
            index++;
        }
    }

    for (char ch = 'A'; ch <= 'Z'; ch++) {
        if (ch == 'J') continue;
        if (!used[ch - 'A']) {
            matrix[index / SIZE][index % SIZE] = ch;
            used[ch - 'A'] = 1;
            index++;
        }
    }
}

void findPosition(char matrix[SIZE][SIZE], char ch, int *row, int *col) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (matrix[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

void playfairDecrypt(char ciphertext[], char key[], char plaintext[]) {
    char matrix[SIZE][SIZE];
    generateKeyMatrix(key, matrix);

    printf("Key Matrix:\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < strlen(ciphertext); i += 2) {
        char a = ciphertext[i];
        char b = ciphertext[i + 1];

        int r1, c1, r2, c2;
        findPosition(matrix, a, &r1, &c1);
        findPosition(matrix, b, &r2, &c2);

        if (r1 == r2) {
            plaintext[i] = matrix[r1][(c1 + SIZE - 1) % SIZE];
            plaintext[i + 1] = matrix[r2][(c2 + SIZE - 1) % SIZE];
        } else if (c1 == c2) {
            plaintext[i] = matrix[(r1 + SIZE - 1) % SIZE][c1];
            plaintext[i + 1] = matrix[(r2 + SIZE - 1) % SIZE][c2];
        } else {
            plaintext[i] = matrix[r1][c2];
            plaintext[i + 1] = matrix[r2][c1];
        }
    }

    plaintext[strlen(ciphertext)] = '\0';
}

int main() {
    char key[50], ciphertext[500], plaintext[500];

    printf("Enter the Playfair cipher key: ");
    scanf("%s", key);

    printf("Enter the ciphertext (without spaces): ");
    scanf("%s", ciphertext);

    playfairDecrypt(ciphertext, key, plaintext);

    printf("Decrypted plaintext: %s\n", plaintext);

    return 0;
}
