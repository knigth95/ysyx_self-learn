// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vcode38.h for the primary calling header

#ifndef VERILATED_VCODE38___024ROOT_H_
#define VERILATED_VCODE38___024ROOT_H_  // guard

#include "verilated.h"

class Vcode38__Syms;

class Vcode38___024root final : public VerilatedModule {
  public:

    // DESIGN SPECIFIC STATE
    VL_IN8(i_en,0,0);
    VL_IN8(i_code,7,0);
    VL_OUT8(o_code,2,0);
    VL_OUT8(o_seg,7,0);
    VL_OUT8(o_en_flag,0,0);
    CData/*0:0*/ __VactContinue;
    IData/*31:0*/ __VstlIterCount;
    IData/*31:0*/ __VicoIterCount;
    IData/*31:0*/ __VactIterCount;
    VlTriggerVec<1> __VstlTriggered;
    VlTriggerVec<1> __VicoTriggered;
    VlTriggerVec<0> __VactTriggered;
    VlTriggerVec<0> __VnbaTriggered;

    // INTERNAL VARIABLES
    Vcode38__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vcode38___024root(Vcode38__Syms* symsp, const char* v__name);
    ~Vcode38___024root();
    VL_UNCOPYABLE(Vcode38___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);


#endif  // guard
