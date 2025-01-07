#include <stdio.h>
#include <string.h>

void encryptVigenere(const char *plaintext, const int keyStream[], int keyLength, char *ciphertext) {
    int i;
    for (i = 0; plaintext[i] != '\0'; i++) {
        char letter = plaintext[i];
        if (letter >= 'a' && letter <= 'z') {
            ciphertext[i] = ((letter - 'a' + keyStream[i % keyLength]) % 26) + 'a';
        } else if (letter >= 'A' && letter <= 'Z') {
            ciphertext[i] = ((letter - 'A' + keyStream[i % keyLength]) % 26) + 'A';
        } else {
            ciphertext[i] = letter;
        }
    }
    ciphertext[i] = '\0';
}

void decryptVigenere(const char *ciphertext, const int keyStream[], int keyLength, char *plaintext) {
    int i;
    for (i = 0; ciphertext[i] != '\0'; i++) {
        char letter = ciphertext[i];
        if (letter >= 'a' && letter <= 'z') {
            plaintext[i] = ((letter - 'a' - keyStream[i % keyLength] + 26) % 26) + 'a';
        } else if (letter >= 'A' && letter <= 'Z') {
            plaintext[i] = ((letter - 'A' - keyStream[i % keyLength] + 26) % 26) + 'A';
        } else {
            plaintext[i] = letter;
        }
    }
    plaintext[i] = '\0';
}

int main() {
    char plaintext[] = "send more money";
    int keyStream[] = {9, 0, 1, 7, 23, 15, 21, 14, 11, 11, 2, 8, 9};
    int keyLength = sizeof(keyStream) / sizeof(keyStream[0]);

    char ciphertext[100];
    char decryptedText[100];

    encryptVigenere(plaintext, keyStream, keyLength, ciphertext);
    printf("Ciphertext: %s\n", ciphertext);

    decryptVigenere(ciphertext, keyStream, keyLength, decryptedText);
    printf("Decrypted text: %s\n", decryptedText);

    return 0;
}
