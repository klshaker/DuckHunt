#include <stdint.h>
#include <iostream>
#include "Vshift.h"
#include <verilated.h>
#include <verilated_vcd_c.h>
#include <bitset>

int main(int argc, const char ** argv, const char ** env) {
  Verilated::commandArgs(argc, argv);

  // TODO (ask bryce this is greater than 32 bits?)
  int64_t d_in = 0x53977053977;
  // In binary this is 01010011100101110111000001010011100101110111.
  // Broken into 2 bit pieces it is 
  std::bitset<32> d_in_bits (d_in);


  Vshift * dut = new Vshift;
  Verilated::traceEverOn(true);
  VerilatedVcdC * tfp = new VerilatedVcdC;
  dut->trace(tfp, 99);
  // TODO Bryce what is this trace and why do we have to open .vcd? 
  tfp->open("shift.vcd");

  dut->clk = 0;
  dut->data_in = 0;

  int time = 0;

  dut->clk = 0;
  dut->ld = 1;
  std::cout << "Writing "<< d_in <<  std::endl;

  dut->data_in = d_in;
  // TODO Does it need 16 clock cycles to read in the data? Doesn't it just need one? Are we doing this 16 times superfluously? 
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
  dut->en = 1;
  //Read from  memory. Every cycle we will read out 2 bits.
  for (int i = 0 ; i < 16 ; i++) {
    dut->clk = 0;
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

