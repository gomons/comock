// MIT License
//
// Copyright (c) 2025 Siarhei Homan
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma once

// Minimal preprocessor metaprogramming for comock
// Replaces boost.preprocessor dependency (401 files -> 1 file)
// Supports sequences up to 16 elements
//
// Sequence format: (elem1)(elem2)(elem3)
// - Each element wrapped in parentheses
// - Handles types with commas (e.g., std::map<int, int>)
//
// Key behaviors (matching boost.preprocessor):
// - SEQ_FOR_EACH_I uses 0-based indices
// - First element is often (void) as a sentinel
// - Index 0 gets skipped by IF(Index, ...) checks

// ============================================================================
// Basic utilities
// ============================================================================

#define COMOCK_PP_CAT(a, b) COMOCK_PP_CAT_I(a, b)
#define COMOCK_PP_CAT_I(a, b) a##b

#define COMOCK_PP_EMPTY()

#define COMOCK_PP_IF(cond, t, f) COMOCK_PP_CAT(COMOCK_PP_IF_, cond)(t, f)
#define COMOCK_PP_IF_0(t, f) f
#define COMOCK_PP_IF_1(t, f) t
#define COMOCK_PP_IF_2(t, f) t
#define COMOCK_PP_IF_3(t, f) t
#define COMOCK_PP_IF_4(t, f) t
#define COMOCK_PP_IF_5(t, f) t
#define COMOCK_PP_IF_6(t, f) t
#define COMOCK_PP_IF_7(t, f) t
#define COMOCK_PP_IF_8(t, f) t
#define COMOCK_PP_IF_9(t, f) t
#define COMOCK_PP_IF_10(t, f) t
#define COMOCK_PP_IF_11(t, f) t
#define COMOCK_PP_IF_12(t, f) t
#define COMOCK_PP_IF_13(t, f) t
#define COMOCK_PP_IF_14(t, f) t
#define COMOCK_PP_IF_15(t, f) t
#define COMOCK_PP_IF_16(t, f) t

#define COMOCK_PP_COMMA_IF(cond) COMOCK_PP_CAT(COMOCK_PP_COMMA_IF_, cond)
#define COMOCK_PP_COMMA_IF_0
#define COMOCK_PP_COMMA_IF_1 ,
#define COMOCK_PP_COMMA_IF_2 ,
#define COMOCK_PP_COMMA_IF_3 ,
#define COMOCK_PP_COMMA_IF_4 ,
#define COMOCK_PP_COMMA_IF_5 ,
#define COMOCK_PP_COMMA_IF_6 ,
#define COMOCK_PP_COMMA_IF_7 ,
#define COMOCK_PP_COMMA_IF_8 ,
#define COMOCK_PP_COMMA_IF_9 ,
#define COMOCK_PP_COMMA_IF_10 ,
#define COMOCK_PP_COMMA_IF_11 ,
#define COMOCK_PP_COMMA_IF_12 ,
#define COMOCK_PP_COMMA_IF_13 ,
#define COMOCK_PP_COMMA_IF_14 ,
#define COMOCK_PP_COMMA_IF_15 ,
#define COMOCK_PP_COMMA_IF_16 ,

#define COMOCK_PP_NIL

// ============================================================================
// Arithmetic
// ============================================================================

#define COMOCK_PP_DEC(x) COMOCK_PP_CAT(COMOCK_PP_DEC_, x)
#define COMOCK_PP_DEC_0 0
#define COMOCK_PP_DEC_1 0
#define COMOCK_PP_DEC_2 1
#define COMOCK_PP_DEC_3 2
#define COMOCK_PP_DEC_4 3
#define COMOCK_PP_DEC_5 4
#define COMOCK_PP_DEC_6 5
#define COMOCK_PP_DEC_7 6
#define COMOCK_PP_DEC_8 7
#define COMOCK_PP_DEC_9 8
#define COMOCK_PP_DEC_10 9
#define COMOCK_PP_DEC_11 10
#define COMOCK_PP_DEC_12 11
#define COMOCK_PP_DEC_13 12
#define COMOCK_PP_DEC_14 13
#define COMOCK_PP_DEC_15 14
#define COMOCK_PP_DEC_16 15

