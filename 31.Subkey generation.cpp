#include <stdio.h>
#include <stdint.h>
#include <string.h>
#define BLOCK_SIZE_64 64
#define BLOCK_SIZE_128 128
#define CONST_64 0x1B
#define CONST_128 0x87

void left_shift(uint8_t *input, uint8_t *output, int block_size) {
    int bytes = block_size / 8;
    uint8_t carry = 0;

    for (int i = 0; i < bytes; i++) {
        uint8_t temp = input[i];
        output[i] = (temp << 1) | carry;
        carry = (temp & 0x80) ? 1 : 0;
    }
}

void generate_subkeys(uint8_t *L, uint8_t *K1, uint8_t *K2, int block_size) {
    uint8_t R = (block_size == BLOCK_SIZE_64) ? CONST_64 : CONST_128;
    int bytes = block_size / 8;
    
    left_shift(L, K1, block_size);
    if (L[0] & 0x80) {
        K1[bytes - 1] ^= R;
    }

    left_shift(K1, K2, block_size);
    if (K1[0] & 0x80) {
        K2[bytes - 1] ^= R;
    }
}

int main() {
    int block_size = 128;
    int bytes = block_size / 8;

    uint8_t L[16] = {0};
    uint8_t K1[16] = {0};
    uint8_t K2[16] = {0};

    memset(L, 0xAB, bytes);

    generate_subkeys(L, K1, K2, block_size);

    printf("K1: ");
    for (int i = 0; i < bytes; i++) {
        printf("%02X ", K1[i]);
    }
    printf("\n");

    printf("K2: ");
    for (int i = 0; i < bytes; i++) {
        printf("%02X ", K2[i]);
    }
    printf("\n");

    return 0;
}
