/*
 * App.h
 *
 *  Created on: july , 2023
 *      Author: Ahmed Samy El Nozahy
 */

#include"../SinglyLinkedList/Singly_Linked_List.h"
#include <ctype.h>


extern const char* title_str[];


typedef enum state_tag
{   
    InValid,
    Valid
} EN_state_t;


void app();
void Add_New_User();
void modify_employee_data();
void delete_employee_data();
void view_employee_data();
void print_menu();
void back_to_menu();


EN_state_t isValidAge(uint8_t age );
EN_state_t isValidName(char *Name);
EN_state_t isValidID(sll_t* emp_list ,uint16_t ID );
