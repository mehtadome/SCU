.syntax unified
.cpu    cortex-m4
.text

// Q16  Q16Divide (Q16 dividend, Q16 divisor)
                .global     Q16Divide
                .thumb_func
                .align

Q16Divide: 
    // R0 = dividend (32 int), R1 = divisor (16 int)

    // (int32_t) (dividend ^ divisor) 
    EOR R3,R0,R1    // R3 = sign

    // if < 0, change the sign, taking the 2s complemenet

    // if  (dividend <  0)
    EOR R2,R0,R0, ASR 31
    ADD R0,R2,R0, LSR 31

    // if (divisor < 0)
    EOR R2,R1,R1, ASR 31
    ADD R1,R2,R1, LSR 31

    SDIV R2,R0,R1    // R2 = quotient
    MLS  R0,R2,R1,R0    // R0 = remainder
    
    .rept 16 

    LSL R2,R2, 1 // quotient << 1
    LSL R0,R0, 1 // remainder << 1

    CMP R0,R1   // if (remainder >= divisor)
    ITT  HS    
    SUBHS R0,R0,R1  // remainder -= divisor
    ADDHS R2,R2,1   // quotient++

    .endr

    // if (sign < 0) quotient = -quotient
    EOR R2,R2,R3, ASR 31
    ADD R0,R2,R3, LSR 31

    BX LR

    .end