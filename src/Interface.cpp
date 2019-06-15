#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <vector>
#include <stack>
#include "../header/Commands.hpp"

#include "../header/Interface.hpp"
#include <sstream>

bool CommandTree::createTree(vector<string> input) {
    if(!(input.size()%3 == 0) || (input.size() == 0)) return false;
    vector<Command*> cmd;
    vector<string> op;
    //Convert brackets
    
    for(int i = 0; i < input.size(); i += 3) {
            vector<string> argList;
            Command* temp; 
            
            string temp2 = input.at(i);
            cmd = shaveParen(cmd, temp2);
            
            
            input.at(i) = removeChar(temp2, '(');
            int rparen;
            if (input.at(i+1) == "") {
                temp2 = input.at(i);
                rparen = numChar(temp2, ')');
                input.at(i) = removeChar(temp2, ')');
            } else {
                temp2 = input.at(i + 1);
                rparen = numChar(temp2, ')');
                input.at(i + 1) = removeChar(temp2, ')');
            }

            argList = breakArgs(input.at(i + 1));
            if (input.at(i) == "test") temp = new test(input.at(i),argList);
            else if (hasString(argList, "[<]")) temp = new leftt(input.at(i),argList);
            else if (hasString(argList, "[>]")) temp = new rightt(input.at(i),argList);
            else if (hasString(argList, "[>>]")) temp = new rightright(input.at(i),argList);
            
            else {
                temp = new com(input.at(i),argList);
               //cout << "com push: " << endl;
            }
            cmd.push_back(temp);
            for (int i = 0; i < rparen; ++i) {
                cmd.push_back(new Rparen); 
               //cout << "rparens push: " << endl;
            }
            cmd.push_back(oper(input.at(i + 2)));
           //cout << "oper push: " << endl;
        }
        cmd.pop_back();
       //cout << "build complete: " << endl;
        /////////////////////////////////////////////////////display(cmd);
        // for(int i = 2; i < input.size(); i += 3) {
        //     if(input.at(i) != "&&" && input.at(i) != "||" && input.at(i) != ";") {
        //        //cout << "Internal arguments incorrect (operator)" << endl;
        //         return false;
        //     }
        //     op.push_back(input.at(i));
        // }
        return postTransform(cmd);
}

Command* CommandTree::oper(string in) {
    Command* delte = new com;
    if(in == ";") return new semi( delte, delte);
    else if(in == "||") return new orr( delte, delte);
    else if(in == "&&") return new andd( delte, delte);
    else if (in == "|") return new pipp(delte, delte);
}

vector <Command*> CommandTree::shaveParen(vector<Command*> cmd, string in) {
    for(int i = 0; i < in.size(); ++i) {
        if(in.at(i) == '(') {
            Command* temp = new Lparen;
           //cout << "lparens push: " << endl;
            cmd.push_back(temp);
        }
    }
    return cmd;
}

bool CommandTree::postTransform(const vector<Command*> cmd) {
    stack<Command*> st;
   //cout << "Connect: " << endl;
    for (int i = 0; i < cmd.size(); ++i) {
       //cout << i << " retType: " << cmd.at(i)->retType()  << endl;
        //st.top()->display();
        if (isCom(cmd.at(i))) {
           //cout << "type 1" << endl;
            tree.push_back(cmd.at(i));
        }
        else if (isLParen(cmd.at(i))) {
           //cout << "t2" << endl;
            st.push(cmd.at(i));
        }
        else if (isRParen(cmd.at(i))) {
           //cout << "t3" << endl;
            while (!isLParen(st.top())) {
                
                tree.push_back(st.top());
                st.pop();
            }
            st.pop();
        } else st.push(cmd.at(i));
        
    }
    while(!st.empty()) {
       //cout << "bb" << endl;
        tree.push_back(st.top());
        st.pop();
    }
   //cout << "after Transform: " << endl;
    /////////////////////////////////////////////display(tree);
    return (connectTree());
}

bool CommandTree::connectTree() {
    stack<Command*> todo, cmd;
   //cout << "Tree size:: "<<tree.size()<< endl;
    for (int i = tree.size() - 1; i >= 0; --i) {
        todo.push(tree.at(i));
    }
   //cout << "to connect: " << endl;
    while(!todo.empty()) {
        Command* top= todo.top();
        todo.pop();
        if(isConnector(top)) {
            Command* lchild, *rchild;
            rchild = cmd.top();
            cmd.pop();
            lchild = cmd.top();
            cmd.pop();
            top->setChild(lchild,rchild);
        }
        cmd.push(top);
    }
    root = tree.at(tree.size() - 1);
    return true;
}

