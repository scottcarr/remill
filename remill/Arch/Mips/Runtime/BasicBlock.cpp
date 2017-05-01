/*
 * Copyright (c) 2017 Trail of Bits, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "remill/Arch/Mips/Runtime/State.h"

extern "C" {

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-variable"

// Method that will implement a basic block. We will clone this method for
// each basic block in the code being lifted.
[[gnu::used]]
Memory *__remill_basic_block(Memory *memory, State &state, addr_t curr_pc) {

  bool branch_taken = false;
  addr_t zero = 0;

  // Note: These variables MUST be defined for all architectures.
  auto &STATE = state;
  auto &MEMORY = *memory;
  auto &PC = state.gpr.PC.IF_64BIT_ELSE(qword, dword);
  auto &BRANCH_TAKEN = branch_taken;

  // `PC` should already have the correct value, but it's nice to make sure
  // that `curr_pc` is used throughout, as it helps with certain downstream
  // uses to be able to depend on the optimizer not eliminating `curr_pc`.
  PC = curr_pc;

  // We will reference these variables from the bitcode side of things so that,
  // given a decoded register name and an operation type (read or write),
  // we can map the register to a specific field in the State structure.

  auto &A0 = state.gpr.A0;
  auto &A0_64 = state.gpr.A0_64;
  auto &A1 = state.gpr.A1;
  auto &A1_64 = state.gpr.A1_64;
  auto &A2 = state.gpr.A2;
  auto &A2_64 = state.gpr.A2_64;
  auto &A3 = state.gpr.A3;
  auto &A3_64 = state.gpr.A3_64;
  auto &AC0 = state.gpr.AC0;
  auto &AC0_64 = state.gpr.AC0_64;
  auto &AC1 = state.gpr.AC1;
  auto &AC2 = state.gpr.AC2;
  auto &AC3 = state.gpr.AC3;
  auto &AT = state.gpr.AT;
  auto &AT_64 = state.gpr.AT_64;
  auto &COP00 = state.gpr.COP00;
  auto &COP01 = state.gpr.COP01;
  auto &COP010 = state.gpr.COP010;
  auto &COP011 = state.gpr.COP011;
  auto &COP012 = state.gpr.COP012;
  auto &COP013 = state.gpr.COP013;
  auto &COP014 = state.gpr.COP014;
  auto &COP015 = state.gpr.COP015;
  auto &COP016 = state.gpr.COP016;
  auto &COP017 = state.gpr.COP017;
  auto &COP018 = state.gpr.COP018;
  auto &COP019 = state.gpr.COP019;
  auto &COP02 = state.gpr.COP02;
  auto &COP020 = state.gpr.COP020;
  auto &COP021 = state.gpr.COP021;
  auto &COP022 = state.gpr.COP022;
  auto &COP023 = state.gpr.COP023;
  auto &COP024 = state.gpr.COP024;
  auto &COP025 = state.gpr.COP025;
  auto &COP026 = state.gpr.COP026;
  auto &COP027 = state.gpr.COP027;
  auto &COP028 = state.gpr.COP028;
  auto &COP029 = state.gpr.COP029;
  auto &COP03 = state.gpr.COP03;
  auto &COP030 = state.gpr.COP030;
  auto &COP031 = state.gpr.COP031;
  auto &COP04 = state.gpr.COP04;
  auto &COP05 = state.gpr.COP05;
  auto &COP06 = state.gpr.COP06;
  auto &COP07 = state.gpr.COP07;
  auto &COP08 = state.gpr.COP08;
  auto &COP09 = state.gpr.COP09;
  auto &COP20 = state.gpr.COP20;
  auto &COP21 = state.gpr.COP21;
  auto &COP210 = state.gpr.COP210;
  auto &COP211 = state.gpr.COP211;
  auto &COP212 = state.gpr.COP212;
  auto &COP213 = state.gpr.COP213;
  auto &COP214 = state.gpr.COP214;
  auto &COP215 = state.gpr.COP215;
  auto &COP216 = state.gpr.COP216;
  auto &COP217 = state.gpr.COP217;
  auto &COP218 = state.gpr.COP218;
  auto &COP219 = state.gpr.COP219;
  auto &COP22 = state.gpr.COP22;
  auto &COP220 = state.gpr.COP220;
  auto &COP221 = state.gpr.COP221;
  auto &COP222 = state.gpr.COP222;
  auto &COP223 = state.gpr.COP223;
  auto &COP224 = state.gpr.COP224;
  auto &COP225 = state.gpr.COP225;
  auto &COP226 = state.gpr.COP226;
  auto &COP227 = state.gpr.COP227;
  auto &COP228 = state.gpr.COP228;
  auto &COP229 = state.gpr.COP229;
  auto &COP23 = state.gpr.COP23;
  auto &COP230 = state.gpr.COP230;
  auto &COP231 = state.gpr.COP231;
  auto &COP24 = state.gpr.COP24;
  auto &COP25 = state.gpr.COP25;
  auto &COP26 = state.gpr.COP26;
  auto &COP27 = state.gpr.COP27;
  auto &COP28 = state.gpr.COP28;
  auto &COP29 = state.gpr.COP29;
  auto &COP30 = state.gpr.COP30;
  auto &COP31 = state.gpr.COP31;
  auto &COP310 = state.gpr.COP310;
  auto &COP311 = state.gpr.COP311;
  auto &COP312 = state.gpr.COP312;
  auto &COP313 = state.gpr.COP313;
  auto &COP314 = state.gpr.COP314;
  auto &COP315 = state.gpr.COP315;
  auto &COP316 = state.gpr.COP316;
  auto &COP317 = state.gpr.COP317;
  auto &COP318 = state.gpr.COP318;
  auto &COP319 = state.gpr.COP319;
  auto &COP32 = state.gpr.COP32;
  auto &COP320 = state.gpr.COP320;
  auto &COP321 = state.gpr.COP321;
  auto &COP322 = state.gpr.COP322;
  auto &COP323 = state.gpr.COP323;
  auto &COP324 = state.gpr.COP324;
  auto &COP325 = state.gpr.COP325;
  auto &COP326 = state.gpr.COP326;
  auto &COP327 = state.gpr.COP327;
  auto &COP328 = state.gpr.COP328;
  auto &COP329 = state.gpr.COP329;
  auto &COP33 = state.gpr.COP33;
  auto &COP330 = state.gpr.COP330;
  auto &COP331 = state.gpr.COP331;
  auto &COP34 = state.gpr.COP34;
  auto &COP35 = state.gpr.COP35;
  auto &COP36 = state.gpr.COP36;
  auto &COP37 = state.gpr.COP37;
  auto &COP38 = state.gpr.COP38;
  auto &COP39 = state.gpr.COP39;
  auto &D0 = state.gpr.D0;
  auto &D0_64 = state.gpr.D0_64;
  auto &D1 = state.gpr.D1;
  auto &D10 = state.gpr.D10;
  auto &D10_64 = state.gpr.D10_64;
  auto &D11 = state.gpr.D11;
  auto &D11_64 = state.gpr.D11_64;
  auto &D12 = state.gpr.D12;
  auto &D12_64 = state.gpr.D12_64;
  auto &D13 = state.gpr.D13;
  auto &D13_64 = state.gpr.D13_64;
  auto &D14 = state.gpr.D14;
  auto &D14_64 = state.gpr.D14_64;
  auto &D15 = state.gpr.D15;
  auto &D15_64 = state.gpr.D15_64;
  auto &D16_64 = state.gpr.D16_64;
  auto &D17_64 = state.gpr.D17_64;
  auto &D18_64 = state.gpr.D18_64;
  auto &D19_64 = state.gpr.D19_64;
  auto &D1_64 = state.gpr.D1_64;
  auto &D2 = state.gpr.D2;
  auto &D20_64 = state.gpr.D20_64;
  auto &D21_64 = state.gpr.D21_64;
  auto &D22_64 = state.gpr.D22_64;
  auto &D23_64 = state.gpr.D23_64;
  auto &D24_64 = state.gpr.D24_64;
  auto &D25_64 = state.gpr.D25_64;
  auto &D26_64 = state.gpr.D26_64;
  auto &D27_64 = state.gpr.D27_64;
  auto &D28_64 = state.gpr.D28_64;
  auto &D29_64 = state.gpr.D29_64;
  auto &D2_64 = state.gpr.D2_64;
  auto &D3 = state.gpr.D3;
  auto &D30_64 = state.gpr.D30_64;
  auto &D31_64 = state.gpr.D31_64;
  auto &D3_64 = state.gpr.D3_64;
  auto &D4 = state.gpr.D4;
  auto &D4_64 = state.gpr.D4_64;
  auto &D5 = state.gpr.D5;
  auto &D5_64 = state.gpr.D5_64;
  auto &D6 = state.gpr.D6;
  auto &D6_64 = state.gpr.D6_64;
  auto &D7 = state.gpr.D7;
  auto &D7_64 = state.gpr.D7_64;
  auto &D8 = state.gpr.D8;
  auto &D8_64 = state.gpr.D8_64;
  auto &D9 = state.gpr.D9;
  auto &D9_64 = state.gpr.D9_64;
  auto &DSPCCond = state.gpr.DSPCCond;
  auto &DSPCarry = state.gpr.DSPCarry;
  auto &DSPEFI = state.gpr.DSPEFI;
  auto &DSPOutFlag = state.gpr.DSPOutFlag;
  auto &DSPOutFlag16_19 = state.gpr.DSPOutFlag16_19;
  auto &DSPOutFlag20 = state.gpr.DSPOutFlag20;
  auto &DSPOutFlag21 = state.gpr.DSPOutFlag21;
  auto &DSPOutFlag22 = state.gpr.DSPOutFlag22;
  auto &DSPOutFlag23 = state.gpr.DSPOutFlag23;
  auto &DSPPos = state.gpr.DSPPos;
  auto &DSPSCount = state.gpr.DSPSCount;
  auto &F0 = state.gpr.F0;
  auto &F1 = state.gpr.F1;
  auto &F10 = state.gpr.F10;
  auto &F11 = state.gpr.F11;
  auto &F12 = state.gpr.F12;
  auto &F13 = state.gpr.F13;
  auto &F14 = state.gpr.F14;
  auto &F15 = state.gpr.F15;
  auto &F16 = state.gpr.F16;
  auto &F17 = state.gpr.F17;
  auto &F18 = state.gpr.F18;
  auto &F19 = state.gpr.F19;
  auto &F2 = state.gpr.F2;
  auto &F20 = state.gpr.F20;
  auto &F21 = state.gpr.F21;
  auto &F22 = state.gpr.F22;
  auto &F23 = state.gpr.F23;
  auto &F24 = state.gpr.F24;
  auto &F25 = state.gpr.F25;
  auto &F26 = state.gpr.F26;
  auto &F27 = state.gpr.F27;
  auto &F28 = state.gpr.F28;
  auto &F29 = state.gpr.F29;
  auto &F3 = state.gpr.F3;
  auto &F30 = state.gpr.F30;
  auto &F31 = state.gpr.F31;
  auto &F4 = state.gpr.F4;
  auto &F5 = state.gpr.F5;
  auto &F6 = state.gpr.F6;
  auto &F7 = state.gpr.F7;
  auto &F8 = state.gpr.F8;
  auto &F9 = state.gpr.F9;
  auto &FCC0 = state.gpr.FCC0;
  auto &FCC1 = state.gpr.FCC1;
  auto &FCC2 = state.gpr.FCC2;
  auto &FCC3 = state.gpr.FCC3;
  auto &FCC4 = state.gpr.FCC4;
  auto &FCC5 = state.gpr.FCC5;
  auto &FCC6 = state.gpr.FCC6;
  auto &FCC7 = state.gpr.FCC7;
  auto &FCR0 = state.gpr.FCR0;
  auto &FCR1 = state.gpr.FCR1;
  auto &FCR10 = state.gpr.FCR10;
  auto &FCR11 = state.gpr.FCR11;
  auto &FCR12 = state.gpr.FCR12;
  auto &FCR13 = state.gpr.FCR13;
  auto &FCR14 = state.gpr.FCR14;
  auto &FCR15 = state.gpr.FCR15;
  auto &FCR16 = state.gpr.FCR16;
  auto &FCR17 = state.gpr.FCR17;
  auto &FCR18 = state.gpr.FCR18;
  auto &FCR19 = state.gpr.FCR19;
  auto &FCR2 = state.gpr.FCR2;
  auto &FCR20 = state.gpr.FCR20;
  auto &FCR21 = state.gpr.FCR21;
  auto &FCR22 = state.gpr.FCR22;
  auto &FCR23 = state.gpr.FCR23;
  auto &FCR24 = state.gpr.FCR24;
  auto &FCR25 = state.gpr.FCR25;
  auto &FCR26 = state.gpr.FCR26;
  auto &FCR27 = state.gpr.FCR27;
  auto &FCR28 = state.gpr.FCR28;
  auto &FCR29 = state.gpr.FCR29;
  auto &FCR3 = state.gpr.FCR3;
  auto &FCR30 = state.gpr.FCR30;
  auto &FCR31 = state.gpr.FCR31;
  auto &FCR4 = state.gpr.FCR4;
  auto &FCR5 = state.gpr.FCR5;
  auto &FCR6 = state.gpr.FCR6;
  auto &FCR7 = state.gpr.FCR7;
  auto &FCR8 = state.gpr.FCR8;
  auto &FCR9 = state.gpr.FCR9;
  auto &FP = state.gpr.FP;
  auto &FP_64 = state.gpr.FP_64;
  auto &F_HI0 = state.gpr.F_HI0;
  auto &F_HI1 = state.gpr.F_HI1;
  auto &F_HI10 = state.gpr.F_HI10;
  auto &F_HI11 = state.gpr.F_HI11;
  auto &F_HI12 = state.gpr.F_HI12;
  auto &F_HI13 = state.gpr.F_HI13;
  auto &F_HI14 = state.gpr.F_HI14;
  auto &F_HI15 = state.gpr.F_HI15;
  auto &F_HI16 = state.gpr.F_HI16;
  auto &F_HI17 = state.gpr.F_HI17;
  auto &F_HI18 = state.gpr.F_HI18;
  auto &F_HI19 = state.gpr.F_HI19;
  auto &F_HI2 = state.gpr.F_HI2;
  auto &F_HI20 = state.gpr.F_HI20;
  auto &F_HI21 = state.gpr.F_HI21;
  auto &F_HI22 = state.gpr.F_HI22;
  auto &F_HI23 = state.gpr.F_HI23;
  auto &F_HI24 = state.gpr.F_HI24;
  auto &F_HI25 = state.gpr.F_HI25;
  auto &F_HI26 = state.gpr.F_HI26;
  auto &F_HI27 = state.gpr.F_HI27;
  auto &F_HI28 = state.gpr.F_HI28;
  auto &F_HI29 = state.gpr.F_HI29;
  auto &F_HI3 = state.gpr.F_HI3;
  auto &F_HI30 = state.gpr.F_HI30;
  auto &F_HI31 = state.gpr.F_HI31;
  auto &F_HI4 = state.gpr.F_HI4;
  auto &F_HI5 = state.gpr.F_HI5;
  auto &F_HI6 = state.gpr.F_HI6;
  auto &F_HI7 = state.gpr.F_HI7;
  auto &F_HI8 = state.gpr.F_HI8;
  auto &F_HI9 = state.gpr.F_HI9;
  auto &GP = state.gpr.GP;
  auto &GP_64 = state.gpr.GP_64;
  auto &HI0 = state.gpr.HI0;
  auto &HI0_64 = state.gpr.HI0_64;
  auto &HI1 = state.gpr.HI1;
  auto &HI2 = state.gpr.HI2;
  auto &HI3 = state.gpr.HI3;
  auto &HWR0 = state.gpr.HWR0;
  auto &HWR1 = state.gpr.HWR1;
  auto &HWR10 = state.gpr.HWR10;
  auto &HWR11 = state.gpr.HWR11;
  auto &HWR12 = state.gpr.HWR12;
  auto &HWR13 = state.gpr.HWR13;
  auto &HWR14 = state.gpr.HWR14;
  auto &HWR15 = state.gpr.HWR15;
  auto &HWR16 = state.gpr.HWR16;
  auto &HWR17 = state.gpr.HWR17;
  auto &HWR18 = state.gpr.HWR18;
  auto &HWR19 = state.gpr.HWR19;
  auto &HWR2 = state.gpr.HWR2;
  auto &HWR20 = state.gpr.HWR20;
  auto &HWR21 = state.gpr.HWR21;
  auto &HWR22 = state.gpr.HWR22;
  auto &HWR23 = state.gpr.HWR23;
  auto &HWR24 = state.gpr.HWR24;
  auto &HWR25 = state.gpr.HWR25;
  auto &HWR26 = state.gpr.HWR26;
  auto &HWR27 = state.gpr.HWR27;
  auto &HWR28 = state.gpr.HWR28;
  auto &HWR29 = state.gpr.HWR29;
  auto &HWR3 = state.gpr.HWR3;
  auto &HWR30 = state.gpr.HWR30;
  auto &HWR31 = state.gpr.HWR31;
  auto &HWR4 = state.gpr.HWR4;
  auto &HWR5 = state.gpr.HWR5;
  auto &HWR6 = state.gpr.HWR6;
  auto &HWR7 = state.gpr.HWR7;
  auto &HWR8 = state.gpr.HWR8;
  auto &HWR9 = state.gpr.HWR9;
  auto &K0 = state.gpr.K0;
  auto &K0_64 = state.gpr.K0_64;
  auto &K1 = state.gpr.K1;
  auto &K1_64 = state.gpr.K1_64;
  auto &LO0 = state.gpr.LO0;
  auto &LO0_64 = state.gpr.LO0_64;
  auto &LO1 = state.gpr.LO1;
  auto &LO2 = state.gpr.LO2;
  auto &LO3 = state.gpr.LO3;
  auto &MPL0 = state.gpr.MPL0;
  auto &MPL1 = state.gpr.MPL1;
  auto &MPL2 = state.gpr.MPL2;
  auto &MSAAccess = state.gpr.MSAAccess;
  auto &MSACSR = state.gpr.MSACSR;
  auto &MSAIR = state.gpr.MSAIR;
  auto &MSAMap = state.gpr.MSAMap;
  auto &MSAModify = state.gpr.MSAModify;
  auto &MSARequest = state.gpr.MSARequest;
  auto &MSASave = state.gpr.MSASave;
  auto &MSAUnmap = state.gpr.MSAUnmap;
  auto &P0 = state.gpr.P0;
  auto &P1 = state.gpr.P1;
  auto &P2 = state.gpr.P2;
  auto &RA = state.gpr.RA;
  auto &RA_64 = state.gpr.RA_64;
  auto &S0 = state.gpr.S0;
  auto &S0_64 = state.gpr.S0_64;
  auto &S1 = state.gpr.S1;
  auto &S1_64 = state.gpr.S1_64;
  auto &S2 = state.gpr.S2;
  auto &S2_64 = state.gpr.S2_64;
  auto &S3 = state.gpr.S3;
  auto &S3_64 = state.gpr.S3_64;
  auto &S4 = state.gpr.S4;
  auto &S4_64 = state.gpr.S4_64;
  auto &S5 = state.gpr.S5;
  auto &S5_64 = state.gpr.S5_64;
  auto &S6 = state.gpr.S6;
  auto &S6_64 = state.gpr.S6_64;
  auto &S7 = state.gpr.S7;
  auto &S7_64 = state.gpr.S7_64;
  auto &SP = state.gpr.SP;
  auto &SP_64 = state.gpr.SP_64;
  auto &T0 = state.gpr.T0;
  auto &T0_64 = state.gpr.T0_64;
  auto &T1 = state.gpr.T1;
  auto &T1_64 = state.gpr.T1_64;
  auto &T2 = state.gpr.T2;
  auto &T2_64 = state.gpr.T2_64;
  auto &T3 = state.gpr.T3;
  auto &T3_64 = state.gpr.T3_64;
  auto &T4 = state.gpr.T4;
  auto &T4_64 = state.gpr.T4_64;
  auto &T5 = state.gpr.T5;
  auto &T5_64 = state.gpr.T5_64;
  auto &T6 = state.gpr.T6;
  auto &T6_64 = state.gpr.T6_64;
  auto &T7 = state.gpr.T7;
  auto &T7_64 = state.gpr.T7_64;
  auto &T8 = state.gpr.T8;
  auto &T8_64 = state.gpr.T8_64;
  auto &T9 = state.gpr.T9;
  auto &T9_64 = state.gpr.T9_64;
  auto &V0 = state.gpr.V0;
  auto &V0_64 = state.gpr.V0_64;
  auto &V1 = state.gpr.V1;
  auto &V1_64 = state.gpr.V1_64;
  auto &W0 = state.gpr.W0;
  auto &W1 = state.gpr.W1;
  auto &W10 = state.gpr.W10;
  auto &W11 = state.gpr.W11;
  auto &W12 = state.gpr.W12;
  auto &W13 = state.gpr.W13;
  auto &W14 = state.gpr.W14;
  auto &W15 = state.gpr.W15;
  auto &W16 = state.gpr.W16;
  auto &W17 = state.gpr.W17;
  auto &W18 = state.gpr.W18;
  auto &W19 = state.gpr.W19;
  auto &W2 = state.gpr.W2;
  auto &W20 = state.gpr.W20;
  auto &W21 = state.gpr.W21;
  auto &W22 = state.gpr.W22;
  auto &W23 = state.gpr.W23;
  auto &W24 = state.gpr.W24;
  auto &W25 = state.gpr.W25;
  auto &W26 = state.gpr.W26;
  auto &W27 = state.gpr.W27;
  auto &W28 = state.gpr.W28;
  auto &W29 = state.gpr.W29;
  auto &W3 = state.gpr.W3;
  auto &W30 = state.gpr.W30;
  auto &W31 = state.gpr.W31;
  auto &W4 = state.gpr.W4;
  auto &W5 = state.gpr.W5;
  auto &W6 = state.gpr.W6;
  auto &W7 = state.gpr.W7;
  auto &W8 = state.gpr.W8;
  auto &W9 = state.gpr.W9;
  auto &ZERO = state.gpr.ZERO;
  auto &ZERO_64 = state.gpr.ZERO_64;

  // Lifted code will be placed here in clones versions of this function.
  return nullptr;
}

#pragma clang diagnostic pop

}  // extern C

#include "remill/Arch/Runtime/Intrinsics.cpp"