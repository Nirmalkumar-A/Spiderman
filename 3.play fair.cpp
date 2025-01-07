#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define SIZE 5

void createMatrix(char key[], char matrix[SIZE][SIZE]) {
    int used[26] = {0}, k = 0;
    used['J' - 'A'] = 1; 
    int x = 0, y = 0;

    for (int i = 0; key[i] != '\0'; i++) {
        char ch = toupper(key[i]);
        if (!used[ch - 'A'] && isalpha(ch)) {
            matrix[x][y++] = ch;
            used[ch - 'A'] = 1;
            if (y == SIZE) {
                y = 0;
                x++;
            }
        }
    }

    for (char ch = 'A'; ch <= 'Z'; ch++) {
        if (!used[ch - 'A']) {
            matrix[x][y++] = ch;
            used[ch - 'A'] = 1;
            if (y == SIZE) {
                y = 0;
                x++;
            }
        }
    }
}

void preprocessText(char plaintext[], char result[]) {
    int k = 0, len = strlen(plaintext);

    for (int i = 0; i < len; i++) {
        if (isalpha(plaintext[i])) {
            result[k++] = toupper(plaintext[i]);
        }
    }

    for (int i = 0; i < k; i += 2) {
        if (i + 1 < k && result[i] == result[i + 1]) {
            for (int j = k; j > i + 1; j--) {
                result[j] = result[j - 1];
            }
            result[i + 1] = 'X';
            k++;
        }
    }

    if (k % 2 != 0) {
        result[k++] = 'X'; 
    }

    result[k] = '\0';
}

void findPosition(char matrix[SIZE][SIZE], char ch, int *row, int *col) {
    if (ch == 'J') ch = 'I'; 
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

void encryptPair(char a, char b, char matrix[SIZE][SIZE], char *res1, char *res2) {
    int row1, col1, row2, col2;
    findPosition(matrix, a, &row1, &col1);
    findPosition(matrix, b, &row2, &col2);

    if (row1 == row2) {
        *res1 = matrix[row1][(col1 + 1) % SIZE];
        *res2 = matrix[row2][(col2 + 1) % SIZE];
    } else if (col1 == col2) {
        *res1 = matrix[(row1 + 1) % SIZE][col1];
        *res2 = matrix[(row2 + 1) % SIZE][col2];
    } else {
        *res1 = matrix[row1][col2];
        *res2 = matrix[row2][col1];
    }
}

void encryptText(char plaintext[], char matrix[SIZE][SIZE], char result[]) {
    char preparedText[100];
    preprocessText(plaintext, preparedText);

    int len = strlen(preparedText), k = 0;
    for (int i = 0; i < len; i += 2) {
        encryptPair(preparedText[i], preparedText[i + 1], matrix, &result[k], &result[k + 1]);
        k += 2;
    }
    result[k] = '\0';
}

int main() {
    char key[100], plaintext[100], encrypted[100], matrix[SIZE][SIZE];

    printf("Enter the keyword: ");
    scanf("%s", key);

    printf("Enter the plaintext: ");
    scanf("%s", plaintext);

    createMatrix(key, matrix);

    printf("\nPlayfair Matrix:\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }

    encryptText(plaintext, matrix, encrypted);

    printf("\nEncrypted Text: %s\n", encrypted);
	return 0;
}
