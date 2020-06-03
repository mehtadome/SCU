.syntax unified
.cpu cortex-m4
.text


// void PutNibble(void *nibbles, uint32_t which, uint32_t value);

.global PutNibble
.thumb_func
.align

PutNibble:
    LSRS    R1,R1,1    // R1 = which shifted right
    LDRB    R3, [R0,R1] // R3 = [byte]

    ITTE CS 
    ANDCS   R3,R3,0x0F // clear nibble if the flag=1 ||  Carry Set
    LSLCS   R2,R2,4    // shift data to next significant nibble   || Carry Set
    ANDCC   R3,R3,0xF0 // clear nibble if the flag=0    || Carry Clear

    ORR R2,R2,R3    // bitfield insertion
    STRB R2, [R0,R1]

    BX LR 

// void GetNibble(void *nibbles, uint32_t which);

.global GetNibble
.thumb_func
.align

GetNibble:
    LSRS R1,R1,1    // which shifted right
    LDRB R3, [R0,R1]    // R3 = [byte]

    ITE CS          // Carry Set
    LSRCS R3,4      // Carry Set
    ANDCC R3,R3,0x0F    // clear nibble if the flag=0 || Carry Clear

    MOV R0,R3   // put R3 data in R0
    BX LR 
    .end
