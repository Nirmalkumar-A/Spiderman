#include <stdio.h>
#include <stdint.h>

int IP[64] = { 
    58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,
    64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17,  9, 1,
    59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,
    63, 55, 47, 39, 31, 23, 15, 7 
};

int FP[64] = { 
    40,  8, 48, 16, 56, 24, 64, 32,
    39,  7, 47, 15, 55, 23, 63, 31,
    38,  6, 46, 14, 54, 22, 62, 30,
    37,  5, 45, 13, 53, 21, 61, 29,
    36,  4, 44, 12, 52, 20, 60, 28,
    35,  3, 43, 11, 51, 19, 59, 27,
    34,  2, 42, 10, 50, 18, 58, 26,
    33,  1, 41,  9, 49, 17, 57, 25 
};

void generate_keys(uint64_t key, uint64_t subkeys[16]) {
    for (int i = 0; i < 16; i++) {
        subkeys[i] = key ^ i;
    }
}

uint32_t feistel(uint32_t half_block, uint64_t subkey) {
    return (half_block ^ subkey) & 0xFFFFFFFF;
}

uint64_t permute(uint64_t input, int *table, int size) {
    uint64_t output = 0;
    for (int i = 0; i < size; i++) {
        output |= ((input >> (64 - table[i])) & 1) << (size - i - 1);
    }
    return output;
}

uint64_t des(uint64_t input, uint64_t key, int mode) {
    uint64_t subkeys[16];
    generate_keys(key, subkeys);
    if (mode == 0) {
        for (int i = 0; i < 8; i++) {
            uint64_t temp = subkeys[i];
            subkeys[i] = subkeys[15 - i];
            subkeys[15 - i] = temp;
        }
    }

    input = permute(input, IP, 64);
    uint32_t left = (input >> 32) & 0xFFFFFFFF;
    uint32_t right = input & 0xFFFFFFFF;

    for (int i = 0; i < 16; i++) {
        uint32_t temp = right;
        right = left ^ feistel(right, subkeys[i]);
        left = temp;
    }

    uint64_t combined = ((uint64_t)right << 32) | left;
    combined = permute(combined, FP, 64);

    return combined;
}

int main() {
    uint64_t plaintext = 0x0123456789ABCDEF;
    uint64_t key = 0x133457799BBCDFF1;
    uint64_t ciphertext = des(plaintext, key, 1);
    uint64_t decrypted = des(ciphertext, key, 0);

    printf("Plaintext:  %016lX\n", plaintext);
    printf("Ciphertext: %016lX\n", ciphertext);
    printf("Decrypted:  %016lX\n", decrypted);

    return 0;
}
