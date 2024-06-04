#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define NMAX 100
#define LMAX 100

typedef struct Date{
    int day;
    int month;
    int year;
}TDate;

typedef struct Task{
    char description[LMAX];
    char dutyManager[LMAX];
    int  priority;
    TDate creationDate;
    TDate dueDate;
}TTask;

typedef struct Data{
    TTask tasks[NMAX];
    int elements;
}TData;

bool isEmpty(TData* data);
bool isFull(TData* data);
void newTask(TData* data, TDate* date);
void modifyTask(TData* data, int index);
void deleteTask(TData* data, int index);
void showTasks(TData* data);
void urgentTasks(TData* data);
void managerTasks(TData* data);

int main() {
    
    TData data = { .elements = 0 };
    TDate date;
    int option, index, month;

    printf("\nIngresa el día de hoy: ");
    scanf("%d", &date.day);
    printf("Ingresa el mes: de hoy: ");
    scanf("%d", &date.month);
    printf("Ingresa el año de hoy: ");
    scanf("%d", &date.year);

    do {
        //menu that will be displayed everytime the user runs the program
        printf("\n-----------------------------------\n");
        printf("Nueva tarea (1)\n");
        printf("Modificar una tarea (2)\n");
        printf("Borrar una tarea (3)\n");
        printf("Mostrar tareas (4)\n");
        printf("Tareas urgentes (5)\n");
        printf("Tareas del manager (6)\n");
        printf("Salir (7)");
        printf("\n-----------------------------------\n");
        printf("Ingresa una opción: ");
        fflush(stdout); fflush(stdin);
        scanf("%d", &option);
        fflush(stdin);

        switch (option){
            case 1:
                newTask(&data, &date);    
                break;

            case 2:
                printf("\nIngrese el índice de la tarea a modificar: ");
                scanf("%d", &index);
                modifyTask(&data, index);
                break;

            case 3:
                printf("\nIngrese el índice de la tarea a eliminar:");
                scanf("%d", &index);
                deleteTask(&data, index);
                break;

            case 4: 
                showTasks(&data);
                break;

            case 5: 
                urgentTasks(&data);
                break;

            case 6:
                managerTasks(&data);
                break;

            case 7:
                return 0;
                break;
            
            default: // option is not between 1 and 7.
                printf("\nOpción no válida\n");
                break;

        }
    } while (1);
}


bool isFull(TData* data){
    return data->elements == NMAX;
}

bool isEmpty(TData* data){
    return data->elements == 0;
}

void newTask(TData* data, TDate* date){
    char description[LMAX];
    char dutyManager[LMAX];
    int priority;
    TDate creationDate;
    TDate dueDate;

    if (isFull(data)) {
        printf("\nThe list is full.");
    } else {
        //data is asked to the user and stored in local variables.    
        printf("\nNew tasks' description: ");
        scanf(" %s", description);
        printf("New task duty manager: ");
        scanf(" %s", dutyManager);
        printf("Priority (1 is high, 0 is low): ");
        scanf("%d", &priority);
        printf("Input this task due date day: ");
        scanf("%d", &dueDate.day);
        printf("Input this task due date month: ");
        scanf("%d", &dueDate.month);
        printf("Input this task due date year: ");
        scanf("%d", &dueDate.year);

        if (priority == 1) {
            int j;
            //I shift every element forward to make room for the new expense.
            for (j = (*data).elements; j > 0; j--){
                (*data).tasks[j] = (*data).tasks[j - 1];
            }
            //store the data in the empty place
            strcpy((*data).tasks[j].description, description);
            strcpy((*data).tasks[j].dutyManager, dutyManager);
            (*data).tasks[j].priority = priority;
            (*data).tasks[0].creationDate.day = date->day;
            (*data).tasks[0].creationDate.month = date->month;
            (*data).tasks[0].creationDate.year = date->year;
            (*data).tasks[0].dueDate.day = dueDate.day;
            (*data).tasks[0].dueDate.month = dueDate.month;
            (*data).tasks[0].dueDate.year = dueDate.year;

            (*data).elements++;
            printf("\nNew expense added successfully!\n");

        } else {
            int i, pos;
            //this loop will traverse the array until it founds the first variable expense.
            for (i = 0; i < NMAX; i++) {
                if ((*data).tasks[i].priority != 1) {
                    break;
                }    
            }
            pos = i;
            //I shift every element forward to make room for the new expense.
            for (int j = (*data).elements; j >= pos; j--) {
                (*data).tasks[j] = (*data).tasks[j - 1];
            }
            //store the data in the empty place
            strcpy((*data).tasks[pos].description, description);
            strcpy((*data).tasks[pos].dutyManager, dutyManager);
            (*data).tasks[pos].priority = priority;
            (*data).tasks[0].creationDate.day = date->day;
            (*data).tasks[0].creationDate.month = date->month;
            (*data).tasks[0].creationDate.year = date->year;
            (*data).tasks[pos].dueDate.day = dueDate.day;
            (*data).tasks[pos].dueDate.month = dueDate.month;
            (*data).tasks[pos].dueDate.year = dueDate.year;

            (*data).elements++;
            printf("\nNew expense added successfully!\n");
        }
    }
}

void modifyTask(TData* data, int index) {
    char description[LMAX];
    char dutyManager[LMAX];
    TDate dueDate;

    if (isEmpty(data)) {
        printf("\nThe list is empty.");
    } else {
        index--;
        printf("\nNew tasks' description: ");
        scanf("%s", description);
        printf("New tasks' duty manager: ");
        scanf("%s", dutyManager);
        printf("New tasks' due date day: ");
        scanf("%d", &dueDate.day);
        printf("New tasks' due date month: ");
        scanf("%d", &dueDate.month);
        printf("New tasks' due date year: ");
        scanf("%d", &dueDate.year);

        strcpy((*data).tasks[index].description, description);
        strcpy((*data).tasks[index].dutyManager, dutyManager);
        (*data).tasks[index].dueDate.day = dueDate.day;
        (*data).tasks[index].dueDate.month = dueDate.month;
        (*data).tasks[index].dueDate.year = dueDate.year;
        printf("\nThe task at index %d was modified successfully!\n", ++index);
    }
}

void deleteTask(TData* data, int index) {

    if (isEmpty(data)) {
        printf("\nThe list is empty.");
    } else {
        index--;
        int i = index;
    
        for (; i < (*data).elements; i++) {
            (*data).tasks[i] = (*data).tasks[i + 1];
        }
        
        (*data).elements--;
        printf("\nTask at index %d was deleted successfully!\n", ++index);
    }
}

void showTasks(TData* data) {

    if (isEmpty(data)) {
        printf("\nThe list is empty.");
    } else {
        printf("\nTasks: \n");
        for (int i = 0; i < (*data).elements; i++) {
            printf("\n-----------------------------------\n");
            printf("Description: %s\n", (*data).tasks[i].description);
            printf("Duty manager: %s\n", (*data).tasks[i].dutyManager);
            printf("Priority (1 is high, 0 is low): %d\n", (int) (*data).tasks[i].priority);
            printf("Creation date: %d/%d/%d \n", (*data).tasks[i].creationDate.day, (*data).tasks[i].creationDate.month, (*data).tasks[i].creationDate.year);
            printf("Due date: %d/%d/%d", (*data).tasks[i].dueDate.day, (*data).tasks[i].dueDate.month, (*data).tasks[i].dueDate.year);
            printf("\n-----------------------------------\n");
        }
    }
}

void urgentTasks(TData* data){}

void managerTasks(TData* data){}