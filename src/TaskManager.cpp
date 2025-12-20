#include "Task.hpp"
#include "TaskManager.hpp"
#include <vector>
#include <iostream>
#include <map>
#include <filesystem>
#include <fstream>
#include <sstream>

std::vector<std::string> parseData(std::string dataLine) {
    std::vector<std::string> parsedData;
    dataLine += "|";
    std::string currString = "";
    for(char& c: dataLine) {
        if(c != '|'){
            currString += c;
        } else {
            parsedData.push_back(currString);
            currString = "";
        }
    }
    return parsedData;
}

TaskManager::TaskManager(std::filesystem::path data){
    this->data = data;
    this->nextId = 1;
    this->longestString = 0;
    // Load any data already in file into map
    std::ifstream inputFile(data);
    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open the file example.txt" << std::endl;
    }
    std::string currLine;
    // Loop through file and parse through data already there
    while(std::getline(inputFile, currLine)){
        std::vector<std::string> currData = parseData(currLine);

        // Separate Data Appropriately
        int currId = std::stoi(currData[0]);
        std::string currDescription = currData[2];
        bool currCompletion = static_cast<bool>(std::stoi(currData[1]));

        // Keep track of longest string length for list formatting
        if(currDescription.length() > this->longestString){
            this->longestString = currDescription.length();
        }
        // Create and insert task to map
        Task t(currId, currDescription, currCompletion);
        task_list.insert({currId, t});

        // Increment the next id for usage
        nextId = currId + 1;
    }

    inputFile.close();

    std::cout << "printing task list" << std::endl;
    for(const auto& pair : task_list) {
        std::cout << pair.first << " : " << pair.second << std::endl;
    }
}

void TaskManager::add(std::string description, std::filesystem::path file_path) {
    std::ofstream outFile(file_path, std::ios::app);
    Task t(nextId, description);
    // if the file is empty put on line 1, otherwise new line
    if(task_list.size() > 0) {
        std::cout << "I got here" << std::endl;
        outFile << '\n' << t; 
    } else {
        outFile << t;
    }
    task_list.insert({nextId, t});
    outFile.close();

    // Keep track of longest string
    if(description.length() > longestString){
        longestString = description.length();
    }
    
    std::cout << "[Success] Added Task " << description << "(ID:" << nextId << ")" << std::endl;

    // Keep track of nextId
    nextId++;

}

void TaskManager::list(){
    Task& t = task_list.at(1);
    std::cout << "lets see what this looks like" << std::endl;
    int longestNum    = std::to_string(nextId).length();
    t.formatListRow(longestNum, this->longestString);
}

void TaskManager::complete(int id){
    Task& t = task_list.at(id);
    t.complete();

    std::cout << "Task " << id << " has been completed" << std::endl;
}

void TaskManager::remove(int id, std::filesystem::path file_path){
    //remove from task_list 
    task_list.erase(id);

    std::ofstream output_file(file_path, std::ios::trunc);

    auto it = task_list.begin();
    auto end = task_list.end();
    output_file << it->second;
    it++;

    // Use iterators for file formatting purposes
    while(it != end){
        output_file << '\n' << it->second;
        it++;
    }

    std::cout << "[Success] Task " << id << " has been permanently deleted.";

}