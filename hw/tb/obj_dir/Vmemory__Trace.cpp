// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vmemory__Syms.h"


//======================

void Vmemory::traceChg(VerilatedVcd* vcdp, void* userthis, uint32_t code) {
    // Callback from vcd->dump()
    Vmemory* t=(Vmemory*)userthis;
    Vmemory__Syms* __restrict vlSymsp = t->__VlSymsp;  // Setup global symbol table
    if (vlSymsp->getClearActivity()) {
	t->traceChgThis(vlSymsp, vcdp, code);
    }
}

//======================


void Vmemory::traceChgThis(Vmemory__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vmemory* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    int c=code;
    if (0 && vcdp && c) {}  // Prevent unused
    // Body
    {
	if (VL_UNLIKELY((2U & vlTOPp->__Vm_traceActivity))) {
	    vlTOPp->traceChgThis__2(vlSymsp, vcdp, code);
	}
	vlTOPp->traceChgThis__3(vlSymsp, vcdp, code);
    }
    // Final
    vlTOPp->__Vm_traceActivity = 0U;
}

void Vmemory::traceChgThis__2(Vmemory__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vmemory* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    int c=code;
    if (0 && vcdp && c) {}  // Prevent unused
    // Body
    {
	vcdp->chgBus  (c+1,(vlTOPp->memory__DOT__mem[0]),16);
	vcdp->chgBus  (c+2,(vlTOPp->memory__DOT__mem[1]),16);
	vcdp->chgBus  (c+3,(vlTOPp->memory__DOT__mem[2]),16);
	vcdp->chgBus  (c+4,(vlTOPp->memory__DOT__mem[3]),16);
	vcdp->chgBus  (c+5,(vlTOPp->memory__DOT__mem[4]),16);
	vcdp->chgBus  (c+6,(vlTOPp->memory__DOT__mem[5]),16);
	vcdp->chgBus  (c+7,(vlTOPp->memory__DOT__mem[6]),16);
	vcdp->chgBus  (c+8,(vlTOPp->memory__DOT__mem[7]),16);
	vcdp->chgBus  (c+9,(vlTOPp->memory__DOT__mem[8]),16);
	vcdp->chgBus  (c+10,(vlTOPp->memory__DOT__mem[9]),16);
	vcdp->chgBus  (c+11,(vlTOPp->memory__DOT__mem[10]),16);
	vcdp->chgBus  (c+12,(vlTOPp->memory__DOT__mem[11]),16);
	vcdp->chgBus  (c+13,(vlTOPp->memory__DOT__mem[12]),16);
	vcdp->chgBus  (c+14,(vlTOPp->memory__DOT__mem[13]),16);
	vcdp->chgBus  (c+15,(vlTOPp->memory__DOT__mem[14]),16);
	vcdp->chgBus  (c+16,(vlTOPp->memory__DOT__mem[15]),16);
    }
}

void Vmemory::traceChgThis__3(Vmemory__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vmemory* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    int c=code;
    if (0 && vcdp && c) {}  // Prevent unused
    // Body
    {
	vcdp->chgBit  (c+17,(vlTOPp->clk));
	vcdp->chgBit  (c+18,(vlTOPp->we));
	vcdp->chgBus  (c+19,(vlTOPp->addr),4);
	vcdp->chgBus  (c+20,(vlTOPp->data_in),16);
	vcdp->chgBus  (c+21,(vlTOPp->data_out),16);
    }
}
