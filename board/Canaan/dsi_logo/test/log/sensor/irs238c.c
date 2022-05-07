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
#include "hw_dev/inc/dev_hw.h"
#include "hw_dev/inc/ext_ctl_hw.h"
#include "sensor/sensor.h"
/*
*
*/
unsigned int irs238c_data[] = 
{
    0x842300A2, 
    0x90001E1E, 
    0x90010000, 
    0x900254C9, 
    0x90030000, 
    0x900454C9, 
    0x90050000, 
    0x900654C9, 
    0x90070000, 
    0x900854C9, 
    0x90090000, 
    0x900A4F96, 
    0x900B0000, 
    0x900C4F96, 
    0x900D0000, 
    0x900E4F96, 
    0x900F0000, 
    0x90104F96, 
    0x90110000, 
    0x90801E1E, 
    0x90810000, 
    0x908210A0, 
    0x908300A0, 
    0x90848000, 
    0x908554C9, 
    0x90860000, 
    0x90870000, 
    0x90880000, 
    0x90890000, 
    0x908A54C9, 
    0x908B0000, 
    0x908C0020, 
    0x908D0000, 
    0x908E0000, 
    0x908F54C9, 
    0x90900000, 
    0x90910040, 
    0x90920000, 
    0x90930000, 
    0x909454C9, 
    0x90950000, 
    0x90960060, 
    0x90970000, 
    0x90980000, 
    0x90994F96, 
    0x909A0000, 
    0x909B1000, 
    0x909C0000, 
    0x909D0000, 
    0x909E4F96, 
    0x909F0000, 
    0x90A01020, 
    0x90A10000, 
    0x90A20000, 
    0x90A34F96, 
    0x90A40000, 
    0x90A51040, 
    0x90A60000, 
    0x90A70000, 
    0x90A84F96, 
    0x90A90000, 
    0x90AA1060, 
    0x90AB0000, 
    0x90ACC000, 
    0x91C00592, 
    0x91C1DF00, 
    0x91C2AB00, 
    0x91C30508, 
    0x91C40008, 
    0x91C50020, 
    0x91C68008, 
    0x91CF0009, 
    0x91D3061A, 
    0x91DB0008, 
    0x91EA1EA1, 
    0x91EBBF26, 
    0x91EC0008, 
    0x91ED0D01, 
    0x91EE5555, 
    0x91EF02F5, 
    0x91F00009, 
    0x91F10031, 
    0x91F216A1, 
    0x91F31EB8, 
    0x91F40005, 
    0x91F50C01, 
    0x91F6FCBF, 
    0x91F704A7, 
    0x91F8000D, 
    0x91F90022, 
    0x92200003, 
    0x9221000C, 
    0x92440003, 
    0x92450008, 
    0x92680001, 
    0x92690001, 
    0x92780B01, 
    0x92790001, 
    0x92880244, 
    0x92890244, 
    0x928A0246, 
    0x928B0244, 
    0x928C0244, 
    0x928D0246, 
    0x928E0244, 
    0x928F0244, 
    0x92900246, 
    0x92910244, 
    0x92920244, 
    0x92930246, 
    0x92940123, 
    0x92950123, 
    0x92960123, 
    0x92970123, 
    0x92980123, 
    0x92990123, 
    0x929A0123, 
    0x929B0123, 
    0x929C0080, 
    0x929D009C, 
    0x929E0095, 
    0x929F0087, 
    0x92A0009C, 
    0x92A10083, 
    0x92A20098, 
    0x92A30080, 
    0x92A40040, 
    0x92A50040, 
    0x92A60040, 
    0x92A70040, 
    0x92A80040, 
    0x92A90040, 
    0x92AA0040, 
    0x92AB0040, 
    0x92AC0040, 
    0x92AD0040, 
    0x92AE0040, 
    0x92AF0040, 
    0x92B00040, 
    0x92B10040, 
    0x92B20040, 
    0x92B30040, 
    0x92B40040, 
    0x92B50040, 
    0x92B60040, 
    0x92B70040, 
    0x92B80040, 
    0x92B90040, 
    0x92BA0040, 
    0x92BB0040, 
    0x92BC0040, 
    0x92BD0040, 
    0x92BE0040, 
    0x92BF0040, 
    0x92C00040, 
    0x92C10040, 
    0x92C20040, 
    0x92C30040, 
    0x92C45633, 
    0x92C59175, 
    0x92C6C5AB, 
    0x92C7F5DD, 
    0x92C84633, 
    0x92C96857, 
    0x92CA8677, 
    0x92CB0095, 
    0x92CC2B1F, 
    0x92CD3F35, 
    0x92CE5249, 
    0x92CF005B, 
    0x92D01211, 
    0x92D11413, 
    0x92D21615, 
    0x92D30017, 
    0x92D4322A, 
    0x92D55343, 
    0x92D66B5B, 
    0x92D70073, 
    0x92D84D35, 
    0x92D97B64, 
    0x92DAA791, 
    0x92DB00BD, 
    0x92DC100B, 
    0x92DD1915, 
    0x92DE221E, 
    0x92DF2C27, 
    0x92E03530, 
    0x92E1003A, 
    0x92E20500, 
    0x92E308D8, 
    0x92E40872, 
    0x92E5084A, 
    0x92E60835, 
    0x92E70001, 
    0x92E80068, 
    0x92E90300, 
    0x92EA0000, 
    0x92EB0000, 
    0x92EC0000, 
    0x92ED0000, 
    0x92EE0000, 
    0x92EF0000, 
    0x92F0002E, 
    0x92F183E2, 
    0x94010002, 
    0xA0010007, 
    0xA0081513, 
    0xA00C0135, 
    0xA0391AA1, 
    0xA03AAAAB, 
    0xA03B000A, 
    0xA03C0000, 
    0xA03D03C0, 
    0xA03E0000, 
    0xA03F0017, 
    0x94000001,
};
/*
*
*/
void irs238c_init(void)
{
    int i,addr,data;
    for(i=0;i<sizeof(irs238c_data)/4;i++)
    {
        addr = irs238c_data[i] >> 16;
        data = irs238c_data[i] & 0xffFF;
        I2cWr(addr,data);
       
        msleep(5);
    }  

    I2cRd(0xA039);
    I2cRd(0xA03A);
    I2cRd(0xA03B);
    I2cRd(0xA03C);
    I2cRd(0xA03D);
    I2cRd(0xA03E);
    I2cRd(0xA03F);
    I2cRd(0x9400);    
}

void irs238c_tof_sensor_config(void)
{
    Active_irs238c_rstn();
    sleep(5);
    Release_irs238c_rstn();
    sleep(1);
    Set_manu(0x01);
    Set_manu(0x00);
    irs238c_init();
    return;
}

