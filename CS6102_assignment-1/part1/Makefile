FILENAME = multiplier
DESIGN = $(FILENAME).v
TESTBENCH = $(FILENAME)_tb.v
OUTPUT = $(FILENAME)_sim
VCD_FILE = $(FILENAME)_tb.vcd

all: compile run

compile:
	@echo "Compiling Verilog files..."
	iverilog -o $(OUTPUT) $(DESIGN) $(TESTBENCH)
	@echo "Compilation successful!"

run:
	@echo "Running simulation..."
	@echo ""
	vvp $(OUTPUT)

clean:
	@echo "Cleaning up..."
	rm -f *_sim *.vcd
	@echo "Clean complete!"

.PHONY: all compile run clean
