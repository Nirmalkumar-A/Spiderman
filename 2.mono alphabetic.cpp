#include <stdio.h>

void encrypt(char *plaintext, char *key, char *ciphertext) {
    int i;
    for (i = 0; plaintext[i] != '\0'; i++) {
        char ch = plaintext[i];
        if (ch >= 'A' && ch <= 'Z') {
            ciphertext[i] = key[ch - 'A'];
        }
        else if (ch >= 'a' && ch <= 'z') {
            ciphertext[i] = key[ch - 'a'] + 32; 
        }
        else {
            ciphertext[i] = ch;
        }
    }
    ciphertext[i] = '\0';  
}

int main() {
    char plaintext[100], ciphertext[100];
    char key[27] ="QWERTYUIOPASDFGHJKLZXCVBNM"; 
    printf("Enter plaintext: ");
    scanf("%[^\n]%*c", plaintext);
    encrypt(plaintext, key, ciphertext);
    printf("Encrypted ciphertext: %s\n", ciphertext);
	return 0;
}
