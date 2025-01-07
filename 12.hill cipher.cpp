#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define N 2

int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1;
}

int determinant(int matrix[N][N]) {
    return (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]);
}

void inverseMatrix(int key[N][N], int inverse[N][N]) {
    int det = determinant(key);
    int det_inv = modInverse(det % 26, 26);
    if (det_inv == -1) {
        printf("Matrix is not invertible under modulo 26.\n");
        exit(1);
    }

    inverse[0][0] = ( key[1][1] * det_inv) % 26;
    inverse[0][1] = (-key[0][1] * det_inv) % 26;
    inverse[1][0] = (-key[1][0] * det_inv) % 26;
    inverse[1][1] = ( key[0][0] * det_inv) % 26;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (inverse[i][j] < 0) {
                inverse[i][j] += 26;
            }
        }
    }
}

void encrypt(char plaintext[], int key[N][N], char ciphertext[]) {
    int textVector[N];
    int resultVector[N];

    for (int i = 0; i < N; i++) {
        textVector[i] = plaintext[i] - 'a';
    }

    for (int i = 0; i < N; i++) {
        resultVector[i] = 0;
        for (int j = 0; j < N; j++) {
            resultVector[i] += key[i][j] * textVector[j];
        }
        resultVector[i] %= 26;
    }

    for (int i = 0; i < N; i++) {
        ciphertext[i] = resultVector[i] + 'a';
    }
    ciphertext[N] = '\0';
}

void decrypt(char ciphertext[], int key[N][N], char plaintext[]) {
    int inverseKey[N][N];
    inverseMatrix(key, inverseKey);

    int textVector[N];
    int resultVector[N];

    for (int i = 0; i < N; i++) {
        textVector[i] = ciphertext[i] - 'a';
    }

    for (int i = 0; i < N; i++) {
        resultVector[i] = 0;
        for (int j = 0; j < N; j++) {
            resultVector[i] += inverseKey[i][j] * textVector[j];
        }
        resultVector[i] %= 26;
    }

    for (int i = 0; i < N; i++) {
        plaintext[i] = resultVector[i] + 'a';
    }
    plaintext[N] = '\0';
}

int main() {
    int key[N][N] = {
        {9, 4},
        {5, 7}
    };

    char plaintext[] = "me";
    char ciphertext[N + 1];
    char decryptedText[N + 1];

    encrypt(plaintext, key, ciphertext);
    printf("Ciphertext: %s\n", ciphertext);

    decrypt(ciphertext, key, decryptedText);
    printf("Decrypted text: %s\n", decryptedText);

    return 0;
}
