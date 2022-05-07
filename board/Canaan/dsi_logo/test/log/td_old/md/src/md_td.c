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
** \file       md_td.c
**
** \brief      td driver layer for operate hw
**
**           (C) Shanghai MicroSharp Co.,Ltd 2013 - 2019
**
** \attention  THIS SAMPLE CODE IS PROVIDED AS IS SAHNGHAI MICROSHARP
**               ACCEPTS NO RESPONSIBILITY OR LIABILITY   
**               FOR ANY ERRORS OR OMMISSIONS.
**
**\version   md_td.c  ,v 1.0 2019/09/16  Kite.Su Exp $
**
**************************************************************************
*/


#include <md_td.h>
#include <td_Coeff.h>
#include <td_types.h>
#include <td_table_config.h>
#include <core_v5.h>
#include <stdio.h>
#include <k510.h>
#include <cache.h>
#include <interrupt.h>
#include <ext_ctl_hw.h>
#include <td_define.h>


static MS_U32 m_XzoneStart = 0;
static MS_U32 m_YzoneStart = 0;
static MS_U32 m_XzoneStop  = 0;
static MS_U32 m_YzoneStop  = 0;

static MS_U32 m_TdDriverIsInitialized = 0;
static MD_TD_RotationHandleT m_RotationHandle;


static MS_U32 m_MixerDriverIsInitialized = 0;
static MD_TD_MixerHandleT m_MixerHandles;


static MS_U32  td_done = 0;

MS_U32 MS_API_TD_WrapCfgDone(void)
{
    MH_TD_set_WrapCfg_Done(1);
    MH_TD_set_WrapCfg(0x00020001); 
    return MS_OK;
}


uint64_t g_start_cycle = 0;
static MS_U32 TD_intr(void *ctx)
{
   
    td_done ++;
    uint64_t cycle = read_cycle();
    printf("!!!!!!!!!!!!!!!!!!TD_intr irq done timer   = %u!, interval %u\n",cycle, cycle - g_start_cycle);
    

    

    if(MH_TD_get_WrapInt_RotationDone() == 1)
    {
        printf("TD_intr MH_TD_get_RotSt_FrameEnd   = %u!\n",MH_TD_get_RotSt_FrameEnd());

        printf("TD_intr MH_TD_get_RotSt_Done   = %u!\n",MH_TD_get_RotSt_Done());
      
        printf("TD_intr RotSt_Cycle   = %u!\n",MH_TD_get_RotSt_CycleCnt());
        MH_TD_set_WrapInt_RotationDone(1);
        printf("TMH_TD_get_WrapInt_RotationDone\n");
    }
    if(MH_TD_get_WrapInt_RotationTimeOut() == 1)
    {
        MH_TD_set_WrapInt_RotationTimeOut(1);
        printf("MH_TD_get_WrapInt_RotationTimeOut\n");
    }
    if(MH_TD_get_WrapInt_MixerDone() == 1)
    {
        printf("IN!!!TD_intr int  val = 0x%x,td_done = %d\n",(*(volatile MS_U32 *)(TD_BASE_ADDR + 0x7c)),td_done);
        MH_TD_set_WrapInt_MixerDone(1);
        printf("MH_TD_set_WrapInt_MixerDone\n\n\n\n\n\n\n\n\n\n\n");
    }

    printf("TD_intr int  val clear = 0x%x\n",(*(volatile MS_U32 *)(TD_BASE_ADDR + 0x7c)));
     



    
    return 0;
}


MS_U32 MS_API_TD_WrapInit(void)
{
    MS_U32 ErrCode = MS_OK;
#ifdef CANAAN_ISP
    int irq_2d = IRQN_TWOD_INT_INTERRUPT;
#else
    int irq_2d = IRQN_ISP_INTERRUPT;
#endif
    if( m_TdDriverIsInitialized == 0 )
    {   
        MH_TD_set_WrapSwRst(0x3ff);
        MH_TD_set_WrapClkEn(0xffffffff);
        MH_TD_set_WrapDmaArbMode(0);//w/r use priority mode
         
        MH_TD_set_WrapDmaWeightWR0(0x01010101);
        MH_TD_set_WrapDmaWeightWR1(0x01010101);
        MH_TD_set_WrapDmaWeightRD0(0x01010101);
        MH_TD_set_WrapDmaWeightRD1(0x01010101);
        MH_TD_set_WrapDmaPriorityWR(0x01234567);
        MH_TD_set_WrapDmaPriorityRD(0x01234567);
        MH_TD_set_WrapDmaIdWR(0x76543210);
        MH_TD_set_WrapDmaIdRD(0x76543210);
        MS_API_TD_WrapCfgDone();

        MH_TD_set_WrapInt(0xFF0000);
        
         printf("pMS_API_TD_WrapInitr\n");
        #if 1
     set_csr(NDS_MIE, MIP_MEIP);
        /* Enable interrupts in general. */
    set_csr(NDS_MSTATUS, MSTATUS_MIE);

    if(plic_set_priority(irq_2d, 1) )
    {
          printf("plic priority err\n");
    }
    plic_irq_register(irq_2d, TD_intr, NULL);
    if(plic_irq_enable(irq_2d))
      {
              printf("plic enable err\n");
       }
   #endif
        m_TdDriverIsInitialized = 1;
    }
    else
    {
        ErrCode = MS_ERR_TD_ALREADY_INIT;
    }
    return(ErrCode);
}




#if 1
#endif


MS_U32 MS_API_TD_RotationFrameStart(void)
{
    MS_U32 ErrCode = MS_OK;
    if( m_TdDriverIsInitialized == 0 )
    {
        ErrCode = MS_ERR_TD_NOT_INIT;
        return ErrCode;
    }
    MH_TD_set_RotCmd_FrameStart(1);
    MH_TD_set_RotCmd_FrameStart(0);

    return ErrCode;
}

