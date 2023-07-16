/*
 * App.c
 *
 *  Created on: july , 2023
 *      Author: Ahmed Samy El Nozahy
 */


#include"app.h"

int flag = 1;
int indx = 0;
char name[10];

sll_t *employees_list;
extern const char *title_str[3];
int choice = 0;
int counter;

void app()
{   
    system("cls");//for windows
    printf("\033[2J\033[H"); //for linux
    employees_list = create_list();
    
    while (flag)
    {
        
        if(counter == 0)
        {
            print_menu();
            counter++;
        }
        else
        {
			getchar();//to clear buffer
            back_to_menu();
        }
        scanf("%d", &choice);

        
        switch (choice)
        {
            case 1:
                Add_New_User();
                break;
            case 2:
                modify_employee_data();
                break;
            case 3:
                delete_employee_data();
                break;
            case 4:
                view_employee_data();
                break;
            case 5:
                display_all_list(employees_list);
                break;
            default:
                flag = 0;
                break;
        }
    }
    
}

void Add_New_User()
{
    //
    while (indx != 100)
    {
        emp_t input_emp;

        printf("\n------------- Employee no.%d ---------------\n", indx + 1);
        
        printf("Enter employee's name: ");
        //fgets(input_emp.name, sizeof(input_emp.name), stdin);
        getchar();
        fflush(stdout);
        fflush(stdin);
        scanf("%[^\n]s", (char *)input_emp.name);
        getchar();//To clear the buffer 

        printf("Enter employee's ID: ");
        fflush(stdin);

        scanf("%u", &input_emp.id);
        getchar(); 

        printf("Enter employee's age: ");
        scanf("%d", &input_emp.age);
        getchar(); 

        printf("Enter employee's salary: ");
        scanf("%f", &input_emp.salary);
        getchar(); 

        printf("Enter employee's title (1. Junior 2. Senior 3. Lead): ");
        int title = 0;
        scanf("%d", &title);

        getchar(); 
        input_emp.title = (EN_Title_t)(title - 1);

        if ((isValidName(input_emp.name) == InValid )
            || (isValidAge(input_emp.age) == InValid) 
            || (isValidID(employees_list, input_emp.id) == InValid))
        {
            printf("\n Please try again.\n");
            continue;
        }

        append_node(employees_list, input_emp);
        indx++;

        printf("\nEmployee added successfully!\n");
        back_to_menu();

        char choice[2];
        printf("\nDo you want to add another employee (Y/n): ");
        fflush(stdout);
        fflush(stdin);
        scanf("%[^\n]s",choice);
        
        //scanf("%c", &choice);
        
        fflush(stdout);
        fflush(stdin);

        if (choice[0] == 'n' || choice[0] == 'N'||choice[1] == 'n' || choice[1] == 'N')
        
            break;       
        printf("\n--------------------------------------------\n");

    }
}

void modify_employee_data()
{
    printf("Enter the ID of the employee to modify: ");
    id_t id;
    scanf("%u", &id);
    getchar();

    node_t* retNode = NULL;
    EN_SLL_state_t searchResult = search_node(employees_list, id, &retNode);

    if (searchResult == LL_OK)
    {
        printf("\n------------- Modifying Employee Data ---------------\n");
        printf("Name: %s\n", (char *)retNode->employee_data.name);
        printf("Age: %d\n", retNode->employee_data.age);
        printf("Salary: %.2f\n", retNode->employee_data.salary);

        printf("Enter the new employee's name: ");
        fgets((char *)retNode->employee_data.name, sizeof(retNode->employee_data.name), stdin);//to prevent buffer overflow

        printf("Enter the new employee's age: ");
        scanf("%d", &retNode->employee_data.age);
        getchar(); 

        printf("Enter the new employee's salary: ");
        scanf("%f", &retNode->employee_data.salary);
        getchar(); 

        printf("\nEmployee data modified successfully!\n");
    }
    else if (searchResult == LL_NODE_NOT_FOUND)
    {
        printf("\nEmployee with ID %u not found!\n", id);
    }
    else
    {
        printf("\nError occurred while searching for the employee!\n");
    }
}

