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
     
    // printing the map
    for (int ind_line = 0; ind_line < size_height; ind_line++){
        for (int ind_row = 0; ind_row < size_width; ind_row++){
            printf("%c", map[ind_row + ind_line*size_width]);
        }
        printf("\n");
    }
}

game_map *move(game_map *p_initial_map, char direction){
    // testing the faisability of the movement
    if (valid_movement(p_initial_map, direction).movement_possible == false) {
        return p_initial_map;
    } 
    
    else {
        // initializing the new dynamically allocated map, copying the parameters unchanged
        game_map *p_new_map = (game_map *) malloc(sizeof(game_map));
        p_new_map->map_size = p_initial_map->map_size;
       
        char available_direction[] = {'NSEW'};

        for (int i = 0; i < 4; i++){
            if (direction == available_direction[i]) {
                //changing the player position
                p_new_map->player_pos.height += tool_direction(i).height;
                p_new_map->player_pos.width += tool_direction(i).width;

                //should change the map into the new one : player position (+ can became @), boxes should be moved
                
            } 
        }

        //free(p_initial_map); à voir si ça marche
    }
}

//plutôt renvoyer une structure qui garde le booléen en mémoire et la map déjà changée
move_tool valid_movement(game_map *p_initial_map, char direction){
    char available_direction[] = {'NSEW'};
    char available_elements[] = {'@+$*. #'};
    move_tool result;
    couple tool_direction_associated;

    for (int i = 0; i < 4; i++){
        if (direction == available_direction[i]){
            tool_direction_associated = tool_direction(i);
        }
    }

    int pointed_element_indice = (p_initial_map->player_pos.height + tool_direction_associated.height) * p_initial_map->map_size.width + (p_initial_map->player_pos.width + tool_direction_associated.width);
    //checking if there is an empty space and moving to it
    if (p_initial_map->map[pointed_element_indice] == available_elements[5]){
        result.movement_possible = true;
        
        return result;
    }

    //checking if there is a wall
    if (){
        return 
    }
}

couple tool_direction(int direction_associated_int){
    couple tool_direction;

    switch (direction_associated_int){
        case 0:
            tool_direction.height = -1;
            tool_direction.width = 0;
            return tool_direction;

        case 1:
            tool_direction.height = 1;
            tool_direction.width = 0;
            return tool_direction;
        
        case 2:
            tool_direction.height = 0;
            tool_direction.width = 1;
            return tool_direction;

        case 3:
            tool_direction.height = 0;
            tool_direction.width = -1;
            return tool_direction;
    }
}

