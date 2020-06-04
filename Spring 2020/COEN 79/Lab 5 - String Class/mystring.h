#ifndef mystring_h
#define mystring_h

#include <iostream>
#include <cstdlib>

namespace coen79_lab5 {

class string {

public:
    // Constructor, Copy Constructor, Deconstructor
    string(const char str[] = "");
    string(char c);
    string(const string& source);
    ~string();

    // Modification member functions
    void operator +=(const string& addend);
    void operator +=(const char addend[]);
    void operator +=(char addend);
    void reserve(size_t n);
    string& operator =(const string& source);
    void insert(const string &source, unsigned int position);
    void dlt(unsigned int position, unsigned int num);
    void replace(char c, unsigned int position);
    void replace(const string& source, unsigned int position);

    // Constant member functions
    size_t length() const { return current_length; }
    char operator [](size_t position) const;
    int search(char c) const;
    int search(const string &substring) const;
    unsigned int count(char c) const;

    // Friend functions
    friend std::ostream& operator <<(std::ostream &outs, const string &source);
    friend bool operator ==(const string &s1, const string &s2);
    friend bool operator !=(const string &s1, const string &s2);
    friend bool operator > (const string &s1, const string &s2);
    friend bool operator < (const string &s1, const string &s2);
    friend bool operator >=(const string &s1, const string &s2);
    friend bool operator <=(const string &s1, const string &s2);


private:
    char *characters;
    size_t allocated;
    size_t current_length;

};

// Non-member functions 
string operator +(const string &s1, const string &s2);
string operator +(const string &s1, const char addend[]);
std::istream& operator >> (std::istream &ins, string &target);

}

#endif