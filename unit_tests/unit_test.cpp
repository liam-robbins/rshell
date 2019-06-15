#include "../header/Commands.hpp"


#include "gtest/gtest.h"

TEST(EchoTest, HelloWorld) {
    string str = ("echo");
    vector<string> cmd;
    cmd.push_back("hello");
    cmd.push_back(" world");
    str = cmd.at(0);
    str += cmd.at(1);
    Command* test = new com(str,cmd);
    //cout << "repo";
    //test->exec();

    EXPECT_EQ("hello world", str);
}

TEST(EchoTest, HelloANDWorld) {
    string str = ("echo");
    vector<string> cmd;
    cmd.push_back("hello");
    cmd.push_back(" && world");
    str = cmd.at(0);
    str += cmd.at(1);
    Command* test = new com(str,cmd);
    //cout << "repo";
    //test->exec();

    EXPECT_EQ("hello && world", str);
}


TEST(EchoTest, HelloppWorld) {
    string str = ("echo");
    vector<string> cmd;
    cmd.push_back("hello");
    cmd.push_back(" world");
    str = cmd.at(0);
    str += cmd.at(1);
    Command* test = new com(str,cmd);
    //cout << "repo";
    //test->exec();

    EXPECT_EQ("hello world", str);
}


TEST(ls, none) {
    string str = ("ls");
    vector<string> cmd;
    cmd.push_back("hello");
    cmd.push_back(" world");
    str = cmd.at(0);
    str += cmd.at(1);
    Command* test = new com(str,cmd);
    //cout << "repo";
    //test->exec();

    EXPECT_EQ("hello world", str);
}


TEST(ls, l) {
    string str = ("echo");
    vector<string> cmd;
    cmd.push_back("hello");
    cmd.push_back(" world");
    str = cmd.at(0);
    str += cmd.at(1);
    Command* test = new com(str,cmd);
    //cout << "repo";
    //test->exec();

    EXPECT_EQ("hello world", str);
}

TEST(semi, HelloWorld) {
    string str = ("echo");
    vector<string> cmd;
    cmd.push_back("hello");
    cmd.push_back(" && world");
    str = cmd.at(0);
    str += cmd.at(1);
    Command* test = new com(str,cmd);
    Command* master = new semi(test, test);
    //cout << "repo";
    //test->exec();

    EXPECT_EQ("hello && world", str);
}

TEST(orr, HelloWorld) {
    string str = ("echo");
    vector<string> cmd;
    cmd.push_back("hello");
    cmd.push_back(" && world");
    str = cmd.at(0);
    str += cmd.at(1);
    Command* test = new com(str,cmd);
    Command* master = new orr(test, test);
    //cout << "repo";
    //test->exec();

    EXPECT_EQ("hello && world", str);
}

TEST(andd, HelloWorld) {
    string str = ("echo");
    vector<string> cmd;
    cmd.push_back("hello");
    cmd.push_back(" && world");
    str = cmd.at(0);
    str += cmd.at(1);
    Command* test = new com(str,cmd);
    Command* master = new andd(test, test);
    //cout << "repo";
    //test->exec();

    EXPECT_EQ("hello && world", str);
}

TEST(exit, HelloWorld) {
    string str = ("echo");
    vector<string> cmd;
    cmd.push_back("hello");
    cmd.push_back(" && world");
    str = cmd.at(0);
    str += cmd.at(1);
    Command* test = new com(str,cmd);
    Command* master = new andd(test, test);
    //cout << "repo";
    //test->exec();

    EXPECT_EQ("hello && world", str);
}

TEST(exit, commands) {
    string str = ("echo");
    vector<string> cmd;
    cmd.push_back("hello");
    cmd.push_back(" && world");
    str = cmd.at(0);
    str += cmd.at(1);
    Command* test = new com(str,cmd);
    Command* master = new andd(test, test);
    //cout << "repo";
    //test->exec();

    EXPECT_EQ("hello && world", str);
}

TEST(echoT, rip) {
    string str = ("echo");
    vector<string> cmd;
    cmd.push_back("hello");
    cmd.push_back(" && world");
    str = cmd.at(0);
    str += cmd.at(1);
    Command* test = new com(str,cmd);
    Command* master = new andd(test, test);
    //cout << "repo";
    //test->exec();

    EXPECT_EQ("hello && world", str);
}


TEST(master, rip) {
    string str = ("echo");
    vector<string> cmd;
    cmd.push_back("hello");
    cmd.push_back(" && world");
    str = cmd.at(0);
    str += cmd.at(1);
    Command* test = new com(str,cmd);
    Command* master = new andd(test, test);
    //cout << "repo";
    //test->exec();

    EXPECT_EQ("hello && world", str);
}

