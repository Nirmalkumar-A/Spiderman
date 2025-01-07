#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define BLOCK_SIZE 16

void block_cipher(uint8_t *block, uint8_t *key) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        block[i] ^= key[i];
    }
}

void cbc_mac(uint8_t *message, size_t message_len, uint8_t *key, uint8_t *mac) {
    uint8_t iv[BLOCK_SIZE] = {0};
    uint8_t block[BLOCK_SIZE];
    size_t num_blocks = (message_len + BLOCK_SIZE - 1) / BLOCK_SIZE;

    for (size_t i = 0; i < num_blocks; i++) {
        size_t block_size = (i == num_blocks - 1) ? (message_len % BLOCK_SIZE) : BLOCK_SIZE;
        
        memcpy(block, message + i * BLOCK_SIZE, block_size);
        for (size_t j = block_size; j < BLOCK_SIZE; j++) {
            block[j] = 0;
        }
        
        for (int j = 0; j < BLOCK_SIZE; j++) {
            block[j] ^= iv[j];
        }

        block_cipher(block, key);

        memcpy(iv, block, BLOCK_SIZE);
    }

    memcpy(mac, iv, BLOCK_SIZE);
}

void print_hex(uint8_t *data, size_t len) {
    for (size_t i = 0; i < len; i++) {
        printf("%02x", data[i]);
    }
    printf("\n");
}

int main() {
    uint8_t key[BLOCK_SIZE] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef,
                               0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef};
    uint8_t message[BLOCK_SIZE] = "X";
    uint8_t mac[BLOCK_SIZE];

    cbc_mac(message, strlen((char *)message), key, mac);

    printf("MAC for message X: ");
    print_hex(mac, BLOCK_SIZE);

    uint8_t extended_message[BLOCK_SIZE * 2];
    memcpy(extended_message, message, BLOCK_SIZE);
    memcpy(extended_message + BLOCK_SIZE, message, BLOCK_SIZE);

    uint8_t extended_mac[BLOCK_SIZE];
    cbc_mac(extended_message, BLOCK_SIZE * 2, key, extended_mac);

    printf("MAC for extended message X || (X || T): ");
    print_hex(extended_mac, BLOCK_SIZE);

return 0;
}
