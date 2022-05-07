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
** \file       td_table_config.c
**
** \brief      td register table config
**
**           (C) Shanghai MicroSharp Co.,Ltd 2013 - 2019
**
** \attention  THIS SAMPLE CODE IS PROVIDED AS IS SAHNGHAI MICROSHARP
**               ACCEPTS NO RESPONSIBILITY OR LIABILITY   
**               FOR ANY ERRORS OR OMMISSIONS.
**
**\version   td_table_config.c  ,v 1.0 2019/12/16  Kite.Su Exp $
**
**************************************************************************
*/

//#include <io_ms.h>
#include <td_define.h>
#include <td_table_config.h>

void  TDMixerConfigVCoef(int a[],int num)
{
    int base_addr= TD_VSCALE_START;
    for (int i =0;i<num; i++)
    {
        RegWr32((base_addr + ((i*2)<<2)),a[i*2]);
        RegWr32((base_addr + ((i*2+1)<<2)),a[i*2+1]);

    }
    printf("TD Mixer VCoef Config done!\n");
}
void  TDMixerConfigHCoef(int a[],int num)
{
    int base_addr= TD_HSCALE_START;
    for (int i =0;i<num; i++)
    {
        RegWr32((base_addr + ((i*4)<<2)),a[i*3]);
        RegWr32((base_addr + ((i*4+1)<<2)),a[i*3+1]);
        RegWr32((base_addr + ((i*4+2)<<2)),a[i*3+2]);

    }
    printf("TD Mixer HCoef Config done!\n");
}

