
# Philosophers

Welcome to the **Philosophers** project! This project is part of the [42 School](https://www.42.fr/) common core, where the objective is to solve the classic "Dining Philosophers" problem using multithreading and proper synchronization techniques.

## About

The **Dining Philosophers** problem illustrates synchronization issues and deadlock in concurrent programming. In this project, we simulate multiple philosophers sitting around a table, eating, thinking, and picking up forks to eat without causing deadlocks or race conditions.

The project uses multithreading and mutexes to ensure the proper functioning of the philosophers while avoiding issues like:
- Deadlock
- Race conditions
- Starvation

## Usage

```bash
./philosophers 5 800 200 200
```

Where:
- `number_of_philosophers`: Number of philosophers at the table
- `time_to_die`: Time in milliseconds before a philosopher dies if they don’t start eating
- `time_to_eat`: Time in milliseconds it takes for a philosopher to eat
- `time_to_sleep`: Time in milliseconds for a philosopher to sleep
- `number_of_times_each_philosopher_must_eat` (optional): Number of times each philosopher needs to eat. If not specified, the simulation continues indefinitely.

## Project Requirements

The project adheres to the following 42 School requirements:
- Avoiding deadlock and race conditions.
- Synchronizing philosopher actions using mutexes.
- Using threads to simulate concurrency.
- Proper error handling for invalid input and system errors.
