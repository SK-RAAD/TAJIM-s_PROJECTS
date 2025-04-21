# Simple Task Manager

A lightweight, console‑based Task Manager written in C.  
Allows you to add, view, update, delete, search and sort tasks by due date, with persistent storage in a binary file.

---

## 📂 Repository Structure


---

## 📝 Description

The **Simple Task Manager** helps you organize your to‑do items in a terminal window. Each task stores:
- **ID** (auto‑incremented integer)
- **Name** (string)
- **Description** (string)
- **Category** (string)
- **Due Date** (`YYYY-MM-DD`)
- **Priority** (integer; lower = higher priority)
- **Completed** status (pending/done)

All changes are saved to `tasks.bin`, so your tasks persist between runs.

---

## ⚙️ Requirements

- A C compiler (e.g. `gcc`) or the provided `task_manager.exe` on Windows
- Terminal / Command Prompt
- *(Optional)* `make` if you prefer using a Makefile

---

## 🚀 Usage

### Running the Executable

1. **Windows**  
   Double‑click `task_manager.exe` or run in Command Prompt:
   ```bat
   task_manager.exe
2.**Linux / macOS**
gcc task_manager.c -o task_manager

./task_manager

**Basic Workflow**
1.Add Task
Enter name, description, category, due date, priority.

2.Display Tasks
Lists all tasks in a formatted table.

3.Update Task
Select by ID and modify fields.

4.Delete Task
Remove by ID.

5.Search Tasks
Find tasks by keyword in name or category.

6.Sort by Due Date
Orders tasks chronologically and saves.

7.Exit
Saves any unsaved changes and quits.

**Notes**
If tasks.bin does not exist, it will be created automatically on the first save.
The .bin file is in binary format; do not edit it by hand.
Maximum of 100 tasks can be stored (fixed array size).

**Features**
Persistent Storage via binary file
Modular Design with separate functions for each operation
Clean Console UI with color highlighting
Easy to Extend: swap bubble sort for qsort(), add case‑insensitive search, GUI, etc.

**Contributing**
Feel free to fork this repo, make improvements
(dynamic arrays, file‑format export, reminders), and submit a pull request!
