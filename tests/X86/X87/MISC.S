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

TEST_BEGIN(FNOP, 1)
TEST_INPUTS(0)
    fnop
TEST_END

TEST_BEGIN(FWAIT, 1)
TEST_INPUTS(0)
    // fwait
    .byte 0x9b
TEST_END

TEST_BEGIN(FNCLEX, 1)
    fnclex
TEST_END

TEST_BEGIN_64(FABS, 1)
TEST_INPUTS(
    0x7ff0000000000000,  /* +inf */
    0xfff0000000000000,  /* -inf */
    0x3fe0000000000000,  /* 0.5 */
    0xbfe0000000000000  /* -0.5 */)

    push ARG1_64
    fld QWORD PTR [rsp]
    fabs
TEST_END_64

TEST_BEGIN_64(FCHS, 1)
TEST_INPUTS(
    0x7ff0000000000000,  /* +inf */
    0xfff0000000000000,  /* -inf */
    0x3fe0000000000000,  /* 0.5 */
    0xbfe0000000000000  /* -0.5 */)

    push ARG1_64
    fld QWORD PTR [rsp]
    fchs
TEST_END_64

TEST_BEGIN_64(FCOS, 1)
TEST_INPUTS(
    0x4058ff5c28f5c28f,  /* 99.99 */
    0xc058ff5c28f5c28f  /* -99.99 */)

    push ARG1_64
    fld QWORD PTR [rsp]
    fcos
TEST_END_64

TEST_BEGIN_64(FSIN, 1)
TEST_INPUTS(
    0x4058ff5c28f5c28f,  /* 99.99 */
    0xc058ff5c28f5c28f  /* -99.99 */)

    push ARG1_64
    fld QWORD PTR [rsp]
    fsin
TEST_END_64

TEST_BEGIN_64(FSINCOS, 1)
TEST_INPUTS(
    0x4058ff5c28f5c28f,  /* 99.99 */
    0xc058ff5c28f5c28f  /* -99.99 */)

    push ARG1_64
    fld QWORD PTR [rsp]
    fsincos
TEST_END_64

TEST_BEGIN_64(FSCALE, 1)
TEST_INPUTS(
    0x401199999999999a,  /* 4.4 */
    0x4012000000000000,  /* 4.5 */
    0x4012666666666666,  /* 4.6 */
    0xc01199999999999a,  /* -4.4 */
    0xc012000000000000,  /* -4.5 */
    0xc012666666666666)  /* -4.6 */

    push ARG1_64
    fld QWORD PTR [rsp]
    fldlg2
    fscale
TEST_END_64

TEST_BEGIN_64(FPREM, 2)
TEST_INPUTS(
    0x4058ff5c28f5c28f, /* 99.99 */ 0x401199999999999a,  /* 4.4 */
    0x4058ff5c28f5c28f, /* 99.99 */ 0xc01199999999999a,  /* -4.4 */
    0xc058ff5c28f5c28f, /* -99.99 */ 0x401199999999999a,  /* 4.4 */
    0xc058ff5c28f5c28f, /* -99.99 */ 0xc01199999999999a)  /* -4.4 */

    push ARG2_64
    fld QWORD PTR [rsp]
    push ARG1_64
    fld QWORD PTR [rsp]
    fprem
TEST_END_64

TEST_BEGIN_64(FPREM1, 2)
TEST_INPUTS(
    0x4058ff5c28f5c28f, /* 99.99 */ 0x401199999999999a,  /* 4.4 */
    0x4058ff5c28f5c28f, /* 99.99 */ 0xc01199999999999a,  /* -4.4 */
    0xc058ff5c28f5c28f, /* -99.99 */ 0x401199999999999a,  /* 4.4 */
    0xc058ff5c28f5c28f, /* -99.99 */ 0xc01199999999999a)  /* -4.4 */

    push ARG2_64
    fld QWORD PTR [rsp]
    push ARG1_64
    fld QWORD PTR [rsp]
    fprem1
TEST_END_64

TEST_BEGIN_64(F2XM1, 1)
TEST_INPUTS(
    0x3fe0000000000000,  /* 0.5 */
    0xbfe0000000000000  /* -0.5 */)

    push ARG1_64
    fld QWORD PTR [rsp]
    f2xm1
TEST_END_64

TEST_BEGIN(FPTAN, 1)
TEST_INPUTS(0)
    fldl2e
    fptan
TEST_END

TEST_BEGIN(FPATAN, 1)
TEST_INPUTS(0)
    fldl2e
    fldlg2
    fpatan
TEST_END

TEST_BEGIN(FSQRT, 1)
TEST_INPUTS(0)
    fldl2e
    fsqrt
TEST_END

TEST_BEGIN(FDECSTP, 1)
TEST_INPUTS(0)
    fldl2e
    fldlg2
    fdecstp
TEST_END

TEST_BEGIN(FINCSTP, 1)
TEST_INPUTS(0)
    fldl2e
    fldlg2
    fincstp
TEST_END

/* Note: We don't test these denormals because, by the time they get into the
 *       FPU, the fact that they were denormal as 64-bit floats has been lost
 *       to the higher precision of the FPU.
 *
 *     0x0008000000000000,  // std::numeric_limits<double>::min() / 2.0
 *     0x8008000000000000,  // std::numeric_limits<double>::min() / -2.0 */

TEST_BEGIN_64(FXAM, 1)
TEST_INPUTS(
    0x7ff0000000000000,  /* +inf */
    0xfff0000000000000,  /* -inf */
    0xfff8000000000000,  /* -nan */
    0x7ff8000000000000,  /* nan */
    0x0010000000000000,  /* std::numeric_limits<double>::min() */
    0x7fefffffffffffff,  /* std::numeric_limits<double>::max() */
    0x0000000000000000,  /* +0 */
    0x8000000000000000) /* -0 */

    push ARG1_64
    fld QWORD PTR [rsp]
    fxam
TEST_END_64

TEST_BEGIN_64(FTST, 1)
TEST_INPUTS(
    0x7ff0000000000000,  /* +inf */
    0xfff0000000000000,  /* -inf */
    0xfff8000000000000,  /* -nan */
    0x7ff8000000000000,  /* nan */
    0x0010000000000000,  /* std::numeric_limits<double>::min() */
    0x7fefffffffffffff,  /* std::numeric_limits<double>::max() */
    0x0008000000000000,  /* std::numeric_limits<double>::min() / 2.0 */
    0x8008000000000000,  /* std::numeric_limits<double>::min() / -2.0 */
    0x0000000000000000,  /* +0 */
    0x8000000000000000, /* -0 */
    0x3fe0000000000000,  /* 0.5 */
    0xbfe0000000000000)  /* -0.5 */

    push ARG1_64
    fld QWORD PTR [rsp]
    ftst
TEST_END_64

TEST_BEGIN_64(FRNDINT, 1)
TEST_INPUTS(
    0x401199999999999a,  /* 4.4 */
    0x4012000000000000,  /* 4.5 */
    0x4012666666666666,  /* 4.6 */
    0xc01199999999999a,  /* -4.4 */
    0xc012000000000000,  /* -4.5 */
    0xc012666666666666)  /* -4.6 */

    push ARG1_64
    fld QWORD PTR [rsp]
    frndint
TEST_END_64

TEST_BEGIN(FY2LX, 1)
TEST_INPUTS(0)
    fldpi
    fldlg2
    fyl2x
TEST_END

TEST_BEGIN(FY2LXP1, 1)
TEST_INPUTS(0)
    fldpi
    fldlg2
    fyl2xp1
TEST_END
