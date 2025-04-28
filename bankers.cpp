#include <iostream>
#include <vector>
#include <fstream>

class BankersAlgorithm {
private:
    int num_processes;  
    int num_resources;  
    std::vector<std::vector<int>> allocation;  
    std::vector<std::vector<int>> maximum;     
    std::vector<std::vector<int>> need;        
    std::vector<int> available;                

public:
    // Constructor that reads input and calculates need matrix
    BankersAlgorithm(const std::string& filename) {
        read_input(filename);
        calculate_need();
    }

    // Reads input data from file
    void read_input(const std::string& filename) {
        std::ifstream input_file(filename);
        if (!input_file.is_open()) {
            std::cerr << "Error: Cannot open file " << filename << std::endl;
            exit(1);
        }

        // Read number of processes and resources
        input_file >> num_processes >> num_resources;

        allocation.resize(num_processes, std::vector<int>(num_resources));
        maximum.resize(num_processes, std::vector<int>(num_resources));
        available.resize(num_resources);

        // Read allocation matrix
        for (int i = 0; i < num_processes; ++i) {
            for (int j = 0; j < num_resources; ++j) {
                input_file >> allocation[i][j];
            }
        }

        // Read maximum matrix
        for (int i = 0; i < num_processes; ++i) {
            for (int j = 0; j < num_resources; ++j) {
                input_file >> maximum[i][j];
            }
        }

        // Read available resources
        for (int j = 0; j < num_resources; ++j) {
            input_file >> available[j];
        }

        input_file.close();
    }

    // Calculates the need matrix (maximum - allocation)
    void calculate_need() {
        need.resize(num_processes, std::vector<int>(num_resources));
        for (int i = 0; i < num_processes; ++i) {
            for (int j = 0; j < num_resources; ++j) {
                need[i][j] = maximum[i][j] - allocation[i][j];
            }
        }
    }

    // Checks if the system is in a safe state
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
};

int main() {
    BankersAlgorithm banker("input.txt");
    banker.is_safe();
    return 0;
}