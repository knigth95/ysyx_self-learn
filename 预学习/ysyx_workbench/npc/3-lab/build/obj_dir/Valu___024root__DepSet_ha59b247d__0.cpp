// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Valu.h for the primary calling header

#include "verilated.h"

#include "Valu___024root.h"

VL_INLINE_OPT void Valu___024root___ico_sequent__TOP__0(Valu___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Valu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Valu___024root___ico_sequent__TOP__0\n"); );
    // Body
    if ((4U & (IData)(vlSelf->ctrl))) {
        if ((2U & (IData)(vlSelf->ctrl))) {
            if ((1U & (IData)(vlSelf->ctrl))) {
                vlSelf->car = 0U;
                vlSelf->of = 0U;
                vlSelf->res = (((IData)(vlSelf->a) 
                                == (IData)(vlSelf->b))
                                ? 0U : 1U);
            } else {
                vlSelf->car = 0U;
                vlSelf->of = 0U;
                vlSelf->res = ((IData)(((~ ((IData)(vlSelf->a) 
                                            >> 3U)) 
                                        & ((IData)(vlSelf->b) 
                                           >> 3U)))
                                ? 0U : ((IData)((((IData)(vlSelf->a) 
                                                  >> 3U) 
                                                 & (~ 
                                                    ((IData)(vlSelf->b) 
                                                     >> 3U))))
                                         ? 1U : (((IData)(vlSelf->a) 
                                                  < (IData)(vlSelf->b))
                                                  ? 0U
                                                  : 1U)));
            }
        } else if ((1U & (IData)(vlSelf->ctrl))) {
            vlSelf->res = ((IData)(vlSelf->a) ^ (IData)(vlSelf->b));
            vlSelf->car = 0U;
            vlSelf->of = 0U;
        } else {
            vlSelf->res = ((IData)(vlSelf->a) | (IData)(vlSelf->b));
            vlSelf->car = 0U;
            vlSelf->of = 0U;
        }
    } else if ((2U & (IData)(vlSelf->ctrl))) {
        if ((1U & (IData)(vlSelf->ctrl))) {
            vlSelf->res = ((IData)(vlSelf->a) & (IData)(vlSelf->b));
            vlSelf->car = 0U;
            vlSelf->of = 0U;
        } else {
            vlSelf->res = (0xfU & (~ (IData)(vlSelf->a)));
            vlSelf->car = 0U;
            vlSelf->of = 0U;
        }
    } else if ((1U & (IData)(vlSelf->ctrl))) {
        vlSelf->tmp = (0xfU & ((IData)(1U) + (~ (IData)(vlSelf->b))));
        vlSelf->car = (1U & (((IData)(vlSelf->a) + (IData)(vlSelf->tmp)) 
                             >> 4U));
        vlSelf->res = (0xfU & ((IData)(vlSelf->a) + (IData)(vlSelf->tmp)));
        vlSelf->of = (((1U & ((IData)(vlSelf->a) >> 3U)) 
                       == (1U & ((IData)(vlSelf->b) 
                                 >> 3U))) & ((1U & 
                                              ((IData)(vlSelf->res) 
                                               >> 3U)) 
                                             != (1U 
                                                 & ((IData)(vlSelf->a) 
                                                    >> 3U))));
    } else {
        vlSelf->res = (0xfU & ((IData)(vlSelf->a) + (IData)(vlSelf->b)));
        vlSelf->car = (1U & (((IData)(vlSelf->a) + (IData)(vlSelf->b)) 
                             >> 4U));
        vlSelf->of = (((1U & ((IData)(vlSelf->a) >> 3U)) 
                       == (1U & ((IData)(vlSelf->b) 
                                 >> 3U))) & ((1U & 
                                              ((IData)(vlSelf->res) 
                                               >> 3U)) 
                                             != (1U 
                                                 & ((IData)(vlSelf->a) 
                                                    >> 3U))));
    }
}

void Valu___024root___eval_ico(Valu___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Valu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Valu___024root___eval_ico\n"); );
    // Body
    if (vlSelf->__VicoTriggered.at(0U)) {
        Valu___024root___ico_sequent__TOP__0(vlSelf);
    }
}

void Valu___024root___eval_act(Valu___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Valu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Valu___024root___eval_act\n"); );
}

