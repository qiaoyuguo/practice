/*
 * =====================================================================================
 *
 *       Filename:  stack.cpp
 *
 *    Description:  reverse a sequence of integers read from console.
 *
 *
 * =====================================================================================
 */
#include <iostream>
#include "stack.h"
#include "simpio.h"
#include "console.h"

void input_and_handle()
{
    Stack<int> s;
    cout << "Enter a list of integers, ending with 0:" << endl;
    while(true)
    {
        cout << "? ";
        int tmp;
        cin >> tmp;
        if(tmp == 0)
            break;
        s.push(tmp);
    }
    cout << "Those integers in reverse order are: " << endl;
    while(!s.isEmpty())
    {
        cout << s.pop() << endl;
    }
}
int main()
{
    input_and_handle();
    return 0;
}

