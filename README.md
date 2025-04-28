# Banker's Algorithm
**Name** Phuong Huyen Dao 

**Class** CS 33211 Operating system
## Overview
The Banker's Algorithm is used for deadlock avoidance problem. It checks whether a system is in a safe state by simulating resource allocation and determining if there exists at least one safe sequence of process execution.

Considering a system with five processes P0 through P4 and three resources of type A, B, C. Resource type A has 10 instances, B has 5 instances and type C has 7 instances. Suppose at time t0 following snapshot of the system has been taken:
<img width="715" alt="Question Assignment 2" src="https://github.com/user-attachments/assets/2e2921ca-0052-481a-b698-c5b4c7f2a573" />

Implement the Banker’s algorithm to answer the following question:
Is the system in a safe state? If Yes, then what is the safe sequence?

## Requirement
- Linux/Unix operating system
- Input file

## Compilation
```
g++ bankers.cpp -o bankers
./bankers
```

## Algorithm
- Calculate the remaining need matrix for safety check comparisons
```
void calculate_need() {
    need.resize(num_processes, std::vector<int>(num_resources));
    for (int i = 0; i < num_processes; ++i) {
        for (int j = 0; j < num_resources; ++j) {
            need[i][j] = maximum[i][j] - allocation[i][j];
        }
    }
}
```
- Safety check
```
   bool is_safe() {
        std::vector<bool> finished(num_processes, false);
        std::vector<int> work = available;
        std::vector<int> safe_sequence;

        int completed = 0;
        while (completed < num_processes) {
            bool found = false;

            // Try to find a process that can be executed
            for (int i = 0; i < num_processes; ++i) {
                if (!finished[i]) {
                    bool can_execute = true;

                    // Check if all resources needed are available
                    for (int j = 0; j < num_resources; ++j) {
                        if (need[i][j] > work[j]) {
                            can_execute = false;
                            break;
                        }
                    }

                    // If process can execute, release its resources
                    if (can_execute) {
                        for (int j = 0; j < num_resources; ++j) {
                            work[j] += allocation[i][j];
                        }

                        safe_sequence.push_back(i);
                        finished[i] = true;
                        found = true;
                        completed++;
                    }
                }
            }

            // If no process can execute, system is unsafe
            if (!found) {
                std::cout << "System is NOT in a safe state.\n";
                return false;
            }
        }

        // If all processes completed, system is safe
        std::cout << "System is in a safe state.\nSafe sequence: ";
        for (size_t i = 0; i < safe_sequence.size(); ++i) {
            std::cout << "P" << safe_sequence[i];
            if (i != safe_sequence.size() - 1) {
                std::cout << " -> ";
            }
        }
        std::cout << std::endl;
        return true;
    }
```
## Program output
![Program output](https://github.com/user-attachments/assets/d14aefde-e216-4d8d-adb3-0d55e28aaca3)
