.syntax unified
.cpu    cortex-m4
.text

.global MxPlusB
.thumb_func
.align

// Function to implement in assembly: Returns (mtop*x + mbtm/2)/mbtm + b

// int32_t MxPlusB(int32_t x, int32_t mtop, int32_t mbtm, int32_t b) ;
MxPlusB:
    // R0 = x, R1 = mtop, R2 = mbtm, R3 = b 

    // R4 = main register for calculations
    // R5 = register for constant of 2
    PUSH {R4,R5}

    // R4 (rounding) = ((x*dvnd * dvsr) >> 31

    // (x*dvnd * dvsr) >> 31
    MUL R1,R1,R0    // x*dvnd
    MUL R4,R2,R1    // R4 = (x*dvnd) * dvsr 
    ASR R4,R4,31    // R4 = R4 >> 31

    // * dvsr) << 1) + dvsr
    MUL R4,R4,R2    // R4 = R4 * dvsr
    LSL R4,R4,1     // R4 = R4 << 1
    ADD R4,R4,R2    // R4 = R4 + dvsr

    // /2
    MOV R5, 2       // R5,=2
    SDIV R4,R4,R5   // R4 = R4 / R5

    // R4 (rounding) + (x * dvnd) / dvsr
    ADD R4,R4,R1    // R4 = R4 + (x*dvnd)
    SDIV R4,R4,R2   // R4 = R4 / dvsr

    // R4 + b 
    ADD R0,R4,R3    // R0 = R4 + b
    POP {R4,R5}
    BX LR

    .end