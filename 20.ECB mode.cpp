#include <stdio.h>
#include <string.h>

void ECB_mode_demo(const char *plaintext, char *ciphertext, char *decrypted, int error_block) {
    int len = strlen(plaintext);
    for (int i = 0; i < len; i++) {
        ciphertext[i] = plaintext[i] ^ 0xAA;
        if (i == error_block) {
            ciphertext[i] ^= 0xFF;
        }
    }
    for (int i = 0; i < len; i++) {
        decrypted[i] = ciphertext[i] ^ 0xAA;
    }
}

void CBC_mode_demo(const char *plaintext, char *ciphertext, char *decrypted, int error_block) {
    int len = strlen(plaintext);
    char iv = 0x00;
    char prev_cipher = iv;

    for (int i = 0; i < len; i++) {
        ciphertext[i] = (plaintext[i] ^ prev_cipher) ^ 0xAA;
        prev_cipher = ciphertext[i];
        if (i == error_block) {
            ciphertext[i] ^= 0xFF;
        }
    }

    prev_cipher = iv;
    for (int i = 0; i < len; i++) {
        decrypted[i] = (ciphertext[i] ^ 0xAA) ^ prev_cipher;
        prev_cipher = ciphertext[i];
    }
}

int main() {
    const char *plaintext = "HELLO";
    int len = strlen(plaintext);
    char ciphertext[10], decrypted[10];
    
    printf("ECB Mode:\n");
    ECB_mode_demo(plaintext, ciphertext, decrypted, 1);
    printf("Ciphertext: ");
    for (int i = 0; i < len; i++) printf("%02X ", (unsigned char)ciphertext[i]);
    printf("\nDecrypted: %s\n\n", decrypted);

    printf("CBC Mode:\n");
    CBC_mode_demo(plaintext, ciphertext, decrypted, 1);
    printf("Ciphertext: ");
    for (int i = 0; i < len; i++) printf("%02X ", (unsigned char)ciphertext[i]);
    printf("\nDecrypted: %s\n", decrypted);

    return 0;
}
