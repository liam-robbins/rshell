# Project information (Assignment 4)

#### Year/Quarter: 
Spring/2019

#### Authors: 
Liam Robbins (862032147) 

Alex de Victoria (862004916)


# Introduction
This program will emulate bash in C++. It will be able to recognize commands and command line arguments, as well as modifiers.

For assignment two specifically, this program will be able to execute bash commands sequentially. It should be able to take connectors ";", "&&", and "||", as well as any command line arguments.  These commands and connectors will behave as stated on the prompt.

# Diagrams
![UML Diagram](https://lh3.googleusercontent.com/7AZXQ9O2RTzW_2qAZ4gokg6s-P_GVlL7-GuojfY2oyhzV9bOqvwXSWOzz_TJMye1jsGnyjQW-2U "UML Diagram")

# Classes
Base class: All commands and sets the default behavior for inherited classes

Commands: will execute the next command following a semicolon(;)

Connectors: set foundation for the 3 connectors AND(&&), OR(||), and semicolon(;)

AND(&&): executes next command that follows && if the first command succeeds

OR(||): executes next command that follows || only if the first command fails

Semicolon(;): the next command that follows ; will always execute

# Assignment 4 debriefing

### Progress:

Completed the goals of assignment 4, implementing I/O redirection and piping. 

### After action report

Not the hardest assignment, but not easy either. Finished in a few hours. piping was implemented easy enough, along with I/O redireciton.
