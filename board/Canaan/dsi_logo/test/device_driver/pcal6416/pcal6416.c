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
#include <stdio.h>
#include "pcal6416.h"
#include "utils.h"
#include <stdlib.h>
#include <string.h>
#include <dmac.h>
#include <muxpin.h>
#include <sleep.h>

struct pcal6416_data pcal6416[2];


/***
        pcal6416 dma init
***/
/*
void pcal6416_init(struct pcal6416_data *data)
{

	i2c_init(data->i2c_num, data->slave_address, data->address_width, data->i2c_clk);

	pcal6416_get_all_gpio_config(data);
}

*/

 int pcal6416_reg_write(struct pcal6416_data *data, uint8_t reg , uint8_t val)
{
	uint8_t ret = 0;
	uint8_t length = 1;
	uint8_t *buf = malloc(length + 1);
	buf[0] = reg;
	buf[1] = val;
	if(data->dma_en == 1)
	{
		i2c_send_data_dma(data->dma_tx_num, data->i2c_num, buf, length + 1);
	}else{
		ret = i2c_send_data(data->i2c_num, buf, length + 1);
	}
	free(buf);

	return ret;
}


 int pcal6416_reg_read(struct pcal6416_data *data, uint8_t reg)
{
	int ret = 0;
//      uint8_t data_buf[5] = {0};
	uint8_t val;
	if(data->dma_en == 1)
	{
		i2c_recv_data_dma(data->dma_tx_num, data->dma_rx_num, data->i2c_num, &reg, 1, &val, 1);
	}else{
		ret = i2c_recv_data(data->i2c_num, &reg, 1, &val, 1);
		if(ret < 0)
			return ret ;
	}

    return val;
}

static int pcal6416_reg_read_one_io(struct pcal6416_data *data, unsigned char reg_base, unsigned char offset)
{
	int reg = IO_REGISTER(reg_base, offset);
	int reg_val = -1;
	int io = FIND_IO_BIT(offset);

	reg_val = pcal6416_reg_read(data, reg);
	if (reg_val < 0) {

		return reg_val;
	}

	return !!(reg_val & BIT_MASK(io));

}


static int pcal6416_reg_write_one_io(struct pcal6416_data *data, unsigned char reg_base, unsigned char offset, unsigned char value)
{
	int reg = IO_REGISTER(reg_base, offset);
	int reg_val = -1;
	int io = FIND_IO_BIT(offset);

	value = !!value;
	reg_val = pcal6416_reg_read(data, reg);
	if (reg_val < 0) {

		return reg_val;
	}

	reg_val = (reg_val & ~(BIT_MASK(io))) | (value << io);

	return pcal6416_reg_write(data, reg, reg_val);
}

/**
        set gpio pin
**/
void pcal6416_pin_set(struct pcal6416_data *data, unsigned char offset, unsigned char value)
{
       pcal6416_reg_write_one_io(data, PCAL6416_REG_OUTPUT_VAL, offset, value);
}


/**
        get gpio pin
*/
int pcal6416_pin_get(struct pcal6416_data *data, unsigned offset)
{
	int val;

//	if (data->all_gpio_config[offset] == GPIO_IN)
		val = pcal6416_reg_read_one_io(data, PCAL6416_REG_INPUT_VAL, offset);
//	else
	
//		val = pcal6416_reg_read_one_io(data, PCAL6416_REG_OUTPUT_VAL, offset);

	return val;
}

/**
        set gpio input
**/
int pcal6416_pin_direction_input(struct pcal6416_data *data, unsigned offset)
{
	int rc = 0;

	rc = pcal6416_reg_write_one_io(data, PCAL6416_REG_CONFIG, offset, GPIO_IN);

	if (!rc)
		data->all_gpio_config[offset] = GPIO_IN;

	return rc;
}

/**
        set gpio input
*/
int pcal6416_pin_direction_output(struct pcal6416_data *data, unsigned offset)
{
	int rc = 0;

	rc = pcal6416_reg_write_one_io(data, PCAL6416_REG_CONFIG, offset, GPIO_OUT);
	if (!rc)
		data->all_gpio_config[offset] = GPIO_OUT;

	return rc;
}

/**
        get all gpio config
**/
int pcal6416_get_all_gpio_config(struct pcal6416_data *data)
{
	int i;
	int reg_val;

	reg_val = pcal6416_reg_read(data, PCAL6416_REG_CONFIG);
	for (i = 0; i < REGISTER_BIT_NUM; i++)
		data->all_gpio_config[i] = (reg_val & BIT_MASK(i)) ? GPIO_IN : GPIO_OUT;

	reg_val = pcal6416_reg_read(data, PCAL6416_REG_CONFIG + 1);
	for (i = 0; i < REGISTER_BIT_NUM; i++)
		data->all_gpio_config[REGISTER_BIT_NUM + i] = (reg_val & BIT_MASK(i)) ? GPIO_IN : GPIO_OUT;

	return 0;
}

/**
        enable pin gpio pull-up/pull-down   
**/

