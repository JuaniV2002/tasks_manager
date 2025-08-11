// Enhanced Task Manager with basic improvements (English UI)
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

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
    TDate currentDate;
    bool dirty;
} TData;

bool isEmpty(TData* data);
bool isFull(TData* data);
void addTask(TData* data);
void updateTask(TData* data, int index);
void deleteTask(TData* data, int index);
void showTasks(TData* data);
void showUrgentTasks(TData* data);
void showTasksByManager(TData* data);
void saveTasksToFile(TData* data, const char* filename);
void loadTasksFromFile(TData* data, const char* filename);
int compareDueDates(const void* a, const void* b);
void showTasksSortedByDueDate(TData* data);
void searchTasks(TData* data);

// Helpers
bool parseDate(const char* input, TDate* out);
int daysUntil(TDate from, TDate to);
void printDueInfo(TDate today, TDate due);
void trimNewline(char* s);
void toLowerStr(char* s);
// CSV helpers
void csv_write_field(FILE* f, const char* s);
bool csv_parse_line(const char* line, TTask* out);

int main() {
    TData data = { .elements = 0, .dirty = false };
    int option, index;

    char dateStr[LMAX];
    printf("\nEnter today's date (DD/MM/YYYY): ");
    scanf(" %99[^\n]", dateStr);
    if (!parseDate(dateStr, &data.currentDate)) {
        printf("Invalid date format. Expected DD/MM/YYYY. Exiting.\n");
        return 1;
    }

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
        printf("Search tasks (10)\n");
        printf("Exit (11)\n");
    printf("-----------------------------------\n");
    printf("Choose an option: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                addTask(&data);
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
                saveTasksToFile(&data, "tasks.csv");
                break;
            case 8:
                loadTasksFromFile(&data, "tasks.csv");
                break;
            case 9:
                showTasksSortedByDueDate(&data);
                break;
            case 10:
                searchTasks(&data);
                break;
            case 11:
                if (data.dirty) {
                    printf("\nYou have unsaved changes. Save to tasks.csv before exiting? (y/n): ");
                    char c; scanf(" %c", &c);
                    if (c == 'y' || c == 'Y') {
                        saveTasksToFile(&data, "tasks.csv");
                    }
                }
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

void addTask(TData* data) {
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
    char dateStr[LMAX];
    printf("Due date (DD/MM/YYYY): ");
    scanf(" %99[^\n]", dateStr);
    if (!parseDate(dateStr, &new_task.dueDate)) {
        printf("Invalid date format. Task not added.\n");
        return;
    }

    new_task.creationDate = data->currentDate;

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
    data->dirty = true;
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
    char dateStr[LMAX];
    printf("New due date (DD/MM/YYYY): ");
    scanf(" %99[^\n]", dateStr);
    if (!parseDate(dateStr, &task->dueDate)) {
        printf("Invalid date format. Keeping previous due date.\n");
    }

    data->dirty = true;
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
    data->dirty = true;
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
    printf("Due date: %d/%d/%d ", task.dueDate.day, task.dueDate.month, task.dueDate.year);
    printDueInfo(data->currentDate, task.dueDate);
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
            printf("Due date: %d/%d/%d ", task.dueDate.day, task.dueDate.month, task.dueDate.year);
            printDueInfo(data->currentDate, task.dueDate);
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
        // CSV: "description","manager",priority,cd,cm,cy,dd,dm,dy
        csv_write_field(file, t.description); fputc(',', file);
        csv_write_field(file, t.manager);    fputc(',', file);
        fprintf(file, "%d,%d,%d,%d,%d,%d,%d\n",
                t.priority,
                t.creationDate.day, t.creationDate.month, t.creationDate.year,
                t.dueDate.day, t.dueDate.month, t.dueDate.year);
    }
    fclose(file);
    data->dirty = false;
    printf("\nTasks saved successfully!\n");
}

void loadTasksFromFile(TData* data, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("\nFile not found.\n");
        return;
    }
    data->elements = 0;
    char line[LMAX * 3];
    while (fgets(line, sizeof(line), file) && data->elements < NMAX) {
        trimNewline(line);
        if (line[0] == '\0') continue;
        TTask t;
        if (!csv_parse_line(line, &t)) {
            printf("Skipping malformed line: %s\n", line);
            continue;
        }
        data->tasks[data->elements++] = t;
    }
    fclose(file);
    data->dirty = false;
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
        printf("Due: %d/%d/%d ", t.dueDate.day, t.dueDate.month, t.dueDate.year);
        printDueInfo(data->currentDate, t.dueDate);
    }
}

