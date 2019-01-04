#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <unistd.h>
#include <limits>


using namespace std;

const string chars = "abcdefghijklmnopqrstuvwxy";


void spawn_shell() {
    char* args[] = {(char*)"/bin/bash", NULL};
    execve("/bin/bash", args, NULL);
}
  

void print_menu() {
    cout << endl;
    cout << "Enter the command you want to execute:" << endl;
    cout << "[1] swap <index1> <index2>                   (Cost: 1)" << endl;
    cout << "[2] replace <char1> <char2>                  (Cost: 1)" << endl;
    cout << "[3] print                                    (Cost: 1)" << endl;
    cout << "[4] quit                                              " << endl;
    cout << "> ";
}

void play() {
    string from(10, '\00');
    string to(10, '\00');
    for (int i = 0; i < 10; ++i) {
        from[i] = chars[rand() % (chars.length() - 1)];
        to[i] = chars[rand() % (chars.length() - 1)];
    }


    cout << "Perform the following operations on String1 to generate String2 with minimum costs." << endl << endl;
    cout << "[1] swap <index1> <index2>                   (Cost: 1)" << endl;
    cout << "    Swaps the char at index1 with the char at index2  " << endl;
    cout << "[2] replace <char1> <char2>                  (Cost: 1)" << endl;
    cout << "    Replaces the first occurence of char1 with char2  " << endl;
    cout << "[3] print                                    (Cost: 1)" << endl;
    cout << "    Prints the current version of the string          " << endl;
    cout << "[4] quit                                              " << endl;
    cout << "    Give up and leave the game                        " << endl;
    cout << endl;
    cout << "String1: " << from << endl;
    cout << "String2: " << to << endl;
    cout << endl;
        
    unsigned int costs = 0; 
    string s(from);

    while (true) {
        print_menu();

        string command;
        cin >> command;

        if (command == "swap") {  // exchange by itself
            unsigned int i1, i2;
            cin >> i1 >> i2;
            if (cin.good() && i1 < s.length() && i2 < s.length()) { // negative will break
                swap(s[i1], s[i2]);
            }
            costs += 1;
        } else if (command == "replace") { // replace by another 
            char c1, c2;
            cin >> c1 >> c2;
            auto index = s.find(c1);
            cout << c1 << c2 << index << endl;
            if (index >= 0) {
                s[index] = c2;
            }
            costs += 1;
        } else if (command == "print") { //origin 
            cout << s << endl;
            costs += 1;
        } else if (command == "quit") {
            cout << "You lost." << endl;
            break;
        } else {
            cout << "Invalid command" << endl;
        }

        if (!cin) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        if (!cout) {
            cout.clear();
        }

        if (s == to) {
            cout << s.length() << endl;
            cout << endl;
            cout << "****************************************" << endl;
            cout << "* Congratulations                       " << endl;
            cout << "* You solved the problem with cost: " << costs << endl;
            cout << "****************************************" << endl;
            cout << endl;
            break;
        }
    }
}




int main() {
    srand(time(nullptr));

    play();
}



/**
0x7fffffffda80 --> 0x7fffffffda90 ("vrnciexoex")
0016| 0x7fffffffda50 --> 0x0 
0024| 0x7fffffffda58 --> 0xffffffecffffffec 
0032| 0x7fffffffda60 --> 0x7fffffffda70 --> 0x70617773 ('swap')
0040| 0x7fffffffda68 --> 0x4 
0048| 0x7fffffffda70 --> 0x70617773 ('swap')
0056| 0x7fffffffda78 --> 0x30782f3030782f ('/x00/x0')
0064| 0x7fffffffda80 --> 0x7fffffffda90 ("vrnciexoex")    # this is the pointer 1 , replace entrance
0072| 0x7fffffffda88 --> 0xa ('\n')
0080| 0x7fffffffda90 ("vrnciexoex")
0088| 0x7fffffffda98 --> 0x7865 ('ex')
0096| 0x7fffffffdaa0 --> 0x7fffffffdab0 ("qtglfvtocx")    # this is the pointer 2
0104| 0x7fffffffdaa8 --> 0xa ('\n')
0112| 0x7fffffffdab0 ("qtglfvtocx")
0120| 0x7fffffffdab8 --> 0x7863 ('cx')
0128| 0x7fffffffdac0 --> 0x7fffffffdad0 ("vrnciexoex")
0136| 0x7fffffffdac8 --> 0xa ('\n')
0144| 0x7fffffffdad0 ("vrnciexoex")
0152| 0x7fffffffdad8 --> 0x7865 ('ex')
0160| 0x7fffffffdae0 --> 0x2 
0168| 0x7fffffffdae8 --> 0x0 
0176| 0x7fffffffdaf0 --> 0x4024e0 (<__libc_csu_init>:   push   r15)
0184| 0x7fffffffdaf8 --> 0x4010c0 (<_start>:    xor    ebp,ebp)

*/