.PHONY: default program clean lint
SRC = ../src
FILES = memory.sv down_counter.sv shift.sv
SVFILES = $(patsubst %, $(SRC)/%, $(FILES))

default :
	@echo "No target given. Try:"
	@echo ""
	@echo "make memory"
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


# Create Verilator simulations
obj_dir/Vmemory : $(SRC)/memory.sv memory.cpp
	verilator -trace -Wall -cc $(SRC)/memory.sv -exe memory.cpp \
		-top-module memory
	cd obj_dir && make -j -f Vmemory.mk

obj_dir/Vshift : $(SRC)/shift.sv shift.cpp
	verilator -trace -Wall -cc $(SRC)/shift.sv -exe shift.cpp \
		-top-module shift
	cd obj_dir && make -j -f Vshift.mk

clean :
	rm -rf obj_dir db incremental_db output_files \
	lab1.qpf lab1.qsf lab1.sdc lab1.qws c5_pin_model_dump.txt
