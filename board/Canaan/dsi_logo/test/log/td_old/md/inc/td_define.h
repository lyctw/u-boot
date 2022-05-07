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
** \file       td_define.h
**
** \brief      td define
**
**           (C) Shanghai MicroSharp Co.,Ltd 2013 - 2019
**
** \attention  THIS SAMPLE CODE IS PROVIDED AS IS SAHNGHAI MICROSHARP
**               ACCEPTS NO RESPONSIBILITY OR LIABILITY   
**               FOR ANY ERRORS OR OMMISSIONS.
**
**\version   td_define.h  ,v 1.0 2019/12/16  Kite.Su Exp $
**
**************************************************************************
*/


#ifndef TD_DEFINE_H_
#define TD_DEFINE_H_

//#include <VIDEO_SUBSYSTEM.h>
#include <video_subsystem_addr.h>


#define   TD_CONFIG_WRAP_START         TD_BASE_ADDR + 0x0000
#define   TD_HSCALE_START              TD_BASE_ADDR + (0x8800)
#define   TD_HSCALE_END                TD_BASE_ADDR + (0x8BFF)
#define   TD_VSCALE_START              TD_BASE_ADDR + (0x9400)
#define   TD_VSCALE_END                TD_BASE_ADDR + (0x95FF)
#define   TD_GAMMA_START               TD_BASE_ADDR + (0x3000 <<2)
#define   TD_GAMMA_END                 TD_BASE_ADDR + (0x3CFF <<2)


#endif /* VO_DEFINE_H_ */
