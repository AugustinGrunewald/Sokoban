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

    move_tool *valid_movement_result = valid_movement(p_initial_map, direction);

    if (valid_movement_result->movement_possible == false) {
        free(valid_movement_result);
        return p_initial_map;
    } 
    
    else {
        // initializing the new dynamically allocated map, copying the parameters unchanged
        game_map *p_new_map = (game_map *) malloc(sizeof(game_map));
        p_new_map->map_size = p_initial_map->map_size;
       
        char available_direction[] = "NSEW";

        for (int i = 0; i < 4; i++){
            if (direction == available_direction[i]) {
                //changing the player position
                p_new_map->player_pos.height = p_initial_map->player_pos.height + tool_direction(i).first_level.height;
                p_new_map->player_pos.width = p_initial_map->player_pos.width + tool_direction(i).first_level.width;                
            } 
        }

        p_new_map->map = valid_movement_result->map;

        free(valid_movement_result);
        return p_new_map;
    }
}

move_tool *valid_movement(game_map *p_initial_map, char direction){
    //creating a string that will contain the new version of the map
    char *p_new_map = (char *) malloc(p_initial_map->map_size.height*p_initial_map->map_size.width*sizeof(char)); 
    
    //adding usefull structure for testing
    char available_direction[] = "NSEW";
    char available_elements[] = "@+$*. #";
    move_tool *result = (move_tool *) malloc(sizeof(move_tool));
    double_couple tool_direction_associated;

    //to simplify the process: it will be the same for each direction
    for (int i = 0; i < 4; i++){
        if (direction == available_direction[i]){
            tool_direction_associated = tool_direction(i);
        }
    }

    int pointed_element_indice = (p_initial_map->player_pos.height + tool_direction_associated.first_level.height - 1) * p_initial_map->map_size.width + (p_initial_map->player_pos.width + tool_direction_associated.first_level.width - 1);
    int pointed_element_indice_further = (p_initial_map->player_pos.height + tool_direction_associated.second_level.height - 1) * p_initial_map->map_size.width + (p_initial_map->player_pos.width + tool_direction_associated.second_level.width - 1);
    int player_position_indice = (p_initial_map->player_pos.height - 1)* p_initial_map->map_size.width + p_initial_map->player_pos.width - 1;

    //checking if there is an empty space or a storage destination without a box and moving to it
    if (p_initial_map->map[pointed_element_indice] == available_elements[5] || p_initial_map->map[pointed_element_indice] == available_elements[4]){
        result->movement_possible = true;
        

        //modify the beginning map 
        for (int i = 0; i < p_initial_map->map_size.height * p_initial_map->map_size.width; i++){
            if (i != player_position_indice || i != pointed_element_indice){
                p_new_map[i] = p_initial_map->map[i];
            }
        }

        if (p_initial_map->map[player_position_indice] == available_elements[1]){
            p_new_map[player_position_indice] = available_elements[4];
        } else {
            p_new_map[player_position_indice] = available_elements[5];
        }

        if (p_initial_map->map[pointed_element_indice] == available_elements[4]){
            p_new_map[pointed_element_indice] = available_elements[1];
        } else {
            p_new_map[pointed_element_indice] = available_elements[0];
        }

        result->map = p_new_map; 
        return result;
    }

    //checking if there is a wall
    if (p_initial_map->map[pointed_element_indice] == available_elements[6]){
        result->movement_possible = false;
        result->map = p_initial_map->map; 

        free(p_new_map);
        return result;
    }

    //checking if there is a box on an empty cell or on a storage destination
    if (p_initial_map->map[pointed_element_indice] == available_elements[2] || p_initial_map->map[pointed_element_indice] == available_elements[3]){
        //checking on the second level (ie one cell further)
        
        //checking if there is an empty cell or a storage destination without a box
        if (p_initial_map->map[pointed_element_indice_further] == available_elements[5] || p_initial_map->map[pointed_element_indice_further] == available_elements[4]){
            result->movement_possible = true;

            //modify the map
            for (int i = 0; i < p_initial_map->map_size.height * p_initial_map->map_size.width; i++){
                    if (i != player_position_indice || i != pointed_element_indice || i != pointed_element_indice_further){
                        p_new_map[i] = p_initial_map->map[i];
                    }
                }

            if (p_initial_map->map[player_position_indice] == available_elements[1]){
                p_new_map[player_position_indice] = available_elements[4];
            } else {
                p_new_map[player_position_indice] = available_elements[5];
            }

            if (p_initial_map->map[pointed_element_indice] == available_elements[3]){
                p_new_map[pointed_element_indice] = available_elements[1];
            } else {
                p_new_map[pointed_element_indice] = available_elements[0];
            }

            if (p_initial_map->map[pointed_element_indice_further] == available_elements[4]){
                p_new_map[pointed_element_indice_further] = available_elements[3];
            } else {
                p_new_map[pointed_element_indice_further] = available_elements[2];
            }

            result->map = p_new_map; 
            return result;            
        }

        //checking if there is a wall
        if (p_initial_map->map[pointed_element_indice_further] == available_elements[6]){
            result->movement_possible = false;
            result->map = p_initial_map->map;

            free(p_new_map);
            return result;
        
        }
        //checking if there is a box on an empty cell or on a storage destination
        if (p_initial_map->map[pointed_element_indice_further] == available_elements[2] || p_initial_map->map[pointed_element_indice_further] == available_elements[3]){
            result->movement_possible = false;
            result->map = p_initial_map->map; 

            free(p_new_map);
            return result;
        }

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

    if (first_map.map_size.width != second_map.map_size.width || first_map.map_size.height != second_map.map_size.height){
        result = false;
        return result;
    }
    else {
        int length_map = first_map.map_size.height * first_map.map_size.width;
        char *first_map_string = first_map.map;
        char *second_map_string = second_map.map;
    
        for (int i = 0; i < length_map; i++) {
            if (first_map_string[i] != second_map_string[i]){
                result = false;
                break;
            }
        }
        return result;
    }
}

bool comparaison_two_adresses(const char *adress_1, const char *adress_2){
    bool result = true;
    
    int adress_1_length = strlen(adress_1);
    int adress_2_length = strlen(adress_2);

    if (adress_1_length != adress_2_length){
        result = false;
        return result;
    }
    else{
        for (int i = 0; i < adress_1_length; i++){
            if (adress_1[i] != adress_2[i]){
                result = false;
                return result;
            }
        }
        return result;
    }
}