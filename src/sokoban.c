#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "sokoban.h"

void print_map(char *map, int width, int height){
    for (int ind_line = 0; ind_line < height; ind_line++){
        for (int ind_row = 0; ind_row < width; ind_row++){
            printf("%c", map[ind_row + ind_line*width]);
        }
        printf("\n");
    }
}

int main(){

    return 0;
}