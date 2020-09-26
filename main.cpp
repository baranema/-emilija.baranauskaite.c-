//
//  main.cpp
//  [emilija.baranauskaite.c++]
//
//  Created by Ema Baranauskaite on 2020-09-26.
//

#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

#include <string>
#include <iostream>
#include <filesystem>
#include <stack>
#include <cstdio>


using namespace std;
namespace fs = std::__fs::filesystem;

void list(string currDir) {
    std::string path = currDir;
        for (const auto & entry : fs::directory_iterator(path))
            std::cout << entry.path() << std::endl;
}

void removeEl(char file[]) {
    if (remove(file) != 0)
        perror("File deletion failed");
    else
        cout << "File deleted successfully";
}

string get_current_dir() {
   char buff[FILENAME_MAX];
   GetCurrentDir( buff, FILENAME_MAX );
   string current_working_dir(buff);
   return current_working_dir;
}

int main(int argc, const char * argv[]) {
    bool stop = false;
    bool changedDir = false;
    
    stack<string> allDirs;
    string command;
    string currDir = get_current_dir();
    allDirs.push(currDir);
    cout << currDir << "> ";
    
    allDirs.push(currDir);
    while (stop == false) {
        string newDir;
        getline(cin, command);
        
        if (command == "list") {
            list(currDir);
        } else if (command == "stop") {
            stop = true;
        } else if (command.find("delete") != std::string::npos) {
            string delimiter = " ";
            string s = command.substr(7, s.find(delimiter));
            
            int n = s.length();
            char file[n+1];
            
            strcpy(file, s.c_str());
            
            removeEl(file);
        } else if (command.find("enter") != std::string::npos) {
            if (command.length() > 7) {
                string delimiter = " ";
                newDir = command.substr(6, command.find(delimiter));
                changedDir = true;
            }
            else {
                cout << "No directory specified" << endl;
            }
        } else if (command == "leave") {
            allDirs.pop();
        }
        else {
            cout << "Command not defined." << endl;
        }
        if (changedDir == false)
            currDir = allDirs.top();
        else {
            changedDir = false;
            currDir = newDir;
        }
        
        allDirs.push(currDir);
        
        cout << currDir << "> ";
    }
    
    return 0;
}