void searchTasks(TData* data) {
    if (isEmpty(data)) {
        printf("\nThe list is empty.\n");
        return;
    }
    char query[LMAX];
    printf("Enter text to search (in description or manager): ");
    scanf(" %99[^\n]", query);
    char qLower[LMAX];
    strncpy(qLower, query, LMAX);
    qLower[LMAX-1] = '\0';
    toLowerStr(qLower);
    bool found = false;
    for (int i = 0; i < data->elements; i++) {
        char d[LMAX], m[LMAX];
        strncpy(d, data->tasks[i].description, LMAX); d[LMAX-1]='\0';
        strncpy(m, data->tasks[i].manager, LMAX);     m[LMAX-1]='\0';
        toLowerStr(d); toLowerStr(m);
        if (strstr(d, qLower) || strstr(m, qLower)) {
            TTask t = data->tasks[i];
            printf("\n[%d]\n", i + 1);
            printf("Description: %s\n", t.description);
            printf("Manager: %s\n", t.manager);
            printf("Priority: %s\n", t.priority ? "High" : "Low");
            printf("Creation: %d/%d/%d\n", t.creationDate.day, t.creationDate.month, t.creationDate.year);
            printf("Due: %d/%d/%d ", t.dueDate.day, t.dueDate.month, t.dueDate.year);
            printDueInfo(data->currentDate, t.dueDate);
            found = true;
        }
    }
    if (!found) {
        printf("No tasks matched your search.\n");
    }
}

// ===== Helpers =====
bool parseDate(const char* input, TDate* out) {
    int d, m, y;
    if (sscanf(input, "%d/%d/%d", &d, &m, &y) != 3) return false;
    if (d < 1 || d > 31 || m < 1 || m > 12 || y < 1) return false;
    out->day = d; out->month = m; out->year = y;
    return true;
}

static time_t to_time(TDate dt) {
    struct tm t = {0};
    t.tm_mday = dt.day;
    t.tm_mon = dt.month - 1;
    t.tm_year = dt.year - 1900;
    t.tm_isdst = -1;
    return mktime(&t);
}

int daysUntil(TDate from, TDate to) {
    time_t a = to_time(from);
    time_t b = to_time(to);
    double diff = difftime(b, a) / (60*60*24);
    if (diff > 0) return (int)(diff + 0.5);
    if (diff < 0) return (int)(diff - 0.5);
    return 0;
}

void printDueInfo(TDate today, TDate due) {
    int d = daysUntil(today, due);
    if (d > 0) {
        printf("(%d day%s remaining)\n", d, d==1?"":"s");
    } else if (d == 0) {
        printf("(%sDue today%s)\n", GREEN, RESET);
    } else {
        int overdue = -d;
        printf("(%sOVERDUE by %d day%s%s)\n", RED, overdue, overdue==1?"":"s", RESET);
    }
}

void trimNewline(char* s) {
    s[strcspn(s, "\r\n")] = 0;
}

void toLowerStr(char* s) {
    for (; *s; ++s) *s = (char)tolower((unsigned char)*s);
}

void csv_write_field(FILE* f, const char* s) {
    fputc('"', f);
    for (const char* p = s; *p; ++p) {
        if (*p == '"') fputc('"', f); // escape quotes by doubling
        fputc(*p, f);
    }
    fputc('"', f);
}

static bool csv_read_quoted(const char* line, int* idx, char* out, size_t outsz) {
    if (line[*idx] != '"') return false;
    (*idx)++; size_t k = 0;
    while (line[*idx] && k + 1 < outsz) {
        char c = line[*idx];
        (*idx)++;
        if (c == '"') {
            if (line[*idx] == '"') { // escaped quote
                out[k++] = '"';
                (*idx)++;
                continue;
            }
            // end quote
            out[k] = '\0';
            if (line[*idx] == ',') (*idx)++; // consume comma
            return true;
        }
        out[k++] = c;
    }
    out[k] = '\0';
    return false;
}

bool csv_parse_line(const char* line, TTask* out) {
    int i = 0;
    // Skip leading spaces
    while (line[i] == ' ') i++;
    if (!csv_read_quoted(line, &i, out->description, LMAX)) return false;
    if (!csv_read_quoted(line, &i, out->manager, LMAX)) return false;
    // Now parse the remaining 7 integers
    int pr, cd, cm, cy, dd, dm, dy;
    if (sscanf(&line[i], "%d,%d,%d,%d,%d,%d,%d", &pr, &cd, &cm, &cy, &dd, &dm, &dy) != 7) return false;
    out->priority = pr;
    out->creationDate.day = cd; out->creationDate.month = cm; out->creationDate.year = cy;
    out->dueDate.day = dd; out->dueDate.month = dm; out->dueDate.year = dy;
    return true;
}
