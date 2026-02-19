#include "multiplier.h"

static const unsigned char lookup_table[256] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0, 2, 4, 6, 8, 10, 12, 14, 3, 1, 7, 5, 11, 9, 15, 13, 0, 3, 6, 5, 12, 15, 10, 9, 11, 8, 13, 14, 7, 4, 1, 2, 0, 4, 8, 12, 3, 7, 11, 15, 6, 2, 14, 10, 5, 1, 13, 9, 0, 5, 10, 15, 7, 2, 13, 8, 14, 11, 4, 1, 9, 12, 3, 6, 0, 6, 12, 10, 11, 13, 7, 1, 5, 3, 9, 15, 14, 8, 2, 4, 0, 7, 14, 9, 15, 8, 1, 6, 13, 10, 3, 4, 2, 5, 12, 11, 0, 8, 3, 11, 6, 14, 5, 13, 12, 4, 15, 7, 10, 2, 9, 1, 0, 9, 1, 8, 2, 11, 3, 10, 4, 13, 5, 12, 6, 15, 7, 14, 0, 10, 7, 13, 14, 4, 9, 3, 15, 5, 8, 2, 1, 11, 6, 12, 0, 11, 5, 14, 10, 1, 15, 4, 7, 12, 2, 9, 13, 6, 8, 3, 0, 12, 11, 7, 5, 9, 14, 2, 10, 6, 1, 13, 15, 3, 4, 8, 0, 13, 9, 4, 1, 12, 8, 5, 2, 15, 11, 6, 3, 14, 10, 7, 0, 14, 15, 1, 13, 3, 2, 12, 9, 7, 6, 8, 4, 10, 11, 5, 0, 15, 13, 2, 9, 6, 4, 11, 1, 14, 12, 3, 8, 7, 5, 10};


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
	return lookup_table[(a << 4) | b];
}
