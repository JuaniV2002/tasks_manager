# Tasks Program

A simple terminal-based task manager written in C. It supports priorities, filtering by manager, and saving/loading tasks from a text file.

## Features

- Add new task: description, manager, priority (High/Low), and due date.
- Update a task: edit any field by index.
- Delete a task: with confirmation prompt.
- Show tasks: list all tasks with details and indices.
- Urgent tasks: show only high-priority tasks (highlighted in red).
- Tasks by manager: filter tasks assigned to a specific manager.
- Save tasks to file (CSV): write tasks to `tasks.csv` with proper quoting.
- Load tasks from file (CSV): read tasks from `tasks.csv`.
- Show tasks sorted by due date: chronological view by due date.
- Search tasks: find by text in description or manager.
- Overdue highlighting: shows days remaining, due today, or overdue by N days.
- Unsaved-changes prompt: offers to save before exiting if you made changes.

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

On start, you’ll be asked for today’s date using the format:

DD/MM/YYYY

When adding or updating a task, enter the due date in the same format.

### CSV format

The program saves to `tasks.csv` with one task per line in this schema:

"description","manager",priority,creation_day,creation_month,creation_year,due_day,due_month,due_year

Notes:
- Description and manager are quoted, with double quotes escaped by doubling (RFC 4180 style).
- Priority is 1 (High) or 0 (Low).
```