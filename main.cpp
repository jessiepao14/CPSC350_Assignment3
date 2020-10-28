#include <iostream>
#include <string>

#include "SyntaxChecker.hpp"

using namespace std;

void welcome();
bool isRepeat();

int main(int argc, char const *argv[])
{
    bool error;
    SyntaxChecker check;
    welcome();
    
    do {
        error = check.checkFile(argv[1]);
    } while (error && isRepeat());

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

