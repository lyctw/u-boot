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
** \file       td_test.c
**
** \brief      for test TD module and will be continuous updating
**
**           (C) Shanghai MicroSharp Co.,Ltd 2013 - 2019
**
** \attention  THIS SAMPLE CODE IS PROVIDED AS IS SAHNGHAI MICROSHARP
**               ACCEPTS NO RESPONSIBILITY OR LIABILITY   
**               FOR ANY ERRORS OR OMMISSIONS.
**
**\version    td_test.c ,v 1.1 2020/01/16  Kite.Su Exp $
**
**************************************************************************
*/
#if 0
#include <td/md/inc/td_table_config.h>
#include <td/md/inc/td_define.h>
#include <td/md/inc/td_hw.h>
#include <td/td_test.h>
#include <vo/vo_types.h>
#include <td/md/inc/md_td.h>
#include <td/mh/inc/mh_td.h>
#endif
#include <core_v5.h>


#include <td_table_config.h>
#include <td_define.h>
#include <td_hw.h>
#include <td_test.h>
#include <td_types.h>
#include <md_td.h>
#include <mh_td.h>


#include <sleep.h>
//#include <isp_2k_core_wrap_define.h>
//#include <vo/md/inc/vo_md.h>
//#include <isp/inc/isp.h>
#include <cache.h>

#include <isp_com.h>

#define VIDEO_DISP_ZONE_X_START   0xC6
#define VIDEO_DISP_ZONE_X_STOP    0x846
#define VIDEO_DISP_ZONE_Y_START   0x2A
#define VIDEO_DISP_ZONE_Y_STOP    0x462
//layer0                          
#define VIDEO_LAYER0_H_POSITION   198
#define VIDEO_LAYER0_V_POSITION   42
#define VIDEO_LAYER0_H_IN_SIZE    1920
#define VIDEO_LAYER0_V_IN_SIZE    1080	
#define VIDEO_LAYER0_H_OUT_SIZE   1920
#define VIDEO_LAYER0_V_OUT_SIZE   1080
#define VIDEO_LAYER0_RD_STRIDE    2048
                                  
                                  
#define OSD_LAYER0_H_POSITION     (298)
#define OSD_LAYER0_V_POSITION     400
#define OSD_LAYER0_H_SIZE         256
#define OSD_LAYER0_V_SIZE         200
#define OSD_LAYER0_RD_STRIDE      2048

#define OSD0_VLU_ADDR0                0x25000000 
#define OSD0_ALP_ADDR0                0x25080000

          
#define OSD0_LOAD_VLU_ADDR0           0x22000000 
#define OSD0_LOAD_ALP_ADDR0           0x23000000 



#define DUMP_Y_320352_ADDR0           0x02000000 
#define DUMP_UV_320352_ADDR0          0x0201B800
#define TD_ROTATION_Y_320352_ADDR     0x01000000 
#define TD_ROTATION_U_320352_ADDR     0x0101B800 


#define MAIN_Y_ADDR0                  0x20000000 
#define MAIN_UV_ADDR0                 0x20280000 

#define MAIN_ROTATION_Y_ADDR          0x02000000
#define MAIN_ROTATION_U_ADDR          0x27280000 

#define MAIN_ROTATION_Y_ADDR_A        0x28000000 
#define MAIN_ROTATION_U_ADDR_A        0x28280000 

#define DUMP_Y_ADDR0                  0x26000000 
#define DUMP_UV_ADDR0                 0x26012c00

#define TD_ROTATION_Y_ADDR            0x27000000 
#define TD_ROTATION_U_ADDR            0x27280000 




#define TD_DUMP_Y_ADDR444         0X23000000  
#define TD_DUMP_U_ADDR444         0X23400000  
#define TD_DUMP_V_ADDR444         0X23800000  


#define TD_ROTATION_Y_ADDR444         0X27000000  
#define TD_ROTATION_U_ADDR444         0X27400000  
#define TD_ROTATION_V_ADDR444         0X27800000  




#define DUMP_Y_320240_ADDR0           0x26000000 //  # y base: 0x800000
#define DUMP_UV_320240_ADDR0          0x26012C00 // # uv base: 0x900000


#define TD_MIXER_WB_ADDR_Y0           0x27000000
#define TD_MIXER_WB_ADDR_Y1           0x27000000
#define TD_MIXER_WB_ADDR_UV0          0x27012C00
#define TD_MIXER_WB_ADDR_UV1          0x27012C00
                                    
    

MS_SYS_HandleT m_TdRotationOutHandle;
MS_SYS_HandleT m_TdMixerOutHandle;

MS_U32 PrintcCnt = 0; 


void TD_PrintRotRegValue(void)
{

    MS_U32 Iloop = 0; 
    MS_U32 RegValue = 0; 
    PrintcCnt ++;

    while(1)
    {
        RegValue = TdRegRd(Iloop);
        printf("reg index = 0x%x, value = 0x%x !\n",Iloop,RegValue);
        Iloop++;
        if(Iloop >= 133)
        {
            break;
        }
    }
    printf(".........................TD_PrintRotRegValue.PrintcCnt = %d.......................................\n\n\n\n\n\n\n\n",PrintcCnt);

}
void TD_MixerPrintRegValue(void)
{

    MS_U32 Iloop = 0; 
    MS_U32 RegValue = 0; 
    Iloop = 512;
    while(1)
    {
        RegValue = TdRegRd(Iloop);
        printf("reg index = 0x%x, value = 0x%x !\n",Iloop*4,RegValue);
        Iloop++;
        if(Iloop >= 812)
        {
            break;
        }
    }
    printf("...........................TD_MixerPrintRegValue......................................\n");

}

//default rotation parameter
TD_RotationTestParam m_TdRotParam = 
{
    TD_ROTATION_90_DEGREE,      //rot command
    TD_ROTATION_PIX_FORMAT_420SP,   //pixel format
    1920,   //width
    1080,   //height
    1920,  //in stride
    1080,  //out stride
    DUMP_ROTATION_ADDR_SRCY,  //src y
    DUMP_ROTATION_ADDR_SRCUV,  //src uv
    0,      //src v
    DUMP_ROTATION_ADDR_DSTY,  //dst y
    DUMP_ROTATION_ADDR_DSTUV, //dst uv
    0, //dst v
    0,  //in swap
    0,  //in endian swap
    0, //output swap
    0 //endian swap   
};

TD_ScalerTestParam m_TdSclParam = 
{
    1920,
    1080,
    1920,
    1080,
    1920,
    TD_VIDEO_LAYER_YUV_MODE_420, //vo mode
    TD_VIDEO_LAYER_Y_ENDIAN_MODE1,
    TD_VIDEO_LAYER_UV_ENDIAN_MODE3,
    1, //yuv
    1, //420
    1, //420
    0, //YUYV
    DUMP_ROTATION_ADDR_DSTY,
    DUMP_ROTATION_ADDR_DSTUV,
    1920,
    
};

TD_MixerTestParam m_TdMixerParam = 
{
    1920,
    1080,
    1920,
    1080,
    1920,
    0, //start x
    0, //start y
    TD_VIDEO_LAYER_YUV_MODE_420, //vo mode
    TD_VIDEO_LAYER_Y_ENDIAN_MODE1,
    TD_VIDEO_LAYER_UV_ENDIAN_MODE3,
    255, //video global alpha
    DUMP_MIXER_ADDR_VIDEO_Y,
    DUMP_MIXER_ADDR_VIDEO_UV,
    320, //osd w
    240,
    320, //osd stride
    320, //alpha stride
    0, //start x
    0, //start y
    TD_RGB_32BIT, //osd type
    TD_FIXED_VALUE, //alpha type
    TD_ORIGINAL_ORDER, //dma type
    0, //rev rgb
    255, //osd global alpha
    DUMP_MIXER_ADDR_OSD,
    DUMP_MIXER_ADDR_ALPHA,
    1920, //wb w
    1080, //wb h
    1920, //wb stride    
    1, //yuv
    1, //420
    1, //420
    0, //YUYV
    DUMP_MIXER_DST_ADDR_Y,
    DUMP_MIXER_DST_ADDR_UV,
    0,
};

MS_U32 gTDIntRotCnt = 0;
MS_U64 gCycleStart = 0;
MS_U64 gCyclEnd = 0;


void TD_TestRotation90DegreeRef(void)
{
    MS_U32 Iloop = 0;
    //MS_U32  RegValue = 0;

    TdRegWr(0x0,0x000003FF );    
    TdRegWr(0x3,0xFFFFFFFF );  
    TdRegWr(0x8,0);    
    TdRegWr(0x9,0x01010101 );  

    TdRegWr(0x9,0x01010101 );  
    TdRegWr(0xa,0x01010101 );  
    TdRegWr(0xb,0x01010101 );  
    TdRegWr(0xc,0x01010101 );  
    TdRegWr(0xd,0x01234567 );  
    TdRegWr(0xe,0x01234567 );  

    TdRegWr(0xf,0x76543210 );  
    TdRegWr(0x10,0x76543210 );  

    TdRegWr(0x1e,0x1 );  
 
    TdRegWr(0x21,0x01010210 ); //90 420sp
    //TdRegWr(0x21,0x1010000 );    //90 mono
    
    //TdRegWr(0x21,0x1010001 );    //270 mono


    TdRegWr(0x22,0xffff ); 
    TdRegWr(0x23,0x00ff00ff ); //height-1  width-1 
    
    TdRegWr(0x24,0x2300FF00 ); //srcY 256
    TdRegWr(0x25,0x23017F00 ); //srcUV256
    
    //TdRegWr(0x24,0x230000e0 ); //270 420sp
     //TdRegWr(0x25,0x231000e0 ); //270 420sp
    
    TdRegWr(0x26,0 ); 
    TdRegWr(0x27,0x24000000 ); 
    TdRegWr(0x28,0x24010000 ); 
    TdRegWr(0x29,0 ); 

    TdRegWr(0x2a,0x1000100 ); //stride
    TdRegWr(0x2b,0x1000100 ); 
    TdRegWr(0x2c,0x1000100 ); 
   
   // memset(0x23000000,0x22,0x30000);//src y
   // memset(0x23030000,0x77,0x10000);//src UV
    
   // memset(0x23000000,0xdd,0x10000);
   // memset(0x23010000,0xee,0x8000);
      //memset(0x24000000,0xaa,0x20000);//des y
    //memset(0x24010000,0xaa,0x80000);//des uv

    TD_PrintRotRegValue();

    //FRAME START
    //msleep(1000);
    TdRegWr(0x20,0x1 ); 
    //msleep(100);
    TdRegWr(0x20, 0x0 ); 
   
    while(1)
    {
        msleep(100);
        if(MH_TD_get_WrapInt_RotationDone() == 1)
        {
            MH_TD_set_WrapInt_RotationDone(1);
            break;
        }
          
    }

    TD_PrintRotRegValue();
    Iloop = 0;
    while(1)
    {
        Iloop ++; 
        //FRAME START
        TdRegWr(0x20,0x1 ); 
        TdRegWr(0x20,0x0 ); 
        while(1)
        {
          
            if(MH_TD_get_WrapInt_RotationDone() == 1)
            {
                MH_TD_set_WrapInt_RotationDone(1);
                break;
            }
        }
        msleep(6000);
        printf("TD rotation Iloop = %d!\n",Iloop);
    }

    printf("Display Config done!\n");
}


void TD_TestRotation90Degree320352YuvMONO(MS_U8 InSwapEn,MS_U8 BigLittleInEndia,MS_U8 OutSwapEn,MS_U8 BigLittleOutEndia)
{
    MD_TD_RotationParmT OpenParam;
    MS_U32 ErrCode = MS_OK;
    //MS_U8 Iloop = 0;
    
    MS_API_TD_WrapInit();

    memset(&OpenParam,0,sizeof(MD_TD_RotationParmT));

 
    OpenParam.RotationMode         = TD_ROTATION_90_DEGREE;
    OpenParam.RotationPixelFormat  = TD_ROTATION_PIX_FORMAT_MONO;

    OpenParam.InSwapEn             = InSwapEn;
    OpenParam.BigLittleInEndia     = BigLittleInEndia;
    OpenParam.OutSwapEn            = OutSwapEn;
    OpenParam.BigLittleOutEndia    = BigLittleOutEndia;
    OpenParam.OtMaxRD              = 1;
    OpenParam.OtMaxWR              = 1;

    OpenParam.DoneTimeOut          = 0xffff;
    
    OpenParam.ActiveHor          = 320;
    OpenParam.ActiveVer          = 352; 
 
    OpenParam.StrideSrcY          = 320; 
    OpenParam.StrideDesY          = 352;
    
    OpenParam.StrideSrcU          = 0; 
    OpenParam.StrideDesU          = 0;

    OpenParam.StrideSrcV          = 0; 
    OpenParam.StrideDesV          = 0;

    OpenParam.BaseAddrSrcY = DUMP_Y_320352_ADDR0 + (OpenParam.ActiveVer -1)*OpenParam.StrideSrcY;
    OpenParam.BaseAddrSrcU = 0;
    OpenParam.BaseAddrSrcV = 0;

    OpenParam.BaseAddrDesY = TD_ROTATION_Y_320352_ADDR;
    OpenParam.BaseAddrDesU = 0;
    OpenParam.BaseAddrDesV = 0;

    m_TdRotationOutHandle = MS_API_TD_RotationOpen(&OpenParam,&ErrCode);
   
    MS_API_TD_RotationFrameStart();
    TD_PrintRotRegValue();
    while(1)
    {
        msleep(100);
        if(MH_TD_get_WrapInt_RotationDone() == 1)
        {
            MH_TD_set_WrapInt_RotationDone(1);
            break;
        }
          
    }
    TD_PrintRotRegValue();

    printf("TD_TestRotation90Degree320352YuvMONO ErrCode = %d!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\n\n",ErrCode);

}



void TD_TestRotation90Degree320352Yuv420(void)
{

    MD_TD_RotationParmT OpenParam;
    MS_U32 ErrCode = MS_OK;
    //MS_U8 Iloop = 0;
    printf("TD_TestRotation90Degree320352Yuv420 start\n");
    MS_API_TD_WrapInit();

    memset(&OpenParam,0,sizeof(MD_TD_RotationParmT));

    OpenParam.RotationMode         = TD_ROTATION_90_DEGREE;
    OpenParam.RotationPixelFormat  = TD_ROTATION_PIX_FORMAT_420SP;

    OpenParam.InSwapEn             = 1;
    OpenParam.BigLittleInEndia     = 1;
    OpenParam.OutSwapEn            = 1;
    OpenParam.BigLittleOutEndia    = 1;
    OpenParam.OtMaxRD              = 1;
    OpenParam.OtMaxWR              = 1;

    OpenParam.DoneTimeOut          = 0xffff;
    
    OpenParam.ActiveHor          = 320;
    OpenParam.ActiveVer          = 352; 
 
    OpenParam.StrideSrcY          = 320; 
    OpenParam.StrideDesY          = 352;
    
    OpenParam.StrideSrcU          = 320; 
    OpenParam.StrideDesU          = 352;

    OpenParam.StrideSrcV          = 0; 
    OpenParam.StrideDesV          = 0;

    OpenParam.BaseAddrSrcY = DUMP_Y_320352_ADDR0 + (OpenParam.ActiveVer -1)*OpenParam.StrideSrcY;
    OpenParam.BaseAddrSrcU = DUMP_UV_320352_ADDR0 + (OpenParam.ActiveVer/2 -1)*OpenParam.StrideSrcU;
    OpenParam.BaseAddrSrcV = 0;

    OpenParam.BaseAddrDesY = 0x01000000;
    OpenParam.BaseAddrDesU = 0x0101b800;
    OpenParam.BaseAddrDesV = 0;

    m_TdRotationOutHandle = MS_API_TD_RotationOpen(&OpenParam,&ErrCode);

    printf("TD_TestRotation90Degree320352Yuv420 111\n");
   
    MS_API_TD_RotationFrameStart();
    printf("TD_TestRotation90Degree320352Yuv420 run\n");
    
    TD_PrintRotRegValue();
    while(1)
    {
        msleep(100);
        if(MH_TD_get_WrapInt_RotationDone() == 1)
        {
            MH_TD_set_WrapInt_RotationDone(1);
            break;
        }
          
    }
    TD_PrintRotRegValue();




    printf("TD_TestRotation90Degree320352Yuv420 ErrCode = %d!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\n\n",ErrCode);

}



void TD_TestRotation90Degree320352Yuv422(void)
{

    MD_TD_RotationParmT OpenParam;
    MS_U32 ErrCode = MS_OK;


    MS_API_TD_WrapInit();

    memset(&OpenParam,0,sizeof(MD_TD_RotationParmT));

    //cfg video layer0
    OpenParam.RotationMode         = TD_ROTATION_90_DEGREE;
    OpenParam.RotationPixelFormat  = TD_ROTATION_PIX_FORMAT_422SP;

    OpenParam.InSwapEn             = 1;
    OpenParam.BigLittleInEndia     = 1;
    OpenParam.OutSwapEn            = 1;
    OpenParam.BigLittleOutEndia    = 1;
    OpenParam.OtMaxRD              = 1;
    OpenParam.OtMaxWR              = 1;

    OpenParam.DoneTimeOut          = 0xffff;
    
    OpenParam.ActiveHor          = 320;
    OpenParam.ActiveVer          = 352; 
 
    OpenParam.StrideSrcY          = 320; 
    OpenParam.StrideDesY          = 352;
 
    OpenParam.StrideSrcU          = 320; 
    OpenParam.StrideDesU          = 352;

    OpenParam.StrideSrcV          = 0; 
    OpenParam.StrideDesV          = 0;

    OpenParam.BaseAddrSrcY = DUMP_Y_320352_ADDR0 + (OpenParam.ActiveVer -1)*OpenParam.StrideSrcY;
    OpenParam.BaseAddrSrcU = DUMP_UV_320352_ADDR0 + (OpenParam.ActiveVer -1)*OpenParam.StrideSrcU;
    OpenParam.BaseAddrSrcV = 0;  

    OpenParam.BaseAddrDesY = 0x27000000;
    OpenParam.BaseAddrDesU = 0x27280000;
    OpenParam.BaseAddrDesV = 0;


    m_TdRotationOutHandle = MS_API_TD_RotationOpen(&OpenParam,&ErrCode);


    MS_API_TD_RotationFrameStart();

    printf(" TD_TestRotation90Degree320352Yuv422 ErrCode = %d!\n",ErrCode);
    msleep(1000);
    
}


void TD_TestRotation90DegreeYuv444(void)
{

    MD_TD_RotationParmT OpenParam;
    MS_U32 ErrCode = MS_OK;
  
    //MS_U8 Iloop = 0;
    
    MS_API_TD_WrapInit();
   
    memset(&OpenParam,0,sizeof(MD_TD_RotationParmT));

    //cfg video layer0
    OpenParam.RotationMode         = TD_ROTATION_90_DEGREE;
    OpenParam.RotationPixelFormat  = TD_ROTATION_PIX_FORMAT_RGB888; //means YUV or RGB separate 

    OpenParam.InSwapEn               =  1;
    OpenParam.BigLittleInEndia       =  1;
    OpenParam.OutSwapEn               = 1;
    OpenParam.BigLittleOutEndia       = 1;

    OpenParam.OtMaxRD              = 1;
    OpenParam.OtMaxWR              = 1;

    OpenParam.DoneTimeOut          = 0xffff;
    
    OpenParam.ActiveHor           = 640;
    OpenParam.ActiveVer           = 480; 
  
    OpenParam.StrideSrcY          = 640; 
    OpenParam.StrideDesY          = 480;
 
    OpenParam.StrideSrcU          = 640; 
    OpenParam.StrideDesU          = 480;

    OpenParam.StrideSrcV          = 640; 
    OpenParam.StrideDesV          = 480;


    OpenParam.BaseAddrSrcY = TD_DUMP_Y_ADDR444 + (OpenParam.ActiveVer -1)*OpenParam.StrideSrcY;
    OpenParam.BaseAddrSrcU = TD_DUMP_U_ADDR444 + (OpenParam.ActiveVer -1)*OpenParam.StrideSrcU;
    OpenParam.BaseAddrSrcV = TD_DUMP_V_ADDR444 + (OpenParam.ActiveVer -1)*OpenParam.StrideSrcV;

    OpenParam.BaseAddrDesY = TD_ROTATION_Y_ADDR444;
    OpenParam.BaseAddrDesU = TD_ROTATION_U_ADDR444;
    OpenParam.BaseAddrDesV = TD_ROTATION_V_ADDR444;
    
    m_TdRotationOutHandle = MS_API_TD_RotationOpen(&OpenParam,&ErrCode);   
    MS_API_TD_RotationFrameStart();
    TD_PrintRotRegValue();
    msleep(1000);
    printf("kite debug >>  TD_TestRotation90DegreeMainYuv444 rotation ErrCode = %d!!!!!!!!!!!!\n\n\n\n\n",ErrCode);
}



void TD_TestRotation90Degree1080pYuv420_Timeout(void)
{

    MD_TD_RotationParmT OpenParam;
    MS_U32 ErrCode = MS_OK;
    //MS_U8 Iloop = 0;
    
    MS_API_TD_WrapInit();

    memset(&OpenParam,0,sizeof(MD_TD_RotationParmT));

    OpenParam.RotationMode         = TD_ROTATION_90_DEGREE;
    OpenParam.RotationPixelFormat  = TD_ROTATION_PIX_FORMAT_420SP;

    OpenParam.InSwapEn             = 1;
    OpenParam.BigLittleInEndia     = 1;
    OpenParam.OutSwapEn            = 1;
    OpenParam.BigLittleOutEndia    = 1;
    OpenParam.OtMaxRD              = 1;
    OpenParam.OtMaxWR              = 1;

    OpenParam.DoneTimeOut          = 1;
    
    OpenParam.ActiveHor          = 1920;
    OpenParam.ActiveVer          = 1080; 
 
    OpenParam.StrideSrcY          = 1920; 
    OpenParam.StrideDesY          = 1080;
    
    OpenParam.StrideSrcU          = 1920; 
    OpenParam.StrideDesU          = 1080;

    OpenParam.StrideSrcV          = 0; 
    OpenParam.StrideDesV          = 0;

    OpenParam.BaseAddrSrcY = DUMP_Y_320352_ADDR0 + (OpenParam.ActiveVer -1)*OpenParam.StrideSrcY;
    OpenParam.BaseAddrSrcU = DUMP_UV_320352_ADDR0 + (OpenParam.ActiveVer/2 -1)*OpenParam.StrideSrcU;
    OpenParam.BaseAddrSrcV = 0;

    OpenParam.BaseAddrDesY = TD_ROTATION_Y_320352_ADDR;
    OpenParam.BaseAddrDesU = TD_ROTATION_U_320352_ADDR;
    OpenParam.BaseAddrDesV = 0;

    m_TdRotationOutHandle = MS_API_TD_RotationOpen(&OpenParam,&ErrCode);
    //enable timeout/rotation int
    
    MS_U32 reg = *(volatile MS_U32 *)(TD_BASE_ADDR + 0x7c);         
    *(volatile MS_U32 *)(TD_BASE_ADDR + 0x7c) = reg&~(7 << 16);

    TD_PrintRotRegValue();
   
    MS_API_TD_RotationFrameStart();
    TD_PrintRotRegValue();
    int cnt = 0;
    while(cnt ++ < 5)
    {
        msleep(5000);
        
        printf("MS_API_TD_RotationFrameStart start timer   = %u!\n",read_cycle());
        MS_API_TD_RotationFrameStart();

          
    }

    msleep(2000);
    printf("TD_TestRotation90Degree1080pYuv420_Timeout ErrCode = %d!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\n\n",ErrCode);

}









void TD_TestRotation270Degree320352Yuv420(void)
{

    MD_TD_RotationParmT OpenParam;
    MS_U32 ErrCode = MS_OK;
    //MS_U8 Iloop = 0;
    
    MS_API_TD_WrapInit();
    memset(&OpenParam,0,sizeof(MD_TD_RotationParmT));

    //cfg video layer0
    OpenParam.RotationMode         = TD_ROTATION_90_DEGREE;
    OpenParam.RotationPixelFormat  = TD_ROTATION_PIX_FORMAT_420SP;

    OpenParam.InSwapEn             = 1;
    OpenParam.BigLittleInEndia     = 1;
    OpenParam.OutSwapEn            = 1;
    OpenParam.BigLittleOutEndia    = 1;
    OpenParam.OtMaxRD              = 1;
    OpenParam.OtMaxWR              = 1;

    OpenParam.DoneTimeOut          = 0xffff;

    OpenParam.ActiveHor          = 320;
    OpenParam.ActiveVer          = 352; 

    OpenParam.StrideSrcY          = 320; 
    OpenParam.StrideDesY          = 384;

    OpenParam.StrideSrcU          = 320; 
    OpenParam.StrideDesU          = 384;

    OpenParam.StrideSrcV          = 0; 
    OpenParam.StrideDesV          = 0;

    OpenParam.BaseAddrSrcY = DUMP_Y_320352_ADDR0 + (OpenParam.ActiveVer -1)*OpenParam.StrideSrcY;
    OpenParam.BaseAddrSrcU = DUMP_UV_320352_ADDR0 + (OpenParam.ActiveVer/2 -1)*OpenParam.StrideSrcU;
    OpenParam.BaseAddrSrcV = 0;  

    OpenParam.BaseAddrDesY = 0x01000000;
    OpenParam.BaseAddrDesU = 0x0101e000;
    OpenParam.BaseAddrDesV = 0;


    m_TdRotationOutHandle = MS_API_TD_RotationOpen(&OpenParam,&ErrCode);


    MS_API_TD_RotationFrameStart();
    msleep(1000);

    memset(&OpenParam,0,sizeof(MD_TD_RotationParmT));

    OpenParam.RotationMode         = TD_ROTATION_270_DEGREE;
    OpenParam.RotationPixelFormat  = TD_ROTATION_PIX_FORMAT_420SP;

    OpenParam.InSwapEn             = 1;
    OpenParam.BigLittleInEndia     = 1;
    OpenParam.OutSwapEn            = 1;
    OpenParam.BigLittleOutEndia    = 1;
    OpenParam.OtMaxRD              = 1;
    OpenParam.OtMaxWR              = 1;

    OpenParam.DoneTimeOut          = 0xffff;
    
    OpenParam.ActiveHor          = 320;
    OpenParam.ActiveVer          = 352; 
 
    OpenParam.StrideSrcY          = 320; 
    OpenParam.StrideDesY          = 384;
    
    OpenParam.StrideSrcU          = 320; 
    OpenParam.StrideDesU          = 384;

    OpenParam.StrideSrcV          = 0; 
    OpenParam.StrideDesV          = 0;

    OpenParam.BaseAddrSrcY = DUMP_Y_320352_ADDR0 + (OpenParam.ActiveHor -32);
    OpenParam.BaseAddrSrcU = DUMP_UV_320352_ADDR0 + (OpenParam.ActiveHor -32);
    OpenParam.BaseAddrSrcV = 0;

    OpenParam.BaseAddrDesY = 0x03000000;
    OpenParam.BaseAddrDesU = 0x0301e000;
    OpenParam.BaseAddrDesV = 0;

    m_TdRotationOutHandle = MS_API_TD_RotationOpen(&OpenParam,&ErrCode);
   
    MS_API_TD_RotationFrameStart();


    msleep(1000);



    printf("TD_TestRotation270Degree320352Yuv420 ErrCode = %d!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\n\n",ErrCode);

}



void TD_TestRotation270Degree320352Yuv422(void)
{

    MD_TD_RotationParmT OpenParam;
    MS_U32 ErrCode = MS_OK;
    //MS_U8 Iloop = 0;
    
    MS_API_TD_WrapInit();

    memset(&OpenParam,0,sizeof(MD_TD_RotationParmT));

    OpenParam.RotationMode         = TD_ROTATION_270_DEGREE;
    OpenParam.RotationPixelFormat  = TD_ROTATION_PIX_FORMAT_422SP;

    OpenParam.InSwapEn             = 1;
    OpenParam.BigLittleInEndia     = 1;
    OpenParam.OutSwapEn            = 1;
    OpenParam.BigLittleOutEndia    = 1;
    OpenParam.OtMaxRD              = 1;
    OpenParam.OtMaxWR              = 1;

    OpenParam.DoneTimeOut          = 0xffff;
    
    OpenParam.ActiveHor          = 320;
    OpenParam.ActiveVer          = 352; 
 
    OpenParam.StrideSrcY          = 320; 
    OpenParam.StrideDesY          = 352;
    
    OpenParam.StrideSrcU          = 320; 
    OpenParam.StrideDesU          = 352;

    OpenParam.StrideSrcV          = 0; 
    OpenParam.StrideDesV          = 0;

    OpenParam.BaseAddrSrcY = DUMP_Y_320352_ADDR0 + (OpenParam.ActiveHor -32);
    OpenParam.BaseAddrSrcU = DUMP_UV_320352_ADDR0 + (OpenParam.ActiveHor -32);
    OpenParam.BaseAddrSrcV = 0;

    OpenParam.BaseAddrDesY = 0x27000000;
    OpenParam.BaseAddrDesU = 0x27280000;
    OpenParam.BaseAddrDesV = 0;

    m_TdRotationOutHandle = MS_API_TD_RotationOpen(&OpenParam,&ErrCode);
   
    MS_API_TD_RotationFrameStart();


    msleep(1000);


    memset(&OpenParam,0,sizeof(MD_TD_RotationParmT));

    //cfg video layer0
    OpenParam.RotationMode         = TD_ROTATION_90_DEGREE;
    OpenParam.RotationPixelFormat  = TD_ROTATION_PIX_FORMAT_422SP;

    OpenParam.InSwapEn             = 1;
    OpenParam.BigLittleInEndia     = 1;
    OpenParam.OutSwapEn            = 1;
    OpenParam.BigLittleOutEndia    = 1;
    OpenParam.OtMaxRD              = 1;
    OpenParam.OtMaxWR              = 1;

    OpenParam.DoneTimeOut          = 0xffff;

    OpenParam.ActiveHor          = 320;
    OpenParam.ActiveVer          = 352; 

    OpenParam.StrideSrcY          = 320; 
    OpenParam.StrideDesY          = 352;

    OpenParam.StrideSrcU          = 320; 
    OpenParam.StrideDesU          = 352;

    OpenParam.StrideSrcV          = 0; 
    OpenParam.StrideDesV          = 0;

    OpenParam.BaseAddrSrcY = DUMP_Y_320352_ADDR0 + (OpenParam.ActiveVer -1)*OpenParam.StrideSrcY;
    OpenParam.BaseAddrSrcU = DUMP_UV_320352_ADDR0 + (OpenParam.ActiveVer -1)*OpenParam.StrideSrcU;
    OpenParam.BaseAddrSrcV = 0;  

    OpenParam.BaseAddrDesY = 0x28000000;
    OpenParam.BaseAddrDesU = 0x28280000;
    OpenParam.BaseAddrDesV = 0;


    m_TdRotationOutHandle = MS_API_TD_RotationOpen(&OpenParam,&ErrCode);


    MS_API_TD_RotationFrameStart();

    printf("TD_TestRotation270Degree320352Yuv420 ErrCode = %d!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\n\n",ErrCode);

}




