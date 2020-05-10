#ifndef polynomial_h
#define polynomial_h
#include <iostream>
#include <cstdlib>

namespace coen79_lab4{

class polynomial {

public:
    static const unsigned int MAXIMUM_DEGREE = 29;
    static const size_t CAPACITY = 30;

    void update_current_degree();

    // variables c & e
    polynomial(double c = 0.0, unsigned int exponent = 0);

    void assign_coef(double coefficient, unsigned int exponent);
    void add_to_coef(double amount, unsigned int exponent);

    void clear();

    polynomial antiderivative() const;
    double coefficient(unsigned int exponent) const;
    double definite_integral(double x0, double x1) const;
    unsigned int degree() const;
    polynomial derivative() const;
    double eval(double x) const;
    bool is_zero() const;
    unsigned int next_term(unsigned int e) const;
    unsigned int previous_term(unsigned int e) const;

    // Constants
    double operator() (double x) const;

    friend polynomial operator +(const polynomial &p1, const polynomial  &p2);
    friend polynomial operator -(const polynomial &p1, const polynomial  &p2);
    friend polynomial operator *(const polynomial &p1, const polynomial  &p2);
    friend std::ostream& operator <<(std::ostream& out, const polynomial &p);

private:
    double numbers[CAPACITY];
};


}

#endif