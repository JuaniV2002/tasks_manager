// Enhanced Task Manager with basic improvements
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define NMAX 100
#define LMAX 100

#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define RESET "\033[0m"

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
void saveTasksToFile(TData* data, const char* filename);
void loadTasksFromFile(TData* data, const char* filename);
int compareDueDates(const void* a, const void* b);
void showTasksSortedByDueDate(TData* data);

int main() {
    TData data = { .elements = 0 };
    TDate date;
    int option, index;

    printf("\nIngresa el d\u00eda de hoy: ");
    scanf("%d", &date.day);
    printf("Ingresa el mes de hoy: ");
    scanf("%d", &date.month);
    printf("Ingresa el a\u00f1o de hoy: ");
    scanf("%d", &date.year);

    do {
        printf("\n-----------------------------------\n");
        printf("Nueva tarea (1)\n");
        printf("Modificar una tarea (2)\n");
        printf("Borrar una tarea (3)\n");
        printf("Mostrar tareas (4)\n");
        printf("Tareas urgentes (5)\n");
        printf("Tareas del manager (6)\n");
        printf("Guardar tareas en archivo (7)\n");
        printf("Cargar tareas desde archivo (8)\n");
        printf("Mostrar tareas ordenadas por vencimiento (9)\n");
        printf("Salir (10)\n");
        printf("-----------------------------------\n");
        printf("Ingresa una opci\u00f3n: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                newTask(&data, &date);
                break;
            case 2:
                printf("\nIngrese el \u00edndice de la tarea a modificar: ");
                scanf("%d", &index);
                modifyTask(&data, index);
                break;
            case 3:
                printf("\nIngrese el \u00edndice de la tarea a eliminar: ");
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
                saveTasksToFile(&data, "tasks.txt");
                break;
            case 8:
                loadTasksFromFile(&data, "tasks.txt");
                break;
            case 9:
                showTasksSortedByDueDate(&data);
                break;
            case 10:
                return 0;
            default:
                printf("\nOpcion no valida\n");
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
        printf("\nLa lista est\u00e1 llena.\n");
        return;
    }

    TTask new_task;
    printf("\nDescripci\u00f3n de la nueva tarea: ");
    scanf(" %99[^\n]", new_task.description);
    printf("Manager a cargo de la nueva tarea: ");
    scanf(" %99[^\n]", new_task.dutyManager);
    printf("Prioridad (1 es alta, 0 es baja): ");
    scanf("%d", &new_task.priority);
    printf("Fecha de vencimiento (d\u00eda): ");
    scanf("%d", &new_task.dueDate.day);
    printf("Fecha de vencimiento (mes): ");
    scanf("%d", &new_task.dueDate.month);
    printf("Fecha de vencimiento (a\u00f1o): ");
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
    printf("\n\u00a1Nueva tarea a\u00f1adida con \u00e9xito!\n");
}

void modifyTask(TData* data, int index) {
    if (isEmpty(data)) {
        printf("\nLa lista est\u00e1 vac\u00eda.\n");
        return;
    }

    if (index < 1 || index > data->elements) {
        printf("\n\u00cdndice fuera de rango.\n");
        return;
    }

    index--;
    TTask* task = &data->tasks[index];
    printf("\nNueva descripci\u00f3n de la tarea: ");
    scanf(" %99[^\n]", task->description);
    printf("Nuevo manager a cargo de la tarea: ");
    scanf(" %99[^\n]", task->dutyManager);
    printf("Nueva prioridad (1 es alta, 0 es baja): ");
    scanf("%d", &task->priority);
    printf("Nueva fecha de vencimiento (d\u00eda): ");
    scanf("%d", &task->dueDate.day);
    printf("Nueva fecha de vencimiento (mes): ");
    scanf("%d", &task->dueDate.month);
    printf("Nueva fecha de vencimiento (a\u00f1o): ");
    scanf("%d", &task->dueDate.year);

    printf("\n\u00a1La tarea en el \u00edndice %d fue modificada con \u00e9xito!\n", index + 1);
}

void deleteTask(TData* data, int index) {
    if (isEmpty(data)) {
        printf("\nLa lista est\u00e1 vac\u00eda.\n");
        return;
    }

    if (index < 1 || index > data->elements) {
        printf("\n\u00cdndice fuera de rango.\n");
        return;
    }

    index--;
    printf("\n\u00bfEst\u00e1s seguro que quer\u00e9s borrar la tarea '%s'? (s/n): ", data->tasks[index].description);
    char confirm;
    scanf(" %c", &confirm);
    if (confirm != 's' && confirm != 'S') {
        printf("\nEliminaci\u00f3n cancelada.\n");
        return;
    }

    for (int i = index; i < data->elements - 1; i++) {
        data->tasks[i] = data->tasks[i + 1];
    }
    data->elements--;

    printf("\n\u00a1La tarea fue eliminada con \u00e9xito!\n");
}

void showTasks(TData* data) {
    if (isEmpty(data)) {
        printf("\nLa lista est\u00e1 vac\u00eda.\n");
        return;
    }

    printf("\nTareas:\n");
    for (int i = 0; i < data->elements; i++) {
        TTask task = data->tasks[i];
        printf("\n[%d]\n", i + 1);
        printf("Descripci\u00f3n: %s\n", task.description);
        printf("Manager responsable: %s\n", task.dutyManager);
        printf("Prioridad: %s\n", task.priority ? "Alta" : "Baja");
        printf("Fecha de creaci\u00f3n: %d/%d/%d\n", task.creationDate.day, task.creationDate.month, task.creationDate.year);
        printf("Fecha de vencimiento: %d/%d/%d\n", task.dueDate.day, task.dueDate.month, task.dueDate.year);
    }
}

void urgentTasks(TData* data) {
    if (isEmpty(data)) {
        printf("\nLa lista est\u00e1 vac\u00eda.\n");
        return;
    }

    printf("\nTareas urgentes:\n");
    bool found = false;
    for (int i = 0; i < data->elements; i++) {
        if (data->tasks[i].priority == 1) {
            TTask task = data->tasks[i];
            printf("\n%s[%d]%s\n", RED, i + 1, RESET);
            printf("Descripci\u00f3n: %s\n", task.description);
            printf("Manager responsable: %s\n", task.dutyManager);
            printf("Prioridad: Alta\n");
            printf("Fecha de creaci\u00f3n: %d/%d/%d\n", task.creationDate.day, task.creationDate.month, task.creationDate.year);
            printf("Fecha de vencimiento: %d/%d/%d\n", task.dueDate.day, task.dueDate.month, task.dueDate.year);
            found = true;
        }
    }

    if (!found) {
        printf("No hay tareas urgentes.\n");
    }
}

void managerTasks(TData* data) {
    if (isEmpty(data)) {
        printf("\nLa lista est\u00e1 vac\u00eda.\n");
        return;
    }

    char managerName[LMAX];
    printf("Ingrese el nombre del manager: ");
    scanf(" %99[^\n]", managerName);

    printf("\nTareas para el manager %s:\n", managerName);
    bool found = false;
    for (int i = 0; i < data->elements; i++) {
        if (strcmp(data->tasks[i].dutyManager, managerName) == 0) {
            TTask task = data->tasks[i];
            printf("\n[%d]\n", i + 1);
            printf("Descripci\u00f3n: %s\n", task.description);
            printf("Manager responsable: %s\n", task.dutyManager);
            printf("Prioridad: %s\n", task.priority ? "Alta" : "Baja");
            printf("Fecha de creaci\u00f3n: %d/%d/%d\n", task.creationDate.day, task.creationDate.month, task.creationDate.year);
            printf("Fecha de vencimiento: %d/%d/%d\n", task.dueDate.day, task.dueDate.month, task.dueDate.year);
            found = true;
        }
    }

    if (!found) {
        printf("No hay tareas para el manager %s.\n", managerName);
    }
}

void saveTasksToFile(TData* data, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("\nError al abrir el archivo.\n");
        return;
    }
    for (int i = 0; i < data->elements; i++) {
        TTask t = data->tasks[i];
        fprintf(file, "%s\n%s\n%d\n%d %d %d\n%d %d %d\n",
                t.description, t.dutyManager, t.priority,
                t.creationDate.day, t.creationDate.month, t.creationDate.year,
                t.dueDate.day, t.dueDate.month, t.dueDate.year);
    }
    fclose(file);
    printf("\n\u00a1Tareas guardadas con \u00e9xito!\n");
}

