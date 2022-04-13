#include <stdint.h>
#include <iostream>
#include "Vdown_counter.h"
#include <verilated.h>
#include <verilated_vcd_c.h>
#include <bitset>

int main(int argc, const char ** argv, const char ** env) {
  Verilated::commandArgs(argc, argv);

  int n;
  if (argc > 1 && argv[1][0] != '+')
    n = atoi(argv[1]);
  else
    n = 7;

  Vdown_counter * dut = new Vdown_counter;
  Verilated::traceEverOn(true);
  VerilatedVcdC * tfp = new VerilatedVcdC;
  dut->trace(tfp, 99);
  tfp->open("down_counter.vcd");

  dut->clk = 0;
  dut->data_in = 0;

  int time = 0;

  dut->clk = 0;
  dut->ld = 1;
  std::cout << "Writing "<< n <<  std::endl;

  dut->data_in = n;
  for (int i = 0 ; i < 16 ; i++) {
    time += 10;
    
    dut->eval();
    tfp->dump( time );

    dut->clk = 1;
    time += 10;
    
    dut->eval();
    tfp->dump( time );
    dut->clk = 0;

  }    
  
  dut->ld = 0;
//Read from  memory
  int count = 0;
  while(!dut->done){
    dut->clk = 0;
    dut->en = 1;
    time += 10;
    
    dut->eval();
    tfp->dump( time );

    dut->clk = 1;
    time += 10;
    
    dut->eval();
    tfp->dump( time );
    std::cout << "(" << count++ << ") done: " << std::bitset<1>(dut->done) << std::endl;

  }    
  std::cout << "(" << count++ << ") done: " << std::bitset<1>(dut->done) << std::endl;
  tfp->close();
  delete tfp;

  dut->final();
  delete dut;

  return 0;
}

