.PHONY: default program clean lint
SRC = ../src
FILES = memory.sv down_counter.sv shift.sv ppu.sv
SVFILES = $(patsubst %, $(SRC)/%, $(FILES))

default :
	@echo "No target given. Try:"
	@echo "make all"
	@echo "make memory"
	@echo "make shift"
	@echo "make down_counter"
	@echo "make lint"


# Quickly check the System Verilog files for errors
lint :
	for file in $(SVFILES); do \
	verilator --lint-only -Wall $$file; done



# Run Verilator simulations
memory : obj_dir/Vmemory
	obj_dir/Vmemory

shift : obj_dir/Vshift
	obj_dir/Vshift

down_counter : obj_dir/Vdown_counter
	obj_dir/Vdown_counter

ppu : obj_dir/Vppu
	obj_dir/Vppu

# Create Verilator simulations
obj_dir/Vdown_counter : $(SRC)/down_counter.sv down_counter.cpp
	verilator -trace -Wall -cc $(SRC)/down_counter.sv -exe down_counter.cpp \
		-top-module down_counter
	cd obj_dir && make -j -f Vdown_counter.mk

obj_dir/Vmemory : $(SRC)/memory.sv memory.cpp
	verilator -trace -Wall -cc $(SRC)/memory.sv -exe memory.cpp \
		-top-module memory
	cd obj_dir && make -j -f Vmemory.mk

obj_dir/Vshift : $(SRC)/shift.sv shift.cpp
	verilator -trace -Wall -cc $(SRC)/shift.sv -exe shift.cpp \
		-top-module shift
	cd obj_dir && make -j -f Vshift.mk

obj_dir/Vppu : $(SRC)/ppu.sv ppu.cpp
	verilator -trace -Wall -cc $(SRC)/ppu.sv -y $(SRC) -exe ppu.cpp \
		-top-module ppu 
	cd obj_dir && make -j -f Vppu.mk

clean :
	rm -rf obj_dir *.vcd

all : clean lint memory shift down_counter
