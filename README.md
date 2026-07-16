# Library Management System (C++)

A console-based Library Management System built in modern C++ (C++17), designed
with clean object-oriented architecture, file-based persistence, and a
menu-driven interface. Built as a portfolio project to demonstrate core
software engineering skills: OOP design, STL usage, file I/O, and modular
project structure.

## Live Demo

Demo of adding a book, registering a member, issuing and returning a book
demo/session_demo.svg


## Features

- **Book management** — add, remove, list, and search books (by title,
  author, or ISBN)
- **Member management** — register, remove, and list library members
- **Circulation system** — issue and return books with automatic due-date
  tracking (14-day loan period)
- **Fine calculation** — automatic overdue fine computation (₹5/day) on return
- **Overdue report** — view all currently overdue loans across the library
- **Member loan history** — view a member's active borrowed books
- **Persistent storage** — all data is saved to plain-text files (`data/`)
  and reloaded automatically on the next run, so nothing is lost between
  sessions
- **Safety checks** — prevents removing a book that's currently on loan,
  removing a member with outstanding books, double-borrowing, or issuing an
  unavailable book

## Project Structure

```
LibraryManagementSystem/
├── include/            # Header files (class declarations)
│   ├── Book.h
│   ├── Member.h
│   ├── Transaction.h
│   └── Library.h
├── src/                # Implementation files
│   ├── Book.cpp
│   ├── Member.cpp
│   ├── Transaction.cpp
│   ├── Library.cpp
│   └── main.cpp        # CLI entry point
├── data/                # Persisted data (auto-generated, gitignored)
├── Makefile
└── README.md
```

## Design Overview

- **`Book`** — represents a title with total/available copy counts.
- **`Member`** — represents a library member and the list of book IDs they
  currently have on loan.
- **`Transaction`** — represents a single issue/return event, including
  issue day, due day, return day, and any fine charged.
- **`Library`** — the core engine that owns all `Book`, `Member`, and
  `Transaction` collections, enforces business rules (availability checks,
  duplicate-loan prevention, fine calculation), and handles loading/saving
  to disk.

Each entity knows how to `serialize()`/`deserialize()` itself to a simple
pipe-delimited text format, keeping persistence logic self-contained and
easy to extend (e.g., swapping in SQLite later without touching business
logic in `Library`).

## Building & Running

Requires a C++17-compatible compiler (e.g., g++ 9+).

```bash
make          # builds the `library_system` executable
./library_system

# or in one step:
make run

# to clean build artifacts:
make clean
```

## Example Session

```
===== Library Management System =====
 1. Add Book
 2. Remove Book
 3. List All Books
 4. Search Books
 5. Register Member
 6. Remove Member
 7. List All Members
 8. Issue Book
 9. Return Book
10. View Member's Active Loans
11. Overdue Report
 0. Exit
=======================================
Select an option: 1
Title: Clean Code
Author: Robert Martin
ISBN: 978-0132350884
Number of copies: 2
Book added with ID 1.
```

## Possible Extensions

- Swap flat-file storage for SQLite (schema maps cleanly onto the existing
  `Book`/`Member`/`Transaction` classes)
- Add an admin/user role split with authentication
- Wrap the `Library` engine in a REST API (e.g., using Crow or Pistache) to
  turn this into a full-stack project
- Add unit tests (e.g., with Catch2) for `Library`'s business rules

## Author's Note

This project was built to practice core software-engineering fundamentals —
OOP class design, separation of concerns (data model vs. business logic vs.
UI), file-based persistence, and STL containers/algorithms — outside of an
AI/ML context.
