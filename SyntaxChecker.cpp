#include "SyntaxChecker.hpp"


using namespace std;

/**************************
 * SyntaxChecker()
 * Default constructor
 * initializes all of the variables
 **************************/
SyntaxChecker::SyntaxChecker() {
    line = 0;
    missingBracketFlag = false;
    missingBracket = '\0';
    expectedBracketFlag = '\0';
    error = 0;
    inBlockComment = false;
}

/**************************
 * checkFile(string fileName)
 * receives a file and processes the 
 * files to find errors
 **************************/
bool SyntaxChecker::checkFile(string fileName) {
    inputFile(fileName);

    if (missingBracketFlag){
        cout << "Missing starting bracket for " << missingBracket << endl;
        return false;
    } else if (expectedBracketFlag) {
        cout << "Line " << line << ": expected " << expectedBracketFlag << " and found " << error << endl;
        return false;
    } else if (myStack.isEmpty()){
        cout << "No errors found" << endl;
        return true;
    } else {
        cout << "Reached end of file: missing " << myStack.pop() << endl;
        return false;
    }

}

/**************************
 * inputFile(string fileName)
 * receives a file and passes each line to get
 * checked for delimiters
 **************************/
void SyntaxChecker::inputFile(string fileName){
    string currentLine;

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
/**************************
 * checkDelimiters(string currentLine)
 * gets a line and parses through each character
 * to determine if the character is a delimiter
 * if it is an open delimiter it pushes the char to the stack
 * if it is a matching closing delimiter it pops the opening delimiter out of the stack
 * otherwise it processes the error
  **************************/
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
/**************************
 * getExpected(char bracket)
 * returns the matching bracket
**************************/
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