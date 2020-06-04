#include "mystring.h"
#include <iostream>
#include <string.h>

// using namespace std;
using namespace coen79_lab5;
namespace coen79_lab5{

/* Constructor, Copy Constructor, Deconstructor */

// string contains sequence of chars. from the str
string::string(const char str[]){
    current_length = strlen(str);
    allocated = current_length + 1;
    characters = new char[allocated];

    // destination, source, number of chars
    strncpy(characters, str, allocated);
}

// string contains c and null character after
string::string(char c){
    current_length = 1;
    allocated = current_length + 1;
    characters = new char[allocated];
    characters[0] = c;
    // next char set to the universal 0 character
    characters[1] = '\0';
}

// string becomes a copy of source string
string::string(const string& source){
    characters = new char[source.current_length];
    strncpy(characters, source.characters, source.current_length);
    current_length = source.current_length;
    allocated = source.allocated;
}

string::~string() {
    delete [] characters;
    current_length = 0;
    allocated = 0;
}

/* Modification member functions */

// addend is concatenated to the end of the string
void string::operator +=(const string& addend){
    size_t total = current_length + addend.current_length;
    allocated = total + 1;
    reserve(allocated);

    // destination, source, number of characters
    strncat(characters, addend.characters, addend.current_length);
    current_length = total;

}

// addend is concatenated to the end of the string
void string::operator +=(const char addend[]){
    size_t total = current_length + strlen(addend);
    allocated = total + 1;
    reserve(allocated);

    // destination, source, number of characters
    strncat(characters, addend, strlen(addend));
    current_length = total;
}

// single character has been concatenated to the end of the string
void string::operator +=(char addend){
    size_t total = current_length + 1;
    allocated = total + 1;
    reserve(allocated);
    characters[current_length] = addend;
    //  characters[current_length +  1] = NULL;
    current_length = total;
}

// 
string& string::operator =(const string& source){
    this -> dlt(0, current_length);
    if (current_length != source.current_length){
        allocated = source.allocated;
        reserve(allocated);
    }

    strncpy(characters, source.characters, source.current_length);
    current_length = source.current_length;
    return *this;
}

// will allow functions to avoid allocating new memory
void string::reserve(size_t n){
    char *new_chars = new char[n];
    if (characters != NULL){
        strncpy (new_chars, characters, current_length);
        // dereference characters pointer
        delete [] characters;
    }
    characters = new_chars;
}

// source string inserted into given string before the character at the given index position 
void string::insert(const string &source, unsigned int position){
    assert(position <= length());

    char *firstTemp = new char[current_length + source.current_length + 1];
    if (position > 0){
        // destination, source, number of characters
        strncpy(firstTemp, characters, position);
    }
    char *secondTemp = new char[allocated - position];
    int j = 0;
    for (int i = position; i <= current_length; i++, j++){
        secondTemp[j] = characters[i];
    }
    delete [] characters;

    // concatenation
    // destination, source, number of characters
    strncat(firstTemp, source.characters, source.current_length);
    strncat(firstTemp, secondTemp, strlen(secondTemp));
    characters = firstTemp;
    current_length += source.current_length;
    allocated = current_length + 1;

}

// num characters are deleted from the string
void string::dlt(unsigned int position, unsigned int num){
    assert((position + num) <= length());

    for (int i = position; i < length(); i++){
        characters[i] = characters[i + num];
    }
    current_length -= num;
}

// the character at given position is replaced with c
void string::replace(char c, unsigned int position){
    assert(position < length());
    // replace the character at specified position
    characters[position] = c;
}

// characters at given position replaced with those in source
void string::replace(const string& source, unsigned int position){
    assert( (position + source.current_length) <= length() );
    int j = 0;
    for (int i = position; i < (position + source.length()); i++){
        *(characters + i) = source[j++];
    }
}


// Constant member functions

// value returned is character at specified position 
//      length is 0 --> length()-1s
char string::operator [](size_t position) const{
    assert (position < length());
    return characters[position];
}

// location of first 'c' is returned, -1 if not there
int string::search(char c) const{
    int theIndex = -1;
    for (int i = 0; i < length(); i++){
        if (c == characters[i]){
            return i;
        }
    }
    return theIndex;
}

// returns the index of the start of the given substring, -1 if not in there
int string::search(const string &substring) const{
    int theIndex = -1;
    // str str if substring of chars exist in og chars, and returns which substring does 
    char *theTemp = strstr(characters, substring.characters);
    if (theTemp != NULL){
        theIndex = *theTemp - *characters;
    }
    return theIndex;
}

// returns the number of char within the string
unsigned int string::count(char c) const{
    unsigned int numOfChars = 0;
    for (int i = 0; i < length(); i++){
        if (characters[i] == c){
            numOfChars++;
        }
    }
    return numOfChars;
}


// Friend functions

// 
 std::ostream& operator <<(std::ostream &outs, const string &source){
    outs << source.characters;
    return outs;
}

 bool operator ==(const string &s1, const string &s2){
    // boolean check if two strings are deep equal
    return (strcmp(s1.characters, s2.characters) == 0);
}

 bool operator !=(const string &s1, const string &s2){
    return (strcmp(s1.characters, s2.characters) != 0);
}   

 bool operator > (const string &s1, const string &s2){
    return (strcmp(s1.characters, s2.characters) > 0);
}

 bool operator < (const string &s1, const string &s2){
    return (strcmp(s1.characters, s2.characters) < 0);
}

 bool operator >=(const string &s1, const string &s2){
    return ( (s1 > s2) || (s1 == s2) );
}

 bool operator <=(const string &s1, const string &s2){
    return ( (s1 < s2) || (s1 == s2) );
}


// Non-member functions 
string operator +(const string &s1, const string &s2){
    string temp;
    temp.reserve(s1.length() + s2.length() + 1);
    temp += s1;
    temp += s2;
    return temp;
}

string operator +(const string &s1, const char addend[]){
    string temp;
    temp.reserve(s1.length() + strlen(addend) +  1);
    temp += s1;
    temp += addend;
    return temp;
}

std::istream& operator >> (std::istream &ins, string &target){
    while  (ins && isspace(ins.peek())){
        ins.ignore();
    }
    char *cinput = new char[500];
    ins >> cinput;
    target = string(cinput);
    return ins;
}


} // namespace end