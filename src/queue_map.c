/**
 * @file queue_map.c
 * 
 * @brief The file containing all the functions for the queue.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "queue_map.h"
#include "sokoban.h"
#include "loader.h"


queue_map nil_queue(){
    return NULL;
}

queue_map enqueue_bis(queue_map queue, first_last_pointers *p_first_last_pointers, game_map *p_map, char direction, cell_map_queue *p_mother){
    //allocating the memory space for the new cell
    cell_map_queue *p_new_cell = (cell_map_queue*)malloc(sizeof(cell_map_queue));

    //filling the new cell with the given data
    p_new_cell->direction = direction;
    p_new_cell->p_map = p_map;
    p_new_cell->p_next = NULL;
    p_new_cell->p_mother = p_mother;

    //linking the new cell to the whole queue and changing the first and last pointers 
    //There are two case: the first one when the queue is empty and when the queue is not
    if (is_empty_queue(queue) == true){
        queue = p_new_cell;
        p_first_last_pointers->p_first = p_new_cell;
        p_first_last_pointers->p_last = p_new_cell;
    }else{
        (p_first_last_pointers->p_last)->p_next = p_new_cell;
        p_first_last_pointers->p_last = p_new_cell;
    }
    return queue;
} 

dequeuing_tool dequeue_bis(queue_map queue, first_last_pointers *p_first_last_pointers){
    dequeuing_tool result;

    //two case : the first one if there is only one map left, and the other if not
    if (p_first_last_pointers->p_first == p_first_last_pointers->p_last){
        //filling the result
        result.p_map = queue;
        result.queue = NULL;

        //changing the first and last pointers
        p_first_last_pointers->p_first = NULL;
        p_first_last_pointers->p_last= NULL;

        return result;
    }else{
        //filling the result
        result.p_map = p_first_last_pointers->p_first;
        result.queue = queue->p_next;
        
        //changing the first and last pointers
        p_first_last_pointers->p_first = queue->p_next;

        return result;
    }
}

bool is_empty_queue(queue_map queue){
    if (queue == NULL){
        return true;
    } else {
        return false;
    }
}

game_map *get_element_queue(queue_map queue, int indice){
    cell_map_queue *current_cell = queue;

    //going to the wanted cell
    for (int ind = 0; ind < indice; ind++){
        current_cell = current_cell->p_next;
    }

    //returning the map
    return current_cell->p_map;
}

void deallocate_queue_solver(queue_map queue){
    if (is_empty_queue(queue) == false){
        deallocate_queue_solver(queue->p_next);

        //freeing all the allocated memory space, for a string representing the map, 
        //the structure that contains the game map and the cell of the queue
        free(queue->p_map->map);
        free(queue->p_map);
        free(queue);
    }    
}