#include "SyntaxChecker.hpp"


using namespace std;


SyntaxChecker::SyntaxChecker() {
    line = 0;
    missingBracketFlag = false;
    missingBracket = '\0';
    expectedBracketFlag = '\0';
    error = 0;
    inBlockComment = false;
}

void SyntaxChecker::checkFile() {
    inputFile();

    if (missingBracketFlag){
        cout << "Missing starting bracket for " << missingBracket << endl;
    } else if (expectedBracketFlag) {
        cout << "Line " << line << ": expected " << expectedBracketFlag << " and found " << error << endl;
    } else if (myStack.isEmpty()){
        cout << "No errors found" << endl;
    } else {
        cout << "Reached end of file: missing " << myStack.pop() << endl;
    }

}


void SyntaxChecker::inputFile(){
    string fileName;
    string currentLine;

    cout << "Please enter a file name: ";
    cin >> fileName;

    ifstream inFile;
    inFile.open(fileName);
    if (!inFile) {
        throw "Error opening " +  fileName + "for reading";
        exit(1);
    }
    cout << fileName << " was read in." << endl;

    while (getline(inFile, currentLine) && !missingBracketFlag && !expectedBracketFlag) {
        cout << "Checking line: " << line << endl;
        checkDelimiters(currentLine);
        line++;
    }
    //myStack.displayStack();
    inFile.close();

    
}

void SyntaxChecker::checkDelimiters(string currentLine) {
    char prev = '\0';
    bool lineCommentFlag = false;
    bool openCommentFlag = false;
    bool quoteFlag = false;
    char current;
    bool notComment;
    for (int i = 0; i < currentLine.length() && !missingBracketFlag && expectedBracketFlag == '\0'; ++i) {
        current = currentLine[i];

        // Check if String, Comment, or Comment Block
        if (current == '"') {
            quoteFlag = true;
        } else if (current == '"' and quoteFlag) {
            quoteFlag = false;
        } else if (prev == '/' && current == '/') {
            lineCommentFlag = true;
        } else if (prev == '/' && current == '*') {
            inBlockComment = true;
        } else if (prev == '*' && current == '/' && inBlockComment) {
            inBlockComment = false;
        } else if (prev == '*' && current == '/' && !inBlockComment) {
            // no starting comment
        }

        // Will check for () {} []
        if (!quoteFlag && !lineCommentFlag && !inBlockComment) {
            if (current == '{' || current == '[' || current == '(') {
                myStack.push(current);
            } else if (current == '}') {
                if (myStack.isEmpty()) {
                    missingBracket = current;
                    missingBracketFlag = true;
                } else if (myStack.stackTop() == '{') {
                    myStack.pop();
                } else {
                    expectedBracketFlag = getExpected(myStack.stackTop());
                    error = current;
                }
            } else if (current == ']') {
                if (myStack.isEmpty()) {
                    missingBracket = current;
                    missingBracketFlag = true;
                } else if (myStack.stackTop() == '[') {
                    myStack.pop();
                } else {
                    expectedBracketFlag = getExpected(myStack.stackTop());
                    error = current;
                }
            } else if (current == ')') {
                if (myStack.isEmpty()) {
                    missingBracket = current;
                    missingBracketFlag = true;
                } else if (myStack.stackTop() == '(') {
                    myStack.pop();
                } else {
                    expectedBracketFlag = getExpected(myStack.stackTop());
                    error = current;
                }
            }
        }
        prev = current;
    }
}

char SyntaxChecker::getExpected(char bracket) {
    char expected;
    if (bracket == '{')
        expected = '}';
    else if (bracket == '}')
        expected = '{';
    else if (bracket == '[')
        expected = ']';
    else if (bracket == ']')
        expected = '[';
    else if (bracket == '(')
        expected = ')';
    else if (bracket == ')')
        expected = '(';
    return expected;
}