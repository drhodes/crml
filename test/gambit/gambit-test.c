#ifdef ___LINKER_INFO
; File: "gambit-test.c", produced by Gambit-C v4.6.0
(
406000
" gambit-test.o1"
(" gambit-test.o1")
(
)
(
)
(
" gambit-test.o1"
)
(
)
(
"display"
"newline"
)
 #f
)
#else
#define ___VERSION 406000
#define ___MODULE_NAME " gambit-test.o1"
#define ___LINKER_ID ____20_gambit_2d_test_2e_o1
#define ___MH_PROC ___H__20_gambit_2d_test_2e_o1
#define ___SCRIPT_LINE 0
#define ___GLO_COUNT 3
#define ___SUP_COUNT 1
#define ___SUB_COUNT 1
#define ___LBL_COUNT 5
#include "gambit.h"

___NEED_GLO(___G__20_gambit_2d_test_2e_o1)
___NEED_GLO(___G_display)
___NEED_GLO(___G_newline)

___BEGIN_GLO
___DEF_GLO(0," gambit-test.o1")
___DEF_GLO(1,"display")
___DEF_GLO(2,"newline")
___END_GLO

___DEF_SUB_STR(___X0,5)
               ___STR5(104,101,108,108,111)

___BEGIN_SUB
 ___DEF_SUB(___X0)
___END_SUB



#undef ___MD_ALL
#define ___MD_ALL ___D_FP ___D_R0 ___D_R1 ___D_R4
#undef ___MR_ALL
#define ___MR_ALL ___R_FP ___R_R0 ___R_R1 ___R_R4
#undef ___MW_ALL
#define ___MW_ALL ___W_FP ___W_R0 ___W_R1 ___W_R4
___BEGIN_M_COD
___BEGIN_M_HLBL
___DEF_M_HLBL_INTRO
___DEF_M_HLBL(___L0__20_gambit_2d_test_2e_o1)
___DEF_M_HLBL(___L1__20_gambit_2d_test_2e_o1)
___DEF_M_HLBL(___L2__20_gambit_2d_test_2e_o1)
___DEF_M_HLBL(___L3__20_gambit_2d_test_2e_o1)
___END_M_HLBL

___BEGIN_M_SW

#undef ___PH_PROC
#define ___PH_PROC ___H__20_gambit_2d_test_2e_o1
#undef ___PH_LBL0
#define ___PH_LBL0 1
#undef ___PD_ALL
#define ___PD_ALL ___D_FP ___D_R0 ___D_R1 ___D_R4
#undef ___PR_ALL
#define ___PR_ALL ___R_FP ___R_R0 ___R_R1 ___R_R4
#undef ___PW_ALL
#define ___PW_ALL ___W_FP ___W_R0 ___W_R1 ___W_R4
___BEGIN_P_COD
___BEGIN_P_HLBL
___DEF_P_HLBL_INTRO
___DEF_P_HLBL(___L0__20_gambit_2d_test_2e_o1)
___DEF_P_HLBL(___L1__20_gambit_2d_test_2e_o1)
___DEF_P_HLBL(___L2__20_gambit_2d_test_2e_o1)
___DEF_P_HLBL(___L3__20_gambit_2d_test_2e_o1)
___END_P_HLBL
___BEGIN_P_SW
___DEF_SLBL(0,___L0__20_gambit_2d_test_2e_o1)
   ___IF_NARGS_EQ(0,___NOTHING)
   ___WRONG_NARGS(0,0,0,0)
___DEF_GLBL(___L__20_gambit_2d_test_2e_o1)
   ___SET_STK(1,___R0)
   ___SET_R1(___SUB(0))
   ___SET_R0(___LBL(2))
   ___ADJFP(4)
   ___POLL(1)
___DEF_SLBL(1,___L1__20_gambit_2d_test_2e_o1)
   ___JUMPGLOSAFE(___SET_NARGS(1),1,___G_display)
___DEF_SLBL(2,___L2__20_gambit_2d_test_2e_o1)
   ___SET_R0(___STK(-3))
   ___POLL(3)
___DEF_SLBL(3,___L3__20_gambit_2d_test_2e_o1)
   ___ADJFP(-4)
   ___JUMPGLOSAFE(___SET_NARGS(0),2,___G_newline)
___END_P_SW
___END_P_COD

___END_M_SW
___END_M_COD

___BEGIN_LBL
 ___DEF_LBL_INTRO(___H__20_gambit_2d_test_2e_o1," gambit-test.o1",___REF_FAL,4,0)
,___DEF_LBL_PROC(___H__20_gambit_2d_test_2e_o1,0,0)
,___DEF_LBL_RET(___H__20_gambit_2d_test_2e_o1,___IFD(___RETI,4,0,0x3f1L))
,___DEF_LBL_RET(___H__20_gambit_2d_test_2e_o1,___IFD(___RETN,1,0,0x1L))
,___DEF_LBL_RET(___H__20_gambit_2d_test_2e_o1,___IFD(___RETI,4,4,0x3f0L))
___END_LBL

___BEGIN_MOD1
___DEF_PRM(0,___G__20_gambit_2d_test_2e_o1,1)
___END_MOD1

___BEGIN_MOD2
___END_MOD2

#endif
