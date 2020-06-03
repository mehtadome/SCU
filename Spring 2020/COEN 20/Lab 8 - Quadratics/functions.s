.syntax unified
.cpu cortex-m4


.global Root1
.thumb_func
// float Root1(float a, float b, float c)
//  -b + sqrt(discriminant(a,b,c) / 2a
Root1:
    PUSH        {LR}
    VPUSH       {S16-S17}
    VMOV        S16,S0      // a in S16
    VMOV        S17,S1      // b in S17

    BL          Discriminant    // b^2 - 4ac

    VSQRT.F32   S0,S0       // sqrt(b^2 - 4ac)
    VNEG.F32    S17,S17     // b = -b 
    VADD.F32    S0,S17,S0   // -b + sqrt(b^2 - 4ac)

    VMOV        S1,2        // put 2 in S2 for division
    VMUL.F32    S16,S1,S16  // 2a
    VDIV.F32    S0,S0,S16   // -b + sqrt(b^2 - 4ac) / 2a

    VPOP        {S16-S17}
    POP         {PC}


.global Root2
.thumb_func
// float Root2(float a, float b, float c)
//  -b - sqrt(discriminant(a,b,c) / 2a
Root2:
    PUSH        {LR}
    VPUSH       {S16-S17}
    VMOV        S16,S0      // a in S16
    VMOV        S17,S1      // b in S17

    BL          Discriminant    // b^2 - 4ac

    VSQRT.F32   S0,S0       // sqrt(b^2 - 4ac)
    VNEG.F32    S17,S17     // b = -b 
    VSUB.F32    S0,S17,S0   // -b - sqrt(b^2 - 4ac)

    VMOV        S1,2        // put 2 in S2 for division
    VMUL.F32    S16,S1,S16  // 2a
    VDIV.F32    S0,S0,S16   // -b + sqrt(b^2 - 4ac) / 2a

    VPOP        {S16-S17}
    POP         {PC}


.global Quadratic
.thumb_func
// float Quadratic(float x, float a, float b, float c)
//  ax^2 + bx + c
Quadratic:
    VMUL.F32    S2,S0,S2    // bx
    VMUL.F32    S0,S0,S0    // x^2
    VMUL.F32    S0,S0,S1    // ax^2

    VADD.F32    S0,S0,S2    // ax^2 + bx
    VADD.F32    S0,S0,S3    // ax^2 + bx + c
    
    BX LR



.global Discriminant
.thumb_func
// float Discriminant(float a, float b, float c)
//  b^2 - 4ac
Discriminant:
    VMUL.F32    S0,S0,S2    // ac
    VMOV        S2,4        // move 4 into S2

    VMUL.F32    S0,S0,S2    // 4ac
    VMUL.F32    S1,S1,S1    // b^2
    VSUB.F32    S0,S1,S0    // b^2 - 4ac

    BX LR

    .end
 
