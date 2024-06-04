#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define NMAX 100
#define LMAX 100

typedef struct Date {
    int day;
    int month;
    int year;
} TDate;

typedef struct Task {
    char description[LMAX];
    char dutyManager[LMAX];
    int priority; // 1 for high, 0 for low
    TDate creationDate;
    TDate dueDate;
} TTask;

typedef struct Data {
    TTask tasks[NMAX];
    int elements;
} TData;

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
    int option, index;

    printf("\nIngresa el día de hoy: ");
    scanf("%d", &date.day);
    printf("Ingresa el mes de hoy: ");
    scanf("%d", &date.month);
    printf("Ingresa el año de hoy: ");
    scanf("%d", &date.year);

    do {
        // Menú que se mostrará cada vez que se ejecute el programa
        printf("\n-----------------------------------\n");
        printf("Nueva tarea (1)\n");
        printf("Modificar una tarea (2)\n");
        printf("Borrar una tarea (3)\n");
        printf("Mostrar tareas (4)\n");
        printf("Tareas urgentes (5)\n");
        printf("Tareas del manager (6)\n");
        printf("Salir (7)\n");
        printf("-----------------------------------\n");
        printf("Ingresa una opción: ");
        fflush(stdout); fflush(stdin);
        scanf("%d", &option);
        fflush(stdin);

        switch (option) {
            case 1:
                newTask(&data, &date);    
                break;
            case 2:
                printf("\nIngrese el índice de la tarea a modificar: ");
                scanf("%d", &index);
                modifyTask(&data, index);
                break;
            case 3:
                printf("\nIngrese el índice de la tarea a eliminar: ");
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
            default:
                printf("\nOpción no válida\n");
                break;
        }
    } while (1);
}

bool isFull(TData* data) {
    return data->elements == NMAX;
}

bool isEmpty(TData* data) {
    return data->elements == 0;
}

void newTask(TData* data, TDate* date) {
    if (isFull(data)) {
        printf("\nLa lista está llena.\n");
        return;
    }

    TTask new_task;
    printf("\nDescripción de la nueva tarea: ");
    scanf(" %99[^\n]", new_task.description);
    printf("Manager a cargo de la nueva tarea: ");
    scanf(" %99[^\n]", new_task.dutyManager);
    printf("Prioridad (1 es alta, 0 es baja): ");
    scanf("%d", &new_task.priority);
    printf("Fecha de vencimiento (día): ");
    scanf("%d", &new_task.dueDate.day);
    printf("Fecha de vencimiento (mes): ");
    scanf("%d", &new_task.dueDate.month);
    printf("Fecha de vencimiento (año): ");
    scanf("%d", &new_task.dueDate.year);

    new_task.creationDate = *date;

    int pos = 0;
    if (new_task.priority == 1) {
        for (pos = data->elements; pos > 0; pos--) {
            data->tasks[pos] = data->tasks[pos - 1];
        }
        data->tasks[0] = new_task;
    } else {
        for (pos = 0; pos < data->elements; pos++) {
            if (data->tasks[pos].priority != 1) {
                break;
            }
        }
        for (int j = data->elements; j > pos; j--) {
            data->tasks[j] = data->tasks[j - 1];
        }
        data->tasks[pos] = new_task;
    }

    data->elements++;
    printf("\n¡Nueva tarea añadida con éxito!\n");
}

void modifyTask(TData* data, int index) {
    if (isEmpty(data)) {
        printf("\nLa lista está vacía.\n");
        return;
    }

    if (index < 1 || index > data->elements) {
        printf("\nÍndice fuera de rango.\n");
        return;
    }

    index--;
    TTask* task = &data->tasks[index];
    printf("\nNueva descripción de la tarea: ");
    scanf(" %99[^\n]", task->description);
    printf("Nuevo manager a cargo de la tarea: ");
    scanf(" %99[^\n]", task->dutyManager);
    printf("Nueva prioridad (1 es alta, 0 es baja): ");
    scanf("%d", &task->priority);
    printf("Nueva fecha de vencimiento (día): ");
    scanf("%d", &task->dueDate.day);
    printf("Nueva fecha de vencimiento (mes): ");
    scanf("%d", &task->dueDate.month);
    printf("Nueva fecha de vencimiento (año): ");
    scanf("%d", &task->dueDate.year);

    printf("\n¡La tarea en el índice %d fue modificada con éxito!\n", index + 1);
}

void deleteTask(TData* data, int index) {
    if (isEmpty(data)) {
        printf("\nLa lista está vacía.\n");
        return;
    }

    if (index < 1 || index > data->elements) {
        printf("\nÍndice fuera de rango.\n");
        return;
    }

    index--;
    for (int i = index; i < data->elements - 1; i++) {
        data->tasks[i] = data->tasks[i + 1];
    }
    data->elements--;

    printf("\n¡La tarea en el índice %d fue eliminada con éxito!\n", index + 1);
}


void showTasks(TData* data) {
    if (isEmpty(data)) {
        printf("\nLa lista está vacía.\n");
        return;
    }

    printf("\nTareas:\n");
    for (int i = 0; i < data->elements; i++) {
        TTask task = data->tasks[i];
        printf("\n-----------------------------------\n");
        printf("Descripción: %s\n", task.description);
        printf("Manager responsable: %s\n", task.dutyManager);
        printf("Prioridad (1 es alta, 0 es baja): %d\n", task.priority);
        printf("Fecha de creación: %d/%d/%d\n", task.creationDate.day, task.creationDate.month, task.creationDate.year);
        printf("Fecha de vencimiento: %d/%d/%d\n", task.dueDate.day, task.dueDate.month, task.dueDate.year);
        printf("-----------------------------------\n");
    }
}


void urgentTasks(TData* data) {
    if (isEmpty(data)) {
        printf("\nLa lista está vacía.\n");
        return;
    }

    printf("\nTareas urgentes:\n");
    bool found = false;
    for (int i = 0; i < data->elements; i++) {
        if (data->tasks[i].priority == 1) {
            TTask task = data->tasks[i];
            printf("\n-----------------------------------\n");
            printf("Descripción: %s\n", task.description);
            printf("Manager responsable: %s\n", task.dutyManager);
            printf("Prioridad: Alta\n");
            printf("Fecha de creación: %d/%d/%d\n", task.creationDate.day, task.creationDate.month, task.creationDate.year);
            printf("Fecha de vencimiento: %d/%d/%d\n", task.dueDate.day, task.dueDate.month, task.dueDate.year);
            printf("-----------------------------------\n");
            found = true;
        }
    }

    if (!found) {
        printf("No hay tareas urgentes.\n");
    }
}

void managerTasks(TData* data){}