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
#ifndef PCAL6416_H
#define PCAL6416_H

#include <stdio.h>
#include <stdint.h>
#include <controler/i2c.h>


#define PCAL6416_REG_INPUT_VAL                  0x00
#define PCAL6416_REG_OUTPUT_VAL                 0x02
#define PCAL6416_REG_CONFIG                     0x06
#define PCAL6416_REG_OUTPUT_DRV                 0x40
#define PCAL6416_REG_INPUT_LATCH                0x44
#define PCAL6416_REG_PULL_EN                    0x46
#define PCAL6416_REG_PULL_SEL                   0x48
#define PCAL6416_REG_INT_MASK                   0x4A
#define PCAL6416_REG_INT_STATUS                 0x4C
#define PCAL6416_REG_OUTPUT_CONTROL             0x4F

#define PCAL6416_ADDR                           0x20
#define PCAL6416_ADDR_LEN                               7

/*pcal6416 has 2 group ios(p0.0-p0.7 and p1.0-p1.7), and its register is in sequence. */
/*      e.g. input_value _0's register is 0x00, and input_value_1's register is 0x01*/

#define REGISTER_BIT_NUM                        8
#define FIND_IO_GROUP(pin)                      ((pin) / REGISTER_BIT_NUM)
#define FIND_IO_BIT(pin)                        ((pin) % REGISTER_BIT_NUM)
#define IO_REGISTER(reg, pin)                   ((reg) + FIND_IO_GROUP(pin))

#define BITS_PER_LONG                           8
#define BIT_MASK(nr)                            (1UL << ((nr) % BITS_PER_LONG))

#ifdef CONFIG_TARGET_K510_CRB_LP3_V0_1
#define K510_CRB	
#endif

enum GPIO_DIRECTION {
	GPIO_OUT = 0,
	GPIO_IN
};

enum GPIO_OUTPUT_MODE {
	OUT_OD = 0,                                     
	OUT_PP                                          
};

struct pcal6416_data {
	i2c_device_number_t i2c_num;
	uint32_t dma_en;
	uint32_t dma_tx_num;
	uint32_t dma_rx_num;
	uint32_t slave_address;
	uint32_t address_width;
	uint32_t i2c_clk;
	
	unsigned char all_gpio_config[REGISTER_BIT_NUM * 2];
};

int pcal6416_reg_write(struct pcal6416_data *data, uint8_t reg , uint8_t val);

 int pcal6416_reg_read(struct pcal6416_data *data, uint8_t reg);


/**
        set gpio pin
**/
void pcal6416_pin_set(struct pcal6416_data *data, unsigned char offset, unsigned char value);

/**
        get gpio pin
*/
int pcal6416_pin_get(struct pcal6416_data *data, unsigned offset);

/**
        set gpio input
**/
int pcal6416_pin_direction_input(struct pcal6416_data *data, unsigned offset);

/**
        set gpio output
*/
int pcal6416_pin_direction_output(struct pcal6416_data *data, unsigned offset);

/**
        get all gpio config
*/
int pcal6416_get_all_gpio_config(struct pcal6416_data *data);


extern struct pcal6416_data pcal6416[2];


