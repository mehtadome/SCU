#ifndef STATS_H
#define STATS_H
#include <iostream>
#include <vector>

namespace coen79_lab2 {
//class definition...
using std::vector;

class statistician{
    public: 
        void next(double value);
        void printSequence();
        int length() const;
        double sum() const;
        double mean()  const;
        double minimum() const;
        double maximum() const;
        void reset();
        double accessElement(int index) const;

        friend statistician operator +(const statistician& s1, const statistician& s2);
        friend statistician operator *(double scale, const statistician& s);
        
    private: 
        // private vector holding sequence of doubles
        vector <double> mySequence;
        // counter variable to keep track of length
        int counter = 0;
        // private sum to keep track
        double mySum = 0.0;
        // private mean
        double myMean;
        // private vars min and max to keep track 
        double myMin;
        double myMax;
};
    // Non class function
    bool operator ==(const statistician& s1, const statistician& s2);
}

#endif 