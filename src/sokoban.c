#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "sokoban.h"
#include "loader.h"


void print_map(struct game_map used_map){
    char *map = used_map.map;
    int width = used_map.width;
    int height = used_map.height;
    
    // printing the width and the height of the map
    printf("%d %d \n", width, height);


    // printing the player position
    int marker = 0;
    int marker_row = 0;
    int marker_line = 0;
    char player[] = {'@'};

    for (int ind_line = 0; ind_line < height; ind_line++){
        for (int ind_row = 0; ind_row < width; ind_row++){
            if (map[ind_row + ind_line*width] == player[0]){
                marker = 1;
                marker_row = ind_row;
                marker_line = ind_line;
            } 
        }
    }
    
    if (marker == 1){
        printf("Player position: width %d height %d \n", marker_row, marker_line);
    } else {
        printf("No player on the map. \n");
    }
   
     
    // printing the map
    for (int ind_line = 0; ind_line < height; ind_line++){
        for (int ind_row = 0; ind_row < width; ind_row++){
            printf("%c", map[ind_row + ind_line*width]);
        }
        printf("\n");
    }
}

int main() {
    return 0;
}

// int main(){
//     struct game_map example_map;

//     example_map.map = "#####  ##. #####";
//     example_map.height = 4;
//     example_map.width = 4;

//     print_map(example_map);
//     return 0;
// }