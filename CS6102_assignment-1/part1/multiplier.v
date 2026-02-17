module multiplier(input wire [3:0] a, b, output wire [3:0] out) ;
    wire p0, p1, p2, p3, p4, p5, p6;

    assign p0 = a[0] & b[0];
    assign p1 = (a[1] & b[0]) ^ (a[0] & b[1]);
    assign p2 = (a[2] & b[0]) ^ (a[1] & b[1]) ^ (a[0] & b[2]);
    assign p3 = (a[3] & b[0]) ^ (a[2] & b[1]) ^
                (a[1] & b[2]) ^ (a[0] & b[3]);
    assign p4 = (a[3] & b[1]) ^ (a[2] & b[2]) ^
                (a[1] & b[3]);
    assign p5 = (a[3] & b[2]) ^ (a[2] & b[3]);
    assign p6 = (a[3] & b[3]);

    assign out[0] = p0 ^ p4;
    assign out[1] = p1 ^ p4 ^ p5;
    assign out[2] = p2 ^ p5 ^ p6;
    assign out[3] = p3 ^ p6;

endmodule
