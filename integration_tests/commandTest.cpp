#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <vector>
#include "../src/Commands.cpp"
//#include "debugging_tools.hpp"

#include <sstream>

using namespace std;

int main(int argc, char **argv) {
    string str = ("echo");
    vector<string> cmd;
    cmd.push_back(argv[1]);
    Command* test = new com(str,cmd);
    //cout << "repo";
    test->exec();
    cmd.at(0) = argv[2];
    test = new com(str,cmd);
    test->exec();
    
    cmd.at(0) = argv[3];
    test = new com(str,cmd);
    test->exec();
    
    cmd.at(0) = argv[4];
    test = new com(str,cmd);
    test->exec();
    
    Command* test2 = new andd(test, test);
    test2->exec();
}