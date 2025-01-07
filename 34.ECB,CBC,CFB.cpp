#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define BLOCK_SIZE 8

void xor_blocks(uint8_t *block1, uint8_t *block2, uint8_t *result, int size) {
    for (int i = 0; i < size; i++) {
        result[i] = block1[i] ^ block2[i];
    }
}

void encrypt_block(uint8_t *block, uint8_t *key, uint8_t *output) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        output[i] = block[i] ^ key[i];
    }
}

void decrypt_block(uint8_t *block, uint8_t *key, uint8_t *output) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        output[i] = block[i] ^ key[i];
    }
}

void pad_block(uint8_t *block, int length) {
    block[length] = 0x80;
    for (int i = length + 1; i < BLOCK_SIZE; i++) {
        block[i] = 0x00;
    }
}

void ecb_mode(uint8_t *plaintext, int length, uint8_t *key, uint8_t *ciphertext) {
    uint8_t block[BLOCK_SIZE];
    for (int i = 0; i < length; i += BLOCK_SIZE) {
        memcpy(block, plaintext + i, BLOCK_SIZE);
        encrypt_block(block, key, ciphertext + i);
    }
}

void cbc_mode(uint8_t *plaintext, int length, uint8_t *key, uint8_t *iv, uint8_t *ciphertext) {
    uint8_t block[BLOCK_SIZE];
    uint8_t temp[BLOCK_SIZE];
    memcpy(temp, iv, BLOCK_SIZE);
    for (int i = 0; i < length; i += BLOCK_SIZE) {
        memcpy(block, plaintext + i, BLOCK_SIZE);
        xor_blocks(block, temp, block, BLOCK_SIZE);
        encrypt_block(block, key, ciphertext + i);
        memcpy(temp, ciphertext + i, BLOCK_SIZE);
    }
}

void cfb_mode(uint8_t *plaintext, int length, uint8_t *key, uint8_t *iv, uint8_t *ciphertext) {
    uint8_t temp[BLOCK_SIZE];
    uint8_t output[BLOCK_SIZE];
    memcpy(temp, iv, BLOCK_SIZE);
    for (int i = 0; i < length; i += BLOCK_SIZE) {
        encrypt_block(temp, key, output);
        xor_blocks(plaintext + i, output, ciphertext + i, BLOCK_SIZE);
        memcpy(temp, ciphertext + i, BLOCK_SIZE);
    }
}

int main() {
    uint8_t key[BLOCK_SIZE] = {0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8};
    uint8_t iv[BLOCK_SIZE] = {0x9, 0xA, 0xB, 0xC, 0xD, 0xE, 0xF, 0x10};
    uint8_t plaintext[] = "HELLO123WORLD456";
    int length = strlen((char *)plaintext);
    uint8_t ciphertext[BLOCK_SIZE * 2] = {0};
    uint8_t decrypted[BLOCK_SIZE * 2] = {0};

    if (length % BLOCK_SIZE != 0) {
        pad_block(plaintext + length, length % BLOCK_SIZE);
        length += BLOCK_SIZE - (length % BLOCK_SIZE);
    }

    printf("ECB Mode:\n");
    ecb_mode(plaintext, length, key, ciphertext);
    ecb_mode(ciphertext, length, key, decrypted);
    printf("Ciphertext: %s\n", ciphertext);
    printf("Decrypted: %s\n", decrypted);

    printf("\nCBC Mode:\n");
    cbc_mode(plaintext, length, key, iv, ciphertext);
    cbc_mode(ciphertext, length, key, iv, decrypted);
    printf("Ciphertext: %s\n", ciphertext);
    printf("Decrypted: %s\n", decrypted);

    printf("\nCFB Mode:\n");
    cfb_mode(plaintext, length, key, iv, ciphertext);
    cfb_mode(ciphertext, length, key, iv, decrypted);
    printf("Ciphertext: %s\n", ciphertext);
    printf("Decrypted: %s\n", decrypted);

    return 0;
}
