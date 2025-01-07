#include <stdio.h>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int extendedGCD(int a, int b, int *x, int *y) {
    if (b == 0) {
        *x = 1;
        *y = 0;
        return a;
    }
    int x1, y1;
    int gcd = extendedGCD(b, a % b, &x1, &y1);
    *x = y1;
    *y = x1 - (a / b) * y1;
    return gcd;
}

int modInverse(int e, int phi) {
    int x, y;
    int gcd = extendedGCD(e, phi, &x, &y);
    if (gcd != 1) {
        return -1;
    } else {
        return (x % phi + phi) % phi;
    }
}

int main() {
    int n = 3599;
    int e = 31;
    int M = 59;

    int factor = gcd(M, n);
    if (factor == 1 || factor == n) {
        printf("The plaintext block does not help factorize n.\n");
        return 1;
    }

    int p = factor;
    int q = n / p;

    printf("Factors of n: p = %d, q = %d\n", p, q);

    int phi = (p - 1) * (q - 1);

    int d = modInverse(e, phi);
    if (d == -1) {
        printf("Failed to compute the private key.\n");
        return 1;
    }

    printf("Public Key (e, n): (%d, %d)\n", e, n);
    printf("Private Key (d, n): (%d, %d)\n", d, n);

return 0;
}
