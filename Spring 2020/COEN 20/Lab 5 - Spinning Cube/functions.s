.syntax unified
.cpu cortex-m4
.text


.global MatrixMultiply
.thumb_func
.align

// RO = A, R1 = B, R2 = C

// (rowindex * cols)+colIndex 
// *4 = byte offset = byte offset (base address of A)
MatrixMultiply: 
         PUSH {R4-R9,LR}
         // R4,R5,R6 = row,col,k 
         // R7,R8,R9 = a,b,c
         // R3 = 3

         MOV R7,R0
         MOV R8,R1
         MOV R9,R2

         LDR R4,=0      // row = 0
         B    rowLoop   // unconditionally go to row loop

rowLoop: CMP R4,3       // row <= 2
         BGE Done

         LDR R5,=0      // col = 0

         B  colLoop     // unconditionally go to col loop

colLoop: CMP R5,3       // col <= 2
         BGE incrementRow        // go back to row loop
         
         LDR R3,=3
         MLA R3,R3,R4,R5  // 3 * row + col
         LDR R1,=0
         STR R1, [R7, R3, LSL 2]    // a[row][col] => 0
         
         LDR R6,=0      // k = 0
         B  kLoop       // unconditionally go to k loop

kLoop:   CMP R6,3       // k <= 2
         BGE incrementCol    // go back to col loop
        
         
         LDR R3,=3
         MLA R3,R3,R4,R5    // 3 * row + col 
         LDR R0, [R7,R3, LSL 2] // a[row][col] => R0

         LDR R3,=3
         MLA R3,R3,R4,R6    // 3 * row + k 
         LDR R1, [R8,R3, LSL 2] // b[row][col] => R0

         LDR R3,=3
         MLA R3,R3,R6,R5    // 3*k + col 
         LDR R2, [R9,R3, LSL 2] // c[row][col] => R0

         BL MultAndAdd

         LDR R3,=3
         MLA R3,R3,R4,R5    // 3 * row + col
         STR R0, [R7,R3, LSL 2] // R0 <= a[row][col]

         ADD R6,R6,1    // k++
         B  kLoop       // unconditionally go to k loop  

incrementCol:
    ADD R5,R5,1
    B colLoop
incrementRow:
    ADD R4,R4,1
    B rowLoop
Done:    POP {R4-R9,PC}
         .end
    