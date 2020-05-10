// Ruchir Mehta
// April 15, 2020
// functions.s

		.syntax		unified
		.cpu		cortex-m4
		.text
	
	// int32_t Add(int32_t a, int32_t b);
		.global		Add
		.thumb_func

	// Add the a+b aka R0 + R1
	Add:
		ADD R0,R0,R1
		BX LR
	
	// int32_t Less1(int32_t a);
		.global		Less1
		.thumb_func

	// Subtract 1 from x 
	Less1:
		SUB R0,R0,1
		BX LR
	
	// int32_t Square2x(int32_t x);
		.global		Square2x
		.thumb_func

	// Add x+x and pass the new x value into Square(x);
	Square2x:
		PUSH {LR}
		ADD R0,R0,R0
		BL Square
		POP {PC}

	// int32_t Last(int32_t x);
		.global		Last
		.thumb_func
	
	// Store original x into R4, call Squareroot(x) and do R0 = R0 + R4
	Last:
		PUSH {R4,LR}
		MOV R4,R0
		BL SquareRoot
		ADD R0,R0,R4
		POP {R4,PC}
		.end