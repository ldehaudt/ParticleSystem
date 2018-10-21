#include "Graphics.hpp"
#include <string.h>
#include <stdlib.h>

int main(int ac, char **av){
    int particles = 3000000;
    bool square = true;
    for (int i = 2; i <= ac; i++){
        if (strcmp(av[i - 1], "-s") == 0){
            square = false;
        }
        else if (atoi(av[i - 1]) != 0){
            particles = atoi(av[i - 1]);
            particles = ((particles + 249) / 250) * 250;
            if (particles > 30000000){
                printf("Too many particles, please stay under 30 million ( T ʖ̯ T)\n");
                particles = 3000000;
            }
        }
    }
    Graphics *g = new Graphics(square, particles);
}
