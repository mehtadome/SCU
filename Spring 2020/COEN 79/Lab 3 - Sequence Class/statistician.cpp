#include <cassert>
#include <iostream>

#include "statistician.h"


using namespace std;
using namespace coen79_lab2;
namespace coen79_lab2 {

// next stores another value in the sequence
void statistician::next(double value) {
    mySequence.push_back(value);

    // sum
    mySum += value;

    // if first iteration, max and min equal first value
    if (counter == 0){
        myMin = value;
        myMax = value;
    } else {
        // if the value less than current minimum, swap
        if (value < myMin){
            myMin = value;
        // else if greater than current maximum, swap
        } else if (value > myMax){
            myMax = value;
        }
    }

    // length
    counter += 1;
}

// debugging method for myself
void statistician::printSequence() {
    // if empty, don't print anything
    if (counter == 0){
    cout << "Sequence is empty." << endl;
    } else {
        cout << "Printing Sequence" << endl;
        for(int i = 0; i < counter; i++) {
            cout << mySequence[i] << endl;
        }
    }
}

int statistician::length() const{
    // length calculated in next()
    return counter;
}

double statistician::sum() const{
    // sum calculated in next()
    return mySum;
}

double statistician::mean() const{
    // void division by 0
    if (counter == 0){
        return 0;
    } else {
        return mySum/counter;
    }
}

double statistician::minimum() const{
    if (counter == 0){
        cout << "Sequence is empty, no minimum." << endl;
    } else {
        // calculated in next()
        return myMin;
    }
}

double statistician::maximum() const{
    if (counter == 0){
        cout << "Sequence is empty, no maximum." << endl;
    } else {
        // calculated in next()
        return myMax;
    }
}

void statistician::reset(){
    mySequence.clear();
    // reset all variables
    counter = 0;
    mySum = 0;
    myMean = 0;
    myMin = 0;
    myMax = 0;
}

// return the current element at in the vectors sequence
double statistician::accessElement(int index) const{
    return mySequence[index];
}

// overloading stuff:
// + overload returns all #s of both sequences
statistician operator +(const statistician& s1, const statistician& s2){
  // create new statistician
  statistician s3;

  // loop through s1
  for (int i = 0; i < s1.length(); i++){
    s3.next( s1.accessElement(i) );
  }

  // loop through s2
  for (int i = 0; i < s2.length(); i++){
    s3.next( s2.accessElement(i) );
  }
  
  return s3;
}

// *  overload returns sequence of scaled #s
statistician operator *(double scale, const statistician& s){
    statistician s4;
    for (int i = 0; i < s.length(); ++i){
        s4.next( s.accessElement(i) * scale );
    }
    // s.reset()
    return s4;
}

// == overload returns true if lengths equal
bool operator ==(const statistician& s1, const statistician& s2){
  return (s1.length() == s2.length() );
}

} // end of namespace