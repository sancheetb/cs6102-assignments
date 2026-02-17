`timescale 1ns / 1ps

module multiplier_tb;

    reg  [3:0] a;
    reg  [3:0] b;
    wire [3:0] out;
    
    integer i, j;

    multiplier uut (.a(a), .b(b), .out(out));

    initial begin
        $display("Starting GF(2^4) Multiplier Test...");
        $display("------------------------------------");
        $display("  A  |  B  | Result (OUT)");
        $display("------------------------------------");

        for (i = 0; i < 16; i = i + 1) begin
            for (j = 0; j < 16; j = j + 1) begin
                
                a = i; 
                b = j;
                
                #10;
                
                $display(" %h  |  %h  |   %h", a, b, out);
            end
        end

        $display("------------------------------------");
        $display("Simulation Finished.");
        $finish;
    end

    initial begin
        $dumpfile("multiplier.vcd");
        $dumpvars(0, multiplier_tb);
    end

endmodule

