/**
 * @file test-queue-map.c
 *
 * @brief Tests to check if the queue map is working.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "loader.h"
#include "sokoban.h"
#include "queue_map.h"

void building_testing_queue_map(const char *adress_1, const char *adress_2, const char *adress_3, const char *adress_4, const char *adress_5){
    //loading the different maps
    game_map *loaded_map_1 = map_loader(adress_1);
    game_map *loaded_map_2 = map_loader(adress_2);
    game_map *loaded_map_3 = map_loader(adress_3);
    game_map *loaded_map_4 = map_loader(adress_4);
    game_map *loaded_map_5 = map_loader(adress_5);

    //testing the nil function
    queue_map list = nil_queue();
    assert(is_empty_queue(list) == true);
    printf("  |  Creating an empty list ... \n");
    printf("  | |  Success \n");
    printf("\n");
    
    //enqueue the five maps in the right order (cf project pdf page 9)
    printf("  |  Enqueuing the five maps in rising order... \n");
    first_last_pointers *p_first_last_pointers = (first_last_pointers *)malloc(sizeof(first_last_pointers));
    p_first_last_pointers->p_first = NULL;
    p_first_last_pointers->p_last = NULL;
    enqueuing_tool *list_result = (enqueuing_tool*)malloc(sizeof(enqueuing_tool));
    list_result->first_last_pointers = p_first_last_pointers;
    list_result->queue = list;

    list_result = enqueue(list_result, loaded_map_1, 'N', 0, NULL);
    list_result = enqueue(list_result, loaded_map_2, 'W', 1, list_result->queue);
    list_result = enqueue(list_result, loaded_map_3, 'S', 2, list_result->queue->p_next);
    list_result = enqueue(list_result, loaded_map_4, 'E', 3, (list_result->queue->p_next)->p_next);
    list_result = enqueue(list_result, loaded_map_5, 'N', 4, ((list_result->queue->p_next)->p_next)->p_next);

    list = list_result->queue;

    //checking if the element at the right place are
    printf("  |  Checking if the different maps are at the right place ... \n");
    bool test_result_1 = comparaison_two_maps(*loaded_map_1, *get_element_queue(list, 0));
    assert(test_result_1 == true);
    printf("  | |  Map 1 ... Success \n");

    bool test_result_2 = comparaison_two_maps(*loaded_map_2, *get_element_queue(list, 1));
    assert(test_result_2 == true);
    printf("  | |  Map 2 ... Success \n");

    bool test_result_3 = comparaison_two_maps(*loaded_map_3, *get_element_queue(list, 2));
    assert(test_result_3 == true);
    printf("  | |  Map 3 ... Success \n");

    bool test_result_4 = comparaison_two_maps(*loaded_map_4, *get_element_queue(list, 3));
    assert(test_result_4 == true);
    printf("  | |  Map 4 ... Success \n");

    bool test_result_5 = comparaison_two_maps(*loaded_map_5, *get_element_queue(list, 4));
    assert(test_result_5 == true);
    printf("  | |  Map 5 ... Success \n");
    printf("\n");


    // //Checking if the remove and insert function works
    // printf("  |  Checking the remove and insert function on the defined list ... \n");
    
    // linked_list_map list_1 = remove_element(list, 0);
    // bool test_result_remove_1 = comparaison_two_maps(*loaded_map_2, *get_element(list_1, 0));
    // assert(test_result_remove_1 == true);
    // printf("  | |  Remove map 1 ... Success \n");
    // list_1 = insert_element(list_1, 0, loaded_map_1);
    // bool test_result_insert_1 = comparaison_two_maps(*loaded_map_1, *get_element(list_1, 0));
    // assert(test_result_insert_1 == true);
    // free(list_1);
    // printf("  | |  Insert map 1 ... Success \n");

    // linked_list_map list_2 = remove_element(list, 2);
    // bool test_result_remove_2 = comparaison_two_maps(*loaded_map_4, *get_element(list_2, 2));
    // assert(test_result_remove_2 == true);    
    // printf("  | |  Remove map 3 ... Success \n");
    // list_2 = insert_element(list_2, 2, loaded_map_2);
    // bool test_result_insert_2 = comparaison_two_maps(*loaded_map_3, *get_element(list_2, 2));
    // assert(test_result_insert_2 == true);
    // printf("  | |  Insert map 3 ... Success \n");

    // linked_list_map list_3 = remove_element(list, 4);
    // bool test_result_remove_3 = comparaison_two_maps(*loaded_map_4, *get_element(list_3, 3));
    // assert(test_result_remove_3 == true);
    // printf("  | |  Remove map 5 ... Success \n");
    // list_3 = insert_element(list_3, 4, loaded_map_5);
    // bool test_result_insert_3 = comparaison_two_maps(*loaded_map_5, *get_element(list_3, 4));
    // assert(test_result_insert_3 == true);
    // printf("  | |  Insert map 5 ... Success \n");
    // printf("\n");

    // //freeing the linked list
    // deallocate_list(list);

    // freeing the loaded maps
    free(loaded_map_1->map);
    free(loaded_map_1);
    free(loaded_map_2->map);
    free(loaded_map_2);
    free(loaded_map_3->map);
    free(loaded_map_3);
    free(loaded_map_4->map);
    free(loaded_map_4);
    free(loaded_map_5->map);
    free(loaded_map_5);
}

int main(void){
    printf("* Starting queue map tests...\n");

    // testing the linked list on several points
    building_testing_queue_map("./data/soko_dumb_1.in", "./data/soko_dumb_2.in", "./data/soko_dumb_3.in", "./data/soko_dumb.in", "./data/soko_dumber.in");

    printf("  +-> OK!\n");
    printf("\n");

    return 0;
}