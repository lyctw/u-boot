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

#include "vo/vo_calc.h"

void vo_core_calc_scale(VO_LAYER0_SIZE_INFO_S *layer0sizeInfo,VO_LAYER0_SCALE_INFO_S *scaleInfo)
{
    unsigned int InputWidth = layer0sizeInfo->in_hsize;
    unsigned int InputHeight = layer0sizeInfo->in_vsize;
    unsigned int OutputWidth = layer0sizeInfo->out_hsize;
    unsigned int OutputHeight = layer0sizeInfo->out_vsize;

    scaleInfo->h_dstep = ((InputWidth % OutputWidth) * 65536 / OutputWidth);
    scaleInfo->h_pstep = (InputWidth/OutputWidth);
    scaleInfo->h_pstep_st = 0;
    scaleInfo->v_dstep = ((InputHeight % OutputHeight) * 65536 / OutputHeight);
    scaleInfo->v_pstep = (InputHeight/OutputHeight);
    scaleInfo->v_pstep_st = 0;
    return;
}
