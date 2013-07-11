/*
 * =====================================================================================
 *
 *       Filename:  BracketMatch.cpp
 *
 *    Description:  check if all the bracketing operators(parentheses, brackets, and curly braces) is matched.
 *
 *
 * =====================================================================================
 */
#include <iostream>
#include "stack.h"
//#include "console.h"
//
//
bool isBracket(char c)
{
    return (c == '{' || c == '}' || c == '('
          || c == ')' || c == '[' || c == ']');
}
bool isMatch(char src, char dst)
{
    return ((src == '[' && dst == ']')
           || (src == '(' && dst == ')')
           || (src == '{' && dst == '}'));
    
}
bool checkMatch(string input_str)
{
    Stack<char> s;
    int len = input_str.length();
    for(int i = 0; i < len; i++)
    {
        char c = input_str.at(i);
        if( isBracket(c) )
        {
            if(s.isEmpty())
                s.push(c);
            else if(isMatch(s.peek(), c))
                s.pop();
            else
                s.push(c);
        }
    }
    if(s.isEmpty())
        return true;
    else
        return false;

}
void printResult(string s)
{
    cout << "'" << s << "'" << " is " << (checkMatch(s) ? "matched" : "not matched") << endl;
}

int main(void)
{
    string s1 = "{int i = 3*(4+5), a[2] = 3}";
    string s2 = "(([])";
    string s3 = ")(";
    string s4 = "{(})";

    printResult(s1);
    printResult(s2);
    printResult(s3);
    printResult(s4);
}

