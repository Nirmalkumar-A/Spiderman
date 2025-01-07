#include <stdio.h>
#include <string.h>
#include <ctype.h>

void generateCipherAlphabet(char keyword[], char cipher[]) {
    int used[26] = {0};
    int index = 0;

    for (int i = 0; keyword[i] != '\0'; i++) {
        char ch = toupper(keyword[i]);
        if (!used[ch - 'A']) {
            cipher[index++] = ch;
            used[ch - 'A'] = 1;
        }
    }

    for (char ch = 'A'; ch <= 'Z'; ch++) {
        if (!used[ch - 'A']) {
            cipher[index++] = ch;
        }
    }
    cipher[index] = '\0';
}

void monoalphabeticEncrypt(char plaintext[], char cipher[], char ciphertext[]) {
    for (int i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            char base = isupper(plaintext[i]) ? 'A' : 'a';
            ciphertext[i] = cipher[plaintext[i] - base];
        } else {
            ciphertext[i] = plaintext[i];
        }
    }
}

void monoalphabeticDecrypt(char ciphertext[], char cipher[], char plaintext[]) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            char base = isupper(ciphertext[i]) ? 'A' : 'a';
            for (int j = 0; j < 26; j++) {
                if (toupper(ciphertext[i]) == cipher[j]) {
                    plaintext[i] = j + base;
                    break;
                }
            }
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
}

int main() {
    char keyword[50], plaintext[100], ciphertext[100], cipher[27];
    printf("Enter the keyword: ");
    scanf("%s", keyword);

    generateCipherAlphabet(keyword, cipher);

    printf("Generated cipher alphabet: %s\n", cipher);

    printf("Enter the plaintext: ");
    scanf(" %[^\n]", plaintext);

    monoalphabeticEncrypt(plaintext, cipher, ciphertext);
    printf("Encrypted ciphertext: %s\n", ciphertext);

    char decrypted[100];
    monoalphabeticDecrypt(ciphertext, cipher, decrypted);
    printf("Decrypted plaintext: %s\n", decrypted);

    return 0;
}
