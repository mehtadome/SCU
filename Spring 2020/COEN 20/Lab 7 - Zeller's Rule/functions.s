/* uint32_t Zeller(uint32_t k, uint32_t m, uint32_t D, uint32_t C)
   {
   int32_t f, r ;

   f = (int32_t) (k + ((13*m-1)/5) + D +D/4 + C/4 - 2*C) ;
   r = f % 7 ;
   if (r < 0) r += 7 ;
   return r ;
   }
*/
/*
    k + D
    D/4
    C/4
    -(C*2)
    13*m ==> 13*(m-1) ==> 13*(m-1)/5

    modulus

    r < 0
        r += 7
    
*/
.syntax		unified
.cpu		cortex-m4
.text
    
.global		Zeller1
.thumb_func
	
Zeller1:
    ADD		R0,R0,R2		// f = k + D
    ADD		R0,R0,R2, LSR 2	// D / 4
    ADD		R0,R0,R3, LSR 2	// C / 4
    SUB		R0,R0,R3, LSL 1	// f -= C*2

    LDR		R3,=13				
    MUL		R2,R1,R3	// 13*m
    SUB		R2,R2,1		// 13*m - 1
    LDR		R3,=5
    UDIV	R2,R2,R3	// R2 = (13*m - 1) / 5
    ADD		R0,R0,R2	// f += R2


    LDR		R3,=7
    SDIV	R2,R0,R3	// R2 = f / 7
    MUL		R2,R2,R3	// R2 *= 7
    SUB		R2,R0,R2	// R2 = f - R2

    CMP		R2,0		// R2 < 0?
    IT		LT			
    ADDLT	R2,R2,R3    // R2 += 7
    MOV		R0,R2

    BX 		LR


.global		Zeller2 
.thumb_func	
Zeller2:
    PUSH	{R4}
    ADD		R0,R0,R2		// f = k + D
    ADD		R0,R0,R2, LSR 2	// D / 4
    ADD		R0,R0,R3, LSR 2	// C / 4
    SUB		R0,R0,R3, LSL 1	// f -= C*2

    LDR		R3,=13				
    MUL		R2,R1,R3			// 13*m
    SUB		R2,R2,1			// 13*m - 1

    LDR		R3,=858993460	// 2^32 / 5
    SMULL	R2,R3,R2,R3		// R2 = R2 * 2^32 / 5
    ADD		R0,R0,R3		// f += R2

    LDR		R3,=613566757	// 2^32 / 7
    SMULL	R2,R3,R0,R3		// R2 = f * 2^32 / 7

    LDR		R4,=7
    MUL		R3,R3,R4		// R3 *= 7
    SUB		R3,R0,R3		// R3 = f - R2

    CMP		R3,0			
    IT		LT				// R3 < 0 
    ADDLT	R3,R3,7			// R3 += 7
    MOV		R0,R3

    POP		{R4}
    BX 		LR
    
.global		Zeller3
.thumb_func

Zeller3:
    PUSH	{R4}
    ADD		R0,R0,R2			// f = k + D
    ADD		R0,R0,R2, LSR 2	// D / 4
    ADD		R0,R0,R3, LSR 2	// C / 4
    SUB		R0,R0,R3, LSL 1	// f -= C*2
    ADD		R4,R1,R1, LSL 3	// 8m + 1m
    ADD		R2,R4,R1, LSL 2	// R2 = 9m + 4m
    SUB		R2,R2,1			// 13*m - 1

    LDR		R4,=5
    UDIV	R2,R2,R4		// 13*m - 1 / 5
    ADD		R0,R0,R2		// f += R2
    LDR		R4,=7

    SDIV	R2,R0,R4		// R2 = f / 7
    LSL		R4,R2,3			// R4 = 8*R2
    SUB		R2,R4,R2		// 8*R2 - R2 
    SUB		R2,R0,R2	    // R2 = f - R2

    CMP		R2,0			
    IT		LT				// R2 < 0
    ADDLT	R2,R2,7			// R2 += 7
    MOV		R0,R2

    POP		{R4}
    BX 		LR
    
    .end










