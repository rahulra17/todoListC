#include "Task.hpp"
#include "TaskManager.hpp"
#include <vector>
#include <iostream>
#include <map>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <iomanip>

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

}

void TaskManager::add(std::string description, std::filesystem::path file_path) {
    std::ofstream outFile(file_path, std::ios::app);
    Task t(nextId, description);
    // if the file is empty put on line 1, otherwise new line
    if(task_list.size() > 0) {
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
    int longestNum    = std::to_string(nextId).length();

    std::stringstream ss;
    ss << std::left;
    ss << std::setw(longestNum + 4) << "ID" << std::setw(8) << "Status" << std::setw(this->longestString) << "Description" << std::endl;
    std::cout << ss.str();
    for(int i = 0; i < ss.str().length() - 1; i++){
        std::cout << '-';
    }
    std::cout << std::endl;
    for(auto& pair: task_list){
        (pair.second).formatListRow(longestNum, this->longestString);
    }
}

void TaskManager::complete(int id, std::filesystem::path file_path){
    Task& t = task_list.at(id);
    t.complete();

    updateFile(file_path);

    std::cout << "Task " << id << " has been completed" << std::endl;
}

void TaskManager::remove(int id, std::filesystem::path file_path){
    //remove from task_list 
    task_list.erase(id);

    updateFile(file_path);

    std::cout << "[Success] Task " << id << " has been permanently deleted.";

}

void TaskManager::updateFile(std::filesystem::path file_path){

    auto it = task_list.begin();
    auto end = task_list.end();

    std::ofstream output_file(file_path, std::ios::trunc);
    output_file << it->second;
    it++;

    // Use iterators for file formatting purposes
    while(it != end){
        output_file << '\n' << it->second;
        it++;
    }
}