void TD_TestRotation90DegreeMainYuv420_IRQ(void)
{

    MD_TD_RotationParmT OpenParam;
    MS_U32 ErrCode = MS_OK;
    MS_U32 startCnt = 0;
    MS_U32 reg = 0;
    MS_U32  downscaleW = 0;
    MS_U32  downscaleH = 0;

    MD_TD_MixerParamaterT MOpenParam;


    uint64_t cycle = read_cycle();
    
    printf("1 cycle = %u \n",cycle);
     
    msleep(10000);
    
    cycle = read_cycle();
         
    printf("2 cycle = %u \n",cycle);

    MS_API_TD_WrapInit();

#if 1
    


    memset(&OpenParam,0,sizeof(MD_TD_RotationParmT));

    //cfg video layer0
    OpenParam.RotationMode         = TD_ROTATION_90_DEGREE;
    OpenParam.RotationPixelFormat  = TD_ROTATION_PIX_FORMAT_420SP;

    OpenParam.InSwapEn             = 1;
    OpenParam.BigLittleInEndia     = 1;
    OpenParam.OutSwapEn            = 1;
    OpenParam.BigLittleOutEndia    = 1;
    OpenParam.OtMaxRD              = 15;
    OpenParam.OtMaxWR              = 15;

    OpenParam.DoneTimeOut          = 0xffff;//0x02;
    
    OpenParam.ActiveHor          = 1920;
    OpenParam.ActiveVer          = 1080; 
 
    OpenParam.StrideSrcY          = 1920; 
    OpenParam.StrideSrcU          = 1920; 

    
    OpenParam.StrideDesY          = 1080;
    OpenParam.StrideDesU          = 1080;

    OpenParam.StrideSrcV          = 0; 
    OpenParam.StrideDesV          = 0;
    // memset(0x2304B000,0xcc,0x265000);

    OpenParam.BaseAddrSrcY = 0x23000000 + (OpenParam.ActiveVer -1)*OpenParam.StrideSrcY;
    OpenParam.BaseAddrSrcU = 0x23280000 + (OpenParam.ActiveVer/2 -1)*OpenParam.StrideSrcU;
    OpenParam.BaseAddrSrcV = 0;

    OpenParam.BaseAddrDesY = MAIN_ROTATION_Y_ADDR;
    OpenParam.BaseAddrDesU = MAIN_ROTATION_U_ADDR;
    OpenParam.BaseAddrDesV = 0;

    //TD_PrintRotRegValue();

    m_TdRotationOutHandle = MS_API_TD_RotationOpen(&OpenParam,&ErrCode);
    TD_PrintRotRegValue();
    reg = *(volatile MS_U32 *)(TD_BASE_ADDR + 0x7c);         
    *(volatile MS_U32 *)(TD_BASE_ADDR + 0x7c) = reg&~(7 << 16);
     
    cycle = read_cycle();
    MS_API_TD_RotationFrameStart();
    printf("MS_API_TD_RotationFrameStart start timer   = %u!\n",cycle);


    msleep(10000);
    while(1)
    {
        printf("MS_API_TD_RotationFrameStart start timer   = %u!\n",read_cycle());
        MS_API_TD_RotationFrameStart();
        msleep(5000);
#if 0     
        startCnt++;
       
        if(startCnt%2)
        {
            reg = *(volatile MS_U32 *)0x924A007c;         
            
            *(volatile MS_U32 *)0x924A007c = reg|(1 << 16);
        }
        else
        {
             reg = *(volatile MS_U32 *)0x924A007c;         
            *(volatile MS_U32 *)0x924A007c = reg&~(1 << 16);

        }
        if(startCnt > 20)
        {
           // break;
        }
#endif
    }
#endif
    startCnt = 0;
    MS_API_TD_MixerInit();
 
    memset(&OpenParam,0,sizeof(MD_TD_MixerParamaterT));
      //memset(TD_MIXER_WB_ADDR_Y0,0x00,0x20000);//des y
    downscaleW = 1920;
    downscaleH = 1080;
      //cfg video layer0
      MOpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerEnable          = 1;
    
      MOpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StartX = 198;
      MOpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StartY = 42;
      MOpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StopX  = 198 + downscaleW;//////////////
      MOpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StopY  = 42 + downscaleH;/////////////////////
    
      MOpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInDataMode        = TD_VIDEO_LAYER_YUV_MODE_420;
      MOpenParam.VideoLayerParam[TD_VIDEO_LAYER0].EndianModeY          = TD_VIDEO_LAYER_Y_ENDIAN_MODE1;
      MOpenParam.VideoLayerParam[TD_VIDEO_LAYER0].EndianModeUV         = TD_VIDEO_LAYER_UV_ENDIAN_MODE2;
    
      MOpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelHszie      = 1920;
      MOpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelVszie      = 1080;
      MOpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgOutPixelHszie     = downscaleW;///////////////
      MOpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgOutPixelVszie     = downscaleH;////////////////////
      MOpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelStrideH    = 1920;
      MOpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelStrideV    = 0;
      MOpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelOffsetH    = 0;
      MOpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelOffsetV    = 0;
      MOpenParam.VideoLayerParam[TD_VIDEO_LAYER0].GlobalAlpha          = 0xff;
      MOpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ReadAddress0Y        =  0x23000000;
      MOpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ReadAddress0UV       =  0x231FA400;
      MOpenParam.LayerMixerOrder                                       = MOpenParam.LayerMixerOrder|(0 << 0 );
      MOpenParam.WindowZone.StartX                                     = MOpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StartX;
      MOpenParam.WindowZone.StopX                                      = MOpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StopX ;
      MOpenParam.WindowZone.StartY                                     = MOpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StartY;
      MOpenParam.WindowZone.StopY                                      = MOpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StopY;
    
    
      MOpenParam.BackGroundComp = 0x00ffffff;
      MOpenParam.DisplayYUV2RGBEn = 1;
    
      //DMA OUT
      MOpenParam.DmaWriteBackEn = 1;
      MOpenParam.DmaWbParam.InputMode              = 1; //0：bt656  1:BT1120     
      
      MOpenParam.DmaWbParam.DataFormat             = 1;     //RGB/RAW  1:YUV  
      MOpenParam.DmaWbParam.DmaInputFormat         = 0;     //1`b0:YUV422;1`b1:YUV420    
    
      MOpenParam.DmaWbParam.OutputMode             = 1 ;
      MOpenParam.DmaWbParam.DmaInput422PixelOrder  = 0;
      MOpenParam.DmaWbParam.RawPixelWidth          = 0;
      
      MOpenParam.DmaWbParam.WriteBaseAddressY0     = MAIN_ROTATION_Y_ADDR;
      MOpenParam.DmaWbParam.WriteBaseAddressY1     = MAIN_ROTATION_Y_ADDR;
      MOpenParam.DmaWbParam.WriteBaseAddressUV0    = MAIN_ROTATION_U_ADDR;
      MOpenParam.DmaWbParam.WriteBaseAddressUV1    = MAIN_ROTATION_U_ADDR;
      
      MOpenParam.DmaWbParam.DataLineYStride        = downscaleW;
      MOpenParam.DmaWbParam.DataLineUVStride       = downscaleW;       
      
      MOpenParam.DmaWbParam.ActiveHszie            = downscaleW;
      MOpenParam.DmaWbParam.ActiveVszie            = downscaleH;////////////
    
      MOpenParam.DmaWbParam.DramLoopSzie           = 0xFFFF;
      
      MOpenParam.DmaWbParam.Ch1OtNum               = 1; 
      MOpenParam.DmaWbParam.Ch1BlenMode            = 0; 
      MOpenParam.DmaWbParam.Ch1ContinuousMode      = 1;   
      MOpenParam.DmaWbParam.Ch1DmaYUVMap           = 0;
      MOpenParam.DmaWbParam.Ch1WbErrDetectEn       = 0;         
      MOpenParam.DmaWbParam.Ch1ErrUnit             = 1;
      MOpenParam.DmaWbParam.Ch1ErrTh               = 1;
      
      MOpenParam.DmaWbParam.Ch2OtNum               = 1;
      MOpenParam.DmaWbParam.Ch2BlenMode            = 0;
      MOpenParam.DmaWbParam.Ch2ContinuousMode      = 1;
      MOpenParam.DmaWbParam.Ch2DmaYUVMap           = 0;
      MOpenParam.DmaWbParam.Ch2WbErrDetectEn       = 0;    
      MOpenParam.DmaWbParam.Ch2ErrUnit             = 1;
      MOpenParam.DmaWbParam.Ch2ErrTh               = 1;
      //END
      m_TdMixerOutHandle = MS_API_TD_MixerOpen(&MOpenParam,&ErrCode);

    while(1)
    {
        reg = *(volatile MS_U32 *)(TD_BASE_ADDR + 0x7c);         
        *(volatile MS_U32 *)(TD_BASE_ADDR + 0x7c) = reg&~(1 << 18);
        cycle = read_cycle();
        printf("MS_API_TD_MixerFrameStart start timer   = %u!\n",cycle);
        
        MS_API_TD_MixerFrameStart();
        
        msleep(200000);

        printf("startCnt  = %d!\n",startCnt);
        startCnt ++ ;
        
        if(startCnt%2)
        {
            reg = *(volatile MS_U32 *)(TD_BASE_ADDR + 0x7c);         
            
            *(volatile MS_U32 *)(TD_BASE_ADDR + 0x7c) = reg|(1 << 18);
        }
        else
        {
             reg = *(volatile MS_U32 *)(TD_BASE_ADDR + 0x7c);         
            *(volatile MS_U32 *)(TD_BASE_ADDR + 0x7c) = reg&~(1 << 18);

        }
    }
    printf("TD_TestRotation90DegreeMainYuv420_IRQ ErrCode = %d!\n",ErrCode);

}

void TD_TestRotation270DegreeMainYuv420_Parm(MS_U32 RatationMode,MS_U16 srcW,MS_U16 srcStride,MS_U16 srcH,MS_U16 OtMaxRD,MS_U16 OtMaxWR)
{

    MD_TD_RotationParmT OpenParam;
    MS_U32 ErrCode = MS_OK;
    uint64_t cycle = 0;
    MS_U32 reg;

    MS_API_TD_WrapInit();


    memset(&OpenParam,0,sizeof(MD_TD_RotationParmT));

    //cfg video layer0
    OpenParam.RotationMode         = TD_ROTATION_270_DEGREE;
    OpenParam.RotationPixelFormat  = TD_ROTATION_PIX_FORMAT_420SP;

    OpenParam.InSwapEn             = 1;
    OpenParam.BigLittleInEndia     = 1;
    OpenParam.OutSwapEn            = 1;
    OpenParam.BigLittleOutEndia    = 1;
    OpenParam.OtMaxRD              = OtMaxRD;
    OpenParam.OtMaxWR              = OtMaxWR;

    OpenParam.DoneTimeOut          = 0xffff;
    
    OpenParam.ActiveHor          = srcW;
    OpenParam.ActiveVer          = srcH; 
 
    OpenParam.StrideSrcY          = srcStride; 
    OpenParam.StrideSrcU          = srcStride; 

    
    OpenParam.StrideDesY          = srcH;
    OpenParam.StrideDesU          = srcH;

    OpenParam.StrideSrcV          = 0; 
    OpenParam.StrideDesV          = 0;
    // memset(0x2304B000,0xcc,0x265000);

    OpenParam.BaseAddrSrcY = 0x23000000 + (OpenParam.ActiveHor -32);
    OpenParam.BaseAddrSrcU = 0x23000000 + 1080*1920 + (OpenParam.ActiveHor -32);
    OpenParam.BaseAddrSrcV = 0;


    OpenParam.BaseAddrDesY = MAIN_ROTATION_Y_ADDR;
    OpenParam.BaseAddrDesU = MAIN_ROTATION_U_ADDR;
    OpenParam.BaseAddrDesV = 0;


    m_TdRotationOutHandle = MS_API_TD_RotationOpen(&OpenParam,&ErrCode);
    //TD_PrintRotRegValue();
    reg = *(volatile MS_U32 *)0x924A007c;         
    *(volatile MS_U32 *)0x924A007c = reg&~(1 << 16);
    MS_API_TD_RotationFrameStart();
    cycle = read_cycle();
    printf("!!!!!!!!!!!!!!!TD_TestRotation270DegreeMainYuv420_Parm start timer   = %u!\n",cycle);
    msleep(1000);
}

void TD_TestRotation90DegreeMainYuv420_Parm(MS_U32 RatationMode,MS_U16 srcW,MS_U16 srcStride,MS_U16 srcH,MS_U16 OtMaxRD,MS_U16 OtMaxWR)
{

    MD_TD_RotationParmT OpenParam;
    MS_U32 ErrCode = MS_OK;
    uint64_t cycle = 0;
    MS_U32 reg;

    MS_API_TD_WrapInit();


    memset(&OpenParam,0,sizeof(MD_TD_RotationParmT));

    //cfg video layer0
    OpenParam.RotationMode         = TD_ROTATION_90_DEGREE;
    OpenParam.RotationPixelFormat  = TD_ROTATION_PIX_FORMAT_420SP;

    OpenParam.InSwapEn             = 1;
    OpenParam.BigLittleInEndia     = 1;
    OpenParam.OutSwapEn            = 1;
    OpenParam.BigLittleOutEndia    = 1;
    OpenParam.OtMaxRD              = OtMaxRD;
    OpenParam.OtMaxWR              = OtMaxWR;

    OpenParam.DoneTimeOut          = 0xffff;
    
    OpenParam.ActiveHor          = srcW;
    OpenParam.ActiveVer          = srcH; 
 
    OpenParam.StrideSrcY          = srcStride; 
    OpenParam.StrideSrcU          = srcStride; 

    
    OpenParam.StrideDesY          = srcH;
    OpenParam.StrideDesU          = srcH;

    OpenParam.StrideSrcV          = 0; 
    OpenParam.StrideDesV          = 0;
    // memset(0x2304B000,0xcc,0x265000);

    OpenParam.BaseAddrSrcY = 0x23000000 + (OpenParam.ActiveVer -1)*OpenParam.StrideSrcY;
    OpenParam.BaseAddrSrcU = 0x23000000 + 1080*1920 + (OpenParam.ActiveVer/2 -1)*OpenParam.StrideSrcU;
    OpenParam.BaseAddrSrcV = 0;

    OpenParam.BaseAddrDesY = MAIN_ROTATION_Y_ADDR;
    OpenParam.BaseAddrDesU = MAIN_ROTATION_U_ADDR;
    OpenParam.BaseAddrDesV = 0;


    m_TdRotationOutHandle = MS_API_TD_RotationOpen(&OpenParam,&ErrCode);
    //TD_PrintRotRegValue();
    reg = *(volatile MS_U32 *)0x924A007c;         
    *(volatile MS_U32 *)0x924A007c = reg&~(1 << 16);
    MS_API_TD_RotationFrameStart();
    cycle = read_cycle();
    printf("!!!!!!!!!!!!!!!TD_TestRotation90DegreeMainYuv420_Parm start timer   = %u!\n",cycle);
    msleep(100);
}


void TD_TestRotation90DegreeMainYuv420(void)
{

    MD_TD_RotationParmT OpenParam;
    MS_U32 ErrCode = MS_OK;

    MS_API_TD_WrapInit();


    memset(&OpenParam,0,sizeof(MD_TD_RotationParmT));

    //cfg video layer0
    OpenParam.RotationMode         = TD_ROTATION_90_DEGREE;
    OpenParam.RotationPixelFormat  = TD_ROTATION_PIX_FORMAT_420SP;

    OpenParam.InSwapEn             = 1;
    OpenParam.BigLittleInEndia     = 1;
    OpenParam.OutSwapEn            = 1;
    OpenParam.BigLittleOutEndia    = 1;
    OpenParam.OtMaxRD              = 1;
    OpenParam.OtMaxWR              = 1;

    OpenParam.DoneTimeOut          = 0xffff;
    
    OpenParam.ActiveHor          = 352;
    OpenParam.ActiveVer          = 320; 
 
    OpenParam.StrideSrcY          = 352; 
    OpenParam.StrideSrcU          = 352; 

    
    OpenParam.StrideDesY          = 320;
    OpenParam.StrideDesU          = 320;

    OpenParam.StrideSrcV          = 0; 
    OpenParam.StrideDesV          = 0;
    // memset(0x2304B000,0xcc,0x265000);

    OpenParam.BaseAddrSrcY = 0x23000000 + (OpenParam.ActiveVer -1)*OpenParam.StrideSrcY;
    OpenParam.BaseAddrSrcU = 0x2301B800 + (OpenParam.ActiveVer/2 -1)*OpenParam.StrideSrcU;
    OpenParam.BaseAddrSrcV = 0;

    OpenParam.BaseAddrDesY = MAIN_ROTATION_Y_ADDR;
    OpenParam.BaseAddrDesU = MAIN_ROTATION_U_ADDR;
    OpenParam.BaseAddrDesV = 0;


    m_TdRotationOutHandle = MS_API_TD_RotationOpen(&OpenParam,&ErrCode);
    TD_PrintRotRegValue();
   
    MS_API_TD_RotationFrameStart();
   
    msleep(2000);
    
    printf("TD_TestRotation90DegreeMainYuv420 ErrCode = %d!\n",ErrCode);



#if 0
    OpenParam.ActiveHor          = 288;
    OpenParam.ActiveVer          = 352; 

    OpenParam.StrideSrcY          = 288; 
    OpenParam.StrideDesY          = 352;

    OpenParam.StrideSrcU          = 288; 
    OpenParam.StrideDesU          = 352;

    OpenParam.StrideSrcV          = 0; 
    OpenParam.StrideDesV          = 0;

    OpenParam.BaseAddrSrcY = MAIN_ROTATION_Y_ADDR + (OpenParam.ActiveVer -1)*OpenParam.StrideSrcY;
    OpenParam.BaseAddrSrcU = MAIN_ROTATION_U_ADDR + (OpenParam.ActiveVer/2 -1)*OpenParam.StrideSrcU;
    // OpenParam.BaseAddrSrcY = DUMP_Y_320352_ADDR0 + (OpenParam.ActiveVer )*OpenParam.StrideSrcY;
    // OpenParam.BaseAddrSrcU = DUMP_UV_320352_ADDR0 + (OpenParam.ActiveVer/2 )*OpenParam.StrideSrcU;
    OpenParam.BaseAddrSrcV = 0;

    OpenParam.BaseAddrDesY = MAIN_ROTATION_Y_ADDR_A;
    OpenParam.BaseAddrDesU = MAIN_ROTATION_U_ADDR_A;
    OpenParam.BaseAddrDesV = 0;
    m_TdRotationOutHandle = MS_API_TD_RotationOpen(&OpenParam,&ErrCode);


    MS_API_TD_RotationFrameStart();

    printf("TD_TestRotation90DegreeMainYuv420 MAIN_ROTATION_Y_ADDR_A ErrCode = %d!\n",ErrCode);
    msleep(2000);

#endif

}
void TD_TestRotation270DegreeMainYuv420(void)
{

    MD_TD_RotationParmT OpenParam;
    MS_U32 ErrCode = MS_OK;
  
    //MS_U8 Iloop = 0;
    msleep(1500);

    MS_API_TD_WrapInit();

    memset(&OpenParam,0,sizeof(MD_TD_RotationParmT));

    //cfg video layer0
    OpenParam.RotationMode         = TD_ROTATION_270_DEGREE;
    OpenParam.RotationPixelFormat  = TD_ROTATION_PIX_FORMAT_420SP;

    OpenParam.InSwapEn             = 1;
    OpenParam.BigLittleInEndia     = 1;
    OpenParam.OutSwapEn            = 1;
    OpenParam.BigLittleOutEndia    = 1;
    OpenParam.OtMaxRD              = 1;
    OpenParam.OtMaxWR              = 1;


    OpenParam.DoneTimeOut          = 0xffff;
    
    OpenParam.ActiveHor          = 640;
    OpenParam.ActiveVer          = 320;
 
    OpenParam.StrideSrcY          = 640; 
    OpenParam.StrideSrcU          = 640; 

    OpenParam.StrideDesY          = 320;
    OpenParam.StrideDesU          = 320;

    OpenParam.StrideSrcV          = 0; 
    OpenParam.StrideDesV          = 0;

    OpenParam.BaseAddrSrcY = 0x23000000 + (OpenParam.ActiveHor -32);
    OpenParam.BaseAddrSrcU = 0x23032000+ (OpenParam.ActiveHor -32);

    OpenParam.BaseAddrSrcV = 0;

    OpenParam.BaseAddrDesY = MAIN_ROTATION_Y_ADDR;
    OpenParam.BaseAddrDesU = MAIN_ROTATION_U_ADDR;
    OpenParam.BaseAddrDesV = 0;


    m_TdRotationOutHandle = MS_API_TD_RotationOpen(&OpenParam,&ErrCode);
  
   
    MS_API_TD_RotationFrameStart();
    TD_PrintRotRegValue();

    printf("TD_TestRotation270DegreeMainYuv420 ErrCode = %d!\n",ErrCode);


}

void TD_TestRotation270DegreeMainYuv422(void)
{

    MD_TD_RotationParmT OpenParam;
    MS_U32 ErrCode = MS_OK;
  
    //MS_U8 Iloop = 0;
    msleep(1000);

    MS_API_TD_WrapInit();
    //memset(TD_ROTATION_Y_ADDR,0xaa,0x20000);//des y

    memset(&OpenParam,0,sizeof(MD_TD_RotationParmT));

    //cfg video layer0
    OpenParam.RotationMode         = TD_ROTATION_270_DEGREE;
    OpenParam.RotationPixelFormat  = TD_ROTATION_PIX_FORMAT_422SP;

    OpenParam.InSwapEn             = 1;
    OpenParam.BigLittleInEndia     = 1;
    OpenParam.OutSwapEn            = 1;
    OpenParam.BigLittleOutEndia    = 1;
    OpenParam.OtMaxRD              = 1;
    OpenParam.OtMaxWR              = 1;


    OpenParam.DoneTimeOut          = 0xffff;
    
    OpenParam.ActiveHor          = 352;
    OpenParam.ActiveVer          = 288; 
 
    OpenParam.StrideSrcY          = 352; 
    OpenParam.StrideSrcU          = 352; 

     
    OpenParam.StrideDesY          = 288;   
    OpenParam.StrideDesU          = 288;

    OpenParam.StrideSrcV          = 0; 
    OpenParam.StrideDesV          = 0;

    OpenParam.BaseAddrSrcY = 0x23000000 + (OpenParam.ActiveHor -32);
    OpenParam.BaseAddrSrcU = 0x23018C00 + (OpenParam.ActiveHor -32);
  // OpenParam.BaseAddrSrcY = DUMP_Y_320352_ADDR0 + (OpenParam.ActiveVer )*OpenParam.StrideSrcY;
   // OpenParam.BaseAddrSrcU = DUMP_UV_320352_ADDR0 + (OpenParam.ActiveVer/2 )*OpenParam.StrideSrcU;
    OpenParam.BaseAddrSrcV = 0;

    OpenParam.BaseAddrDesY = MAIN_ROTATION_Y_ADDR;
    OpenParam.BaseAddrDesU = MAIN_ROTATION_U_ADDR;
    OpenParam.BaseAddrDesV = 0;


    m_TdRotationOutHandle = MS_API_TD_RotationOpen(&OpenParam,&ErrCode);
  
   
    MS_API_TD_RotationFrameStart();
    TD_PrintRotRegValue();
    msleep(1000);

    printf("TD_TestRotation270DegreeMainYuv422 rotation ErrCode = %d!\n",ErrCode);


}

void TD_TestRotation90DegreeMainYuv422(void)
{

    MD_TD_RotationParmT OpenParam;
    MS_U32 ErrCode = MS_OK;
  
    //MS_U8 Iloop = 0;
    msleep(1000);

    MS_API_TD_WrapInit();
    //memset(TD_ROTATION_Y_ADDR,0xaa,0x20000);//des y

    memset(&OpenParam,0,sizeof(MD_TD_RotationParmT));

    //cfg video layer0
    OpenParam.RotationMode         = TD_ROTATION_90_DEGREE;
    OpenParam.RotationPixelFormat  = TD_ROTATION_PIX_FORMAT_422SP;

    OpenParam.InSwapEn             = 1;
    OpenParam.BigLittleInEndia     = 1;
    OpenParam.OutSwapEn            = 1;
    OpenParam.BigLittleOutEndia    = 1;
    OpenParam.OtMaxRD              = 1;
    OpenParam.OtMaxWR              = 1;


    OpenParam.DoneTimeOut          = 0xffff;
    
    OpenParam.ActiveHor          = 352;
    OpenParam.ActiveVer          = 288; 
 
    OpenParam.StrideSrcY          = 352; 
    OpenParam.StrideSrcU          = 352; 

     
    OpenParam.StrideDesY          = 288;   
    OpenParam.StrideDesU          = 288;

    OpenParam.StrideSrcV          = 0; 
    OpenParam.StrideDesV          = 0;

    OpenParam.BaseAddrSrcY = 0x23000000 + (OpenParam.ActiveVer -1)*OpenParam.StrideSrcY;
    OpenParam.BaseAddrSrcU = 0x23018C00 + (OpenParam.ActiveVer -1)*OpenParam.StrideSrcU;
  // OpenParam.BaseAddrSrcY = DUMP_Y_320352_ADDR0 + (OpenParam.ActiveVer )*OpenParam.StrideSrcY;
   // OpenParam.BaseAddrSrcU = DUMP_UV_320352_ADDR0 + (OpenParam.ActiveVer/2 )*OpenParam.StrideSrcU;
    OpenParam.BaseAddrSrcV = 0;

    OpenParam.BaseAddrDesY = MAIN_ROTATION_Y_ADDR;
    OpenParam.BaseAddrDesU = MAIN_ROTATION_U_ADDR;
    OpenParam.BaseAddrDesV = 0;


    m_TdRotationOutHandle = MS_API_TD_RotationOpen(&OpenParam,&ErrCode);
  
   
    MS_API_TD_RotationFrameStart();
    TD_PrintRotRegValue();
    msleep(1000);

    printf("TD_TestRotation90DegreeMainYuv422 rotation ErrCode = %d!\n",ErrCode);


}

void TD_TestRotation90DegreeMainYuv444(void)
{

    MD_TD_RotationParmT OpenParam;
    MS_U32 ErrCode = MS_OK;
  
    //MS_U8 Iloop = 0;
    
    MS_API_TD_WrapInit();
   
    memset(&OpenParam,0,sizeof(MD_TD_RotationParmT));

    //cfg video layer0
    OpenParam.RotationMode         = TD_ROTATION_90_DEGREE;
    OpenParam.RotationPixelFormat  = TD_ROTATION_PIX_FORMAT_RGB888; //means YUV or RGB separate 

    OpenParam.InSwapEn               =  1;
    OpenParam.BigLittleInEndia       =  1;
    OpenParam.OutSwapEn               = 1;
    OpenParam.BigLittleOutEndia       = 1;

    OpenParam.OtMaxRD              = 1;
    OpenParam.OtMaxWR              = 1;

    OpenParam.DoneTimeOut          = 0xffff;
    
    OpenParam.ActiveHor           = 640;
    OpenParam.ActiveVer           = 480; 
  
    OpenParam.StrideSrcY          = 2048; 
    OpenParam.StrideDesY          = 2048;
 
    OpenParam.StrideSrcU          = 2048; 
    OpenParam.StrideDesU          = 2048;

    OpenParam.StrideSrcV          = 2048; 
    OpenParam.StrideDesV          = 2048;


    OpenParam.BaseAddrSrcY = MAIN_Y_ADDR0 + (OpenParam.ActiveVer -1)*OpenParam.StrideSrcY;
    OpenParam.BaseAddrSrcU = MAIN_Y_ADDR0 + (OpenParam.ActiveVer -1)*OpenParam.StrideSrcU;
    OpenParam.BaseAddrSrcV = MAIN_Y_ADDR0 + (OpenParam.ActiveVer -1)*OpenParam.StrideSrcV;

    OpenParam.BaseAddrDesY = TD_ROTATION_Y_ADDR444;
    OpenParam.BaseAddrDesU = TD_ROTATION_U_ADDR444;
    OpenParam.BaseAddrDesV = TD_ROTATION_V_ADDR444;
    m_TdRotationOutHandle = MS_API_TD_RotationOpen(&OpenParam,&ErrCode);   
    MS_API_TD_RotationFrameStart();
    TD_PrintRotRegValue();
    msleep(1000);
    printf("kite debug >>  TD_TestRotation90DegreeMainYuv444 rotation ErrCode = %d!!!!!!!!!!!!\n\n\n\n\n",ErrCode);
}




void TestTDRotation(MS_U8 testCase)
{

    MS_U8 TestCase = TD_CASE_UNDEFINE;
    TestCase  = TD_ROTATION_90_DEGREE_MAIN_422;//TD_ROTATION_90_DEGREE_MAIN_420_IRQ;
    printf("TestTDRotation START @@@@@@@@@@@@@@@@.\n");
    switch( TestCase )
    {

        case TD_ROTATION_90_DEGREE_320352_MONO:
            TD_TestRotation90Degree320352YuvMONO(1,1,1,1);
            break;
        case TD_ROTATION_90_DEGREE_320352_MONO_ENDIAN_INPUT:
            TD_TestRotation90Degree320352YuvMONO(1,0,1,1);
            break;
        case TD_ROTATION_90_DEGREE_320352_MONO_SWAP_INPUT:
            TD_TestRotation90Degree320352YuvMONO(0,1,1,1);
            break;
        case TD_ROTATION_90_DEGREE_320352_MONO_ENDIAN_OUTPUT:
            TD_TestRotation90Degree320352YuvMONO(1,1,1,0);
            break;
        case TD_ROTATION_90_DEGREE_320352_MONO_SWAP_OUTPUT:
            TD_TestRotation90Degree320352YuvMONO(1,1,0,1);
            break;

        case TD_ROTATION_90_DEGREE_320352_420:
            TD_TestRotation90Degree320352Yuv420();
            break;
        case TD_ROTATION_90_DEGREE_320352_422:
            TD_TestRotation90Degree320352Yuv422();
            break;
        case TD_ROTATION_90_DEGREE_444:
            TD_TestRotation90DegreeYuv444();
            break;

        case TD_ROTATION_90_DEGREE_1080p_420_TIMEOUT:
            TD_TestRotation90Degree1080pYuv420_Timeout();
            break;

        case TD_ROTATION_270_DEGREE_320352_420:
            TD_TestRotation270Degree320352Yuv420();
            break;
        case TD_ROTATION_270_DEGREE_320352_422://VO_CASE_LAYER_TD_ROTATION_TEST_422
            TD_TestRotation270Degree320352Yuv422();
            break;
        
        case TD_ROTATION_90_DEGREE_MAIN_420_IRQ:   ////VO_CASE_LAYER_TD_ROTATION_TEST
       
          TD_TestRotation90DegreeMainYuv420_IRQ();
            break;

        case TD_ROTATION_90_DEGREE_MAIN_420:   ////VO_CASE_LAYER_TD_ROTATION_TEST
          //TD_TestRotation270DegreeMainYuv420();
          TD_TestRotation90DegreeMainYuv420();
            break;
        case TD_ROTATION_270_DEGREE_MAIN_420:
            TD_TestRotation270DegreeMainYuv420();
            break;
        case TD_ROTATION_90_DEGREE_MAIN_422:
            //TD_TestRotation90DegreeMainYuv422();
            TD_TestRotation270DegreeMainYuv422();
            break;
  
        case TD_ROTATION_90_DEGREE_MAIN_444:
            TD_TestRotation90DegreeMainYuv444();
            break;
            
            
        default:
            break;
                
    }
}




#if 1
#endif


void TD_MixerTestVideo320240Osd256200(MS_U32 ImgInDataMode)
{
    MD_TD_MixerParamaterT OpenParam;
    MS_U32 ErrCode = MS_OK;

    MS_API_TD_WrapInit();

    MS_API_TD_MixerInit();

    memset(&OpenParam,0,sizeof(MD_TD_MixerParamaterT));
    //memset(TD_MIXER_WB_ADDR_Y0,0x00,0x20000);//des y

    //cfg video layer0
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerEnable          = 1;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StartX = 198;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StartY = 42;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StopX  = 198 + 320;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StopY  = 42 + 240;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInDataMode        = ImgInDataMode;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].EndianModeY          = TD_VIDEO_LAYER_Y_ENDIAN_MODE1;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].EndianModeUV         = TD_VIDEO_LAYER_UV_ENDIAN_MODE3;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelHszie      = 320;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelVszie      = 240;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgOutPixelHszie     = 320;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgOutPixelVszie     = 240;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelStrideH    = 320;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelStrideV    = 0;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelOffsetH    = 0;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelOffsetV    = 0;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].GlobalAlpha          = 0xff;
    
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ReadAddress0Y        =  DUMP_Y_320240_ADDR0;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ReadAddress0UV       =  DUMP_UV_320240_ADDR0;

    OpenParam.LayerMixerOrder                                       = OpenParam.LayerMixerOrder|(0 << 0);

  


    //cfg OSD layer4
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].OsdEnable                = 0;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].OsdType                  = TD_RGB_24BIT;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].AlphaTpye                = TD_FIXED_VALUE;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].OsdPixelHszie            = 128;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].OsdPixelVszie            = 128;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].LayerPosition.StartX     = 198;   
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].LayerPosition.StartY     = 42;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].LayerPosition.StopX      = 198 + 128;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].LayerPosition.StopY      = 42 + 128;

    OpenParam.OSDLayerParam[TD_OSD_LAYER0].RequestBLen              = 0xf;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].DmaMap                   = TD_ORIGINAL_ORDER;//original
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].RevRGB                   = 1;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].DataInStride             = 256;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].AlphaInStride            = 256;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].RGB2YUVEnable            = 1;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].GlobalAlpha              = 0xff;

    OpenParam.OSDLayerParam[TD_OSD_LAYER0].ReadAddress0Value        = OSD0_VLU_ADDR0;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].ReadAddress0Alp          = OSD0_ALP_ADDR0;

    OpenParam.LayerMixerOrder                                       = OpenParam.LayerMixerOrder|(1 << 4);

    OpenParam.WindowZone.StartX                                     =   OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StartX;
    OpenParam.WindowZone.StopX                                      =  OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StopX ;
    OpenParam.WindowZone.StartY                                     = OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StartY;
    OpenParam.WindowZone.StopY                                      = OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StopY;





    OpenParam.BackGroundComp = 0x00008080;
    OpenParam.DisplayYUV2RGBEn = 1;

    //DMA OUT
    OpenParam.DmaWriteBackEn = 1;
    OpenParam.DmaWbParam.InputMode              = 1; //0：bt656  1:BT1120     
    
    OpenParam.DmaWbParam.DataFormat             = 1;     //RGB/RAW  1:YUV  
    OpenParam.DmaWbParam.DmaInputFormat         = 0;     //1`b0:YUV422;1`b1:YUV420    

    OpenParam.DmaWbParam.OutputMode             = 1 ;
    OpenParam.DmaWbParam.DmaInput422PixelOrder  = 0;
    OpenParam.DmaWbParam.RawPixelWidth          = 0;
    
    OpenParam.DmaWbParam.WriteBaseAddressY0     = TD_MIXER_WB_ADDR_Y0;
    OpenParam.DmaWbParam.WriteBaseAddressY1     = TD_MIXER_WB_ADDR_Y1;
    OpenParam.DmaWbParam.WriteBaseAddressUV0    = TD_MIXER_WB_ADDR_UV0;
    OpenParam.DmaWbParam.WriteBaseAddressUV1    = TD_MIXER_WB_ADDR_UV1;
    
    OpenParam.DmaWbParam.DataLineYStride        = 320;
    OpenParam.DmaWbParam.DataLineUVStride       = 320;       
    
    OpenParam.DmaWbParam.DramLoopSzie           = 0xFFFF;
    
    OpenParam.DmaWbParam.ActiveHszie            = 320;
    OpenParam.DmaWbParam.ActiveVszie            = 240;
    
    OpenParam.DmaWbParam.Ch1OtNum               = 1; 
    OpenParam.DmaWbParam.Ch1BlenMode            = 0; 
    OpenParam.DmaWbParam.Ch1ContinuousMode      = 1;   
    OpenParam.DmaWbParam.Ch1DmaYUVMap           = 0;
    OpenParam.DmaWbParam.Ch1WbErrDetectEn       = 0;         
    OpenParam.DmaWbParam.Ch1ErrUnit             = 1;
    OpenParam.DmaWbParam.Ch1ErrTh               = 1;
    OpenParam.DmaWbParam.Ch2OtNum               = 1;
    OpenParam.DmaWbParam.Ch2BlenMode            = 0;
    OpenParam.DmaWbParam.Ch2ContinuousMode      = 1;
    OpenParam.DmaWbParam.Ch2DmaYUVMap           = 0;
    OpenParam.DmaWbParam.Ch2WbErrDetectEn       = 0;    
    OpenParam.DmaWbParam.Ch2ErrUnit             = 1;
    OpenParam.DmaWbParam.Ch2ErrTh               = 1;
    //END
    m_TdMixerOutHandle = MS_API_TD_MixerOpen(&OpenParam,&ErrCode);
  
    *(volatile MS_U32 *)0x924a00cc = 0xff;


    MS_API_TD_MixerFrameStart();
    TD_PrintRotRegValue();
    TD_MixerPrintRegValue();

   
    msleep(2000);
    while(1)
    {    
        TD_MixerPrintRegValue();
        MS_API_TD_MixerFrameStart();
        msleep(3000);
        
    }
            
    printf("TD_MixerTestVideo320240Osd256200 Config done!\n");
}

