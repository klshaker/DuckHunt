// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vmemory__Syms.h"


//======================

void Vmemory::trace(VerilatedVcdC* tfp, int, int) {
    tfp->spTrace()->addCallback(&Vmemory::traceInit, &Vmemory::traceFull, &Vmemory::traceChg, this);
}
void Vmemory::traceInit(VerilatedVcd* vcdp, void* userthis, uint32_t code) {
    // Callback from vcd->open()
    Vmemory* t=(Vmemory*)userthis;
    Vmemory__Syms* __restrict vlSymsp = t->__VlSymsp;  // Setup global symbol table
    if (!Verilated::calcUnusedSigs()) {
	VL_FATAL_MT(__FILE__,__LINE__,__FILE__,"Turning on wave traces requires Verilated::traceEverOn(true) call before time 0.");
    }
    vcdp->scopeEscape(' ');
    t->traceInitThis(vlSymsp, vcdp, code);
    vcdp->scopeEscape('.');
}
void Vmemory::traceFull(VerilatedVcd* vcdp, void* userthis, uint32_t code) {
    // Callback from vcd->dump()
    Vmemory* t=(Vmemory*)userthis;
    Vmemory__Syms* __restrict vlSymsp = t->__VlSymsp;  // Setup global symbol table
    t->traceFullThis(vlSymsp, vcdp, code);
}

//======================


void Vmemory::traceInitThis(Vmemory__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vmemory* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    int c=code;
    if (0 && vcdp && c) {}  // Prevent unused
    vcdp->module(vlSymsp->name());  // Setup signal names
    // Body
    {
	vlTOPp->traceInitThis__1(vlSymsp, vcdp, code);
    }
}

void Vmemory::traceFullThis(Vmemory__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vmemory* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    int c=code;
    if (0 && vcdp && c) {}  // Prevent unused
    // Body
    {
	vlTOPp->traceFullThis__1(vlSymsp, vcdp, code);
    }
    // Final
    vlTOPp->__Vm_traceActivity = 0U;
}

void Vmemory::traceInitThis__1(Vmemory__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vmemory* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    int c=code;
    if (0 && vcdp && c) {}  // Prevent unused
    // Body
    {
	vcdp->declBit  (c+17,"clk",-1);
	vcdp->declBit  (c+18,"we",-1);
	vcdp->declBus  (c+19,"addr",-1,3,0);
	vcdp->declBus  (c+20,"data_in",-1,15,0);
	vcdp->declBus  (c+21,"data_out",-1,15,0);
	vcdp->declBus  (c+22,"memory WORD_SIZE",-1,31,0);
	vcdp->declBus  (c+22,"memory NUM_WORDS",-1,31,0);
	vcdp->declBus  (c+23,"memory ADDR_BITS",-1,31,0);
	vcdp->declBit  (c+17,"memory clk",-1);
	vcdp->declBit  (c+18,"memory we",-1);
	vcdp->declBus  (c+19,"memory addr",-1,3,0);
	vcdp->declBus  (c+20,"memory data_in",-1,15,0);
	vcdp->declBus  (c+21,"memory data_out",-1,15,0);
	{int i; for (i=0; i<16; i++) {
		vcdp->declBus  (c+1+i*1,"memory mem",(i+0),15,0);}}
    }
}

void Vmemory::traceFullThis__1(Vmemory__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vmemory* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    int c=code;
    if (0 && vcdp && c) {}  // Prevent unused
    // Body
    {
	vcdp->fullBus  (c+1,(vlTOPp->memory__DOT__mem[0]),16);
	vcdp->fullBus  (c+2,(vlTOPp->memory__DOT__mem[1]),16);
	vcdp->fullBus  (c+3,(vlTOPp->memory__DOT__mem[2]),16);
	vcdp->fullBus  (c+4,(vlTOPp->memory__DOT__mem[3]),16);
	vcdp->fullBus  (c+5,(vlTOPp->memory__DOT__mem[4]),16);
	vcdp->fullBus  (c+6,(vlTOPp->memory__DOT__mem[5]),16);
	vcdp->fullBus  (c+7,(vlTOPp->memory__DOT__mem[6]),16);
	vcdp->fullBus  (c+8,(vlTOPp->memory__DOT__mem[7]),16);
	vcdp->fullBus  (c+9,(vlTOPp->memory__DOT__mem[8]),16);
	vcdp->fullBus  (c+10,(vlTOPp->memory__DOT__mem[9]),16);
	vcdp->fullBus  (c+11,(vlTOPp->memory__DOT__mem[10]),16);
	vcdp->fullBus  (c+12,(vlTOPp->memory__DOT__mem[11]),16);
	vcdp->fullBus  (c+13,(vlTOPp->memory__DOT__mem[12]),16);
	vcdp->fullBus  (c+14,(vlTOPp->memory__DOT__mem[13]),16);
	vcdp->fullBus  (c+15,(vlTOPp->memory__DOT__mem[14]),16);
	vcdp->fullBus  (c+16,(vlTOPp->memory__DOT__mem[15]),16);
	vcdp->fullBit  (c+17,(vlTOPp->clk));
	vcdp->fullBit  (c+18,(vlTOPp->we));
	vcdp->fullBus  (c+19,(vlTOPp->addr),4);
	vcdp->fullBus  (c+20,(vlTOPp->data_in),16);
	vcdp->fullBus  (c+21,(vlTOPp->data_out),16);
	vcdp->fullBus  (c+22,(0x10U),32);
	vcdp->fullBus  (c+23,(4U),32);
    }
}