MS_U32 MS_API_TD_RotationFrameStartAF(void)
{
    MS_U32 ErrCode = MS_OK;
    if( m_TdDriverIsInitialized == 0 )
    {
        ErrCode = MS_ERR_TD_NOT_INIT;
        return ErrCode;
    }
    MH_TD_set_RotCmd_FrameStart(0);

    return ErrCode;
}

MS_SYS_HandleT MS_API_TD_RotationOpen(const MD_TD_RotationParmT* RotationOpenParm,
                                   MS_U32* errorCodePtr)
{
    MS_U32 ErrCode = MS_OK;
    MD_TD_RotationHandleT* ReturnPtr = NULL;

    if(m_TdDriverIsInitialized == 0)
    {
       ErrCode = MS_ERR_TD_NOT_INIT;
       if(errorCodePtr != 0)
       {
           *errorCodePtr = ErrCode;
       }
       return((MS_SYS_HandleT)ReturnPtr);
    }
       
    if(RotationOpenParm == NULL || errorCodePtr == NULL)
    {
        ErrCode = MS_ERR_TD_ILLEGAL_PARAM;
        if(errorCodePtr != NULL)
        {
           *errorCodePtr = ErrCode;
        }
        return((MS_SYS_HandleT)ReturnPtr);
    }

    memcpy(&m_RotationHandle.RotationParm,RotationOpenParm,sizeof(MD_TD_RotationParmT));
    
    

    if(m_RotationHandle.RotationParm.RotationMode <= TD_ROTATION_270_DEGREE)
    {
        MH_TD_set_RotCtl_Mode(m_RotationHandle.RotationParm.RotationMode);    
    }
    else
    {
        ErrCode = MS_ERR_TD_ILLEGAL_PARAM;
        if(errorCodePtr != NULL)
        {
            *errorCodePtr = ErrCode;
        }
        return((MS_SYS_HandleT)ReturnPtr);
    }
    
    if(m_RotationHandle.RotationParm.RotationPixelFormat <= TD_ROTATION_PIX_FORMAT_RGB888)
    {
        MH_TD_set_RotCtl_PixFormat(m_RotationHandle.RotationParm.RotationPixelFormat);    
    }
    else
    {
        ErrCode = MS_ERR_TD_ILLEGAL_PARAM;
        if(errorCodePtr != NULL)
        {
            *errorCodePtr = ErrCode;
        }
        return((MS_SYS_HandleT)ReturnPtr);
    }

    MH_TD_set_RotCtl_InSwap(m_RotationHandle.RotationParm.InSwapEn);
    MH_TD_set_RotCtl_EndiaInEn(m_RotationHandle.RotationParm.BigLittleInEndia);
    MH_TD_set_RotCtl_OutSwap(m_RotationHandle.RotationParm.OutSwapEn);
    MH_TD_set_RotCtl_EndiaOutEn(m_RotationHandle.RotationParm.BigLittleOutEndia);
    MH_TD_set_RotCtl_OtMaxRd(m_RotationHandle.RotationParm.OtMaxRD);
    MH_TD_set_RotCtl_OtMaxWr(m_RotationHandle.RotationParm.OtMaxWR);
    MH_TD_set_RotTimeOut_Val(m_RotationHandle.RotationParm.DoneTimeOut);


    if(m_RotationHandle.RotationParm.ActiveVer != 0 && m_RotationHandle.RotationParm.ActiveHor != 0 )
    {
        MH_TD_set_RotImageSizeActive_Ver(m_RotationHandle.RotationParm.ActiveVer - 1);
        MH_TD_set_RotImageSizeActive_Hor(m_RotationHandle.RotationParm.ActiveHor - 1);

    }
    else
    {
        ErrCode = MS_ERR_TD_ILLEGAL_PARAM;
        if(errorCodePtr != NULL)
        {
            *errorCodePtr = ErrCode;
        }
        return((MS_SYS_HandleT)ReturnPtr);
    }
    
    if(m_RotationHandle.RotationParm.BaseAddrSrcY != 0 && m_RotationHandle.RotationParm.BaseAddrDesY != 0)
    {
        MH_TD_set_RotAddrBaseYSrc(m_RotationHandle.RotationParm.BaseAddrSrcY);
        MH_TD_set_RotAddrBaseYDes(m_RotationHandle.RotationParm.BaseAddrDesY);

    }
    else
    {
        ErrCode = MS_ERR_TD_ILLEGAL_PARAM;
        if(errorCodePtr != NULL)
        {
            *errorCodePtr = ErrCode;
        }
        return((MS_SYS_HandleT)ReturnPtr);
    }

    MH_TD_set_RotAddrBaseUSrc(m_RotationHandle.RotationParm.BaseAddrSrcU);
    MH_TD_set_RotAddrBaseVSrc(m_RotationHandle.RotationParm.BaseAddrSrcV);

    MH_TD_set_RotAddrBaseUDes(m_RotationHandle.RotationParm.BaseAddrDesU);
    MH_TD_set_RotAddrBaseVDes(m_RotationHandle.RotationParm.BaseAddrDesV);

    if(m_RotationHandle.RotationParm.ActiveHor <= m_RotationHandle.RotationParm.StrideSrcY)
    {
        MH_TD_set_RotStrideY_Src(m_RotationHandle.RotationParm.StrideSrcY);
        MH_TD_set_RotStrideY_Des(m_RotationHandle.RotationParm.StrideDesY);

    }
    else
    {
        ErrCode = MS_ERR_TD_ILLEGAL_PARAM;
        if(errorCodePtr != NULL)
        {
           *errorCodePtr = ErrCode;
        }
        return((MS_SYS_HandleT)ReturnPtr);
    }

    MH_TD_set_RotStrideU_Src(m_RotationHandle.RotationParm.StrideSrcU);
    MH_TD_set_RotStrideU_Des(m_RotationHandle.RotationParm.StrideDesU);
    MH_TD_set_RotStrideV_Src(m_RotationHandle.RotationParm.StrideSrcV);
    MH_TD_set_RotStrideV_Des(m_RotationHandle.RotationParm.StrideDesV);

    
   
    if(errorCodePtr != NULL)
    {
        *errorCodePtr = ErrCode;
    }

    ReturnPtr = &m_RotationHandle;
    return((MS_SYS_HandleT)ReturnPtr);

}




