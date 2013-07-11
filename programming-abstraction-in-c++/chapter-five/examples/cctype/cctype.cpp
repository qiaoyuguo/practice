/*
 * =====================================================================================
 *
 *       Filename: cctype.cpp
 *
 *    Description: This program simulates the <cctype> interface using
 *    set of characters.
 *
 * =====================================================================================
 */

#include <string>
#include "set.h"
#include "cctype.h"
using namespace std;

/* Function prototypes  */

Set<char> setFromString(string str);

/*
 * Constant sets
 * --------------
 * These sets are initialized to contain the characters in the
 * corresponding character class.
 * */
const Set<char> DIGIT_SET = setFromString("0123456789");
const Set<char> LOWER_SET = setFromString("abcdefghijklmnopqrstuvwxyz");
const Set<char> UPPER_SET = setFromString("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
const Set<char> PUNCT_SET = setFromString("!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}");
const Set<char> SPACE_SET = setFromString(" \t\v\f\n\r");
const Set<char> XDIGIT_SET = setFromString("0123456789ABCDEFabcdef");
const Set<char> ALPHA_SET = LOWER_SET + UPPER_SET;
const Set<char> ALNUM_SET = ALPHA_SET + DIGIT_SET;
const Set<char> PRINT_SET = ALNUM_SET + PUNCT_SET + SPACE_SET;

/* Exported Function  */
bool isalnum(char ch) {return ALNUM_SET.contains(ch);}
bool isalpha(char ch) {return ALPHA_SET.contains(ch);}
bool isdigit(char ch) {return DIGIT_SET.contains(ch);}
bool islower(char ch) {return LOWER_SET.contains(ch);}
bool isprint(char ch) {return PRINT_SET.contains(ch);}
bool ispunct(char ch) {return PUNCT_SET.contains(ch);}
bool isspace(char ch) {return SPACE_SET.contains(ch);}
bool isupper(char ch) {return UPPER_SET.contains(ch);}
bool isxdigit(char ch) {return XDIGIT_SET.contains(ch);}

/* Helper function to create a set from a string of characters  */

Set<char> setFromString(string str) {
    Set<char> set;
    for(int i = 0; i < str.length(); i++)
        set.add(str[i]);
    return set;
}