void loadTasksFromFile(TData* data, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("\nArchivo no encontrado.\n");
        return;
    }
    data->elements = 0;
    while (!feof(file) && data->elements < NMAX) {
        TTask* t = &data->tasks[data->elements];
        if (fgets(t->description, LMAX, file) == NULL) break;
        t->description[strcspn(t->description, "\n")] = 0;
        fgets(t->dutyManager, LMAX, file);
        t->dutyManager[strcspn(t->dutyManager, "\n")] = 0;
        fscanf(file, "%d", &t->priority);
        fscanf(file, "%d %d %d", &t->creationDate.day, &t->creationDate.month, &t->creationDate.year);
        fscanf(file, "%d %d %d", &t->dueDate.day, &t->dueDate.month, &t->dueDate.year);
        fgetc(file); // Skip newline
        data->elements++;
    }
    fclose(file);
    printf("\n\u00a1Tareas cargadas desde archivo!\n");
}

int compareDueDates(const void* a, const void* b) {
    const TTask* t1 = (const TTask*)a;
    const TTask* t2 = (const TTask*)b;

    if (t1->dueDate.year != t2->dueDate.year)
        return t1->dueDate.year - t2->dueDate.year;
    if (t1->dueDate.month != t2->dueDate.month)
        return t1->dueDate.month - t2->dueDate.month;
    return t1->dueDate.day - t2->dueDate.day;
}

void showTasksSortedByDueDate(TData* data) {
    if (isEmpty(data)) {
        printf("\nLa lista est\u00e1 vac\u00eda.\n");
        return;
    }

    TTask sorted[NMAX];
    memcpy(sorted, data->tasks, sizeof(TTask) * data->elements);
    qsort(sorted, data->elements, sizeof(TTask), compareDueDates);

    printf("\nTareas ordenadas por fecha de vencimiento:\n");
    for (int i = 0; i < data->elements; i++) {
        TTask t = sorted[i];
        printf("\n[%d]\n", i + 1);
        printf("Descripci\u00f3n: %s\n", t.description);
        printf("Manager: %s\n", t.dutyManager);
        printf("Prioridad: %s\n", t.priority ? "Alta" : "Baja");
        printf("Creaci\u00f3n: %d/%d/%d\n", t.creationDate.day, t.creationDate.month, t.creationDate.year);
        printf("Vencimiento: %d/%d/%d\n", t.dueDate.day, t.dueDate.month, t.dueDate.year);
    }
}
