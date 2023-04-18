# Tasks program
This C program was designed to manage tasks, whether is in a big company, a startup, or even a house! It can perform this actions:
- _Cargar tarea_ (Register task): This option adds a new task on the list
- _Modificar tarea_ (Modify task): It will allow you to modify certain fields of a task
- _Completar una tarea_ (Complete a task): This function will mark a task as done and delete it from the list
- _Listar tareas_ (Show tasks): As the name suggests, it will show all the tasks in the list
- _Tareas urgentes_ (Urgent tasks): It will show all the tasks that were registered as urgent
- _Tareas de empleado_ (Employee tasks): Given a name, it will show all the tasks to be done by the employee
- _Guardar y salir_ (Save and exit): This option will save all the tasks in a binary file and exit the program

To give this program a try on Linux:
- Install gcc with this command:
  ```
  sudo apt update
  sudo apt install build-essential
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
  
  ---
  
  # Programa de manejo de tareas
  Este programa C fue diseñado para manejar tareas, ya sea en una gran empresa, un emprendimiento o incluso en un hogar! Puede realizar estas acciones:
  - _Cargar tarea_: Esta opcion añade una nueva tarea a la lista
  - _Modificar tarea_: Te permitira modificar ciertos campos de una tarea 
  - _Completar una tarea_: Esta funcion marcara una tarea como completada y la borrara de la lista
  -_Listar tareas_: Como el nombre sugiere, mostrara todas las tareas en la lista
  - _Tareas urgentes_: Mostrara las tareas que fueron registradas como urgentes
  - _Tareas de empleado_: Dado un nombre, mostrara todas las tareas a hacer por un empleado
  - _Guardar y salir_: Esta opcion guardara las tareas en un archivo binario y saldra del programa
  
  Para probar este programa en Linux:
- Instala gcc con este comando:
  ```
  sudo apt update
  sudo apt install build-essential
  ```
- Verifica la version del compilador de C para corroorar su instalacion:
  ```
  gcc --version
  ```
- Compila el programa:
  ```
  gcc -o expenses expenses.c
  ```
- Corre el programa:
  ```
  ./expenses
  ```
