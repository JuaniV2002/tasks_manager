# Tasks program
This C program was designed to manage tasks, whether is in a big company, a startup, or even a house! It can perform this actions:
- _Cargar tarea_ (Register task): this option adds a new task.
- _Modificar tarea_ (Modify task): it will allow you to modify certain fields of a task.
- _Completar una tarea_ (Complete a task): this function will mark a task as done and delete it.
- _Listar tareas_ (Show tasks): as the name suggests, it will show all the tasks in the list.
- _Tareas urgentes_ (Urgent tasks): it will show all the tasks that were registered as urgent.
- _Tareas de empleado_ (Employee tasks): given a name, it will show all the tasks assigned to that employee.
- _Guardar tareas en archivo_ (Save tasks on file): this option will save all the tasks in a file.

To give this program a try on Linux:
- Install gcc with this command:
  ```
  sudo apt update
  sudo apt install build-essential
  ```
  or if you are on mac using homebrew:
  ```
  brew update
  brew install gcc
  ```
- Check C compiler version to verify a successful installation:
  ```
  gcc --version
  ```
- Compile the program:
  ```
  gcc -o expenses expenses.c
  ```
- Run the program:
  ```
  ./expenses
  ```