MS_U32 MS_API_TD_Layer0Line0BDCtl(bool LimtEnabled,MS_U8 Outstand)
{
   MS_U32 ErrCode = MS_OK;
   
   if( 1 == LimtEnabled )
   {    
       if( 0x1f > Outstand )
       {
          MH_TD_set_Layer0Line0BdCtl_LimitEn(1);
          MH_TD_set_Layer0Line0BdCtl_OutStand(Outstand);
       }
       else
       {
           ErrCode = MS_ERR_TD_ILLEGAL_PARAM;
           return ErrCode;
       }
     
   }
   else if( 0 == LimtEnabled )
   {
       MH_TD_set_Layer0Line0BdCtl_LimitEn(0);
   }
   else
   {
       ErrCode = MS_ERR_TD_ILLEGAL_PARAM;
       return ErrCode;
   }
   return ErrCode;
}



MS_U32 MS_API_TD_Layer0Line1BDCtl(bool LimtEnabled,MS_U8 Outstand)
{
   MS_U32 ErrCode = MS_OK;
   
   if( 1 == LimtEnabled )
   {
      
       if( 0x1f > Outstand )
       {
          MH_TD_set_Layer0Line1BdCtl_LimitEn(1);
          MH_TD_set_Layer0Line1BdCtl_OutStand(Outstand);

       }
       else
       {
           ErrCode = MS_ERR_TD_ILLEGAL_PARAM;
           return ErrCode;
       }
     
   }
   else if( 0 == LimtEnabled )
   {
       MH_TD_set_Layer0Line1BdCtl_LimitEn(0);
   }
   else
   {
       ErrCode = MS_ERR_TD_ILLEGAL_PARAM;
       return ErrCode;
   }
   return ErrCode;
}



MS_U32 MS_API_TD_Layer0Line2BDCtl(bool LimtEnabled,MS_U8 Outstand)
{
   MS_U32 ErrCode = MS_OK;
   
   if( 1 == LimtEnabled )
   {
      
       if( 0x1f > Outstand )
       {
          MH_TD_set_Layer0Line2BdCtl_LimitEn(1);
          MH_TD_set_Layer0Line2BdCtl_OutStand(Outstand);

       }
       else
       {
           ErrCode = MS_ERR_TD_ILLEGAL_PARAM;
           return ErrCode;
       }
     
   }
   else if( 0 == LimtEnabled )
   {
       MH_TD_set_Layer0Line2BdCtl_LimitEn(0);
   }
   else
   {
       ErrCode = MS_ERR_TD_ILLEGAL_PARAM;
       return ErrCode;
   }
   return ErrCode;
}

MS_U32 MS_API_TD_Layer0Line3BDCtl(bool LimtEnabled,MS_U8 Outstand)
{
   MS_U32 ErrCode = MS_OK;
   
   if( 1 == LimtEnabled )
   {
      
       if( 0x1f > Outstand )
       {
          MH_TD_set_Layer0Line3BdCtl_LimitEn(1);
          MH_TD_set_Layer0Line3BdCtl_OutStand(Outstand);

       }
       else
       {
           ErrCode = MS_ERR_TD_ILLEGAL_PARAM;
           return ErrCode;
       }
     
   }
   else if( 0 == LimtEnabled )
   {
       MH_TD_set_Layer0Line3BdCtl_LimitEn(0);
   }
   else
   {
       ErrCode = MS_ERR_TD_ILLEGAL_PARAM;
       return ErrCode;
   }
   return ErrCode;
}







MS_U32 MS_API_TD_Layer4BDCtl(bool LimtEnabled,MS_U8 Outstand)
{
   MS_U32 ErrCode = MS_OK;
   
   if( 1 == LimtEnabled )
   {
      
       if( 0x1f > Outstand )
       {
          MH_TD_set_Layer4BdCtl_LimitEn(1);
          MH_TD_set_Layer4BdCtl_OutStand(Outstand);

       }
       else
       {
           ErrCode = MS_ERR_TD_ILLEGAL_PARAM;
           return ErrCode;
       }
     
   }
   else if( 0 == LimtEnabled )
   {
       MH_TD_set_Layer4BdCtl_LimitEn(0);
   }
   else
   {
       ErrCode = MS_ERR_TD_ILLEGAL_PARAM;
       return ErrCode;
   }
   return ErrCode;
}



/*! 
**************************************************************************** 
** [Brief] 
**
** Set Back Ground as R G B component
** 
** [Syntax]
** 
** MS_U32 MS_API_TD_SetBackgroundComponentRGB( MS_U8 Y,MS_U8 U,MS_U8 V)
**
** [Parameter]
** 
**  Rcomponent
**  Gcomponent
**  Bcomponent

** [Return]
** 
** #MS_OK                         On success. 
** #MS_ERR_TD_ILLEGAL_PARAM       err Byte size for init
***************************************************************************** 
*/ 

MS_U32 MS_API_TD_SetBackgroundComponentRGB( MS_U8 Y,MS_U8 U,MS_U8 V )
{
   MS_U32 ErrCode = MS_OK;
   if(m_MixerDriverIsInitialized)
   {
       MH_TD_set_DispBackGroud_Y(Y);
       MH_TD_set_DispBackGroud_U(U);
       MH_TD_set_DispBackGroud_V(V);
   }
   else
   {
       ErrCode = MS_ERR_TD_NOT_INIT;
   }
   return ErrCode;
}


