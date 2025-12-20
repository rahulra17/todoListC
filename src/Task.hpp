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
            std::cout << "Initializing Task: " << description << std::endl;
            this->id = id;
            this->description = description;
            completed = false;
        }

        Task(int id, std::string description, bool completed) {
            std::cout << "Initializing Task: " << description << std::endl;
            this->id = id;
            this->description = description;
            this->completed = completed;
        }

        void complete();

        void formatListRow(int biggestNum, int longestStringLength);

        friend std::ostream& operator<<(std::ostream& os, const Task& t);
};

