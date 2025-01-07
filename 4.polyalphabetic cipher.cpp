#include <stdio.h>
#include <string.h>
#include <ctype.h>

void encrypt(char plaintext[], char key[], char ciphertext[]) {
    int textLen = strlen(plaintext);
    int keyLen = strlen(key);
    int i, j = 0;

    for (i = 0; i < textLen; i++) {
        if (isalpha(plaintext[i])) {
            char base = isupper(plaintext[i]) ? 'A' : 'a';
            char keyBase = isupper(key[j % keyLen]) ? 'A' : 'a';
            ciphertext[i] = (plaintext[i] - base + (key[j % keyLen] - keyBase)) % 26 + base;
            j++;
        } else {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[textLen] = '\0';
}

void decrypt(char ciphertext[], char key[], char plaintext[]) {
    int textLen = strlen(ciphertext);
    int keyLen = strlen(key);
    int i, j = 0;

    for (i = 0; i < textLen; i++) {
        if (isalpha(ciphertext[i])) {
            char base = isupper(ciphertext[i]) ? 'A' : 'a';
            char keyBase = isupper(key[j % keyLen]) ? 'A' : 'a';
            plaintext[i] = (ciphertext[i] - base - (key[j % keyLen] - keyBase) + 26) % 26 + base;
            j++;
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[textLen] = '\0';
}

int main() {
    char plaintext[100], key[100], ciphertext[100];

    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0';

    printf("Enter the key: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0';

    encrypt(plaintext, key, ciphertext);
    printf("Encrypted text: %s\n", ciphertext);

    decrypt(ciphertext, key, plaintext);
    printf("Decrypted text: %s\n", plaintext);

    return 0;
}
