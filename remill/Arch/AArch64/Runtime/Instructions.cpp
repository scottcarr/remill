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

#include "remill/Arch/Runtime/Intrinsics.h"
#include "remill/Arch/Runtime/Operators.h"

#include <fenv.h>
#include <algorithm>
#include <bitset>
#include <cmath>

#include "remill/Arch/AArch64/Runtime/State.h"
#include "remill/Arch/AArch64/Runtime/Operators.h"
#include "remill/Arch/AArch64/Runtime/Types.h"

#define REG_PC state.gpr.pc.qword
#define REG_SP state.gpr.sp.qword
#define REG_LP state.gpr.x30.qword
#define REG_FP state.gpr.x29.qword
#define REG_XZR static_cast<uint64_t>(0)

#define REG_X0 state.gpr.x0.qword
#define REG_X1 state.gpr.x1.qword
#define REG_X2 state.gpr.x2.qword
#define REG_X3 state.gpr.x3.qword

#define REG_X4 state.gpr.x4.qword
#define REG_X5 state.gpr.x5.qword
#define REG_X6 state.gpr.x6.qword
#define REG_X7 state.gpr.x7.qword

#define REG_X8 state.gpr.x8.qword
#define REG_X9 state.gpr.x9.qword
#define REG_X10 state.gpr.x10.qword
#define REG_X11 state.gpr.x11.qword

#define REG_X12 state.gpr.x12.qword
#define REG_X13 state.gpr.x13.qword
#define REG_X14 state.gpr.x14.qword
#define REG_X15 state.gpr.x15.qword

#define REG_X16 state.gpr.x16.qword
#define REG_X17 state.gpr.x17.qword
#define REG_X18 state.gpr.x18.qword
#define REG_X19 state.gpr.x19.qword

#define REG_X20 state.gpr.x20.qword
#define REG_X21 state.gpr.x21.qword
#define REG_X22 state.gpr.x22.qword
#define REG_X23 state.gpr.x23.qword

#define REG_X24 state.gpr.x24.qword
#define REG_X25 state.gpr.x25.qword
#define REG_X26 state.gpr.x26.qword
#define REG_X27 state.gpr.x27.qword

#define REG_X28 state.gpr.x28.qword
#define REG_X29 state.gpr.x29.qword
#define REG_X30 state.gpr.x30.qword

#define FLAG_Z state.sr.z  // Zero flag.
#define FLAG_C state.sr.c  // Carry flag.
#define FLAG_V state.sr.v  // Overflow.
#define FLAG_N state.sr.n  // Negative.

#define HYPER_CALL state.hyper_call
#define INTERRUPT_VECTOR state.interrupt_vector

namespace {
// Takes the place of an unsupported instruction.
DEF_SEM(HandleUnsupported) {
  return __remill_sync_hyper_call(
      state, memory, SyncHyperCall::kAArch64EmulateInstruction);
}

// Takes the place of an invalid instruction.
DEF_SEM(HandleInvalidInstruction) {
  HYPER_CALL = AsyncHyperCall::kInvalidInstruction;
  return memory;
}

}  // namespace

// Takes the place of an unsupported instruction.
DEF_ISEL(UNSUPPORTED_INSTRUCTION) = HandleUnsupported;
DEF_ISEL(INVALID_INSTRUCTION) = HandleInvalidInstruction;

#include "remill/Arch/AArch64/Semantics/FLAGS.cpp"

#include "remill/Arch/AArch64/Semantics/BINARY.cpp"
#include "remill/Arch/AArch64/Semantics/BRANCH.cpp"
#include "remill/Arch/AArch64/Semantics/CALL_RET.cpp"
#include "remill/Arch/AArch64/Semantics/DATAXFER.cpp"
#include "remill/Arch/AArch64/Semantics/MISC.cpp"
#include "remill/Arch/AArch64/Semantics/SHIFT.cpp"
#include "remill/Arch/AArch64/Semantics/NOP.cpp"