MS_U32 MS_API_TD_SetBackgroundZone( MS_U16 HorStart,MS_U16 VerStart,MS_U16 HorStop,MS_U16 VerStop )
{
   MS_U32 ErrCode = MS_OK;
   if(m_MixerDriverIsInitialized)
   {
       if(HorStart >= HorStop || VerStart >= VerStop)
       {
           ErrCode = MS_ERR_TD_ILLEGAL_PARAM;
           return ErrCode;
       }
       m_XzoneStart = HorStart;
       m_XzoneStop  = HorStop;
       MH_TD_set_DispXZone_Start(HorStart);
       MH_TD_set_DispXZone_Stop(HorStop-1);
       m_YzoneStart = VerStart;
       m_YzoneStop  = VerStop;
       MH_TD_set_DispYZone_Start(VerStart);
       MH_TD_set_DispYZone_Stop(VerStop-1);
   }
   else
   {
       ErrCode = MS_ERR_TD_NOT_INIT;
   }
   return ErrCode;
}


MS_U32 MS_API_TD_SetVideoLayer0Positon( MS_U32 HorStart,MS_U32 VerStart,MS_U32 HorStop,MS_U32 VerStop)
{
   MS_U32 ErrCode = MS_OK;   

   if(m_MixerDriverIsInitialized)
   {
       if(HorStart >= HorStop || VerStart >= VerStop)
       {
           ErrCode = MS_ERR_TD_ILLEGAL_PARAM;
           return ErrCode;
       }
       if(!m_MixerHandles.MixerParamater.VideoLayerParam[TD_VIDEO_LAYER0].LayerEnable)
       {
           ErrCode = MS_ERR_TD_LAYER_NOT_ENABLE;
           return ErrCode;             
       }
       if(HorStart < m_XzoneStart || VerStart < m_YzoneStart || HorStop > m_XzoneStop || VerStop > m_YzoneStop)
       {
           //Layers position can't beyond the border of background zone
           ErrCode = MS_ERR_TD_ILLEGAL_PARAM;
           return ErrCode;   
       }

       MH_TD_set_Layer0XCtl_Start(HorStart);
       MH_TD_set_Layer0XCtl_Stop(HorStop - 1);
       MH_TD_set_Layer0YCtl_Start(VerStart);
       MH_TD_set_Layer0YCtl_Stop( VerStop -1 );
   }
   else
   {
       ErrCode = MS_ERR_TD_NOT_INIT;
   }
   return ErrCode;
}




MS_U32 MS_API_TD_SetOsdLayer0Positon( MS_U32 HorStart,MS_U32 VerStart,MS_U32 HorStop,MS_U32 VerStop)
{
   MS_U32 ErrCode = MS_OK;   
   if(m_MixerDriverIsInitialized)
   {

   
       if(HorStart >= HorStop || VerStart >= VerStop)
       {
           ErrCode = MS_ERR_TD_ILLEGAL_PARAM;
           return ErrCode;
       }
       if(!m_MixerHandles.MixerParamater.OSDLayerParam[TD_OSD_LAYER0].OsdEnable)
       {
           ErrCode = MS_ERR_TD_LAYER_NOT_ENABLE;
           return ErrCode;             
       }
       if(HorStart < m_XzoneStart || VerStart < m_YzoneStart || HorStop > m_XzoneStop || VerStop > m_YzoneStop)
       {
           //Layers position can't beyond the border of background zone
           ErrCode = MS_ERR_TD_ILLEGAL_PARAM;
           return ErrCode;   
       }
       MH_TD_set_Layer4XCtl_Start( HorStart);
       MH_TD_set_Layer4XCtl_Stop( HorStop - 1);
       MH_TD_set_Layer4YCtl_Start( VerStart);
       MH_TD_set_Layer4YCtl_Stop( VerStop - 1);   

   }
   else
   {
       ErrCode = MS_ERR_TD_NOT_INIT;
   }
   return ErrCode;
}






MS_U32 MS_API_TD_SetVideoLayer0Win( MS_U32 HorSizeIn,MS_U32 HorStride,MS_U32 VerSizeIn,MS_U32 HorSizeOut,MS_U32 VerSizeOut,MS_U16 HOffest,MS_U16 VOffest)
{

   MS_U32 ErrCode = MS_OK;   
   
   MS_U32  HscalePstep = 0;
   MS_U32  HscaleDstep = 0;
   MS_U32  VscalePstep = 0;
   MS_U32  VscaleDstep = 0;
   if(m_MixerDriverIsInitialized)
   {

       if(!m_MixerHandles.MixerParamater.VideoLayerParam[TD_VIDEO_LAYER0].LayerEnable)
       {
           ErrCode = MS_ERR_TD_LAYER_NOT_ENABLE;
           return ErrCode;             
       }
       HscalePstep = (HorSizeIn/HorSizeOut);
       HscaleDstep = ((HorSizeIn % HorSizeOut) * 65536 / HorSizeOut);
       VscalePstep = (VerSizeIn/VerSizeOut);
       VscaleDstep = ((VerSizeIn % VerSizeOut) * 65536 / VerSizeOut);
       MH_TD_set_Layer0ImgInPixSzie_Hsize(HorSizeIn - 1);
       MH_TD_set_Layer0ImgInPixSzie_Vsize(VerSizeIn - 1);

       MH_TD_set_Layer0ImgOutPixSzie_Hsize(HorSizeOut - 1);
       MH_TD_set_Layer0ImgOutPixSzie_Vsize(VerSizeOut - 1);

       MH_TD_set_Layer0ImgInStride_Hsize((HorStride >> 3) -1);
       MH_TD_set_Layer0ImgInStride_Vsize(VerSizeIn -1);
       MH_TD_set_Layer0ImgInOffset_Hoffset(HOffest);
       MH_TD_set_Layer0ImgInOffset_Voffset(VOffest);

       MH_TD_set_Layer0VscaleStep_Pstep(VscalePstep);
       MH_TD_set_Layer0VscaleStep_Dstep(VscaleDstep);
       MH_TD_set_Layer0VscaleSt_Pstep(0);

       MH_TD_set_Layer0HscaleStep_Pstep(HscalePstep);
       MH_TD_set_Layer0HscaleStep_Dstep(HscaleDstep);
       MH_TD_set_Layer0HscaleSt_Pstep(0);
   }
   else
   {
       ErrCode = MS_ERR_TD_NOT_INIT;
   } 
   return ErrCode;
   
}





