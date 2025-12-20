#include "Task.hpp"

#include <string>
#include <vector>
#include <iostream>
#include <iomanip>


std::ostream& operator<<(std::ostream& os, const Task& t) {
    return os << t.id << "|" << static_cast<int>(t.completed) << "|" << t.description;
}

void Task::complete(){
    this->completed = true;
}

void Task::formatListRow(int biggestNum, int longestStringLength){
    std::string completeString = this->completed ? "[X]" : "[]";
    std::cout << std::right;
    std::cout << this->id << std::setw(biggestNum+ 4) << completeString << std::setw(longestStringLength + 8) << this->description << std::endl;
}