/**
 * @file test-move.c
 * 
 * @brief Tests to check if the move functions are working
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "loader.h"
#include "sokoban.h"



void testing_move_1(const char *adress) {
    printf("  | testing the move with %s ...  \n", adress);
    game_map *loaded_map = map_loader(adress);
    
    //testing each direction
    char available_direction[] = "NSEW";

    for (int i = 0; i < 4; i++){
        printf("  | | testing the move with %s and the direction %c ... \n", adress, available_direction[i]);
        
        //building the new adress of the file used to check if the move function works
        int adress_length = strlen(adress);
        char adress_bis[adress_length + 2];
        for (int j = 0; j < adress_length - 3; j++){
            adress_bis[j] = adress[j];
        }
        adress_bis[adress_length - 3] = '_';
        adress_bis[adress_length - 2] = available_direction[i];
        for (int k = adress_length - 1; k < adress_length + 2; k++){
            adress_bis[k] = adress[k - 2];
        }

        const char *adress_bis_bis = adress_bis;

        //loading the check file and using the move function 
        game_map *loaded_map_with_movement_data = map_loader(adress_bis_bis);
        game_map *loaded_map_with_movement = move(loaded_map, available_direction[i]);

        //checking if the maps are the same
        bool test_result = comparaison_two_maps(*loaded_map_with_movement_data, *loaded_map_with_movement);
        if(test_result == true){
            printf("  | | | Success \n");
        }else{
            printf("  | | | Failure \n");
        }

        free(loaded_map_with_movement_data->map);
        free(loaded_map_with_movement_data);
        // free(loaded_map_with_movement->map);
        // free(loaded_map_with_movement);       not working
    }

    free(loaded_map->map);
    free(loaded_map);

    printf("\n");
}

void testing_move_2(const char *adress, char direction) {
    int adress_length = strlen(adress);

    for (int i = 0; i < 4; i++){        
        //building the adress of the file used before moving
        char adress_bis_1[adress_length];
        for (int j = 0; j < adress_length - 3; j++){
            adress_bis_1[j] = adress[j];
        }
        char copy_i[2];
        sprintf(copy_i, "%d", i + 1);

        adress_bis_1[adress_length - 3] = '_';
        adress_bis_1[adress_length - 2] = *copy_i;
        for (int k = adress_length - 1; k < adress_length + 2; k++){
            adress_bis_1[k] = adress[k - 2];
        }

        const char *adress_bis_bis_1 = adress_bis_1;

        printf("  | | testing the move with %s and the direction %c ... \n", adress_bis_bis_1, direction);

        //building the new adress of the file used to check if the move function works
        int adress_length_bis = adress_length + 2;
        char adress_bis_2[adress_length_bis];
        for (int j = 0; j < adress_length - 3; j++){
            adress_bis_2[j] = adress[j];
        }
        adress_bis_2[adress_length - 3] = '_';
        adress_bis_2[adress_length - 2] = *copy_i;
        adress_bis_2[adress_length - 1] = '_';
        adress_bis_2[adress_length] = direction;
        for (int k = adress_length - 1; k < adress_length + 2; k++){
            adress_bis_2[k] = adress[k - 2];
        }
        
        
        const char *adress_bis_bis_2 = adress_bis_2;

        printf("%s\n", adress_bis_bis_1);
        printf("%s\n", adress_bis_bis_2);
       

        

        game_map *loaded_map = map_loader(adress_bis_bis_1);

        //loading the check file and using the move function 
        game_map *loaded_map_with_movement_data = map_loader(adress_bis_bis_2);
        game_map *loaded_map_with_movement = move(loaded_map, direction);

        //checking if the maps are the same
        bool test_result = comparaison_two_maps(*loaded_map_with_movement_data, *loaded_map_with_movement);
        if(test_result == true){
            printf("  | | | Success \n");
        }else{
            printf("  | | | Failure \n");
        }

        free(loaded_map_with_movement_data->map);
        free(loaded_map_with_movement_data);
        free(loaded_map->map);
        free(loaded_map);
    }

    printf("\n");
}

void test_comparaison_function(void){
    game_map *first_map = map_loader("./data/soko99.in");
    game_map *second_map = map_loader("./data/soko1.in");

    bool res = comparaison_two_maps(*first_map, *second_map);

    if(res == true){
        printf("same map\n");
    }else{
        printf("different map\n");
    }

    free(first_map->map);
    free(first_map);
    free(second_map->map);
    free(second_map);
}

int main(void){
    printf("* Starting moving tests...\n");
    printf("\n");

    printf("** Starting tests : simple player movements ... \n");
    testing_move_1("./data/soko_move_1.in");
    printf("\n");

    printf("** Starting tests : player movement on dest. ... \n");
    testing_move_1("./data/soko_move_2.in");
    printf("\n");

    printf("** Starting tests : move box to east ... \n");  
    testing_move_2("./data/soko_move_3.in", 'E');
    printf("\n");

    // printf("** Starting tests : move box to west ... \n");  
    // testing_move_2("./data/soko_move_4.in", 'W');
    // printf("\n");

    // printf("** Starting tests : move box to north ... \n");  
    // testing_move_2("./data/soko_move_5.in", 'N');
    // printf("\n");

    // printf("** Starting tests : move box to south ... \n");  
    // testing_move_2("./data/soko_move_6.in", 'S');
    // printf("\n");

    // printf("** Starting tests : does nothing ... \n");  
    // //testing_move_3("./data/soko_move_6_4.in");
    // printf("\n");

    printf("  +-> OK!\n");
    printf("\n");

    // test_comparaison_function();

    return 0;
}