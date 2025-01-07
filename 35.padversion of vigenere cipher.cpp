#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void generate_random_key(int *key, int length) {
    for (int i = 0; i < length; i++) {
        key[i] = rand() % 26;
    }
}

void encrypt_text(const char *plaintext, char *ciphertext, int *key, int length) {
    for (int i = 0; i < length; i++) {
        if (plaintext[i] >= 'A' && plaintext[i] <= 'Z') {
            ciphertext[i] = ((plaintext[i] - 'A' + key[i]) % 26) + 'A';
        } else if (plaintext[i] >= 'a' && plaintext[i] <= 'z') {
            ciphertext[i] = ((plaintext[i] - 'a' + key[i]) % 26) + 'a';
        } else {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[length] = '\0';
}

void decrypt_text(const char *ciphertext, char *plaintext, int *key, int length) {
    for (int i = 0; i < length; i++) {
        if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            plaintext[i] = ((ciphertext[i] - 'A' - key[i] + 26) % 26) + 'A';
        } else if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
            plaintext[i] = ((ciphertext[i] - 'a' - key[i] + 26) % 26) + 'a';
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[length] = '\0';
}

int main() {
    char plaintext[256];
    char ciphertext[256];
    char decryptedtext[256];
    int key[256];

    printf("Enter plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0';

    int length = strlen(plaintext);

    srand(time(NULL));
    generate_random_key(key, length);

    encrypt_text(plaintext, ciphertext, key, length);
    decrypt_text(ciphertext, decryptedtext, key, length);

    printf("Plaintext:  %s\n", plaintext);
    printf("Ciphertext: %s\n", ciphertext);
    printf("Decrypted:  %s\n", decryptedtext);

    return 0;
}
