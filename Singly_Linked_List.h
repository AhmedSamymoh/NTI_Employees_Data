/*
 * Singly_Linked_List.h
 *
 *  Created on: july , 2023
 *      Author: Ahmed Samy El Nozahy
 */

#ifndef SINGLY_LINKED_LIST_H
#define SINGLY_LINKED_LIST_H

#include<stdio.h>
#include<stdlib.h>
#include"Std_Types.h"


typedef int data_t;
typedef unsigned int id_t;


typedef enum title_tag
{
    Junior,
    Senior,
    Lead
} EN_Title_t;

typedef struct employee_tag
{
    char name[50];
    int age;
    float salary;
    id_t id;
    EN_Title_t title;
} emp_t;

typedef struct tag_node
{
    emp_t employee_data;
    struct tag_node *next;
}node_t;

typedef struct tag_singly_linkedlist
{
    node_t* head;
    int size;
}sll_t;


typedef enum
{
    LL_OK,
    LL_NOT_OK,
    LL_NODE_NOT_CREATED,
    LL_NODE_NOT_FOUND,
    LL_NODE_EMPTY
}EN_SLL_state_t;



//function to create linkedlist
sll_t* create_list();

//function to append node at the end of the linkedlist
EN_SLL_state_t append_node(sll_t *list , emp_t employee_data);

//function to create new nodes
node_t * create_node(emp_t employee_data);

//function to display the linkedlist
void display_all_list(sll_t* list);

//function to free the list
EN_SLL_state_t free_list(sll_t* list);

//function to search for a certain node
EN_SLL_state_t search_node(sll_t* list , id_t id, node_t** retNode);

//function to clear a node byValue
EN_SLL_state_t delete_node_byValue(sll_t * list , id_t id);


//function to insert a node in a position
EN_SLL_state_t insert_node_atPos(sll_t * list , emp_t emp_Data , int pos);

//function to clear a node byPosition
EN_SLL_state_t delete_node_byPosition(sll_t * list , int pos);

//function to print the title
void print_title(EN_Title_t title);
















#endif