/***********************lp3*********************************
						U44		--- > iic1
	0 :			dvp_rst
	1 :			ws2812_data
	2 : 		RS485_SLR (Digital Input Slew rate select: Low = 20 Mbps, High = 250 kbps)
	3 :			UART_RE (connect 485 chip RE, Receiver enable input)
	4 :			UART_DE (connect 485 chip  DE, Driver enable input)
	5 :			SPI_NOR_RESET
	6 :			SPI_NOR_DQS
	7 :			N_VBUSEN	(axp228 11 pin)	none
	8 : 		BT_REG_ON_H
	9 :			BT_WAKE_L
	10 :		WIFI_HOST_WAKE_L
	11 :		UART0_TXD	(ap6354 Bluetooth usart)
	12 :		UART0_RXD	(ap6354 Bluetooth usart)
	13 :		GPIO_VBUS_EN (TPS22914 ->VBUS_EN)
	14 :		SD2_DET
	15 :		GNNE_SLEEP
	
						U39		--- > iic2
	0 :			OPTION1
	1 :			OPTION2
	2 : 		OPTION3		(key)
	3 :			MIPI_DSI_RESET
	4 :			GPIO_CSI_EN
	5 :			GPIO_DSI_EN
	6 :			GPIO_MIC_EN
	7 :			DEV1_POWER_EN		(RT6212AHGJ6F -> en)
	8 : 		DEV2_POWER_EN		(DEV1_POWER_EN -> en   U33)
	9 :			SD3_RESET_B			(EMMC)
	10 :		SD_EN
	11 :		SD_VSELECT
	12 :		MIPI_DSI_IO
	13 :		PMU_IRQ			(axp228 29 pin)
	14 :		WIFI_REG_ON_H
	15 :		BT_HOST_WAKE_L
********************************************************/

/****************************lp4*******************************
				
					U39		--- > iic2
	0 :			OPTION1
	1 :			OPTION2
	2 :			OPTION3		(key)
	3 :			MIPI_DSI_RESET
	4 :			GPIO_CSI_EN
	5 :			GPIO_DSI_EN
	6 :			GPIO_MIC_EN
	7 :			DEV1_POWER_EN		(RT6212AHGJ6F -> en)
	8 : 		DEV2_POWER_EN		(DEV1_POWER_EN -> en   U33)
	9 :			SD3_RESET_B			(EMMC)
	10 :		SD_EN
	11 :		SD_VSELECT
	12 :		MIPI_DSI_IO
	13 :		PMU_IRQ			(axp228 29 pin)
	14 :		WIFI_REG_ON_H
	15 :		BT_HOST_WAKE_L		

***********************************************************/

#ifdef _EVBLP4

#define pcal6416_mipi_dsi_reset(en)					do{pcal6416_pin_direction_output(&pcal6416[0], 3); pcal6416_pin_set(&pcal6416[0], 3, en);}while(0)				//low reset 
#define pcal6416_gpio_csi_en(en)					do{pcal6416_pin_direction_output(&pcal6416[0], 4); pcal6416_pin_set(&pcal6416[0], 4, en);}while(0)
#define pcal6416_gpio_dsi_en(en)					do{pcal6416_pin_direction_output(&pcal6416[0], 5); pcal6416_pin_set(&pcal6416[0], 5, en);}while(0)
#define pcal6416_gpio_mic_en(en)					do{pcal6416_pin_direction_output(&pcal6416[0], 6); pcal6416_pin_set(&pcal6416[0], 6, en);}while(0)
#define pcal6416_dev1_power_en(en)					do{pcal6416_pin_direction_output(&pcal6416[0], 7); pcal6416_pin_set(&pcal6416[0], 7, en);}while(0)
#define pcal6416_dev2_power_en(en)					do{pcal6416_pin_direction_output(&pcal6416[0], 8); pcal6416_pin_set(&pcal6416[0], 8, en);}while(0)
#define	pcal6416_sd3_reset_b(en)					do{pcal6416_pin_direction_output(&pcal6416[0], 9); pcal6416_pin_set(&pcal6416[0], 9, en);}while(0)				//low reset 
#define pcal6416_sd_en(en)							do{pcal6416_pin_direction_output(&pcal6416[0], 10); pcal6416_pin_set(&pcal6416[0], 10, en);}while(0)
#define pcal6416_sd_vselect(en)						do{pcal6416_pin_direction_output(&pcal6416[0], 11); pcal6416_pin_set(&pcal6416[0], 11, en);}while(0)
#define pcal6416_mipi_dsi_io(en)					do{pcal6416_pin_direction_output(&pcal6416[0], 12); pcal6416_pin_set(&pcal6416[0], 12, en);}while(0)
	
