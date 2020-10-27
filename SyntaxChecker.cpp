#include "SyntaxChecker.hpp"
#include "GenStack.hpp"

using namespace std;


SyntaxChecker::SyntaxChecker() {
    line = 0;
    missingBracketFlag = false;
    expectedBracketFlag = '\0';
    error = 0;
}

void SyntaxChecker::checkFile() {
    inputFile();

    if (error == 'e') {
        cout << "No errors found" << endl;
    }
}


int SyntaxChecker::inputFile(){
    string fileName;
    string currentLine;
    int line = 0;

    cout << "Please enter a file name: ";
    cin >> fileName;

    ifstream inFile;
    inFile.open(fileName);
    if (!inFile) {
        throw "Error opening " +  fileName + "for reading";
        exit(1);
    }
    cout << fileName << " was read in." << endl;

    while(getline(inFile, currentLine)) {
        cout << "Checking line: " << line << endl;
        if (!checkDelimiters(currentLine)){     // check delimiters
            return line;
        }
        line++;
    }

    inFile.close();

}

bool SyntaxChecker::checkDelimiters(string currentLine) {
    GenStack<char> myStack;
    bool commentFlag = false;
    bool quoteFlag = false;
    char current;

    for (int i = 0; i < currentLine.length(); ++i) {
        current = currentLine[i];

        if(current == '/') {
            commentFlag = true;
            return true;
        } else if (commentFlag && current == '/'){
            return true;
        } else if (commentFlag && current == '*') {
            // idk what to do with comment block
        } else if (current == '"') {
            quoteFlag = true;
        } else if (quoteFlag && current == '"') {
            quoteFlag = false;
        } else {
            if (current == '{' || current == '[' || current == '(') {
                myStack.push(current);
            } else if (current == '}') {
                if (myStack.isEmpty()){
                    missingBracketFlag = true;
                    return false;
                } else if (myStack.stackTop() != '{') {
                    expectedBracketFlag = getExpected(myStack.pop());
                    return false;
                }
            } else if (current == ']') {
                if (myStack.isEmpty()){
                    missingBracketFlag = true;
                    return false;
                } else if (myStack.stackTop() != '[') {
                    expectedBracketFlag = getExpected(myStack.pop());
                    return false;
                }
            } else if (current == ')'){
                if (myStack.isEmpty()){
                    missingBracketFlag = true;
                    return false;
                } else if (myStack.stackTop() != '(') {
                    expectedBracketFlag = getExpected(myStack.pop());
                    return false;
                }
            }
        }
        return true;
    }
    if (myStack.isEmpty())
        error = 'e';
    else if (myStack.pop() == '{')
        error = '}';
    else if (myStack.pop() == '[')
        error = ']';
    else if (myStack.pop() == '(')
        error = ')';
}

char SyntaxChecker::getExpected(char bracket) {
    if (bracket == '{')
        return '}';
    else if (bracket == '}')
        return '{';
    else if (bracket == '[')
        return ']';
    else if (bracket == ']')
        return '[';
    else if (bracket == '(')
        return ')';
    else if (bracket == ')')
        return '(';
}