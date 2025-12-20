#pragma once

#include "Task.hpp"
#include <vector>
#include <iostream>
#include <map>
#include <filesystem>
#include <fstream>

class TaskManager{
    private:
        std::map<int, Task> task_list;
        std::filesystem::path data;
        int nextId;
        int longestString;
        void updateFile(std::filesystem::path file_path);

    public:
        TaskManager(std::filesystem::path data);

        void add(std::string description, std::filesystem::path file_path);

        void list();

        void complete(int id, std::filesystem::path file_path);

        void remove(int id, std::filesystem::path file_path);
};

