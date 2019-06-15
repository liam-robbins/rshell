#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <vector>
#include "../header/Commands.hpp"
#include "../header/Interface.hpp"
#include <sstream>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>



void Connector::display() {
    lprog->display();
    cout << " ("<<this->type << ") ";
    rprog->display();
    return;
}

void com::display() {
    if (type == "operand") return;
    for(int i = 0; i < argc -1; ++i) {
        cout << "arg[" << i << "]: {" << argv[i] << "} ";
    }
    return;
}


void com::init(string str, vector<string> argList) {
    
    type = str;
    argc = argList.size() + 2;
    for(int i = 0; i < 10; i++){
        argv[i] = (char*)malloc(50*sizeof(char));
    }
    argv[0] = const_cast<char*>(type.c_str());
    for(int i = 1; i < argc - 1; ++i) {
        strcpy(argv[i],argList.at(i-1).c_str());
        //argv[i] = const_cast<char*>(argList.at(i-1).c_str());
    }
    argv[argc-1] = NULL;
    
}

void redir::reinit(string str, vector<string> argList) {
    for(int i = 0; i < argList.size(); ++i) {
        if (argList.at(i) == "[<]" || argList.at(i) == "[>]" || argList.at(i) == "[>>]") {
            argList.erase(argList.begin() + i);
            //cout << "asdf" << endl;
            fn = argList.at(i);
            argList.erase(argList.begin() + i);
            //--argc;
        }
    }
    type = str;
    argc = argList.size() + 2;
    for(int i = 0; i < 10; i++){
        argv[i] = (char*)malloc(50*sizeof(char));
    }
    argv[0] = const_cast<char*>(type.c_str());
    for(int i = 1; i < argc - 1; ++i) {
        strcpy(argv[i],argList.at(i-1).c_str());
        //argv[i] = const_cast<char*>(argList.at(i-1).c_str());
    }
    argv[argc-1] = NULL;
    
}




bool com::exec() {
    int check, status;
    pid_t pid = fork();
    if (pid < 0) {
        perror("Fork error: %d");
        exit(0);
    } else if (pid == 0) {
        if (type == "exit") exit(0);
        if (execvp(this->argv[0],this->argv) == -1) {
            perror("execvp failed");
            check = -1;
            exit(check);
        }
    } else {
        //cout << check << endl;
        wait(&status);

        //cout << check << endl;
        if (type == "exit") {
            exit(0);
        }
        
        if(WEXITSTATUS(status) != 0) return false; 
        else return true; 
    }
    
    return true;
}

bool semi::exec() {
    lprog->exec();
    rprog->exec();
    return true;
}

bool orr::exec() {
    bool r = lprog->exec();
    //cout << "or right side return: " << r << endl;
    if (!r) return (rprog->exec());
    return true;
}

bool andd::exec() {
    bool r = lprog->exec();
    //cout << "and left side return: " << r << endl;
    if (r) return(rprog->exec());
    return true;
}

bool test::exec() {
    if(argv[1] == NULL) {
        cout << "(false)" << endl;
        return false;
    }
    string arg = argv[1];
    
    if (arg == "-f" && isReg(argv[2])){}
    else if (arg == "-d" && isDir(argv[2])){}
    else if (arg == "-e" && (isReg(argv[2]) || isDir(argv[2]))){}
    else if (argv[2] == NULL && (isReg(argv[1]) || isDir(argv[1]))){}
    else {cout << "(false)" << endl; return false;}
    
    cout << "(true)" << endl;
    return true;
}

int redir::isReg(const char* str) {
    struct stat check;
    stat(str, &check);
    return S_ISREG(check.st_mode);
}

int redir::find(char* f) {
    for(int i = 0; i < argc; ++i) {
        if(strcmp(argv[i], f) == 0) return i + 1;
    }
    return 0;
}



bool leftt::exec() {
    int check, status;
    
    //strcpy(fn, argv[find(strdup("[<]"))])
    //cout << "fn:" << fn<< endl;
    //argv[1] = "";

    pid_t pid = fork();
    if (pid < 0) {
        perror("Fork error: %d");
        exit(0);
    } else if (pid == 0) {
        if(!isReg(fn.c_str())) {
            perror("Filename Error");
            exit(0);
        }
        int out;
        out = open(fn.c_str(),O_RDONLY);
        dup2(out,0);
        if (type == "exit") exit(0);
        if (execvp(this->argv[0],this->argv) == -1) {
            perror("execvp failed");
            check = -1;
            exit(check);
        }
    } else {
        //cout << check << endl;
        wait(&status);

        //cout << check << endl;
        if (type == "exit") {
            exit(0);
        }
        
        if(WEXITSTATUS(status) != 0) return false; 
        else return true; 
    }
    
    return true;
    
}

bool rightt::exec() {
    int check, status;
    
    //strcpy(fn, argv[find(strdup("[<]"))])
    //cout << "fn:" << fn<< endl;
    //argv[1] = "";
    pid_t pid = fork();
    if (pid < 0) {
        perror("Fork error: %d");
        exit(0);
    } else if (pid == 0) {
        int out;
        out = open(fn.c_str(),O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
        dup2(out,1);
        if (type == "exit") exit(0);
        if (execvp(this->argv[0],this->argv) == -1) {
            perror("execvp failed");
            check = -1;
            exit(check);
        }
    } else {
        //cout << check << endl;
        wait(&status);

        //cout << check << endl;
        if (type == "exit") {
            exit(0);
        }
        
        if(WEXITSTATUS(status) != 0) return false; 
        else return true; 
    }
    
    return true;
}

bool rightright::exec() {
    int check, status;
    //[10][10];
    //strcpy(fn, argv[find(strdup("[<]"))])
    //cout << "fn:" << fn<< endl;
    //argv[1] = "";
    pid_t pid = fork();
    if (pid < 0) {
        perror("Fork error: %d");
        exit(0);
    } else if (pid == 0) {
        int out;
        out = open(fn.c_str(), O_WRONLY | O_APPEND);
        dup2(out,1);
        if (type == "exit") exit(0);
        if (execvp(this->argv[0],this->argv) == -1) {
            perror("execvp failed");
            check = -1;
            exit(check);
        }
    } else {
        //cout << check << endl;
        wait(&status);

        //cout << check << endl;
        if (type == "exit") {
            exit(0);
        }
        
        if(WEXITSTATUS(status) != 0) return false; 
        else return true; 
    }
    
    return true;
}



int test::isReg(const char* str) {
    struct stat check;
    stat(str, &check);
    return S_ISREG(check.st_mode);
}

int test::isDir(const char* str) {
    struct stat check;
    stat(str, &check);
    return S_ISDIR(check.st_mode);
}

bool pipp::exec() {

    pid_t id = fork();
    int stat;
    
    if(id == 0) {
        int status;
        int peepee[2];
        pipe(peepee);
        pid_t id2 = fork();
        if(id2 == 0) {
            //cout << "ah" << endl;
            close(peepee[0]);
            dup2(peepee[1], 1);
            lprog->exec();
            exit(0);
        } else {
            close(peepee[1]);
            dup2(peepee[0], 0);
            wait(&status);
            rprog->exec();
            exit(0); 
        }
    } else {
        wait(&stat);
        return true;
    }

}