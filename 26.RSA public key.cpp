#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

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

int mod_inverse(int e, int phi) {
    for (int d = 2; d < phi; d++) {
        if ((e * d) % phi == 1) {
            return d;
        }
    }
    return -1;
}

int main() {
    int p = 61, q = 53;
    int n = p * q;
    int phi = (p - 1) * (q - 1);
    
    int e = 17;
    while (gcd(e, phi) != 1) {
        e++;
    }
    
    int d = mod_inverse(e, phi);
    
    printf("Public Key: (e: %d, n: %d)\n", e, n);
    printf("Private Key: (d: %d, n: %d)\n", d, n);
    
return 0;
}
