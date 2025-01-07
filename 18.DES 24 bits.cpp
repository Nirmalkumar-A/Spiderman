#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define KEY_SIZE 56
#define HALF_KEY_SIZE 28
#define SUBKEY_SIZE 48
#define NUM_ROUNDS 16

uint8_t left_shift(uint8_t *half, int shifts) {
    uint8_t temp = *half;
    *half = ((*half << shifts) | (*half >> (HALF_KEY_SIZE - shifts))) & ((1 << HALF_KEY_SIZE) - 1);
    return temp;
}

void key_schedule(uint8_t *key, uint8_t subkeys[NUM_ROUNDS][SUBKEY_SIZE]) {
    uint8_t C = 0, D = 0;
    uint8_t temp_key[KEY_SIZE];
    memcpy(temp_key, key, KEY_SIZE / 8);

    for (int i = 0; i < HALF_KEY_SIZE; i++) {
        C |= ((temp_key[i] >> (i % 8)) & 1) << (i);
    }

    for (int i = HALF_KEY_SIZE; i < KEY_SIZE; i++) {
        D |= ((temp_key[i] >> (i % 8)) & 1) << (i - HALF_KEY_SIZE);
    }

    for (int round = 0; round < NUM_ROUNDS; round++) {
        C = left_shift(&C, 1);
        D = left_shift(&D, 1);
        
        uint8_t subkey[SUBKEY_SIZE] = {0};
        for (int i = 0; i < 24; i++) {
            subkey[i] = (C >> i) & 1;
        }
        for (int i = 24; i < 48; i++) {
            subkey[i] = (D >> (i - 24)) & 1;
        }

        memcpy(subkeys[round], subkey, sizeof(subkey));
    }
}

void print_subkey(uint8_t *subkey) {
    for (int i = 0; i < SUBKEY_SIZE; i++) {
        printf("%d", subkey[i]);
    }
    printf("\n");
}

int main() {
    uint8_t key[KEY_SIZE] = {0x13, 0x34, 0x57, 0x79, 0x9B, 0xAD, 0xBC, 0xEF};
    uint8_t subkeys[NUM_ROUNDS][SUBKEY_SIZE];

    key_schedule(key, subkeys);

    printf("Generated Subkeys:\n");
    for (int i = 0; i < NUM_ROUNDS; i++) {
        printf("Subkey %d: ", i + 1);
        print_subkey(subkeys[i]);
    }

return 0;
}
