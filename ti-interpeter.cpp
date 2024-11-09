#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <cstdlib>
#include <algorithm>
#include <limits>

using namespace std;

void Stop() {
    cout << "Exiting program..." << endl;
    exit(0);
}

void ClrHome() {
    cout << "\033c";
}

void Output(const string& line) {
    string modified_line = line;
    modified_line.erase(0, 7);
    modified_line.erase(0, 1);

    size_t comma_pos1 = modified_line.find(',');
    size_t comma_pos2 = modified_line.find(',', comma_pos1 + 1);

    int spaces = stoi(modified_line.substr(comma_pos1 + 1, comma_pos2 - comma_pos1 - 1));
    string string_output = modified_line.substr(comma_pos2 + 1);

    string_output = string_output.substr(0, string_output.find_last_not_of(" \t\n\r") + 1);
    string_output.erase(remove(string_output.begin(), string_output.end(), '"'), string_output.end());

    cout << string(spaces, ' ') << string_output << endl;
}

void Pause() {
    cin.get();
}

int Goto(int& current_line, const string& label, const vector<string>& valid_lines) {
    for (size_t i = 0; i < valid_lines.size(); ++i) {
        if (valid_lines[i].find("Lbl " + label) != string::npos) {
            current_line = i;
            return 0;
        }
    }
    return -1;
}

void Menu(const string& line, int& current_line, const vector<string>& valid_lines) {
    string modified_line = line;
    modified_line.erase(0, 5);
    modified_line.erase(0, 1);

    vector<string> options;
    size_t start = 0, end;
    while ((end = modified_line.find(',', start)) != string::npos) {
        string option = modified_line.substr(start, end - start);
        option.erase(remove(option.begin(), option.end(), '"'), option.end());
        options.push_back(option);
        start = end + 1;
    }

    string last_option = modified_line.substr(start);
    last_option.erase(remove(last_option.begin(), last_option.end(), '"'), last_option.end());
    options.push_back(last_option);

    cout << options[0] << endl;
    for (size_t i = 1; i < options.size(); i += 2) {
        cout << (i / 2 + 1) << ". " << options[i] << endl;
    }

    int choice;
    bool choice_valid = false;
    while (!choice_valid) {
        cout << "Enter the number of the option you want to select: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number." << endl;
        } else if (choice >= 1 && choice <= options.size() / 2) {
            choice_valid = true;
        } else {
            cout << "Invalid option. Please enter a number between 1 and " << options.size() / 2 << "." << endl;
        }
    }
    
    ClrHome();

    for (size_t i = 1; i < options.size(); i += 2) {
        if (choice == (i / 2 + 1)) {
            if (options[i] == "Stop") {
                Stop();
            } else if (options[i] == "Print") {
                Output(options[i + 1]);
            } else {
                Goto(current_line, options[i + 1], valid_lines);
                Pause();
                return;
            }
        }
    }

}

void Prompt(const string& variable, unordered_map<string, string>& variables) {
    cout << "Enter a value for variable " << variable << ": ";
    string value;
    cin >> value;
    variables[variable] = value;
    
    cout << "You entered: " << value << endl;
    Pause();
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Please provide the file path." << endl;
        return 1;
    }

    cout << "TI-BASIC Interpreter" << endl;
    cout << "File: " << argv[1] << endl;
    cout << "Press Enter to start the program." << endl;

    Pause();

    ifstream file(argv[1]);
    string line;
    vector<string> valid_lines;
    unordered_map<string, string> variables;
    int current_line = 0;

    vector<string> commands = {"ClrHome", "Output", "Pause", "Goto", "Lbl", "Menu", "Stop", "Prompt"};

    while (getline(file, line)) {
        line.erase(line.find_last_not_of(" \n\r\t") + 1);
        for (const auto& command : commands) {
            if (line.find(command) == 0) {
                valid_lines.push_back(line);
                break;
            }
        }
    }

    while (current_line < valid_lines.size()) {
        line = valid_lines[current_line];
        if (line.find("ClrHome") == 0) {
            ClrHome();
        } else if (line.find("Output") == 0) {
            Output(line);
        } else if (line.find("Pause") == 0) {
            Pause();
        } else if (line.find("Goto") == 0) {
            Goto(current_line, line.substr(5), valid_lines);
        } else if (line.find("Menu") == 0) {
            Menu(line, current_line, valid_lines);
        } else if (line.find("Stop") == 0) {
            Stop();
        } else if (line.find("Prompt") == 0) {
            Prompt(line.substr(7), variables);
        }

        if (line.find("Goto") != 0) {
            current_line++;
        }
    }

    return 0;
}
