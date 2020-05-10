#include "poly.h"
#include <cassert>
#include <cmath>
#include <fstream>



namespace coen79_lab4 {

// polynomial created with all zero coefficients
polynomial::polynomial(double c, unsigned int exponent){
    assert(exponent <= MAXIMUM_DEGREE);
    for (int i = 0; i < CAPACITY; ++i){
        numbers[i] = 0;
    }
    numbers[exponent] = c;
}

// sets coefficient for exponent
void polynomial::assign_coef(double coefficient, unsigned int exponent){
    assert(exponent<=MAXIMUM_DEGREE);
    numbers[exponent] = coefficient;
}

// add to coefficient for exponent wanted
void polynomial::add_to_coef(double amount, unsigned int exponent){
    assert(exponent <= MAXIMUM_DEGREE);
    numbers[exponent] += amount;
}

void polynomial::clear(){
    polynomial(0.0, 0.0);
}

// return antiderivsative to the polynomial
polynomial polynomial::antiderivative() const{
    assert(degree() < MAXIMUM_DEGREE);

    polynomial anti(0, 0);
    anti.numbers[0] = 0;

    for (int i = 0; i < MAXIMUM_DEGREE; ++i){
        anti.numbers[i+1] = (numbers[i] / (i + 1));
    }
    return anti;
}

// return coefficient at specified exponent
double polynomial::coefficient(unsigned int exponent) const{
    if (exponent > MAXIMUM_DEGREE){
        return 0;
    } else {
        return numbers[exponent];
    }
}

// returns value of integral from x0-->x1
double polynomial::definite_integral(double x0, double x1) const{
    polynomial anti;
    anti = antiderivative();

    double top = 0.0;
    double bottom = 0.0;
    for (int i = 0; i < MAXIMUM_DEGREE; ++i){
        // sum of upper and lower bound
        top += (anti.numbers[i] *  pow(x0, i));
        bottom += (anti.numbers[i] *  pow(x1, i));
    }
    return top - bottom;
}

// returns value of largest exponent
unsigned int polynomial::degree() const{

    for (int i = CAPACITY-1; i >= 0; --i){
        if (numbers[i] != 0){
            return i;
        }

    }
    return 0;
}

// return first derivative of the polynomial
polynomial polynomial::derivative() const{
    polynomial deriv;
    for (int i = 1; i < MAXIMUM_DEGREE; ++i){
        // derivative equation
        deriv.numbers[i-1] = (numbers[i] * i);
    }
    return deriv;
}

// return valye for x
double polynomial::eval(double x) const{
    for (int i = 0; i < CAPACITY; ++i){
        if (x == numbers[i]){
            return numbers[i];
        }
    }
    return NULL;
}

// returns true if entire polynomial is zero
bool polynomial::is_zero() const{
    for (int i = 0; i < MAXIMUM_DEGREE; ++i){
        if (numbers[i] != 0){
            return false;
        }
    }
    return true;
}

// returns next term larger than e
unsigned int polynomial::next_term(unsigned int e) const{
    for (int i = e+1; e < CAPACITY; ++i){
        if (numbers[i] != 0){
            return i;
        }
    }
    return 0;
}

// returns next term smaller than e
unsigned int polynomial::previous_term(unsigned int e) const{
    for (int i = e-1; e >= 0; --i){
        if (numbers[i] != 0){
            return i;
        }
    }
    return 0;
}

// Overloads
double polynomial::operator() (double x) const{
    return eval(x);
}

polynomial operator +(const polynomial &p1, const polynomial  &p2){
    polynomial finished;
    for (int i = 0; i < polynomial::CAPACITY; ++i){
        finished.numbers[i] = (p1.numbers[i] + p2.numbers[i]);
    }
    return finished;
}

polynomial operator -(const polynomial &p1, const polynomial  &p2){
    polynomial finished;
    for (int i = 0; i < polynomial::CAPACITY; ++i){
        finished.numbers[i] = p1.numbers[i] - p2.numbers[i];
    }
    return finished;
}

polynomial operator *(const polynomial &p1, const polynomial  &p2){
    assert(p1.degree() + p2.degree() <= polynomial::MAXIMUM_DEGREE);
    polynomial finished;
    for (int i = 0; i < polynomial::CAPACITY; ++i){
        for (int j = 0; j < polynomial::CAPACITY; ++j){
        
            finished.numbers[i+j] += (p1.numbers[i] * p2.numbers[j]); 
        }
    }
    return finished;
}


std::ostream& operator <<(std::ostream& out, const polynomial &p){

    for (int i = p.degree(); i >= 0; --i){

        // if block for positive coefficinets
        if (p.numbers[i] > 0 && i != p.degree()){

            if (i > 1){
                out << "+ " << p.numbers[i]  << "x^" << i << " ";
            } else if (i == 1){
                out << "+ " << p.numbers[i] << "x" << " ";
            } else if (i == 0){
                out << "+ " << p.numbers[i];
            }

        } else if (p.numbers[i] > 0 && i == p.degree()){
            if (i > 1){
                out << p.numbers[i] << "x^" << i << " ";
            } else if (i == 1){
                out << p.numbers[i] << "x" << " ";
            } else if (i == 0){
                out << p.numbers[i];
            }
        } 

        // if block for negative coefficients
        if (p.numbers[i] < 0 && i != p.degree()){

            if (i > 1){
                out << "- " << abs(p.numbers[i])  << "x^" << i << " ";
            } else if (i == 1){
                out << "- " << abs(p.numbers[i]) << "x" << " ";
            } else if (i == 0){
                out << "- " << abs(p.numbers[i]);
            }

        } else if (p.numbers[i] < 0 && i == p.degree()){
            if (i > 1){
                out << p.numbers[i] << "x^" << i << " ";
            } else if (i == 1){
                out << p.numbers[i] << "x" << " ";
            } else if (i == 0){
                out << p.numbers[i];
            }
        } 

    } 
    return out;     
}

} // namespace
