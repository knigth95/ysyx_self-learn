// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vcode38.h for the primary calling header

#include "verilated.h"

#include "Vcode38___024root.h"

extern const VlUnpacked<CData/*2:0*/, 512> Vcode38__ConstPool__TABLE_h0d68042a_0;
extern const VlUnpacked<CData/*0:0*/, 512> Vcode38__ConstPool__TABLE_h2ab8c13b_0;
extern const VlUnpacked<CData/*7:0*/, 8> Vcode38__ConstPool__TABLE_h171c8c8f_0;

VL_INLINE_OPT void Vcode38___024root___ico_sequent__TOP__0(Vcode38___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcode38__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcode38___024root___ico_sequent__TOP__0\n"); );
    // Init
    SData/*8:0*/ __Vtableidx1;
    __Vtableidx1 = 0;
    CData/*2:0*/ __Vtableidx2;
    __Vtableidx2 = 0;
    // Body
    __Vtableidx1 = (((IData)(vlSelf->i_code) << 1U) 
                    | (IData)(vlSelf->i_en));
    vlSelf->o_code = Vcode38__ConstPool__TABLE_h0d68042a_0
        [__Vtableidx1];
    vlSelf->o_en_flag = Vcode38__ConstPool__TABLE_h2ab8c13b_0
        [__Vtableidx1];
    __Vtableidx2 = vlSelf->o_code;
    vlSelf->o_seg = Vcode38__ConstPool__TABLE_h171c8c8f_0
        [__Vtableidx2];
}

void Vcode38___024root___eval_ico(Vcode38___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcode38__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcode38___024root___eval_ico\n"); );
    // Body
    if (vlSelf->__VicoTriggered.at(0U)) {
        Vcode38___024root___ico_sequent__TOP__0(vlSelf);
    }
}

void Vcode38___024root___eval_act(Vcode38___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcode38__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcode38___024root___eval_act\n"); );
}

void Vcode38___024root___eval_nba(Vcode38___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcode38__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcode38___024root___eval_nba\n"); );
}

void Vcode38___024root___eval_triggers__ico(Vcode38___024root* vlSelf);
#ifdef VL_DEBUG
VL_ATTR_COLD void Vcode38___024root___dump_triggers__ico(Vcode38___024root* vlSelf);
#endif  // VL_DEBUG
void Vcode38___024root___eval_triggers__act(Vcode38___024root* vlSelf);
#ifdef VL_DEBUG
VL_ATTR_COLD void Vcode38___024root___dump_triggers__act(Vcode38___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vcode38___024root___dump_triggers__nba(Vcode38___024root* vlSelf);
#endif  // VL_DEBUG

void Vcode38___024root___eval(Vcode38___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcode38__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcode38___024root___eval\n"); );
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
        Vcode38___024root___eval_triggers__ico(vlSelf);
        if (vlSelf->__VicoTriggered.any()) {
            __VicoContinue = 1U;
            if (VL_UNLIKELY((0x64U < vlSelf->__VicoIterCount))) {
#ifdef VL_DEBUG
                Vcode38___024root___dump_triggers__ico(vlSelf);
#endif
                VL_FATAL_MT("/home/knight/桌面/College-Class/ysyx/预学习/ysyx_workbench/npc/2-lab/vsrc/code38.v", 1, "", "Input combinational region did not converge.");
            }
            vlSelf->__VicoIterCount = ((IData)(1U) 
                                       + vlSelf->__VicoIterCount);
            Vcode38___024root___eval_ico(vlSelf);
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
            Vcode38___024root___eval_triggers__act(vlSelf);
            if (vlSelf->__VactTriggered.any()) {
                vlSelf->__VactContinue = 1U;
                if (VL_UNLIKELY((0x64U < vlSelf->__VactIterCount))) {
#ifdef VL_DEBUG
                    Vcode38___024root___dump_triggers__act(vlSelf);
#endif
                    VL_FATAL_MT("/home/knight/桌面/College-Class/ysyx/预学习/ysyx_workbench/npc/2-lab/vsrc/code38.v", 1, "", "Active region did not converge.");
                }
                vlSelf->__VactIterCount = ((IData)(1U) 
                                           + vlSelf->__VactIterCount);
                __VpreTriggered.andNot(vlSelf->__VactTriggered, vlSelf->__VnbaTriggered);
                vlSelf->__VnbaTriggered.set(vlSelf->__VactTriggered);
                Vcode38___024root___eval_act(vlSelf);
            }
        }
        if (vlSelf->__VnbaTriggered.any()) {
            __VnbaContinue = 1U;
            if (VL_UNLIKELY((0x64U < __VnbaIterCount))) {
#ifdef VL_DEBUG
                Vcode38___024root___dump_triggers__nba(vlSelf);
#endif
                VL_FATAL_MT("/home/knight/桌面/College-Class/ysyx/预学习/ysyx_workbench/npc/2-lab/vsrc/code38.v", 1, "", "NBA region did not converge.");
            }
            __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
            Vcode38___024root___eval_nba(vlSelf);
        }
    }
}

#ifdef VL_DEBUG
void Vcode38___024root___eval_debug_assertions(Vcode38___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcode38__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcode38___024root___eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((vlSelf->i_en & 0xfeU))) {
        Verilated::overWidthError("i_en");}
}
#endif  // VL_DEBUG
