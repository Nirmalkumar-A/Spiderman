#include <stdio.h>
#include <math.h>

int main() {
    int totalCharacters = 25;
    double log2TotalKeys = totalCharacters * log2(totalCharacters) - totalCharacters * log2(M_E);
    double log2UniqueKeys = log2TotalKeys - log2(26);

    printf("Total possible keys: ~2^%.2f\n", log2TotalKeys);
    printf("Effectively unique keys: ~2^%.2f\n", log2UniqueKeys);

    return 0;
}