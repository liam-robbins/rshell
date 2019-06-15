#ifndef COMMANDS_H
#define COMMANDS_H

#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <vector>



using namespace std;



class Command {
    protected:
        string type = "abstract";
    public:
        Command(){}
        virtual void display() {cout << type;}
        virtual bool exec() = 0;
        virtual string retType() {return this->type;}
        virtual void setChild(Command* lchild, Command* rchild) {}
};



class Lparen : public Command {
    
    public:
        virtual bool exec() {}
        Lparen() {type = "Lparen";}
};

class Rparen : public Command {
    
    public:
        virtual bool exec() {}
        Rparen() {type = "Rparen";}
};

class com : public Command {
    protected:
        string pp = "operand";
        int argc;
        char **argv = (char**)malloc(10*sizeof(char*));
        //char* argv[100];
    public:
        com() {type = "operand";}
        com(string str, vector<string> input) {init(str, input);}
        void init(string str, vector<string> argList);
        virtual void display(); //debugging
        virtual bool exec();
    protected:
        
};



class Connector : public Command {
    public:

        Command* lprog;
        Command* rprog;
    public:
        Connector() {type = "operator";}
        virtual void display();
        virtual bool exec() {return true;}
        virtual void setChild(Command* lchild, Command* rchild) {
            lprog = lchild;
            rprog = rchild;
        }
};

class test : public com {
    private:
    public:
        test(string str, vector<string> input) {init(str, input);}
        virtual bool exec();
    private:
        int isReg(const char* str);
        int isDir(const char* str);
};

class redir : public com {
    protected:
    string fn;
    
    public:
        redir() {}
        virtual bool exec() = 0;
    void reinit(string str, vector<string> argList);
    protected:
    int isReg(const char* str);
    int find(char* f);

};
class rightt : public redir {
    private:
    public:
        rightt(string str, vector<string> input) {reinit(str, input);}
        virtual bool exec();
    private:
};

class rightright : public redir {
    private:
    public:
        rightright(string str, vector<string> input) {reinit(str, input);}
        virtual bool exec();
    private:
};

class leftt : public redir {
    private:
    public:
        leftt(string str, vector<string> input) {reinit(str, input);}
        virtual bool exec();
    private:
};


class semi : public Connector {
    private:
    public:
        semi() {}
        semi(Command* lin, Command* rin) {lprog = lin; rprog = rin;}
        virtual bool exec();
};

class orr : public Connector {
    private:
    public:
        orr() {}
        orr(Command* lin, Command* rin) {lprog = lin; rprog = rin;}
        virtual bool exec();
        //virtual void display() {cout <<"Worked";}
        //void echotest() {lprog->display(); rprog->display();}
        //virtual bool exe() {cout << "Did it";}
};

class andd : public Connector {
    private:
    
    public:
        andd() {}
        virtual bool exec();
        andd(Command* lin, Command* rin) {lprog = lin; rprog = rin;}
        //virtual bool exe() {cout << "Did it";}
};

class pipp : public Connector {
    private:
    
    public:
        pipp() {}
        virtual bool exec();
        pipp(Command* lin, Command* rin) {lprog = lin; rprog = rin;}
        //virtual bool exe() {cout << "Did it";}
};

#endif