bool CommandTree::connectTree(const vector<Command*> cmd, const vector<string> op) {
    //cout << "Connecting Tree: " <<  endl;
    Command* temp;
    if (op.size() == 1) temp = cmd.at(0);
    else if(op.at(0) == ";") temp = new semi(cmd.at(0), cmd.at(1));
    else if (op.at(0) == "||") temp = new orr(cmd.at(0), cmd.at(1));
    else if (op.at(0) == "&&") temp = new andd(cmd.at(0), cmd.at(1));
    else if (op.at(0) == "|") temp = new pipp(cmd.at(0), cmd.at(1));
    else return true;
    tree.push_back(temp);
    
    for(int i = 1; i < op.size() - 1; ++i) {
        //cout << "entered tree loop: " << i <<  endl;
        if(op.at(i) == ";") { temp = new semi(tree.at(i-1), cmd.at(i + 1));}
        else if (op.at(i) == "||") {temp = new orr(tree.at(i-1), cmd.at(i + 1));}
        else if (op.at(i) == "&&") {temp = new andd(tree.at(i-1), cmd.at(i + 1)); }
        else if (op.at(i) == "|") temp = new pipp(cmd.at(i-1), cmd.at(i + 1));
        else return true;
        tree.push_back(temp);
    }
    root = tree.at(tree.size() - 1);
    return true;
}

vector<string> CommandTree::breakArgs(string input) {
    
    vector<string> out;
    stringstream word(input);
    string in;
    while (word >> in) {
        out.push_back(in);
    }
    
    return out;
}

bool CommandTree::exec() {
    root->exec();
}

void CommandTree::display() {
    root->display();
}

vector<string> CommandInterface::ProccessArgs(string in) {
    vector<string> recognizedConnectorList = {";", "||", "&&", "|"};
    vector<string> ret;
    stringstream ss(in);
    
    string agg;
    bool inQuote = false;
    bool hasQuote = false;
    while(ss >> in) {
        if (in.length() == 0) return ret;
        if(!isEven(numChar(in,'\"'))) inQuote = toggle(inQuote);
        else if (hasChar(in,'\"')) hasQuote = toggle(hasQuote);
        
        if(isCommand(in, recognizedConnectorList) && !inQuote && !hasQuote) {
            agg.pop_back();
            agg = removeChar(agg, '\"');
            ret.push_back(agg);
            ret.push_back(in);
            agg = "";
        } else {
            agg += in + " ";
        }
        hasQuote = false;
    }
    agg.pop_back();
    agg = removeChar(agg, '\"');
    ret.push_back(agg);
    /////////////////////////////////////////////////display(ret);
    return ret;
}
// vector<string> CommandInterface::correctInput(string in) {
//     vector<string> gracefull = {"echo", "parse failed: Unrecognized input\n", ";"};
//     bool inQuote = false;
//     bool hasQuote = false;

//     for(int i = 0; i < in.size(); ++i) {
//         if(!inQuote && !hasQuote)
//     }
    // if ((numChar(in, '[') != numChar(in, ']')) || (numChar(in, '(') != numChar(in, ')'))
    //     || (numChar(in, '\"') % 2)) return gracefull;
//     return gracefull;
// }

bool CommandTree::hasString(vector<string> args, string str) {
    for (int i = 0; i < args.size(); ++i) {
        if (args.at(i) == str) {
            return true;
        }
    }
    return false;
}

vector<string> CommandInterface::parse() {
    
    string in;
    getline(cin, in);
    //vector<string> recognizedCommandList = {"echo", "ls", "mkdir", "exit", "false", "git"};
    vector<string> recognizedConnectorList = {";", "||", "&&", "|"};
    vector<string> gracefull = {"echo", "parse failed: Unrecognized input\n", ";"};
    vector<char> recognizedExceptionList = {'"'};
    string temp = in;
    
    if ((numChar(in, '[') != numChar(in, ']')) || (numChar(in, '(') != numChar(in, ')'))
        || (numChar(in, '\"') % 2)) return gracefull;
        
    in = ridHash(in);
    
    vector<string> input;
    if (in.size() == 0) return input;
    if (in.at(in.size()-1) != ';') in += " ;";
    
    
    stringstream word(in);
    in = "";
    bool inQuote;
    bool hasQuote;
    bool hasBracket;
    while (word >> in) {
        if (true) {  //isCommand(in, recognizedCommandList)
            string tt = removeChar(in, '(');
            if(tt == "[") {
                in.pop_back();
                in += "test";
                //cout << "INNNNNNN: " << in << endl;
                hasBracket = true;
            }
            input.push_back(in);
            string temp = "";
            in = "";
            word >> temp;
            inQuote = false;
            hasQuote = false;
            bool redirectQuote = false;
            if (hasChar(temp, recognizedExceptionList.at(0))) { //if has a double quote
                if(!isEven(numChar(temp,recognizedExceptionList.at(0)))) {
                    inQuote = toggle(inQuote);
                }
                else {
                    temp = removeChar(temp, recognizedExceptionList.at(0));
                    
                    hasQuote = true;
                }
                temp = removeChar(temp, recognizedExceptionList.at(0));
                
                //cout << temp << endl;
            }
            while (!isCommand(temp,recognizedConnectorList) || inQuote || hasQuote) {
                hasQuote = false;
                //cout << inQuote << endl;
                //cout << temp;
                if (hasChar(temp, recognizedExceptionList.at(0))) {
                    if(!isEven(numChar(temp,recognizedExceptionList.at(0)))) {
                        
                        inQuote = toggle(inQuote);
                    } else {
                        temp = removeChar(temp,recognizedExceptionList.at(0));
                        hasQuote = true;
                        redirectQuote = true;
                        continue;
                    }
                    temp = removeChar(temp,recognizedExceptionList.at(0));
                    //cout << inQuote << endl;
                } 
                if (!redirectQuote && !inQuote && temp == "<" || temp == ">" || temp == ">>") {
                    temp = "[" + temp + "]";
                }
                redirectQuote = false;
                if (temp.length() == 0) {
                    
                    word >> temp; 
                    continue;
                }

                if (temp.at(temp.size()-1) == ';' && !inQuote) {
                    temp.pop_back();
                    in = in + temp + " ";
                    temp = ";";
                    break;
                }
                in = in + temp + " ";
                word >> temp;
                //cout << "in: " << in << endl;
                //cout << "t: " << temp << endl;
            }
            in = removeChar(in,recognizedExceptionList.at(0));
            if(hasBracket) {
                in = removeChar(in, ']');
                in.pop_back();
                //in.push_back(';');
                hasBracket = false;
            }
            if(in.size() != 0 && in.at(in.size() - 1) == ' ') in.pop_back();
            
            input.push_back(in);
            in = temp;
            input.push_back(in);
            
        }
        else {
           //cout << "Parser error" << endl;
            return gracefull;
        }
    }
    
    //display(input);
    
    //cout << "exited" << endl;
    return input;
}