void TD_MixerTestVideoMainRGB(MS_U32 ImgInDataMode)
{
    MD_TD_MixerParamaterT OpenParam;
    MS_U32 ErrCode = MS_OK;

    MS_API_TD_WrapInit();
   
    MS_API_TD_MixerInit();

    memset(&OpenParam,0,sizeof(MD_TD_MixerParamaterT));
    //memset(TD_MIXER_WB_ADDR_Y0,0x00,0x20000);//des y

    //cfg video layer0
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerEnable          = 1;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StartX = 198;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StartY = 42;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StopX  = 198 + 720;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StopY  = 42 + 576;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInDataMode        = ImgInDataMode;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].EndianModeY          = TD_VIDEO_LAYER_Y_ENDIAN_MODE1;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].EndianModeUV         = TD_VIDEO_LAYER_UV_ENDIAN_MODE2;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelHszie      = 1080;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelVszie      = 1920;
    
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgOutPixelHszie     = 720;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgOutPixelVszie     = 576;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelStrideH    = 1080;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelStrideV    = 0;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelOffsetH    = 0;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelOffsetV    = 0;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].GlobalAlpha          = 0xff;
    
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ReadAddress0Y        =  0x23000000;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ReadAddress0UV       =  0x23000000 + OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelHszie*OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelVszie ;

    OpenParam.LayerMixerOrder                                       = OpenParam.LayerMixerOrder|(0 << 0 );

  

    
    OpenParam.WindowZone.StartX                                     =   OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StartX;
    OpenParam.WindowZone.StopX                                      =  OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StopX ;
    OpenParam.WindowZone.StartY                                     = OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StartY;
    OpenParam.WindowZone.StopY                                      = OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StopY;



    OpenParam.BackGroundComp = 0x00ffffff;
    OpenParam.DisplayYUV2RGBEn = 1;

    //DMA OUT
    OpenParam.DmaWriteBackEn = 1;
    OpenParam.DmaWbParam.InputMode              = 1; //0：bt656  1:BT1120     
    
    OpenParam.DmaWbParam.DataFormat             = 0;     //0:RGB/RAW  1:YUV  
    OpenParam.DmaWbParam.DmaInputFormat         = 0;     //1`b0:YUV422;1`b1:YUV420    


    OpenParam.DmaWbParam.DmaInput422PixelOrder  = 0;


    OpenParam.DmaWbParam.OutputMode             = 0 ;  //0:rgb888  1:argb8888
    OpenParam.DmaWbParam.RawPixelWidth          = 7;   //7:24 bit //0:argb8888
    OpenParam.DmaWbParam.DataLineYStride        = 720*3;


    
    OpenParam.DmaWbParam.WriteBaseAddressY0     = MAIN_ROTATION_Y_ADDR;
    OpenParam.DmaWbParam.WriteBaseAddressY1     = MAIN_ROTATION_Y_ADDR;
    OpenParam.DmaWbParam.WriteBaseAddressUV0    = MAIN_ROTATION_U_ADDR;
    OpenParam.DmaWbParam.WriteBaseAddressUV1    = MAIN_ROTATION_U_ADDR;
    

    OpenParam.DmaWbParam.DataLineUVStride       = 0;       
    
    OpenParam.DmaWbParam.ActiveHszie            = 720;
    OpenParam.DmaWbParam.ActiveVszie            = 576;


    
    OpenParam.DmaWbParam.DramLoopSzie           = 0xFFFF;
    
    
    OpenParam.DmaWbParam.Ch1OtNum               = 1; 
    OpenParam.DmaWbParam.Ch1BlenMode            = 0; 
    OpenParam.DmaWbParam.Ch1ContinuousMode      = 1;   
    OpenParam.DmaWbParam.Ch1DmaYUVMap           = 1;
    OpenParam.DmaWbParam.Ch1WbErrDetectEn       = 0;         
    OpenParam.DmaWbParam.Ch1ErrUnit             = 1;
    OpenParam.DmaWbParam.Ch1ErrTh               = 1;
    
    OpenParam.DmaWbParam.Ch2OtNum               = 1;
    OpenParam.DmaWbParam.Ch2BlenMode            = 0;
    OpenParam.DmaWbParam.Ch2ContinuousMode      = 1;
    OpenParam.DmaWbParam.Ch2DmaYUVMap           = 0;
    OpenParam.DmaWbParam.Ch2WbErrDetectEn       = 0;    
    OpenParam.DmaWbParam.Ch2ErrUnit             = 1;
    OpenParam.DmaWbParam.Ch2ErrTh               = 1;
    //END
    m_TdMixerOutHandle = MS_API_TD_MixerOpen(&OpenParam,&ErrCode);
  

    MS_API_TD_MixerFrameStart();
    //TD_PrintRotRegValue();
    TD_MixerPrintRegValue();

   
    msleep(2000);
  
    printf("TD_MixerTestVideoMainRGB  Config done!...............................\n\n\n\n");
}



void TD_MixerTestVideoMainYUV_Postion(MS_U32 ImgInDataMode)
{
    MD_TD_MixerParamaterT OpenParam;
    MS_U32 ErrCode = MS_OK;

    MS_API_TD_WrapInit();
   
    MS_API_TD_MixerInit();

    memset(&OpenParam,0,sizeof(MD_TD_MixerParamaterT));
    
    //cfg video layer0
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerEnable          = 1;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StartX = 200;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StartY = 96;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StopX  = 200 + 320;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StopY  = 96 + 352;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInDataMode        = ImgInDataMode;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].EndianModeY          = TD_VIDEO_LAYER_Y_ENDIAN_MODE1;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].EndianModeUV         = TD_VIDEO_LAYER_UV_ENDIAN_MODE2;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelHszie      = 320;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelVszie      = 352;
    
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgOutPixelHszie     = 320;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgOutPixelVszie     = 352;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelStrideH    = 320;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelStrideV    = 0;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelOffsetH    = 0;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelOffsetV    = 0;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].GlobalAlpha          = 0xff;
    
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ReadAddress0Y        =  0x23000000;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ReadAddress0UV       =  0x2301b800;

    OpenParam.LayerMixerOrder                                       = OpenParam.LayerMixerOrder|(0 << 0 );

    //cfg OSD layer4
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].OsdEnable                = 1;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].OsdType                  = TD_RGB_32BIT;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].AlphaTpye                = TD_FIXED_VALUE;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].OsdPixelHszie            = 320;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].OsdPixelVszie            = 240;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].LayerPosition.StartX     = 192;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].LayerPosition.StartY     = 160;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].LayerPosition.StopX      = 192 + 320;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].LayerPosition.StopY      = 160 + 240;

    OpenParam.OSDLayerParam[TD_OSD_LAYER0].RequestBLen              = 0xf;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].DmaMap                   = TD_ORIGINAL_ORDER;//original
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].RevRGB                   = 1;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].DataInStride             = 1280;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].AlphaInStride            = 320;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].RGB2YUVEnable            = 1;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].GlobalAlpha              = 0xff;

    OpenParam.OSDLayerParam[TD_OSD_LAYER0].ReadAddress0Value        = OSD0_VLU_ADDR0;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].ReadAddress0Alp          = OSD0_ALP_ADDR0;

    OpenParam.LayerMixerOrder                                       = OpenParam.LayerMixerOrder|(1 << 16);

    OpenParam.WindowZone.StartX                                     =  64;
    OpenParam.WindowZone.StopX                                      =  64 + 640;
    OpenParam.WindowZone.StartY                                     =  64;
    OpenParam.WindowZone.StopY                                      =  64 + 480;


    OpenParam.BackGroundComp = 0x00ffffff;
    OpenParam.DisplayYUV2RGBEn = 1;

    //DMA OUT
    OpenParam.DmaWriteBackEn = 1;
    OpenParam.DmaWbParam.InputMode              = 1; //0：bt656  1:BT1120     
    
    OpenParam.DmaWbParam.DataFormat             = 1;     //RGB/RAW  1:YUV  
    OpenParam.DmaWbParam.DmaInputFormat         = 0;     //1`b0:YUV422;1`b1:YUV420    

    OpenParam.DmaWbParam.OutputMode             = 1 ;
    OpenParam.DmaWbParam.DmaInput422PixelOrder  = 0;
    OpenParam.DmaWbParam.RawPixelWidth          = 0;
    
    OpenParam.DmaWbParam.WriteBaseAddressY0     = MAIN_ROTATION_Y_ADDR_A;
    OpenParam.DmaWbParam.WriteBaseAddressY1     = MAIN_ROTATION_U_ADDR_A;
    OpenParam.DmaWbParam.WriteBaseAddressUV0    = MAIN_ROTATION_Y_ADDR_A;
    OpenParam.DmaWbParam.WriteBaseAddressUV1    = MAIN_ROTATION_U_ADDR_A;
    
    OpenParam.DmaWbParam.DataLineYStride        = 640;
    OpenParam.DmaWbParam.DataLineUVStride       = 640;       
    
    OpenParam.DmaWbParam.ActiveHszie            = 640;
    OpenParam.DmaWbParam.ActiveVszie            = 480;

    OpenParam.DmaWbParam.DramLoopSzie           = 0xFFFF;
    
    OpenParam.DmaWbParam.Ch1OtNum               = 1; 
    OpenParam.DmaWbParam.Ch1BlenMode            = 0; 
    OpenParam.DmaWbParam.Ch1ContinuousMode      = 1;   
    OpenParam.DmaWbParam.Ch1DmaYUVMap           = 0;
    OpenParam.DmaWbParam.Ch1WbErrDetectEn       = 0;         
    OpenParam.DmaWbParam.Ch1ErrUnit             = 1;
    OpenParam.DmaWbParam.Ch1ErrTh               = 1;
    
    OpenParam.DmaWbParam.Ch2OtNum               = 1;
    OpenParam.DmaWbParam.Ch2BlenMode            = 0;
    OpenParam.DmaWbParam.Ch2ContinuousMode      = 1;
    OpenParam.DmaWbParam.Ch2DmaYUVMap           = 0;
    OpenParam.DmaWbParam.Ch2WbErrDetectEn       = 0;    
    OpenParam.DmaWbParam.Ch2ErrUnit             = 1;
    OpenParam.DmaWbParam.Ch2ErrTh               = 1;
    //END
    m_TdMixerOutHandle = MS_API_TD_MixerOpen(&OpenParam,&ErrCode);
  

    MS_API_TD_MixerFrameStart();
    TD_PrintRotRegValue();
    TD_MixerPrintRegValue();

   
    msleep(2000);
  
    printf("TD_MixerTestVideoMainYUV_Postion Display Config done!...............................\n\n\n\n");
}
void TD_MixerTestVideoMainYUV_Joint_debug(MS_U32 ImgInDataMode)
{
    MD_TD_MixerParamaterT OpenParam;
    MS_U32 ErrCode = MS_OK;
    msleep(1000);

    MS_API_TD_WrapInit();
   
    MS_API_TD_MixerInit();

    memset(&OpenParam,0,sizeof(MD_TD_MixerParamaterT));
    
    //cfg video layer0
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerEnable          = 0;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StartX = 64;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StartY = 64;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StopX  = 64 + 320;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StopY  = 64 + 240;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInDataMode        = ImgInDataMode;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].EndianModeY          = TD_VIDEO_LAYER_Y_ENDIAN_MODE2;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].EndianModeUV         = TD_VIDEO_LAYER_UV_ENDIAN_MODE2;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelHszie      = 320;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelVszie      = 240;
    
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgOutPixelHszie     = 320;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgOutPixelVszie     = 240;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelStrideH    = 2048;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelStrideV    = 0;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelOffsetH    = 0;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelOffsetV    = 0;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].GlobalAlpha          = 0xff;
    
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ReadAddress0Y        =  0x20000000;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ReadAddress0UV       =  0x20280000;

    OpenParam.LayerMixerOrder                                       = OpenParam.LayerMixerOrder|(0 << 0 );

    //cfg OSD layer4
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].OsdEnable                = 1;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].OsdType                  = TD_RGB_32BIT;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].AlphaTpye                = TD_FIXED_VALUE;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].OsdPixelHszie            = 320;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].OsdPixelVszie            = 240;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].LayerPosition.StartX     = 64;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].LayerPosition.StartY     = 64;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].LayerPosition.StopX      = 64 + 320;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].LayerPosition.StopY      = 64 + 240;

    OpenParam.OSDLayerParam[TD_OSD_LAYER0].RequestBLen              = 0xf;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].DmaMap                   = TD_ORIGINAL_ORDER;//original
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].RevRGB                   = 1;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].DataInStride             = 1280;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].AlphaInStride            = 320;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].RGB2YUVEnable            = 1;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].GlobalAlpha              = 0xff;

    OpenParam.OSDLayerParam[TD_OSD_LAYER0].ReadAddress0Value        = OSD0_VLU_ADDR0;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].ReadAddress0Alp          = OSD0_ALP_ADDR0;

    OpenParam.LayerMixerOrder                                       = OpenParam.LayerMixerOrder|(1 << 16);

    OpenParam.WindowZone.StartX                                     =  64;
    OpenParam.WindowZone.StopX                                      =  64 + 320;
    OpenParam.WindowZone.StartY                                     =  64;
    OpenParam.WindowZone.StopY                                      =  64 + 240;


    OpenParam.BackGroundComp = 0x00ffffff;
    OpenParam.DisplayYUV2RGBEn = 1;

    //DMA OUT
    OpenParam.DmaWriteBackEn = 1;
    OpenParam.DmaWbParam.InputMode              = 1; //0：bt656  1:BT1120     
    
    OpenParam.DmaWbParam.DataFormat             = 1;     //RGB/RAW  1:YUV  
    OpenParam.DmaWbParam.DmaInputFormat         = 0;     //1`b0:YUV422;1`b1:YUV420    

    OpenParam.DmaWbParam.OutputMode             = 1 ;
    OpenParam.DmaWbParam.DmaInput422PixelOrder  = 0;
    OpenParam.DmaWbParam.RawPixelWidth          = 0;
    
    OpenParam.DmaWbParam.WriteBaseAddressY0     = MAIN_ROTATION_Y_ADDR_A;
    OpenParam.DmaWbParam.WriteBaseAddressY1     = MAIN_ROTATION_Y_ADDR_A;
    OpenParam.DmaWbParam.WriteBaseAddressUV0    = MAIN_ROTATION_U_ADDR_A;
    OpenParam.DmaWbParam.WriteBaseAddressUV1    = MAIN_ROTATION_U_ADDR_A;
    
    OpenParam.DmaWbParam.DataLineYStride        = 2048;
    OpenParam.DmaWbParam.DataLineUVStride       = 2048;       
    
    OpenParam.DmaWbParam.ActiveHszie            = 320;
    OpenParam.DmaWbParam.ActiveVszie            = 240;

    OpenParam.DmaWbParam.DramLoopSzie           = 0xFFFF;
    
    OpenParam.DmaWbParam.Ch1OtNum               = 1; 
    OpenParam.DmaWbParam.Ch1BlenMode            = 0; 
    OpenParam.DmaWbParam.Ch1ContinuousMode      = 1;   
    OpenParam.DmaWbParam.Ch1DmaYUVMap           = 0;
    OpenParam.DmaWbParam.Ch1WbErrDetectEn       = 0;         
    OpenParam.DmaWbParam.Ch1ErrUnit             = 1;
    OpenParam.DmaWbParam.Ch1ErrTh               = 1;
    
    OpenParam.DmaWbParam.Ch2OtNum               = 1;
    OpenParam.DmaWbParam.Ch2BlenMode            = 0;
    OpenParam.DmaWbParam.Ch2ContinuousMode      = 1;
    OpenParam.DmaWbParam.Ch2DmaYUVMap           = 0;
    OpenParam.DmaWbParam.Ch2WbErrDetectEn       = 0;    
    OpenParam.DmaWbParam.Ch2ErrUnit             = 1;
    OpenParam.DmaWbParam.Ch2ErrTh               = 1;
    //END
    m_TdMixerOutHandle = MS_API_TD_MixerOpen(&OpenParam,&ErrCode);
  

    MS_API_TD_MixerFrameStart();
#if 0
    msleep(2000);
    OpenParam.DmaWbParam.WriteBaseAddressY0     = MAIN_ROTATION_Y_ADDR_A;
    OpenParam.DmaWbParam.WriteBaseAddressY1     = MAIN_ROTATION_Y_ADDR_A;
    OpenParam.DmaWbParam.WriteBaseAddressUV0    = MAIN_ROTATION_U_ADDR_A;
    OpenParam.DmaWbParam.WriteBaseAddressUV1    = MAIN_ROTATION_U_ADDR_A;

    MH_TD_set_DispMixAlp0_Layer0GlbAlp(0xee);
    MH_TD_set_WbBaseAddr0Y(OpenParam.DmaWbParam.WriteBaseAddressY0);
    MH_TD_set_WbBaseAddr1Y(OpenParam.DmaWbParam.WriteBaseAddressY1);
    MH_TD_set_WbBaseAddr0UV(OpenParam.DmaWbParam.WriteBaseAddressUV0); 
    MH_TD_set_WbBaseAddr1UV(OpenParam.DmaWbParam.WriteBaseAddressUV1);

    MS_API_TD_MixerFrameStart();
    msleep(2000);
#endif
    printf("TD_MixerTestVideoMainYUV_Joint Config done!...ErrCode = %d.......................\n\n\n",ErrCode);
}

void TD_MixerTestVideoMainYUV_Joint(MS_U32 ImgInDataMode)
{
    MD_TD_MixerParamaterT OpenParam;
    MS_U32 ErrCode = MS_OK;
    msleep(1000);

    MS_API_TD_WrapInit();
   
    MS_API_TD_MixerInit();

    memset(&OpenParam,0,sizeof(MD_TD_MixerParamaterT));
    
    //cfg video layer0
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerEnable          = 0;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StartX = 64;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StartY = 64;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StopX  = 64 + 320;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StopY  = 64 + 240;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInDataMode        = ImgInDataMode;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].EndianModeY          = TD_VIDEO_LAYER_Y_ENDIAN_MODE2;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].EndianModeUV         = TD_VIDEO_LAYER_UV_ENDIAN_MODE2;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelHszie      = 320;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelVszie      = 240;
    
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgOutPixelHszie     = 320;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgOutPixelVszie     = 240;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelStrideH    = 2048;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelStrideV    = 0;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelOffsetH    = 0;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelOffsetV    = 0;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].GlobalAlpha          = 0xff;
    
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ReadAddress0Y        =  0x20000000;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ReadAddress0UV       =  0x20280000;

    OpenParam.LayerMixerOrder                                       = OpenParam.LayerMixerOrder|(0 << 0 );

    //cfg OSD layer4
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].OsdEnable                = 0;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].OsdType                  = TD_RGB_32BIT;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].AlphaTpye                = TD_FIXED_VALUE;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].OsdPixelHszie            = 320;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].OsdPixelVszie            = 240;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].LayerPosition.StartX     = 64;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].LayerPosition.StartY     = 64;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].LayerPosition.StopX      = 64 + 320;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].LayerPosition.StopY      = 64 + 240;

    OpenParam.OSDLayerParam[TD_OSD_LAYER0].RequestBLen              = 0xf;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].DmaMap                   = TD_ORIGINAL_ORDER;//original
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].RevRGB                   = 1;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].DataInStride             = 1280;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].AlphaInStride            = 320;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].RGB2YUVEnable            = 1;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].GlobalAlpha              = 0xff;

    OpenParam.OSDLayerParam[TD_OSD_LAYER0].ReadAddress0Value        = OSD0_VLU_ADDR0;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].ReadAddress0Alp          = OSD0_ALP_ADDR0;

    OpenParam.LayerMixerOrder                                       = OpenParam.LayerMixerOrder|(1 << 16);

    OpenParam.WindowZone.StartX                                     =  64;
    OpenParam.WindowZone.StopX                                      =  64 + 320;
    OpenParam.WindowZone.StartY                                     =  64;
    OpenParam.WindowZone.StopY                                      =  64 + 240;


    OpenParam.BackGroundComp = 0x0011aa11;
    OpenParam.DisplayYUV2RGBEn = 1;

    //DMA OUT
    OpenParam.DmaWriteBackEn = 1;
    OpenParam.DmaWbParam.InputMode              = 1; //0：bt656  1:BT1120     
    
    OpenParam.DmaWbParam.DataFormat             = 1;     //RGB/RAW  1:YUV  
    OpenParam.DmaWbParam.DmaInputFormat         = 0;     //1`b0:YUV422;1`b1:YUV420    

    OpenParam.DmaWbParam.OutputMode             = 1 ;
    OpenParam.DmaWbParam.DmaInput422PixelOrder  = 0;
    OpenParam.DmaWbParam.RawPixelWidth          = 0;
    
    OpenParam.DmaWbParam.WriteBaseAddressY0     = MAIN_ROTATION_Y_ADDR;
    OpenParam.DmaWbParam.WriteBaseAddressY1     = MAIN_ROTATION_Y_ADDR;
    OpenParam.DmaWbParam.WriteBaseAddressUV0    = MAIN_ROTATION_U_ADDR;
    OpenParam.DmaWbParam.WriteBaseAddressUV1    = MAIN_ROTATION_U_ADDR;
    
    OpenParam.DmaWbParam.DataLineYStride        = 2048;
    OpenParam.DmaWbParam.DataLineUVStride       = 2048;       
    
    OpenParam.DmaWbParam.ActiveHszie            = 320;
    OpenParam.DmaWbParam.ActiveVszie            = 240;

    OpenParam.DmaWbParam.DramLoopSzie           = 0xFFFF;
    
    OpenParam.DmaWbParam.Ch1OtNum               = 1; 
    OpenParam.DmaWbParam.Ch1BlenMode            = 0; 
    OpenParam.DmaWbParam.Ch1ContinuousMode      = 1;   
    OpenParam.DmaWbParam.Ch1DmaYUVMap           = 0;
    OpenParam.DmaWbParam.Ch1WbErrDetectEn       = 0;         
    OpenParam.DmaWbParam.Ch1ErrUnit             = 1;
    OpenParam.DmaWbParam.Ch1ErrTh               = 1;
    
    OpenParam.DmaWbParam.Ch2OtNum               = 1;
    OpenParam.DmaWbParam.Ch2BlenMode            = 0;
    OpenParam.DmaWbParam.Ch2ContinuousMode      = 1;
    OpenParam.DmaWbParam.Ch2DmaYUVMap           = 0;
    OpenParam.DmaWbParam.Ch2WbErrDetectEn       = 0;    
    OpenParam.DmaWbParam.Ch2ErrUnit             = 1;
    OpenParam.DmaWbParam.Ch2ErrTh               = 1;
    //END
    m_TdMixerOutHandle = MS_API_TD_MixerOpen(&OpenParam,&ErrCode);
  

    MS_API_TD_MixerFrameStart();

    TD_PrintRotRegValue();
#if 0
    msleep(2000);
    OpenParam.DmaWbParam.WriteBaseAddressY0     = MAIN_ROTATION_Y_ADDR_A;
    OpenParam.DmaWbParam.WriteBaseAddressY1     = MAIN_ROTATION_Y_ADDR_A;
    OpenParam.DmaWbParam.WriteBaseAddressUV0    = MAIN_ROTATION_U_ADDR_A;
    OpenParam.DmaWbParam.WriteBaseAddressUV1    = MAIN_ROTATION_U_ADDR_A;

    MH_TD_set_DispMixAlp0_Layer0GlbAlp(0xee);
    MH_TD_set_WbBaseAddr0Y(OpenParam.DmaWbParam.WriteBaseAddressY0);
    MH_TD_set_WbBaseAddr1Y(OpenParam.DmaWbParam.WriteBaseAddressY1);
    MH_TD_set_WbBaseAddr0UV(OpenParam.DmaWbParam.WriteBaseAddressUV0); 
    MH_TD_set_WbBaseAddr1UV(OpenParam.DmaWbParam.WriteBaseAddressUV1);

    MS_API_TD_MixerFrameStart();
    msleep(2000);
#endif
    printf("TD_MixerTestVideoMainYUV_Joint Config done!...ErrCode = %d.......................\n\n\n",ErrCode);
}


void TD_MixerTestVideoMainYUV_Crop(MS_U32 ImgInDataMode)
{
    MD_TD_MixerParamaterT OpenParam;
    MS_U32 ErrCode = MS_OK;

    MS_API_TD_WrapInit();
   
    MS_API_TD_MixerInit();

    memset(&OpenParam,0,sizeof(MD_TD_MixerParamaterT));
    
    //cfg video layer0
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerEnable          = 1;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StartX = 136;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StartY = 96;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StopX  = 136 + 160;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StopY  = 96 + 176;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInDataMode        = ImgInDataMode;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].EndianModeY          = TD_VIDEO_LAYER_Y_ENDIAN_MODE1;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].EndianModeUV         = TD_VIDEO_LAYER_UV_ENDIAN_MODE2;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelHszie      = 160;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelVszie      = 176;
    
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgOutPixelHszie     = 160;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgOutPixelVszie     = 176;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelStrideH    = 320;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelStrideV    = 0;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelOffsetH    = (320-160)>>3;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelOffsetV    = 352 -176;














    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].GlobalAlpha          = 0xff;
    
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ReadAddress0Y        =  0x23000000;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ReadAddress0UV       =  0x2301b800;

    OpenParam.LayerMixerOrder                                       = OpenParam.LayerMixerOrder|(0 << 0 );

    //cfg OSD layer4
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].OsdEnable                = 1;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].OsdType                  = TD_RGB_32BIT;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].AlphaTpye                = TD_FIXED_VALUE;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].OsdPixelHszie            = 320;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].OsdPixelVszie            = 240;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].LayerPosition.StartX     = 192;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].LayerPosition.StartY     = 160;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].LayerPosition.StopX      = 192 + 320;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].LayerPosition.StopY      = 160 + 240;

    OpenParam.OSDLayerParam[TD_OSD_LAYER0].RequestBLen              = 0xf;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].DmaMap                   = TD_ORIGINAL_ORDER;//original
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].RevRGB                   = 1;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].DataInStride             = 1280;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].AlphaInStride            = 320;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].RGB2YUVEnable            = 1;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].GlobalAlpha              = 0xff;

    OpenParam.OSDLayerParam[TD_OSD_LAYER0].ReadAddress0Value        = OSD0_VLU_ADDR0;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].ReadAddress0Alp          = OSD0_ALP_ADDR0;

    OpenParam.LayerMixerOrder                                       = OpenParam.LayerMixerOrder|(1 << 16);

    OpenParam.WindowZone.StartX                                     =  64;
    OpenParam.WindowZone.StopX                                      =  64 + 640;
    OpenParam.WindowZone.StartY                                     =  64;
    OpenParam.WindowZone.StopY                                      =  64 + 480;


    OpenParam.BackGroundComp = 0x00ffffff;
    OpenParam.DisplayYUV2RGBEn = 1;

    //DMA OUT
    OpenParam.DmaWriteBackEn = 1;
    OpenParam.DmaWbParam.InputMode              = 1; //0：bt656  1:BT1120     
    
    OpenParam.DmaWbParam.DataFormat             = 1;     //RGB/RAW  1:YUV  
    OpenParam.DmaWbParam.DmaInputFormat         = 0;     //1`b0:YUV422;1`b1:YUV420    

    OpenParam.DmaWbParam.OutputMode             = 1 ;
    OpenParam.DmaWbParam.DmaInput422PixelOrder  = 0;
    OpenParam.DmaWbParam.RawPixelWidth          = 0;
    
    OpenParam.DmaWbParam.WriteBaseAddressY0     = MAIN_ROTATION_Y_ADDR;
    OpenParam.DmaWbParam.WriteBaseAddressY1     = MAIN_ROTATION_Y_ADDR;
    OpenParam.DmaWbParam.WriteBaseAddressUV0    = MAIN_ROTATION_U_ADDR;
    OpenParam.DmaWbParam.WriteBaseAddressUV1    = MAIN_ROTATION_U_ADDR;
    
    OpenParam.DmaWbParam.DataLineYStride        = 640;
    OpenParam.DmaWbParam.DataLineUVStride       = 640;       
    
    OpenParam.DmaWbParam.ActiveHszie            = 640;
    OpenParam.DmaWbParam.ActiveVszie            = 480;

    OpenParam.DmaWbParam.DramLoopSzie           = 0xFFFF;
    
    OpenParam.DmaWbParam.Ch1OtNum               = 1; 
    OpenParam.DmaWbParam.Ch1BlenMode            = 0; 
    OpenParam.DmaWbParam.Ch1ContinuousMode      = 1;   
    OpenParam.DmaWbParam.Ch1DmaYUVMap           = 0;
    OpenParam.DmaWbParam.Ch1WbErrDetectEn       = 0;         
    OpenParam.DmaWbParam.Ch1ErrUnit             = 1;
    OpenParam.DmaWbParam.Ch1ErrTh               = 1;
    
    OpenParam.DmaWbParam.Ch2OtNum               = 1;
    OpenParam.DmaWbParam.Ch2BlenMode            = 0;
    OpenParam.DmaWbParam.Ch2ContinuousMode      = 1;
    OpenParam.DmaWbParam.Ch2DmaYUVMap           = 0;
    OpenParam.DmaWbParam.Ch2WbErrDetectEn       = 0;    
    OpenParam.DmaWbParam.Ch2ErrUnit             = 1;
    OpenParam.DmaWbParam.Ch2ErrTh               = 1;
    //END
    m_TdMixerOutHandle = MS_API_TD_MixerOpen(&OpenParam,&ErrCode);
  

    MS_API_TD_MixerFrameStart();
    TD_PrintRotRegValue();
    TD_MixerPrintRegValue();

   
    msleep(2000);
  
    printf("TD_MixerTestVideoMainYUV_Crop Display Config done!...............................\n\n\n\n");
}





void TD_MixerTestVideoMainYUV_MixerSelect(MS_U32 ImgInDataMode)
{
    MD_TD_MixerParamaterT OpenParam;
    MS_U32 ErrCode = MS_OK;

    MS_API_TD_WrapInit();
   
    MS_API_TD_MixerInit();

    memset(&OpenParam,0,sizeof(MD_TD_MixerParamaterT));
    
    //cfg video layer0
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerEnable          = 1;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StartX = 198;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StartY = 42;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StopX  = 198 + 320;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StopY  = 42 + 352;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInDataMode        = ImgInDataMode;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].EndianModeY          = TD_VIDEO_LAYER_Y_ENDIAN_MODE1;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].EndianModeUV         = TD_VIDEO_LAYER_UV_ENDIAN_MODE2;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelHszie      = 320;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelVszie      = 352;
    
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgOutPixelHszie     = 320;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgOutPixelVszie     = 352;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelStrideH    = 320;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelStrideV    = 0;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelOffsetH    = 0;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelOffsetV    = 0;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].GlobalAlpha          = 0x99;
    
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ReadAddress0Y        =  0x23000000;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ReadAddress0UV       =  0x2301b800;

    OpenParam.LayerMixerOrder                                       = OpenParam.LayerMixerOrder|(1 << 0 );

    //cfg OSD layer4
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].OsdEnable                = 1;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].OsdType                  = TD_RGB_32BIT;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].AlphaTpye                = TD_L2_ALPHA_ADDR;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].OsdPixelHszie            = 320;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].OsdPixelVszie            = 240;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].LayerPosition.StartX     = 198;   
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].LayerPosition.StartY     = 42;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].LayerPosition.StopX      = 198 + 320;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].LayerPosition.StopY      = 42 + 240;

    OpenParam.OSDLayerParam[TD_OSD_LAYER0].RequestBLen              = 0xf;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].DmaMap                   = TD_ORIGINAL_ORDER;//original
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].RevRGB                   = 1;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].DataInStride             = 1280;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].AlphaInStride            = 320;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].RGB2YUVEnable            = 1;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].GlobalAlpha              = 0xff;

    OpenParam.OSDLayerParam[TD_OSD_LAYER0].ReadAddress0Value        = OSD0_VLU_ADDR0;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].ReadAddress0Alp          = OSD0_ALP_ADDR0;

    OpenParam.LayerMixerOrder                                       = OpenParam.LayerMixerOrder|(0 << 16);

    OpenParam.WindowZone.StartX                                     =  198;
    OpenParam.WindowZone.StopX                                      =  198 + 640;
    OpenParam.WindowZone.StartY                                     =  42;
    OpenParam.WindowZone.StopY                                      =  42 + 480;


    OpenParam.BackGroundComp = 0x00ffffff;
    OpenParam.DisplayYUV2RGBEn = 1;

    //DMA OUT
    OpenParam.DmaWriteBackEn = 1;
    OpenParam.DmaWbParam.InputMode              = 1; //0：bt656  1:BT1120     
    
    OpenParam.DmaWbParam.DataFormat             = 1;     //RGB/RAW  1:YUV  
    OpenParam.DmaWbParam.DmaInputFormat         = 0;     //1`b0:YUV422;1`b1:YUV420    

    OpenParam.DmaWbParam.OutputMode             = 1 ;
    OpenParam.DmaWbParam.DmaInput422PixelOrder  = 0;
    OpenParam.DmaWbParam.RawPixelWidth          = 0;
    
    OpenParam.DmaWbParam.WriteBaseAddressY0     = MAIN_ROTATION_Y_ADDR;
    OpenParam.DmaWbParam.WriteBaseAddressY1     = MAIN_ROTATION_Y_ADDR;
    OpenParam.DmaWbParam.WriteBaseAddressUV0    = MAIN_ROTATION_U_ADDR;
    OpenParam.DmaWbParam.WriteBaseAddressUV1    = MAIN_ROTATION_U_ADDR;
    
    OpenParam.DmaWbParam.DataLineYStride        = 640;
    OpenParam.DmaWbParam.DataLineUVStride       = 640;       
    
    OpenParam.DmaWbParam.ActiveHszie            = 640;
    OpenParam.DmaWbParam.ActiveVszie            = 480;

    OpenParam.DmaWbParam.DramLoopSzie           = 0xFFFF;
    
    OpenParam.DmaWbParam.Ch1OtNum               = 1; 
    OpenParam.DmaWbParam.Ch1BlenMode            = 0; 
    OpenParam.DmaWbParam.Ch1ContinuousMode      = 1;   
    OpenParam.DmaWbParam.Ch1DmaYUVMap           = 0;
    OpenParam.DmaWbParam.Ch1WbErrDetectEn       = 0;         
    OpenParam.DmaWbParam.Ch1ErrUnit             = 1;
    OpenParam.DmaWbParam.Ch1ErrTh               = 1;
    
    OpenParam.DmaWbParam.Ch2OtNum               = 1;
    OpenParam.DmaWbParam.Ch2BlenMode            = 0;
    OpenParam.DmaWbParam.Ch2ContinuousMode      = 1;
    OpenParam.DmaWbParam.Ch2DmaYUVMap           = 0;
    OpenParam.DmaWbParam.Ch2WbErrDetectEn       = 0;    
    OpenParam.DmaWbParam.Ch2ErrUnit             = 1;
    OpenParam.DmaWbParam.Ch2ErrTh               = 1;
    //END
    m_TdMixerOutHandle = MS_API_TD_MixerOpen(&OpenParam,&ErrCode);
  

    MS_API_TD_MixerFrameStart();
    TD_PrintRotRegValue();
    TD_MixerPrintRegValue();

   
    msleep(2000);
  
    printf("TD_MixerTestVideoMainYUV_MixerSelect Display Config done!...............................\n\n\n\n");
}

