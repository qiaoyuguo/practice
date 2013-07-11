/*
 * =====================================================================================
 *
 *       Filename:  roll.cpp
 *
 *    Description:  simulate roll(n,k) function in postscript, which 
 *    looply rotates the top n elements k times(with top element rotate 
 *    first
 *
 *
 * =====================================================================================
 */
#include <iostream>
#include "stack.h"
#include "queue.h"
//#include "console.h"

Stack<char> createStack(string str)
{
    Stack<char> s;
    int len = str.length();
    for(int i = 0; i < len; i++)
    {
        s.push(str.at(i));
    }
    return s;
}
// roll([D C B A], 4, 1) -> [C B A D]
// roll([D C B A], 3, 2) -> [B D C A]
// roll([D C B A], 2, 4) -> [D C B A])
Stack<char> roll(Stack<char> & stack, int n, int k)
{
    int size = stack.size();
    int i;
    if(k < 0 || n < 0 || n > size)
    {
        error("roll: argument out of range");
        return stack;
    }

    if(k > n) 
        k = k % n;
    if(k == 0 || n == 0)
        return stack;

    Stack<char>  headStack; // a  helper stack to contain the rotated k element
    for(i = 0; i < k; i++)
    {
        headStack.push(stack.pop());
    }

    Stack<char> midStack; // a helper Stack to contain the middle unchanged element
    for(; i < n; i++)
    {
        midStack.push(stack.pop());
    }

    while(! headStack.isEmpty())
    {
        stack.push(headStack.pop());
    }
    while(! midStack.isEmpty())
    {
        stack.push(midStack.pop());
    }

    return stack;
}

void core_handle(string str, int n, int k)
{
    cout << "for string " << str << endl;
    Stack<char> s = createStack(str);
    cout << s.toString() << endl;
    roll(s, n, k);
    cout << s.toString() << endl << endl;
}

int main(void)
{
    core_handle("ABCD", 4, 1);
    core_handle("ABCD", 3, 2);
    core_handle("ABCD", 2, 4);

    return 0;
}

