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
    //testing the faisability of the movement and initializing the new dynamically allocated map
    move_tool *valid_movement_result = valid_movement(p_initial_map, direction);
    game_map *p_new_map = (game_map *) malloc(sizeof(game_map));

    if (valid_movement_result->movement_possible == false) {
        //copying the parameters unchanged
        p_new_map->map_size.height = p_initial_map->map_size.height;
        p_new_map->map_size.width = p_initial_map->map_size.width;
        p_new_map->player_pos.height = p_initial_map->player_pos.height;
        p_new_map->player_pos.width = p_initial_map->player_pos.width;
        
        p_new_map->map = valid_movement_result->map;
    } 
    
    else {
        //copying the parameters unchanged
        p_new_map->map_size.height = p_initial_map->map_size.height;
        p_new_map->map_size.width = p_initial_map->map_size.width;
       
        char available_direction[] = {NORD, SOUTH, EAST, WEST};

        for (int i = 0; i < 4; i++){
            if (direction == available_direction[i]) {
                //changing the player position
                p_new_map->player_pos.height = p_initial_map->player_pos.height + tool_direction(i).first_level.height;
                p_new_map->player_pos.width = p_initial_map->player_pos.width + tool_direction(i).first_level.width;                
            } 
        }
        //changing the map
        p_new_map->map = valid_movement_result->map;
    }

    //freeing the structure that give the validity of a movement
    free(valid_movement_result);

    return p_new_map;
}

move_tool *valid_movement(game_map *p_initial_map, char direction){
    //creating a string that will contain the new version of the map
    char *p_new_map = (char *) malloc(p_initial_map->map_size.height*p_initial_map->map_size.width*sizeof(char)); 
    
    //adding usefull structure for testing
    char available_direction[] = {NORD, SOUTH, EAST, WEST};
    move_tool *result = (move_tool *) malloc(sizeof(move_tool));
    double_couple tool_direction_associated;

    //to simplify the process: it will be the same for each direction thanks to the tool_direction structure
    for (int i = 0; i < 4; i++){
        if (direction == available_direction[i]){
            tool_direction_associated = tool_direction(i);
        }
    }

    //some int used to find which character that will be used in the next part of the function
    int pointed_element_indice = (p_initial_map->player_pos.height + tool_direction_associated.first_level.height - 1) * p_initial_map->map_size.width + (p_initial_map->player_pos.width + tool_direction_associated.first_level.width - 1);
    int pointed_element_indice_further = (p_initial_map->player_pos.height + tool_direction_associated.second_level.height - 1) * p_initial_map->map_size.width + (p_initial_map->player_pos.width + tool_direction_associated.second_level.width - 1);
    int player_position_indice = (p_initial_map->player_pos.height - 1)* p_initial_map->map_size.width + p_initial_map->player_pos.width - 1;


    //first case to check :
    //checking if there is an empty space or a storage destination without a box and moving to it
    if (p_initial_map->map[pointed_element_indice] == EMPTY || p_initial_map->map[pointed_element_indice] == STORAGE_EMPTY){
        result->movement_possible = true;
        

        //modify the map excepting where's the player and the further character that will be changed
        for (int i = 0; i < p_initial_map->map_size.height * p_initial_map->map_size.width; i++){
            if (i != player_position_indice || i != pointed_element_indice){
                p_new_map[i] = p_initial_map->map[i];
            }
        }

        //changing the first character (where the player was)
        if (p_initial_map->map[player_position_indice] == BOY_ON){
            p_new_map[player_position_indice] = STORAGE_EMPTY;
        } else {
            p_new_map[player_position_indice] = EMPTY;
        }

        //changing the second character (the further character that need to be change)
        if (p_initial_map->map[pointed_element_indice] == STORAGE_EMPTY){
            p_new_map[pointed_element_indice] = BOY_ON;
        } else {
            p_new_map[pointed_element_indice] = BOY_EMPTY;
        }

        result->map = p_new_map; 
        return result;
    }


    //second case to check :
    //checking if there is a wall
    if (p_initial_map->map[pointed_element_indice] == WALL){
        result->movement_possible = false;
        
        //copying the map, nothing need to be changed
        for (int i = 0; i < p_initial_map->map_size.height * p_initial_map->map_size.width; i++){
            p_new_map[i] = p_initial_map->map[i];
        }
    
        result->map = p_new_map; 
        return result;
    }


    //last case to check
    //checking if there is a box on an empty cell or on a storage destination
    if (p_initial_map->map[pointed_element_indice] == BOX_EMPTY || p_initial_map->map[pointed_element_indice] == BOX_ON){
        //checking on the second level (ie one cell further)
        
        //first case to check :
        //checking if there is an empty cell or a storage destination without a box
        if (p_initial_map->map[pointed_element_indice_further] == EMPTY || p_initial_map->map[pointed_element_indice_further] == STORAGE_EMPTY){
            result->movement_possible = true;

            //modify the map excepting where's the player and the further character that will be changed
            for (int i = 0; i < p_initial_map->map_size.height * p_initial_map->map_size.width; i++){
                    if (i != player_position_indice || i != pointed_element_indice || i != pointed_element_indice_further){
                        p_new_map[i] = p_initial_map->map[i];
                    }
                }

            //changing the first character (where the player was)
            if (p_initial_map->map[player_position_indice] == BOY_ON){
                p_new_map[player_position_indice] = STORAGE_EMPTY;
            } else {
                p_new_map[player_position_indice] = EMPTY;
            }

            //changing the second character (the further character that need to be change)
            if (p_initial_map->map[pointed_element_indice] == BOX_ON){
                p_new_map[pointed_element_indice] = BOY_ON;
            } else {
                p_new_map[pointed_element_indice] = BOY_EMPTY;
            }

            //changing the lasy character (the further further character that need to be change)
            if (p_initial_map->map[pointed_element_indice_further] == STORAGE_EMPTY){
                p_new_map[pointed_element_indice_further] = BOX_ON;
            } else {
                p_new_map[pointed_element_indice_further] = BOX_EMPTY;
            }

            result->map = p_new_map; 
            return result;            
        }


        //second case to check :
        //checking if there is a wall
        if (p_initial_map->map[pointed_element_indice_further] == WALL){
            result->movement_possible = false;
            for (int i = 0; i < p_initial_map->map_size.height * p_initial_map->map_size.width; i++){
                p_new_map[i] = p_initial_map->map[i];
            }
    
            result->map = p_new_map; 
            return result;
        }

        //last case to check :
        //checking if there is a box on an empty cell or on a storage destination
        if (p_initial_map->map[pointed_element_indice_further] == BOX_EMPTY || p_initial_map->map[pointed_element_indice_further] == BOX_ON){
            result->movement_possible = false;
            for (int i = 0; i < p_initial_map->map_size.height * p_initial_map->map_size.width; i++){
                p_new_map[i] = p_initial_map->map[i];
            }
    
            result->map = p_new_map; 
            return result;
        }


        //adding these "else" that are unused because in every case a if is used
        else {
            return result;
        }
    } 

    else{
        return result;
    }
}

