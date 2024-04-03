// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vcode38.h"
#include "Vcode38__Syms.h"

//============================================================
// Constructors

Vcode38::Vcode38(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vcode38__Syms(contextp(), _vcname__, this)}
    , i_en{vlSymsp->TOP.i_en}
    , i_code{vlSymsp->TOP.i_code}
    , o_code{vlSymsp->TOP.o_code}
    , o_seg{vlSymsp->TOP.o_seg}
    , o_en_flag{vlSymsp->TOP.o_en_flag}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

Vcode38::Vcode38(const char* _vcname__)
    : Vcode38(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vcode38::~Vcode38() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vcode38___024root___eval_debug_assertions(Vcode38___024root* vlSelf);
#endif  // VL_DEBUG
void Vcode38___024root___eval_static(Vcode38___024root* vlSelf);
void Vcode38___024root___eval_initial(Vcode38___024root* vlSelf);
void Vcode38___024root___eval_settle(Vcode38___024root* vlSelf);
void Vcode38___024root___eval(Vcode38___024root* vlSelf);

void Vcode38::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vcode38::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vcode38___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        vlSymsp->__Vm_didInit = true;
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vcode38___024root___eval_static(&(vlSymsp->TOP));
        Vcode38___024root___eval_initial(&(vlSymsp->TOP));
        Vcode38___024root___eval_settle(&(vlSymsp->TOP));
    }
    // MTask 0 start
    VL_DEBUG_IF(VL_DBG_MSGF("MTask0 starting\n"););
    Verilated::mtaskId(0);
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vcode38___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vcode38::eventsPending() { return false; }

uint64_t Vcode38::nextTimeSlot() {
    VL_FATAL_MT(__FILE__, __LINE__, "", "%Error: No delays in the design");
    return 0;
}

//============================================================
// Utilities

const char* Vcode38::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vcode38___024root___eval_final(Vcode38___024root* vlSelf);

VL_ATTR_COLD void Vcode38::final() {
    Vcode38___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vcode38::hierName() const { return vlSymsp->name(); }
const char* Vcode38::modelName() const { return "Vcode38"; }
unsigned Vcode38::threads() const { return 1; }
