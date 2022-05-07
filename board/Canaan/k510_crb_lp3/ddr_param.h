/* Copyright (c) 2022, Canaan Bright Sight Co., Ltd
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 * CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef _DDR_PARAM_H
#define _DDR_PARAM_H
/* Normal fib evb
 * 800 & 1066 & 1333 & 1600 set params as below
 * #define DDR_ODT_ENABLE                  1
 * #define DDR_CA_TRAINING                 1
 * #define DDR_WL_TRAINING                 1
 * #define DDR_RG_TRAINING                 1
 * #define DDR_RE_TRAINING                 1
 * #define DDR_WE_TRAINING                 1
 *
 * 1866 not stable
 * ****
 * 2133 don't run write eye and read eye training, use the default value of DLL2/3/4/5
 * #define DDR_ODT_ENABLE                  1
 * #define DDR_CA_TRAINING                 1
 * #define DDR_WL_TRAINING                 1
 * #define DDR_RG_TRAINING                 1
 * #define DDR_RE_TRAINING                 0
 * #define DDR_WE_TRAINING                 0
 * #define DDR_RG_BACKOFF                         2
 * #define DDR_READ_GATE_DELAY_DEASSERTION        0
 *
 * Interposer fib evb
 * 800 & 1066 & 1333 set params as below
 * #define DDR_ODT_ENABLE                  1
 * #define DDR_CA_TRAINING                 1
 * #define DDR_WL_TRAINING                 1
 * #define DDR_RG_TRAINING                 1
 * #define DDR_RE_TRAINING                 1
 * #define DDR_WE_TRAINING                 1
 *
 * 1600 don't run write eye and read eye training, use the default value of DLL2/3/4/5
 * #define DDR_ODT_ENABLE                  1
 * #define DDR_CA_TRAINING                 1
 * #define DDR_WL_TRAINING                 1
 * #define DDR_RG_TRAINING                 1
 * #define DDR_RE_TRAINING                 0
 * #define DDR_WE_TRAINING                 0
 *
 * 1866 & 2133 not stable
 *
*/

/* Board type */
#define DDR_LPDDR3                      1
#define DDR_LPDDR4                      0

/* DDR rate */
#define DDR_800                         0
#define DDR_1066                        0
#define DDR_1333                        0
#define DDR_1600                        1
#define DDR_1866                        0
#define DDR_2133                        0

/* ODT enalbe */
#define DDR_ODT_ENABLE                  1

/* Training enable */
#define DDR_CA_TRAINING                 1
#define DDR_WL_TRAINING                 1
#define DDR_RG_TRAINING                 1
#define DDR_RE_TRAINING                 1
#define DDR_WE_TRAINING                 1

/*
 * Choose old training flow or new flow
 * 0: Use new training flow
 * 1: Use old training flow
*/
#define DDR_WL_TRAINING_OLD             1
#define DDR_RG_TRAINING_OLD             0
// #define DDR_RE_TRAINING_OLD             0
#define DDR_RE_TRAINING_READ_PATTERN    1
// #define DDR_WE_TRAINING_OLD             0
#define DDR_WE_TRAINING_WRITE_PATTERN   1


/* Read eye training */
#define DDR_READ_EYE_LOOP_ALL           1

/* Read Gate Training backoff value */
#if DDR_800
#define DDR_RG_BACKOFF                         4
#define DDR_READ_GATE_DELAY_DEASSERTION        1 /* <=3 */
#endif

#if DDR_1066
#define DDR_RG_BACKOFF                         3
#define DDR_READ_GATE_DELAY_DEASSERTION        1 /* <=3 */
#endif

#if DDR_1333
#define DDR_RG_BACKOFF                         4
#define DDR_READ_GATE_DELAY_DEASSERTION        1 /* <=3 */
#endif

#if DDR_1600
#define DDR_RG_BACKOFF                         4
#define DDR_READ_GATE_DELAY_DEASSERTION        0 /* <=3 */
#endif

#if DDR_1866
#define DDR_RG_BACKOFF                         4
#define DDR_READ_GATE_DELAY_DEASSERTION        0 /* <=3 */
#endif

#if DDR_2133
#define DDR_RG_BACKOFF                         2
#define DDR_READ_GATE_DELAY_DEASSERTION        0 /* <=3 */
#endif

/* DDR test parttern */

/* DDR random test and cache enable, will get a strange result*/
#define DDR_RANDOM_CACHE_TEST                   0

/* DDR stress test */
#define DDR_STRESS_TEST                         1

/* DDR read gate auto training enable */
#define DDR_READ_GATE_AUTO_TRAINING             0

/********************************* Don't modify below *******************************/
/* Set new flow macro */
#if DDR_RG_TRAINING_OLD
#define DDR_RG_TRAINING_NEW             0
#else
#define DDR_RG_TRAINING_NEW             1
#endif

/* Set new flow macro */
#if DDR_WL_TRAINING_OLD
#define DDR_WL_TRAINING_NEW             0
#else
#define DDR_WL_TRAINING_NEW             1
#endif

/* Set new flow macro */
// #if DDR_RE_TRAINING_OLD
// #define DDR_RE_TRAINING_NEW             0
// #else
// #define DDR_RE_TRAINING_NEW             1
// #endif

/* Set new flow macro */
// #if DDR_WE_TRAINING_OLD
// #define DDR_WE_TRAINING_NEW             0
// #else
// #define DDR_WE_TRAINING_NEW             1
// #endif

/* Judge macro conflict */
#if DDR_LPDDR3 + DDR_LPDDR4 != 1
#error DDR type only choose one
#endif

#if DDR_800 + DDR_1066 + DDR_1333 + DDR_1600 + DDR_1866 + DDR_2133 != 1
#error DDR freq only choose one
#endif

#if DDR_RG_TRAINING
    #if DDR_RG_TRAINING_OLD + DDR_RG_TRAINING_NEW != 1
    #error DDR Read Gate Training only choose one
    #endif
#endif

#if DDR_WL_TRAINING
    #if DDR_WL_TRAINING_OLD + DDR_WL_TRAINING_NEW != 1
    #error DDR Write Leveling Training only choose one
    #endif
#endif

#endif //