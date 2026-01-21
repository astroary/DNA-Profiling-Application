# 🧬 DNA Profiling Application

A command-line tool developed to identify individuals based on genetic markers known as Short Tandem Repeats (STRs). The application automates the process of matching raw DNA strands against a provided database by calculating the longest consecutive sequences of specific STR sequences.

## 📋 Project Overview
Forensic DNA profiling utilizes portions of the genome with high genetic diversity. This application processes various STR sequences (such as AGAT, AATG, or TATC) and compares the counts against a loaded database to determine a match. If the counts for multiple STRs align with a database entry, a positive identification is made.



## 🛠️ Features & Functionality
The application is built around a command-driven menu system:
* **Database Management**: Loads individual profiles and their corresponding STR repeat counts from text files.
* **DNA Processing**: Loads raw DNA sequences and automatically calculates the longest consecutive repeat counts for every STR listed in the database.
* **Search Algorithm**: Efficiently searches the loaded database for a match based on processed STR counts.
* **Data Integrity**: Uses a custom `ourvector` class to store all sequence data nucleotide-by-nucleotide, ensuring memory efficiency and strict container control.

## ⚙️ Technical Constraints & Implementation
* **Language**: C++11.
* **Memory Management**: Zero heap memory allocation (no pointers, `new`, or `delete` keywords).
* **Modular Design**: Heavily decomposed into functions, maintaining low cyclomatic complexity for high code clarity.
* **File I/O**: Each input file is opened and read exactly once to optimize performance.

---
**Course:** CS 251: Data Structures, Spring 2022, Prof Pat Troy
**Developed By:** Aryansingh Chauhan (astroary)