// vector<string> CommandInterface::parse() {
    
//     string in;
//     getline(cin, in);
//     //vector<string> recognizedCommandList = {"echo", "ls", "mkdir", "exit", "false", "git"};
//     vector<string> recognizedConnectorList = {";", "||", "&&"};
//     vector<string> gracefull = {"echo", "parse failed: Unrecognized input\n", ";"};
//     vector<char> recognizedExceptionList = {'"'};
//     if ((numChar(in, '[') != numChar(in, ']')) || (numChar(in, '(') != numChar(in, ')'))
//         || (numChar(in, '\"') % 2)) return gracefull;
        
    
//     in = ridHash(in);
    
//     vector<string> input = ProccessArgs(in);
    
//     return gracefull;
//     // stringstream word(in);
    
//     // while (word >> in) {
//     //     if (true) {  //isCommand(in, recognizedCommandList)
//     //         stack <string> op;
//     //         stack <string> st;
//     //         input.push_back(in);
//     //         string temp = "";
//     //         in = "";
//     //         word >> temp;
//     //         inQuote = false;
//     //         hasQuote = false;
//     //         if (hasChar(temp, recognizedExceptionList.at(0))) { //if has a double quote
//     //             if(!isEven(numChar(temp,recognizedExceptionList.at(0)))) {
//     //                 inQuote = toggle(inQuote);
//     //             }
//     //             else {
//     //                 temp = removeChar(temp, recognizedExceptionList.at(0));
                    
//     //                 hasQuote = true;
//     //             }
//     //             temp = removeChar(temp, recognizedExceptionList.at(0));
                
//     //             //cout << temp << endl;
//     //         }
//     //         while (!isCommand(temp,recognizedConnectorList) || inQuote || hasQuote) {
//     //             hasQuote = false;
//     //             //cout << inQuote << endl;
//     //             //cout << temp;
//     //             if (hasChar(temp, recognizedExceptionList.at(0))) {
//     //                 if(!isEven(numChar(temp,recognizedExceptionList.at(0)))) {
                        
//     //                     inQuote = toggle(inQuote);
//     //                 } else {
//     //                     temp = removeChar(temp,recognizedExceptionList.at(0));
//     //                     hasQuote = true;
//     //                     continue;
//     //                 }
//     //                 temp = removeChar(temp,recognizedExceptionList.at(0));
//     //                 //cout << inQuote << endl;
//     //             }
//     //             if (temp.length() == 0) {
                    
//     //                 word >> temp; 
//     //                 continue;
//     //             }

//     //             if (temp.at(temp.size()-1) == ';' && !inQuote) {
//     //                 temp.pop_back();
//     //                 in = in + temp + " ";
//     //                 temp = ";";
//     //                 break;
//     //             }
//     //             in = in + temp + " ";
//     //             word >> temp;
//     //             //cout << "in: " << in << endl;
//     //             //cout << "t: " << temp << endl;

                
//     //         }
//     //         if(in.size() != 0 && in.at(in.size() - 1) == ' ') in.pop_back();
//     //         in = removeChar(in,recognizedExceptionList.at(0));
//     //         input.push_back(in);
//     //         in = temp;
//     //         input.push_back(in);
//     //     }
//     //     else {
//     //        //cout << "Parser error" << endl;
//     //         return gracefull;
//     //     }
//     // }
    
//     // //display(input);
    
//     // //cout << "exited" << endl;
//     // return input;
// }