#define COMOCK_PP_GREATER(x, y) COMOCK_PP_CAT(COMOCK_PP_GREATER_, x##_##y)
#define COMOCK_PP_GREATER_0_0 0
#define COMOCK_PP_GREATER_0_1 0
#define COMOCK_PP_GREATER_0_2 0
#define COMOCK_PP_GREATER_1_0 1
#define COMOCK_PP_GREATER_1_1 0
#define COMOCK_PP_GREATER_1_2 0
#define COMOCK_PP_GREATER_2_0 1
#define COMOCK_PP_GREATER_2_1 1
#define COMOCK_PP_GREATER_2_2 0
#define COMOCK_PP_GREATER_3_0 1
#define COMOCK_PP_GREATER_3_1 1
#define COMOCK_PP_GREATER_3_2 1
#define COMOCK_PP_GREATER_4_0 1
#define COMOCK_PP_GREATER_4_1 1
#define COMOCK_PP_GREATER_4_2 1
#define COMOCK_PP_GREATER_5_0 1
#define COMOCK_PP_GREATER_5_1 1
#define COMOCK_PP_GREATER_5_2 1
#define COMOCK_PP_GREATER_6_0 1
#define COMOCK_PP_GREATER_6_1 1
#define COMOCK_PP_GREATER_6_2 1
#define COMOCK_PP_GREATER_7_0 1
#define COMOCK_PP_GREATER_7_1 1
#define COMOCK_PP_GREATER_7_2 1
#define COMOCK_PP_GREATER_8_0 1
#define COMOCK_PP_GREATER_8_1 1
#define COMOCK_PP_GREATER_8_2 1
#define COMOCK_PP_GREATER_9_0 1
#define COMOCK_PP_GREATER_9_1 1
#define COMOCK_PP_GREATER_9_2 1
#define COMOCK_PP_GREATER_10_0 1
#define COMOCK_PP_GREATER_10_1 1
#define COMOCK_PP_GREATER_10_2 1
#define COMOCK_PP_GREATER_11_0 1
#define COMOCK_PP_GREATER_11_1 1
#define COMOCK_PP_GREATER_11_2 1
#define COMOCK_PP_GREATER_12_0 1
#define COMOCK_PP_GREATER_12_1 1
#define COMOCK_PP_GREATER_12_2 1
#define COMOCK_PP_GREATER_13_0 1
#define COMOCK_PP_GREATER_13_1 1
#define COMOCK_PP_GREATER_13_2 1
#define COMOCK_PP_GREATER_14_0 1
#define COMOCK_PP_GREATER_14_1 1
#define COMOCK_PP_GREATER_14_2 1
#define COMOCK_PP_GREATER_15_0 1
#define COMOCK_PP_GREATER_15_1 1
#define COMOCK_PP_GREATER_15_2 1
#define COMOCK_PP_GREATER_16_0 1
#define COMOCK_PP_GREATER_16_1 1
#define COMOCK_PP_GREATER_16_2 1

// ============================================================================
// Sequence operations
// ============================================================================

// SEQ_SIZE: Count elements in a sequence (a)(b)(c)
// Trick: Each element consumes one macro and chains to the next
#define COMOCK_PP_SEQ_SIZE(seq) COMOCK_PP_CAT(COMOCK_PP_SEQ_SIZE_, COMOCK_PP_SEQ_SIZE_0 seq)