int pcal6416_set_gpio_pull_enable(struct pcal6416_data *data, unsigned offset)
{
	int reg = IO_REGISTER(PCAL6416_REG_PULL_EN, offset);
	int reg_val = -1;
	int io = FIND_IO_BIT(offset);

	reg_val = pcal6416_reg_read(data, reg);
	if (reg_val < 0) {

		return reg_val;
	}

	reg_val = (reg_val & ~(BIT_MASK(io))) | (1 << io);

	return pcal6416_reg_write(data, reg, reg_val);
}

/**
        get one pin pull-up/pull-down  enable / disable
**/
static uint8_t pcal6416_get_gpio_pull_enable(struct pcal6416_data *data, unsigned offset)
{
	int reg = IO_REGISTER(PCAL6416_REG_PULL_EN, offset);
	int reg_val = -1;
	int io = FIND_IO_BIT(offset);
	int val ;

	reg_val = pcal6416_reg_read(data, reg);
	if(reg_val < 0)
		return reg_val;

	val = !!(reg_val & BIT_MASK(io));

	return val;
}


/**
        set gpio pull-up/pull-down 
**/
int pcal6416_set_gpio_pull_select(struct pcal6416_data *data, unsigned offset)
{
	int reg = IO_REGISTER(PCAL6416_REG_PULL_EN, offset);
	int reg_val = -1;
	int io = FIND_IO_BIT(offset);

	if(pcal6416_get_gpio_pull_enable(data, offset) <= 0)
		return -1;

	reg_val = pcal6416_reg_read(data, reg);
	if (reg_val < 0) {

		return reg_val;
	}

	reg_val = (reg_val & ~(BIT_MASK(io))) | (1 << io);

	return pcal6416_reg_write(data, reg, reg_val);
}

/***two pcal6416 default config *****/
struct pcal6416_data pcal6416[2] = {
	{
		.i2c_num = 2,								// i2c 2  U44
		.dma_tx_num = 1,							// dma tx ch
		.dma_rx_num = 0,							// dma rx ch
		.dma_en = 0,								// dma close default
		.slave_address = PCAL6416_ADDR,				// slave addr
		.address_width = PCAL6416_ADDR_LEN, 		// slave addr width
		.i2c_clk = 100000,							// iic clk clk
	},
	{
		.i2c_num = 1,								// i2c 1  U39
		.dma_tx_num = 3,							// dma tx ch
		.dma_rx_num = 2,							// dma rx ch
		.dma_en = 0,								// dma default close
		.slave_address = PCAL6416_ADDR,				// slave addr
		.address_width = PCAL6416_ADDR_LEN, 		// slave addr width
		.i2c_clk = 100000,							// iic clk clk
	}
};


void pcal6416_init(uint8_t dma_en)
{

#ifdef _EVBLP4
	muxpin_set_function(95, FUNC_I2C2_SCLK);
    muxpin_set_function(94, FUNC_I2C2_SDA);
	if(dma_en)
		pcal6416[0].dma_en = 1;	
	i2c_init(pcal6416[0].i2c_num, pcal6416[0].slave_address, pcal6416[0].address_width, pcal6416[0].i2c_clk);
	
	pcal6416_get_all_gpio_config(&pcal6416[0]);
#else

#ifdef K510_CRB
	muxpin_set_function(93, FUNC_I2C2_SCLK);				// U44
    muxpin_set_function(92, FUNC_I2C2_SDA);
	
//	muxpin_set_function(119, FUNC_I2C1_SCLK);				// U39
//    muxpin_set_function(118, FUNC_I2C1_SDA);
#else
	muxpin_set_function(117, FUNC_I2C2_SCLK);				// U44
    muxpin_set_function(116, FUNC_I2C2_SDA);
	
	muxpin_set_function(119, FUNC_I2C1_SCLK);				// U39
    muxpin_set_function(118, FUNC_I2C1_SDA);
#endif
	if(dma_en)
	{
		pcal6416[0].dma_en = 1;	
		pcal6416[1].dma_en = 1;	
	}		
#ifdef K510_CRB

//	i2c_init(pcal6416[1].i2c_num, pcal6416[1].slave_address, pcal6416[1].address_width, pcal6416[1].i2c_clk);
	i2c_init(pcal6416[0].i2c_num, pcal6416[0].slave_address, pcal6416[0].address_width, pcal6416[0].i2c_clk);

	
#else
	i2c_init(pcal6416[0].i2c_num, pcal6416[0].slave_address, pcal6416[0].address_width, pcal6416[0].i2c_clk);
	i2c_init(pcal6416[1].i2c_num, pcal6416[1].slave_address, pcal6416[1].address_width, pcal6416[1].i2c_clk);
#endif
//	pcal6416_get_all_gpio_config(&pcal6416[0]);
//	pcal6416_get_all_gpio_config(&pcal6416[1]);

#endif
		
}



#if 0
int main(void)
{
	
	pcal6416_init(0);				// pcal6416 init


	pcal6416_gpio_csi_en(1); 
	pcal6416_gpio_dsi_en(1);
	pcal6416_mipi_dsi_reset(1);
	pcal6416_mipi_dsi_io(1);

	k510_logi("+++++++++++++++++++++++++++++++ \n");
	while(1);
}

#endif