void Valu___024root___eval_nba(Valu___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Valu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Valu___024root___eval_nba\n"); );
}

void Valu___024root___eval_triggers__ico(Valu___024root* vlSelf);
#ifdef VL_DEBUG
VL_ATTR_COLD void Valu___024root___dump_triggers__ico(Valu___024root* vlSelf);
#endif  // VL_DEBUG
void Valu___024root___eval_triggers__act(Valu___024root* vlSelf);
#ifdef VL_DEBUG
VL_ATTR_COLD void Valu___024root___dump_triggers__act(Valu___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Valu___024root___dump_triggers__nba(Valu___024root* vlSelf);
#endif  // VL_DEBUG

void Valu___024root___eval(Valu___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Valu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Valu___024root___eval\n"); );
    // Init
    CData/*0:0*/ __VicoContinue;
    VlTriggerVec<0> __VpreTriggered;
    IData/*31:0*/ __VnbaIterCount;
    CData/*0:0*/ __VnbaContinue;
    // Body
    vlSelf->__VicoIterCount = 0U;
    __VicoContinue = 1U;
    while (__VicoContinue) {
        __VicoContinue = 0U;
        Valu___024root___eval_triggers__ico(vlSelf);
        if (vlSelf->__VicoTriggered.any()) {
            __VicoContinue = 1U;
            if (VL_UNLIKELY((0x64U < vlSelf->__VicoIterCount))) {
#ifdef VL_DEBUG
                Valu___024root___dump_triggers__ico(vlSelf);
#endif
                VL_FATAL_MT("/home/knight/桌面/College-Class/ysyx/预学习/ysyx_workbench/npc/3-lab/vsrc/alu.v", 1, "", "Input combinational region did not converge.");
            }
            vlSelf->__VicoIterCount = ((IData)(1U) 
                                       + vlSelf->__VicoIterCount);
            Valu___024root___eval_ico(vlSelf);
        }
    }
    __VnbaIterCount = 0U;
    __VnbaContinue = 1U;
    while (__VnbaContinue) {
        __VnbaContinue = 0U;
        vlSelf->__VnbaTriggered.clear();
        vlSelf->__VactIterCount = 0U;
        vlSelf->__VactContinue = 1U;
        while (vlSelf->__VactContinue) {
            vlSelf->__VactContinue = 0U;
            Valu___024root___eval_triggers__act(vlSelf);
            if (vlSelf->__VactTriggered.any()) {
                vlSelf->__VactContinue = 1U;
                if (VL_UNLIKELY((0x64U < vlSelf->__VactIterCount))) {
#ifdef VL_DEBUG
                    Valu___024root___dump_triggers__act(vlSelf);
#endif
                    VL_FATAL_MT("/home/knight/桌面/College-Class/ysyx/预学习/ysyx_workbench/npc/3-lab/vsrc/alu.v", 1, "", "Active region did not converge.");
                }
                vlSelf->__VactIterCount = ((IData)(1U) 
                                           + vlSelf->__VactIterCount);
                __VpreTriggered.andNot(vlSelf->__VactTriggered, vlSelf->__VnbaTriggered);
                vlSelf->__VnbaTriggered.set(vlSelf->__VactTriggered);
                Valu___024root___eval_act(vlSelf);
            }
        }
        if (vlSelf->__VnbaTriggered.any()) {
            __VnbaContinue = 1U;
            if (VL_UNLIKELY((0x64U < __VnbaIterCount))) {
#ifdef VL_DEBUG
                Valu___024root___dump_triggers__nba(vlSelf);
#endif
                VL_FATAL_MT("/home/knight/桌面/College-Class/ysyx/预学习/ysyx_workbench/npc/3-lab/vsrc/alu.v", 1, "", "NBA region did not converge.");
            }
            __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
            Valu___024root___eval_nba(vlSelf);
        }
    }
}

#ifdef VL_DEBUG
void Valu___024root___eval_debug_assertions(Valu___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Valu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Valu___024root___eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((vlSelf->a & 0xf0U))) {
        Verilated::overWidthError("a");}
    if (VL_UNLIKELY((vlSelf->b & 0xf0U))) {
        Verilated::overWidthError("b");}
    if (VL_UNLIKELY((vlSelf->ctrl & 0xf8U))) {
        Verilated::overWidthError("ctrl");}
}
#endif  // VL_DEBUG