#define COMOCK_PP_SEQ_SIZE_0(_) COMOCK_PP_SEQ_SIZE_1
#define COMOCK_PP_SEQ_SIZE_1(_) COMOCK_PP_SEQ_SIZE_2
#define COMOCK_PP_SEQ_SIZE_2(_) COMOCK_PP_SEQ_SIZE_3
#define COMOCK_PP_SEQ_SIZE_3(_) COMOCK_PP_SEQ_SIZE_4
#define COMOCK_PP_SEQ_SIZE_4(_) COMOCK_PP_SEQ_SIZE_5
#define COMOCK_PP_SEQ_SIZE_5(_) COMOCK_PP_SEQ_SIZE_6
#define COMOCK_PP_SEQ_SIZE_6(_) COMOCK_PP_SEQ_SIZE_7
#define COMOCK_PP_SEQ_SIZE_7(_) COMOCK_PP_SEQ_SIZE_8
#define COMOCK_PP_SEQ_SIZE_8(_) COMOCK_PP_SEQ_SIZE_9
#define COMOCK_PP_SEQ_SIZE_9(_) COMOCK_PP_SEQ_SIZE_10
#define COMOCK_PP_SEQ_SIZE_10(_) COMOCK_PP_SEQ_SIZE_11
#define COMOCK_PP_SEQ_SIZE_11(_) COMOCK_PP_SEQ_SIZE_12
#define COMOCK_PP_SEQ_SIZE_12(_) COMOCK_PP_SEQ_SIZE_13
#define COMOCK_PP_SEQ_SIZE_13(_) COMOCK_PP_SEQ_SIZE_14
#define COMOCK_PP_SEQ_SIZE_14(_) COMOCK_PP_SEQ_SIZE_15
#define COMOCK_PP_SEQ_SIZE_15(_) COMOCK_PP_SEQ_SIZE_16
#define COMOCK_PP_SEQ_SIZE_16(_) COMOCK_PP_SEQ_SIZE_17

#define COMOCK_PP_SEQ_SIZE_COMOCK_PP_SEQ_SIZE_0 0
#define COMOCK_PP_SEQ_SIZE_COMOCK_PP_SEQ_SIZE_1 1
#define COMOCK_PP_SEQ_SIZE_COMOCK_PP_SEQ_SIZE_2 2
#define COMOCK_PP_SEQ_SIZE_COMOCK_PP_SEQ_SIZE_3 3
#define COMOCK_PP_SEQ_SIZE_COMOCK_PP_SEQ_SIZE_4 4
#define COMOCK_PP_SEQ_SIZE_COMOCK_PP_SEQ_SIZE_5 5
#define COMOCK_PP_SEQ_SIZE_COMOCK_PP_SEQ_SIZE_6 6
#define COMOCK_PP_SEQ_SIZE_COMOCK_PP_SEQ_SIZE_7 7
#define COMOCK_PP_SEQ_SIZE_COMOCK_PP_SEQ_SIZE_8 8
#define COMOCK_PP_SEQ_SIZE_COMOCK_PP_SEQ_SIZE_9 9
#define COMOCK_PP_SEQ_SIZE_COMOCK_PP_SEQ_SIZE_10 10
#define COMOCK_PP_SEQ_SIZE_COMOCK_PP_SEQ_SIZE_11 11
#define COMOCK_PP_SEQ_SIZE_COMOCK_PP_SEQ_SIZE_12 12
#define COMOCK_PP_SEQ_SIZE_COMOCK_PP_SEQ_SIZE_13 13
#define COMOCK_PP_SEQ_SIZE_COMOCK_PP_SEQ_SIZE_14 14
#define COMOCK_PP_SEQ_SIZE_COMOCK_PP_SEQ_SIZE_15 15
#define COMOCK_PP_SEQ_SIZE_COMOCK_PP_SEQ_SIZE_16 16
#define COMOCK_PP_SEQ_SIZE_COMOCK_PP_SEQ_SIZE_17 17

// SEQ_ELEM: Extract Nth element from sequence
// Based on boost.preprocessor technique:
// - ELEM_N expands to: element, COMOCK_PP_NIL
// - Wrapper extracts first arg, discards COMOCK_PP_NIL

