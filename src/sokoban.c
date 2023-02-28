#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "sokoban.h"

void print_map(char *map, int width, int height){
    printf("%d %d \n", width, height);
    
    int marker = 0; 
    for (int ind_line = 0; ind_line < height; ind_line++){
        for (int ind_row = 0; ind_row < width; ind_row++){
            if (strcmp(map[ind_row + ind_line*width], "@") != 0){
                printf("Player position: width %d height %d", ind_row, ind_line);
                marker = 1;
                break;
            } 
        }
    }
    
    if (marker == 0){
        printf("No player on the map. \n");
    }

   
     
    for (int ind_line = 0; ind_line < height; ind_line++){
        for (int ind_row = 0; ind_row < width; ind_row++){
            printf("%c", map[ind_row + ind_line*width]);
        }
        printf("\n");
    }
}

int main(){
    char *map = "#####  ##. #####";

    print_map(map, 4, 4);
    return 0;
}