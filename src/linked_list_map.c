/**
 * @file linked_list_map.c
 * 
 * @brief The file containing all the functions for the linked list.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "linked_list_map.h"
#include "sokoban.h"
#include "loader.h"


linked_list_map nil(){
    return NULL;
}

linked_list_map cons(game_map *p_map, linked_list_map list){
    //allocating the needed memory for the cell
    cell_map *p_new_list = (cell_map *) malloc(sizeof(cell_map));

    //filling the new cell
    p_new_list->p_map = p_map;
    p_new_list->p_next = list; 

    return p_new_list;
}

bool is_empty(linked_list_map list){
    if (list == NULL){
        return true;
    } else {
        return false;
    }
}

game_map *get_element(linked_list_map list, int indice){
    cell_map *current_cell = list;

    //Go to the wanted indice in the list and returning the game map
    for (int ind = 0; ind < indice; ind++){
        current_cell = current_cell->p_next;
    }
    return current_cell->p_map;
}

linked_list_map insert_element(linked_list_map list, int indice, game_map *p_map){
    cell_map *current_cell = list;
    cell_map *old_cell = list;
    // allocating the needed space for the new cell
    cell_map *new_cell = (cell_map *)malloc(sizeof(cell_map));

    //particular case : indice = 0
    if (indice == 0){
        free(new_cell);
        return cons(p_map, list);
    }
    else{
        //going to the the right places in the list :
        //current_cell = cell after the new cell / old_cell = cell before the new cell
        for (int ind = 0; ind < indice; ind++){
            current_cell = current_cell->p_next;
        }
        for (int ind = 0; ind < indice - 1; ind++){
            old_cell = old_cell->p_next;
        }

        //filling the new cell and linking it to the next cell
        new_cell->p_map = p_map;
        new_cell->p_next = current_cell;

        //linking the previous cell to the new cell 
        old_cell->p_next = new_cell;

        return list;
    }
}

linked_list_map remove_element(linked_list_map list, int indice){
    cell_map *current_cell = list;
    cell_map *old_cell = list;
    cell_map *copy_cell;

    //particular case : indice = 0
    if (indice == 0){
        return list->p_next;
    }
    else{
        // going to the right places in the list :
        // current cell = cell after the removed cell / old_cell = cell before the removed cell
        for (int ind = 0; ind < indice; ind++){
            current_cell = current_cell->p_next;
        }
        for (int ind = 0; ind < indice - 1; ind++){
            old_cell = old_cell->p_next;
        }

        //linking the old and current cell
        copy_cell = current_cell;
        current_cell = current_cell->p_next;
        old_cell->p_next = current_cell;

        //freeing the cell that is removed
        free(copy_cell);
        
        return list;
    }
}

void deallocate_list(linked_list_map list){
    if (is_empty(list) == false){
        deallocate_list(list->p_next);

        //freeing the cell
        free(list);
    }    
}

void deallocate_list_solver(linked_list_map list){
    if (is_empty(list) == false){
        deallocate_list(list->p_next);

        //freeing only the cell, the string giving the map and the structure giving the game_map are 
        //freed using the dequeue_queue (only used in the solver)
        free(list);
    }    
}