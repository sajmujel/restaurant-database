# Restaurant Database (C)

A console application for managing a database of restaurants, written in C. Restaurants are stored in memory as a **singly linked list** and persisted to a plain text file.

## Features

- **Management** – add, edit, delete and view restaurants (name, address)
- **Ratings** – rate a restaurant (1–5) and leave a comment, browse existing ratings
- **Search** – search restaurants by rating or alphabetically
- **Persistence** – data is loaded from `database.txt` on start and saved on changes

## What I practised

- Dynamic memory management (`malloc` / `free`, handling failed allocation)
- Linked list implementation (insert, delete, traversal, sorting)
- File I/O (`fopen`, read / append / overwrite modes)
- Input validation and splitting code into modules (`restaurant`, `ratings`, `utils`)

## Project structure

```
main/
├── main.cpp            # menus and program loop
├── CMakeLists.txt
└── files/
    ├── restaurant.*    # linked list, CRUD operations, file handling
    ├── ratings.*       # rating logic
    ├── utils.*         # console helpers
    └── constants.h     # limits and shared strings
```

## Build and run

Requires CMake 3.8+ and a C++ compiler (tested with MSVC).

```bash
cd main
cmake -B build
cmake --build build
./build/main        # on Windows: build\Debug\main.exe
```

> **Note:** the UI uses `conio.h` and `Windows.h`, so the program currently runs on **Windows only**. Making it portable is a possible future improvement.

## Author

Samuel Bachratý – first-year Information Security student at BUT Brno (FEKT).
