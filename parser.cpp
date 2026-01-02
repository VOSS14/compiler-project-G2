#include <iostream>
#include <vector>
#include <string>
#include <stack>

using namespace std;

// --- GLOBAL VARIABLES ---
string input;
int pos = 0;

// --- TASK 1: RECURSIVE DESCENT FUNCTIONS ---
bool B_Recursive() {
    if (pos < input.length() && input[pos] == 'b') {
        pos++;
        return B_Recursive();
    }
    return true; // Epsilon case
}

bool A_Recursive() {
    if (pos < input.length() && input[pos] == 'a') {
        pos++; // Match first 'a'
        if (B_Recursive()) {
            if (pos < input.length() && input[pos] == 'a') {
                pos++; // Match last 'a'
                return true;
            }
        }
    }
    return false;
}

// --- TASK 2: FIXED LALR SIMULATION ---
void simulateLALR(string str) {
    stack<int> s;
    s.push(0); 
    str += "$"; 
    int i = 0;

    cout << "\n--- LALR Parsing Trace ---" << endl;
    cout << "Step\tStack\t\tInput\tAction" << endl;

    while (i < str.length()) {
        int state = s.top();
        char symbol = str[i];

        if (state == 0 && symbol == 'a') {
            cout << i << "\t[0]\t\t" << str.substr(i) << "\tShift S1" << endl;
            s.push(1); i++;
        } else if (state == 1 && symbol == 'b') {
            cout << i << "\t[0, 1]\t\t" << str.substr(i) << "\tShift S2" << endl;
            s.push(2); i++;
        } else if (state == 2 && symbol == 'b') {
            cout << i << "\t[0, 1, 2]\t" << str.substr(i) << "\tShift S2" << endl;
            s.push(2); i++;
        } else if ((state == 1 || state == 2) && symbol == 'a') {
            cout << i << "\t[0...]\t\t" << str.substr(i) << "\tShift S3" << endl;
            s.push(3); i++;
        } else if (state == 3 && symbol == '$') {
            cout << i << "\t[0...3]\t\t$\tACCEPT" << endl;
            cout << "\nLALR SUCCESS: String fully parsed." << endl;
            break;
        } else {
            cout << "\nLALR ERROR: Invalid sequence at '" << symbol << "'" << endl;
            break;
        }
    }
}

// --- MAIN EXECUTION ---
int main() {
    cout << "=== Compiler Project Group G2 ===" << endl;
    cout << "Enter string (e.g., abba): ";
    cin >> input;

    // Run Task 1
    pos = 0;
    if (A_Recursive() && pos == input.length()) {
        cout << "\n1. RECURSIVE DESCENT: SUCCESS" << endl;
    } else {
        cout << "\n1. RECURSIVE DESCENT: FAILED" << endl;
    }

    // Run Task 2
    simulateLALR(input);

    return 0;
}
