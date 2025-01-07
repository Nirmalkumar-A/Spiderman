#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOCK_SIZE 8
#define MAX_BLOCKS 3

void xorBlocks(unsigned char *block1, unsigned char *block2, unsigned char *result, int size) {
    for (int i = 0; i < size; i++) {
        result[i] = block1[i] ^ block2[i];
    }
}

void sdesEncrypt(unsigned char *plaintext, unsigned char *key, unsigned char *ciphertext) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        ciphertext[i] = plaintext[i] ^ key[i % BLOCK_SIZE];
    }
}

void incrementCounter(unsigned char *counter, int size) {
    for (int i = size - 1; i >= 0; i--) {
        counter[i] = (counter[i] + 1) % 2;
        if (counter[i] != 0) break;
    }
}

void printBinary(const char *label, unsigned char *data, int size) {
    printf("%s: ", label);
    for (int i = 0; i < size; i++) {
        printf("%d", data[i]);
    }
    printf("\n");
}

int main() {
    unsigned char key[BLOCK_SIZE] = {0, 1, 1, 1, 1, 1, 0, 1};
    unsigned char initialCounter[BLOCK_SIZE] = {0, 0, 0, 0, 0, 0, 0, 0};
    unsigned char counter[BLOCK_SIZE];
    memcpy(counter, initialCounter, BLOCK_SIZE);

    unsigned char plaintext[MAX_BLOCKS * BLOCK_SIZE] = {
        0, 0, 0, 0, 0, 0, 0, 1,  // Block 1
        0, 0, 0, 0, 0, 0, 1, 0,  // Block 2
        0, 0, 0, 0, 0, 1, 0, 0   // Block 3
    };
    unsigned char ciphertext[MAX_BLOCKS * BLOCK_SIZE] = {0};
    unsigned char decryptedText[MAX_BLOCKS * BLOCK_SIZE] = {0};

    int numBlocks = 3;
    unsigned char encryptedCounter[BLOCK_SIZE];

    for (int i = 0; i < numBlocks; i++) {
        sdesEncrypt(counter, key, encryptedCounter);
        xorBlocks(plaintext + i * BLOCK_SIZE, encryptedCounter, ciphertext + i * BLOCK_SIZE, BLOCK_SIZE);
        incrementCounter(counter, BLOCK_SIZE);
    }

    printBinary("Plaintext", plaintext, numBlocks * BLOCK_SIZE);
    printBinary("Ciphertext", ciphertext, numBlocks * BLOCK_SIZE);

    memcpy(counter, initialCounter, BLOCK_SIZE);

    for (int i = 0; i < numBlocks; i++) {
        sdesEncrypt(counter, key, encryptedCounter);
        xorBlocks(ciphertext + i * BLOCK_SIZE, encryptedCounter, decryptedText + i * BLOCK_SIZE, BLOCK_SIZE);
        incrementCounter(counter, BLOCK_SIZE);
    }

    printBinary("Decrypted Text", decryptedText, numBlocks * BLOCK_SIZE);

return 0;
}
