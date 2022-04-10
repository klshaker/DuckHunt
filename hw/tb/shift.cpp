#include <stdint.h>
#include <iostream>
#include "Vshift.h"
#include <verilated.h>
#include <verilated_vcd_c.h>
#include <bitset>

int main(int argc, const char ** argv, const char ** env) {
  Verilated::commandArgs(argc, argv);

  int64_t d_in = 0x53977053977;

  Vshift * dut = new Vshift;
  Verilated::traceEverOn(true);
  VerilatedVcdC * tfp = new VerilatedVcdC;
  dut->trace(tfp, 99);
  tfp->open("shift.vcd");

  dut->clk = 0;
  dut->data_in = 0;

  int time = 0;

  dut->clk = 0;
  dut->ld = 1;
  std::cout << "Writing "<< d_in <<  std::endl;

  dut->data_in = d_in;
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
  for (int i = 0 ; i < 16 ; i++) {
    dut->clk = 0;
    dut->en = 1;
    time += 10;
    
    dut->eval();
    tfp->dump( time );

    dut->clk = 1;
    time += 10;
    
    dut->eval();
    tfp->dump( time );
    std::cout << "datout: " << std::bitset<3>(dut->data_out) << std::endl;

  }    
  tfp->close();
  delete tfp;

  dut->final();
  delete dut;

  return 0;
}