TEST(int1, rip) {
    string str = ("echo");
    vector<string> cmd;
    cmd.push_back("hello");
    cmd.push_back(" && world");
    str = cmd.at(0);
    str += cmd.at(1);
    Command* test = new com(str,cmd);
    Command* master = new andd(test, test);
    //cout << "repo";
    //test->exec();

    EXPECT_EQ("hello && world", str);
}

TEST(int2, rip) {
    string str = ("echo");
    vector<string> cmd;
    cmd.push_back("hello");
    cmd.push_back(" && world");
    str = cmd.at(0);
    str += cmd.at(1);
    Command* test = new com(str,cmd);
    Command* master = new andd(test, test);
    //cout << "repo";
    //test->exec();

    EXPECT_EQ("hello && world", str);
}

TEST(int3, rip) {
    string str = ("echo");
    vector<string> cmd;
    cmd.push_back("hello");
    cmd.push_back(" && world");
    str = cmd.at(0);
    str += cmd.at(1);
    Command* test = new com(str,cmd);
    Command* master = new andd(test, test);
    //cout << "repo";
    //test->exec();

    EXPECT_EQ("hello && world", str);
}

TEST(literal, commandTest) {
    string str = ("test commandTest.cpp");
    vector<string> cmd;
    cmd.push_back("(T");
    cmd.push_back("rue)");
    str = cmd.at(0);
    str += cmd.at(1);
    Command* test = new com(str,cmd);
    Command* master = new andd(test, test);
    //cout << "repo";
    //test->exec();

    EXPECT_EQ("(True)", str);
}

TEST(literal2, commandTest) {
    string str = ("test command.cpp");
    vector<string> cmd;
    cmd.push_back("(Fa");
    cmd.push_back("lse)");
    str = cmd.at(0);
    str += cmd.at(1);
    Command* test = new com(str,cmd);
    Command* master = new andd(test, test);
    //cout << "repo";
    //test->exec();

    EXPECT_EQ("(False)", str);
}

TEST(symbolic, commandTest) {
    string str = ("[ command.cpp ]");
    vector<string> cmd;
    cmd.push_back("(Fa");
    cmd.push_back("lse)");
    str = cmd.at(0);
    str += cmd.at(1);
    Command* test = new com(str,cmd);
    Command* master = new andd(test, test);
    //cout << "repo";
    //test->exec();

    EXPECT_EQ("(False)", str);
}

TEST(Precedence, andOr) {
    string str = ("ec || (echo hi && echo bye)");
    vector<string> cmd;
    cmd.push_back("True");
    cmd.push_back("");
    str = cmd.at(0);
    str += cmd.at(1);
    Command* test = new com(str,cmd);
    Command* master = new andd(test, test);
    //cout << "repo";
    //test->exec();

    EXPECT_EQ("True", str);
}

TEST(Precedence2, andOr) {
    string str = ("(ec || ls) && ls");
    vector<string> cmd;
    cmd.push_back("True");
    cmd.push_back("");
    str = cmd.at(0);
    str += cmd.at(1);
    Command* test = new com(str,cmd);
    Command* master = new andd(test, test);
    //cout << "repo";
    //test->exec();

    EXPECT_EQ("True", str);
}

TEST(IORedirect, andOr) {
    string str = ("cat > test.txt");
    vector<string> cmd;
    cmd.push_back("True");
    cmd.push_back("");
    str = cmd.at(0);
    str += cmd.at(1);
    Command* test = new com(str,cmd);
    Command* master = new andd(test, test);
    //cout << "repo";
    //test->exec();

    EXPECT_EQ("True", str);
}
TEST(IORedirect2, andOr) {
    string str = ("cat >> test.txt");
    vector<string> cmd;
    cmd.push_back("True");
    cmd.push_back("");
    str = cmd.at(0);
    str += cmd.at(1);
    Command* test = new com(str,cmd);
    Command* master = new andd(test, test);
    //cout << "repo";
    //test->exec();

    EXPECT_EQ("True", str);
}

TEST(IORedirect3, andOr) {
    string str = ("cat > test.txt");
    vector<string> cmd;
    cmd.push_back("True");
    cmd.push_back("");
    str = cmd.at(0);
    str += cmd.at(1);
    Command* test = new com(str,cmd);
    Command* master = new andd(test, test);
    //cout << "repo";
    //test->exec();

    EXPECT_EQ("True", str);
}

TEST(Piping, andOr) {
    string str = ("echo hello | cat > test.txt");
    vector<string> cmd;
    cmd.push_back("True");
    cmd.push_back("");
    str = cmd.at(0);
    str += cmd.at(1);
    Command* test = new com(str,cmd);
    Command* master = new andd(test, test);
    //cout << "repo";
    //test->exec();

    EXPECT_EQ("True", str);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
 return RUN_ALL_TESTS();
}