void TD_MixerTestVideoMainYUV_Alpha(MS_U32 ImgInDataMode)
{
    MD_TD_MixerParamaterT OpenParam;
    MS_U32 ErrCode = MS_OK;

    MS_API_TD_WrapInit();
   
    MS_API_TD_MixerInit();

    memset(&OpenParam,0,sizeof(MD_TD_MixerParamaterT));
    
    //cfg video layer0
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerEnable          = 1;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StartX = 198;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StartY = 42;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StopX  = 198 + 320;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StopY  = 42 + 352;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInDataMode        = ImgInDataMode;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].EndianModeY          = TD_VIDEO_LAYER_Y_ENDIAN_MODE1;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].EndianModeUV         = TD_VIDEO_LAYER_UV_ENDIAN_MODE2;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelHszie      = 320;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelVszie      = 352;
    
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgOutPixelHszie     = 320;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgOutPixelVszie     = 352;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelStrideH    = 320;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelStrideV    = 0;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelOffsetH    = 0;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelOffsetV    = 0;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].GlobalAlpha          = 0xff;
    
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ReadAddress0Y        =  0x23000000;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ReadAddress0UV       =  0x2301b800;

    OpenParam.LayerMixerOrder                                       = OpenParam.LayerMixerOrder|(0 << 0 );

  


    //cfg OSD layer4
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].OsdEnable                = 1;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].OsdType                  = TD_RGB_32BIT;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].AlphaTpye                = TD_L2_ALPHA_ADDR;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].OsdPixelHszie            = 320;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].OsdPixelVszie            = 240;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].LayerPosition.StartX     = 198;   
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].LayerPosition.StartY     = 42;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].LayerPosition.StopX      = 198 + 320;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].LayerPosition.StopY      = 42 + 240;

    OpenParam.OSDLayerParam[TD_OSD_LAYER0].RequestBLen              = 0xf;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].DmaMap                   = TD_ORIGINAL_ORDER;//original
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].RevRGB                   = 1;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].DataInStride             = 1280;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].AlphaInStride            = 320;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].RGB2YUVEnable            = 1;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].GlobalAlpha              = 0xff;

    OpenParam.OSDLayerParam[TD_OSD_LAYER0].ReadAddress0Value        = OSD0_VLU_ADDR0;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].ReadAddress0Alp          = OSD0_ALP_ADDR0;

    OpenParam.LayerMixerOrder                                       = OpenParam.LayerMixerOrder|(1 << 16);

    OpenParam.WindowZone.StartX                                     =  198;
    OpenParam.WindowZone.StopX                                      =  198 + 640;
    OpenParam.WindowZone.StartY                                     =  42;
    OpenParam.WindowZone.StopY                                      =  42 + 480;


    OpenParam.BackGroundComp = 0x00ffffff;
    OpenParam.DisplayYUV2RGBEn = 1;

    //DMA OUT
    OpenParam.DmaWriteBackEn = 1;
    OpenParam.DmaWbParam.InputMode              = 1; //0：bt656  1:BT1120     
    
    OpenParam.DmaWbParam.DataFormat             = 1;     //RGB/RAW  1:YUV  
    OpenParam.DmaWbParam.DmaInputFormat         = 0;     //1`b0:YUV422;1`b1:YUV420    

    OpenParam.DmaWbParam.OutputMode             = 1 ;
    OpenParam.DmaWbParam.DmaInput422PixelOrder  = 0;
    OpenParam.DmaWbParam.RawPixelWidth          = 0;
    
    OpenParam.DmaWbParam.WriteBaseAddressY0     = MAIN_ROTATION_Y_ADDR;
    OpenParam.DmaWbParam.WriteBaseAddressY1     = MAIN_ROTATION_Y_ADDR;
    OpenParam.DmaWbParam.WriteBaseAddressUV0    = MAIN_ROTATION_U_ADDR;
    OpenParam.DmaWbParam.WriteBaseAddressUV1    = MAIN_ROTATION_U_ADDR;
    
    OpenParam.DmaWbParam.DataLineYStride        = 640;
    OpenParam.DmaWbParam.DataLineUVStride       = 640;       
    
    OpenParam.DmaWbParam.ActiveHszie            = 640;
    OpenParam.DmaWbParam.ActiveVszie            = 480;

    OpenParam.DmaWbParam.DramLoopSzie           = 0xFFFF;
    
    OpenParam.DmaWbParam.Ch1OtNum               = 1; 
    OpenParam.DmaWbParam.Ch1BlenMode            = 0; 
    OpenParam.DmaWbParam.Ch1ContinuousMode      = 1;   
    OpenParam.DmaWbParam.Ch1DmaYUVMap           = 0;
    OpenParam.DmaWbParam.Ch1WbErrDetectEn       = 0;         
    OpenParam.DmaWbParam.Ch1ErrUnit             = 1;
    OpenParam.DmaWbParam.Ch1ErrTh               = 1;
    
    OpenParam.DmaWbParam.Ch2OtNum               = 1;
    OpenParam.DmaWbParam.Ch2BlenMode            = 0;
    OpenParam.DmaWbParam.Ch2ContinuousMode      = 1;
    OpenParam.DmaWbParam.Ch2DmaYUVMap           = 0;
    OpenParam.DmaWbParam.Ch2WbErrDetectEn       = 0;    
    OpenParam.DmaWbParam.Ch2ErrUnit             = 1;
    OpenParam.DmaWbParam.Ch2ErrTh               = 1;
    //END
    m_TdMixerOutHandle = MS_API_TD_MixerOpen(&OpenParam,&ErrCode);
  

    MS_API_TD_MixerFrameStart();
    TD_PrintRotRegValue();
    TD_MixerPrintRegValue();

   
    msleep(2000);
  
    printf("TD_MixerTestVideoMainYUV_Alpha Display Config done!...............................\n\n\n\n");
}


void TD_MixerTestVideoMainYUV_Backgroud(MS_U32 ImgInDataMode)
{
    MD_TD_MixerParamaterT OpenParam;
    MS_U32 ErrCode = MS_OK;

    MS_API_TD_WrapInit();
   
    MS_API_TD_MixerInit();

    memset(&OpenParam,0,sizeof(MD_TD_MixerParamaterT));
    
    //cfg video layer0
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerEnable          = 1;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StartX = 198;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StartY = 42;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StopX  = 198 + 320;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StopY  = 42 + 352;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInDataMode        = ImgInDataMode;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].EndianModeY          = TD_VIDEO_LAYER_Y_ENDIAN_MODE1;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].EndianModeUV         = TD_VIDEO_LAYER_UV_ENDIAN_MODE2;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelHszie      = 320;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelVszie      = 352;
    
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgOutPixelHszie     = 320;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgOutPixelVszie     = 352;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelStrideH    = 320;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelStrideV    = 0;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelOffsetH    = 0;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelOffsetV    = 0;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].GlobalAlpha          = 0xff;
    
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ReadAddress0Y        =  0x23000000;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ReadAddress0UV       =  0x2301b800;

    OpenParam.LayerMixerOrder                                       = OpenParam.LayerMixerOrder|(0 << 0 );

  


    //cfg OSD layer4
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].OsdEnable                = 0;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].OsdType                  = TD_RGB_24BIT;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].AlphaTpye                = TD_FIXED_VALUE;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].OsdPixelHszie            = 128;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].OsdPixelVszie            = 128;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].LayerPosition.StartX     = 198;   
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].LayerPosition.StartY     = 42;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].LayerPosition.StopX      = 198 + 128;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].LayerPosition.StopY      = 42 + 128;

    OpenParam.OSDLayerParam[TD_OSD_LAYER0].RequestBLen              = 0xf;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].DmaMap                   = TD_ORIGINAL_ORDER;//original
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].RevRGB                   = 1;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].DataInStride             = 128;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].AlphaInStride            = 128;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].RGB2YUVEnable            = 1;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].GlobalAlpha              = 0xff;

    OpenParam.OSDLayerParam[TD_OSD_LAYER0].ReadAddress0Value        = OSD0_VLU_ADDR0;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].ReadAddress0Alp          = OSD0_ALP_ADDR0;

    OpenParam.LayerMixerOrder                                       = OpenParam.LayerMixerOrder|(1 << 16);

    OpenParam.WindowZone.StartX                                     =  198;
    OpenParam.WindowZone.StopX                                      =  198 + 640;
    OpenParam.WindowZone.StartY                                     =  42;
    OpenParam.WindowZone.StopY                                      =  42 + 480;


    OpenParam.BackGroundComp = 0x00ffffff;
    OpenParam.DisplayYUV2RGBEn = 1;

    //DMA OUT
    OpenParam.DmaWriteBackEn = 1;
    OpenParam.DmaWbParam.InputMode              = 1; //0：bt656  1:BT1120     
    
    OpenParam.DmaWbParam.DataFormat             = 1;     //RGB/RAW  1:YUV  
    OpenParam.DmaWbParam.DmaInputFormat         = 0;     //1`b0:YUV422;1`b1:YUV420    

    OpenParam.DmaWbParam.OutputMode             = 1 ;
    OpenParam.DmaWbParam.DmaInput422PixelOrder  = 0;
    OpenParam.DmaWbParam.RawPixelWidth          = 0;
    
    OpenParam.DmaWbParam.WriteBaseAddressY0     = MAIN_ROTATION_Y_ADDR;
    OpenParam.DmaWbParam.WriteBaseAddressY1     = MAIN_ROTATION_Y_ADDR;
    OpenParam.DmaWbParam.WriteBaseAddressUV0    = MAIN_ROTATION_U_ADDR;
    OpenParam.DmaWbParam.WriteBaseAddressUV1    = MAIN_ROTATION_U_ADDR;
    
    OpenParam.DmaWbParam.DataLineYStride        = 640;
    OpenParam.DmaWbParam.DataLineUVStride       = 640;       
    
    OpenParam.DmaWbParam.ActiveHszie            = 640;
    OpenParam.DmaWbParam.ActiveVszie            = 480;

    OpenParam.DmaWbParam.DramLoopSzie           = 0xFFFF;
    
    OpenParam.DmaWbParam.Ch1OtNum               = 1; 
    OpenParam.DmaWbParam.Ch1BlenMode            = 0; 
    OpenParam.DmaWbParam.Ch1ContinuousMode      = 1;   
    OpenParam.DmaWbParam.Ch1DmaYUVMap           = 0;
    OpenParam.DmaWbParam.Ch1WbErrDetectEn       = 0;         
    OpenParam.DmaWbParam.Ch1ErrUnit             = 1;
    OpenParam.DmaWbParam.Ch1ErrTh               = 1;
    
    OpenParam.DmaWbParam.Ch2OtNum               = 1;
    OpenParam.DmaWbParam.Ch2BlenMode            = 0;
    OpenParam.DmaWbParam.Ch2ContinuousMode      = 1;
    OpenParam.DmaWbParam.Ch2DmaYUVMap           = 0;
    OpenParam.DmaWbParam.Ch2WbErrDetectEn       = 0;    
    OpenParam.DmaWbParam.Ch2ErrUnit             = 1;
    OpenParam.DmaWbParam.Ch2ErrTh               = 1;
    //END
    m_TdMixerOutHandle = MS_API_TD_MixerOpen(&OpenParam,&ErrCode);
  

    MS_API_TD_MixerFrameStart();
    TD_PrintRotRegValue();
    TD_MixerPrintRegValue();

   
    msleep(2000);
  
    printf("TD_MixerTestVideoMainYUV_Backgroud Display Config done!...............................\n\n\n\n");
}



MS_U32 StartNum = 0;
extern uint64_t g_start_cycle;

void TD_MixerTestVideoMainYUV_1080to320240(MS_U32 ImgInDataMode,MS_U32 InputW,MS_U32 InputH,MS_U32 downscaleW,MS_U32 downscaleH)
{
    MD_TD_MixerParamaterT OpenParam;
    MS_U32 ErrCode = MS_OK;
  
    MS_U32 reg = 0;

    MS_API_TD_WrapInit();
   
    MS_API_TD_MixerInit();

    memset(&OpenParam,0,sizeof(MD_TD_MixerParamaterT));
    //memset(TD_MIXER_WB_ADDR_Y0,0x00,0x20000);//des y

    //cfg video layer0
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerEnable          = 1;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StartX = 198;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StartY = 42;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StopX  = 198 + downscaleW;//////////////
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StopY  = 42 + downscaleH;/////////////////////

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInDataMode        = ImgInDataMode;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].EndianModeY          = TD_VIDEO_LAYER_Y_ENDIAN_MODE1;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].EndianModeUV         = TD_VIDEO_LAYER_UV_ENDIAN_MODE3;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelHszie      = InputW;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelVszie      = InputH;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgOutPixelHszie     = downscaleW;///////////////
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgOutPixelVszie     = downscaleH;////////////////////
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelStrideH    = 1920;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelStrideV    = 0;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelOffsetH    = 0;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelOffsetV    = 0;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].GlobalAlpha          = 0xff;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ReadAddress0Y        =  0x01000000;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ReadAddress0UV       =  0x011FA400;
    OpenParam.LayerMixerOrder                                       = OpenParam.LayerMixerOrder|(0 << 0 );
    OpenParam.WindowZone.StartX                                     = OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StartX;
    OpenParam.WindowZone.StopX                                      = OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StopX ;
    OpenParam.WindowZone.StartY                                     = OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StartY;
    OpenParam.WindowZone.StopY                                      = OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StopY;


    OpenParam.BackGroundComp = 0x00ffffff;
    OpenParam.DisplayYUV2RGBEn = 1;

    //DMA OUT
    OpenParam.DmaWriteBackEn = 1;
    OpenParam.DmaWbParam.InputMode              = 1; //0：bt656  1:BT1120     
    
    OpenParam.DmaWbParam.DataFormat             = 1;     //RGB/RAW  1:YUV  
    OpenParam.DmaWbParam.DmaInputFormat         = 0;     //1`b0:YUV422;1`b1:YUV420    

    OpenParam.DmaWbParam.OutputMode             = 1 ;
    OpenParam.DmaWbParam.DmaInput422PixelOrder  = 0;
    OpenParam.DmaWbParam.RawPixelWidth          = 0;
    
    OpenParam.DmaWbParam.WriteBaseAddressY0     = MAIN_ROTATION_Y_ADDR;
    OpenParam.DmaWbParam.WriteBaseAddressY1     = MAIN_ROTATION_Y_ADDR;
    OpenParam.DmaWbParam.WriteBaseAddressUV0    = MAIN_ROTATION_Y_ADDR + downscaleW * downscaleH;
    OpenParam.DmaWbParam.WriteBaseAddressUV1    = MAIN_ROTATION_Y_ADDR + downscaleW * downscaleH;
    
    OpenParam.DmaWbParam.DataLineYStride        = ((downscaleW + 7)>>3) << 3;
    OpenParam.DmaWbParam.DataLineUVStride       =  ((downscaleW + 7)>>3) << 3;       
    
    OpenParam.DmaWbParam.ActiveHszie            = downscaleW;
    OpenParam.DmaWbParam.ActiveVszie            = downscaleH;////////////

    OpenParam.DmaWbParam.DramLoopSzie           = 0xFFFF;
    
    OpenParam.DmaWbParam.Ch1OtNum               = 1; 
    OpenParam.DmaWbParam.Ch1BlenMode            = 0; 
    OpenParam.DmaWbParam.Ch1ContinuousMode      = 1;   
    OpenParam.DmaWbParam.Ch1DmaYUVMap           =  1;
    OpenParam.DmaWbParam.Ch1WbErrDetectEn       = 0;         
    OpenParam.DmaWbParam.Ch1ErrUnit             = 1;
    OpenParam.DmaWbParam.Ch1ErrTh               = 1;
    
    OpenParam.DmaWbParam.Ch2OtNum               = 1;
    OpenParam.DmaWbParam.Ch2BlenMode            = 0;
    OpenParam.DmaWbParam.Ch2ContinuousMode      = 1;
    OpenParam.DmaWbParam.Ch2DmaYUVMap           = 1;
    OpenParam.DmaWbParam.Ch2WbErrDetectEn       = 0;    
    OpenParam.DmaWbParam.Ch2ErrUnit             = 1;
    OpenParam.DmaWbParam.Ch2ErrTh               = 1;
    reg = *(volatile MS_U32 *)(TD_BASE_ADDR + 0x7c);         
    *(volatile MS_U32 *)(TD_BASE_ADDR + 0x7c) = reg&~(1 << 18);
    //END
    m_TdMixerOutHandle = MS_API_TD_MixerOpen(&OpenParam,&ErrCode);

    printf("TD_MixerTestVideoMainYUV StartNum = %d\n",StartNum);
    StartNum++;
    MS_API_TD_MixerFrameStart();
    g_start_cycle = read_cycle();
    printf("scaler start cycle %llu\n", g_start_cycle);
    msleep(2000);
    while(0)
    {
        if(MH_TD_get_WrapInt_MixerDone() == 1)
        {
            printf(" MH_TD_get_WrapInt_MixerDone TD_intr int  val = 0x%x,\n",(*(volatile MS_U32 *)(TD_BASE_ADDR + 0x7c)));
            MH_TD_set_WrapInt_MixerDone(1);
            printf("MH_TD_set_WrapInt_MixerDone\n");
        
            break;
        }
        else
        {
            printf(" MH_TD_get_Wrap = 0x%x,\n",(*(volatile MS_U32 *)(TD_BASE_ADDR + 0x7c)));

            printf("Don't done\n");
            msleep(10);
        }

    }
    //TD_PrintRotRegValue();
    //TD_MixerPrintRegValue();

}

#if 0
void TD_MixerTestVideoMainYUV_1080to320240(MS_U32 ImgInDataMode,MS_U32 downscaleW,MS_U32 downscaleH)
{
    MD_TD_MixerParamaterT OpenParam;
    MS_U32 ErrCode = MS_OK;

    MS_API_TD_WrapInit();
   
    MS_API_TD_MixerInit();

    memset(&OpenParam,0,sizeof(MD_TD_MixerParamaterT));
    //memset(TD_MIXER_WB_ADDR_Y0,0x00,0x20000);//des y

    //cfg video layer0
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerEnable          = 1;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StartX = 198;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StartY = 42;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StopX  = 198 + downscaleW;//////////////
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StopY  = 42 + downscaleH;/////////////////////

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInDataMode        = ImgInDataMode;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].EndianModeY          = TD_VIDEO_LAYER_Y_ENDIAN_MODE1;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].EndianModeUV         = TD_VIDEO_LAYER_UV_ENDIAN_MODE2;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelHszie      = 1920;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelVszie      = 1080;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgOutPixelHszie     = downscaleW;///////////////
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgOutPixelVszie     = downscaleH;////////////////////
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelStrideH    = 1920;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelStrideV    = 0;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelOffsetH    = 0;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelOffsetV    = 0;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].GlobalAlpha          = 0xff;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ReadAddress0Y        =  0x24000000;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ReadAddress0UV       =  0x241FA400;
    OpenParam.LayerMixerOrder                                       = OpenParam.LayerMixerOrder|(0 << 0 );
    OpenParam.WindowZone.StartX                                     = OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StartX;
    OpenParam.WindowZone.StopX                                      = OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StopX ;
    OpenParam.WindowZone.StartY                                     = OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StartY;
    OpenParam.WindowZone.StopY                                      = OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StopY;


    OpenParam.BackGroundComp = 0x00ffffff;
    OpenParam.DisplayYUV2RGBEn = 1;

    //DMA OUT
    OpenParam.DmaWriteBackEn = 1;
    OpenParam.DmaWbParam.InputMode              = 1; //0：bt656  1:BT1120     
    
    OpenParam.DmaWbParam.DataFormat             = 1;     //RGB/RAW  1:YUV  
    OpenParam.DmaWbParam.DmaInputFormat         = 0;     //1`b0:YUV422;1`b1:YUV420    

    OpenParam.DmaWbParam.OutputMode             = 1 ;
    OpenParam.DmaWbParam.DmaInput422PixelOrder  = 0;
    OpenParam.DmaWbParam.RawPixelWidth          = 0;
    
    OpenParam.DmaWbParam.WriteBaseAddressY0     = MAIN_ROTATION_Y_ADDR;
    OpenParam.DmaWbParam.WriteBaseAddressY1     = MAIN_ROTATION_Y_ADDR;
    OpenParam.DmaWbParam.WriteBaseAddressUV0    = MAIN_ROTATION_U_ADDR;
    OpenParam.DmaWbParam.WriteBaseAddressUV1    = MAIN_ROTATION_U_ADDR;
    
    OpenParam.DmaWbParam.DataLineYStride        = ((downscaleW + 7)>>3) << 3;
    OpenParam.DmaWbParam.DataLineUVStride       =  ((downscaleW + 7)>>3) << 3;       
    
    OpenParam.DmaWbParam.ActiveHszie            = downscaleW;
    OpenParam.DmaWbParam.ActiveVszie            = downscaleH;////////////

    OpenParam.DmaWbParam.DramLoopSzie           = 0xFFFF;
    
    OpenParam.DmaWbParam.Ch1OtNum               = 1; 
    OpenParam.DmaWbParam.Ch1BlenMode            = 0; 
    OpenParam.DmaWbParam.Ch1ContinuousMode      = 1;   
    OpenParam.DmaWbParam.Ch1DmaYUVMap           = 1;
    OpenParam.DmaWbParam.Ch1WbErrDetectEn       = 0;         
    OpenParam.DmaWbParam.Ch1ErrUnit             = 1;
    OpenParam.DmaWbParam.Ch1ErrTh               = 1;
    
    OpenParam.DmaWbParam.Ch2OtNum               = 1;
    OpenParam.DmaWbParam.Ch2BlenMode            = 0;
    OpenParam.DmaWbParam.Ch2ContinuousMode      = 1;
    OpenParam.DmaWbParam.Ch2DmaYUVMap           = 1;
    OpenParam.DmaWbParam.Ch2WbErrDetectEn       = 0;    
    OpenParam.DmaWbParam.Ch2ErrUnit             = 1;
    OpenParam.DmaWbParam.Ch2ErrTh               = 1;
    //END

    MS_U32 reg = *(volatile MS_U32 *)(TD_BASE_ADDR + 0x7c);         
    *(volatile MS_U32 *)(TD_BASE_ADDR + 0x7c) = reg&~(7 << 16);
    
    m_TdMixerOutHandle = MS_API_TD_MixerOpen(&OpenParam,&ErrCode);
    MS_API_TD_MixerFrameStart();    
    msleep(300);
    //TD_PrintRotRegValue();
    //TD_MixerPrintRegValue();
    printf("TD_MixerTestVideoMainYUV_1080to320240 Display Config done!...............................\n");
    printf("int reg status 0x%x\n", *(volatile MS_U32 *)(TD_BASE_ADDR + 0x7c));
}

#endif


void TD_MixerTestVideoMainYUV_320to176144(MS_U32 ImgInDataMode)
{
    MD_TD_MixerParamaterT OpenParam;
    MS_U32 ErrCode = MS_OK;

    MS_API_TD_WrapInit();
   
    MS_API_TD_MixerInit();

    memset(&OpenParam,0,sizeof(MD_TD_MixerParamaterT));
    //memset(TD_MIXER_WB_ADDR_Y0,0x00,0x20000);//des y

    //cfg video layer0
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerEnable          = 1;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StartX = 198;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StartY = 42;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StopX  = 198 + 176;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StopY  = 42 + 144;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInDataMode        = ImgInDataMode;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].EndianModeY          = TD_VIDEO_LAYER_Y_ENDIAN_MODE1;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].EndianModeUV         = TD_VIDEO_LAYER_UV_ENDIAN_MODE2;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelHszie      = 320;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelVszie      = 352;
    
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgOutPixelHszie     = 176;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgOutPixelVszie     = 144;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelStrideH    = 320;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelStrideV    = 0;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelOffsetH    = 0;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelOffsetV    = 0;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].GlobalAlpha          = 0xff;
    
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ReadAddress0Y        =  0x23000000;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ReadAddress0UV       =  0x2301b800;

    OpenParam.LayerMixerOrder                                       = OpenParam.LayerMixerOrder|(0 << 0 );

  


    //cfg OSD layer4
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].OsdEnable                = 0;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].OsdType                  = TD_RGB_24BIT;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].AlphaTpye                = TD_FIXED_VALUE;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].OsdPixelHszie            = 128;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].OsdPixelVszie            = 128;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].LayerPosition.StartX     = 198;   
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].LayerPosition.StartY     = 42;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].LayerPosition.StopX      = 198 + 128;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].LayerPosition.StopY      = 42 + 128;

    OpenParam.OSDLayerParam[TD_OSD_LAYER0].RequestBLen              = 0xf;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].DmaMap                   = TD_ORIGINAL_ORDER;//original
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].RevRGB                   = 1;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].DataInStride             = 128;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].AlphaInStride            = 128;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].RGB2YUVEnable            = 1;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].GlobalAlpha              = 0xff;

    OpenParam.OSDLayerParam[TD_OSD_LAYER0].ReadAddress0Value        = OSD0_VLU_ADDR0;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].ReadAddress0Alp          = OSD0_ALP_ADDR0;

    OpenParam.LayerMixerOrder                                       = OpenParam.LayerMixerOrder|(1 << 16);

    OpenParam.WindowZone.StartX                                     =   OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StartX;
    OpenParam.WindowZone.StopX                                      =  OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StopX ;
    OpenParam.WindowZone.StartY                                     = OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StartY;
    OpenParam.WindowZone.StopY                                      = OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StopY;


    OpenParam.BackGroundComp = 0x00ffffff;
    OpenParam.DisplayYUV2RGBEn = 1;

    //DMA OUT
    OpenParam.DmaWriteBackEn = 1;
    OpenParam.DmaWbParam.InputMode              = 1; //0：bt656  1:BT1120     
    
    OpenParam.DmaWbParam.DataFormat             = 1;     //RGB/RAW  1:YUV  
    OpenParam.DmaWbParam.DmaInputFormat         = 0;     //1`b0:YUV422;1`b1:YUV420    

    OpenParam.DmaWbParam.OutputMode             = 1 ;
    OpenParam.DmaWbParam.DmaInput422PixelOrder  = 0;
    OpenParam.DmaWbParam.RawPixelWidth          = 0;
    
    OpenParam.DmaWbParam.WriteBaseAddressY0     = MAIN_ROTATION_Y_ADDR;
    OpenParam.DmaWbParam.WriteBaseAddressY1     = MAIN_ROTATION_Y_ADDR;
    OpenParam.DmaWbParam.WriteBaseAddressUV0    = MAIN_ROTATION_U_ADDR;
    OpenParam.DmaWbParam.WriteBaseAddressUV1    = MAIN_ROTATION_U_ADDR;
    
    OpenParam.DmaWbParam.DataLineYStride        = 176;
    OpenParam.DmaWbParam.DataLineUVStride       = 176;       
    
    OpenParam.DmaWbParam.ActiveHszie            = 176;
    OpenParam.DmaWbParam.ActiveVszie            = 144;

    OpenParam.DmaWbParam.DramLoopSzie           = 0xFFFF;
    
    OpenParam.DmaWbParam.Ch1OtNum               = 1; 
    OpenParam.DmaWbParam.Ch1BlenMode            = 0; 
    OpenParam.DmaWbParam.Ch1ContinuousMode      = 1;   
    OpenParam.DmaWbParam.Ch1DmaYUVMap           = 1;
    OpenParam.DmaWbParam.Ch1WbErrDetectEn       = 0;         
    OpenParam.DmaWbParam.Ch1ErrUnit             = 1;
    OpenParam.DmaWbParam.Ch1ErrTh               = 1;
    
    OpenParam.DmaWbParam.Ch2OtNum               = 1;
    OpenParam.DmaWbParam.Ch2BlenMode            = 0;
    OpenParam.DmaWbParam.Ch2ContinuousMode      = 1;
    OpenParam.DmaWbParam.Ch2DmaYUVMap           = 1;
    OpenParam.DmaWbParam.Ch2WbErrDetectEn       = 0;    
    OpenParam.DmaWbParam.Ch2ErrUnit             = 1;
    OpenParam.DmaWbParam.Ch2ErrTh               = 1;
    //END
    m_TdMixerOutHandle = MS_API_TD_MixerOpen(&OpenParam,&ErrCode);
  

    MS_API_TD_MixerFrameStart();    
    TD_MixerPrintRegValue();



    //cfg video layer0
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerEnable          = 1;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StartX = 198;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StartY = 42;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StopX  = 198 + 320;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StopY  = 42 + 352;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInDataMode        = ImgInDataMode;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].EndianModeY          = TD_VIDEO_LAYER_Y_ENDIAN_MODE1;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].EndianModeUV         = TD_VIDEO_LAYER_UV_ENDIAN_MODE3;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelHszie      = 320;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelVszie      = 352;
    
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgOutPixelHszie     = 320;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgOutPixelVszie     = 352;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelStrideH    = 320;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelStrideV    = 0;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelOffsetH    = 0;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelOffsetV    = 0;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].GlobalAlpha          = 0xff;
    
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ReadAddress0Y        =  0x23000000;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ReadAddress0UV       =  0x2301b800;
    OpenParam.WindowZone.StartX                                     =   OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StartX;
    OpenParam.WindowZone.StopX                                      =  OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StopX ;
    OpenParam.WindowZone.StartY                                     = OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StartY;
    OpenParam.WindowZone.StopY                                      = OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StopY;

    OpenParam.LayerMixerOrder                                       = OpenParam.LayerMixerOrder|(0 << 0 );
    OpenParam.DmaWriteBackEn = 1;
    OpenParam.DmaWbParam.InputMode              = 1; //0：bt656  1:BT1120     
    
    OpenParam.DmaWbParam.DataFormat             = 1;     //RGB/RAW  1:YUV  
    OpenParam.DmaWbParam.DmaInputFormat         = 0;     //1`b0:YUV422;1`b1:YUV420    

    OpenParam.DmaWbParam.OutputMode             = 1 ;
    OpenParam.DmaWbParam.DmaInput422PixelOrder  = 0;
    OpenParam.DmaWbParam.RawPixelWidth          = 0;
    
    OpenParam.DmaWbParam.WriteBaseAddressY0     = MAIN_ROTATION_Y_ADDR_A;
    OpenParam.DmaWbParam.WriteBaseAddressY1     = MAIN_ROTATION_Y_ADDR_A;
    OpenParam.DmaWbParam.WriteBaseAddressUV0    = MAIN_ROTATION_U_ADDR_A;
    OpenParam.DmaWbParam.WriteBaseAddressUV1    = MAIN_ROTATION_U_ADDR_A;
    
    OpenParam.DmaWbParam.DataLineYStride        = 320;
    OpenParam.DmaWbParam.DataLineUVStride       = 320;       
    
    OpenParam.DmaWbParam.ActiveHszie            = 320;
    OpenParam.DmaWbParam.ActiveVszie            = 352;

    OpenParam.DmaWbParam.DramLoopSzie           = 0xFFFF;
    
    OpenParam.DmaWbParam.Ch1OtNum               = 1; 
    OpenParam.DmaWbParam.Ch1BlenMode            = 0; 
    OpenParam.DmaWbParam.Ch1ContinuousMode      = 1;   
    OpenParam.DmaWbParam.Ch1DmaYUVMap           = 1;
    OpenParam.DmaWbParam.Ch1WbErrDetectEn       = 0;         
    OpenParam.DmaWbParam.Ch1ErrUnit             = 1;
    OpenParam.DmaWbParam.Ch1ErrTh               = 1;
    
    OpenParam.DmaWbParam.Ch2OtNum               = 1;
    OpenParam.DmaWbParam.Ch2BlenMode            = 0;
    OpenParam.DmaWbParam.Ch2ContinuousMode      = 1;
    OpenParam.DmaWbParam.Ch2DmaYUVMap           = 1;
    OpenParam.DmaWbParam.Ch2WbErrDetectEn       = 0;    
    OpenParam.DmaWbParam.Ch2ErrUnit             = 1;
    OpenParam.DmaWbParam.Ch2ErrTh               = 1;


    m_TdMixerOutHandle = MS_API_TD_MixerOpen(&OpenParam,&ErrCode);
  

    MS_API_TD_MixerFrameStart();    

    
    msleep(1000);
  
    printf("TD_MixerTestVideoMainYUV_320to176144 Display Config done!...............................\n\n\n\n");
}


void TD_MixerTestVideoMainYUV_320to640480(MS_U32 ImgInDataMode)
{
    MD_TD_MixerParamaterT OpenParam;
    MS_U32 ErrCode = MS_OK;

    MS_API_TD_WrapInit();
   
    MS_API_TD_MixerInit();

    memset(&OpenParam,0,sizeof(MD_TD_MixerParamaterT));
    //memset(TD_MIXER_WB_ADDR_Y0,0x00,0x20000);//des y

    //cfg video layer0
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerEnable          = 1;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StartX = 198;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StartY = 42;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StopX  = 198 + 640;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StopY  = 42 + 480;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInDataMode        = ImgInDataMode;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].EndianModeY          = TD_VIDEO_LAYER_Y_ENDIAN_MODE1;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].EndianModeUV         = TD_VIDEO_LAYER_UV_ENDIAN_MODE2;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelHszie      = 320;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelVszie      = 352;
    
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgOutPixelHszie     = 640;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgOutPixelVszie     = 480;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelStrideH    = 320;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelStrideV    = 0;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelOffsetH    = 0;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelOffsetV    = 0;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].GlobalAlpha          = 0xff;
    
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ReadAddress0Y        =  0x23000000;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ReadAddress0UV       =  0x2301b800;

    OpenParam.LayerMixerOrder                                       = OpenParam.LayerMixerOrder|(0 << 0 );

  


    //cfg OSD layer4
  //cfg OSD layer4
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].OsdEnable                = 1;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].OsdType                  = TD_RGB_32BIT;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].AlphaTpye                = TD_L2_ALPHA_ADDR;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].OsdPixelHszie            = 320;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].OsdPixelVszie            = 240;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].LayerPosition.StartX     = 262;   
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].LayerPosition.StartY     = 106;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].LayerPosition.StopX      = 262 + 320;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].LayerPosition.StopY      = 106 + 240;

    OpenParam.OSDLayerParam[TD_OSD_LAYER0].RequestBLen              = 0xf;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].DmaMap                   = TD_ORIGINAL_ORDER;//original
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].RevRGB                   = 1;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].DataInStride             = 1280;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].AlphaInStride            = 320;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].RGB2YUVEnable            = 1;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].GlobalAlpha              = 0xff;

    OpenParam.OSDLayerParam[TD_OSD_LAYER0].ReadAddress0Value        = OSD0_VLU_ADDR0;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].ReadAddress0Alp          = OSD0_ALP_ADDR0;

    OpenParam.LayerMixerOrder                                       = OpenParam.LayerMixerOrder|(1 << 16);

    
    OpenParam.WindowZone.StartX                                     =   OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StartX;
    OpenParam.WindowZone.StopX                                      =  OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StopX ;
    OpenParam.WindowZone.StartY                                     = OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StartY;
    OpenParam.WindowZone.StopY                                      = OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StopY;





    OpenParam.BackGroundComp = 0x00ffffff;
    OpenParam.DisplayYUV2RGBEn = 1;

    //DMA OUT
    OpenParam.DmaWriteBackEn = 1;
    OpenParam.DmaWbParam.InputMode              = 1; //0：bt656  1:BT1120     
    
    OpenParam.DmaWbParam.DataFormat             = 1;     //RGB/RAW  1:YUV  
    OpenParam.DmaWbParam.DmaInputFormat         = 0;     //1`b0:YUV422;1`b1:YUV420    

    OpenParam.DmaWbParam.OutputMode             = 1 ;
    OpenParam.DmaWbParam.DmaInput422PixelOrder  = 0;
    OpenParam.DmaWbParam.RawPixelWidth          = 0;
    
    OpenParam.DmaWbParam.WriteBaseAddressY0     = MAIN_ROTATION_Y_ADDR;
    OpenParam.DmaWbParam.WriteBaseAddressY1     = MAIN_ROTATION_Y_ADDR;
    OpenParam.DmaWbParam.WriteBaseAddressUV0    = MAIN_ROTATION_U_ADDR;
    OpenParam.DmaWbParam.WriteBaseAddressUV1    = MAIN_ROTATION_U_ADDR;
    
    OpenParam.DmaWbParam.DataLineYStride        = 640;
    OpenParam.DmaWbParam.DataLineUVStride       = 640;       
    
    OpenParam.DmaWbParam.ActiveHszie            = 640;
    OpenParam.DmaWbParam.ActiveVszie            = 480;


    
    OpenParam.DmaWbParam.DramLoopSzie           = 0xFFFF;
    
    
    OpenParam.DmaWbParam.Ch1OtNum               = 1; 
    OpenParam.DmaWbParam.Ch1BlenMode            = 0; 
    OpenParam.DmaWbParam.Ch1ContinuousMode      = 1;   
    OpenParam.DmaWbParam.Ch1DmaYUVMap           = 0;
    OpenParam.DmaWbParam.Ch1WbErrDetectEn       = 0;         
    OpenParam.DmaWbParam.Ch1ErrUnit             = 1;
    OpenParam.DmaWbParam.Ch1ErrTh               = 1;
    
    OpenParam.DmaWbParam.Ch2OtNum               = 1;
    OpenParam.DmaWbParam.Ch2BlenMode            = 0;
    OpenParam.DmaWbParam.Ch2ContinuousMode      = 1;
    OpenParam.DmaWbParam.Ch2DmaYUVMap           = 0;
    OpenParam.DmaWbParam.Ch2WbErrDetectEn       = 0;    
    OpenParam.DmaWbParam.Ch2ErrUnit             = 1;
    OpenParam.DmaWbParam.Ch2ErrTh               = 1;
    //END
    m_TdMixerOutHandle = MS_API_TD_MixerOpen(&OpenParam,&ErrCode);
  

    MS_API_TD_MixerFrameStart();
    TD_PrintRotRegValue();
    TD_MixerPrintRegValue();

   
    msleep(2000);
  
    printf("TD_MixerTestVideoMainYUV_320to640480  Config done!...............................\n\n\n\n");
}




