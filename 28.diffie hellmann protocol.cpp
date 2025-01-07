#include <stdio.h>
#include <math.h>

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

int main() {
    int a = 5; 
    int q = 23;
    int x_A = 6; 
    int x_B = 15; 

    int A = mod_exp(a, x_A, q); 
    int B = mod_exp(a, x_B, q); 

    printf("Alice sends A: %d\n", A);
    printf("Bob sends B: %d\n", B);

    int K_Alice = mod_exp(B, x_A, q); 
    int K_Bob = mod_exp(A, x_B, q); 

    printf("Alice's computed key: %d\n", K_Alice);
    printf("Bob's computed key: %d\n", K_Bob);

return 0;
}
