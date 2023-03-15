#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "queue_map.h"
#include "sokoban.h"
#include "loader.h"


queue_map nil_queue(){
    return NULL;
}

queue_map cons_queue(game_map *p_map, queue_map queue, char direction, int depth, cell_map *p_mother){
    cell_map *p_new_queue = (cell_map *) malloc(sizeof(cell_map));

    p_new_queue->depth = depth;
    p_new_queue->direction = direction;
    p_new_queue->p_mother = p_mother;
    p_new_queue->p_map = p_map;
    p_new_queue->p_next = queue; 
    return p_new_queue;
}

enqueuing_tool enqueue(first_last_pointers *first_last_pointers, game_map *p_map, queue_map queue, char direction, int depth, cell_map *p_mother){
    enqueuing_tool enqueuing_tool;
    cell_map *p_new_cell = (cell_map *) malloc(sizeof(cell_map));

    // filling the new cell with the needed informations and linking the pointers
    p_new_cell->depth = depth;
    p_new_cell->direction = direction;
    p_new_cell->p_mother = p_mother;
    p_new_cell->p_map = p_map;
    *(first_last_pointers->p_last)->p_next = *p_new_cell;

    first_last_pointers->p_last = p_new_cell;

    //fillinf the enqueuing tool
    enqueuing_tool.first_last_pointers = first_last_pointers;
    enqueuing_tool.queue = queue;

    return enqueuing_tool;
}

dequeuing_tool dequeue(first_last_pointers *first_last_pointers, queue_map queue){
    dequeuing_tool dequeuing_tool;
    cell_map *copy_cell;

    //filling the structure first_last_pointers
    first_last_pointers->p_first = queue->p_next;
    copy_cell = queue;

    //filling the dequeuing tool
    dequeuing_tool.p_map = queue->p_map;
    dequeuing_tool.first_last_pointers = first_last_pointers;
    dequeuing_tool.queue = queue->p_next;

    free(copy_cell);

    return dequeuing_tool;
}

int size_queue(queue_map queue){
    int size = 0;
    cell_map *index = queue;

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
    cell_map *index = queue;

    while (index != NULL){
        print_map(*(index->p_map));
        index = index->p_next;
    }
}

game_map *get_element_queue(queue_map queue, int indice){
    cell_map *current_cell = queue;

    for (int ind = 0; ind < indice; ind++){
        current_cell = current_cell->p_next;
    }
    return current_cell->p_map;
}

queue_map insert_element_queue(queue_map queue, int indice, game_map *p_map, char direction, int depth, cell_map *p_mother){
    cell_map *current_cell = queue;
    cell_map *old_cell = queue;
    cell_map *new_cell = (cell_map *)malloc(sizeof(cell_map));

    //particular case : indice = 0
    if (indice == 0){
        free(new_cell);
        return cons_queue(p_map, queue, direction, depth, p_mother);
    }
    else{
        for (int ind = 0; ind < indice; ind++){
            current_cell = current_cell->p_next;
        }
        for (int ind = 0; ind < indice - 1; ind++){
            old_cell = old_cell->p_next;
        }

        new_cell->p_map = p_map;
        new_cell->p_next = current_cell;
        new_cell->depth = depth;
        new_cell->direction = direction;
        new_cell->p_mother = p_mother;
        old_cell->p_next = new_cell;

        return queue;
    }
}

queue_map remove_element_queue(queue_map queue, int indice){
    cell_map *current_cell = queue;
    cell_map *old_cell = queue;
    cell_map *copy_cell;

    //particular case : indice = 0
    if (indice == 0){
        return queue->p_next;
    }
    else{
        for (int ind = 0; ind < indice; ind++){
            current_cell = current_cell->p_next;
        }
        for (int ind = 0; ind < indice - 1; ind++){
            old_cell = old_cell->p_next;
        }

        copy_cell = current_cell;
        current_cell = current_cell->p_next;
        old_cell->p_next = current_cell;
        free(copy_cell);
        
        return queue;
    }
}

void deallocate_queue(queue_map queue){
    if (is_empty_queue(queue) == false){
        deallocate_queue(queue->p_next);
        free(queue);
    }    
}