void TD_MixerTestVideoMainYUV_MixerMainStream_Rotation(MS_U32 ImgInDataMode)
{
    MD_TD_MixerParamaterT OpenParam;
    MS_U32 ErrCode = MS_OK;
    MD_TD_RotationParmT RotationOpenParam;

    MS_API_TD_WrapInit();
   
    MS_API_TD_MixerInit();

    memset(&OpenParam,0,sizeof(MD_TD_MixerParamaterT));
    //memset(TD_MIXER_WB_ADDR_Y0,0x00,0x20000);//des y

    //cfg video layer0
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerEnable          = 1;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StartX = 198;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StartY = 42;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StopX  = 198 + 640;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StopY  = 42 + 480;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInDataMode        = ImgInDataMode;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].EndianModeY          = TD_VIDEO_LAYER_Y_ENDIAN_MODE1;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].EndianModeUV         = TD_VIDEO_LAYER_UV_ENDIAN_MODE2;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelHszie      = 640;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelVszie      = 480;
    
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgOutPixelHszie     = 640;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgOutPixelVszie     = 480;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelStrideH    = 2048;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelStrideV    = 0;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelOffsetH    = 0;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelOffsetV    = 0;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].GlobalAlpha          = 0xff;
    
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ReadAddress0Y        =  MAIN_Y_ADDR0;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ReadAddress0UV       =  MAIN_UV_ADDR0;

    OpenParam.LayerMixerOrder                                       = OpenParam.LayerMixerOrder|(0 << 0 );


    //cfg OSD layer4
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].OsdEnable                = 1;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].OsdType                  = TD_RGB_32BIT;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].AlphaTpye                = TD_L2_ALPHA_ADDR;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].OsdPixelHszie            = 320;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].OsdPixelVszie            = 240;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].LayerPosition.StartX     = 262;   
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].LayerPosition.StartY     = 106;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].LayerPosition.StopX      = 262 + 320;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].LayerPosition.StopY      = 106 + 240;

    OpenParam.OSDLayerParam[TD_OSD_LAYER0].RequestBLen              = 0xf;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].DmaMap                   = TD_ORIGINAL_ORDER;//original
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].RevRGB                   = 1;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].DataInStride             = 1280;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].AlphaInStride            = 320;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].RGB2YUVEnable            = 1;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].GlobalAlpha              = 0xff;

    OpenParam.OSDLayerParam[TD_OSD_LAYER0].ReadAddress0Value        = OSD0_VLU_ADDR0;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].ReadAddress0Alp          = OSD0_ALP_ADDR0;

    OpenParam.LayerMixerOrder                                       = OpenParam.LayerMixerOrder|(1 << 16);

    OpenParam.WindowZone.StartX                                     =  198;
    OpenParam.WindowZone.StopX                                      =  198 + 640;
    OpenParam.WindowZone.StartY                                     =  42;
    OpenParam.WindowZone.StopY                                      =  42 + 480;




    OpenParam.BackGroundComp = 0x00ffffff;
    OpenParam.DisplayYUV2RGBEn = 1;

    //DMA OUT
    OpenParam.DmaWriteBackEn = 1;
    OpenParam.DmaWbParam.InputMode              = 1; //0：bt656  1:BT1120     
    
    OpenParam.DmaWbParam.DataFormat             = 1;     //RGB/RAW  1:YUV  
    OpenParam.DmaWbParam.DmaInputFormat         = 0;     //1`b0:YUV422;1`b1:YUV420    

    OpenParam.DmaWbParam.OutputMode             = 1 ;
    OpenParam.DmaWbParam.DmaInput422PixelOrder  = 0;
    OpenParam.DmaWbParam.RawPixelWidth          = 0;
    
    OpenParam.DmaWbParam.WriteBaseAddressY0     = MAIN_ROTATION_Y_ADDR;
    OpenParam.DmaWbParam.WriteBaseAddressY1     = MAIN_ROTATION_Y_ADDR;
    OpenParam.DmaWbParam.WriteBaseAddressUV0    = MAIN_ROTATION_U_ADDR;
    OpenParam.DmaWbParam.WriteBaseAddressUV1    = MAIN_ROTATION_U_ADDR;
    
    OpenParam.DmaWbParam.DataLineYStride        = 640;
    OpenParam.DmaWbParam.DataLineUVStride       = 640;       
    
    OpenParam.DmaWbParam.ActiveHszie            = 640;
    OpenParam.DmaWbParam.ActiveVszie            = 480;


    
    OpenParam.DmaWbParam.DramLoopSzie           = 0xFFFF;
    
    
    OpenParam.DmaWbParam.Ch1OtNum               = 1; 
    OpenParam.DmaWbParam.Ch1BlenMode            = 0; 
    OpenParam.DmaWbParam.Ch1ContinuousMode      = 1;   
    OpenParam.DmaWbParam.Ch1DmaYUVMap           = 0;
    OpenParam.DmaWbParam.Ch1WbErrDetectEn       = 0;         
    OpenParam.DmaWbParam.Ch1ErrUnit             = 1;
    OpenParam.DmaWbParam.Ch1ErrTh               = 1;
    
    OpenParam.DmaWbParam.Ch2OtNum               = 1;
    OpenParam.DmaWbParam.Ch2BlenMode            = 0;
    OpenParam.DmaWbParam.Ch2ContinuousMode      = 1;
    OpenParam.DmaWbParam.Ch2DmaYUVMap           = 0;
    OpenParam.DmaWbParam.Ch2WbErrDetectEn       = 0;    
    OpenParam.DmaWbParam.Ch2ErrUnit             = 1;
    OpenParam.DmaWbParam.Ch2ErrTh               = 1;
    //END
    m_TdMixerOutHandle = MS_API_TD_MixerOpen(&OpenParam,&ErrCode);
  

    MS_API_TD_MixerFrameStart();
    msleep(2000);


    //////////////////////////////////////

    memset(&RotationOpenParam,0,sizeof(MD_TD_RotationParmT));

    //cfg video layer0
    RotationOpenParam.RotationMode         = TD_ROTATION_90_DEGREE;
    RotationOpenParam.RotationPixelFormat  = TD_ROTATION_PIX_FORMAT_420SP;

    RotationOpenParam.InSwapEn             = 1;
    RotationOpenParam.BigLittleInEndia     = 1;
    RotationOpenParam.OutSwapEn            = 1;
    RotationOpenParam.BigLittleOutEndia    = 1;
    RotationOpenParam.OtMaxRD              = 1;
    RotationOpenParam.OtMaxWR              = 1;

    RotationOpenParam.DoneTimeOut          = 0xffff;

    RotationOpenParam.ActiveHor          = 640;
    RotationOpenParam.ActiveVer          = 480; 

    RotationOpenParam.StrideSrcY          = 2048; 
    RotationOpenParam.StrideDesY          = 2048;

    RotationOpenParam.StrideSrcU          = 2048; 
    RotationOpenParam.StrideDesU          = 2048;

    RotationOpenParam.StrideSrcV          = 0; 
    RotationOpenParam.StrideDesV          = 0;

    RotationOpenParam.BaseAddrSrcY = MAIN_ROTATION_Y_ADDR + (RotationOpenParam.ActiveVer -1)*RotationOpenParam.StrideSrcY;
    RotationOpenParam.BaseAddrSrcU = MAIN_ROTATION_U_ADDR + (RotationOpenParam.ActiveVer/2 -1)*RotationOpenParam.StrideSrcU;
    RotationOpenParam.BaseAddrSrcV = 0;

    RotationOpenParam.BaseAddrDesY = MAIN_ROTATION_Y_ADDR_A;
    RotationOpenParam.BaseAddrDesU = MAIN_ROTATION_U_ADDR_A;
    RotationOpenParam.BaseAddrDesV = 0;


    m_TdRotationOutHandle = MS_API_TD_RotationOpen(&RotationOpenParam,&ErrCode);


    MS_API_TD_RotationFrameStart();
    TD_PrintRotRegValue();
    msleep(2000);

    printf("TD_TestRotation90DegreeMainYuv420 ErrCode = %d!\n",ErrCode);

  
    printf("TD_MixerTestVideoMainYUV_MixerMainStream_Rotation Config done!.ErrCode = %d..............................\n\n\n\n",ErrCode);
}







void TestTDMixer(MS_U8 testCase)
{

    MS_U8 TestCase = TD_CASE_UNDEFINE;
    
    TestCase =TD_MIXER_MAINYUV_1080to320240 ;
    switch( TestCase )
    {

    
        case TD_MIXER_MAIN_RGB:
            TD_MixerTestVideoMainRGB(TD_VIDEO_LAYER_YUV_MODE_420);
            break;
        
        case TD_MIXER_VIDEO_320352_OSD_256200:
            TD_MixerTestVideo320240Osd256200(TD_VIDEO_LAYER_YUV_MODE_420);
            break;
        
        case TD_MIXER_MAINYUV_320to640480://VO_CASE_LAYER_TD_MIXER_TEST
            TD_MixerTestVideoMainYUV_320to640480(TD_VIDEO_LAYER_YUV_MODE_420);
         
            break;
        case TD_MIXER_MAINYUV_320to176144://VO_CASE_LAYER_TD_MIXER_VOUT_COMPARE_TEST
            TD_MixerTestVideoMainYUV_320to176144(TD_VIDEO_LAYER_YUV_MODE_420);
            break;
        

        case TD_MIXER_MAINYUV_1080to320240://VO_CASE_LAYER_TD_MIXER_VOUT_COMPARE_TEST
            {
            //TD_MixerTestVideoMainYUV_1080to320240(TD_VIDEO_LAYER_YUV_MODE_420, 1920, 1080, 352, 288);
            unsigned int downscaleH;
            
             unsigned int InputW;
             unsigned int InputH;
            
     unsigned int downscaleW;
    unsigned int downscaleStride;
        unsigned int step = 0;
             unsigned int OutputCase[][2]=
             {
                 {1280,960},
                 {1280,720},
                 {800,600},
                 {720,576},
                 {720,480},
                 {640,480},
                 {352,288},
                 {320,240},
             };
while(1)
{
            InputW = 1920;
            InputH = 1080;
            
            downscaleW = OutputCase[step][0];
            downscaleH = OutputCase[step][1];
            
            downscaleStride = ((downscaleW + 7)>>3) << 3;
            step++;
            if(step == 8)
            {
                step = 0;
            }   
            printf("new loop, w %d, h %d\n", downscaleW, downscaleH);

            TD_MixerTestVideoMainYUV_1080to320240(TD_VIDEO_LAYER_YUV_MODE_420, InputW,InputH,downscaleW,downscaleH);
}
            }
            break;
        case TD_MIXER_MAINYUV_BACKGROUND:
            TD_MixerTestVideoMainYUV_Backgroud(TD_VIDEO_LAYER_YUV_MODE_420);
            break;
        
        case TD_MIXER_MAINYUV_ALPHA:
            TD_MixerTestVideoMainYUV_Alpha(TD_VIDEO_LAYER_YUV_MODE_420);
            break;
        
        case TD_MIXER_MAINYUV_MIXER:
            TD_MixerTestVideoMainYUV_MixerSelect(TD_VIDEO_LAYER_YUV_MODE_420);
            break;


        case TD_MIXER_MAINYUV_POSITION:
            TD_MixerTestVideoMainYUV_Postion(TD_VIDEO_LAYER_YUV_MODE_420);
            break;
        
        case TD_MIXER_MAINYUV_CROP:
            TD_MixerTestVideoMainYUV_Crop(TD_VIDEO_LAYER_YUV_MODE_420);
            break;

        case TD_MIXER_MAINYUV_JOINT:  ////VO_CASE_LAYER_TD_MIXER_TEST
            TD_MixerTestVideoMainYUV_Joint(TD_VIDEO_LAYER_YUV_MODE_420);
            break;
            case TD_MIXER_MAINYUV_JOINT_DEBUG:  ////VO_CASE_LAYER_TD_MIXER_TEST
            TD_MixerTestVideoMainYUV_Joint_debug(TD_VIDEO_LAYER_YUV_MODE_420);
            break; 
            
        case TD_MIXER_MAINYUV_ROTATION:
            TD_MixerTestVideoMainYUV_MixerMainStream_Rotation(TD_VIDEO_LAYER_YUV_MODE_420);
            break;

            
        default:
            break;
                
    }


}



void temp_test(void)
{
    MD_TD_MixerParamaterT OpenParam;
    MS_U32 ErrCode = MS_OK;
    msleep(3000);

    MS_API_TD_WrapInit();
   
    MS_API_TD_MixerInit();

    memset(&OpenParam,0,sizeof(MD_TD_MixerParamaterT));
    
    //cfg video layer0
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerEnable          = 1;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StartX = 64;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StartY = 64;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StopX  = 64 + 640;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StopY  = 64 + 480;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInDataMode        = TD_VIDEO_LAYER_YUV_MODE_420;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].EndianModeY          = TD_VIDEO_LAYER_Y_ENDIAN_MODE2;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].EndianModeUV         = TD_VIDEO_LAYER_UV_ENDIAN_MODE5;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelHszie      = 640;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelVszie      = 480;
    
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgOutPixelHszie     = 640;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgOutPixelVszie     = 480;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelStrideH    = 640;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelStrideV    = 0;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelOffsetH    = 0;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelOffsetV    = 0;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].GlobalAlpha          = 0xff;
    
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ReadAddress0Y        =  0x26000000;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ReadAddress0UV       =  0x26000000 + 640*480;

    OpenParam.LayerMixerOrder                                       = OpenParam.LayerMixerOrder|(0 << 0 );

    //cfg OSD layer4
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].OsdEnable                = 0;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].OsdType                  = TD_RGB_32BIT;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].AlphaTpye                = TD_FIXED_VALUE;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].OsdPixelHszie            = 320;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].OsdPixelVszie            = 240;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].LayerPosition.StartX     = 192;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].LayerPosition.StartY     = 160;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].LayerPosition.StopX      = 192 + 320;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].LayerPosition.StopY      = 160 + 240;

    OpenParam.OSDLayerParam[TD_OSD_LAYER0].RequestBLen              = 0xf;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].DmaMap                   = TD_ORIGINAL_ORDER;//original
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].RevRGB                   = 1;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].DataInStride             = 1280;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].AlphaInStride            = 320;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].RGB2YUVEnable            = 1;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].GlobalAlpha              = 0xff;

    OpenParam.OSDLayerParam[TD_OSD_LAYER0].ReadAddress0Value        = OSD0_VLU_ADDR0;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].ReadAddress0Alp          = OSD0_ALP_ADDR0;

    OpenParam.LayerMixerOrder                                       = OpenParam.LayerMixerOrder|(1 << 16);

    OpenParam.WindowZone.StartX                                     =  64;
    OpenParam.WindowZone.StopX                                      =  64 + 640;
    OpenParam.WindowZone.StartY                                     =  64;
    OpenParam.WindowZone.StopY                                      =  64 + 480;


    OpenParam.BackGroundComp = 0x00ffffff;
    OpenParam.DisplayYUV2RGBEn = 1;

    //DMA OUT
    OpenParam.DmaWriteBackEn = 1;
    OpenParam.DmaWbParam.InputMode              = 1; //0£ºbt656  1:BT1120     
    
    OpenParam.DmaWbParam.DataFormat             = 1;     //RGB/RAW  1:YUV  
    OpenParam.DmaWbParam.DmaInputFormat         = 1;     //1`b0:YUV422;1`b1:YUV420    

    OpenParam.DmaWbParam.OutputMode             = 1;
    OpenParam.DmaWbParam.DmaInput422PixelOrder  = 0;
    OpenParam.DmaWbParam.RawPixelWidth          = 0;
    
    OpenParam.DmaWbParam.WriteBaseAddressY0     = DUMP_MIXER_DST_ADDR_Y;
    OpenParam.DmaWbParam.WriteBaseAddressY1     = DUMP_MIXER_DST_ADDR_Y;
    OpenParam.DmaWbParam.WriteBaseAddressUV0    = DUMP_MIXER_DST_ADDR_UV;
    OpenParam.DmaWbParam.WriteBaseAddressUV1    = DUMP_MIXER_DST_ADDR_UV;
    
    OpenParam.DmaWbParam.DataLineYStride        = 640;
    OpenParam.DmaWbParam.DataLineUVStride       = 640;       
    
    OpenParam.DmaWbParam.ActiveHszie            = 640;
    OpenParam.DmaWbParam.ActiveVszie            = 480;

    OpenParam.DmaWbParam.DramLoopSzie           = 0xFFFF;
    
    OpenParam.DmaWbParam.Ch1OtNum               = 1; 
    OpenParam.DmaWbParam.Ch1BlenMode            = 0; 
    OpenParam.DmaWbParam.Ch1ContinuousMode      = 1;   
    OpenParam.DmaWbParam.Ch1DmaYUVMap           = 0;
    OpenParam.DmaWbParam.Ch1WbErrDetectEn       = 0;         
    OpenParam.DmaWbParam.Ch1ErrUnit             = 1;
    OpenParam.DmaWbParam.Ch1ErrTh               = 1;
    
    OpenParam.DmaWbParam.Ch2OtNum               = 1;
    OpenParam.DmaWbParam.Ch2BlenMode            = 0;
    OpenParam.DmaWbParam.Ch2ContinuousMode      = 1;
    OpenParam.DmaWbParam.Ch2DmaYUVMap           = 0;
    OpenParam.DmaWbParam.Ch2WbErrDetectEn       = 0;    
    OpenParam.DmaWbParam.Ch2ErrUnit             = 1;
    OpenParam.DmaWbParam.Ch2ErrTh               = 1;
    //END
    m_TdMixerOutHandle = MS_API_TD_MixerOpen(&OpenParam,&ErrCode);
  

    MS_API_TD_MixerFrameStart();
#if 1
    msleep(2000);
    OpenParam.DmaWbParam.WriteBaseAddressY0     = MAIN_ROTATION_Y_ADDR_A;
    OpenParam.DmaWbParam.WriteBaseAddressY1     = MAIN_ROTATION_Y_ADDR_A;
    OpenParam.DmaWbParam.WriteBaseAddressUV0    = MAIN_ROTATION_U_ADDR_A;
    OpenParam.DmaWbParam.WriteBaseAddressUV1    = MAIN_ROTATION_U_ADDR_A;

    MH_TD_set_DispMixAlp0_Layer0GlbAlp(0xee);
    MH_TD_set_WbBaseAddr0Y(OpenParam.DmaWbParam.WriteBaseAddressY0);
    MH_TD_set_WbBaseAddr1Y(OpenParam.DmaWbParam.WriteBaseAddressY1);
    MH_TD_set_WbBaseAddr0UV(OpenParam.DmaWbParam.WriteBaseAddressUV0); 
    MH_TD_set_WbBaseAddr1UV(OpenParam.DmaWbParam.WriteBaseAddressUV1);

    MS_API_TD_MixerFrameStart();
    msleep(2000);
#endif
    printf("TD_MixerTestVideoMainYUV_Joint Config done!...ErrCode = %d.......................\n\n\n",ErrCode);
}

void resetVO(void)
{
/*
    MH_VO_set_DispEnable(0);

    MH_VO_set_DmaSwCtl_ReqRd(0);
    
    MH_VO_set_SoftRstCtl_Vo(1);


    MH_VO_set_SoftRstCtl_Core(1);
    MH_VO_set_SoftRstCtl_Disp(1);
    MH_VO_set_SoftRstCtl_Apb(1);
   
    printf("MH_VO_get_SoftRstCtl 0x%x!\n",MH_VO_get_SoftRstCtl());

    //release Rst
    MH_VO_set_SoftRstCtl_Vo(0);

    MH_VO_set_SoftRstCtl(0x0);
*/
}

void TD_TestScaler(TD_MixerTestParam *param)
{

    MD_TD_MixerParamaterT OpenParam;
    MS_U32 ErrCode = MS_OK;

    MS_API_TD_WrapInit();

    MS_API_TD_MixerInit();

    memset(&OpenParam,0,sizeof(MD_TD_MixerParamaterT));

    //cfg video layer0
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerEnable          = 1;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StartX = VIDEO_LAYER0_H_POSITION + param->videoStartX;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StartY = VIDEO_LAYER0_V_POSITION + param->videoStartY;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StopX  = VIDEO_LAYER0_H_POSITION + param->videoStartX + param->videoOutWidth;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StopY  = VIDEO_LAYER0_V_POSITION + param->videoStartY + param->videoOutHeight;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInDataMode        = param->yuvMode;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].EndianModeY          = param->endianModeY;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].EndianModeUV         = param->endianModeUV;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelHszie      = param->videoWidth;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelVszie      = param->videoHeight;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgOutPixelHszie     = param->videoOutWidth;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgOutPixelVszie     = param->videoOutHeight;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelStrideH    = param->videoStride;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelStrideV    = 0;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelOffsetH    = 0;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelOffsetV    = 0;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].GlobalAlpha          = param->videoGlbAlpha;
    
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ReadAddress0Y        =  param->videoAddrY;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ReadAddress0UV       =  param->videoAddrUV;

    OpenParam.LayerMixerOrder                                       = OpenParam.LayerMixerOrder|(0 << 0);


    //cfg OSD layer4
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].OsdEnable                = 0;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].OsdType                  = param->osdType;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].AlphaTpye                = param->alphaType;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].OsdPixelHszie            = param->osdWidth;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].OsdPixelVszie            = param->osdHeight;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].LayerPosition.StartX     = VIDEO_LAYER0_H_POSITION + param->osdStartX;   
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].LayerPosition.StartY     = VIDEO_LAYER0_V_POSITION + param->osdStartY;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].LayerPosition.StopX      = VIDEO_LAYER0_H_POSITION + param->osdStartX +param->osdWidth;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].LayerPosition.StopY      = VIDEO_LAYER0_V_POSITION + param->osdStartY + param->osdHeight;

    OpenParam.OSDLayerParam[TD_OSD_LAYER0].RequestBLen              = 0xf;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].DmaMap                   = param->dmaMap;//original
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].RevRGB                   = param->revRGB;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].DataInStride             = param->osdStride;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].AlphaInStride            = param->alphaStride;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].RGB2YUVEnable            = 1;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].GlobalAlpha              = param->osdGlbAlpha;

    OpenParam.OSDLayerParam[TD_OSD_LAYER0].ReadAddress0Value        = param->osdAddr;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].ReadAddress0Alp          = param->osdAlphaAddr;

    OpenParam.LayerMixerOrder                                       = OpenParam.LayerMixerOrder|(1 << 16);

    OpenParam.WindowZone.StartX                                     = VIDEO_DISP_ZONE_X_START;
    OpenParam.WindowZone.StopX                                      = VIDEO_DISP_ZONE_X_START + param->wbWidth;
    OpenParam.WindowZone.StartY                                     = VIDEO_DISP_ZONE_Y_START;
    OpenParam.WindowZone.StopY                                      = VIDEO_DISP_ZONE_Y_START + param->wbHeight;


    //DMA OUT

    ///////
        OpenParam.BackGroundComp = 0x00808080;
    if(param->wbRGBorYUV == 1) //yuv
        OpenParam.DisplayYUV2RGBEn = 1;
    else    //rgb
        OpenParam.DisplayYUV2RGBEn = 1;
    
    //DMA OUT

    
    OpenParam.DmaWriteBackEn = 1;
    OpenParam.DmaWbParam.InputMode              = 1; //0:BT656  1:BT1120     
    
    OpenParam.DmaWbParam.DataFormat             = param->wbRGBorYUV;     // 0:RGB/RAW  1:YUV  
    OpenParam.DmaWbParam.DmaInputFormat         = param->wbYUVInputFormat;     //1`b0:YUV422;1`b1:YUV420    

    OpenParam.DmaWbParam.OutputMode             = param->wbOutputFormat; //0: yuv422, 1: yuv420, 0:r/g/b separate, 1:argb
    OpenParam.DmaWbParam.DmaInput422PixelOrder  = param->wbYUV422PxlOrder;
    OpenParam.DmaWbParam.RawPixelWidth          = param->wbPixWidth; //0: 8 bit rgb/raw
    
    OpenParam.DmaWbParam.WriteBaseAddressY0     = param->wbBaseAddrY;
    OpenParam.DmaWbParam.WriteBaseAddressY1     = param->wbBaseAddrY;
    OpenParam.DmaWbParam.WriteBaseAddressUV0    = param->wbBaseAddrUV;
    OpenParam.DmaWbParam.WriteBaseAddressUV1    = param->wbBaseAddrUV;
    
    OpenParam.DmaWbParam.DataLineYStride        = param->wbStride;
    OpenParam.DmaWbParam.DataLineUVStride       = param->wbStride;       
    
    OpenParam.DmaWbParam.DramLoopSzie           = 0xFFFF;
    
    OpenParam.DmaWbParam.ActiveHszie            = param->wbWidth;
    OpenParam.DmaWbParam.ActiveVszie            = param->wbHeight;

#if 0    
    OpenParam.DmaWbParam.Ch1OtNum               = 1; 
    OpenParam.DmaWbParam.Ch1BlenMode            = 0; 
    OpenParam.DmaWbParam.Ch1ContinuousMode      = 1;   
    OpenParam.DmaWbParam.Ch1DmaYUVMap           = 0;
    OpenParam.DmaWbParam.Ch1WbErrDetectEn       = 0;         
    OpenParam.DmaWbParam.Ch1ErrUnit             = 1;
    OpenParam.DmaWbParam.Ch1ErrTh               = 1;
    OpenParam.DmaWbParam.Ch2OtNum               = 1;
    OpenParam.DmaWbParam.Ch2BlenMode            = 0;
    OpenParam.DmaWbParam.Ch2ContinuousMode      = 1;
    OpenParam.DmaWbParam.Ch2DmaYUVMap           = 0;
    OpenParam.DmaWbParam.Ch2WbErrDetectEn       = 0;    
    OpenParam.DmaWbParam.Ch2ErrUnit             = 1;
    OpenParam.DmaWbParam.Ch2ErrTh               = 1;  

#else
    OpenParam.DmaWbParam.Ch1OtNum               = 1; 
    OpenParam.DmaWbParam.Ch1BlenMode            = 0; 
    OpenParam.DmaWbParam.Ch1ContinuousMode      = 1;   
    OpenParam.DmaWbParam.Ch1DmaYUVMap           = 1;
    OpenParam.DmaWbParam.Ch1WbErrDetectEn       = 0;         
    OpenParam.DmaWbParam.Ch1ErrUnit             = 1;
    OpenParam.DmaWbParam.Ch1ErrTh               = 1;
    
    OpenParam.DmaWbParam.Ch2OtNum               = 1;
    OpenParam.DmaWbParam.Ch2BlenMode            = 0;
    OpenParam.DmaWbParam.Ch2ContinuousMode      = 1;
    OpenParam.DmaWbParam.Ch2DmaYUVMap           = 0;
    OpenParam.DmaWbParam.Ch2WbErrDetectEn       = 0;    
    OpenParam.DmaWbParam.Ch2ErrUnit             = 1;
    OpenParam.DmaWbParam.Ch2ErrTh               = 1;    
#endif    
    //END
    m_TdMixerOutHandle = MS_API_TD_MixerOpen(&OpenParam,&ErrCode);

    MS_API_TD_MixerFrameStart();
    gCycleStart = read_cycle();

   
    //msleep(500);
            
    printf("Display Config done!\n");
    TD_PrintRotRegValue();
    TD_MixerPrintRegValue();
}    

#if 0
{
    MD_TD_MixerParamaterT OpenParam;
    MS_U32 ErrCode = MS_OK;
#if 1
    MS_API_TD_WrapInit();

    MS_API_TD_MixerInit();

    memset(&OpenParam,0,sizeof(MD_TD_MixerParamaterT));

    //cfg video layer0
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerEnable          = 1;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StartX = VIDEO_DISP_ZONE_X_START;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StartY = VIDEO_DISP_ZONE_Y_START;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StopX  = VIDEO_DISP_ZONE_X_START + param->outWidth;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StopY  = VIDEO_DISP_ZONE_Y_START + param->outHeight;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInDataMode        = param->yuvMode;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].EndianModeY          = TD_VIDEO_LAYER_Y_ENDIAN_MODE2;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].EndianModeUV         = TD_VIDEO_LAYER_UV_ENDIAN_MODE4;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelHszie      = param->inWidth;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelVszie      = param->inHeight;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgOutPixelHszie     = param->outWidth;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgOutPixelVszie     = param->outHeight;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelStrideH    = param->inStride;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelStrideV    = 0;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelOffsetH    = 0;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelOffsetV    = 0;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].GlobalAlpha          = 0xff;
    
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ReadAddress0Y        =  DUMP_ROTATION_ADDR_SRCY;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ReadAddress0UV       =  DUMP_ROTATION_ADDR_SRCY + param->inHeight * param->inStride;//DUMP_ROTATION_ADDR_SRCUV;

    OpenParam.LayerMixerOrder                                       = OpenParam.LayerMixerOrder|(0 << 0);


    OpenParam.WindowZone.StartX                                     = VIDEO_DISP_ZONE_X_START;
    OpenParam.WindowZone.StopX                                      = VIDEO_DISP_ZONE_X_START + param->outWidth;
    OpenParam.WindowZone.StartY                                     = VIDEO_DISP_ZONE_Y_START;
    OpenParam.WindowZone.StopY                                      = VIDEO_DISP_ZONE_Y_START + param->outHeight;


    OpenParam.BackGroundComp = 0x00808080;
    if(param->wbRGBorYUV == 1) //yuv
        OpenParam.DisplayYUV2RGBEn = 1;
    else    //rgb
        OpenParam.DisplayYUV2RGBEn = 1;
    
    //DMA OUT

    
    OpenParam.DmaWriteBackEn = 1;
    OpenParam.DmaWbParam.InputMode              = 1; //0:BT656  1:BT1120     
    
    OpenParam.DmaWbParam.DataFormat             = param->wbRGBorYUV;     // 0:RGB/RAW  1:YUV  
    OpenParam.DmaWbParam.DmaInputFormat         = param->wbYUVInputFormat;     //1`b0:YUV422;1`b1:YUV420    

    OpenParam.DmaWbParam.OutputMode             = param->wbOutputFormat; //0: yuv422, 1: yuv420, 0:r/g/b separate, 1:argb
    OpenParam.DmaWbParam.DmaInput422PixelOrder  = param->wbYUV422PxlOrder;
    OpenParam.DmaWbParam.RawPixelWidth          = 0; //0: 8 bit rgb/raw
    
    OpenParam.DmaWbParam.WriteBaseAddressY0     = param->wbBaseAddrY;
    OpenParam.DmaWbParam.WriteBaseAddressY1     = param->wbBaseAddrY;
    OpenParam.DmaWbParam.WriteBaseAddressUV0    = param->wbBaseAddrUV;
    OpenParam.DmaWbParam.WriteBaseAddressUV1    = param->wbBaseAddrUV;
    
    OpenParam.DmaWbParam.DataLineYStride        = param->wbStride;
    OpenParam.DmaWbParam.DataLineUVStride       = param->wbStride;       
    
    OpenParam.DmaWbParam.DramLoopSzie           = 0xFFFF;
    
    OpenParam.DmaWbParam.ActiveHszie            = param->outWidth;
    OpenParam.DmaWbParam.ActiveVszie            = param->outHeight;

    OpenParam.DmaWbParam.Ch1OtNum               = 1; 
    OpenParam.DmaWbParam.Ch1BlenMode            = 0; 
    OpenParam.DmaWbParam.Ch1ContinuousMode      = 1;   
    OpenParam.DmaWbParam.Ch1DmaYUVMap           = 0;
    OpenParam.DmaWbParam.Ch1WbErrDetectEn       = 0;         
    OpenParam.DmaWbParam.Ch1ErrUnit             = 1;
    OpenParam.DmaWbParam.Ch1ErrTh               = 1;
    OpenParam.DmaWbParam.Ch2OtNum               = 1;
    OpenParam.DmaWbParam.Ch2BlenMode            = 0;
    OpenParam.DmaWbParam.Ch2ContinuousMode      = 1;
    OpenParam.DmaWbParam.Ch2DmaYUVMap           = 0;
    OpenParam.DmaWbParam.Ch2WbErrDetectEn       = 0;    
    OpenParam.DmaWbParam.Ch2ErrUnit             = 1;
    OpenParam.DmaWbParam.Ch2ErrTh               = 1; 
    
    //END
    m_TdMixerOutHandle = MS_API_TD_MixerOpen(&OpenParam,&ErrCode);

    MS_API_TD_MixerFrameStart();
    gCycleStart = read_cycle();

#else
    MS_API_TD_WrapInit();
       
    MS_API_TD_MixerInit();

    memset(&OpenParam,0,sizeof(MD_TD_MixerParamaterT));
    
    //cfg video layer0
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerEnable          = 1;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StartX = VIDEO_DISP_ZONE_X_START;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StartY = VIDEO_DISP_ZONE_Y_START;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StopX  = VIDEO_DISP_ZONE_X_START + 320;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StopY  = VIDEO_DISP_ZONE_Y_START + 240;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInDataMode        = TD_VIDEO_LAYER_YUV_MODE_420;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].EndianModeY          = TD_VIDEO_LAYER_Y_ENDIAN_MODE2;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].EndianModeUV         = TD_VIDEO_LAYER_UV_ENDIAN_MODE4;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelHszie      = 640;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelVszie      = 480;
    
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgOutPixelHszie     = 320;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgOutPixelVszie     = 240;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelStrideH    = 640;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelStrideV    = 0;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelOffsetH    = 0;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelOffsetV    = 0;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].GlobalAlpha          = 0xff;
    
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ReadAddress0Y        =  DUMP_ROTATION_ADDR_SRCY;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ReadAddress0UV       =  DUMP_ROTATION_ADDR_SRCY + param->inHeight * param->inStride;//DUMP_ROTATION_ADDR_SRCUV;

    OpenParam.LayerMixerOrder                                       = OpenParam.LayerMixerOrder|(0 << 0 );


    OpenParam.WindowZone.StartX                                     =  VIDEO_DISP_ZONE_X_START;
    OpenParam.WindowZone.StopX                                      =  VIDEO_DISP_ZONE_X_START + 320;
    OpenParam.WindowZone.StartY                                     =  VIDEO_DISP_ZONE_Y_START;
    OpenParam.WindowZone.StopY                                      =  VIDEO_DISP_ZONE_Y_START + 240;


    OpenParam.BackGroundComp = 0x00808080;
    OpenParam.DisplayYUV2RGBEn = 1;

    //DMA OUT
    OpenParam.DmaWriteBackEn = 1;
    OpenParam.DmaWbParam.InputMode              = 1; //0£ºbt656  1:BT1120     
    
    OpenParam.DmaWbParam.DataFormat             = 1;     //RGB/RAW  1:YUV  
    OpenParam.DmaWbParam.DmaInputFormat         = 1;     //1`b0:YUV422;1`b1:YUV420    

    OpenParam.DmaWbParam.OutputMode             = 1;
    OpenParam.DmaWbParam.DmaInput422PixelOrder  = 0;
    OpenParam.DmaWbParam.RawPixelWidth          = 0;
    
    OpenParam.DmaWbParam.WriteBaseAddressY0     = DUMP_MIXER_DST_ADDR_Y;
    OpenParam.DmaWbParam.WriteBaseAddressY1     = DUMP_MIXER_DST_ADDR_Y;
    OpenParam.DmaWbParam.WriteBaseAddressUV0    = DUMP_MIXER_DST_ADDR_UV;
    OpenParam.DmaWbParam.WriteBaseAddressUV1    = DUMP_MIXER_DST_ADDR_UV;
    
    OpenParam.DmaWbParam.DataLineYStride        = 320;
    OpenParam.DmaWbParam.DataLineUVStride       = 320;       
    
    OpenParam.DmaWbParam.ActiveHszie            = 320;
    OpenParam.DmaWbParam.ActiveVszie            = 240;

    OpenParam.DmaWbParam.DramLoopSzie           = 0xFFFF;
    
    OpenParam.DmaWbParam.Ch1OtNum               = 1; 
    OpenParam.DmaWbParam.Ch1BlenMode            = 0; 
    OpenParam.DmaWbParam.Ch1ContinuousMode      = 1;   
    OpenParam.DmaWbParam.Ch1DmaYUVMap           = 0;
    OpenParam.DmaWbParam.Ch1WbErrDetectEn       = 0;         
    OpenParam.DmaWbParam.Ch1ErrUnit             = 1;
    OpenParam.DmaWbParam.Ch1ErrTh               = 1;
    
    OpenParam.DmaWbParam.Ch2OtNum               = 1;
    OpenParam.DmaWbParam.Ch2BlenMode            = 0;
    OpenParam.DmaWbParam.Ch2ContinuousMode      = 1;
    OpenParam.DmaWbParam.Ch2DmaYUVMap           = 0;
    OpenParam.DmaWbParam.Ch2WbErrDetectEn       = 0;    
    OpenParam.DmaWbParam.Ch2ErrUnit             = 1;
    OpenParam.DmaWbParam.Ch2ErrTh               = 1;
    //END
    m_TdMixerOutHandle = MS_API_TD_MixerOpen(&OpenParam,&ErrCode);
  

    MS_API_TD_MixerFrameStart();

    printf("Display Config done!\n");