// Element extraction macros that return (elem, NIL)
#define COMOCK_PP_SEQ_ELEM_0(x) x, COMOCK_PP_NIL
#define COMOCK_PP_SEQ_ELEM_1(_) COMOCK_PP_SEQ_ELEM_0
#define COMOCK_PP_SEQ_ELEM_2(_) COMOCK_PP_SEQ_ELEM_1
#define COMOCK_PP_SEQ_ELEM_3(_) COMOCK_PP_SEQ_ELEM_2
#define COMOCK_PP_SEQ_ELEM_4(_) COMOCK_PP_SEQ_ELEM_3
#define COMOCK_PP_SEQ_ELEM_5(_) COMOCK_PP_SEQ_ELEM_4
#define COMOCK_PP_SEQ_ELEM_6(_) COMOCK_PP_SEQ_ELEM_5
#define COMOCK_PP_SEQ_ELEM_7(_) COMOCK_PP_SEQ_ELEM_6
#define COMOCK_PP_SEQ_ELEM_8(_) COMOCK_PP_SEQ_ELEM_7
#define COMOCK_PP_SEQ_ELEM_9(_) COMOCK_PP_SEQ_ELEM_8
#define COMOCK_PP_SEQ_ELEM_10(_) COMOCK_PP_SEQ_ELEM_9
#define COMOCK_PP_SEQ_ELEM_11(_) COMOCK_PP_SEQ_ELEM_10
#define COMOCK_PP_SEQ_ELEM_12(_) COMOCK_PP_SEQ_ELEM_11
#define COMOCK_PP_SEQ_ELEM_13(_) COMOCK_PP_SEQ_ELEM_12
#define COMOCK_PP_SEQ_ELEM_14(_) COMOCK_PP_SEQ_ELEM_13
#define COMOCK_PP_SEQ_ELEM_15(_) COMOCK_PP_SEQ_ELEM_14

// Wrapper macros to extract element from (elem, NIL) pair
// Uses variadic macros for MSVC compatibility when elem contains commas
#define COMOCK_PP_SEQ_ELEM_EXTRACT_I(elem_with_nil) COMOCK_PP_SEQ_ELEM_EXTRACT_II(elem_with_nil)
#define COMOCK_PP_SEQ_ELEM_EXTRACT_II(...) COMOCK_PP_SEQ_ELEM_EXTRACT_III(__VA_ARGS__)
#define COMOCK_PP_SEQ_ELEM_EXTRACT_III(elem, ...) elem

// SEQ_HEAD: Get first element of sequence (properly extracted)
#define COMOCK_PP_SEQ_HEAD(seq) COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_0 seq)
#define COMOCK_PP_SEQ_TAIL_I(x)
#define COMOCK_PP_SEQ_TAIL(seq) COMOCK_PP_SEQ_TAIL_I seq

// SEQ_FOR_EACH_I: Iterate over sequence with 0-based index
// Calls: macro(~, data, 0, elem0) macro(~, data, 1, elem1) ...
// Manually unrolled for up to 16 elements
#define COMOCK_PP_SEQ_FOR_EACH_I(macro, data, seq) \
    COMOCK_PP_CAT(COMOCK_PP_SEQ_FOR_EACH_I_, COMOCK_PP_SEQ_SIZE(seq))(macro, data, seq)

#define COMOCK_PP_SEQ_FOR_EACH_I_0(macro, data, seq)

#define COMOCK_PP_SEQ_FOR_EACH_I_1(macro, data, seq) \
    macro(~, data, 0, COMOCK_PP_SEQ_HEAD(seq))

#define COMOCK_PP_SEQ_FOR_EACH_I_2(macro, data, seq) \
    macro(~, data, 0, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_0 seq)) \
    macro(~, data, 1, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_1 seq))

#define COMOCK_PP_SEQ_FOR_EACH_I_3(macro, data, seq) \
    macro(~, data, 0, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_0 seq)) \
    macro(~, data, 1, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_1 seq)) \
    macro(~, data, 2, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_2 seq))

#define COMOCK_PP_SEQ_FOR_EACH_I_4(macro, data, seq) \
    macro(~, data, 0, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_0 seq)) \
    macro(~, data, 1, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_1 seq)) \
    macro(~, data, 2, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_2 seq)) \
    macro(~, data, 3, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_3 seq))

#define COMOCK_PP_SEQ_FOR_EACH_I_5(macro, data, seq) \
    macro(~, data, 0, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_0 seq)) \
    macro(~, data, 1, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_1 seq)) \
    macro(~, data, 2, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_2 seq)) \
    macro(~, data, 3, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_3 seq)) \
    macro(~, data, 4, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_4 seq))

