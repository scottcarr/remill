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

namespace {

template <typename D, typename S1, typename S2>
DEF_SEM(DoMOV, D dst, S1, S2 src) {
  Write(dst, Read(src));
  return memory;
}

template <typename D, typename S1, typename S2>
DEF_SEM(DoMOVZ, D dst, S1, S2 src) {
  Write(dst, Read(src));
  return memory;
}

}  // namespace

DEF_ISEL(MOV_R64W_R64_R64) = DoMOV<R64W, R64, R64>;
DEF_ISEL(MOVZ_R64W_R64_U64) = DoMOVZ<R64W, R64, I64>;