MS_U32 MS_API_TD_SetOsdLayerWin( MS_U8 OsdLayer,MS_U32 HorSize,MS_U32 VerSize)
{

   MS_U32 ErrCode = MS_OK;   
   if(!m_MixerDriverIsInitialized)
   {
       ErrCode = MS_ERR_TD_NOT_INIT;
       return ErrCode;
   }

   if(!m_MixerHandles.MixerParamater.OSDLayerParam[OsdLayer].OsdEnable)
   {
       ErrCode = MS_ERR_TD_LAYER_NOT_ENABLE;
       return ErrCode;             
   }   
   switch(OsdLayer)
   {
       case TD_OSD_LAYER0:
           MH_TD_set_Osd0Size_Width(HorSize);
           MH_TD_set_Osd0Size_Height(VerSize);
       break;

     
       default:   
           ErrCode = MS_ERR_TD_ILLEGAL_PARAM;
       break;
   }

  return ErrCode;

}





MS_U32 MS_API_TD_SetOsdLayerType( MS_U8 OsdLayer,MD_TD_OSDLayerTypeE OsdType,MD_TD_OSDAlphaTypeE AlphaTpye)
{

   MS_U32 ErrCode = MS_OK;   
   if(!m_MixerDriverIsInitialized)
   {
       ErrCode = MS_ERR_TD_NOT_INIT;
       return ErrCode;
   } 
   if( OsdType < TD_RGB_24BIT || OsdType > TD_RGB_1555 )
   {
       ErrCode = MS_ERR_TD_ILLEGAL_PARAM;  
       return ErrCode;    
   }
   if(!m_MixerHandles.MixerParamater.OSDLayerParam[OsdLayer].OsdEnable)
   {
       ErrCode = MS_ERR_TD_LAYER_NOT_ENABLE;
       return ErrCode;             
   }   
   if( AlphaTpye < TD_FIXED_VALUE || AlphaTpye > TD_INTERVAL_A )
   {
       ErrCode = MS_ERR_TD_ILLEGAL_PARAM;  
       return ErrCode;    
   }

   switch(OsdLayer)
   {
       case TD_OSD_LAYER0:
           MH_TD_set_Osd0Info_OsdType(OsdType);
           MH_TD_set_Osd0Info_AlphaTpye(AlphaTpye);  
       break;

   
       default:   
           ErrCode = MS_ERR_TD_ILLEGAL_PARAM;  
           return ErrCode;
       break;
      
  }

  return ErrCode;

}







MS_U32 MS_API_TD_MixAlpha(MD_TD_MixerOrderE Mixerlayer, MS_U8 AlphaVal )
{
   // Default initializations.
   MS_U32 ErrCode = MS_OK;

   if(!m_MixerDriverIsInitialized)
   {
       ErrCode = MS_ERR_TD_NOT_INIT;
       return ErrCode;
   } 

   switch(Mixerlayer)
   {
       case TD_MIXER_VIDEO_LAYER_0:
           MH_TD_set_DispMixAlp0_Layer0GlbAlp(AlphaVal);
       break;
      
       case TD_MIXER_OSD_LAYER_0:
           MH_TD_set_DispMixAlp1_Layer4GlbAlp(AlphaVal);
       break;
     
       default:
           ErrCode = MS_ERR_TD_ILLEGAL_PARAM;  
           return ErrCode;
       break;
   }
 
   return ErrCode;
}


MS_U32 MS_API_TD_PlaneMixerOrder( MS_U32 OrderMap)
{
   // Default initializations.
   MS_U32 ErrCode = MS_OK;
   if(!m_MixerDriverIsInitialized)
   {
       ErrCode = MS_ERR_TD_NOT_INIT;
       return ErrCode;
   } 

   MH_TD_set_DispMixSel(OrderMap);
   
   return ErrCode;
}







MS_U32 MS_API_TD_DisplayLayerEn( MD_TD_MixerOrderE Mixerlayer,MS_U32 Enabled)
{
   MS_U32 ErrCode = MS_OK;
   if(!m_MixerDriverIsInitialized)
   {
       ErrCode = MS_ERR_TD_NOT_INIT;
       return ErrCode;
   } 

   if(Mixerlayer> TD_MIXER_OSD_LAYER_2 || Mixerlayer < TD_MIXER_VIDEO_LAYER_0)
   {
       ErrCode = MS_ERR_TD_ILLEGAL_PARAM;

   }
   switch(Mixerlayer)
   {
       case TD_MIXER_VIDEO_LAYER_0:
           MH_TD_set_DispEnable_Layer0En(Enabled);
          

       break;
     
       case TD_MIXER_OSD_LAYER_0:
           MH_TD_set_DispEnable_Layer4En(Enabled);
       break;

  
       
      default:   
          break;
      
  }

  return ErrCode;

}


#if 1
#endif


void MS_API_TD_Exit(void)
{
    return;
}




MS_U32 MS_API_TD_Close(MS_SYS_HandleT handle)
{
    MS_U32 err_code = MS_OK;
  
    return(err_code);
}



MS_U32 MS_API_TD_MixerFrameStart(void)
{
    MS_U32 ErrCode = MS_OK;
    //MS_TD_HandleT* handle_ptr = NULL;

    if( m_MixerDriverIsInitialized == 0 )
    {
        ErrCode = MS_ERR_TD_NOT_INIT;
       // return ErrCode;
    }

    

    MH_TD_set_DispEnable_FrameStart(1);    
    MH_TD_set_DispEnable_FrameStart(0);  
    return ErrCode;
}



MS_U32 vsync_cnt;
MS_U32 switch_pp;

//static MS_U32 TD_intr(void *ctx)
//{
//    MH_TD_set_DispIRQ_IRQ0(1);
//    vsync_cnt ++;
//    if(vsync_cnt%90 == 0)
//    {
//        printf("vsync_cnt comes ,vsync_cnt = %d\n",vsync_cnt);
//    }
   //printf("isp intr come!");
   
//    return 0;
//}