#define COMOCK_PP_SEQ_FOR_EACH_I_6(macro, data, seq) \
    macro(~, data, 0, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_0 seq)) \
    macro(~, data, 1, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_1 seq)) \
    macro(~, data, 2, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_2 seq)) \
    macro(~, data, 3, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_3 seq)) \
    macro(~, data, 4, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_4 seq)) \
    macro(~, data, 5, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_5 seq))

#define COMOCK_PP_SEQ_FOR_EACH_I_7(macro, data, seq) \
    macro(~, data, 0, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_0 seq)) \
    macro(~, data, 1, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_1 seq)) \
    macro(~, data, 2, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_2 seq)) \
    macro(~, data, 3, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_3 seq)) \
    macro(~, data, 4, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_4 seq)) \
    macro(~, data, 5, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_5 seq)) \
    macro(~, data, 6, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_6 seq))

#define COMOCK_PP_SEQ_FOR_EACH_I_8(macro, data, seq) \
    macro(~, data, 0, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_0 seq)) \
    macro(~, data, 1, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_1 seq)) \
    macro(~, data, 2, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_2 seq)) \
    macro(~, data, 3, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_3 seq)) \
    macro(~, data, 4, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_4 seq)) \
    macro(~, data, 5, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_5 seq)) \
    macro(~, data, 6, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_6 seq)) \
    macro(~, data, 7, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_7 seq))

#define COMOCK_PP_SEQ_FOR_EACH_I_9(macro, data, seq) \
    macro(~, data, 0, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_0 seq)) \
    macro(~, data, 1, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_1 seq)) \
    macro(~, data, 2, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_2 seq)) \
    macro(~, data, 3, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_3 seq)) \
    macro(~, data, 4, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_4 seq)) \
    macro(~, data, 5, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_5 seq)) \
    macro(~, data, 6, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_6 seq)) \
    macro(~, data, 7, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_7 seq)) \
    macro(~, data, 8, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_8 seq))

#define COMOCK_PP_SEQ_FOR_EACH_I_10(macro, data, seq) \
    macro(~, data, 0, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_0 seq)) \
    macro(~, data, 1, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_1 seq)) \
    macro(~, data, 2, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_2 seq)) \
    macro(~, data, 3, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_3 seq)) \
    macro(~, data, 4, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_4 seq)) \
    macro(~, data, 5, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_5 seq)) \
    macro(~, data, 6, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_6 seq)) \
    macro(~, data, 7, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_7 seq)) \
    macro(~, data, 8, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_8 seq)) \
    macro(~, data, 9, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_9 seq))

#define COMOCK_PP_SEQ_FOR_EACH_I_11(macro, data, seq) \
    macro(~, data, 0, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_0 seq)) \
    macro(~, data, 1, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_1 seq)) \
    macro(~, data, 2, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_2 seq)) \
    macro(~, data, 3, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_3 seq)) \
    macro(~, data, 4, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_4 seq)) \
    macro(~, data, 5, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_5 seq)) \
    macro(~, data, 6, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_6 seq)) \
    macro(~, data, 7, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_7 seq)) \
    macro(~, data, 8, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_8 seq)) \
    macro(~, data, 9, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_9 seq)) \
    macro(~, data, 10, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_10 seq))

#define COMOCK_PP_SEQ_FOR_EACH_I_12(macro, data, seq) \
    macro(~, data, 0, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_0 seq)) \
    macro(~, data, 1, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_1 seq)) \
    macro(~, data, 2, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_2 seq)) \
    macro(~, data, 3, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_3 seq)) \
    macro(~, data, 4, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_4 seq)) \
    macro(~, data, 5, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_5 seq)) \
    macro(~, data, 6, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_6 seq)) \
    macro(~, data, 7, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_7 seq)) \
    macro(~, data, 8, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_8 seq)) \
    macro(~, data, 9, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_9 seq)) \
    macro(~, data, 10, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_10 seq)) \
    macro(~, data, 11, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_11 seq))