void delete_employee_data()
{
    printf("Enter the ID of the employee to delete: ");
    id_t id;
    scanf("%u", &id);
    getchar(); 

    EN_SLL_state_t deleteResult = delete_node_byValue(employees_list, id);

    if (deleteResult == LL_OK)
    {
        printf("\nEmployee with ID %u deleted successfully!\n", id);
    }
    else if (deleteResult == LL_NODE_NOT_FOUND)
    {
        printf("\nEmployee with ID %u not found!\n", id);
    }
    else
    {
        printf("\nError occurred while deleting the employee!\n");
    }
}

void view_employee_data()
{
    printf("Enter the ID of the employee to view: ");
    id_t id;
    scanf("%u", &id);
    getchar(); 

    node_t* retNode = NULL;
    EN_SLL_state_t searchResult = search_node(employees_list, id, &retNode);

    if (searchResult == LL_OK)
    {
        printf("\n------------- Employee Data ---------------\n");
        printf("Name: %s\n", (char *)retNode->employee_data.name);
        printf("Age: %d\n", retNode->employee_data.age);
        printf("Salary: %.2f\n", retNode->employee_data.salary);
        print_title(retNode->employee_data.title);
    }
    else if (searchResult == LL_NODE_NOT_FOUND)
    {
        printf("\nEmployee with ID %u not found!\n", id);
    }
    else
    {
        printf("\nError occurred while searching for the employee!\n");
    }
}

EN_state_t isValidAge(uint8_t age )
{
    if ((age > 60) || (age < 0))
    {
        printf("\nInvalid age\n");
        return InValid;
    }
   return Valid;

}

EN_state_t isValidName(char *Name)
{
    if ((sizeof(Name) > 45)|| !isalpha(*Name))
    {
        printf("\nInvalid Name\n");
        return InValid;
    }
    else
    {
        return Valid;
    }
}

EN_state_t isValidID(sll_t* emp_list ,uint16_t ID )
{   
    node_t* current = emp_list->head;

    while (current != NULL) {
        if (current->employee_data.id == ID) {
            printf("\nID already exists in the employee list.\n");
            return InValid;
        }
        current = current->next;

    }
    // for (int i = 0; i < 10; i++)
    // {
    //     if (!isdigit(ID))
    //     {
    //     printf("\nInvalid ID\n");
    //     return InValid;
    //     }
    // }
    return Valid;
}
void print_menu()
{   
    printf("\n\t\t\t\t==============================================================\n");
    printf("\t\t\t\t==================                         ===================\n");
    printf("\t\t\t\t================== EMPLOYEES DATA's SYSTEM ===================\n");
    printf("\t\t\t\t==================                         ===================\n");
    printf("\t\t\t\t==============================================================\n");
    printf("\t\t\t\t=== 1- Add a new employee data                             ===\n");
    printf("\t\t\t\t=== 2- Modify the data of an employee                      ===\n");
    printf("\t\t\t\t=== 3- Delete the data of an employee                      ===\n");
    printf("\t\t\t\t=== 4- View the data of an employee                        ===\n");
    printf("\t\t\t\t=== 5- View all the employee's data                        ===\n");
    printf("\t\t\t\t=== .. Any key to exit ..                                  ===\n");
    printf("\t\t\t\t==============================================================\n");
    printf("\t\t\t\tPlease select one of the options:");
}
void back_to_menu()
{
    char choice;
    printf("\n .. Press any thing to go back .. ");
    fflush(stdin);
    fflush(stdout);
    scanf("%c", &choice);

    if (choice !=27)
    {
        system("cls");
        printf("\033[2J\033[H");
        print_menu();
    }
}
