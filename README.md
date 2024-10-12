# Multi-Threaded Task Scheduler in C++

## Overview
This project implements a multi-threaded task scheduler using modern C++ concurrency features. The scheduler allows you to schedule tasks to run after a specified delay and executes them using a thread pool.

### Features:
- Schedule tasks to run after a specific delay.
- Tasks are executed in parallel using a thread pool.
- Dynamically add, cancel, or reschedule tasks.
- Gracefully stops execution when required.

## Requirements
- C++11 or higher
- POSIX Threads (for Linux/Mac)
- On Windows, use Visual Studio or MinGW with threading support.

## How to Build

To build the project, you can use a simple Makefile or compile it manually with the following command:

```bash
g++ -std=c++11 -pthread main.cpp scheduler.cpp -o scheduler