MS_U32 MS_API_TD_MixerInit(void)
{
   MS_U32 ErrCode = MS_OK;


   
    if( m_MixerDriverIsInitialized == 0)
    {
       //init coeff
       if( ErrCode == MS_OK )
       {
           TDMixerConfigVCoef(TD_V_Coef,64);
           TDMixerConfigHCoef(TD_H_Coef,64);
       }
       

       m_MixerDriverIsInitialized =1;

   }
   else
   {
       ErrCode = MS_ERR_TD_ALREADY_INIT;
   }
   return(ErrCode);
}

MS_U32 stephv;

MS_SYS_HandleT MS_API_TD_MixerOpen(const MD_TD_MixerParamaterT* LayerOpenLayerParm,
                                  MS_U32* errorCodePtr)
{
    MS_U32 ErrCode = MS_OK;
    MD_TD_MixerHandleT* return_ptr = 0;
    MS_U32 BackGroundComp = 0; 
    MS_U32 Iloop = 0;
    MS_U32 HorStride = 0;
    MS_U32 HorSizeIn = 0;
    MS_U32 VerSizeIn = 0;
    MS_U32 HorSizeOut = 0;
    MS_U32 VerSizeOut = 0;
    MS_U16 HOffest = 0;
    MS_U16 VOffest = 0;
    
    MS_U32 total_hsize = 0;
    MS_U32 background_hsize = 0;
    MS_U32 total_h_ratio = 0;
    MS_U32 background_vsize = 0;
    MS_U32 v_back_porch = 0;
    MS_U32 total_vsize = 0;
    MS_U32 total_v_ext = 0;
    MS_U32 total_hv_size = 0;

    
    *errorCodePtr = MS_OK;
    if(m_MixerDriverIsInitialized == 0)
    {
        ErrCode = MS_ERR_TD_NOT_INIT;
        if(errorCodePtr != 0)
        {
            *errorCodePtr = ErrCode;
        }
        return((MS_SYS_HandleT)return_ptr);
    }

    if(LayerOpenLayerParm == NULL)
    {
        ErrCode = MS_ERR_TD_ILLEGAL_PARAM;
        if(errorCodePtr != NULL)
        {
        *errorCodePtr = ErrCode;
        }
        return((MS_SYS_HandleT)return_ptr);
    }
    MH_TD_set_SoftRstCtl((MS_U32)0x0000000f);
    MH_TD_set_DmaSwCtl((MS_U32)0x00000011);

    memcpy(&m_MixerHandles.MixerParamater,LayerOpenLayerParm,sizeof(MD_TD_MixerParamaterT));

    //BACKGROUND: XZONE YZONE BACKGROUND_COMP

    if( (m_MixerHandles.MixerParamater.WindowZone.StartX < m_MixerHandles.MixerParamater.WindowZone.StopX) && (m_MixerHandles.MixerParamater.WindowZone.StartY < m_MixerHandles.MixerParamater.WindowZone.StopY))
    {

        MS_API_TD_SetBackgroundZone( m_MixerHandles.MixerParamater.WindowZone.StartX,
            m_MixerHandles.MixerParamater.WindowZone.StartY,
            m_MixerHandles.MixerParamater.WindowZone.StopX,
            m_MixerHandles.MixerParamater.WindowZone.StopY );

        BackGroundComp = m_MixerHandles.MixerParamater.BackGroundComp;

        MS_API_TD_SetBackgroundComponentRGB((BackGroundComp>>16)&0xff ,(BackGroundComp>>8)&0xff,BackGroundComp&0xff);

    }
    else
    {
        ErrCode = MS_ERR_TD_ILLEGAL_PARAM;
        if(errorCodePtr != NULL)
        {
            *errorCodePtr = ErrCode;
        }
        return((MS_SYS_HandleT)return_ptr);
    }
    //VIDEO_LAYER
    for( Iloop = 0;Iloop < MS_TD_VIDEO_LAYER_TOTAL ; Iloop++)
    {
        if(Iloop == TD_VIDEO_LAYER0)
        {
            if(m_MixerHandles.MixerParamater.VideoLayerParam[Iloop].LayerEnable)
            {                    
                MH_TD_set_Layer0Ctl_Enable(1);

                MS_API_TD_DisplayLayerEn(TD_MIXER_VIDEO_LAYER_0,1);
                MH_TD_set_DispEnable_Layer0Enhs(1);
                MH_TD_set_DispEnable_Layer0WEnhs(1);

                MS_API_TD_Layer0Line0BDCtl(1,7);
                MS_API_TD_Layer0Line1BDCtl(1,7);
                MS_API_TD_Layer0Line2BDCtl(1,7);
                MS_API_TD_Layer0Line3BDCtl(1,7);
                MH_TD_set_Layer0ScaleBlenth_Blen(0xf);

                MH_TD_set_Layer0ImgInDatMode_DatMode(m_MixerHandles.MixerParamater.VideoLayerParam[TD_VIDEO_LAYER0].ImgInDataMode);
                MH_TD_set_Layer0ImgInDatMode_EndianY(m_MixerHandles.MixerParamater.VideoLayerParam[TD_VIDEO_LAYER0].EndianModeY);
                MH_TD_set_Layer0ImgInDatMode_EndianUv(m_MixerHandles.MixerParamater.VideoLayerParam[TD_VIDEO_LAYER0].EndianModeUV);


                HorSizeIn = m_MixerHandles.MixerParamater.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelHszie;
                VerSizeIn = m_MixerHandles.MixerParamater.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelVszie;
                HorSizeOut = m_MixerHandles.MixerParamater.VideoLayerParam[TD_VIDEO_LAYER0].ImgOutPixelHszie;
                VerSizeOut = m_MixerHandles.MixerParamater.VideoLayerParam[TD_VIDEO_LAYER0].ImgOutPixelVszie;
                HOffest = m_MixerHandles.MixerParamater.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelOffsetH;
                VOffest = m_MixerHandles.MixerParamater.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelOffsetV;
                HorStride = m_MixerHandles.MixerParamater.VideoLayerParam[TD_VIDEO_LAYER0].ImgInPixelStrideH;

                MS_API_TD_SetVideoLayer0Win(HorSizeIn,HorStride,VerSizeIn,HorSizeOut,VerSizeOut,HOffest,VOffest);

                MS_API_TD_SetVideoLayer0Positon(m_MixerHandles.MixerParamater.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StartX,
                               m_MixerHandles.MixerParamater.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StartY,
                               m_MixerHandles.MixerParamater.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StopX,
                               m_MixerHandles.MixerParamater.VideoLayerParam[TD_VIDEO_LAYER0].LayerPosition.StopY );

                MS_API_TD_MixAlpha(TD_MIXER_VIDEO_LAYER_0,m_MixerHandles.MixerParamater.VideoLayerParam[TD_VIDEO_LAYER0].GlobalAlpha);

            }
            else
            {
                MH_TD_set_Layer0Ctl_Enable(0);
            }    
        }
    }

    for( Iloop = 0;Iloop < MS_TD_OSD_LAYER_TOTAL ; Iloop++)
    {  
        if(Iloop == TD_OSD_LAYER0)
        {
            if(m_MixerHandles.MixerParamater.OSDLayerParam[TD_OSD_LAYER0].OsdEnable)
            {
                MS_API_TD_DisplayLayerEn(TD_MIXER_OSD_LAYER_0,1);

                MS_API_TD_Layer4BDCtl(1,7);    

                MS_API_TD_SetOsdLayerWin(TD_OSD_LAYER0,
                       m_MixerHandles.MixerParamater.OSDLayerParam[TD_OSD_LAYER0].OsdPixelHszie,
                       m_MixerHandles.MixerParamater.OSDLayerParam[TD_OSD_LAYER0].OsdPixelVszie);

                MS_API_TD_SetOsdLayerType(TD_OSD_LAYER0,
                       m_MixerHandles.MixerParamater.OSDLayerParam[TD_OSD_LAYER0].OsdType,
                       m_MixerHandles.MixerParamater.OSDLayerParam[TD_OSD_LAYER0].AlphaTpye);

                MH_TD_set_Osd0DMACtl_DMARequestLen(m_MixerHandles.MixerParamater.OSDLayerParam[TD_OSD_LAYER0].RequestBLen);         
                MH_TD_set_Osd0DMACtl_DMAMap(m_MixerHandles.MixerParamater.OSDLayerParam[TD_OSD_LAYER0].DmaMap);         
                MH_TD_set_Osd0DMACtl_RGBRev(m_MixerHandles.MixerParamater.OSDLayerParam[TD_OSD_LAYER0].RevRGB);


                MH_TD_set_Osd0Stride_OsdStride(m_MixerHandles.MixerParamater.OSDLayerParam[TD_OSD_LAYER0].DataInStride >> 3);
                MH_TD_set_Osd0Stride_AlpStride(m_MixerHandles.MixerParamater.OSDLayerParam[TD_OSD_LAYER0].AlphaInStride >> 3);

                MS_API_TD_SetOsdLayer0Positon(m_MixerHandles.MixerParamater.OSDLayerParam[TD_OSD_LAYER0].LayerPosition.StartX,
                               m_MixerHandles.MixerParamater.OSDLayerParam[TD_OSD_LAYER0].LayerPosition.StartY,
                               m_MixerHandles.MixerParamater.OSDLayerParam[TD_OSD_LAYER0].LayerPosition.StopX,
                               m_MixerHandles.MixerParamater.OSDLayerParam[TD_OSD_LAYER0].LayerPosition.StopY);

                MS_API_TD_MixAlpha(TD_MIXER_OSD_LAYER_0,m_MixerHandles.MixerParamater.OSDLayerParam[TD_OSD_LAYER0].GlobalAlpha);
            }
        }
    }

    for( Iloop = 0;Iloop < MS_TD_VIDEO_LAYER_TOTAL ; Iloop++)
    {
        if(Iloop == TD_VIDEO_LAYER0)
        {
            if(m_MixerHandles.MixerParamater.VideoLayerParam[Iloop].LayerEnable)
            {
                MH_TD_set_Layer0Baddr0Y(m_MixerHandles.MixerParamater.VideoLayerParam[TD_VIDEO_LAYER0].ReadAddress0Y);
                MH_TD_set_Layer0Baddr0UV(m_MixerHandles.MixerParamater.VideoLayerParam[TD_VIDEO_LAYER0].ReadAddress0UV);
            }               
        }
    }

    for( Iloop = 0;Iloop < MS_TD_OSD_LAYER_TOTAL ; Iloop++)
    {
        if(Iloop == TD_OSD_LAYER0)
        {
            if(m_MixerHandles.MixerParamater.OSDLayerParam[Iloop].OsdEnable)
            {
                MH_TD_set_Osd0VluAddr0(m_MixerHandles.MixerParamater.OSDLayerParam[TD_OSD_LAYER0].ReadAddress0Value);
                MH_TD_set_Osd0AlpAddr0(m_MixerHandles.MixerParamater.OSDLayerParam[TD_OSD_LAYER0].ReadAddress0Alp);
            }

        }

    }

    MH_TD_set_DispMixSel(m_MixerHandles.MixerParamater.LayerMixerOrder);
    MH_TD_set_DispHsyncCtl((MS_U32)0x320006);
    MH_TD_set_DispVsyncCtl((MS_U32)0x60001);

    background_hsize = HorSizeOut;
    background_vsize = VerSizeOut;

    total_h_ratio = 110;
    total_v_ext = 3;

    v_back_porch =  m_MixerHandles.MixerParamater.WindowZone.StartY;

    total_hsize = background_hsize*total_h_ratio/100 + 192;  //0x680
    total_vsize = background_vsize + v_back_porch + total_v_ext; //0x2fd
    total_hv_size = (total_vsize&0x1FFF)<<16|(total_hsize&0x1FFF);
    
    //printf("total_vsize = 0x%x,total_hsize = 0x%x,total_hv_size = 0x%x\n",total_vsize,total_hsize, total_hv_size);

    //printf("MH_TD_get_DispEnable = 0x%x\n",MH_TD_get_DispEnable());

    
    //MH_TD_set_DispSize(0x04650a50);//sw
    //MH_TD_set_DispSize(0x02fd0680);//rtl

     MH_TD_set_DispSize(total_hv_size);



    //MH_TD_set_DispSize(0x04650bb8);

    
    //MH_VO_set_OsdYUV2RGBCtl_Osd0En(1);

     
    //DISPLAY ctl
    MH_TD_set_DispCtl(0x10002);
 

    MH_TD_set_DispYUV2RGBCtl_En(m_MixerHandles.MixerParamater.DisplayYUV2RGBEn);

    //WB DMA
    if( m_MixerHandles.MixerParamater.DmaWriteBackEn == 1 )
    {
        MH_TD_set_WbDma_En(1);
        MH_TD_set_WbMode_Input(m_MixerHandles.MixerParamater.DmaWbParam.InputMode );

        MH_TD_set_WbPixel_FormatSel(m_MixerHandles.MixerParamater.DmaWbParam.DataFormat);   
        MH_TD_set_WbPixel_InputFormat( m_MixerHandles.MixerParamater.DmaWbParam.DmaInputFormat);
        MH_TD_set_WbPixel_OutputFormat(m_MixerHandles.MixerParamater.DmaWbParam.OutputMode );
        MH_TD_set_WbPixel_422PixelOrder(m_MixerHandles.MixerParamater.DmaWbParam.DmaInput422PixelOrder);
        MH_TD_set_WbPixel_RGBPixelWidth(m_MixerHandles.MixerParamater.DmaWbParam.RawPixelWidth);

        MH_TD_set_WbBaseAddr0Y(m_MixerHandles.MixerParamater.DmaWbParam.WriteBaseAddressY0);
        MH_TD_set_WbBaseAddr1Y(m_MixerHandles.MixerParamater.DmaWbParam.WriteBaseAddressY1);
        MH_TD_set_WbBaseAddr0UV(m_MixerHandles.MixerParamater.DmaWbParam.WriteBaseAddressUV0); 
        MH_TD_set_WbBaseAddr1UV(m_MixerHandles.MixerParamater.DmaWbParam.WriteBaseAddressUV1);

        MH_TD_set_WbOutY_Hstride(m_MixerHandles.MixerParamater.DmaWbParam.DataLineYStride);
        
        MH_TD_set_WbOutUV_Hstride(m_MixerHandles.MixerParamater.DmaWbParam.DataLineUVStride);
        
        MH_TD_set_WbLoop_BufferSize(m_MixerHandles.MixerParamater.DmaWbParam.DramLoopSzie);
        MH_TD_set_WbActiveV_size(m_MixerHandles.MixerParamater.DmaWbParam.ActiveVszie - 1);
        MH_TD_set_WbActiveH_size(m_MixerHandles.MixerParamater.DmaWbParam.ActiveHszie - 1);

        MH_TD_set_WbCh1Dma_OtNum(m_MixerHandles.MixerParamater.DmaWbParam.Ch1OtNum);
        MH_TD_set_WbCh1Dma_Blen(m_MixerHandles.MixerParamater.DmaWbParam.Ch1BlenMode);
        MH_TD_set_WbCh1Dma_ContinuousMode(m_MixerHandles.MixerParamater.DmaWbParam.Ch1ContinuousMode);
        MH_TD_set_WbCh1Dma_Swap(m_MixerHandles.MixerParamater.DmaWbParam.Ch1DmaYUVMap);
        MH_TD_set_WbCh1Dma_ErrDetectEn(m_MixerHandles.MixerParamater.DmaWbParam.Ch1WbErrDetectEn);
        MH_TD_set_WbCh1ErrUnit_Unit(m_MixerHandles.MixerParamater.DmaWbParam.Ch1ErrUnit);
        MH_TD_set_WbCh1ErrTh_threshold(m_MixerHandles.MixerParamater.DmaWbParam.Ch1ErrTh);

        MH_TD_set_WbCh2Dma_OtNum(m_MixerHandles.MixerParamater.DmaWbParam.Ch2OtNum);
        MH_TD_set_WbCh2Dma_Blen(m_MixerHandles.MixerParamater.DmaWbParam.Ch2BlenMode);
        MH_TD_set_WbCh2Dma_ContinuousMode(m_MixerHandles.MixerParamater.DmaWbParam.Ch2ContinuousMode);
        MH_TD_set_WbCh2Dma_Swap(m_MixerHandles.MixerParamater.DmaWbParam.Ch2DmaYUVMap);
        MH_TD_set_WbCh2Dma_ErrDetectEn(m_MixerHandles.MixerParamater.DmaWbParam.Ch2WbErrDetectEn);
        MH_TD_set_WbCh2ErrUnit_Unit(m_MixerHandles.MixerParamater.DmaWbParam.Ch2ErrUnit);
        MH_TD_set_WbCh2ErrTh_threshold(m_MixerHandles.MixerParamater.DmaWbParam.Ch2ErrTh);
    }
    else
    {
        MH_TD_set_WbDma_En(0);
    }
      
    //END
    if(errorCodePtr != 0)
    {
        *errorCodePtr = ErrCode;
    }
    MH_TD_set_WbDma(0x3);
    //MH_TD_set_WbPixel(0xe0);
    
    //MH_TD_set_WbCh1Dma(0x104111);
   // MH_TD_set_WbCh1ErrUnit(0x1010101);
   // MH_TD_set_WbCh1ErrTh(0x1010101);
    
   // MH_TD_set_WbCh2Dma(0x104111);
   // MH_TD_set_WbCh2ErrUnit(0x1010101);
    //MH_TD_set_WbCh2ErrTh(0x1010101);

    return_ptr = &m_MixerHandles;
    return((MS_SYS_HandleT)return_ptr);
}


