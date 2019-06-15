#ifndef DEBUGGING_TOOLS_H
#define DEBUGGING_TOOLS_H

#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <vector>
#include "Commands.hpp"

void display(vector<Command*> vec) {
    for(int i = 0; i < vec.size(); ++i) {
        cout << i << ": ";
        vec.at(i)->display();
        
    }
    cout <<endl;
}
void display(vector<string> vec) {
    for(int i = 0; i < vec.size(); ++i) {
        cout << "(" << vec.at(i) << ") ";
    }
    cout << endl;
}

#endif