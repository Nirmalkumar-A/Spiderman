#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOCK_SIZE 8

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

void sdesDecrypt(unsigned char *ciphertext, unsigned char *key, unsigned char *plaintext) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        plaintext[i] = ciphertext[i] ^ key[i % BLOCK_SIZE];
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
    unsigned char key[BLOCK_SIZE] = {1, 0, 1, 0, 0, 0, 0, 0};
    unsigned char iv[BLOCK_SIZE] = {1, 0, 1, 0, 1, 0, 1, 0};
    unsigned char plaintext[16] = {
        0, 0, 0, 0, 0, 0, 0, 1,
        0, 0, 1, 0, 0, 0, 1, 1
    };

    int numBlocks = 2;
    unsigned char ciphertext[16] = {0};
    unsigned char decryptedText[16] = {0};

    unsigned char previousBlock[BLOCK_SIZE];
    memcpy(previousBlock, iv, BLOCK_SIZE);

    for (int i = 0; i < numBlocks; i++) {
        unsigned char xorResult[BLOCK_SIZE];
        xorBlocks(plaintext + i * BLOCK_SIZE, previousBlock, xorResult, BLOCK_SIZE);
        sdesEncrypt(xorResult, key, ciphertext + i * BLOCK_SIZE);
        memcpy(previousBlock, ciphertext + i * BLOCK_SIZE, BLOCK_SIZE);
    }

    printBinary("Plaintext", plaintext, 16);
    printBinary("Ciphertext", ciphertext, 16);

    memcpy(previousBlock, iv, BLOCK_SIZE);

    for (int i = 0; i < numBlocks; i++) {
        unsigned char decryptedBlock[BLOCK_SIZE];
        sdesDecrypt(ciphertext + i * BLOCK_SIZE, key, decryptedBlock);
        xorBlocks(decryptedBlock, previousBlock, decryptedText + i * BLOCK_SIZE, BLOCK_SIZE);
        memcpy(previousBlock, ciphertext + i * BLOCK_SIZE, BLOCK_SIZE);
    }

    printBinary("Decrypted Text", decryptedText, 16);

return 0;
}
