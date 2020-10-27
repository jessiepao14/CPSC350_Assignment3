#ifndef _SYNTAX_CHECKER_HPP_
#define _SYNTAX_CHECKER_HPP_

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class SyntaxChecker {
    private:
        int line;
        bool missingBracketFlag;
        char expectedBracketFlag;
        char error;

    public:
        SyntaxChecker();
        int inputFile(); 
        bool checkDelimiters(string currentLine);
        char getExpected(char bracket);
        void checkFile();

};


#endif