#ifndef __INTERFACEHPP__
#define __INTERFACEHPP__

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <vector>
//#include "../header/Commands.hpp"
//#include "../header/debugging_tools.hpp"

using namespace std;
struct pass {
    string name;
    string argList;
};

class CommandInterface {
    public:
    
    vector<string> parse();
    
    private:
    
    bool isCommand(string input, vector<string> vec) {
        for(int i = 0; i < vec.size(); ++i) {
            if(input == vec.at(i)) return true;
        }
        return false;
    }
    
    
    bool hasChar(string input, char ch) {
        for(int i = 0; i < input.length(); ++i) {
            if(input[i] == ch) return true;
        }
        return false;
    }
    string removeChar(string in, char ch) {
        string ret = "";
        for(int i = 0; i < in.length(); ++ i) {
            if (in[i] != ch) ret += in[i];
        }
        return ret;
    }
    
    int numChar(string in, char ch) {
        int ret = 0;
        for(int i = 0; i < in.length(); ++ i) {
            if (in[i] == ch) ++ret;
        }
        return ret;
    }
    
    bool isEven(int num) {
        if (num % 2) return false;
        return true;
    }
    bool toggle(bool in) {
        if (in) return false;
        else return true;
    }
    string ridHash(string temp) {
        string in = "";
        bool hash = false;
        for (int i = 0; i < temp.size(); ++i) {
            if (temp.at(i) == '#') {
                hash = true;
            }
            if(!hash) in += temp.at(i);
        }
        return in;
    }
    void display(vector<string> vec) {
        for(int i = 0; i < vec.size(); ++i) {
            cout << "(" << vec.at(i) << ") ";
        }
        cout << endl;
    }

    vector<string> ProccessArgs(string in);
    vector<string> correctInput(string in);
};

class CommandTree {
    private:
        Command* root;
        vector<Command*> tree;
    public:
        CommandTree(){}
        bool createTree(vector<string> input);
        bool connectTree(const vector<Command*> cmd, const vector<string> op);
        bool postTransform(const vector<Command*> cmd);
        bool connectTree();
        void display();
        bool exec();
    private:
        vector<string> breakArgs(string input);
        bool isCom(Command* in) {
            if (!isLParen(in) && !isRParen(in) && !isConnector(in)) return true;
            return false;
        }
        bool isLParen(Command* in) {
            if (in->retType() == "Lparen") return true;
            return false;
        }
        bool isRParen(Command* in) {
            if (in->retType() == "Rparen") return true;
            return false;
        }
        bool isConnector(Command* in) {
            if (in->retType() == "operator") return true;
            return false;
        }
        
        bool hasString(vector<string> args, string str);
        

        void display(vector<Command*> vec) {
            for(int i = 0; i < vec.size(); ++i) {
                cout << i << ": ";
                vec.at(i)->display();
                cout << endl;
            }
        }
        string removeChar(string in, char ch) {
        string ret = "";
        for(int i = 0; i < in.length(); ++ i) {
            if (in[i] != ch) ret += in[i];
        }
        return ret;
        }
        int numChar(string in, char ch) {
            int ret = 0;
            for(int i = 0; i < in.length(); ++ i) {
                if (in[i] == ch) ++ret;
            }
            return ret;
        }
        Command* oper(string in);
        vector <Command*> shaveParen(vector<Command*> cmd, string in);
};


#endif