#ifndef _SYNTAX_CHECKER_HPP_
#define _SYNTAX_CHECKER_HPP_

#include "GenStack.hpp"

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class SyntaxChecker {
    private:
        int line;
        bool missingBracketFlag;
        char missingBracket;
        char expectedBracketFlag;
        char error;
        bool inBlockComment;
        GenStack<char> myStack;

    public:
        SyntaxChecker();
        void inputFile();
        void checkDelimiters(string currentLine);
        char getExpected(char bracket);
        void checkFile();

};


#endif