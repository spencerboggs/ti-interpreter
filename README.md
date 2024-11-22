# TI-BASIC Interpreter
A C++ program that simulates a TI-BASIC interpreter. It reads a TI-BASIC program from a text file, parses commands like ClrHome, Output, Pause, Goto, Menu, and more, and executes them interactively. Users can input values for variables, navigate through menus, and track program flow using labels and jumps.

## Features
* Command Parsing: Reads and parses TI-BASIC commands from a text file.
* Interactive Execution: Executes TI-BASIC commands like clearing the screen (ClrHome), displaying output (Output), pausing (Pause), and jumping to labels (Goto).
* Menu System: Implements a dynamic menu system where users can select options and navigate through different parts of the program.
* Variable Prompting: Prompts the user for variable input and stores the values for further use in the program.
* Program Control: Supports program flow control using labels and the Goto command.

## Dependenceis
The project requires the following C++ standard libraries:
* `<iostream>`
* `<fstream>`
* `<vector>`
* `<string>`
* `<unordered_map>`
* `<cstdlib>`
* `<algorithm>`
* `<limits>`

## Usage
1. Clone the repo and open the project in a C++ development environment:
```
git clone https://github.com/spencerboggs/ti-interpreter.git
cd ti-basic-interpreter
```
2. Compile the project:
```
g++ -o ti-interpreter ti-interpreter.cpp
```
3. Run the interpreter with a TI-BASIC script:
```
./ti-interpreter path_to_program.txt
```

The program will prompt you to press Enter to start. It will then read and execute the TI-BASIC commands from the provided file.

## Commands
* ClrHome: Clears the screen.
* Output: Displays text on the screen with a specified indentation.
* Pause: Pauses execution until the user presses Enter.
* Goto: Jumps to a specified label.
* Lbl: Defines a label in the program.
* Menu: Displays a menu with options for the user to choose from.
* Stop: Exits the program.
* Prompt: Prompts the user to input a value for a variable.
