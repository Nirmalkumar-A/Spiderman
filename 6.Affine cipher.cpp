#include <stdio.h>
#include <string.h>
#include <ctype.h>

int modInverse(int a, int m) {
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1;
}

void decryptAffineCipher(char ciphertext[], int a, int b) {
    int a_inverse = modInverse(a, 26);
    if (a_inverse == -1) {
        printf("Error: No modular inverse for 'a'.\n");
        return;
    }

    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            char base = isupper(ciphertext[i]) ? 'A' : 'a';
            int y = ciphertext[i] - base;
            int x = (a_inverse * (y - b + 26)) % 26;
            ciphertext[i] = x + base;
        }
    }
}

int main() {
    char ciphertext[100];
    int a = 11, b = 17; // Alternative keys

    printf("Enter the ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    ciphertext[strcspn(ciphertext, "\n")] = '\0';

    decryptAffineCipher(ciphertext, a, b);

    printf("Decrypted plaintext: %s\n", ciphertext);

    return 0;
}
