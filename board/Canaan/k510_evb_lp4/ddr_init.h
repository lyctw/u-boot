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
#ifndef _DDR_INIT_H
#define _DDR_INIT_H
#include <common.h>
#include <linux/io.h>


#define reg_write(reg, val) writel(val, reg)
#define reg_read(reg, var)  do{var = readl(reg);}while(0);

#define bit_bits_mask(bitwidth, offset)         (((0x1 << (bitwidth)) - 0x1) << (offset))
#define bit_set_bit(var, offset)                (var |= (0x1 << (offset)))
#define bit_clr_bit(var, offset)                (var &= (~(0x1 << (offset))))
#define bit_set_bits(var, bitwidth, offset)     (var |= bit_bits_mask(bitwidth, offset))
#define bit_clr_bits(var, bitwidth, offset)     (var &= ~bit_bits_mask(bitwidth, offset))
#define bit_check_bit(var, offset)              (((var) >> (offset)) & 0x1)
#define bit_set_field(var, bitwidth, offset, val) \
             (var = ((var & (~bit_bits_mask((bitwidth), (offset)))) | ((val) << (offset))))
#define bit_get_field(var, bitwidth, offset)    ((var >> (offset)) & bit_bits_mask(bitwidth, 0))

int ddr_init(void);
#endif
