#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "sokoban.h"
#include "loader.h"


void print_map(game_map used_map){
    char *map = used_map.map;

    int size_width = used_map.map_size.width;
    int size_height = used_map.map_size.height;
    
    int player_width = used_map.player_pos.width;
    int player_height = used_map.player_pos.height;
    
    // printing the width and the height of the map
    printf("Map size: %d %d \n", size_width, size_height);

    // printing the player position
    printf("Player position: %d %d \n", player_width, player_height);
    // int marker = 0;
    // int marker_row = 0;
    // int marker_line = 0;
    // char player[] = {'@'};

    // for (int ind_line = 0; ind_line < size_height; ind_line++){
    //     for (int ind_row = 0; ind_row < size_width; ind_row++){
    //         if (map[ind_row + ind_line*size_width] == player[0]){
    //             marker = 1;
    //             marker_row = ind_row + 1;
    //             marker_line = ind_line + 1;
    //         } 
    //     }
    // }
    
    // if (marker == 1){
    //     printf("Player position: width %d height %d \n", marker_row, marker_line);
    // } else {
    //     printf("No player on the map. \n");
    // }
   
     
    // printing the map
    for (int ind_line = 0; ind_line < size_height; ind_line++){
        for (int ind_row = 0; ind_row < size_width; ind_row++){
            printf("%c", map[ind_row + ind_line*size_width]);
        }
        printf("\n");
    }
}

// int main(){
//     struct game_map example_map;

//     example_map.map = "#####  ##. #####";
//     example_map.height = 4;
//     example_map.width = 4;

//     print_map(example_map);
//     return 0;
// }