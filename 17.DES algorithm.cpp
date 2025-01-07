0#include <stdio.h>
#include <string.h>

#define BLOCK_SIZE 64  
#define KEY_SIZE 56    

void feistel(unsigned char *R, unsigned char *subkey, unsigned char *output) {
    for (int i = 0; i < 32; i++) {
        output[i] = R[i] ^ subkey[i];  
    }
}

void generateSubkeys(unsigned char *key, unsigned char subkeys[16][48]) {
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 48; j++) {
            subkeys[i][j] = key[j % 56];  
        }
    }
}

void desDecrypt(unsigned char *ciphertext, unsigned char *key, unsigned char *plaintext) {
    unsigned char subkeys[16][48];  
    unsigned char L[32], R[32], L_new[32], R_new[32], temp[32];
    
    generateSubkeys(key, subkeys);

    memcpy(L, ciphertext, 32);
    memcpy(R, ciphertext + 32, 32);

    for (int i = 15; i >= 0; i--) {
        feistel(R, subkeys[i], L_new);
        
        memcpy(temp, L, 32);
        memcpy(L, R_new, 32);
        memcpy(R, temp, 32);
    }

    memcpy(plaintext, L, 32);
    memcpy(plaintext + 32, R, 32);
}

int main() {
    unsigned char ciphertext[BLOCK_SIZE] = { 0x6b, 0x79, 0x0f, 0x3e, 0xd1, 0x45, 0x87, 0x9a, 0x35, 0x4c, 0x97, 0xd2, 0x22, 0xe1, 0x56, 0x7b, 0x98, 0x67, 0xa2, 0xe9, 0x45, 0x63, 0xf0, 0xa9, 0xd6, 0x59, 0x1b, 0xd4, 0xe2, 0x9a, 0xb4, 0x21, 0x43, 0x67, 0x56, 0x75, 0xb1, 0xc9, 0x9d, 0xe8, 0x65, 0x4b, 0x87, 0x7e, 0x59, 0x5a, 0x1a, 0xb4, 0x45, 0xa1, 0x91, 0xb6, 0xda, 0x3d, 0x11, 0xfa, 0x55, 0x64, 0x87 }; 
    unsigned char key[KEY_SIZE] = { 0x13, 0x57, 0x99, 0x48, 0x62, 0x23, 0x15 }; 
    unsigned char plaintext[BLOCK_SIZE];
    
    desDecrypt(ciphertext, key, plaintext);
    
    printf("Decrypted Text: ");
    for (int i = 0; i < BLOCK_SIZE; i++) {
        printf("%c", plaintext[i]);
    }
    printf("\n");
    
return 0;
}