#endif

}
#endif
void TD_TestRotation(TD_RotationTestParam *param)
{
    MD_TD_RotationParmT OpenParam;
    MS_U32 ErrCode = MS_OK;
  
    MS_U8 Iloop = 0;

    MS_API_TD_WrapInit();
    

    memset(&OpenParam,0,sizeof(MD_TD_RotationParmT));

    //cfg video layer0
    OpenParam.RotationMode         = param->rotMode;
    OpenParam.RotationPixelFormat  = param->pxlFormat;

    OpenParam.InSwapEn             = param->InSwapEn;
    OpenParam.BigLittleInEndia     = param->BigLittleInEndia;

    OpenParam.OutSwapEn            = param->enOutSwap;
    OpenParam.BigLittleOutEndia    = param->enEndianSwap;
#if 1
    OpenParam.InSwapEn             = 1;
    OpenParam.BigLittleInEndia     = 1;
    OpenParam.OutSwapEn            = 1;
    OpenParam.BigLittleOutEndia    = 1;

#endif
    
    OpenParam.OtMaxRD              = 15;
    OpenParam.OtMaxWR              = 15;

    OpenParam.DoneTimeOut          = 0xffff;
    
    OpenParam.ActiveHor          = param->width;
    OpenParam.ActiveVer          = param->height; 
 
    OpenParam.StrideSrcY          = param->inStride; 
    OpenParam.StrideDesY          = param->outStride;
 
    OpenParam.StrideSrcU          = param->inStride; 
    OpenParam.StrideDesU          = param->outStride;

    OpenParam.StrideSrcV          = param->inStride; 
    OpenParam.StrideDesV          = param->outStride;

    if(OpenParam.RotationPixelFormat == TD_ROTATION_PIX_FORMAT_420SP || 
        OpenParam.RotationPixelFormat == TD_ROTATION_PIX_FORMAT_MONO)
    {
        if(OpenParam.RotationMode == TD_ROTATION_90_DEGREE)
        {
            printf("420 rotae 90\n");
            OpenParam.BaseAddrSrcY = param->addrSrcY + (OpenParam.ActiveVer - 1)*OpenParam.StrideSrcY;
            OpenParam.BaseAddrSrcU = param->addrSrcUV + (OpenParam.ActiveVer/2 -1)*OpenParam.StrideSrcU;
            OpenParam.BaseAddrSrcV = 0;
        }
        else
        {
            OpenParam.BaseAddrSrcY = param->addrSrcY + OpenParam.ActiveHor - 32;
            OpenParam.BaseAddrSrcU = param->addrSrcUV + OpenParam.ActiveHor - 32;
            OpenParam.BaseAddrSrcV = 0;

        }
        
        OpenParam.StrideSrcV          = 0; 
        OpenParam.StrideDesV          = 0;
    }   
    else if(OpenParam.RotationPixelFormat == TD_ROTATION_PIX_FORMAT_422SP)
    {
        if(OpenParam.RotationMode == TD_ROTATION_90_DEGREE)
        {
            printf("422 rotae 90\n");
            OpenParam.BaseAddrSrcY = param->addrSrcY + (OpenParam.ActiveVer - 1)*OpenParam.StrideSrcY;
            OpenParam.BaseAddrSrcU = param->addrSrcUV + (OpenParam.ActiveVer -1)*OpenParam.StrideSrcU;
            OpenParam.BaseAddrSrcV = 0;
            
        }
        else
        {
            OpenParam.BaseAddrSrcY = param->addrSrcY + OpenParam.ActiveHor - 32;
            OpenParam.BaseAddrSrcU = param->addrSrcUV + OpenParam.ActiveHor - 32;
            OpenParam.BaseAddrSrcV = 0;

        }
        OpenParam.StrideSrcV          = 0; 
        OpenParam.StrideDesV          = 0;        
    }
    else 
    {
        if(OpenParam.RotationMode == TD_ROTATION_90_DEGREE)
        {
            printf("444 rotae 90\n");
            OpenParam.BaseAddrSrcY = param->addrSrcY + (OpenParam.ActiveVer - 1)*OpenParam.StrideSrcY;
            OpenParam.BaseAddrSrcU = param->addrSrcUV + (OpenParam.ActiveVer -1)*OpenParam.StrideSrcU;
            OpenParam.BaseAddrSrcV = param->addrSrcV + (OpenParam.ActiveVer -1)*OpenParam.StrideSrcV;;
        }
        else
        {
            OpenParam.BaseAddrSrcY = param->addrSrcY + OpenParam.ActiveHor - 32;
            OpenParam.BaseAddrSrcU = param->addrSrcUV + OpenParam.ActiveHor - 32;
            OpenParam.BaseAddrSrcV = param->addrSrcV + OpenParam.ActiveHor - 32;;

        }
    }

    

    OpenParam.BaseAddrDesY = param->addrDstY;
    OpenParam.BaseAddrDesU = param->addrDstUV;
    OpenParam.BaseAddrDesV = param->addrDstV;


    m_TdRotationOutHandle = MS_API_TD_RotationOpen(&OpenParam,&ErrCode);
    printf("start rotation\n");

    MS_API_TD_RotationFrameStart();
    gCycleStart = read_cycle();
    
    printf("TD rotation ErrCode = %d!\n",ErrCode);

}


void TD_TestMixer(TD_MixerTestParam *param)
{

    MD_TD_MixerParamaterT OpenParam;
    MS_U32 ErrCode = MS_OK;

    MS_API_TD_WrapInit();

    MS_API_TD_MixerInit();

    memset(&OpenParam,0,sizeof(MD_TD_MixerParamaterT));

    //cfg video layer0
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerEnable          = 1;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StartX = VIDEO_LAYER0_H_POSITION + param->videoStartX;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StartY = VIDEO_LAYER0_V_POSITION + param->videoStartY;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StopX  = VIDEO_LAYER0_H_POSITION + param->videoStartX + param->videoWidth;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StopY  = VIDEO_LAYER0_V_POSITION + param->videoStartY + param->videoHeight;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInDataMode        = param->yuvMode;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].EndianModeY          = param->endianModeY;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].EndianModeUV         = param->endianModeUV;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelHszie      = param->videoWidth;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelVszie      = param->videoHeight;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgOutPixelHszie     = param->videoWidth;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgOutPixelVszie     = param->videoHeight;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelStrideH    = param->videoStride;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelStrideV    = 0;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelOffsetH    = 0;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelOffsetV    = 0;

    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].GlobalAlpha          = param->videoGlbAlpha;
    
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ReadAddress0Y        =  param->videoAddrY;
    OpenParam.VideoLayerParam[TD_VIDEO_LAYER0].ReadAddress0UV       =  param->videoAddrUV;

    OpenParam.LayerMixerOrder                                       = OpenParam.LayerMixerOrder|(0 << 0);


    //cfg OSD layer4
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].OsdEnable                = 1;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].OsdType                  = param->osdType;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].AlphaTpye                = param->alphaType;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].OsdPixelHszie            = param->osdWidth;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].OsdPixelVszie            = param->osdHeight;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].LayerPosition.StartX     = VIDEO_LAYER0_H_POSITION + param->osdStartX;   
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].LayerPosition.StartY     = VIDEO_LAYER0_V_POSITION + param->osdStartY;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].LayerPosition.StopX      = VIDEO_LAYER0_H_POSITION + param->osdStartX +param->osdWidth;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].LayerPosition.StopY      = VIDEO_LAYER0_V_POSITION + param->osdStartY + param->osdHeight;

    OpenParam.OSDLayerParam[TD_OSD_LAYER0].RequestBLen              = 0xf;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].DmaMap                   = param->dmaMap;//original
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].RevRGB                   = param->revRGB;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].DataInStride             = param->osdStride;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].AlphaInStride            = param->alphaStride;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].RGB2YUVEnable            = 1;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].GlobalAlpha              = param->osdGlbAlpha;

    OpenParam.OSDLayerParam[TD_OSD_LAYER0].ReadAddress0Value        = param->osdAddr;
    OpenParam.OSDLayerParam[TD_OSD_LAYER0].ReadAddress0Alp          = param->osdAlphaAddr;

    OpenParam.LayerMixerOrder                                       = OpenParam.LayerMixerOrder|(1 << 16);

    OpenParam.WindowZone.StartX                                     = VIDEO_DISP_ZONE_X_START;
    OpenParam.WindowZone.StopX                                      = VIDEO_DISP_ZONE_X_START + param->wbWidth;
    OpenParam.WindowZone.StartY                                     = VIDEO_DISP_ZONE_Y_START;
    OpenParam.WindowZone.StopY                                      = VIDEO_DISP_ZONE_Y_START + param->wbHeight;


    //DMA OUT

    ///////
        OpenParam.BackGroundComp = 0x00808080;
    if(param->wbRGBorYUV == 1) //yuv
        OpenParam.DisplayYUV2RGBEn = 1;
    else    //rgb
        OpenParam.DisplayYUV2RGBEn = 1;
    
    //DMA OUT

    
    OpenParam.DmaWriteBackEn = 1;
    OpenParam.DmaWbParam.InputMode              = 1; //0:BT656  1:BT1120     
    
    OpenParam.DmaWbParam.DataFormat             = param->wbRGBorYUV;     // 0:RGB/RAW  1:YUV  
    OpenParam.DmaWbParam.DmaInputFormat         = param->wbYUVInputFormat;     //1`b0:YUV422;1`b1:YUV420    

    OpenParam.DmaWbParam.OutputMode             = param->wbOutputFormat; //0: yuv422, 1: yuv420, 0:r/g/b separate, 1:argb
    OpenParam.DmaWbParam.DmaInput422PixelOrder  = param->wbYUV422PxlOrder;
    OpenParam.DmaWbParam.RawPixelWidth          = 0; //0: 8 bit rgb/raw
    
    OpenParam.DmaWbParam.WriteBaseAddressY0     = param->wbBaseAddrY;
    OpenParam.DmaWbParam.WriteBaseAddressY1     = param->wbBaseAddrY;
    OpenParam.DmaWbParam.WriteBaseAddressUV0    = param->wbBaseAddrUV;
    OpenParam.DmaWbParam.WriteBaseAddressUV1    = param->wbBaseAddrUV;
    
    OpenParam.DmaWbParam.DataLineYStride        = param->wbStride;
    OpenParam.DmaWbParam.DataLineUVStride       = param->wbStride;       
    
    OpenParam.DmaWbParam.DramLoopSzie           = 0xFFFF;
    
    OpenParam.DmaWbParam.ActiveHszie            = param->wbWidth;
    OpenParam.DmaWbParam.ActiveVszie            = param->wbHeight;
    
    OpenParam.DmaWbParam.Ch1OtNum               = 1; 
    OpenParam.DmaWbParam.Ch1BlenMode            = 0; 
    OpenParam.DmaWbParam.Ch1ContinuousMode      = 1;   
    OpenParam.DmaWbParam.Ch1DmaYUVMap           = 0;
    OpenParam.DmaWbParam.Ch1WbErrDetectEn       = 0;         
    OpenParam.DmaWbParam.Ch1ErrUnit             = 1;
    OpenParam.DmaWbParam.Ch1ErrTh               = 1;
    OpenParam.DmaWbParam.Ch2OtNum               = 1;
    OpenParam.DmaWbParam.Ch2BlenMode            = 0;
    OpenParam.DmaWbParam.Ch2ContinuousMode      = 1;
    OpenParam.DmaWbParam.Ch2DmaYUVMap           = 0;
    OpenParam.DmaWbParam.Ch2WbErrDetectEn       = 0;    
    OpenParam.DmaWbParam.Ch2ErrUnit             = 1;
    OpenParam.DmaWbParam.Ch2ErrTh               = 1;   
    //END
    m_TdMixerOutHandle = MS_API_TD_MixerOpen(&OpenParam,&ErrCode);

    MS_API_TD_MixerFrameStart();
    gCycleStart = read_cycle();

   
    //msleep(500);
            
    //printf("Display Config done!\n");
}

