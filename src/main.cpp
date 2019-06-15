#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <vector>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "../header/Commands.hpp"
#include "../header/debugging_tools.hpp"
#include "../header/Interface.hpp"
//#include "CommandTree.hpp"
#include <sstream>


using namespace std;

int main() {
    while(1) {
        cout << "$ ";
        CommandInterface* menu = new CommandInterface;
        CommandTree* program = new CommandTree;
        
    
        vector<string> input = menu->parse();
        //display(input);
        if (!program->createTree(input))continue;
        // //program.display();
        if (!program->exec()) continue;;
        
    }
    return 0;
}