double_couple tool_direction(int direction_associated_int){
    double_couple tool_direction;

    //given a direction, it returns a double couple structure 
    //that will used to move the player and the other element likes boxes
    switch (direction_associated_int){
        case 0:
            tool_direction.first_level.height = -1;
            tool_direction.first_level.width = 0;

            tool_direction.second_level.height = -2;
            tool_direction.second_level.width = 0;
            return tool_direction;

        case 1:
            tool_direction.first_level.height = 1;
            tool_direction.first_level.width = 0;

            tool_direction.second_level.height = 2;
            tool_direction.second_level.width = 0;
            return tool_direction;
        
        case 2:
            tool_direction.first_level.height = 0;
            tool_direction.first_level.width = 1;

            tool_direction.second_level.height = 0;
            tool_direction.second_level.width = 2;
            return tool_direction;

        default:
            tool_direction.first_level.height = 0;
            tool_direction.first_level.width = -1;

            tool_direction.second_level.height = 0;
            tool_direction.second_level.width = -2;
            return tool_direction;
    }
}

bool comparaison_two_maps(game_map first_map, game_map second_map){
    bool result = true;

    //checking if the size of the map are similar
    if (first_map.map_size.width != second_map.map_size.width || first_map.map_size.height != second_map.map_size.height){
        result = false;
        return result;
    }
    else {
        //checking all the characters in case the size of the map are similar
        if (strcmp(first_map.map, second_map.map) == 0){
            return result;
        }else{
            result = true;
            return result;
        }
    }
}

bool comparaison_two_adresses(const char *adress_1, const char *adress_2){
    bool result = true;
    int adress_1_length = strlen(adress_1);
    int adress_2_length = strlen(adress_2);

    //checking if the two strings have the same length
    if (adress_1_length != adress_2_length){
        result = false;
        return result;
    }
    //checking every characters in case the size of the map are similar
    else{
        if (strcmp(adress_1, adress_2) == 0){
            return result;
        }else{
            result = false;
            return result;
        }
    }
}

game_map *replay(game_map *loaded_map, int length_direction_string, char *direction_string){
    game_map *current_step_map = loaded_map;

    //initializing the current step map with the first movement
    current_step_map = move(current_step_map, direction_string[0]);

    for(int direction_step = 1; direction_step < length_direction_string; direction_step++){
        char current_direction = direction_string[direction_step];

        game_map *next_step_map = move(current_step_map, current_direction);

        //freeing the last map created by the move function that is now useless
        free(current_step_map->map);
        free(current_step_map);

        current_step_map = next_step_map;      
    }
    return current_step_map;
}

bool wining_test_play(game_map map){
    bool result = false;
    int length_map = map.map_size.height * map.map_size.width;
    char *map_string = map.map;

    for (int ind = 0; ind < length_map; ind++){
        //searching if there is still a box on an empty space (which means it's not a wining map)
        if (map_string[ind] == '$'){
            return result;
        }
    }
    //if we get out of the loop, it means the map is a wining one
    result = true;

    return result;
}
