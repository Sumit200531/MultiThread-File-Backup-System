## Overview

This project is a Multithreaded File Backup and Recovery System developed in C++17. It automates file backups, preserves folder structures, supports incremental backups based on file modification timestamps, and provides recovery functionality through a restore mechanism.

The system leverages modern C++ features such as std::filesystem, std::thread, std::mutex, and std::atomic to improve backup performance and reliability.




## Features

* [x] Recursive directory traversal
* [x] Folder structure preservation
* [x] Multithreaded file copying
* [x] Thread-safe logging using mutexes
* [x] Incremental backups using modification timestamps
* [x] Backup statistics using atomic counters
* [x] Restore functionality
* [x] Configurable source directory
* [x] Timestamped audit logs
* [x] Menu-driven interface


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