#define COMOCK_PP_SEQ_FOR_EACH_I_13(macro, data, seq) \
    macro(~, data, 0, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_0 seq)) \
    macro(~, data, 1, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_1 seq)) \
    macro(~, data, 2, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_2 seq)) \
    macro(~, data, 3, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_3 seq)) \
    macro(~, data, 4, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_4 seq)) \
    macro(~, data, 5, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_5 seq)) \
    macro(~, data, 6, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_6 seq)) \
    macro(~, data, 7, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_7 seq)) \
    macro(~, data, 8, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_8 seq)) \
    macro(~, data, 9, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_9 seq)) \
    macro(~, data, 10, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_10 seq)) \
    macro(~, data, 11, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_11 seq)) \
    macro(~, data, 12, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_12 seq))

#define COMOCK_PP_SEQ_FOR_EACH_I_14(macro, data, seq) \
    macro(~, data, 0, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_0 seq)) \
    macro(~, data, 1, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_1 seq)) \
    macro(~, data, 2, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_2 seq)) \
    macro(~, data, 3, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_3 seq)) \
    macro(~, data, 4, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_4 seq)) \
    macro(~, data, 5, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_5 seq)) \
    macro(~, data, 6, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_6 seq)) \
    macro(~, data, 7, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_7 seq)) \
    macro(~, data, 8, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_8 seq)) \
    macro(~, data, 9, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_9 seq)) \
    macro(~, data, 10, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_10 seq)) \
    macro(~, data, 11, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_11 seq)) \
    macro(~, data, 12, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_12 seq)) \
    macro(~, data, 13, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_13 seq))

#define COMOCK_PP_SEQ_FOR_EACH_I_15(macro, data, seq) \
    macro(~, data, 0, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_0 seq)) \
    macro(~, data, 1, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_1 seq)) \
    macro(~, data, 2, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_2 seq)) \
    macro(~, data, 3, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_3 seq)) \
    macro(~, data, 4, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_4 seq)) \
    macro(~, data, 5, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_5 seq)) \
    macro(~, data, 6, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_6 seq)) \
    macro(~, data, 7, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_7 seq)) \
    macro(~, data, 8, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_8 seq)) \
    macro(~, data, 9, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_9 seq)) \
    macro(~, data, 10, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_10 seq)) \
    macro(~, data, 11, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_11 seq)) \
    macro(~, data, 12, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_12 seq)) \
    macro(~, data, 13, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_13 seq)) \
    macro(~, data, 14, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_14 seq))

#define COMOCK_PP_SEQ_FOR_EACH_I_16(macro, data, seq) \
    macro(~, data, 0, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_0 seq)) \
    macro(~, data, 1, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_1 seq)) \
    macro(~, data, 2, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_2 seq)) \
    macro(~, data, 3, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_3 seq)) \
    macro(~, data, 4, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_4 seq)) \
    macro(~, data, 5, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_5 seq)) \
    macro(~, data, 6, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_6 seq)) \
    macro(~, data, 7, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_7 seq)) \
    macro(~, data, 8, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_8 seq)) \
    macro(~, data, 9, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_9 seq)) \
    macro(~, data, 10, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_10 seq)) \
    macro(~, data, 11, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_11 seq)) \
    macro(~, data, 12, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_12 seq)) \
    macro(~, data, 13, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_13 seq)) \
    macro(~, data, 14, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_14 seq)) \
    macro(~, data, 15, COMOCK_PP_SEQ_ELEM_EXTRACT_I(COMOCK_PP_SEQ_ELEM_15 seq))

// ============================================================================
// Compatibility aliases for boost.preprocessor naming
// ============================================================================

#define BOOST_PP_CAT COMOCK_PP_CAT
#define BOOST_PP_IF COMOCK_PP_IF
#define BOOST_PP_COMMA_IF COMOCK_PP_COMMA_IF
#define BOOST_PP_DEC COMOCK_PP_DEC
#define BOOST_PP_GREATER COMOCK_PP_GREATER
#define BOOST_PP_SEQ_SIZE COMOCK_PP_SEQ_SIZE
#define BOOST_PP_SEQ_FOR_EACH_I COMOCK_PP_SEQ_FOR_EACH_I
