#include <iostream>
#include <string>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sstream>
#include <signal.h>

using namespace std;

fstream history;

void signalHandler(int signum) {
    history.close();
    cout << "Caught signal " << signum << endl;
    history.open("historyFile.txt", ios::out);
    string content;
    while(getline(history, content)) {
        cout << content;
    }
    history.close();
    system("exit");
}

void write(int fd, const char *buf, int count) {
    write(fd, buf, count);
}

void readPipe(int fd, char *buf, int count) {
    read(fd, buf, count);
}

int main() {
    string input;
    
    history.open("historyFile.txt", ios::in);
    while(1) {
    signal(SIGINT, signalHandler);
    cout << "InsertFunnyPromptHere:\\$";
    //Get the line, if = myprocess, call getpid, else, system(fjnifs)
    getline(cin, input);
    history << input << endl;
    if (input == "myprocess") {
        system("ps -u");
    }
    else if (input == "allprocesses") {
        system("ps -a");
    }
    else if (input.substr(0, 4) == "chgd") { //Take up to first space -> command, param
        string command;
        string params;
        stringstream inputstream(input);
        inputstream >> command >> params;
        system("chdir(params.c_str())");
    }
    else if (input == "clr") {
        system("clear");
    }
    else if (input == "dir") {
        system("ls");
    }
    else if (input == "environ") {
        system("env");
    }
    else if (input.substr(0, 6) == "repeat") {
        string command;
        string word;
        string operater;
        string fileName;
        stringstream inputstream(input);
        inputstream >> command;
        inputstream >> word;
        if (inputstream >> operater) {
            cout << operater;
            fstream redirectFile;
            inputstream >> fileName;
            redirectFile.open(fileName, ios::in);
            redirectFile << word;
            redirectFile.close();
        }
        else {
            cout << word << endl;
        }
    }
    else if (input == "hiMom") {
        int pid;
        int pip[2];
        char instring[20];
        int count;

        pipe(pip);

        pid = fork();
        if (pid == 0) {
            close(pip[0]);
            write(pip[1], "hiMom", 5);
            close(pip[1]);
        }
        else {
            close(pip[1]);
            readPipe(pip[0], instring, 20);
            close(pip[0]);
            printf("%s\n", instring);
        }
    }
    else if (input == "quit") {
        history.close();
        history.open("historyFile.txt", ios::out);
        string content;
        while(getline(history, content)) {
            cout << content;
        }
        history.close();
        system("exit");
        //I have no idea why but I just cannot for the life of me get this to work
    }
    else if (input == "help") {
        cout << "myprocess - Return the current process ID" << endl;
        cout << "allprocesses - Return all current processes" << endl;
        cout << "chgd <directory> - Change the current working directory to <directory>" << endl;
        cout << "clr - Clear the screen" << endl;
        cout << "dir <directory> - List the contents of <directory>" << endl;
        cout << "environ - List all the environment strings" << endl;
        cout << "quit - Quit the shell" << endl;
        cout << "help - Display the user manual" << endl;
        cout << "repeat <string> - Output the string to the console" << endl;
        cout << "repeat <string> > <filename> - Redirect the string to the specified file" << endl;
        cout << "hiMom - Execute parent-child process communication" << endl;
        cout << "Ctrl-C - Perform a signal interrupt" << endl;
    }
    else {
        system("input.c_str()");
    }}
}