void TestTDCase(MS_U8 testCase)
{

    MS_BOOL bEnableInt = MS_FALSE;
    MS_U8 TestCase = TD_CASE_UNDEFINE;
    volatile MS_U32 status = 0;

    TestCase = testCase;//TD_ROTATION_90_DEGREE_720P_422;//TD_SCALER_1080P_420IN_ARGBOUT;//TD_ROTATION_90_DEGREE_CIF_422;//TD_MIXER_420_ARGB8888_GLOBAL_ALPHA_TRAVERSAL;//TD_MIXER_420_ARGB8888_GLOBAL_ALPHA_TRAVERSAL;//TD_SCALER_1080P_420IN_YUV422OUT;//;
    printf("TestTDCase %d\n", TestCase);
#ifndef CANAAN_ISP

    //switch axi bus to 2d
    *(volatile MS_U32 *)0x924700cc = 0x1;
#endif
    
    switch( TestCase )
    {
        case TD_ROTATION_90_DEGREE_320352_MONO:
            TD_TestRotation90Degree320352YuvMONO(1,1,1,1);
            break;
        case TD_ROTATION_90_DEGREE_320352_MONO_ENDIAN_INPUT:
            TD_TestRotation90Degree320352YuvMONO(1,0,1,1);
            break;
        case TD_ROTATION_90_DEGREE_320352_MONO_SWAP_INPUT:
            TD_TestRotation90Degree320352YuvMONO(0,1,1,1);
            break;
        case TD_ROTATION_90_DEGREE_320352_MONO_ENDIAN_OUTPUT:
            TD_TestRotation90Degree320352YuvMONO(1,1,1,0);
            break;
        case TD_ROTATION_90_DEGREE_320352_MONO_SWAP_OUTPUT:
            TD_TestRotation90Degree320352YuvMONO(1,1,0,1);
            break;

        case TD_ROTATION_90_DEGREE_320352_420:
            TD_TestRotation90Degree320352Yuv420();
            break;
        case TD_ROTATION_90_DEGREE_320352_422:
            TD_TestRotation90Degree320352Yuv422();
            break;
        case TD_ROTATION_90_DEGREE_444:
            TD_TestRotation90DegreeYuv444();
            break;

        case TD_ROTATION_90_DEGREE_1080p_420_TIMEOUT:
            TD_TestRotation90Degree1080pYuv420_Timeout();
            break;

        case TD_ROTATION_270_DEGREE_320352_420:
            TD_TestRotation270Degree320352Yuv420();
            break;
        case TD_ROTATION_270_DEGREE_320352_422:
            TD_TestRotation270Degree320352Yuv422();
            break;

        case TD_ROTATION_90_DEGREE_MAIN_420:   ////VO_CASE_LAYER_TD_ROTATION_TEST
            TD_TestRotation90DegreeMainYuv420();
            break;
        case TD_ROTATION_270_DEGREE_MAIN_420:
            TD_TestRotation270DegreeMainYuv420();
            break;
        case TD_ROTATION_90_DEGREE_MAIN_422:
            TD_TestRotation90DegreeMainYuv422();
            break;

        case TD_ROTATION_90_DEGREE_MAIN_444:
            TD_TestRotation90DegreeMainYuv444();
            break;

        
        case TD_MIXER_VIDEO_320352_OSD_256200:
            TD_MixerTestVideo320240Osd256200(TD_VIDEO_LAYER_YUV_MODE_420);
            break;
        
        case TD_MIXER_MAINYUV_320to640480:
            TD_MixerTestVideoMainYUV_320to640480(TD_VIDEO_LAYER_YUV_MODE_420);
         
            break;
        case TD_MIXER_MAINYUV_320to176144:
            TD_MixerTestVideoMainYUV_320to176144(TD_VIDEO_LAYER_YUV_MODE_420);
            break;
        
        case TD_MIXER_MAINYUV_BACKGROUND:
            TD_MixerTestVideoMainYUV_Backgroud(TD_VIDEO_LAYER_YUV_MODE_420);
            break;
        
        case TD_MIXER_MAINYUV_ALPHA:
            TD_MixerTestVideoMainYUV_Alpha(TD_VIDEO_LAYER_YUV_MODE_420);
            break;
        
        case TD_MIXER_MAINYUV_MIXER:
            TD_MixerTestVideoMainYUV_MixerSelect(TD_VIDEO_LAYER_YUV_MODE_420);
            break;


        case TD_MIXER_MAINYUV_POSITION:
            TD_MixerTestVideoMainYUV_Postion(TD_VIDEO_LAYER_YUV_MODE_420);
            break;
        
        case TD_MIXER_MAINYUV_CROP:
            TD_MixerTestVideoMainYUV_Crop(TD_VIDEO_LAYER_YUV_MODE_420);
            break;

        case TD_MIXER_MAINYUV_JOINT:  ////VO_CASE_LAYER_TD_MIXER_TEST
            TD_MixerTestVideoMainYUV_Joint(TD_VIDEO_LAYER_YUV_MODE_420);
            break;
        
            
        case TD_MIXER_MAINYUV_ROTATION:
            TD_MixerTestVideoMainYUV_MixerMainStream_Rotation(TD_VIDEO_LAYER_YUV_MODE_420);
            break;
            

        case TD_ROTATION_90_DEGREE_1080P_420: //passed on final release
            m_TdRotParam.width = 1080;
            m_TdRotParam.height = 1920;
            m_TdRotParam.inStride = 1080;
            m_TdRotParam.outStride = 1920;
            m_TdRotParam.addrSrcY = 0x01000000;//DUMP_ROTATION_ADDR_SRCY;
            m_TdRotParam.addrSrcUV = m_TdRotParam.addrSrcY + m_TdRotParam.inStride * m_TdRotParam.height;
            m_TdRotParam.addrDstY = 0x02000000;//DUMP_ROTATION_ADDR_DSTY;
            m_TdRotParam.addrDstUV = 0x02000000 + 1920*1080;//DUMP_ROTATION_ADDR_DSTUV;

            MH_TD_set_WrapInt(0x7);

            unsigned int reg = *(volatile MS_U32 *)(TD_BASE_ADDR + 0x7c);         
            *(volatile MS_U32 *)(TD_BASE_ADDR + 0x7c) = reg&~(1 << 16);

            TD_TestRotation(&m_TdRotParam);
            //SimRotate(m_TdRotParam.rotMode,m_TdRotParam.width, m_TdRotParam.height,m_TdRotParam.inStride,m_TdRotParam.outStride, m_TdRotParam.addrSrcY,m_TdRotParam.addrSrcUV,m_TdRotParam.addrDstY,m_TdRotParam.addrDstUV);

            msleep(2000);
            status = MH_TD_get_RotSt_FrameEnd();

            printf("TD_intr MH_TD_get_RotSt_FrameEnd   = %u!\n",status);
            status = MH_TD_get_RotSt_Done();
            
            printf("TD_intr MH_TD_get_RotSt_Done   = %u!\n",status);

#ifndef CANAAN_ISP
            //Switch axi to VO
            *(volatile MS_U32 *)0x924700cc = 0x0;
#endif
            ////VO_Test2D_YUV(VO_VIDEO_LAYER_YUV_MODE_420, 1920, 1080, 1920,VO_SYSTEM_MODE_1920x1080x30P);
            while(1);            
            break;
        case TD_ROTATION_90_DEGREE_720P_420: //pass
            m_TdRotParam.width = 720;
            m_TdRotParam.height = 1280;
            m_TdRotParam.inStride = 720;
            m_TdRotParam.outStride = 1280;            
            m_TdRotParam.addrSrcY = DUMP_ROTATION_ADDR_SRCY;
            m_TdRotParam.addrSrcUV = m_TdRotParam.addrSrcY + m_TdRotParam.inStride * m_TdRotParam.height;
            m_TdRotParam.addrDstY = DUMP_ROTATION_ADDR_DSTY;
            m_TdRotParam.addrDstUV = DUMP_ROTATION_ADDR_DSTUV;
            TD_TestRotation(&m_TdRotParam);
            //SimRotate(m_TdRotParam.rotMode,m_TdRotParam.width, m_TdRotParam.height,m_TdRotParam.inStride,m_TdRotParam.outStride, m_TdRotParam.addrSrcY,m_TdRotParam.addrSrcUV,m_TdRotParam.addrDstY,m_TdRotParam.addrDstUV)
#ifndef CANAAN_ISP
            //Switch axi to VO
            *(volatile MS_U32 *)0x924700cc = 0x0;
#endif
            //VO_Test2D_YUV(VO_VIDEO_LAYER_YUV_MODE_420, 1280, 720, 1280,VO_SYSTEM_MODE_1920x1080x30P);
            while(1);            
            break;

        case TD_ROTATION_90_DEGREE_VGA_420:
            m_TdRotParam.width = 640;
            m_TdRotParam.height = 480;
            m_TdRotParam.inStride = 1280;
            m_TdRotParam.outStride = 512;            
            m_TdRotParam.addrSrcY = DUMP_ROTATION_ADDR_SRCY;
            m_TdRotParam.addrSrcUV = m_TdRotParam.addrSrcY + 1280*720;// m_TdRotParam.inStride * m_TdRotParam.height;
            m_TdRotParam.addrDstY = DUMP_ROTATION_ADDR_DSTY;
            m_TdRotParam.addrDstUV = DUMP_ROTATION_ADDR_DSTUV;
            TD_TestRotation(&m_TdRotParam);
            msleep(2000);
            
            //Switch axi to VO
            *(volatile MS_U32 *)0x924700cc = 0x0;
            //VO_Test2D_YUV(VO_VIDEO_LAYER_YUV_MODE_420, 480, 640, 512,VO_SYSTEM_MODE_1280x720x50P);
            while(1);
            break;
        case TD_ROTATION_90_DEGREE_CIF_420:
            m_TdRotParam.width = 352;
            m_TdRotParam.height = 288;
            m_TdRotParam.inStride = 352;
            m_TdRotParam.outStride = 320;             
            m_TdRotParam.addrSrcY = DUMP_ROTATION_ADDR_SRCY;
            m_TdRotParam.addrSrcUV = m_TdRotParam.addrSrcY + m_TdRotParam.inStride * m_TdRotParam.height;
            m_TdRotParam.addrDstY = DUMP_ROTATION_ADDR_DSTY;
            m_TdRotParam.addrDstUV = DUMP_ROTATION_ADDR_DSTUV;
            //TD_TestRotation(&m_TdRotParam);
            //SimRotate(m_TdRotParam.rotMode,m_TdRotParam.width, m_TdRotParam.height,m_TdRotParam.inStride,m_TdRotParam.outStride, m_TdRotParam.addrSrcY,m_TdRotParam.addrSrcUV,m_TdRotParam.addrDstY,m_TdRotParam.addrDstUV);
            msleep(2000);
            
            //Switch axi to VO
            *(volatile MS_U32 *)0x924700cc = 0x0;
            //VO_Test2D_YUV(VO_VIDEO_LAYER_YUV_MODE_420, 288, 352, 320,VO_SYSTEM_MODE_1280x720x50P);
            while(1);
            
            break;
        case TD_ROTATION_90_DEGREE_QCIF_420:
            m_TdRotParam.width = 176;
            m_TdRotParam.height = 144;
            m_TdRotParam.inStride = 176;
            m_TdRotParam.outStride = 192;             
            m_TdRotParam.addrSrcY = DUMP_ROTATION_ADDR_SRCY;
            m_TdRotParam.addrSrcUV = m_TdRotParam.addrSrcY + m_TdRotParam.inStride * m_TdRotParam.height;
            m_TdRotParam.addrDstY = DUMP_ROTATION_ADDR_DSTY;
            m_TdRotParam.addrDstUV = DUMP_ROTATION_ADDR_DSTUV;
            TD_TestRotation(&m_TdRotParam);
            msleep(2000);
            break;
        case TD_ROTATION_270_DEGREE_1080P_420:
            m_TdRotParam.rotMode = TD_ROTATION_270_DEGREE;            
            m_TdRotParam.width = 1080;
            m_TdRotParam.height = 1920;
            m_TdRotParam.inStride = 1080;
            m_TdRotParam.outStride = 1920;
            m_TdRotParam.addrSrcY = DUMP_ROTATION_ADDR_SRCY;
            m_TdRotParam.addrSrcUV = m_TdRotParam.addrSrcY + m_TdRotParam.inStride * m_TdRotParam.height;
            m_TdRotParam.addrDstY = DUMP_ROTATION_ADDR_DSTY;
            m_TdRotParam.addrDstUV = DUMP_ROTATION_ADDR_DSTUV;
            TD_TestRotation(&m_TdRotParam);
            msleep(2000);
            break;
        case TD_ROTATION_270_DEGREE_720P_420:
            m_TdRotParam.rotMode = TD_ROTATION_270_DEGREE;                        
            m_TdRotParam.width = 720;
            m_TdRotParam.height = 1280;
            m_TdRotParam.inStride = 720;
            m_TdRotParam.outStride = 1280;            
            m_TdRotParam.addrSrcY = DUMP_ROTATION_ADDR_SRCY;
            m_TdRotParam.addrSrcUV = m_TdRotParam.addrSrcY + m_TdRotParam.inStride * m_TdRotParam.height;
            m_TdRotParam.addrDstY = DUMP_ROTATION_ADDR_DSTY;
            m_TdRotParam.addrDstUV = DUMP_ROTATION_ADDR_DSTUV;
            TD_TestRotation(&m_TdRotParam);
            msleep(2000);
            break;
        case TD_ROTATION_270_DEGREE_VGA_420:  //pass
            m_TdRotParam.rotMode = TD_ROTATION_270_DEGREE;                        
            m_TdRotParam.width = 640;
            m_TdRotParam.height = 480;
            m_TdRotParam.inStride = 640;
            m_TdRotParam.outStride = 512;            
            m_TdRotParam.addrSrcY = DUMP_ROTATION_ADDR_SRCY;
            m_TdRotParam.addrSrcUV = m_TdRotParam.addrSrcY + m_TdRotParam.inStride * m_TdRotParam.height;
            m_TdRotParam.addrDstY = DUMP_ROTATION_ADDR_DSTY;
            m_TdRotParam.addrDstUV = DUMP_ROTATION_ADDR_DSTUV;
            TD_TestRotation(&m_TdRotParam);
            msleep(2000);
#ifndef CANAAN_ISP
            //Switch axi to VO
            *(volatile MS_U32 *)0x924700cc = 0x0;
#endif
            //VO_Test2D_YUV(VO_VIDEO_LAYER_YUV_MODE_420, 480, 640, 512,VO_SYSTEM_MODE_1080x1920x30P);
            while(1);

            break;
        case TD_ROTATION_270_DEGREE_CIF_420: 
            
            m_TdRotParam.rotMode = TD_ROTATION_270_DEGREE;                        
            m_TdRotParam.width = 352;
            m_TdRotParam.height = 288;
            m_TdRotParam.inStride = 352;
            m_TdRotParam.outStride = 320;             
            m_TdRotParam.addrSrcY = DUMP_ROTATION_ADDR_SRCY;
            m_TdRotParam.addrSrcUV = m_TdRotParam.addrSrcY + m_TdRotParam.inStride * m_TdRotParam.height;
            m_TdRotParam.addrDstY = DUMP_ROTATION_ADDR_DSTY;
            m_TdRotParam.addrDstUV = DUMP_ROTATION_ADDR_DSTUV;
            TD_TestRotation(&m_TdRotParam);
            //SimRotate(m_TdRotParam.rotMode,m_TdRotParam.width, m_TdRotParam.height,m_TdRotParam.inStride,m_TdRotParam.outStride, m_TdRotParam.addrSrcY,m_TdRotParam.addrSrcUV,m_TdRotParam.addrDstY,m_TdRotParam.addrDstUV);
            msleep(2000);
            
            //Switch axi to VO
            *(volatile MS_U32 *)0x924700cc = 0x0;
            //VO_Test2D_YUV(VO_VIDEO_LAYER_YUV_MODE_420, 288, 352, 320,VO_SYSTEM_MODE_1280x720x50P);
            while(1);

            break;
        case TD_ROTATION_270_DEGREE_QCIF_420: 
            m_TdRotParam.rotMode = TD_ROTATION_270_DEGREE;            
            m_TdRotParam.width = 176;
            m_TdRotParam.height = 144;
            m_TdRotParam.inStride = 176;
            m_TdRotParam.outStride = 192;             
            m_TdRotParam.addrSrcY = DUMP_ROTATION_ADDR_SRCY;
            m_TdRotParam.addrSrcUV = m_TdRotParam.addrSrcY + m_TdRotParam.inStride * m_TdRotParam.height;
            m_TdRotParam.addrDstY = DUMP_ROTATION_ADDR_DSTY;
            m_TdRotParam.addrDstUV = DUMP_ROTATION_ADDR_DSTUV;
            TD_TestRotation(&m_TdRotParam);
            msleep(2000);

            break;
        case TD_ROTATION_90_DEGREE_1080P_422:  
            m_TdRotParam.pxlFormat = TD_ROTATION_PIX_FORMAT_422SP;
            m_TdRotParam.width = 1080;
            m_TdRotParam.height = 1920;
            m_TdRotParam.inStride = 1080;
            m_TdRotParam.outStride = 1920;
            m_TdRotParam.addrSrcY = DUMP_ROTATION_ADDR_SRCY;
            m_TdRotParam.addrSrcUV = m_TdRotParam.addrSrcY + m_TdRotParam.inStride * m_TdRotParam.height;
            m_TdRotParam.addrDstY = DUMP_ROTATION_ADDR_DSTY;
            m_TdRotParam.addrDstUV = DUMP_ROTATION_ADDR_DSTUV;
            TD_TestRotation(&m_TdRotParam);
            msleep(2000);
                        
#ifndef CANAAN_ISP

            //Switch axi to VO
            *(volatile MS_U32 *)0x924700cc = 0x0;
#endif
            //VO_Test2D_YUV(VO_VIDEO_LAYER_YUV_MODE_422, 1920, 1080, 1920,VO_SYSTEM_MODE_1920x1080x30P);
            
            while(1);
            
            break;
        case TD_ROTATION_90_DEGREE_720P_422: //pass
            m_TdRotParam.pxlFormat = TD_ROTATION_PIX_FORMAT_422SP;            
            m_TdRotParam.width = 720;
            m_TdRotParam.height = 1280;
            m_TdRotParam.inStride = 720;
            m_TdRotParam.outStride = 1280;            
            m_TdRotParam.addrSrcY = DUMP_ROTATION_ADDR_SRCY;
            m_TdRotParam.addrSrcUV = m_TdRotParam.addrSrcY + m_TdRotParam.inStride * m_TdRotParam.height;
            m_TdRotParam.addrDstY = DUMP_ROTATION_ADDR_DSTY;
            m_TdRotParam.addrDstUV = DUMP_ROTATION_ADDR_DSTUV;
            m_TdRotParam.addrSrcV = 0;
            m_TdRotParam.addrDstV = 0;
            TD_TestRotation(&m_TdRotParam);
            msleep(2000);
#ifndef CANAAN_ISP
            
            //Switch axi to VO
            *(volatile MS_U32 *)0x924700cc = 0x0;
#endif

            //VO_Test2D_YUV(VO_VIDEO_LAYER_YUV_MODE_422, 1280, 720, 1280,VO_SYSTEM_MODE_1920x1080x30P);
            
            while(1);            
            break;
        case TD_ROTATION_90_DEGREE_VGA_422: 
            m_TdRotParam.pxlFormat = TD_ROTATION_PIX_FORMAT_422SP;            
            m_TdRotParam.width = 640;
            m_TdRotParam.height = 480;
            m_TdRotParam.inStride = 1280;
            m_TdRotParam.outStride = 512;            
            m_TdRotParam.addrSrcY = DUMP_ROTATION_ADDR_SRCY;
            m_TdRotParam.addrSrcUV = m_TdRotParam.addrSrcY + 1280*720;//m_TdRotParam.inStride * m_TdRotParam.height;
            m_TdRotParam.addrDstY = DUMP_ROTATION_ADDR_DSTY;
            m_TdRotParam.addrDstUV = DUMP_ROTATION_ADDR_DSTUV;
            TD_TestRotation(&m_TdRotParam);
            msleep(2000);
#ifndef CANAAN_ISP
            
            //Switch axi to VO
            *(volatile MS_U32 *)0x924700cc = 0x0;
#endif
            //VO_Test2D_YUV(VO_VIDEO_LAYER_YUV_MODE_422, 480, 640, 512,VO_SYSTEM_MODE_1920x1080x30P);
            while(1);            
            break;
        case TD_ROTATION_90_DEGREE_CIF_422: 
            m_TdRotParam.pxlFormat = TD_ROTATION_PIX_FORMAT_422SP;            
            m_TdRotParam.width = 352;
            m_TdRotParam.height = 288;
            m_TdRotParam.inStride = 352;
            m_TdRotParam.outStride = 320;             
            m_TdRotParam.addrSrcY = DUMP_ROTATION_ADDR_SRCY;
            m_TdRotParam.addrSrcUV = m_TdRotParam.addrSrcY + m_TdRotParam.inStride * m_TdRotParam.height;
            m_TdRotParam.addrDstY = DUMP_ROTATION_ADDR_DSTY;
            m_TdRotParam.addrDstUV = DUMP_ROTATION_ADDR_DSTUV;
            TD_TestRotation(&m_TdRotParam);
            msleep(2000);
                        

            //Switch axi to VO
            *(volatile MS_U32 *)0x924700cc = 0x0;
            //VO_Test2D_YUV(VO_VIDEO_LAYER_YUV_MODE_422, 288, 352, 320,VO_SYSTEM_MODE_1280x720x50P);
            
            while(1);
            
            break;
        case TD_ROTATION_90_DEGREE_QCIF_422:
            m_TdRotParam.pxlFormat = TD_ROTATION_PIX_FORMAT_422SP;            
            m_TdRotParam.width = 176;
            m_TdRotParam.height = 144;
            m_TdRotParam.inStride = 176;
            m_TdRotParam.outStride = 144;             
            m_TdRotParam.addrSrcY = DUMP_ROTATION_ADDR_SRCY;
            m_TdRotParam.addrSrcUV = m_TdRotParam.addrSrcY + m_TdRotParam.inStride * m_TdRotParam.height;
            m_TdRotParam.addrDstY = DUMP_ROTATION_ADDR_DSTY;
            m_TdRotParam.addrDstUV = DUMP_ROTATION_ADDR_DSTUV;
            TD_TestRotation(&m_TdRotParam);
            break;
        case TD_ROTATION_270_DEGREE_1080P_422:
            m_TdRotParam.pxlFormat = TD_ROTATION_PIX_FORMAT_422SP;            
            m_TdRotParam.rotMode = TD_ROTATION_270_DEGREE;            
            m_TdRotParam.width = 1080;
            m_TdRotParam.height = 1920;
            m_TdRotParam.inStride = 1080;
            m_TdRotParam.outStride = 1920;
            m_TdRotParam.addrSrcY = DUMP_ROTATION_ADDR_SRCY;
            m_TdRotParam.addrSrcUV = m_TdRotParam.addrSrcY + m_TdRotParam.inStride * m_TdRotParam.height;
            m_TdRotParam.addrDstY = DUMP_ROTATION_ADDR_DSTY;
            m_TdRotParam.addrDstUV = DUMP_ROTATION_ADDR_DSTUV;
            TD_TestRotation(&m_TdRotParam);
            break;
        case TD_ROTATION_270_DEGREE_720P_422: 
            m_TdRotParam.pxlFormat = TD_ROTATION_PIX_FORMAT_422SP;            
            m_TdRotParam.rotMode = TD_ROTATION_270_DEGREE;                        
            m_TdRotParam.width = 720;
            m_TdRotParam.height = 1280;
            m_TdRotParam.inStride = 720;
            m_TdRotParam.outStride = 1280;            
            m_TdRotParam.addrSrcY = DUMP_ROTATION_ADDR_SRCY;
            m_TdRotParam.addrSrcUV = m_TdRotParam.addrSrcY + m_TdRotParam.inStride * m_TdRotParam.height;
            m_TdRotParam.addrDstY = DUMP_ROTATION_ADDR_DSTY;
            m_TdRotParam.addrDstUV = DUMP_ROTATION_ADDR_DSTUV;
            TD_TestRotation(&m_TdRotParam);
            msleep(2000);
            //Switch axi to VO
            *(volatile MS_U32 *)0x924700cc = 0x0;
            //VO_Test2D_YUV(VO_VIDEO_LAYER_YUV_MODE_422, 1280, 720, 1280,VO_SYSTEM_MODE_1280x720x50P);
            
            while(1);            
            break;
        case TD_ROTATION_270_DEGREE_VGA_422:  
            m_TdRotParam.pxlFormat = TD_ROTATION_PIX_FORMAT_422SP;            
            m_TdRotParam.rotMode = TD_ROTATION_270_DEGREE;                        
            m_TdRotParam.width = 640;
            m_TdRotParam.height = 480;
            m_TdRotParam.inStride = 1280;
            m_TdRotParam.outStride = 512;            
            m_TdRotParam.addrSrcY = DUMP_ROTATION_ADDR_SRCY;
            m_TdRotParam.addrSrcUV = m_TdRotParam.addrSrcY + 720*1280;//m_TdRotParam.inStride * m_TdRotParam.height;
            m_TdRotParam.addrDstY = DUMP_ROTATION_ADDR_DSTY;
            m_TdRotParam.addrDstUV = DUMP_ROTATION_ADDR_DSTUV;
            TD_TestRotation(&m_TdRotParam);
            msleep(2000);
           //Switch axi to VO
#ifndef CANAAN_ISP
           *(volatile MS_U32 *)0x924700cc = 0x0;
#endif
            //VO_Test2D_YUV(VO_VIDEO_LAYER_YUV_MODE_422, 480, 640, 512,VO_SYSTEM_MODE_1080x1920x30P);
            while(1);            
            break;
        case TD_ROTATION_270_DEGREE_CIF_422:  
            m_TdRotParam.pxlFormat = TD_ROTATION_PIX_FORMAT_422SP;            
            m_TdRotParam.rotMode = TD_ROTATION_270_DEGREE;            
            m_TdRotParam.width = 352;
            m_TdRotParam.height = 288;
            m_TdRotParam.inStride = 352;
            m_TdRotParam.outStride = 320;             
            m_TdRotParam.addrSrcY = DUMP_ROTATION_ADDR_SRCY;
            m_TdRotParam.addrSrcUV = m_TdRotParam.addrSrcY + m_TdRotParam.inStride * m_TdRotParam.height;
            m_TdRotParam.addrDstY = DUMP_ROTATION_ADDR_DSTY;
            m_TdRotParam.addrDstUV = DUMP_ROTATION_ADDR_DSTUV;
            TD_TestRotation(&m_TdRotParam);
            msleep(2000);
                        

            //Switch axi to VO
            *(volatile MS_U32 *)0x924700cc = 0x0;
            //VO_Test2D_YUV(VO_VIDEO_LAYER_YUV_MODE_422, 288, 352, 320,VO_SYSTEM_MODE_1280x720x50P);

            while(1);
            break;
        case TD_ROTATION_270_DEGREE_QCIF_422:
            m_TdRotParam.pxlFormat = TD_ROTATION_PIX_FORMAT_422SP;            
            m_TdRotParam.rotMode = TD_ROTATION_270_DEGREE;            
            m_TdRotParam.width = 176;
            m_TdRotParam.height = 144;
            m_TdRotParam.inStride = 176;
            m_TdRotParam.outStride = 144;             
            m_TdRotParam.addrSrcY = DUMP_ROTATION_ADDR_SRCY;
            m_TdRotParam.addrSrcUV = m_TdRotParam.addrSrcY + m_TdRotParam.inStride * m_TdRotParam.height;
            m_TdRotParam.addrDstY = DUMP_ROTATION_ADDR_DSTY;
            m_TdRotParam.addrDstUV = DUMP_ROTATION_ADDR_DSTUV;
            TD_TestRotation(&m_TdRotParam);

            break;
        case TD_ROTATION_90_DEGREE_1080P_MONO:
            m_TdRotParam.pxlFormat = TD_ROTATION_PIX_FORMAT_MONO;
            m_TdRotParam.rotMode = TD_ROTATION_90_DEGREE;            
            m_TdRotParam.width = 1080;
            m_TdRotParam.height = 1920;
            m_TdRotParam.inStride = 1080;
            m_TdRotParam.outStride = 1920;
            m_TdRotParam.addrSrcY = DUMP_ROTATION_ADDR_SRCY;
            m_TdRotParam.addrSrcUV = m_TdRotParam.addrSrcY + m_TdRotParam.inStride * m_TdRotParam.height;
            m_TdRotParam.addrDstY = DUMP_ROTATION_ADDR_DSTY;
            m_TdRotParam.addrDstUV = DUMP_ROTATION_ADDR_DSTUV;
            TD_TestRotation(&m_TdRotParam);
            msleep(2000);

            //Switch axi to VO
            *(volatile MS_U32 *)0x924700cc = 0x0;
            ////VO_Test2D_YUV(VO_VIDEO_LAYER_YUV_MODE_420, 1920, 1080, 1920,VO_SYSTEM_MODE_1920x1080x30P);
            //VO_Test2D_RGB(1920,1080,1920,MONOCHROME_8BIT);

            break;
        case TD_ROTATION_270_DEGREE_1080P_MONO: //pass
            printf("TD_ROTATION_270_DEGREE_1080P_MONO test\n");
            m_TdRotParam.pxlFormat = TD_ROTATION_PIX_FORMAT_MONO;
            m_TdRotParam.rotMode = TD_ROTATION_270_DEGREE;
            m_TdRotParam.width = 1080;
            m_TdRotParam.height = 1920;
            m_TdRotParam.inStride = 1080;
            m_TdRotParam.outStride = 1920;
            m_TdRotParam.addrSrcY = DUMP_ROTATION_ADDR_SRCY;
            m_TdRotParam.addrSrcUV = m_TdRotParam.addrSrcY + m_TdRotParam.inStride * m_TdRotParam.height;
            m_TdRotParam.addrDstY = DUMP_ROTATION_ADDR_DSTY;
            m_TdRotParam.addrDstUV = DUMP_ROTATION_ADDR_DSTUV;
            TD_TestRotation(&m_TdRotParam);
            msleep(2000);
#ifndef CANAAN_ISP
            //Switch axi to VO
            *(volatile MS_U32 *)0x924700cc = 0x0;
#endif
            ////VO_Test2D_YUV(VO_VIDEO_LAYER_YUV_MODE_420, 1920, 1080, 1920,VO_SYSTEM_MODE_1920x1080x30P);
            //VO_Test2D_RGB(1920,1080,1920, MONOCHROME_8BIT, VO_SYSTEM_MODE_1920x1080x30P);
            while(1);
            break;
        case TD_ROTATION_90_DEGREE_CIF_RGB888: //pass
            //yuv444 planar format, need to dump memory to check!!!
            m_TdRotParam.pxlFormat = TD_ROTATION_PIX_FORMAT_RGB888;
            m_TdRotParam.rotMode = TD_ROTATION_90_DEGREE;            
            m_TdRotParam.width = 352;
            m_TdRotParam.height = 288;
            m_TdRotParam.inStride = 352;
            m_TdRotParam.outStride = 288;
            m_TdRotParam.addrSrcY = DUMP_ROTATION_ADDR_SRCY;
            m_TdRotParam.addrSrcUV = m_TdRotParam.addrSrcY + m_TdRotParam.inStride * m_TdRotParam.height;
            m_TdRotParam.addrSrcV = m_TdRotParam.addrSrcUV + m_TdRotParam.inStride * m_TdRotParam.height;
            m_TdRotParam.addrDstY = DUMP_ROTATION_ADDR_DSTY;
            m_TdRotParam.addrDstUV = DUMP_ROTATION_ADDR_DSTUV;
            m_TdRotParam.addrDstV = DUMP_ROTATION_ADDR_DSTV;
            TD_TestRotation(&m_TdRotParam);
            msleep(2000);

#ifndef CANAAN_ISP
            //Switch axi to VO
            *(volatile MS_U32 *)0x924700cc = 0x0;
#endif

            //VO_Test2D_YUV(VO_VIDEO_LAYER_YUV_MODE_422, 288, 352, 288,VO_SYSTEM_MODE_1920x1080x30P);
            while(1);
            

            break;
        case TD_ROTATION_270_DEGREE_CIF_RGB888: 
            //yuv444 planar format, need to dump memory to check!!!
            m_TdRotParam.pxlFormat = TD_ROTATION_PIX_FORMAT_RGB888;
            m_TdRotParam.rotMode = TD_ROTATION_270_DEGREE;            
            m_TdRotParam.width = 352;
            m_TdRotParam.height = 288;
            m_TdRotParam.inStride = 352;
            m_TdRotParam.outStride = 288;
            m_TdRotParam.addrSrcY = DUMP_ROTATION_ADDR_SRCY;
            m_TdRotParam.addrSrcUV = m_TdRotParam.addrSrcY + m_TdRotParam.inStride * m_TdRotParam.height;
            m_TdRotParam.addrSrcV = m_TdRotParam.addrSrcUV + m_TdRotParam.inStride * m_TdRotParam.height;
            m_TdRotParam.addrDstY = DUMP_ROTATION_ADDR_DSTY;
            m_TdRotParam.addrDstUV = DUMP_ROTATION_ADDR_DSTUV;
            m_TdRotParam.addrDstV = DUMP_ROTATION_ADDR_DSTV;
            TD_TestRotation(&m_TdRotParam);
            msleep(2000);
            status = MH_TD_get_RotSt();
            printf("ROT status 0x%x\n", status);
#ifndef CANAAN_ISP
            //Switch axi to VO
            *(volatile MS_U32 *)0x924700cc = 0x0;
#endif

            //VO_Test2D_YUV(VO_VIDEO_LAYER_YUV_MODE_422, 288, 352, 288,VO_SYSTEM_MODE_1920x1080x30P);
            while(1);


            break;
        case TD_ROTATION_90_DEGREE_1080P_BITSWAP_420:
            m_TdRotParam.pxlFormat = TD_ROTATION_PIX_FORMAT_420SP;
            m_TdRotParam.rotMode = TD_ROTATION_90_DEGREE;     
            m_TdRotParam.enOutSwap = 1;
            m_TdRotParam.width = 1080;
            m_TdRotParam.height = 1920;
            m_TdRotParam.inStride = 1080;
            m_TdRotParam.outStride = 1920;
            m_TdRotParam.addrSrcY = DUMP_ROTATION_ADDR_SRCY;
            m_TdRotParam.addrSrcUV = m_TdRotParam.addrSrcY + m_TdRotParam.inStride * m_TdRotParam.height;
            m_TdRotParam.addrDstY = DUMP_ROTATION_ADDR_DSTY;
            m_TdRotParam.addrDstUV = DUMP_ROTATION_ADDR_DSTUV;
            TD_TestRotation(&m_TdRotParam);

            break;
        case TD_ROTATION_90_DEGREE_1080P_ENDIANSWAP_420:
            m_TdRotParam.pxlFormat = TD_ROTATION_PIX_FORMAT_420SP;
            m_TdRotParam.rotMode = TD_ROTATION_90_DEGREE;     
            m_TdRotParam.enEndianSwap = 1;
            m_TdRotParam.width = 1080;
            m_TdRotParam.height = 1920;
            m_TdRotParam.inStride = 1080;
            m_TdRotParam.outStride = 1920;
            m_TdRotParam.addrSrcY = DUMP_ROTATION_ADDR_SRCY;
            m_TdRotParam.addrSrcUV = m_TdRotParam.addrSrcY + m_TdRotParam.inStride * m_TdRotParam.height;
            m_TdRotParam.addrDstY = DUMP_ROTATION_ADDR_DSTY;
            m_TdRotParam.addrDstUV = DUMP_ROTATION_ADDR_DSTUV;
            TD_TestRotation(&m_TdRotParam);

            break;
        case TD_ROTATION_90_DEGREE_STRIDE_TEST: //pass
            //The case can use main case 'ms_test_imx385_normal_2k' to get 320x240 source.
            m_TdRotParam.pxlFormat = TD_ROTATION_PIX_FORMAT_420SP;
            m_TdRotParam.rotMode = TD_ROTATION_90_DEGREE;     
            m_TdRotParam.width = 320;
            m_TdRotParam.height = 240;
            m_TdRotParam.inStride = 2048;
            m_TdRotParam.outStride = 256;
            m_TdRotParam.addrSrcY = ROTATE_TEST_ADDRESS_SRCY;
            m_TdRotParam.addrSrcUV = ROTATE_TEST_ADDRESS_SRCUV;//m_TdRotParam.addrSrcY + m_TdRotParam.inStride * m_TdRotParam.height;
            m_TdRotParam.addrDstY = DUMP_ROTATION_ADDR_DSTY;
            m_TdRotParam.addrDstUV = DUMP_ROTATION_ADDR_DSTUV;
            TD_TestRotation(&m_TdRotParam);
            msleep(2000);

#ifndef CANAAN_ISP
            //Switch axi to VO
            *(volatile MS_U32 *)0x924700cc = 0x0;
#endif

            //VO_Test2D_YUV(VO_VIDEO_LAYER_YUV_MODE_420, 240, 320, 256,VO_SYSTEM_MODE_1920x1080x30P);
            //while(1);

            msleep(5000);
            MS_U32 inStride = 320;
            MS_U32 outStride = 256;
            MS_U32 step = 64;
            while(1)
            {
                msleep(5000);
                inStride += step;
                outStride += step;
                if(inStride >= 4096)
                    inStride = 320;
                if(outStride >= 4096)
                    outStride = 256;
                //change ISP DS0 output stride 
                *(volatile unsigned int *)(ISP_2K_BASE_ADDR+4*0x31) = inStride << 16 | inStride;
                
                msleep(500);
                //rotate
                m_TdRotParam.inStride = inStride;
                m_TdRotParam.outStride = outStride;
                //m_TdRotParam.addrSrcUV = m_TdRotParam.addrSrcY + m_TdRotParam.inStride * m_TdRotParam.height;

#ifndef CANAAN_ISP
                
                //Switch axi to 2D
                *(volatile MS_U32 *)0x924700cc = 0x1;
#endif
                TD_TestRotation(&m_TdRotParam);
                msleep(2000);
                //change VO stride

#ifndef CANAAN_ISP
                //Switch axi to VO
                *(volatile MS_U32 *)0x924700cc = 0x0;
#endif

                //VO_Video_Layer_Stride_test(0, 0, 240, 320, outStride);
                //VO_Test2D_YUV(VO_VIDEO_LAYER_YUV_MODE_420, 240, 320, outStride,VO_SYSTEM_MODE_1280x720x50P);
                
                printf("input stride %d, output stride %d\n", inStride, outStride);
            }

            break;
        case TD_SCALER_1080P_420IN_YUV420OUT:
        {
            //temp_test();
//
            m_TdMixerParam.videoWidth = 1920;
            m_TdMixerParam.videoHeight = 1080;
            m_TdMixerParam.videoStride = 1920;
            m_TdMixerParam.videoOutWidth = 640;
            m_TdMixerParam.videoOutHeight = 480;
            
            m_TdMixerParam.yuvMode = TD_VIDEO_LAYER_YUV_MODE_420;
            m_TdMixerParam.endianModeY = TD_VIDEO_LAYER_Y_ENDIAN_MODE1;
            m_TdMixerParam.endianModeUV = TD_VIDEO_LAYER_UV_ENDIAN_MODE3;
            m_TdMixerParam.videoGlbAlpha = 255;
            m_TdMixerParam.videoAddrY = 0x01000000;//DUMP_ROTATION_ADDR_SRCY;
            m_TdMixerParam.videoAddrUV = 0x01000000/*DUMP_ROTATION_ADDR_SRCY*/ + 1080*1920;//m_TdMixerParam.videoHeight*m_TdMixerParam.videoStride;
            m_TdMixerParam.videoStartX = 0;
            m_TdMixerParam.videoStartY = 0;

            m_TdMixerParam.wbWidth = m_TdMixerParam.videoOutWidth;
            m_TdMixerParam.wbHeight = m_TdMixerParam.videoOutHeight;
            m_TdMixerParam.wbStride = m_TdMixerParam.wbWidth;
            m_TdMixerParam.wbRGBorYUV = 1; //yuv
            m_TdMixerParam.wbYUVInputFormat = 1; //420
            m_TdMixerParam.wbOutputFormat = 1; //420
            m_TdMixerParam.wbBaseAddrY = 0x02000000;//DUMP_MIXER_DST_ADDR_Y;
            m_TdMixerParam.wbBaseAddrUV = 0x02000000 + m_TdMixerParam.videoOutWidth * m_TdMixerParam.videoOutHeight;//DUMP_MIXER_DST_ADDR_UV;

            TD_TestScaler(&m_TdMixerParam);

             msleep(2000);

#ifndef CANAAN_ISP
            //Switch axi to VO
            *(volatile MS_U32 *)0x924700cc = 0x0;
#endif


            //VO_TestLayer_TD_MIXER_VOUT(VO_VIDEO_LAYER_YUV_MODE_420);
            //VO_Test2D_YUV(VO_VIDEO_LAYER_YUV_MODE_420, m_TdMixerParam.wbWidth, m_TdMixerParam.wbHeight, m_TdMixerParam.wbStride,VO_SYSTEM_MODE_1920x1080x30P);
            msleep(5000);
            //while(1);


            MS_U32 width = 1920;
            MS_U32 height = 1080;
            MS_U32 step = 64;
            while(1)
            {


                //resetVO();
                msleep(50);
#ifndef CANAAN_ISP
                
                //Switch axi to 2D
                *(volatile MS_U32 *)0x924700cc = 0x1;
#endif
                m_TdMixerParam.videoWidth = 1920;
                m_TdMixerParam.videoHeight = 1080;
                m_TdMixerParam.videoStride = 1920;
                m_TdMixerParam.videoOutWidth = width;
                m_TdMixerParam.videoOutHeight = height;

                m_TdMixerParam.yuvMode = TD_VIDEO_LAYER_YUV_MODE_420;
                m_TdMixerParam.endianModeY = TD_VIDEO_LAYER_Y_ENDIAN_MODE1;
                m_TdMixerParam.endianModeUV = TD_VIDEO_LAYER_UV_ENDIAN_MODE2;
                m_TdMixerParam.videoGlbAlpha = 255;
                m_TdMixerParam.videoAddrY = DUMP_ROTATION_ADDR_SRCY;
                m_TdMixerParam.videoAddrUV = DUMP_ROTATION_ADDR_SRCY + 1920*1080;//m_TdMixerParam.videoHeight*m_TdMixerParam.videoStride;
                m_TdMixerParam.videoStartX = 0;
                m_TdMixerParam.videoStartY = 0;

                m_TdMixerParam.wbWidth = m_TdMixerParam.videoOutWidth;
                m_TdMixerParam.wbHeight = m_TdMixerParam.videoOutHeight;
                m_TdMixerParam.wbStride = m_TdMixerParam.wbWidth;
                m_TdMixerParam.wbRGBorYUV = 1; //yuv
                m_TdMixerParam.wbYUVInputFormat = 1; //420
                m_TdMixerParam.wbOutputFormat = 1; //420
                m_TdMixerParam.wbBaseAddrY = DUMP_MIXER_DST_ADDR_Y;
                m_TdMixerParam.wbBaseAddrUV =DUMP_MIXER_DST_ADDR_Y + width * height; //DUMP_MIXER_DST_ADDR_UV;

                TD_TestScaler(&m_TdMixerParam);



                
                printf("w %d, h %d\n", width, height);

                            
                msleep(2000);

#ifndef CANAAN_ISP
                //Switch axi to VO
                *(volatile MS_U32 *)0x924700cc = 0x0;
#endif

                
                ////VO_Test2D_YUV(VO_VIDEO_LAYER_YUV_MODE_420, m_TdMixerParam.wbWidth, m_TdMixerParam.wbHeight, m_TdMixerParam.wbStride,VO_SYSTEM_MODE_1920x1080x30P);
                msleep(2000);
if(height == 1080)
    height = 1088;
                width -= step;
                height -= step ;
                
                if(width < 128)
                    width = 1280;
                if(height < 64)
                    height = 720;
            }
            break;
        }
        case TD_SCALER_1080P_420IN_YUV422OUT: //422 output pass
        {
            //temp_test();
//
            m_TdMixerParam.videoWidth = 1280;
            m_TdMixerParam.videoHeight = 720;
            m_TdMixerParam.videoStride = 1920;
            m_TdMixerParam.videoOutWidth = 320;
            m_TdMixerParam.videoOutHeight = 240;
            
            m_TdMixerParam.yuvMode = TD_VIDEO_LAYER_YUV_MODE_420;
            m_TdMixerParam.endianModeY = TD_VIDEO_LAYER_Y_ENDIAN_MODE1;
            m_TdMixerParam.endianModeUV = TD_VIDEO_LAYER_UV_ENDIAN_MODE3;
            m_TdMixerParam.videoGlbAlpha = 255;
            m_TdMixerParam.videoAddrY = DUMP_ROTATION_ADDR_SRCY;
            m_TdMixerParam.videoAddrUV = DUMP_ROTATION_ADDR_SRCY + 1080*1920;m_TdMixerParam.videoHeight*m_TdMixerParam.videoStride;
            m_TdMixerParam.videoStartX = 0;
            m_TdMixerParam.videoStartY = 0;

            m_TdMixerParam.wbWidth = m_TdMixerParam.videoOutWidth;
            m_TdMixerParam.wbHeight = m_TdMixerParam.videoOutHeight;
            m_TdMixerParam.wbStride = m_TdMixerParam.wbWidth;
            m_TdMixerParam.wbRGBorYUV = 1; //yuv
            m_TdMixerParam.wbYUVInputFormat = 1; //420
            m_TdMixerParam.wbOutputFormat = 0; //420
            m_TdMixerParam.wbBaseAddrY = DUMP_MIXER_DST_ADDR_Y;
            m_TdMixerParam.wbBaseAddrUV = DUMP_MIXER_DST_ADDR_UV;

            TD_TestScaler(&m_TdMixerParam);

             msleep(2000);

            //Switch axi to VO
            *(volatile MS_U32 *)0x924700cc = 0x0;

            //VO_TestLayer_TD_MIXER_VOUT(VO_VIDEO_LAYER_YUV_MODE_420);
            //VO_Test2D_YUV(VO_VIDEO_LAYER_YUV_MODE_422, m_TdMixerParam.wbWidth, m_TdMixerParam.wbHeight, m_TdMixerParam.wbStride,VO_SYSTEM_MODE_1280x720x50P);
            msleep(5000);
            //while(1);


            MS_U32 width = 1280;
            MS_U32 height = 720;
            MS_U32 step = 64;
            while(1)
            {


                resetVO();
                msleep(50);
                //Switch axi to 2D
                *(volatile MS_U32 *)0x924700cc = 0x1;

                m_TdMixerParam.videoWidth = 1280;
                m_TdMixerParam.videoHeight = 720;
                m_TdMixerParam.videoStride = 1920;
                m_TdMixerParam.videoOutWidth = width;
                m_TdMixerParam.videoOutHeight = height;

                m_TdMixerParam.yuvMode = TD_VIDEO_LAYER_YUV_MODE_420;
                m_TdMixerParam.endianModeY = TD_VIDEO_LAYER_Y_ENDIAN_MODE1;
                m_TdMixerParam.endianModeUV = TD_VIDEO_LAYER_UV_ENDIAN_MODE3;
                m_TdMixerParam.videoGlbAlpha = 255;
                m_TdMixerParam.videoAddrY = DUMP_ROTATION_ADDR_SRCY;
                m_TdMixerParam.videoAddrUV = DUMP_ROTATION_ADDR_SRCY + 1920*1080;//m_TdMixerParam.videoHeight*m_TdMixerParam.videoStride;
                m_TdMixerParam.videoStartX = 0;
                m_TdMixerParam.videoStartY = 0;

                m_TdMixerParam.wbWidth = m_TdMixerParam.videoOutWidth;
                m_TdMixerParam.wbHeight = m_TdMixerParam.videoOutHeight;
                m_TdMixerParam.wbStride = m_TdMixerParam.wbWidth;
                m_TdMixerParam.wbRGBorYUV = 1; //yuv
                m_TdMixerParam.wbYUVInputFormat = 1; //420
                m_TdMixerParam.wbOutputFormat = 0; //420
                m_TdMixerParam.wbBaseAddrY = DUMP_MIXER_DST_ADDR_Y;
                m_TdMixerParam.wbBaseAddrUV = DUMP_MIXER_DST_ADDR_UV;

                TD_TestScaler(&m_TdMixerParam);



                
printf("w %d, h %d\n", width, height);

                            
                msleep(2000);

                //Switch axi to VO
                *(volatile MS_U32 *)0x924700cc = 0x0;
                
                //VO_Test2D_YUV(VO_VIDEO_LAYER_YUV_MODE_422, m_TdMixerParam.wbWidth, m_TdMixerParam.wbHeight, m_TdMixerParam.wbStride,VO_SYSTEM_MODE_1280x720x50P);
                msleep(5000);

                width -= step;
                height -= step;
                if(width < 128)
                    width = 1280;
                if(height < 64)
                    height = 720;
            }
            break;
        }        
        case TD_SCALER_1080P_420IN_ARGBOUT:
        {
            m_TdMixerParam.videoWidth = 640;
            m_TdMixerParam.videoHeight = 480;
            m_TdMixerParam.videoStride = 640;
            m_TdMixerParam.videoOutWidth = 640;
            m_TdMixerParam.videoOutHeight = 480;
            
            m_TdMixerParam.yuvMode = TD_VIDEO_LAYER_YUV_MODE_420;
            m_TdMixerParam.endianModeY = TD_VIDEO_LAYER_Y_ENDIAN_MODE1;
            m_TdMixerParam.endianModeUV = TD_VIDEO_LAYER_UV_ENDIAN_MODE2;
            m_TdMixerParam.videoGlbAlpha = 255;
            m_TdMixerParam.videoAddrY = DUMP_ROTATION_ADDR_SRCY;
            m_TdMixerParam.videoAddrUV = DUMP_ROTATION_ADDR_SRCY + m_TdMixerParam.videoHeight*m_TdMixerParam.videoStride;
            m_TdMixerParam.videoStartX = 0;
            m_TdMixerParam.videoStartY = 0;

            m_TdMixerParam.wbWidth = m_TdMixerParam.videoOutWidth;
            m_TdMixerParam.wbHeight = m_TdMixerParam.videoOutHeight;
            m_TdMixerParam.wbStride = m_TdMixerParam.wbWidth * 3;
            m_TdMixerParam.wbRGBorYUV = 0; //yuv
            m_TdMixerParam.wbYUVInputFormat = 0; //420
            m_TdMixerParam.wbOutputFormat = 0; //420
            m_TdMixerParam.wbBaseAddrY = DUMP_MIXER_DST_ADDR_Y;
            m_TdMixerParam.wbBaseAddrUV = DUMP_MIXER_DST_ADDR_UV;
            m_TdMixerParam.wbPixWidth = 7;
            TD_TestScaler(&m_TdMixerParam);

             msleep(2000);

            //Switch axi to VO
            *(volatile MS_U32 *)0x924700cc = 0x0;

            //VO_TestLayer_TD_MIXER_VOUT(VO_VIDEO_LAYER_YUV_MODE_420);
            ////VO_Test2D_YUV(VO_VIDEO_LAYER_YUV_MODE_422, m_TdMixerParam.wbWidth, m_TdMixerParam.wbHeight, m_TdMixerParam.wbStride,VO_SYSTEM_MODE_1280x720x50P);
            ////VO_Test2D_RGB(640, 480, 640*3, RGB_24BIT, VO_SYSTEM_MODE_1280x720x50P);

            msleep(5000);
            while(1);


            msleep(2000);


            //Switch axi to VO
            *(volatile MS_U32 *)0x924700cc = 0x0;

            ////VO_Test2D_YUV(VO_VIDEO_LAYER_YUV_MODE_420, m_TdSclParam.outWidth, m_TdSclParam.outHeight, m_TdSclParam.wbStride,VO_SYSTEM_MODE_1920x1080x30P);

            VO_TestLayer_TD_MIXER_VOUT(TD_VIDEO_LAYER_YUV_MODE_420);

            ////VO_Test2D_RGB(640, 480, 640*4, RGB_32BIT);
            msleep(5000);
            while(1);

            MS_U32 width = 1920;
            MS_U32 height = 1080;
            MS_U32 step = 32;
            while(1)
            {
                width -= step;
                height -= step;
                if(width < 128)
                    width = 1920;
                if(height < 64)
                    height = 1080;

                m_TdSclParam.outHeight = width;
                m_TdSclParam.outHeight = height;
                
                TD_TestScaler(&m_TdSclParam);
                //VO_Test2D_RGB(width, height, 1920*4, RGB_32BIT);

            }
            
            break;
        }      
        case TD_SCALER_1080P_420IN_SEPARATE_RGBOUT:
        {
            //don't support separate r/g/b!!!
            break;
        }        
        case TD_SCALER_1080P_422IN_YUV422OUT:
        {
            //temp_test();
//
            m_TdMixerParam.videoWidth = 1280;
            m_TdMixerParam.videoHeight = 720;
            m_TdMixerParam.videoStride = 1280;
            m_TdMixerParam.videoOutWidth = 336;
            m_TdMixerParam.videoOutHeight = 192;
            
            m_TdMixerParam.yuvMode = TD_VIDEO_LAYER_YUV_MODE_422;
            m_TdMixerParam.endianModeY = TD_VIDEO_LAYER_Y_ENDIAN_MODE1;
            m_TdMixerParam.endianModeUV = TD_VIDEO_LAYER_UV_ENDIAN_MODE3;
            m_TdMixerParam.videoGlbAlpha = 255;
            m_TdMixerParam.videoAddrY = DUMP_ROTATION_ADDR_SRCY;
            m_TdMixerParam.videoAddrUV = DUMP_ROTATION_ADDR_SRCY + m_TdMixerParam.videoHeight*m_TdMixerParam.videoStride;
            m_TdMixerParam.videoStartX = 0;
            m_TdMixerParam.videoStartY = 0;

            m_TdMixerParam.wbWidth = m_TdMixerParam.videoOutWidth;
            m_TdMixerParam.wbHeight = m_TdMixerParam.videoOutHeight;
            m_TdMixerParam.wbStride = m_TdMixerParam.wbWidth;
            m_TdMixerParam.wbRGBorYUV = 1; //yuv
            m_TdMixerParam.wbYUVInputFormat = 0; //420
            m_TdMixerParam.wbOutputFormat = 0; //420
            m_TdMixerParam.wbBaseAddrY = DUMP_MIXER_DST_ADDR_Y;
            m_TdMixerParam.wbBaseAddrUV = DUMP_MIXER_DST_ADDR_UV;

            TD_TestScaler(&m_TdMixerParam);

             msleep(2000);

            //Switch axi to VO
            *(volatile MS_U32 *)0x924700cc = 0x0;

            //VO_TestLayer_TD_MIXER_VOUT(VO_VIDEO_LAYER_YUV_MODE_420);
            //VO_Test2D_YUV(VO_VIDEO_LAYER_YUV_MODE_422, m_TdMixerParam.wbWidth, m_TdMixerParam.wbHeight, m_TdMixerParam.wbStride,VO_SYSTEM_MODE_1280x720x50P);
            msleep(5000);
            while(1);


            MS_U32 width = 720;
            MS_U32 height = 576;
            MS_U32 step = 64;
            while(1)
            {


                resetVO();
                msleep(50);
                //Switch axi to 2D
                *(volatile MS_U32 *)0x924700cc = 0x1;

                m_TdMixerParam.videoWidth = 1280;
                m_TdMixerParam.videoHeight = 720;
                m_TdMixerParam.videoStride = 1280;
                m_TdMixerParam.videoOutWidth = width;
                m_TdMixerParam.videoOutHeight = height;

                m_TdMixerParam.yuvMode = TD_VIDEO_LAYER_YUV_MODE_422;
                m_TdMixerParam.endianModeY = TD_VIDEO_LAYER_Y_ENDIAN_MODE1;
                m_TdMixerParam.endianModeUV = TD_VIDEO_LAYER_UV_ENDIAN_MODE3;
                m_TdMixerParam.videoGlbAlpha = 255;
                m_TdMixerParam.videoAddrY = DUMP_ROTATION_ADDR_SRCY;
                m_TdMixerParam.videoAddrUV = DUMP_ROTATION_ADDR_SRCY + m_TdMixerParam.videoHeight*m_TdMixerParam.videoStride;
                m_TdMixerParam.videoStartX = 0;
                m_TdMixerParam.videoStartY = 0;

                m_TdMixerParam.wbWidth = m_TdMixerParam.videoOutWidth;
                m_TdMixerParam.wbHeight = m_TdMixerParam.videoOutHeight;
                m_TdMixerParam.wbStride = m_TdMixerParam.wbWidth;
                m_TdMixerParam.wbRGBorYUV = 1; //yuv
                m_TdMixerParam.wbYUVInputFormat = 0; //420
                m_TdMixerParam.wbOutputFormat = 0; //420
                m_TdMixerParam.wbBaseAddrY = DUMP_MIXER_DST_ADDR_Y;
                m_TdMixerParam.wbBaseAddrUV = DUMP_MIXER_DST_ADDR_UV;

                TD_TestScaler(&m_TdMixerParam);



                
printf("w %d, h %d\n", width, height);

                            
                msleep(2000);

                //Switch axi to VO
                *(volatile MS_U32 *)0x924700cc = 0x0;
                
                //VO_Test2D_YUV(VO_VIDEO_LAYER_YUV_MODE_422, m_TdMixerParam.wbWidth, m_TdMixerParam.wbHeight, m_TdMixerParam.wbStride,VO_SYSTEM_MODE_1280x720x50P);
                msleep(5000);

                width -= step;
                height -= step;
                if(width < 128 )
                    width = 720;
                if(height < 64)
                    height = 576;
            }
            break;
        }        
        case TD_SCALER_1080P_422IN_YUV420OUT:  //some res has issue!!!
        {
            //temp_test();
//
            m_TdMixerParam.videoWidth = 1280;
            m_TdMixerParam.videoHeight = 720;
            m_TdMixerParam.videoStride = 1280;
            m_TdMixerParam.videoOutWidth = 336;
            m_TdMixerParam.videoOutHeight = 192;
            
            m_TdMixerParam.yuvMode = TD_VIDEO_LAYER_YUV_MODE_422;
            m_TdMixerParam.endianModeY = TD_VIDEO_LAYER_Y_ENDIAN_MODE1;
            m_TdMixerParam.endianModeUV = TD_VIDEO_LAYER_UV_ENDIAN_MODE3;
            m_TdMixerParam.videoGlbAlpha = 255;
            m_TdMixerParam.videoAddrY = DUMP_ROTATION_ADDR_SRCY;
            m_TdMixerParam.videoAddrUV = DUMP_ROTATION_ADDR_SRCY + m_TdMixerParam.videoHeight*m_TdMixerParam.videoStride;
            m_TdMixerParam.videoStartX = 0;
            m_TdMixerParam.videoStartY = 0;

            m_TdMixerParam.wbWidth = m_TdMixerParam.videoOutWidth;
            m_TdMixerParam.wbHeight = m_TdMixerParam.videoOutHeight;
            m_TdMixerParam.wbStride = 352;//m_TdMixerParam.wbWidth;
            m_TdMixerParam.wbRGBorYUV = 1; //yuv
            m_TdMixerParam.wbYUVInputFormat = 1; //420
            m_TdMixerParam.wbOutputFormat = 1; //420
            m_TdMixerParam.wbBaseAddrY = DUMP_MIXER_DST_ADDR_Y;
            m_TdMixerParam.wbBaseAddrUV = DUMP_MIXER_DST_ADDR_UV;

            TD_TestScaler(&m_TdMixerParam);

             msleep(2000);

            //Switch axi to VO
            *(volatile MS_U32 *)0x924700cc = 0x0;

            //VO_TestLayer_TD_MIXER_VOUT(VO_VIDEO_LAYER_YUV_MODE_420);
            //VO_Test2D_YUV(VO_VIDEO_LAYER_YUV_MODE_420, m_TdMixerParam.wbWidth, m_TdMixerParam.wbHeight, m_TdMixerParam.wbStride,VO_SYSTEM_MODE_1280x720x50P);
            msleep(5000);
            while(1);


            MS_U32 width = 720;
            MS_U32 height = 576;
            MS_U32 step = 64;
            while(1)
            {


                resetVO();
                msleep(50);
                //Switch axi to 2D
                *(volatile MS_U32 *)0x924700cc = 0x1;

                m_TdMixerParam.videoWidth = 1280;
                m_TdMixerParam.videoHeight = 720;
                m_TdMixerParam.videoStride = 1280;
                m_TdMixerParam.videoOutWidth = width;
                m_TdMixerParam.videoOutHeight = height;

                m_TdMixerParam.yuvMode = TD_VIDEO_LAYER_YUV_MODE_422;
                m_TdMixerParam.endianModeY = TD_VIDEO_LAYER_Y_ENDIAN_MODE1;
                m_TdMixerParam.endianModeUV = TD_VIDEO_LAYER_UV_ENDIAN_MODE3;
                m_TdMixerParam.videoGlbAlpha = 255;
                m_TdMixerParam.videoAddrY = DUMP_ROTATION_ADDR_SRCY;
                m_TdMixerParam.videoAddrUV = DUMP_ROTATION_ADDR_SRCY + m_TdMixerParam.videoHeight*m_TdMixerParam.videoStride;
                m_TdMixerParam.videoStartX = 0;
                m_TdMixerParam.videoStartY = 0;

                m_TdMixerParam.wbWidth = m_TdMixerParam.videoOutWidth;
                m_TdMixerParam.wbHeight = m_TdMixerParam.videoOutHeight;
                m_TdMixerParam.wbStride = m_TdMixerParam.wbWidth;
                m_TdMixerParam.wbRGBorYUV = 1; //yuv
                m_TdMixerParam.wbYUVInputFormat = 1; //420
                m_TdMixerParam.wbOutputFormat = 1; //420
                m_TdMixerParam.wbBaseAddrY = DUMP_MIXER_DST_ADDR_Y;
                m_TdMixerParam.wbBaseAddrUV = DUMP_MIXER_DST_ADDR_UV;

                TD_TestScaler(&m_TdMixerParam);



                
printf("w %d, h %d\n", width, height);

                            
                msleep(2000);

                //Switch axi to VO
                *(volatile MS_U32 *)0x924700cc = 0x0;
                
                //VO_Test2D_YUV(VO_VIDEO_LAYER_YUV_MODE_420, m_TdMixerParam.wbWidth, m_TdMixerParam.wbHeight, m_TdMixerParam.wbStride,VO_SYSTEM_MODE_1280x720x50P);
                msleep(5000);

                width -= step;
                height -= step;
                if(width < 128 )
                    width = 720;
                if(height < 64)
                    height = 576;
            }
            break;
        }        
        case TD_SCALER_1080P_422IN_ARGBOUT: //failed yet!!!
        {
            m_TdSclParam.inWidth = 1920;
            m_TdSclParam.inHeight = 1080;
            m_TdSclParam.outHeight = 1920;
            m_TdSclParam.outHeight = 1080;
            m_TdSclParam.inStride = 1920;
            m_TdSclParam.yuvMode = TD_VIDEO_LAYER_YUV_MODE_422;
            m_TdSclParam.wbRGBorYUV = 0; //rgb
            m_TdSclParam.wbYUVInputFormat = 0; //422
            m_TdSclParam.wbOutputFormat = 1; //argb
            m_TdSclParam.wbBaseAddrY = DUMP_ROTATION_ADDR_DSTY;
            m_TdSclParam.wbBaseAddrUV = DUMP_ROTATION_ADDR_DSTUV;
            m_TdSclParam.wbStride = 1920*4;
            TD_TestScaler(&m_TdSclParam);

            MS_U32 width = 1920;
            MS_U32 height = 1080;
            MS_U32 step = 32;
            while(1)
            {
                width -= step;
                height -= step;
                if(width < 128)
                    width = 1920;
                if(height < 64)
                    height = 1080;

                m_TdSclParam.outWidth = width;
                m_TdSclParam.outHeight = height;
                
                TD_TestScaler(&m_TdSclParam);
                //VO_Test2D_RGB(width, height, 1920*4, RGB_32BIT);
                   
            }
            
            break;
        }        
        case TD_SCALER_1080P_422IN_SEPARATE_RGBOUT:
        {
            //don't know how to output separate r/g/b yet!!!
            break;
        }        
       
        case TD_MIXER_420_ARGB8888_GLOBAL_ALPHA_TRAVERSAL:
        {
            //download 1920x1080 nv12 video source to ddr DUMP_MIXER_ADDR_VIDEO_Y
            //download 320x240 argb8888 osd data to ddr DUMP_MIXER_ADDR_OSD
            m_TdMixerParam.videoWidth = 640;
            m_TdMixerParam.videoHeight = 480;
            m_TdMixerParam.videoStride = 640;
            m_TdMixerParam.yuvMode = TD_VIDEO_LAYER_YUV_MODE_420;
            m_TdMixerParam.endianModeY = TD_VIDEO_LAYER_Y_ENDIAN_MODE1;
            m_TdMixerParam.endianModeUV = TD_VIDEO_LAYER_UV_ENDIAN_MODE3;
            m_TdMixerParam.videoGlbAlpha = 255;
            m_TdMixerParam.videoAddrY = DUMP_MIXER_ADDR_VIDEO_Y;
            m_TdMixerParam.videoAddrUV = DUMP_MIXER_ADDR_VIDEO_Y + 640*480;
            m_TdMixerParam.videoStartX = 0;
            m_TdMixerParam.videoStartY = 0;
            m_TdMixerParam.osdWidth = 320;
            m_TdMixerParam.osdHeight = 240;
            m_TdMixerParam.osdStride = 320*4;
            m_TdMixerParam.osdType = TD_RGB_32BIT;
            m_TdMixerParam.alphaType = TD_FIXED_VALUE;
            m_TdMixerParam.dmaMap = TD_ORIGINAL_ORDER;
            m_TdMixerParam.revRGB = 1;
            m_TdMixerParam.osdGlbAlpha = 255;
            m_TdMixerParam.osdAddr = DUMP_MIXER_ADDR_OSD;
            m_TdMixerParam.wbWidth = 640;
            m_TdMixerParam.wbHeight = 480;
            m_TdMixerParam.wbStride = 640;
            m_TdMixerParam.wbRGBorYUV = 1; //yuv
            m_TdMixerParam.wbYUVInputFormat = 1; //420
            m_TdMixerParam.wbOutputFormat = 1; //420
            m_TdMixerParam.wbBaseAddrY = DUMP_MIXER_DST_ADDR_Y;
            m_TdMixerParam.wbBaseAddrUV = DUMP_MIXER_DST_ADDR_UV;
            m_TdMixerParam.osdStartX = 100;
            m_TdMixerParam.osdStartY = 100;
            TD_TestMixer(&m_TdMixerParam);
            ////VO_Test2D_YUV(VO_VIDEO_LAYER_YUV_MODE_420, 1920, 1080, 1920,VO_SYSTEM_MODE_1920x1080x30P);

            
            msleep(2000);
            #if 1
        
           //Switch axi to VO
           *(volatile MS_U32 *)0x924700cc = 0x0;
        
           //VO_TestLayer_TD_MIXER_VOUT(VO_VIDEO_LAYER_YUV_MODE_420);
           //VO_Test2D_YUV(VO_VIDEO_LAYER_YUV_MODE_420, 640, 480, 640,VO_SYSTEM_MODE_1920x1080x30P);
           msleep(5000);
           //while(1);

            MS_S32 alpha = 255;
            while(1)
            {
                msleep(3000);
                alpha-=20;
                if(alpha < 0)
                    alpha = 255;
                m_TdMixerParam.videoGlbAlpha = alpha;
                m_TdMixerParam.osdGlbAlpha = alpha;

                resetVO();
                
                //Switch axi to 2D
                *(volatile MS_U32 *)0x924700cc = 0x1;
                
                TD_TestMixer(&m_TdMixerParam);
                printf("new alpha %d\n", alpha);
                msleep(1000);
                
                //Switch axi to VO
                *(volatile MS_U32 *)0x924700cc = 0x0;
                //VO_TestReset();
                   //VO_Test2D_YUV(VO_VIDEO_LAYER_YUV_MODE_420, 640, 480, 640,VO_SYSTEM_MODE_1920x1080x30P);

            }
            #endif
            break;
        }
        case TD_MIXER_422_RGB888_SEPARATE_ALPHA:
        {
            //download 640x480 422 video source to ddr DUMP_MIXER_ADDR_VIDEO_Y
            //download 640x480 rgb888 osd data to ddr DUMP_MIXER_ADDR_OSD
            //download alpha data to ddr DUMP_MIXER_ADDR_ALPHA
            m_TdMixerParam.videoWidth = 640;
            m_TdMixerParam.videoHeight = 480;
            m_TdMixerParam.videoStride = 640;
            m_TdMixerParam.videoStartX = 0;
            m_TdMixerParam.videoStartY = 0;
            m_TdMixerParam.yuvMode = TD_VIDEO_LAYER_YUV_MODE_420;//to change to 422 source
            m_TdMixerParam.endianModeY = TD_VIDEO_LAYER_Y_ENDIAN_MODE1;
            m_TdMixerParam.endianModeUV = TD_VIDEO_LAYER_UV_ENDIAN_MODE3;
            m_TdMixerParam.videoGlbAlpha = 255;
            m_TdMixerParam.videoAddrY = DUMP_MIXER_ADDR_VIDEO_Y;
            m_TdMixerParam.videoAddrUV = DUMP_MIXER_ADDR_VIDEO_Y + 640*480;
            m_TdMixerParam.osdWidth = 640;
            m_TdMixerParam.osdHeight = 480;
            m_TdMixerParam.osdStride = 640*3;
            m_TdMixerParam.osdStartX = 1280;
            m_TdMixerParam.osdStartY = 0;
            m_TdMixerParam.osdType = TD_RGB_24BIT;
            m_TdMixerParam.alphaType = TD_L2_ALPHA_ADDR;
            m_TdMixerParam.dmaMap = TD_ORIGINAL_ORDER;
            m_TdMixerParam.revRGB = 1;
            m_TdMixerParam.osdGlbAlpha = 255;
            m_TdMixerParam.osdAddr = DUMP_MIXER_ADDR_OSD;
            m_TdMixerParam.osdAlphaAddr = DUMP_MIXER_ADDR_ALPHA;
            m_TdMixerParam.wbWidth = 1920;
            m_TdMixerParam.wbHeight = 1080;
            m_TdMixerParam.wbStride = 1920;
            m_TdMixerParam.wbRGBorYUV = 1; //yuv
            m_TdMixerParam.wbYUVInputFormat = 1; //420
            m_TdMixerParam.wbOutputFormat = 1; //420
            m_TdMixerParam.wbBaseAddrY = DUMP_MIXER_DST_ADDR_Y;
            m_TdMixerParam.wbBaseAddrUV = DUMP_MIXER_DST_ADDR_UV;
            TD_TestMixer(&m_TdMixerParam);
            msleep(2000);

            //Switch axi to VO
            *(volatile MS_U32 *)0x924700cc = 0x0;
            
            //VO_TestLayer_TD_MIXER_VOUT(VO_VIDEO_LAYER_YUV_MODE_420);
            //VO_Test2D_YUV(VO_VIDEO_LAYER_YUV_MODE_420, 1920, 1080, 1920,VO_SYSTEM_MODE_1920x1080x30P);
            msleep(5000);

            MS_S32 step = 32;

            while(1)
            {
                msleep(2000);
                m_TdMixerParam.videoStartX += step;
                m_TdMixerParam.videoStartY += step;

                if(m_TdMixerParam.videoStartX > 1280)
                    m_TdMixerParam.videoStartX = 0;
                if(m_TdMixerParam.videoStartY > 600)
                    m_TdMixerParam.videoStartY = 0;

                m_TdMixerParam.osdStartX -= step;
                m_TdMixerParam.osdStartY += step;

                if(m_TdMixerParam.osdStartX < 0)
                    m_TdMixerParam.osdStartX = 1280;
                if(m_TdMixerParam.osdStartY > 600)
                    m_TdMixerParam.osdStartY = 0;


                resetVO();
                
                //Switch axi to 2D
                *(volatile MS_U32 *)0x924700cc = 0x1;                
                TD_TestMixer(&m_TdMixerParam);

                
                msleep(1000);
                
                //Switch axi to VO
                *(volatile MS_U32 *)0x924700cc = 0x0;
                
                //VO_Test2D_YUV(VO_VIDEO_LAYER_YUV_MODE_420, 1920, 1080, 1920,VO_SYSTEM_MODE_1920x1080x30P);

            }
            break;
        }
        case TD_MIXER_420_ARGB4444_INTEGRATED_ALPHA:
        {
            //download 1920x1080 nv12 video source to ddr DUMP_MIXER_ADDR_VIDEO_Y
            //download cif argb4444 osd data to ddr DUMP_MIXER_ADDR_OSD
            m_TdMixerParam.videoWidth = 640;
            m_TdMixerParam.videoHeight = 480;
            m_TdMixerParam.videoStride = 640;
            m_TdMixerParam.videoStartX = 0;
            m_TdMixerParam.videoStartY = 0;
            m_TdMixerParam.yuvMode = TD_VIDEO_LAYER_YUV_MODE_420;
            m_TdMixerParam.endianModeY = TD_VIDEO_LAYER_Y_ENDIAN_MODE1;
            m_TdMixerParam.endianModeUV = TD_VIDEO_LAYER_UV_ENDIAN_MODE3;
            m_TdMixerParam.videoGlbAlpha = 255;
            m_TdMixerParam.videoAddrY = DUMP_MIXER_ADDR_VIDEO_Y;
            m_TdMixerParam.videoAddrUV = DUMP_MIXER_ADDR_VIDEO_Y + 640*480;
            m_TdMixerParam.osdWidth = 352;
            m_TdMixerParam.osdHeight = 288;
            m_TdMixerParam.osdStride = 720;
            m_TdMixerParam.osdStartX = 0;
            m_TdMixerParam.osdStartY = 0;
            m_TdMixerParam.osdType = TD_RGB_4444;
            m_TdMixerParam.alphaType = TD_INTERVAL_A;
            m_TdMixerParam.dmaMap = TD_ORIGINAL_ORDER;
            m_TdMixerParam.revRGB = 1;
            m_TdMixerParam.osdGlbAlpha = 255;
            m_TdMixerParam.osdAddr = DUMP_MIXER_ADDR_OSD;
            m_TdMixerParam.osdAlphaAddr = DUMP_MIXER_ADDR_ALPHA;
            m_TdMixerParam.wbWidth = 1920;
            m_TdMixerParam.wbHeight = 1080;
            m_TdMixerParam.wbStride = 1920;
            m_TdMixerParam.wbRGBorYUV = 1; //yuv
            m_TdMixerParam.wbYUVInputFormat = 1; //420
            m_TdMixerParam.wbOutputFormat = 1; //420
            m_TdMixerParam.wbBaseAddrY = DUMP_MIXER_DST_ADDR_Y;
            m_TdMixerParam.wbBaseAddrUV = DUMP_MIXER_DST_ADDR_UV;
            TD_TestMixer(&m_TdMixerParam);
            msleep(2000);
            
             //Switch axi to VO
             *(volatile MS_U32 *)0x924700cc = 0x0;
             
             //VO_TestLayer_TD_MIXER_VOUT(VO_VIDEO_LAYER_YUV_MODE_420);
             //VO_Test2D_YUV(VO_VIDEO_LAYER_YUV_MODE_420, 1920, 1080, 1920,VO_SYSTEM_MODE_1920x1080x30P);
             msleep(5000);
            while(1);

            break;
        }       
        case TD_MIXER_420_RGB565_ENDIANSWAP_BGR:
        {
            //download 1920x1080 nv12 video source to ddr DUMP_MIXER_ADDR_VIDEO_Y
            //download cif rgb565 endian swap bgr osd data to ddr DUMP_MIXER_ADDR_OSD
            m_TdMixerParam.videoWidth = 640;
            m_TdMixerParam.videoHeight = 480;
            m_TdMixerParam.videoStride = 640;
            m_TdMixerParam.videoStartX = 0;
            m_TdMixerParam.videoStartY = 0;
            m_TdMixerParam.yuvMode = TD_VIDEO_LAYER_YUV_MODE_420;
            m_TdMixerParam.endianModeY = TD_VIDEO_LAYER_Y_ENDIAN_MODE1;
            m_TdMixerParam.endianModeUV = TD_VIDEO_LAYER_UV_ENDIAN_MODE3;
            m_TdMixerParam.videoGlbAlpha = 255;
            m_TdMixerParam.videoAddrY = DUMP_MIXER_ADDR_VIDEO_Y;
            m_TdMixerParam.videoAddrUV = DUMP_MIXER_ADDR_VIDEO_Y + 640*480;
            m_TdMixerParam.osdWidth = 352;
            m_TdMixerParam.osdHeight = 288;
            m_TdMixerParam.osdStride = 720;
            m_TdMixerParam.osdStartX = 0;
            m_TdMixerParam.osdStartY = 0;
            m_TdMixerParam.osdType = TD_RGB_16BIT;
            m_TdMixerParam.alphaType = TD_FIXED_VALUE;
            m_TdMixerParam.dmaMap = TD_LITTLE_ENDIAN;
            m_TdMixerParam.revRGB = 1;
            m_TdMixerParam.osdGlbAlpha = 255;
            m_TdMixerParam.osdAddr = DUMP_MIXER_ADDR_OSD;
            m_TdMixerParam.osdAlphaAddr = DUMP_MIXER_ADDR_ALPHA;
            m_TdMixerParam.wbWidth = 1920;
            m_TdMixerParam.wbHeight = 1080;
            m_TdMixerParam.wbStride = 1920;
            m_TdMixerParam.wbRGBorYUV = 1; //yuv
            m_TdMixerParam.wbYUVInputFormat = 1; //420
            m_TdMixerParam.wbOutputFormat = 1; //420
            m_TdMixerParam.wbBaseAddrY = DUMP_MIXER_DST_ADDR_Y;
            m_TdMixerParam.wbBaseAddrUV = DUMP_MIXER_DST_ADDR_UV;
            TD_TestMixer(&m_TdMixerParam);
            msleep(2000);
            
            //Switch axi to VO
            *(volatile MS_U32 *)0x924700cc = 0x0;

            //VO_TestLayer_TD_MIXER_VOUT(VO_VIDEO_LAYER_YUV_MODE_420);
            //VO_Test2D_YUV(VO_VIDEO_LAYER_YUV_MODE_420, 1920, 1080, 1920,VO_SYSTEM_MODE_1920x1080x30P);
            msleep(5000);
            while(1);


            break;
        }        
        case TD_MIXER_420_ARGB1555_TWOBYTEENDIAN_RGB:
        {
            //download 1920x1080 nv12 video source to ddr DUMP_MIXER_ADDR_VIDEO_Y
            //download cif argb1555 two byte swap osd data to ddr DUMP_MIXER_ADDR_OSD
            m_TdMixerParam.videoWidth = 640;
            m_TdMixerParam.videoHeight = 480;
            m_TdMixerParam.videoStride = 640;
            m_TdMixerParam.videoStartX = 0;
            m_TdMixerParam.videoStartY = 0;
            m_TdMixerParam.yuvMode = TD_VIDEO_LAYER_YUV_MODE_420;
            m_TdMixerParam.endianModeY = TD_VIDEO_LAYER_Y_ENDIAN_MODE1;
            m_TdMixerParam.endianModeUV = TD_VIDEO_LAYER_UV_ENDIAN_MODE3;
            m_TdMixerParam.videoGlbAlpha = 255;
            m_TdMixerParam.videoAddrY = DUMP_MIXER_ADDR_VIDEO_Y;
            m_TdMixerParam.videoAddrUV = DUMP_MIXER_ADDR_VIDEO_Y + 640*480;
            m_TdMixerParam.osdWidth = 352;
            m_TdMixerParam.osdHeight = 288;
            m_TdMixerParam.osdStride = 720;
            m_TdMixerParam.osdStartX = 0;
            m_TdMixerParam.osdStartY = 0;
            m_TdMixerParam.osdType = TD_RGB_1555;
            m_TdMixerParam.alphaType = TD_FIXED_VALUE;
            m_TdMixerParam.dmaMap = TD_TWO_BIT_ENDIAN;
            m_TdMixerParam.revRGB = 0;
            m_TdMixerParam.osdGlbAlpha = 255;
            m_TdMixerParam.osdAddr = DUMP_MIXER_ADDR_OSD;
            m_TdMixerParam.osdAlphaAddr = DUMP_MIXER_ADDR_ALPHA;
            m_TdMixerParam.wbWidth = 1920;
            m_TdMixerParam.wbHeight = 1080;
            m_TdMixerParam.wbStride = 1920;
            m_TdMixerParam.wbRGBorYUV = 1; //yuv
            m_TdMixerParam.wbYUVInputFormat = 1; //420
            m_TdMixerParam.wbOutputFormat = 1; //420
            m_TdMixerParam.wbBaseAddrY = DUMP_MIXER_DST_ADDR_Y;
            m_TdMixerParam.wbBaseAddrUV = DUMP_MIXER_DST_ADDR_UV;
            TD_TestMixer(&m_TdMixerParam);
            msleep(2000);
            
            //Switch axi to VO
            *(volatile MS_U32 *)0x924700cc = 0x0;

            //VO_TestLayer_TD_MIXER_VOUT(VO_VIDEO_LAYER_YUV_MODE_420);
            //VO_Test2D_YUV(VO_VIDEO_LAYER_YUV_MODE_420, 1920, 1080, 1920,VO_SYSTEM_MODE_1920x1080x30P);
            msleep(5000);
            while(1);


            break;
        }       
        case TD_MIXER_420_MONO8_RANDOM_SIZE:
        {
            //download 1920x1080 nv12 video source to ddr DUMP_MIXER_ADDR_VIDEO_Y
            //download 1920x1080 Y data to ddr DUMP_MIXER_ADDR_OSD
            m_TdMixerParam.videoWidth = 640;
            m_TdMixerParam.videoHeight = 480;
            m_TdMixerParam.videoStride = 640;
            m_TdMixerParam.videoStartX = 0;
            m_TdMixerParam.videoStartY = 0;
            m_TdMixerParam.yuvMode = TD_VIDEO_LAYER_YUV_MODE_420;
            m_TdMixerParam.endianModeY = TD_VIDEO_LAYER_Y_ENDIAN_MODE1;
            m_TdMixerParam.endianModeUV = TD_VIDEO_LAYER_UV_ENDIAN_MODE3;
            m_TdMixerParam.videoGlbAlpha = 255;
            m_TdMixerParam.videoAddrY = DUMP_MIXER_ADDR_VIDEO_Y;
            m_TdMixerParam.videoAddrUV = DUMP_MIXER_ADDR_VIDEO_Y + 640*480;
            m_TdMixerParam.osdWidth = 1920;
            m_TdMixerParam.osdHeight = 1080;
            m_TdMixerParam.osdStride = 1920;
            m_TdMixerParam.osdStartX = 0;
            m_TdMixerParam.osdStartY = 0;
            m_TdMixerParam.osdType = TD_MONOCHROME_8BIT;
            m_TdMixerParam.alphaType = TD_FIXED_VALUE;
            m_TdMixerParam.dmaMap = TD_ORIGINAL_ORDER;
            m_TdMixerParam.revRGB = 0;
            m_TdMixerParam.osdGlbAlpha = 255;
            m_TdMixerParam.osdAddr = DUMP_MIXER_ADDR_OSD;
            m_TdMixerParam.osdAlphaAddr = DUMP_MIXER_ADDR_ALPHA;
            m_TdMixerParam.wbWidth = 1920;
            m_TdMixerParam.wbHeight = 1080;
            m_TdMixerParam.wbStride = 1920;
            m_TdMixerParam.wbRGBorYUV = 1; //yuv
            m_TdMixerParam.wbYUVInputFormat = 1; //420
            m_TdMixerParam.wbOutputFormat = 1; //420
            m_TdMixerParam.wbBaseAddrY = DUMP_MIXER_DST_ADDR_Y;
            m_TdMixerParam.wbBaseAddrUV = DUMP_MIXER_DST_ADDR_UV;
            TD_TestMixer(&m_TdMixerParam);
            msleep(2000);
            
            //Switch axi to VO
            *(volatile MS_U32 *)0x924700cc = 0x0;

            //VO_TestLayer_TD_MIXER_VOUT(VO_VIDEO_LAYER_YUV_MODE_420);
            //VO_Test2D_YUV(VO_VIDEO_LAYER_YUV_MODE_420, 1920, 1080, 1920,VO_SYSTEM_MODE_1920x1080x30P);

            MS_U32 w,h;
            while(1)
            {
                msleep(5000);

                w = random() % 1920;
                h = random() % 1080;
                printf("Random width %d, height %d\n", w,h);

                resetVO();
                
                //Switch axi to 2D
                *(volatile MS_U32 *)0x924700cc = 0x1;                

                m_TdMixerParam.osdWidth = w;
                m_TdMixerParam.osdHeight = h;
                TD_TestMixer(&m_TdMixerParam);
                printf("osd %d x %d\n", w,h);
                            
                msleep(1000);
                
                //Switch axi to VO
                *(volatile MS_U32 *)0x924700cc = 0x0;
                
                //VO_TestLayer_TD_MIXER_VOUT(VO_VIDEO_LAYER_YUV_MODE_420);
                //VO_Test2D_YUV(VO_VIDEO_LAYER_YUV_MODE_420, 1920, 1080, 1920,VO_SYSTEM_MODE_1920x1080x30P);
            }
            break;
        }        
        case TD_MIXER_420_STRIDE:
        {
            //USE DS0 output as TD video input, DS2 rgb output as TD osd input
            m_TdMixerParam.videoWidth = 640;
            m_TdMixerParam.videoHeight = 480;
            m_TdMixerParam.videoStride = 2048;
            m_TdMixerParam.videoStartX = 0;
            m_TdMixerParam.videoStartY = 0;
            m_TdMixerParam.yuvMode = TD_VIDEO_LAYER_YUV_MODE_420;
            m_TdMixerParam.endianModeY = TD_VIDEO_LAYER_Y_ENDIAN_MODE1;
            m_TdMixerParam.endianModeUV = TD_VIDEO_LAYER_UV_ENDIAN_MODE3;
            m_TdMixerParam.videoGlbAlpha = 255;
            m_TdMixerParam.videoAddrY = ISP_BUF_DS0_Y;
            m_TdMixerParam.videoAddrUV = ISP_BUF_DS0_UV;
            m_TdMixerParam.osdWidth = 320;
            m_TdMixerParam.osdHeight = 240;
            m_TdMixerParam.osdStride = 2048;
            m_TdMixerParam.osdStartX = 800;
            m_TdMixerParam.osdStartY = 0;
            m_TdMixerParam.osdType = TD_RGB_32BIT;
            m_TdMixerParam.alphaType = TD_FIXED_VALUE;
            m_TdMixerParam.dmaMap = TD_LITTLE_ENDIAN;
            m_TdMixerParam.revRGB = 0;
            m_TdMixerParam.osdGlbAlpha = 255;
            m_TdMixerParam.osdAddr = ISP_BUF_DS2_R;
            m_TdMixerParam.osdAlphaAddr = 0;
            m_TdMixerParam.wbWidth = 1920;
            m_TdMixerParam.wbHeight = 1080;
            m_TdMixerParam.wbStride = 1920;
            m_TdMixerParam.wbRGBorYUV = 1; //yuv
            m_TdMixerParam.wbYUVInputFormat = 1; //420
            m_TdMixerParam.wbOutputFormat = 1; //420
            m_TdMixerParam.wbBaseAddrY = DUMP_MIXER_DST_ADDR_Y;
            m_TdMixerParam.wbBaseAddrUV = DUMP_MIXER_DST_ADDR_UV;
            TD_TestMixer(&m_TdMixerParam);
            //VO_Test2D_YUV(VO_VIDEO_LAYER_YUV_MODE_420, 1920, 1080, 1920,VO_SYSTEM_MODE_1920x1080x30P);

            msleep(2000);
            
            //Switch axi to VO
            *(volatile MS_U32 *)0x924700cc = 0x0;

            //VO_TestLayer_TD_MIXER_VOUT(VO_VIDEO_LAYER_YUV_MODE_420);
            //VO_Test2D_YUV(VO_VIDEO_LAYER_YUV_MODE_420, 1920, 1080, 1920,VO_SYSTEM_MODE_1920x1080x30P);
while(1);
            MS_U32 videoStride = 640;
            MS_U32 osdStride = 1280;
            MS_U32 wbStride = 1920;
            while(1)
            {
                msleep(2000);
                videoStride += 32;
                osdStride += 32;
                wbStride += 32;
                if(videoStride > 4096)
                    videoStride = 640;
                if(osdStride > 4096)
                    osdStride = 1280;
                if(wbStride > 4096)
                    wbStride = 1920;
                
                printf("videoStride %d, osdStride %d, wbStride %d\n", videoStride,osdStride,wbStride);

                //change ds0/2 stride
                *(volatile unsigned int *)(0x92420000+0xC4) = videoStride << 16 | videoStride;
                *(volatile unsigned int *)(0x92420000+0xF4) = osdStride << 16 | osdStride;

                //change td stride
                m_TdMixerParam.videoStride = videoStride;
                m_TdMixerParam.osdStride = osdStride;
                m_TdMixerParam.wbStride = wbStride;
                
                TD_TestMixer(&m_TdMixerParam);
                //change vo stride
                //VO_Test2D_YUV(VO_VIDEO_LAYER_YUV_MODE_420, 1920, 1080, wbStride,VO_SYSTEM_MODE_1920x1080x30P);


                            
            }
            break;
        }        
        default:
            break;
                
    }



}




