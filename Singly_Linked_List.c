/*
 * Singly_Linked_List.c
 *
 *  Created on: july , 2023
 *      Author: Ahmed Samy El Nozahy
 */

#include"Singly_Linked_List.h"


const char *title_str[3] = {"Junior", "Senior", "Lead"};


//fun to create linkedlist
sll_t* create_list(){
    
    sll_t *list = malloc(1*sizeof(node_t));
    if(list == NULL)
        return NULL;    
    list->head = NULL;
    list->size = 0;
    return list;

}

//fun to append node at the end of the linkedlist
EN_SLL_state_t append_node(sll_t *list , emp_t employee_data){

    if(list == NULL)
        return LL_NOT_OK;

    node_t *new_node = create_node(employee_data);

    if(new_node == NULL)
        return LL_NODE_NOT_CREATED;
    
    if (list->head == NULL)
    {
        list->head = new_node;
    }
    else
    {
        node_t* current = list->head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = new_node;
    }

    list->size++;
    return LL_OK;

}

//fun to create new nodes
node_t * create_node(emp_t emp_Data){

    node_t *new_node = malloc(1*sizeof(node_t));
    if(new_node == NULL)
        return NULL;
    
    new_node->employee_data = emp_Data;
    new_node->next = NULL;
    return new_node;
}

//fun to display the linkedlist

void display_all_list(sll_t* list)
{ 
    if ((list == NULL)||(list->head == NULL))
    {
        printf("\n--------------------- there is no Data !! --------------------\n");
    }
    printf("\n--------------------------------------------------------------\n");

    int i = 0;
    node_t* current = list->head;

    while (current != NULL)
    {
        printf("\n------------- Employee no.%d ---------------\n", i + 1);
		printf("ID: %d\n", current->employee_data.id);
        printf("Name: %s\n", (char *)current->employee_data.name);
        printf("Age: %d\n", current->employee_data.age);
        printf("Salary: %.2f\n", current->employee_data.salary);
        print_title(current->employee_data.title);

        current = current->next;
        i++;
    }

    printf("\n-------------------------------------------\n");
}



//fun to free the list
EN_SLL_state_t free_list(sll_t* list)
{
    if(list == NULL)
        return LL_NOT_OK;
    
    if(list->head == NULL)
        return LL_NODE_EMPTY;
    
    node_t * current = list->head;

    while (current != NULL)
    {
        list->head = list->head->next;
        
        free(current);
        current = list->head;
    }

    return LL_OK;

}


EN_SLL_state_t search_node(sll_t* list , id_t id, node_t** retNode)
{
    if(list == NULL)
        return LL_NOT_OK;
    
    if(list->head == NULL)
        return LL_NODE_EMPTY;

    node_t *current = list->head; 

    while (current != NULL)
    {
        if (current->employee_data.id == id)
        {
            *retNode = current;
            return LL_OK;
        }
        current = current->next;
    }

    return LL_NODE_NOT_FOUND;

}
EN_SLL_state_t delete_node_byValue(sll_t * list , id_t id)
{
    if(list == NULL)
        return LL_NOT_OK;
    
    if(list->head == NULL)
        return LL_NODE_EMPTY;

    node_t * current = list->head , *previous = current;
    if(current->employee_data.id == id)//val to be deleted at head
    { 
        list->head = list->head->next;
        free(current);
        list->size--;
        return LL_OK;
    }
    while (current != NULL && current->employee_data.id != id)//current != NULL must be first not to dereferencing a NULL Ptr
    {
        previous = current;
        current = current->next;

    }
    //not found
    if(current == NULL)
    {
        printf("Node NOT found !!\n");
        return LL_NODE_NOT_FOUND;
    }
    else{//found
        previous->next = current->next;
        list->size--;
        free(current);
        return LL_OK;
    }
}


EN_SLL_state_t delete_node_byPosition(sll_t * list , int pos)
{
    if(list == NULL)
        return LL_NOT_OK;
        
    if (pos < 0 || pos > list->size)
        return LL_NOT_OK;
    
    if(list->head == NULL)
        return LL_NODE_EMPTY;

    node_t * current = list->head , *previous = current;

    if(pos == 0)
    {
        list->head = list->head->next;
        free(current);
        list->size--;
        return LL_OK;
    }
    for(int i = 0; i < pos && current != NULL ;i++)
    {
        previous = current;
        current = current->next;
    }
    if(current == NULL)
    {
        previous->next = NULL;
        list->size--; 
        free(current);

        return LL_OK;
    }
    previous->next = current->next;
    list->size--;
    free(current);
    return LL_OK;

    
}

//function to insert a node in a position
EN_SLL_state_t insert_node_atPos(sll_t * list , emp_t emp_Data , int pos)
{
    if(list == NULL)
        return LL_NOT_OK;
    if (pos < 0 || pos > list->size)
        return LL_NOT_OK;
    if(list->head == NULL)
        return LL_NODE_EMPTY;
    
    node_t * new_node = create_node(emp_Data);
    node_t * current = list->head , *previous = current;
    if(pos == 0)
    {        
        new_node->next = list->head; 
        list->head = new_node;
        list->size++;
        return LL_OK;
    }
    
    for(int i = 0; i < pos && current != NULL ;i++)
    {
        previous = current;
        current = current->next;
    }
    if(current == NULL)
    {
        previous->next = new_node;
        new_node->next = current;

        list->size++;
        return LL_OK;
    }
    previous->next = new_node;
    new_node->next = current;
    list->size++;
    return LL_OK;



}

void print_title(EN_Title_t title)
{
    switch (title)
    {
    case 0:
        printf("Title: %s\n", title_str[0]);
        break;
    case 1:
        printf("Title: %s\n", title_str[1]);
        break;
    case 2:
        printf("Title: %s\n", title_str[2]);
        break;
    
    default:
        break;
    }
}