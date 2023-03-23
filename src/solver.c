#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include <SDL2/SDL.h>

#include "gui.h"
#include "solver.h"
#include "queue_map.h"
#include "linked_list_map.h"
#include "sokoban.h"
#include "loader.h"

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
    search_queue = enqueue_bis(search_queue, p_first_last_pointers, initial_map, '.', 0, NULL);
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
        p_current_map = p_current_cell->p_map;

        
        dequeued_queue = enqueue_bis(dequeued_queue, p_first_last_pointers_bis, p_current_map, p_current_cell->direction, p_current_cell->depth, p_current_cell->p_mother);

        if (wining_test(*p_current_map) == true){
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
                search_queue = enqueue_bis(search_queue, p_first_last_pointers,p_new_map, direction, p_current_cell->depth + 1, p_current_cell);
            }
        }
        // free(p_current_cell);
        // printf("ugefgvu\n");
    }

    cell_map_queue *p_current_cell_bis = p_first_last_pointers_bis->p_last;
    game_map *p_current_map_bis = p_current_cell_bis->p_map;

    if (wining_test(*p_current_map_bis) == true){
        //building the winning plan
        cell_map_queue *index = p_current_cell_bis;
        int length = plan_length(p_current_cell_bis);
        char plan_bis[length];

        for (int i = 0; i < length; i++){
            plan_bis[length - i - 1] = index->direction;
            index = index->p_mother;
        }
        //copying the plan without the first usefull character
        char plan[length - 1];
        for (int i = 0; i < length - 1; i++){
            plan[i] = plan_bis[i+1];
        }

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

bool searching_linked_list(game_map *p_map, linked_list_map list){
    bool result = false;
    cell_map *index = list;

    while (index != NULL) {
        if (comparaison_two_maps(*(index->p_map), *p_map) == true){
            result = true;
            return result;
        }
        index = index->p_next; 
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

void replay_solver(game_map *loaded_map, int length_direction_string, char *direction_string){
    game_map *current_step_map = loaded_map;

    int height = loaded_map->map_size.height;
    int width = loaded_map->map_size.width;

    // initialize GUI window
    GUI_init("Sokoban", width, height);

    printf("jwsefjgwsdfgwsf");

    // display first map
    GUI_show(width, height, current_step_map->map); 
    
    current_step_map = move(current_step_map, direction_string[0]);

    //display map after first movement
    GUI_show(width, height, current_step_map->map); 

    for(int direction_step = 1; direction_step < length_direction_string; direction_step++){
        char current_direction = direction_string[direction_step];

        game_map *next_step_map = move(current_step_map, current_direction);

        free(current_step_map->map);
        free(current_step_map);

        current_step_map = next_step_map;     

        //display level
        GUI_show(width, height, current_step_map->map); 
    }

    // closing the window
    GUI_close();

    printf("\n");
    printf("THIS COMPUTER IS TOO STRONG ...\n");
    printf("HE ALWAYS WIN :o \n");
    printf("\n");
}