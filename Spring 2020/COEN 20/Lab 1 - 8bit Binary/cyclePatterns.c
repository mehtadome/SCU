#include <stdint.h>
#include <stdbool.h>
#include <math.h>

/* Bits2Unsigned

Multiplies 2^n against the element and adds to result
    + equation is such: (b0 * 2^0) + (b1 * 2^1) ... + (b7 * 2^7)
*/
uint32_t Bits2Unsigned(int8_t bits[8]) {

    int n, temp, result;
    n = 0;
    result = 0;
    temp = 0;

    for (int i = 0; i <= 7; i++) {
        temp = (int)pow(2, n);
        
        result = result + bits[i] * temp;
        n = n + 1;
    }
    return result;
} 

/* Bits2Signed

Calls Bits2Unsigned method and works with number 
    + If >127, it is negative and use difference to get Signed Number
    + If <=127, it is positive and simply return
*/
int32_t Bits2Signed(int8_t bits[8]) {
    int unsignedNum, difference, signedNum;

    // Get the unsigned version of the number
    unsignedNum = Bits2Unsigned(bits);
    // check if number > 128
    if (unsignedNum > 127){
        difference = unsignedNum - 128;
        signedNum = -128 + difference;

        return signedNum;
    } else {
        // return number if <=127 since it must be positive
        return unsignedNum;
    }
}

/* Increment 

Increments by 1.
    + If the element is a 1, it becomes 0
    + If the element is a 0, it becomes 1 and breaks
*/
void Increment(int8_t bits[8]) {
    for (int i = 0; i <= 7; i++){
        // if it's a 0, add the increment/carry over and break
        if (bits[i] == 0) {
            bits[i] = 1;
            break;
        // meaning bits[i] is 1
        } else {
            bits[i] = 0;
        }
    }
}

/* Unsigned2Bits

Uses modulus to determine whether odd or even at division
    + If odd, the binary digit is 1
    + If even, the binary digit is 0
*/
void Unsigned2Bits(uint32_t n, int8_t bits[8]) {
    for (int i = 0; i <= 7; i++){
        if (n % 2 == 1){
            bits[i] = 1;
        } else {
            bits[i] = 0;
        }
        n = (int)floor(n/2);
    }
}