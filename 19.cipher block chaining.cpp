#include <stdio.h>
#include <string.h>
#define BLOCK_SIZE 8

void print_hex(unsigned char *data, size_t len) {
    for (size_t i = 0; i < len; i++) {
        printf("%02x", data[i]);
    }
    printf("\n");
}

void des3_cbc_encrypt(unsigned char *plaintext, size_t len, unsigned char *key, unsigned char *iv, unsigned char *ciphertext) {
}

int main() {
    unsigned char plaintext[] = "This is a test message!";
    unsigned char key[24] = {0x13, 0x34, 0x57, 0x79, 0x9a, 0xbc, 0xde, 0xf0, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff, 0x01};
    unsigned char iv[BLOCK_SIZE] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};
    unsigned char ciphertext[64];

    size_t len = strlen((char *)plaintext);
    if (len % BLOCK_SIZE != 0) {
        len += BLOCK_SIZE - (len % BLOCK_SIZE);
    }

    des3_cbc_encrypt(plaintext, len, key, iv, ciphertext);

    printf("Ciphertext: ");
    print_hex(ciphertext, len);

return 0;
}
