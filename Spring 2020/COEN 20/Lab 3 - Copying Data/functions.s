.syntax		unified
.cpu		cortex-m4
.text

// (void *dst, void *src)

// 1 bit at a time
.global UseLDRB
.thumb_func
.align

UseLDRB:
    .rept 512   // 512 bytes / 1 = 512
    // load and store byte into R2, from R1/R0
    LDRB R2, [R1], 1
    STRB R2, [R0], 1
    .endr
    BX LR

// 2 bits at a time
.global UseLDRH
.thumb_func
.align

UseLDRH:
    .rept 256    // 512 bytes / 2 = 256
    // load and store two byte into R2, from R1/R0
    LDRH R2, [R1], 2    
    STRH R2, [R0], 2
    .endr
    BX LR

// 4 bits at a time
.global UseLDR
.thumb_func
.align

UseLDR:
    .rept 128   // 512 bytes / 4 = 128
    // load and store four byte into R2, from R1/R0
    LDR R2, [R1], 4
    STR R2, [R0], 4
    .endr
    BX LR

// 8 bits at a time
.global UseLDRD
.thumb_func
.align

UseLDRD:
    .rept 64    // 512 bytes / 8 = 64
    // load and store R1 into mostSig R3 and leastSig R2
    LDRD  R3,R2, [R1], 8 
    STRD R3,R2, [R0], 8
    .endr
    BX LR

// 32 bits at a time
.global UseLDM
.thumb_func
.align

UseLDM:
    PUSH {R4-R9}
    .rept 16    // 512 bytes / 32 = 16
    // load and store sixteen bytes into R2, from R1/R0 using LDMIA and STRMIA
    // used for expansion of registers to account for larger bytes
    LDMIA R1!, {R2-R9}
    STMIA R0!, {R2-R9}
    .endr
    POP {R4-R9}
    BX LR


