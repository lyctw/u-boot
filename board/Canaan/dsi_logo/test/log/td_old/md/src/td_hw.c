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
/*!
**************************************************************************
** \file       td_hw.c
**
** \brief      vo VoRegWr VoRegRd for WRAP ADDRESS
**
**           (C) Shanghai MicroSharp Co.,Ltd 2013 - 2019
**
** \attention  THIS SAMPLE CODE IS PROVIDED AS IS SAHNGHAI MICROSHARP
**               ACCEPTS NO RESPONSIBILITY OR LIABILITY   
**               FOR ANY ERRORS OR OMMISSIONS.
**
**\version   td_hw.c  ,v 1.0 2019/12/16  Kite.Su Exp $
**
**************************************************************************
*/


//#include <io_ms.h>
#include <td_define.h>
void TdRegWr(int addr, int data)
{
    int offset_addr =0;
    offset_addr = TD_CONFIG_WRAP_START  + (addr <<2);
    RegWr32(offset_addr,data) ;
}
int TdRegRd(int addr)
{
    int offset_addr =0;
    offset_addr = TD_CONFIG_WRAP_START +(addr <<2);
    return(RegRd32(offset_addr));
}




int TdVscalerRegRd(int addr)
{
    int offset_addr =0;
    offset_addr = TD_VSCALE_START +(addr <<2);
    return(RegRd32(offset_addr));
}

int TdHscalerRegRd(int addr)
{
    int offset_addr =0;
    offset_addr = TD_HSCALE_START +(addr <<2);
    return(RegRd32(offset_addr));
}