#else
//i2c1
#define pcal6416_set_dvp_reset(en)					do{pcal6416_pin_direction_output(&pcal6416[1], 0); pcal6416_pin_set(&pcal6416[1], 0, en);}while(0)				// low reset 
#define pcal6416_set_spi_nor_reset(en)				do{pcal6416_pin_direction_output(&pcal6416[1], 5); pcal6416_pin_set(&pcal6416[1], 5, en);}while(0)				//low reset 
#define pcal6416_set_nor_dqs(en)					do{pcal6416_pin_direction_output(&pcal6416[1], 6); pcal6416_pin_set(&pcal6416[1], 6, en);}while(0)
#define pcal6416_set_gpio_vbus_en(en)				do{pcal6416_pin_direction_output(&pcal6416[1], 13); pcal6416_pin_set(&pcal6416[1], 13, en);}while(0)
#define pcal6416_set_sd2_det(en)					do{pcal6416_pin_direction_output(&pcal6416[1], 14); pcal6416_pin_set(&pcal6416[1], 14, en);}while(0)
#define pcal6416_set_gnne_sleep(en)					do{pcal6416_pin_direction_output(&pcal6416[1], 15); pcal6416_pin_set(&pcal6416[1], 15, en);}while(0)
#define pcal6416_get_gnne_sleep_status()	  		do{pcal6416_pin_direction_input(&pcal6416[1], 15); pcal6416_pin_get(&pcal6416[1], 15);}while(0)


// iic 2

#ifdef K510_CRB

#define pcal6416_mipi_dsi_reset(en)					do{pcal6416_pin_direction_output(&pcal6416[0], 15); pcal6416_pin_set(&pcal6416[0], 15, en);}while(0)				//low reset
#define pcal6416_gpio_dsi_en(en)					do{pcal6416_pin_direction_output(&pcal6416[0], 14); pcal6416_pin_set(&pcal6416[0], 14, en);}while(0)

#else

#define pcal6416_mipi_dsi_reset(en)					do{pcal6416_pin_direction_output(&pcal6416[0], 3); pcal6416_pin_set(&pcal6416[0], 3, en);}while(0)				//low reset
#define pcal6416_gpio_dsi_en(en)					do{pcal6416_pin_direction_output(&pcal6416[0], 5); pcal6416_pin_set(&pcal6416[0], 5, en);}while(0)

#endif

#define pcal6416_gpio_csi_en(en)					do{pcal6416_pin_direction_output(&pcal6416[0], 4); pcal6416_pin_set(&pcal6416[0], 4, en);}while(0)
#define pcal6416_gpio_mic_en(en)					do{pcal6416_pin_direction_output(&pcal6416[0], 6); pcal6416_pin_set(&pcal6416[0], 6, en);}while(0)
#define pcal6416_dev1_power_en(en)					do{pcal6416_pin_direction_output(&pcal6416[0], 7); pcal6416_pin_set(&pcal6416[0], 7, en);}while(0)
#define pcal6416_dev2_power_en(en)					do{pcal6416_pin_direction_output(&pcal6416[0], 8); pcal6416_pin_set(&pcal6416[0], 8, en);}while(0)
#define	pcal6416_sd3_reset_b(en)					do{pcal6416_pin_direction_output(&pcal6416[0], 9); pcal6416_pin_set(&pcal6416[0], 9, en);}while(0)				//low reset 
#define pcal6416_sd_en(en)							do{pcal6416_pin_direction_output(&pcal6416[0], 10); pcal6416_pin_set(&pcal6416[0], 10, en);}while(0)
#define pcal6416_sd_vselect(en)						do{pcal6416_pin_direction_output(&pcal6416[0], 11); pcal6416_pin_set(&pcal6416[0], 11, en);}while(0)
#define pcal6416_mipi_dsi_io(en)					do{pcal6416_pin_direction_output(&pcal6416[0], 12); pcal6416_pin_set(&pcal6416[0], 12, en);}while(0)

#endif

void pcal6416_init(uint8_t dma_en);

#endif
