/**
 * @file solver.c
 * 
 * @brief The file containing all the functions used in solver.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#include "solver.h"
#include "queue_map.h"
#include "linked_list_map.h"
#include "sokoban.h"
#include "loader.h"
#include "bst_map.h"

bool wining_test(game_map map){
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

stats *solver(game_map *initial_map){
    //initializing the result structure and launching the chronometer
    double time_spent = 0.0;
    clock_t begin = clock();
    stats *result = (stats*)malloc(sizeof(stats));
    int nmb_explored_nodes = 1;
    
    //for the solver the algorithm presented in the project pdf is used (see page 4)

    queue_map search_queue = nil_queue();
    queue_map dequeued_queue = nil_queue();
    linked_list_map explored_list = nil();

    //initializing the first last pointers used in the queue (creating two of them because two queue are used)
    first_last_pointers *p_first_last_pointers = (first_last_pointers *)malloc(sizeof(first_last_pointers));
    p_first_last_pointers->p_first = NULL;
    p_first_last_pointers->p_last = NULL;
    first_last_pointers *p_first_last_pointers_bis = (first_last_pointers *)malloc(sizeof(first_last_pointers));
    p_first_last_pointers_bis->p_first = NULL;
    p_first_last_pointers_bis->p_last = NULL;

    //starting the algorithm
    search_queue = enqueue_bis(search_queue, p_first_last_pointers, initial_map, '.', NULL);
    explored_list = cons(initial_map, explored_list);
    dequeuing_tool dequeue_result;


    while (is_empty_queue(search_queue) == false){
        //increasing the counter of nodes
        nmb_explored_nodes ++;

        //declaring the used structures
        game_map *p_current_map;
        cell_map_queue *p_current_cell;

        dequeue_result = dequeue_bis(search_queue, p_first_last_pointers);
        search_queue = dequeue_result.queue;
        p_current_cell = dequeue_result.p_map;

        //simpler name use in the rest of the loop
        p_current_map = p_current_cell->p_map;
        
        dequeued_queue = enqueue_bis(dequeued_queue, p_first_last_pointers_bis, p_current_map, p_current_cell->direction, p_current_cell->p_mother);

        //checking if there is a box in the corner, in this case don't search with this map
        if (box_in_corner(p_current_map) == false){
            if (wining_test(*p_current_map) == true){
                free(p_current_cell);
                break;
            }
            char available_direction[] = "NSEW";

            for (int i = 0; i < 4; i++){
                char direction = available_direction[i];

                game_map *p_new_map = move(p_current_map, direction);

                if (searching_linked_list(p_new_map, explored_list) == true){
                    free(p_new_map->map);
                    free(p_new_map);
                }else{
                    explored_list = cons(p_new_map, explored_list);
                    search_queue = enqueue_bis(search_queue, p_first_last_pointers, p_new_map, direction, p_first_last_pointers_bis->p_last);
                }
            }
        }
        free(p_current_cell);
    }

    cell_map_queue *p_current_cell_bis = p_first_last_pointers_bis->p_last;
    game_map *p_current_map_bis = p_current_cell_bis->p_map;

    if (wining_test(*p_current_map_bis) == true){
        //building the winning plan
        cell_map_queue *index = p_current_cell_bis;
        int length = plan_length(p_current_cell_bis);
        char plan_bis[length]; 

        //allocating enough place for the plan that will be return and that need to be saved after getting out of this function
        char *plan = (char*)malloc((length)* sizeof(char));

        //filling the plan_bis and then the real plan
        for (int i = 1; i < length; i++){
            plan_bis[length - i - 1] = index->direction;
            index = index->p_mother;
        }
        for(int i = 0; i < length - 1; i++){
            plan[i] = plan_bis[i];
        }
        plan[length - 1] = '\0';

        //filling the result structure
        result->solution_plan = plan;
        result->win = true;
        result->nmb_explored_nodes = nmb_explored_nodes;
        result->plan_length = length;


        //freeing the memory
        deallocate_queue_solver(search_queue);
        deallocate_queue_solver(dequeued_queue);
        deallocate_list_solver(explored_list);

        free(p_first_last_pointers);
        free(p_first_last_pointers_bis);

        //finishing the chronometer, translating the result into seconds and adding it in the result structure
        clock_t end = clock();
        time_spent += (double)(end - begin)/CLOCKS_PER_SEC;
        result->time_spent = time_spent;

        return result;
    }else{
        result->solution_plan = NULL;
        result->win = false;
        result->nmb_explored_nodes = nmb_explored_nodes;
        result->plan_length = 0;


        //freeing the memory
        deallocate_queue_solver(search_queue);
        deallocate_queue_solver(dequeued_queue);
        deallocate_list_solver(explored_list);

        free(p_first_last_pointers);
        free(p_first_last_pointers_bis);

        //finishing the chronometer, translating the result into seconds and adding it in the result structure
        clock_t end = clock();
        time_spent += (double)(end - begin)/CLOCKS_PER_SEC;
        result->time_spent = time_spent;

        return result;
    }
}

stats *solver_bst(game_map *initial_map){
    //initializing the result structure and launching the chronometer
    double time_spent = 0.0;
    clock_t begin = clock();
    stats *result = (stats*)malloc(sizeof(stats));
    int nmb_explored_nodes = 1;
    
    //for the solver the algorithm presented in the project pdf is used (see page 4)

    queue_map search_queue = nil_queue();
    queue_map dequeued_queue = nil_queue();
    bst_map explored_tree = nil_tree();

    //initializing the first last pointers used in the queue (creating two of them because two queue are used)
    first_last_pointers *p_first_last_pointers = (first_last_pointers *)malloc(sizeof(first_last_pointers));
    p_first_last_pointers->p_first = NULL;
    p_first_last_pointers->p_last = NULL;
    first_last_pointers *p_first_last_pointers_bis = (first_last_pointers *)malloc(sizeof(first_last_pointers));
    p_first_last_pointers_bis->p_first = NULL;
    p_first_last_pointers_bis->p_last = NULL;

    //starting the algorithm
    search_queue = enqueue_bis(search_queue, p_first_last_pointers, initial_map, '.', NULL);
    explored_tree = insert_tree(explored_tree, initial_map);
    dequeuing_tool dequeue_result;


    while (is_empty_queue(search_queue) == false){
        //increasing the counter of nodes
        nmb_explored_nodes ++;

        //declaring the used structures
        game_map *p_current_map;
        cell_map_queue *p_current_cell;

        dequeue_result = dequeue_bis(search_queue, p_first_last_pointers);
        search_queue = dequeue_result.queue;
        p_current_cell = dequeue_result.p_map;

        //simpler name use in the rest of the loop
        p_current_map = p_current_cell->p_map;
        
        dequeued_queue = enqueue_bis(dequeued_queue, p_first_last_pointers_bis, p_current_map, p_current_cell->direction, p_current_cell->p_mother);

        //checking if there is a box in the corner, in this case don't search with this map
        if (box_in_corner(p_current_map) == false){
            if (wining_test(*p_current_map) == true){
                free(p_current_cell);
                break;
            }
            char available_direction[] = "NSEW";

            for (int i = 0; i < 4; i++){
                char direction = available_direction[i];

                game_map *p_new_map = move(p_current_map, direction);

                if (searching_bst(explored_tree, p_new_map) == true){
                    free(p_new_map->map);
                    free(p_new_map);
                }else{
                    explored_tree = insert_tree(explored_tree, p_new_map);
                    search_queue = enqueue_bis(search_queue, p_first_last_pointers, p_new_map, direction, p_first_last_pointers_bis->p_last);
                }
            }
        }
        free(p_current_cell);
    }

    cell_map_queue *p_current_cell_bis = p_first_last_pointers_bis->p_last;
    game_map *p_current_map_bis = p_current_cell_bis->p_map;

    if (wining_test(*p_current_map_bis) == true){
        //building the winning plan
        cell_map_queue *index = p_current_cell_bis;
        int length = plan_length(p_current_cell_bis);
        char plan_bis[length]; 

        //allocating enough place for the plan that will be return and that need to be saved after getting out of this function
        char *plan = (char*)malloc((length)* sizeof(char));

        //filling the plan_bis and then the real plan
        for (int i = 1; i < length; i++){
            plan_bis[length - i - 1] = index->direction;
            index = index->p_mother;
        }
        for(int i = 0; i < length - 1; i++){
            plan[i] = plan_bis[i];
        }
        plan[length - 1] = '\0';

        //filling the result structure
        result->solution_plan = plan;
        result->win = true;
        result->nmb_explored_nodes = nmb_explored_nodes;
        result->plan_length = length;


        //freeing the memory
        deallocate_queue_solver(search_queue);
        deallocate_queue_solver(dequeued_queue);
        deallocate_tree(explored_tree);

        free(p_first_last_pointers);
        free(p_first_last_pointers_bis);

        //finishing the chronometer, translating the result into seconds and adding it in the result structure
        clock_t end = clock();
        time_spent += (double)(end - begin)/CLOCKS_PER_SEC;
        result->time_spent = time_spent;

        return result;
    }else{
        result->solution_plan = NULL;
        result->win = false;
        result->nmb_explored_nodes = nmb_explored_nodes;
        result->plan_length = 0;


        //freeing the memory
        deallocate_queue_solver(search_queue);
        deallocate_queue_solver(dequeued_queue);
        deallocate_tree(explored_tree);

        free(p_first_last_pointers);
        free(p_first_last_pointers_bis);

        //finishing the chronometer, translating the result into seconds and adding it in the result structure
        clock_t end = clock();
        time_spent += (double)(end - begin)/CLOCKS_PER_SEC;
        result->time_spent = time_spent;

        return result;
    }
}

bool searching_linked_list(game_map *p_map, linked_list_map list){
    bool result = false;
    cell_map *index = list;

    while (index != NULL) {
        //first testing if the players are at the same position, this really increased the solving process 
        if (index->p_map->player_pos.height == p_map->player_pos.height && index->p_map->player_pos.width == p_map->player_pos.width){
            if (strncmp(index->p_map->map, p_map->map, p_map->map_size.height * p_map->map_size.width) == 0){
                result = true;
                return result;
            }
            index = index->p_next;
        }else{
            index = index->p_next; 
        }
    }

    return result;
}

int plan_length(queue_map queue){
    int size = 0;
    cell_map_queue *index = queue;

    while (index != NULL) {
        index = index->p_mother; 
        size++;
    }

    return size;
}

bool box_in_corner(game_map *p_map){
    //initialasing some parameters
    bool result = false;
    int plan_length = p_map->map_size.height * p_map->map_size.width;
    char *map = p_map->map;

    for (int ind = 0; ind < plan_length; ind++){
        if (map[ind] == BOX_EMPTY){
            //four different case to check: 
            //two case with a wall on the left  
            if (map[ind - 1] == WALL){
                //checking above the player
                if (map[ind - p_map->map_size.width] == WALL){
                    result = true;
                    return result;
                }

                //checking under the player
                if (map[ind + p_map->map_size.width] == WALL){
                    result = true;
                    return result;
                }
            }

            //two case with a wall on the right
            if (map[ind + 1] == WALL){
                //checking above the player
                if (map[ind - p_map->map_size.width] == WALL){
                    result = true;
                    return result;
                }
                //checking under the player
                if (map[ind + p_map->map_size.width] == WALL){
                    result = true;
                    return result;
                }
            }
        }
    }

    return result;
}