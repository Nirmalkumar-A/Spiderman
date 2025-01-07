#include <stdio.h>
#include <string.h>

void encrypt(char *text, int shift) {
    int i;
    for (i = 0; text[i] != '\0'; i++) {
        char ch = text[i];

        if (ch >= 'A' && ch <= 'Z') {
            text[i] = ((ch - 'A' + shift) % 26) + 'A';
        }

        else if (ch >= 'a' && ch <= 'z') {
            text[i] = ((ch - 'a' + shift) % 26) + 'a';
        }
    }
}

int main() {
    char text[] = "HELLO World";
    int shift = 3;  

    printf("Original text: %s\n", text);
    
    encrypt(text, shift);
    
    printf("Encrypted text: %s\n", text);
    
}
