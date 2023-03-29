/**
 * @file test-replay.c
 * 
 * @brief Test if the replays works.
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "sokoban.h"
#include "loader.h"


/**
 * @brief A function that tests the replay function.
 * 
 * @param adress_original_file The first map to which you want to move the player.
 * 
 * @param plan_length The number of movement you want to make from the list (should be < length of the plan).
 * 
 * @param plan The string containing the movements characters.
 * 
 * @param adress_result_file The adress of the map you should get a the end of the test (it's loaded to then compare the map build with replay with this one).
 */

void test_replay(const char *adress_original_file, int plan_length, char *plan, const char *adress_result_file){
    printf("  | | Testing the replay with %s, a plan length of %d, a plan of %s ... \n", adress_original_file, plan_length, plan);

    //loading the differents maps used for the test
    game_map *original_map = map_loader(adress_original_file);
    game_map *result_map = map_loader(adress_result_file);
    game_map *result_map_after_movements = replay(original_map, plan_length, plan);

    bool test_result = comparaison_two_maps(*result_map, *result_map_after_movements);
    assert(test_result == true);
    printf("  | | | Success \n");

    //freeing the allocations 
    free(result_map_after_movements->map);
    free(result_map_after_movements);
    free(result_map->map);
    free(result_map);
    free(original_map->map);
    free(original_map);
}


/**
 * @brief The main of this file that should test replaying some maps.
 * 
 * @return Nothing 
 */

int main(void){
    printf("* Starting replay tests...\n");

    //tests with soko_dumb.in
    test_replay("./data/soko_dumb.in", 3, "SSSEENN", "./data/soko_dumb_1.in");
    test_replay("./data/soko_dumb.in", 5, "SSSEENN", "./data/soko_dumb_2.in");
    test_replay("./data/soko_dumb.in", 7, "SSSEENN", "./data/soko_dumb_win.in");
    test_replay("./data/soko_dumb.in", 7, "ESEESSWNN", "./data/soko_dumb_3.in");
    test_replay("./data/soko_dumb.in", 9, "ESEESSWNN", "./data/soko_dumb_win.in");
    printf("\n");

    //tests with soko1
    //extracting the big plan from soko1-plan.in
    char big_plan[] = "NNWWSWWNEESWSWWWNNEESSESSWWNSEENNNENENESSSWSWENEESWWNENNWWSWWNWWSSESSEENNWNEWNEEENESSSWSWENENNWWWWWWSSESSEENNWESEENEESWWWENENNWWWWSSENWNEEENESSNWWWWWWSSESSEENEEEENWSWWWNNWNEEENESSSESWW";
    test_replay("./data/soko1.in", 100, big_plan, "./data/soko1_1.in");
    test_replay("./data/soko1.in", 150, big_plan, "./data/soko1_2.in");
    test_replay("./data/soko1.in", 184, big_plan, "./data/soko1_win.in");
    printf("\n");


    printf("  +-> OK!\n");
    printf("\n");

    return 0;
}