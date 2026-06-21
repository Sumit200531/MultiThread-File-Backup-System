# Multithreaded File Backup and Recovery System

A C++17-based file backup and recovery application that automates directory backups while preserving folder structure and maintaining audit logs.

## Features

* Recursive directory traversal
* Folder structure preservation
* Multithreaded file copying using `std::thread`
* Thread-safe logging using `std::mutex`
* Incremental backups using file modification timestamps
* Restore functionality
* Backup statistics using `std::atomic`
* Timestamped audit logging
* Menu-driven interface
* Configurable source directory

## Technologies Used

* C++17
* STL
* std::filesystem
* std::thread
* std::mutex
* std::atomic

## Project Structure

```text
src/
include/
config/
logs/
backups_current/
```

## Build

```bash
g++ src/main.cpp src/FileManager.cpp -Iinclude -pthread -o backup.exe
```

## Run

```bash
backup.exe
```
