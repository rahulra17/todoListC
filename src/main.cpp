#include <iostream>
#include <filesystem>
#include "TaskManager.hpp"
#include "Task.hpp"

int main(int argc, char* argv[]) {
    std::cout << "Project initialized." << std::endl;
    std::filesystem::path file_path = "/Users/rahulramineni/CSProjects/C++Practice/cpp-todo/test.txt";
    std::cout << "Initializing TaskManager." << std::endl;
    TaskManager t(file_path);
    if(argc > 1){
        std::string arg = std::string(argv[1]);
        if(arg == "add"){
            if(argv[2]) {
                t.add(argv[2], file_path);
            } else {
                std::cerr << "Error: No Task Description Found" << std::endl;
                return -1;
            }
        }
        else if(arg == "remove"){
            if(arg[2]) {
                t.remove(std::stoi(argv[2]), file_path);
            } else {
                std::cerr << "Error: No Task ID found" << std::endl;
                return -1;
            }
        } 
        else if(arg == "list") {
            t.list();
        }
    }


    return 0;
}


