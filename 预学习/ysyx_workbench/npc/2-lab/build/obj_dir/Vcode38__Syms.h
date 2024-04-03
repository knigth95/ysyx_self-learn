// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VCODE38__SYMS_H_
#define VERILATED_VCODE38__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "Vcode38.h"

// INCLUDE MODULE CLASSES
#include "Vcode38___024root.h"

// SYMS CLASS (contains all model state)
class Vcode38__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    Vcode38* const __Vm_modelp;
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    Vcode38___024root              TOP;

    // CONSTRUCTORS
    Vcode38__Syms(VerilatedContext* contextp, const char* namep, Vcode38* modelp);
    ~Vcode38__Syms();

    // METHODS
    const char* name() { return TOP.name(); }
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);

#endif  // guard
