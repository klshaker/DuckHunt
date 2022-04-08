#include <iostream>
#include "Vmemory.h"
#include <verilated.h>
#include <verilated_vcd_c.h>

int main(int argc, const char ** argv, const char ** env) {
  Verilated::commandArgs(argc, argv);

  int n;
  if (argc > 1 && argv[1][0] != '+')
    n = atoi(argv[1]);
  else
    n = 7;

  Vmemory * dut = new Vmemory;
  
  Verilated::traceEverOn(true);
  VerilatedVcdC * tfp = new VerilatedVcdC;
  dut->trace(tfp, 99);
  tfp->open("memory.vcd");

  dut->clk = 0;
  dut->data_in = 0;

  int time = 0;

//Write to memory
  for (int i = 0 ; i < 16 ; i++) {
    dut->clk = 0;
	dut->we = 1;
	dut->addr = i;
    dut->data_in = i;
    time += 10;
    
    dut->eval();
    tfp->dump( time );

    dut->clk = 1;
    time += 10;
    
    dut->eval();
    tfp->dump( time );

    std::cout << "(" << i << ") Writing "<< dut->data_in << " to address " << dut->addr  << std::endl;
  }    
  
  dut->we = 0;
//Read from  memory
  for (int i = 0 ; i < 16 ; i++) {
    dut->clk = 0;
	dut->addr = i;
    time += 10;
    
    dut->eval();
    tfp->dump( time );

    dut->clk = 1;
    time += 10;
    
    dut->eval();
    tfp->dump( time );
    std::cout << i << ' ' << dut->data_out << std::endl;

  }    
  tfp->close();
  delete tfp;

  dut->final();
  delete dut;

  return 0;
}

