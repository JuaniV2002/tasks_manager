# Tasks Program

This C program was designed to manage tasks—whether it's for a big company, a startup, or even your household! It provides a simple, terminal-based interface for task management with priority sorting and file persistence.

## Features

- **_Cargar tarea_ (Register task):** Add a new task with description, priority, due date, and manager.
- **_Modificar tarea_ (Modify task):** Modify the fields of a given task.
- **_Completar una tarea_ (Complete a task):** Mark a task as done and delete it from the list (with confirmation).
- **_Listar tareas_ (Show tasks):** Display all tasks in the list with their full details and index numbers.
- **_Tareas urgentes_ (Urgent tasks):** List only the high-priority tasks, highlighted in red.
- **_Tareas de empleado_ (Employee tasks):** Filter tasks assigned to a specific employee or manager.
- **_Guardar tareas en archivo_ (Save tasks on file):** Save all current tasks to a `.txt` file in plain text format.
- **_Cargar tareas desde archivo_ (Load tasks from file):** Load tasks from a previously saved file.
- **_Mostrar tareas ordenadas por vencimiento_ (Show tasks sorted by due date):** View tasks sorted chronologically based on their due date.
- **Confirmation before deletion:** Prevent accidental removal of tasks by asking the user to confirm.
- **Colored output:** Urgent tasks are printed in red to visually stand out.

## Getting Started

To give this program a try on **Linux**:

```bash
sudo apt update
sudo apt install build-essential
```
or if you are on mac using homebrew:
  
```bash
brew update
brew install gcc
```
Verify the compiler is available:
  
```bash
gcc --version
```

## Compile the program:
  
```bash
gcc -o tasks tasks.c
```

## Run the program:
  
```bash
./tasks
```