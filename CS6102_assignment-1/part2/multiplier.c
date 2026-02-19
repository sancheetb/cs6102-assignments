#include "multiplier.h"

/**
 * GF(16) multiplication
 * Mod Polynomial: x^4 + x + 1 (0x13)
 */
unsigned char mul_f(unsigned char a, unsigned char b)
{

    // unsigned char a0 = (a >> 0) & 1;
    // unsigned char a1 = (a >> 1) & 1;
    // unsigned char a2 = (a >> 2) & 1;
    // unsigned char a3 = (a >> 3) & 1;

    // unsigned char b0 = (b >> 0) & 1;
    // unsigned char b1 = (b >> 1) & 1;
    // unsigned char b2 = (b >> 2) & 1;
    // unsigned char b3 = (b >> 3) & 1;

    // unsigned char p0 = a0 & b0;
    // unsigned char p1 = (a1 & b0) ^ (a0 & b1);
    // unsigned char p2 = (a2 & b0) ^ (a1 & b1) ^ (a0 & b2);
    // unsigned char p3 = (a3 & b0) ^ (a2 & b1) ^
    //                    (a1 & b2) ^ (a0 & b3);
    // unsigned char p4 = (a3 & b1) ^ (a2 & b2) ^
    //                    (a1 & b3);
    // unsigned char p5 = (a3 & b2) ^ (a2 & b3);
    // unsigned char p6 = (a3 & b3);

    
    // unsigned char r0 = p0 ^ p4;
    // unsigned char r1 = p1 ^ p4 ^ p5;
    // unsigned char r2 = p2 ^ p5 ^ p6;
    // unsigned char r3 = p3 ^ p6;

    // unsigned char r0 = (a0 & b0) ^ (a3 & b1) ^ (a2 & b2) ^ (a1 & b3);
    // unsigned char r1 = (a1 & b0) ^ (a0 & b1) ^ (a3 & b1) ^ (a2 & b2) ^ (a1 & b3) ^ (a3 & b2) ^ (a2 & b3);
    // unsigned char r2 = (a2 & b0) ^ (a1 & b1) ^ (a0 & b2) ^ (a3 & b2) ^ (a2 & b3) ^ (a3 & b3);
    // unsigned char r3 = (a3 & b0) ^ (a2 & b1) ^ (a1 & b2) ^ (a0 & b3) ^ (a3 & b3);

    


    
    // return (r0 << 0) | (r1 << 1) | (r2 << 2) | (r3 << 3);

	// return ( ((a0 & b0) ^ (a3 & b1) ^ (a2 & b2) ^ (a1 & b3))<< 0) | (((a1 & b0) ^ (a0 & b1) ^ (a3 & b1) ^ (a2 & b2) ^ (a1 & b3) ^ (a3 & b2) ^ (a2 & b3)) << 1) | (((a2 & b0) ^ (a1 & b1) ^ (a0 & b2) ^ (a3 & b2) ^ (a2 & b3) ^ (a3 & b3)) << 2) | (((a3 & b0) ^ (a2 & b1) ^ (a1 & b2) ^ (a0 & b3) ^ (a3 & b3)) << 3);
	//
	unsigned char res = 0;
    for (int i = 0; i < 4; i++) {
        if (b & 1) res ^= a;
        unsigned char mask = (a & 0x08) ? 0x13 : 0x00; // If bit 3 is set, reduce by poly
        a = (a << 1) ^ mask;
        b >>= 1;
    }
    return res & 0x0F; // Ensure result is 4-bit
}