void SimRotate(MS_U8 rotMode,MS_U32 width, MS_U32 height, MS_S32 inPitch, MS_S32 outPitch, MS_U8 *pSrcY, MS_U8 *pSrcUV, MS_U8 *pDstY, MS_U8 *pDstUV)
{
printf("sim rotation start\n");
    MS_U8 *pReadY = (MS_U8 *)pSrcY;
    MS_U16 *pReadUV = (MS_U16 *)pSrcUV;
    MS_U8 *pWriteY = (MS_U8 *)pDstY;
    MS_U16 *pWriteUV = (MS_U16 *)pDstUV;
    int i=0,j=0;
    int uvWidth = (height+1)/2;
    int uvHeight = (width+1)/2;
    int yWidth = height;
    int yHeight = width;

    if(rotMode == 0) //90 degree
    {
        printf("sim rotation 90 degree\n");
        for(i=0;i<yHeight;i++)
        {
            for(j=yWidth-1;j>=(yWidth - outPitch);j--)
            {
                *pWriteY++ = *(pReadY+j*inPitch+i);
            }
    //        for(j=yWidth;j<outPitch;j++)
    //            *pWriteY ++ = *(pReadY+(yWidth -1 -j)*inPitch+i);

        }
        printf("y roation finished\n");
        for(i=0;i<uvHeight;i++)
        {
            for(j=uvWidth -1;j>=(uvWidth - outPitch/2);j--)
            {
                *pWriteUV++ = *(pReadUV+j*inPitch/2+i);

            }
    //        for(j=uvWidth;j<outPitch/2;j++)
    //            *pWriteUV++ = *(pReadUV+(uvWidth-1-j)*inPitch/2+i);

        }
    }
    else
    {
        //270 degree
        printf("sim rotation 270 degree\n");

        for(i=yHeight -1;i>=0;i--)
        {
            for(j=0;j<(outPitch);j++)
            {
                *pWriteY++ = *(pReadY+j*inPitch+i);

            }
        }
        for(i=uvHeight-1;i>=0;i--)
        {
            for(j=0;j<(outPitch/2);j++)
            {
                *pWriteUV++ = *(pReadUV+j*inPitch/2+i);
    
            }
    
        }


    }
    cache_flush();
    printf("sim rotation done!\n");
}














