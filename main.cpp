#include <iostream>
#include <string>

#include "SyntaxChecker.hpp"

using namespace std;

void welcome();
bool isRepeat();
string getFileName();

int main(int argc, char const *argv[])
{
    bool error;
    string fileName;
    SyntaxChecker check;
    welcome();
    
    error = check.checkFile(argv[1]);
    while (error && isRepeat()) {
        fileName = getFileName();
        error = check.checkFile(fileName);
    }

    return 0;
}

void welcome() {
    cout << "~~~~~~~ Welcome to Syntax Checker ~~~~~~~\n\n" << endl;
}

bool isRepeat() {
    char answer;
    cout << "Would you like to process another file? (y or n)" << endl;
    cin >> answer;
    if (answer == 'y' || answer == 'Y') {
        return true;
    }
    return false;
}

string getFileName() {
    string fileName;
    cout << "Please enter the file you would like to check: " << endl;
    cin >> fileName;
    return fileName;
}


