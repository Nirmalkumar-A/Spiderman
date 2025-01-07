#include <stdio.h>
#include <string.h>
#include <ctype.h>

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

int modInverse(int a) {
    for (int i = 1; i < 26; i++) {
        if ((a * i) % 26 == 1) return i;
    }
    return -1;
}

void encrypt(char text[], int a, int b, char result[]) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            char base = islower(text[i]) ? 'a' : 'A';
            result[i] = ((a * (text[i] - base) + b) % 26) + base;
        } else {
            result[i] = text[i];
        }
    }
    result[strlen(text)] = '\0';
}

void decrypt(char text[], int a, int b, char result[]) {
    int a_inv = modInverse(a);
    if (a_inv == -1) {
        printf("Invalid 'a': no modular inverse exists.\n");
        return;
    }
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            char base = islower(text[i]) ? 'a' : 'A';
            result[i] = ((a_inv * (text[i] - base - b + 26)) % 26) + base;
        } else {
            result[i] = text[i];
        }
    }
    result[strlen(text)] = '\0';
}

int main() {
    char text[100], encrypted[100], decrypted[100];
    int a, b;

    printf("Enter text: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0'; 

    printf("Enter values of 'a' and 'b': ");
    if (scanf("%d %d", &a, &b) != 2) {
        printf("Invalid input for 'a' and 'b'.\n");
        return 1;
    }

    if (gcd(a, 26) != 1) {
        printf("'a' must be coprime with 26. Try again.\n");
        return 1;
    }

    encrypt(text, a, b, encrypted);
    printf("Encrypted: %s\n", encrypted);

    decrypt(encrypted, a, b, decrypted);
    printf("Decrypted: %s\n", decrypted);
	return 0;
}