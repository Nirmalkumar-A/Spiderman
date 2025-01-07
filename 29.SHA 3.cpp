#include <stdio.h>
#include <stdint.h>

#define STATE_SIZE 5
#define LANE_SIZE 64

typedef uint64_t lane_t;

lane_t state[STATE_SIZE][STATE_SIZE];


void init_state() {
    for (int i = 0; i < STATE_SIZE; i++) {
        for (int j = 0; j < STATE_SIZE; j++) {
            state[i][j] = 0;
        }
    }
}

void set_message_block() {
    for (int i = 0; i < STATE_SIZE; i++) {
        state[0][i] = 1UL << i;  
    }
}


int all_capacity_nonzero() {
    for (int i = 0; i < STATE_SIZE / 2; i++) {  
        if (state[i][0] == 0) { 
            return 0; 
        }
    }
    return 1;  
}

int track_nonzero_bits() {
    int rounds = 0;
    while (!all_capacity_nonzero()) {
        rounds++;
        for (int i = 0; i < STATE_SIZE / 2; i++) {  
            state[i][0] ^= 1UL << (rounds % LANE_SIZE);  
        }
    }
    return rounds;
}

int main() {
    init_state();
    set_message_block();
    int rounds = track_nonzero_bits();
    printf("It takes %d rounds for all capacity lanes to have at least one nonzero bit.\n", rounds);
return 0;
}
