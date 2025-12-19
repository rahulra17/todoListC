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
    this->nextId = 0;
    // Load any data already in file into map
    std::ifstream inputFile(data);
    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open the file example.txt" << std::endl;
    }
    std::string currLine;
    while(std::getline(inputFile, currLine)){
        std::vector<std::string> currData = parseData(currLine);
        int currId = std::stoi(currData[0]);
        std::string currDescription = currData[2];
        bool currCompletion = static_cast<bool>(std::stoi(currData[1]));
        Task t(currId, currDescription, currCompletion);
        task_list.insert({currId, t});
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
    task_list.insert({nextId, t});
    outFile << '\n' << t; 
    outFile.close();
}

void TaskManager::list(){

}

void TaskManager::complete(int id){

}

void TaskManager::remove(int id, std::filesystem::path file_path){
    std::ostringstream search_ostream;

    search_ostream << task_list.at(id);

    std::string search_for = search_ostream.str();

    std::cout << "this is what im searching for: " << search_for << std::endl; 


    task_list.erase(id);
    std::ostringstream data;

    //read file
    std::ifstream in_stream(file_path);

    data << in_stream.rdbuf();

    //close read file since we have all of it in data
    in_stream.close();

    std::string file_contents = data.str();

    size_t pos = file_contents.find(search_for);

}