#include <stdio.h>
#include <string.h>
#include <ctype.h> 
void letterFrequencyAttack(const char *ciphertext) {
    int freq[26] = {0};
    int i, j;
    for (i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            freq[tolower(ciphertext[i]) - 'a']++;
        }
    }
    printf("Letter frequencies:\n");
    for (i = 0; i < 26; i++) {
        printf("%c: %d\n", 'a' + i, freq[i]);
    }
    printf("\nTop 10 possible plaintexts based on shifting:\n");
    for (i = 0; i < 26; i++) {
        printf("Shift %d: ", i);
        for (j = 0; ciphertext[j] != '\0'; j++) {
            if (isalpha(ciphertext[j])) {
                char letter = tolower(ciphertext[j]);
                printf("%c", ((letter - 'a' - i + 26) % 26) + 'a');
            } else {
                printf("%c", ciphertext[j]);
            }
        }
        printf("\n");
    }
}
int main() {
    char ciphertext[] = "wkhtxlfneurzqirampsvryhuwkhodcbgrj"; // Example ciphertext

    letterFrequencyAttack(ciphertext);

    return 0;
}
