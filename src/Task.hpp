#pragma once // Modern include guard

#include <string>
#include <vector>
#include <iostream>

struct Task {
    private: 
        int id;
        std::string description;
        bool completed;

    public:
        Task(int id, std::string description) {
            std::cout << "Initializing Task" << std::endl;
            this->id = id;
            this->description = description;
            completed = false;
        }

        Task(int id, std::string description, bool completed) {
            std::cout << "Initializing Task" << std::endl;
            this->id = id;
            this->description = description;
            this->completed = completed;
        }

        friend std::ostream& operator<<(std::ostream& os, const Task& t);
};

