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
    
    //enqueue the five maps in the rising order (bottom - 1,2,...,5 - head)
    
    printf("  |  Enqueuing the five maps in rising order... \n");
    //initializing the queue and all the linked stuff to it
    first_last_pointers *p_first_last_pointers = (first_last_pointers *)malloc(sizeof(first_last_pointers));
    p_first_last_pointers->p_first = NULL;
    p_first_last_pointers->p_last = NULL;

    //enqueueing the first map
    list = enqueue_bis(list, p_first_last_pointers, loaded_map_1, 'N', 0, NULL);
    //enqeueing the second map (saying the mother cell is cell 1)
    list = enqueue_bis(list, p_first_last_pointers, loaded_map_2, 'S', 1, p_first_last_pointers->p_last);
    //enqeueing the third map (saying the mother cell is cell 2)
    list = enqueue_bis(list, p_first_last_pointers, loaded_map_3, 'E', 2, p_first_last_pointers->p_last);
    //enqeueing the four map (saying the mother cell is cell 2)
    list = enqueue_bis(list, p_first_last_pointers, loaded_map_4, 'S', 3, p_first_last_pointers->p_first->p_next);
    //enqeueing the five map (saying the mother cell is cell 3)
    list = enqueue_bis(list, p_first_last_pointers, loaded_map_5, 'W', 4, p_first_last_pointers->p_first->p_next->p_next);


    //checking if the element are at the right place 
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


    //checking if the dequeue function works well
    printf("  |  Checking if the dequeuing function works well ... \n");
    dequeuing_tool dequeuing_result;

    //deuqueuing map 1
    printf("  | |  Dequeuing map 1 ... \n");
    dequeuing_result = dequeue_bis(list, p_first_last_pointers);
    list = dequeuing_result.queue;

    bool test_result_1_bis = comparaison_two_maps(*loaded_map_1, *(dequeuing_result.p_map->p_map));
    assert(test_result_1_bis == true);
    printf("  | |  Map 1 ... Success \n");

    free(dequeuing_result.p_map);

    //deuqueuing map 2
    printf("  | |  Dequeuing map 2 ... \n");
    dequeuing_result = dequeue_bis(list, p_first_last_pointers);
    list = dequeuing_result.queue;

    bool test_result_2_bis = comparaison_two_maps(*loaded_map_2, *(dequeuing_result.p_map->p_map));
    assert(test_result_2_bis == true);
    printf("  | |  Map 2 ... Success \n");

    free(dequeuing_result.p_map);

    //deuqueuing map 3
    printf("  | |  Dequeuing map 3 ... \n");
    dequeuing_result = dequeue_bis(list, p_first_last_pointers);
    list = dequeuing_result.queue;

    bool test_result_3_bis = comparaison_two_maps(*loaded_map_3, *(dequeuing_result.p_map->p_map));
    assert(test_result_3_bis == true);
    printf("  | |  Map 3 ... Success \n");

    free(dequeuing_result.p_map);

    //deuqueuing map 4
    printf("  | |  Dequeuing map 4 ... \n");
    dequeuing_result = dequeue_bis(list, p_first_last_pointers);
    list = dequeuing_result.queue;

    bool test_result_4_bis = comparaison_two_maps(*loaded_map_4, *(dequeuing_result.p_map->p_map));
    assert(test_result_4_bis == true);
    printf("  | |  Map 1 ... Success \n");

    free(dequeuing_result.p_map);

    //deuqueuing map 5
    printf("  | |  Dequeuing map 5 ... \n");
    dequeuing_result = dequeue_bis(list, p_first_last_pointers);
    list = dequeuing_result.queue;

    bool test_result_5_bis = comparaison_two_maps(*loaded_map_5, *(dequeuing_result.p_map->p_map));
    assert(test_result_5_bis == true);
    printf("  | |  Map 5 ... Success \n");

    free(dequeuing_result.p_map);
     

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