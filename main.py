import sys

# Parsing the file
file = open(sys.argv[1], "r")
lines = file.readlines()
file.close()

# Adding valid commands to a list
commands = ['ClrHome', 'Output', 'Pause', 'Goto', 'Lbl', 'Menu', 'Stop', 'Prompt']
valid_lines = []
for i in range(len(lines)):
    lines[i] = lines[i].replace('\n', '')
    if lines[i].startswith(tuple(commands)):
        valid_lines.append(lines[i])

# Running the program
current_line = 0
variables = {}

def ClrHome():
    print('\033c', end='')

def Output(line):
    line = line.replace('Output(', '')
    line = line.replace('"', '', 1)
    if '"' in line:
        line = line.split('"')[0]
    line = line.split(',', 2)
    spaces = int(line[1])
    string = line[2]
    print(' ' * spaces + string)

def Pause():
    input("")

def Goto(label):
    global current_line
    for i in range(len(valid_lines)):
        if f'Lbl {label}' in valid_lines[i]:
            current_line = i
            return
    
def Menu(line):
    line = line.replace('Menu(', '')
    line = line.replace('"', '')
    line = line.split(',')
    print(line[0])
    for i in range(1, len(line), 2):
        print(f'{(i // 2) + 1}. {line[i]}')
    choice_valid = False
    while (not choice_valid):  
        choice = input('Enter the number of the option you want to select: ')
        if choice.isdigit() and 1 <= int(choice) <= len(line) // 2:
            choice_valid = True
        else:
            print('\033[F\033[K', end='')
    for i in range(1, len(line), 2):
        if choice == str(i // 2 + 1):
            Goto(line[i + 1])
    ClrHome()

def Stop():
    sys.exit()

def Prompt(variable):
    global variables
    variables[variable] = input(f'Enter a value for variable {variable}: ')

while current_line < len(valid_lines):
    line = valid_lines[current_line]
    if line.startswith('ClrHome'):
        ClrHome()
    elif line.startswith('Output'):
        Output(line)
    elif line.startswith('Pause'):
        Pause()
    elif line.startswith('Goto'):
        Goto(line.replace('Goto ', ''))
    elif line.startswith('Menu'):
        Menu(line)
    elif line.startswith('Stop'):
        Stop()
    elif line.startswith('Prompt'):
        Prompt(line.replace('Prompt ', ''))
    
    if not line.startswith('Goto'):
        current_line += 1
