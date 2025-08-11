// Enhanced Task Manager with basic improvements (English UI)
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
    char manager[LMAX];
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
void addTask(TData* data, TDate* date);
void updateTask(TData* data, int index);
void deleteTask(TData* data, int index);
void showTasks(TData* data);
void showUrgentTasks(TData* data);
void showTasksByManager(TData* data);
void saveTasksToFile(TData* data, const char* filename);
void loadTasksFromFile(TData* data, const char* filename);
int compareDueDates(const void* a, const void* b);
void showTasksSortedByDueDate(TData* data);

int main() {
    TData data = { .elements = 0 };
    TDate date;
    int option, index;

    printf("\nEnter today's day: ");
    scanf("%d", &date.day);
    printf("Enter today's month: ");
    scanf("%d", &date.month);
    printf("Enter today's year: ");
    scanf("%d", &date.year);

    do {
    printf("\n-----------------------------------\n");
    printf("Add new task (1)\n");
    printf("Update a task (2)\n");
    printf("Delete a task (3)\n");
    printf("Show tasks (4)\n");
    printf("Urgent tasks (5)\n");
    printf("Tasks by manager (6)\n");
    printf("Save tasks to file (7)\n");
    printf("Load tasks from file (8)\n");
    printf("Show tasks sorted by due date (9)\n");
    printf("Exit (10)\n");
    printf("-----------------------------------\n");
    printf("Choose an option: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                addTask(&data, &date);
                break;
            case 2:
                printf("\nEnter the index of the task to update: ");
                scanf("%d", &index);
                updateTask(&data, index);
                break;
            case 3:
                printf("\nEnter the index of the task to delete: ");
                scanf("%d", &index);
                deleteTask(&data, index);
                break;
            case 4:
                showTasks(&data);
                break;
            case 5:
                showUrgentTasks(&data);
                break;
            case 6:
                showTasksByManager(&data);
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
                printf("\nInvalid option\n");
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

void addTask(TData* data, TDate* date) {
    if (isFull(data)) {
        printf("\nThe list is full.\n");
        return;
    }

    TTask new_task;
    printf("\nDescription for the new task: ");
    scanf(" %99[^\n]", new_task.description);
    printf("Manager responsible for the new task: ");
    scanf(" %99[^\n]", new_task.manager);
    printf("Priority (1 is high, 0 is low): ");
    scanf("%d", &new_task.priority);
    printf("Due date (day): ");
    scanf("%d", &new_task.dueDate.day);
    printf("Due date (month): ");
    scanf("%d", &new_task.dueDate.month);
    printf("Due date (year): ");
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
    printf("\nNew task added successfully!\n");
}

void updateTask(TData* data, int index) {
    if (isEmpty(data)) {
        printf("\nThe list is empty.\n");
        return;
    }

    if (index < 1 || index > data->elements) {
        printf("\nIndex out of range.\n");
        return;
    }

    index--;
    TTask* task = &data->tasks[index];
    printf("\nNew task description: ");
    scanf(" %99[^\n]", task->description);
    printf("New manager responsible for the task: ");
    scanf(" %99[^\n]", task->manager);
    printf("New priority (1 is high, 0 is low): ");
    scanf("%d", &task->priority);
    printf("New due date (day): ");
    scanf("%d", &task->dueDate.day);
    printf("New due date (month): ");
    scanf("%d", &task->dueDate.month);
    printf("New due date (year): ");
    scanf("%d", &task->dueDate.year);

    printf("\nThe task at index %d was updated successfully!\n", index + 1);
}

void deleteTask(TData* data, int index) {
    if (isEmpty(data)) {
        printf("\nThe list is empty.\n");
        return;
    }

    if (index < 1 || index > data->elements) {
        printf("\nIndex out of range.\n");
        return;
    }

    index--;
    printf("\nAre you sure you want to delete the task '%s'? (y/n): ", data->tasks[index].description);
    char confirm;
    scanf(" %c", &confirm);
    if (confirm != 'y' && confirm != 'Y') {
        printf("\nDeletion canceled.\n");
        return;
    }

    for (int i = index; i < data->elements - 1; i++) {
        data->tasks[i] = data->tasks[i + 1];
    }
    data->elements--;

    printf("\nThe task was deleted successfully!\n");
}

void showTasks(TData* data) {
    if (isEmpty(data)) {
        printf("\nThe list is empty.\n");
        return;
    }

    printf("\nTasks:\n");
    for (int i = 0; i < data->elements; i++) {
        TTask task = data->tasks[i];
        printf("\n[%d]\n", i + 1);
        printf("Description: %s\n", task.description);
        printf("Manager: %s\n", task.manager);
        printf("Priority: %s\n", task.priority ? "High" : "Low");
        printf("Creation date: %d/%d/%d\n", task.creationDate.day, task.creationDate.month, task.creationDate.year);
        printf("Due date: %d/%d/%d\n", task.dueDate.day, task.dueDate.month, task.dueDate.year);
    }
}

void showUrgentTasks(TData* data) {
    if (isEmpty(data)) {
        printf("\nThe list is empty.\n");
        return;
    }

    printf("\nUrgent tasks:\n");
    bool found = false;
    for (int i = 0; i < data->elements; i++) {
        if (data->tasks[i].priority == 1) {
            TTask task = data->tasks[i];
            printf("\n%s[%d]%s\n", RED, i + 1, RESET);
            printf("Description: %s\n", task.description);
            printf("Manager: %s\n", task.manager);
            printf("Priority: High\n");
            printf("Creation date: %d/%d/%d\n", task.creationDate.day, task.creationDate.month, task.creationDate.year);
            printf("Due date: %d/%d/%d\n", task.dueDate.day, task.dueDate.month, task.dueDate.year);
            found = true;
        }
    }

    if (!found) {
        printf("There are no urgent tasks.\n");
    }
}

void showTasksByManager(TData* data) {
    if (isEmpty(data)) {
        printf("\nThe list is empty.\n");
        return;
    }

    char managerName[LMAX];
    printf("Enter the manager's name: ");
    scanf(" %99[^\n]", managerName);

    printf("\nTasks for manager %s:\n", managerName);
    bool found = false;
    for (int i = 0; i < data->elements; i++) {
        if (strcmp(data->tasks[i].manager, managerName) == 0) {
            TTask task = data->tasks[i];
            printf("\n[%d]\n", i + 1);
            printf("Description: %s\n", task.description);
            printf("Manager: %s\n", task.manager);
            printf("Priority: %s\n", task.priority ? "High" : "Low");
            printf("Creation date: %d/%d/%d\n", task.creationDate.day, task.creationDate.month, task.creationDate.year);
            printf("Due date: %d/%d/%d\n", task.dueDate.day, task.dueDate.month, task.dueDate.year);
            found = true;
        }
    }

    if (!found) {
        printf("There are no tasks for manager %s.\n", managerName);
    }
}

void saveTasksToFile(TData* data, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("\nError opening file.\n");
        return;
    }
    for (int i = 0; i < data->elements; i++) {
        TTask t = data->tasks[i];
        fprintf(file, "%s\n%s\n%d\n%d %d %d\n%d %d %d\n",
                t.description, t.manager, t.priority,
                t.creationDate.day, t.creationDate.month, t.creationDate.year,
                t.dueDate.day, t.dueDate.month, t.dueDate.year);
    }
    fclose(file);
    printf("\nTasks saved successfully!\n");
}

void loadTasksFromFile(TData* data, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("\nFile not found.\n");
        return;
    }
    data->elements = 0;
    while (!feof(file) && data->elements < NMAX) {
        TTask* t = &data->tasks[data->elements];
        if (fgets(t->description, LMAX, file) == NULL) break;
        t->description[strcspn(t->description, "\n")] = 0;
        fgets(t->manager, LMAX, file);
        t->manager[strcspn(t->manager, "\n")] = 0;
        fscanf(file, "%d", &t->priority);
        fscanf(file, "%d %d %d", &t->creationDate.day, &t->creationDate.month, &t->creationDate.year);
        fscanf(file, "%d %d %d", &t->dueDate.day, &t->dueDate.month, &t->dueDate.year);
        fgetc(file); // Skip newline
        data->elements++;
    }
    fclose(file);
    printf("\nTasks loaded from file!\n");
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
        printf("\nThe list is empty.\n");
        return;
    }

    TTask sorted[NMAX];
    memcpy(sorted, data->tasks, sizeof(TTask) * data->elements);
    qsort(sorted, data->elements, sizeof(TTask), compareDueDates);

    printf("\nTasks sorted by due date:\n");
    for (int i = 0; i < data->elements; i++) {
        TTask t = sorted[i];
        printf("\n[%d]\n", i + 1);
        printf("Description: %s\n", t.description);
        printf("Manager: %s\n", t.manager);
        printf("Priority: %s\n", t.priority ? "High" : "Low");
        printf("Creation: %d/%d/%d\n", t.creationDate.day, t.creationDate.month, t.creationDate.year);
        printf("Due: %d/%d/%d\n", t.dueDate.day, t.dueDate.month, t.dueDate.year);
    }
}
