#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

void decrypt(char ciphertext[], char plaintext[], int key) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            char offset = isupper(ciphertext[i]) ? 'A' : 'a';
            plaintext[i] = ((ciphertext[i] - offset - key + ALPHABET_SIZE) % ALPHABET_SIZE) + offset;
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[strlen(ciphertext)] = '\0';
}

int main() {
    char ciphertext[500], plaintext[500];

    printf("Enter the ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    ciphertext[strcspn(ciphertext, "\n")] = '\0'; 

    printf("\nPossible plaintexts:\n");
    for (int key = 0; key < ALPHABET_SIZE; key++) {
        decrypt(ciphertext, plaintext, key);
        printf("Key %2d: %s\n", key, plaintext);
    }

return 0;
}
