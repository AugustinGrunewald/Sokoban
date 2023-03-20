#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "queue_map.h"
#include "sokoban.h"
#include "loader.h"


queue_map nil_queue(){
    return NULL;
}

queue_map enqueue_bis(queue_map queue, first_last_pointers *p_first_last_pointers, game_map *p_map, char direction, int depth, cell_map_queue *p_mother){
    cell_map_queue *p_new_cell = (cell_map_queue*)malloc(sizeof(cell_map_queue));

    //filling the new cell with the given data
    p_new_cell->depth = depth;
    p_new_cell->direction = direction;
    p_new_cell->p_map = p_map;
    p_new_cell->p_next = NULL;
    p_new_cell->p_mother = p_mother;

    //linking the new cell to the whole queue and changing the first and last pointers (two case: the first one when the queue is empty and when the queue is not)
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

int size_queue(queue_map queue){
    int size = 0;
    cell_map_queue *index = queue;

    while (index != NULL) {
        index = index->p_next; 
        size++;
    }

    return size;
}

bool is_empty_queue(queue_map queue){
    if (queue == NULL){
        return true;
    } else {
        return false;
    }
}

void print_queue(queue_map queue){
    cell_map_queue *index = queue;

    while (index != NULL){
        print_map(*(index->p_map));
        index = index->p_next;
    }
}

game_map *get_element_queue(queue_map queue, int indice){
    cell_map_queue *current_cell = queue;

    for (int ind = 0; ind < indice; ind++){
        current_cell = current_cell->p_next;
    }
    return current_cell->p_map;
}

void deallocate_queue(queue_map queue){
    if (is_empty_queue(queue) == false){
        deallocate_queue(queue->p_next);
        free(queue);
    }    
}