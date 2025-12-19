#include "Task.hpp"

#include <string>
#include <vector>
#include <iostream>

std::ostream& operator<<(std::ostream& os, const Task& t) {
    return os << t.id << "|" << static_cast<int>(t.completed) << "|" << t.description;
}