#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define P 23
#define Q 11
#define G 4

int mod_exp(int base, int exp, int mod) {
    int result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

void dsa_sign(int message, int x, int *r, int *s) {
    int k = (rand() % (Q - 1)) + 1;
    *r = mod_exp(G, k, P) % Q;
    *s = ((message + x * (*r)) * mod_exp(k, Q - 2, Q)) % Q;
}

int rsa_sign(int message, int d, int n) {
    return mod_exp(message, d, n);
}

int main() {
    srand(time(0));

    int message = 15;

    int x = 5;
    int y = mod_exp(G, x, P);

    int r1, s1, r2, s2;
    dsa_sign(message, x, &r1, &s1);
    dsa_sign(message, x, &r2, &s2);

    int rsa_n = 55;
    int rsa_d = 7;
    int rsa_s1 = rsa_sign(message, rsa_d, rsa_n);
    int rsa_s2 = rsa_sign(message, rsa_d, rsa_n);

    printf("DSA Signature 1: r = %d, s = %d\n", r1, s1);
    printf("DSA Signature 2: r = %d, s = %d\n", r2, s2);
    printf("RSA Signature 1: %d\n", rsa_s1);
    printf("RSA Signature 2: %d\n", rsa_s2);

    return 0;
}
