#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LENGTH 1000

void countFrequencies(const char *ciphertext, int freq[]) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isprint(ciphertext[i])) {
            freq[ciphertext[i]]++;
        }
    }
}

void printFrequencies(int freq[]) {
    printf("Character Frequencies:\n");
    for (int i = 0; i < 128; i++) {
        if (freq[i] > 0) {
            printf("'%c': %d\n", i, freq[i]);
        }
    }
}

void decryptMessage(const char *ciphertext, const char *mapping, char *plaintext) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        char ch = ciphertext[i];
        if (isprint(ch) && mapping[ch] != 0) {
            plaintext[i] = mapping[ch];
        } else {
            plaintext[i] = ch; 
        }
    }
    plaintext[strlen(ciphertext)] = '\0';
}

int main() {
    const char ciphertext[MAX_LENGTH] =
        "531305))6:4826)41.)41);806*:48+860))85;;]8*;:*8+83 "
        "(88)5*†;46(;88*96*2;8)(;485);5*42:(;4956*2(5*4)88 "
        ";4069285);)6+8)411;1(19:48081;8:81+1;4885;4)485+528806*81 "
        "(19;48;(88;4(1234:48)42;161;188;12;";

    int freq[128] = {0};
    char mapping[128] = {0}; 
    char plaintext[MAX_LENGTH];

    countFrequencies(ciphertext, freq);
    printFrequencies(freq);

    mapping['5'] = 'e';
    mapping['3'] = 't';
    mapping['1'] = 'h';
    mapping['0'] = 'a';
    mapping['8'] = 'o';
    mapping['6'] = 'n';
    mapping['4'] = 'i';
    mapping['2'] = 's';
    mapping['9'] = 'r';

    decryptMessage(ciphertext, mapping, plaintext);

    printf("\nDecoded message:\n%s\n", plaintext);
	return 0;
}
