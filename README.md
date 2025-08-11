# Tasks Program

A simple terminal-based task manager written in C. It supports priorities, filtering by manager, and saving/loading tasks from a text file.

## Features

- Add new task: description, manager, priority (High/Low), and due date.
- Update a task: edit any field by index.
- Delete a task: with confirmation prompt.
- Show tasks: list all tasks with details and indices.
- Urgent tasks: show only high-priority tasks (highlighted in red).
- Tasks by manager: filter tasks assigned to a specific manager.
- Save tasks to file: write tasks to a plain-text `.txt` file.
- Load tasks from file: read tasks from a previously saved file.
- Show tasks sorted by due date: chronological view by due date.

## Setup

On macOS (Homebrew):

```bash
brew update
brew install gcc
gcc --version
```

On Linux (Debian/Ubuntu):

```bash
sudo apt update
sudo apt install build-essential
gcc --version
```

## Build

```bash
gcc -o tasks tasks.c
```

## Run

```bash
./tasks
```