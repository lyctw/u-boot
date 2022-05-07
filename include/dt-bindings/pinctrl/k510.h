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
/**
 * @brief      FPIOA IO
 *
 *             FPIOA IO is the specific pin of the chip package. Every IO
 *             has a 32bit width register that can independently implement
 *             schmitt trigger, invert input, invert output, strong pull
 *             up, driving selector, static input and static output. And more,
 *             it can implement any pin of any peripheral devices.
 *
 * @note       FPIOA IO's register bits Layout
 *
 * | Bits      | Name     |Description                                        |
 * |-----------|----------|---------------------------------------------------|
 * | 31        | PAD_DI   | Read current IO's data input.                     |
 * | 30:24     | NA       | Reserved bits.                                    |
 * | 23:16     | LSIO_SEL | If IO_SEL is 0, use this to choose LSIO func      |
 * | 15:12     | NA       | Reserved bits.                                    |
 * | 11:10     | IO_SEL   | Use this to choose IO func                        |
 * |  9        | SL       | Slew rate control enable.                         |
 * |  8        | IO_MSC   | Output enable.It can disable or enable IO output. |
 * |  7        | IE_EN    | Input enable. It can disable or enable IO input.  |
 * |  6        | OE_EN    | Output enable.It can disable or enable IO output. |
 * |  5        | PU       | Pull enable.                                      |
 * |  4        | PD       | Pull select: 0 for pull down, 1 for pull up.      |
 * | 3:1       | DS       | Driving selector.                                 |
 * |  0        | ST       | Schmitt trigger.                                  |
 *
 */

#define MUXPIN_PAD_DI_OFF 31

#define MUXPIN_LSIO_SEL_OFF 16

#define MUXPIN_IO_SEL_OFF 10
#define MUXPIN_IO_SEL_LSIO 3

#define MUXPIN_SL (1<<8)
#define MUXPIN_IO_MSC (1<<8)

#define MUXPIN_IE_EN (1<<7)
#define MUXPIN_OE_EN (1<<6)

#define MUXOIN_PU  (1<<5)
#define MUXPIN_PD  (1<<4)

#define MUXPIN_DRIVING_OFF 1
#define MUXPIN_DRIVING_0 0
#define MUXPIN_DRIVING_1 1
#define MUXPIN_DRIVING_2 2
#define MUXPIN_DRIVING_3 3
#define MUXPIN_DRIVING_4 4
#define MUXPIN_DRIVING_5 5
#define MUXPIN_DRIVING_6 6
#define MUXPIN_DRIVING_7 7
#define MUXPIN_DRIVING_MAX 8

#define MUXPIN_ST (1<<0)

#define IO_MMC0_CLK 7
#define IO_MMC0_CMD 8
#define IO_MMC0_DATA7 9
#define IO_MMC0_DATA6 10
#define IO_MMC0_DATA5 11
#define IO_MMC0_DATA4 12
#define IO_MMC0_DATA3 13
#define IO_MMC0_DATA2 14
#define IO_MMC0_DATA1 15
#define IO_MMC0_DATA0 16

#define IO_MMC1_CLK 17
#define IO_MMC1_CMD 18
#define IO_MMC1_DATA3 19
#define IO_MMC1_DATA2 20
#define IO_MMC1_DATA1 21
#define IO_MMC1_DATA0 22

#define IO_MMC2_CLK 23
#define IO_MMC2_CMD 24
#define IO_MMC2_DATA3 25
#define IO_MMC2_DATA2 26
#define IO_MMC2_DATA1 27
#define IO_MMC2_DATA0 28

#define IO_EMAC_TX_CLK_OUT 29  /*!< EMAC output tx clock             */
#define IO_EMAC_TX_CLK_IN  29  /*!< EMAC input tx clock              */
#define IO_EMAC_REF_OUT    29  /*!< EMAC RMII output ref clock       */
#define IO_EMAC_REF_IN     29  /*!< EMAC RMII input erf clock        */
#define IO_EMAC_RX_CLK_OUT 30  /*!< EMAC output rx clock             */
#define IO_EMAC_RX_CLK_IN  30  /*!< EMAC input rx clock              */
#define IO_EMAC_COL    31  /*!< EMAC Collision detect from the PHY */
#define IO_EMAC_CRS    32  /*!< EMAC Carrier sense from the PHY  */
#define IO_EMAC_TX_ER  33  /*!< EMAC Transmit error signal to the PHY */
#define IO_EMAC_RX_ER  34  /*!< EMAC Receive error signal from the PHY */
#define IO_EMAC_MDC    35  /*!< EMAC Management data clock to pin */
#define IO_EMAC_MDIO   36  /*!< EMAC Management data input/out pin */
#define IO_EMAC_RX_CTL 37  /*!< EMAC Receive control signal from the PHY. */
#define IO_EMAC_TX_CTL 38  /*!< EMAC Transmit control signal to the PHY */
#define IO_EMAC_TX_EN 38  /*!< EMAC RMII Transmit enable to the PHY */
#define IO_EMAC_RX_D3 39  /*!< EMAC Receive data from the PHY   */
#define IO_EMAC_RX_D2 40  /*!< EMAC Receive data from the PHY   */
#define IO_EMAC_RX_D1 41  /*!< EMAC Receive data from the PHY   */
#define IO_EMAC_RX_D0 42  /*!< EMAC Receive data from the PHY   */
#define IO_EMAC_TX_D3 43  /*!< EMAC Transmit data to the PHY    */
#define IO_EMAC_TX_D2 44  /*!< EMAC Transmit data to the PHY    */
#define IO_EMAC_TX_D1 45  /*!< EMAC Transmit data to the PHY    */
#define IO_EMAC_TX_D0 46      

#define IO_SPI0_CLK   86
#define IO_SPI0_CS    87
#define IO_SPI0_D0    88
#define IO_SPI0_D1    89
#define IO_SPI0_D2    90
#define IO_SPI0_D3    91
#define IO_SPI0_D4    92
#define IO_SPI0_D5    93
#define IO_SPI0_D6    94
#define IO_SPI0_D7    95
#define IO_SPI0_ARB   96

#define IO_UART0_RX  112
#define IO_UART0_TX  113

#define LSIO_FUNC_SPI1_D0     0            /*!< SPI0 Data 0                      */
#define LSIO_FUNC_SPI1_D1     1            /*!< SPI0 Data 1                      */
#define LSIO_FUNC_SPI1_D2     2            /*!< SPI0 Data 2                      */
#define LSIO_FUNC_SPI1_D3     3            /*!< SPI0 Data 3                      */
#define LSIO_FUNC_SPI1_D4     4            /*!< SPI0 Data 4                      */
#define LSIO_FUNC_SPI1_D5     5            /*!< SPI0 Data 5                      */
#define LSIO_FUNC_SPI1_D6      6            /*!< SPI0 Data 6                      */
#define LSIO_FUNC_SPI1_D7      7            /*!< SPI0 Data 7                      */
#define LSIO_FUNC_SPI1_SS0     8            /*!< SPI0 Chip Select 0               */
#define LSIO_FUNC_SPI1_SLK    9            /*!< SPI0 Serial Clock                */


#define	FUNC_SPI1_D0                           (0 << 16) | 0        	/*!< SPI0 Data 0                      */
#define	FUNC_SPI1_D1                           (0 << 16) | 1        	/*!< SPI0 Data 1                      */
#define	FUNC_SPI1_D2                           (0 << 16) | 2        	/*!< SPI0 Data 2                      */
#define	FUNC_SPI1_D3                           (0 << 16) | 3        	/*!< SPI0 Data 3                      */
#define	FUNC_SPI1_D4                           (0 << 16) | 4        	/*!< SPI0 Data 4                      */
#define	FUNC_SPI1_D5                           (0 << 16) | 5        	/*!< SPI0 Data 5                      */
#define	FUNC_SPI1_D6                           (0 << 16) | 6        	/*!< SPI0 Data 6                      */
#define	FUNC_SPI1_D7                           (0 << 16) | 7        	/*!< SPI0 Data 7                      */
#define	FUNC_SPI1_SS0                          (0 << 16) | 8        	/*!< SPI0 Chip Select 0               */
#define	FUNC_SPI1_SS1                          (0 << 16) | 9        	/*!< SPI0 Chip Select 1               */
#define	FUNC_SPI1_SS2                          (0 << 16) | 10       	/*!< SPI0 Chip Select 2               */
#define	FUNC_SPI1_SS3                          (0 << 16) | 11       	/*!< SPI0 Chip Select 3               */
#define	FUNC_SPI1_ARB                          (0 << 16) | 12       	/*!< SPI0 Arbitration                 */
#define	FUNC_SPI1_SCLK                         (0 << 16) | 13       	/*!< SPI0 Serial Clock                */
#define	FUNC_GPIO0                             (0 << 16) | 14       	/*!< GPIO pin 0                       */
#define	FUNC_GPIO1                             (0 << 16) | 15       	/*!< GPIO pin 1                       */
#define	FUNC_GPIO2                             (0 << 16) | 16       	/*!< GPIO pin 2                       */
#define	FUNC_GPIO3                             (0 << 16) | 17       	/*!< GPIO pin 3                       */
#define	FUNC_GPIO4                             (0 << 16) | 18       	/*!< GPIO pin 4                       */
#define	FUNC_GPIO5                             (0 << 16) | 19       	/*!< GPIO pin 5                       */
#define	FUNC_GPIO6                             (0 << 16) | 20       	/*!< GPIO pin 6                       */
#define	FUNC_GPIO7                             (0 << 16) | 21       	/*!< GPIO pin 7                       */
#define	FUNC_SPI2_D0                           (0 << 16) | 22       	/*!< SPI1 Data 0                      */
#define	FUNC_SPI2_D1                           (0 << 16) | 23       	/*!< SPI1 Data 1                      */
#define	FUNC_SPI2_D2                           (0 << 16) | 24       	/*!< SPI1 Data 2                      */
#define	FUNC_SPI2_D3                           (0 << 16) | 25       	/*!< SPI1 Data 3                      */
#define	FUNC_SPI2_D4                           (0 << 16) | 26       	/*!< SPI1 Data 4                      */
#define	FUNC_SPI2_D5                           (0 << 16) | 27       	/*!< SPI1 Data 5                      */
#define	FUNC_SPI2_D6                           (0 << 16) | 28       	/*!< SPI1 Data 6                      */
#define	FUNC_SPI2_D7                           (0 << 16) | 29       	/*!< SPI1 Data 7                      */
#define	FUNC_SPI2_SS0                          (0 << 16) | 30       	/*!< SPI1 Chip Select 0               */
#define	FUNC_SPI2_SS1                          (0 << 16) | 31       	/*!< SPI1 Chip Select 1               */
#define	FUNC_SPI2_SS2                          (0 << 16) | 32       	/*!< SPI1 Chip Select 2               */
#define	FUNC_SPI2_SS3                          (0 << 16) | 33       	/*!< SPI1 Chip Select 3               */
#define	FUNC_SPI2_ARB                          (0 << 16) | 34       	/*!< SPI1 Arbitration                 */
#define	FUNC_SPI2_SCLK                         (0 << 16) | 35       	/*!< SPI1 Serial Clock                */
#define	FUNC_SPI3_D0                           (0 << 16) | 36       	/*!< SPI1 Data 0                      */
#define	FUNC_SPI3_D1                           (0 << 16) | 37       	/*!< SPI1 Data 1                      */
#define	FUNC_SPI3_D2                           (0 << 16) | 38       	/*!< SPI1 Data 2                      */
#define	FUNC_SPI3_D3                           (0 << 16) | 39       	/*!< SPI1 Data 3                      */
#define	FUNC_SPI3_D4                           (0 << 16) | 40       	/*!< SPI1 Data 4                      */
#define	FUNC_SPI3_D5                           (0 << 16) | 41       	/*!< SPI1 Data 5                      */
#define	FUNC_SPI3_D6                           (0 << 16) | 42       	/*!< SPI1 Data 6                      */
#define	FUNC_SPI3_D7                           (0 << 16) | 43       	/*!< SPI1 Data 7                      */
#define	FUNC_SPI3_SS0                          (0 << 16) | 44       	/*!< SPI1 Chip Select 0               */
#define	FUNC_SPI3_SS1                          (0 << 16) | 45       	/*!< SPI1 Chip Select 1               */
#define	FUNC_SPI3_SS2                          (0 << 16) | 46       	/*!< SPI1 Chip Select 2               */
#define	FUNC_SPI3_SS3                          (0 << 16) | 47       	/*!< SPI1 Chip Select 3               */
#define	FUNC_SPI3_ARB                          (0 << 16) | 48       	/*!< SPI1 Arbitration                 */
#define	FUNC_SPI3_SCLK                         (0 << 16) | 49       	/*!< SPI1 Serial Clock                */
#define	FUNC_SPI_SLAVE_D0                      (0 << 16) | 50       	/*!< SPI Slave Data 0                 */
#define	FUNC_SPI_SLAVE_SS                      (0 << 16) | 51       	/*!< SPI Slave Select                 */
#define	FUNC_SPI_SLAVE_SCLK                    (0 << 16) | 52       	/*!< SPI Slave Serial Clock           */
#define	FUNC_I2S2SCLK                          (0 << 16) | 53       	/*!< I2S0 Serial Clock(BCLK)          */
#define	FUNC_I2S2WS                            (0 << 16) | 54       	/*!< I2S0 Word Select(LRCLK)          */
#define	FUNC_I2S2IN_D0                         (0 << 16) | 55       	/*!< I2S0 Serial Data Input 0         */
#define	FUNC_I2S2IN_D1                         (0 << 16) | 56       	/*!< I2S0 Serial Data Input 1         */
#define	FUNC_I2S2IN_D2                         (0 << 16) | 57       	/*!< I2S0 Serial Data Input 2         */
#define	FUNC_I2S2IN_D3                         (0 << 16) | 58       	/*!< I2S0 Serial Data Input 3         */
#define	FUNC_I2S2OUT_D0                        (0 << 16) | 59       	/*!< I2S0 Serial Data Output 0        */
#define	FUNC_I2S2OUT_D1                        (0 << 16) | 60       	/*!< I2S0 Serial Data Output 1        */
#define	FUNC_I2S2OUT_D2                        (0 << 16) | 61       	/*!< I2S0 Serial Data Output 2        */
#define	FUNC_I2S2OUT_D3                        (0 << 16) | 62       	/*!< I2S0 Serial Data Output 3        */
#define	FUNC_I2C0_SCLK                         (0 << 16) | 63       	/*!< I2C0 Serial Clock                */
#define	FUNC_I2C0_SDA                          (0 << 16) | 64       	/*!< I2C0 Serial Data                 */
#define	FUNC_I2C1_SCLK                         (0 << 16) | 65       	/*!< I2C1 Serial Clock                */
#define	FUNC_I2C1_SDA                          (0 << 16) | 66       	/*!< I2C1 Serial Data                 */
#define	FUNC_I2C2_SCLK                         (0 << 16) | 67       	/*!< I2C2 Serial Clock                */
#define	FUNC_I2C2_SDA                          (0 << 16) | 68       	/*!< I2C2 Serial Data                 */
#define	FUNC_UART1_CTS                         (0 << 16) | 69       	/*!< UART1 Clear To Send              */
#define	FUNC_UART1_DSR                         (0 << 16) | 70       	/*!< UART1 Data Set Ready             */
#define	FUNC_UART1_DCD                         (0 << 16) | 71       	/*!< UART1 Data Carrier Detect        */
#define	FUNC_UART1_RI                          (0 << 16) | 72       	/*!< UART1 Ring Indicator             */
#define FUNC_UART1_RX ((0 << 16) | 73)

#define	FUNC_UART1_SIR_IN                      (0 << 16) | 74       	/*!< UART1 Serial Infrared Input      */
#define	FUNC_UART1_DTR                         (0 << 16) | 75       	/*!< UART1 Data Terminal Ready        */
#define	FUNC_UART1_RTS                         (0 << 16) | 76       	/*!< UART1 Request To Send            */
#define	FUNC_UART1_OUT2                        (0 << 16) | 77       	/*!< UART1 User-designated Output 2   */
#define	FUNC_UART1_OUT1                        (0 << 16) | 78       	/*!< UART1 User-designated Output 1   */

#define FUNC_UART1_TX ((0 << 16) | 79)

#define	FUNC_UART1_SIR_OUT                     (0 << 16) | 80       	/*!< UART1 Serial Infrared Output     */
#define	FUNC_UART1_BAUD                        (0 << 16) | 81       	/*!< UART1 Transmit Clock Output      */
#define	FUNC_UART1_RE                          (0 << 16) | 82       	/*!< UART1 Receiver Output Enable     */
#define	FUNC_UART1_DE                          (0 << 16) | 83       	/*!< UART1 Driver Output Enable       */
#define	FUNC_UART1_RS485_EN                    (0 << 16) | 84       	/*!< UART1 RS485 Enable               */
#define	FUNC_UART2_CTS                         (0 << 16) | 85       	/*!< UART2 Clear To Send              */
#define	FUNC_UART2_DSR                         (0 << 16) | 86       	/*!< UART2 Data Set Ready             */
#define	FUNC_UART2_DCD                         (0 << 16) | 87       	/*!< UART2 Data Carrier Detect        */
#define	FUNC_UART2_RI                          (0 << 16) | 88       	/*!< UART2 Ring Indicator             */
#define	FUNC_UART2_RX                          (0 << 16) | 89       	/*!<                                  */
#define	FUNC_UART2_SIR_IN                      (0 << 16) | 90       	/*!< UART2 Serial Infrared Input      */
#define	FUNC_UART2_DTR                         (0 << 16) | 91       	/*!< UART2 Data Terminal Ready        */
#define	FUNC_UART2_RTS                         (0 << 16) | 92       	/*!< UART2 Request To Send            */
#define	FUNC_UART2_OUT2                        (0 << 16) | 93       	/*!< UART2 User-designated Output 2   */
#define	FUNC_UART2_OUT1                        (0 << 16) | 94       	/*!< UART2 User-designated Output 1   */
#define	FUNC_UART2_TX                          (0 << 16) | 95       	/*!<                                  */
#define	FUNC_UART2_SIR_OUT                     (0 << 16) | 96       	/*!< UART2 Serial Infrared Output     */
#define	FUNC_UART2_BAUD                        (0 << 16) | 97       	/*!< UART2 Transmit Clock Output      */
#define	FUNC_UART2_RE                          (0 << 16) | 98       	/*!< UART2 Receiver Output Enable     */
#define	FUNC_UART2_DE                          (0 << 16) | 99       	/*!< UART2 Driver Output Enable       */
#define	FUNC_UART2_RS485_EN                    (0 << 16) | 100      	/*!< UART2 RS485 Enable               */
#define	FUNC_UART3_CTS                         (0 << 16) | 101      	/*!< UART3 Clear To Send              */
#define	FUNC_UART3_DSR                         (0 << 16) | 102      	/*!< UART3 Data Set Ready             */
#define	FUNC_UART3_DCD                         (0 << 16) | 103      	/*!< UART3 Data Carrier Detect        */
#define	FUNC_UART3_RI                          (0 << 16) | 104      	/*!< UART3 Ring Indicator             */
#define	FUNC_UART3_RX                          (0 << 16) | 105      	/*!<                                  */
#define	FUNC_UART3_SIR_IN                      (0 << 16) | 106      	/*!< UART3 Serial Infrared Input      */
#define	FUNC_UART3_DTR                         (0 << 16) | 107      	/*!< UART3 Data Terminal Ready        */
#define	FUNC_UART3_RTS                         (0 << 16) | 108      	/*!< UART3 Request To Send            */
#define	FUNC_UART3_OUT2                        (0 << 16) | 109      	/*!< UART3 User-designated Output 2   */
#define	FUNC_UART3_OUT1                        (0 << 16) | 110      	/*!< UART3 User-designated Output 1   */
#define	FUNC_UART3_TX                          (0 << 16) | 111      	/*!<                                  */
#define	FUNC_UART3_SIR_OUT                     (0 << 16) | 112      	/*!< UART3 Serial Infrared Output     */
#define	FUNC_UART3_BAUD                        (0 << 16) | 113      	/*!< UART3 Transmit Clock Output      */
#define	FUNC_UART3_RE                          (0 << 16) | 114      	/*!< UART3 Receiver Output Enable     */
#define	FUNC_UART3_DE                          (0 << 16) | 115      	/*!< UART3 Driver Output Enable       */
#define	FUNC_UART3_RS485_EN                    (0 << 16) | 116      	/*!< UART3 RS485 Enable               */
#define	FUNC_CLK_SPI2                          (0 << 16) | 117      	/*!< Clock SPI2                       */
#define	FUNC_CLK_I2C2                          (0 << 16) | 118      	/*!< Clock I2C2                       */
#define	FUNC_AUDO_FSYNC                        (0 << 16) | 119      	/*!<                                  */
#define	FUNC_AUDIO_IN0                         (0 << 16) | 120      	/*!<                                  */
#define	FUNC_AUDIO_IN1                         (0 << 16) | 121      	/*!<                                  */
#define	FUNC_AUDIO_IN2                         (0 << 16) | 122      	/*!<                                  */
#define	FUNC_AUDIO_IN3                         (0 << 16) | 123      	/*!<                                  */
#define	FUNC_AUDIO_IN4                         (0 << 16) | 124      	/*!<                                  */
#define	FUNC_AUDIO_IN5                         (0 << 16) | 125      	/*!<                                  */
#define	FUNC_AUDIO_IN6                         (0 << 16) | 126      	/*!<                                  */
#define	FUNC_AUDIO_IN7                         (0 << 16) | 127      	/*!<                                  */
#define	FUNC_AUDIO_IN8                         (0 << 16) | 128      	/*!<                                  */
#define	FUNC_AUDIO_IN9                         (0 << 16) | 129      	/*!<                                  */
#define	FUNC_AUDIO_IN10                        (0 << 16) | 130      	/*!<                                  */
#define	FUNC_AUDIO_IN11                        (0 << 16) | 131      	/*!<                                  */
#define	FUNC_AUDIO_IN12                        (0 << 16) | 132      	/*!<                                  */
#define	FUNC_AUDIO_IN13                        (0 << 16) | 133      	/*!<                                  */
#define	FUNC_AUDIO_IN14                        (0 << 16) | 134      	/*!<                                  */
#define	FUNC_AUDIO_IN15                        (0 << 16) | 135      	/*!<                                  */
#define	FUNC_AUDIO_OUT0                        (0 << 16) | 136      	/*!<                                  */
#define	FUNC_AUDIO_OUT1                        (0 << 16) | 137      	/*!<                                  */
#define	FUNC_AUDIO_OUT2                        (0 << 16) | 138      	/*!<                                  */
#define	FUNC_AUDIO_OUT3                        (0 << 16) | 139      	/*!<                                  */
#define	FUNC_AUDIO_OUT4                        (0 << 16) | 140      	/*!<                                  */
#define	FUNC_AUDIO_OUT5                        (0 << 16) | 141      	/*!<                                  */
#define	FUNC_AUDIO_OUT6                        (0 << 16) | 142      	/*!<                                  */
#define	FUNC_AUDIO_OUT7                        (0 << 16) | 143      	/*!<                                  */
#define	FUNC_SCLK_GATE                         (0 << 16) | 144      	/*!<                                  */
#define	FUNC_SCLK_EN                           (0 << 16) | 145      	/*!<                                  */
#define	FUNC_WS_OUT                            (0 << 16) | 146      	/*!<                                  */
#define	FUNC_TDM_FSYNC                         (0 << 16) | 147      	/*!<                                  */
#define	FUNC_VAD_IN_DATA                       (0 << 16) | 148      	/*!<                                  */
#define	FUNC_VAD_FSYNC                         (0 << 16) | 149      	/*!<                                  */
#define	FUNC_PWM_PINS_1_IO_PINS_PWM_0_O_OVAL   (0 << 16) | 150      	/*!<                                  */
#define	FUNC_PWM_PINS_1_IO_PINS_PWM_1_O_OVAL   (0 << 16) | 151      	/*!<                                  */
#define	FUNC_PWM_PINS_1_IO_PINS_PWM_2_O_OVAL   (0 << 16) | 152      	/*!<                                  */
#define	FUNC_PWM_PINS_1_IO_PINS_PWM_3_O_OVAL   (0 << 16) | 153      	/*!<                                  */
#define	FUNC_LSRESV0                           (0 << 16) | 154      	/*!<                                  */
#define	FUNC_LSRESV1                           (0 << 16) | 155      	/*!<                                  */
#define	FUNC_LSRESV2                           (0 << 16) | 156      	/*!<                                  */
#define	FUNC_LSRESV3                           (0 << 16) | 157      	/*!<                                  */
#define	FUNC_LSRESV4                           (0 << 16) | 158      	/*!<                                  */
#define	FUNC_LSRESV5                           (0 << 16) | 159      	/*!<                                  */
#define	FUNC_LSRESV6                           (0 << 16) | 160      	/*!<                                  */
#define	FUNC_LSRESV7                           (0 << 16) | 161      	/*!<                                  */
#define	FUNC_LSRESV8                           (0 << 16) | 162      	/*!<                                  */
#define	FUNC_LSRESV9                           (0 << 16) | 163      	/*!<                                  */
#define	FUNC_LSRESV10                          (0 << 16) | 164      	/*!<                                  */
#define	FUNC_LSRESV11                          (0 << 16) | 165      	/*!<                                  */
#define	FUNC_LSRESV12                          (0 << 16) | 166      	/*!<                                  */
#define	FUNC_LSRESV13                          (0 << 16) | 167      	/*!<                                  */
#define	FUNC_LSRESV14                          (0 << 16) | 168      	/*!<                                  */
#define	FUNC_LSRESV15                          (0 << 16) | 169      	/*!<                                  */
#define	FUNC_LSRESV16                          (0 << 16) | 170      	/*!<                                  */
#define	FUNC_LSRESV17                          (0 << 16) | 171      	/*!<                                  */
#define	FUNC_LSRESV18                          (0 << 16) | 172      	/*!<                                  */
#define	FUNC_LSRESV19                          (0 << 16) | 173      	/*!<                                  */
#define	FUNC_LSRESV20                          (0 << 16) | 174      	/*!<                                  */
#define	FUNC_LSRESV21                          (0 << 16) | 175      	/*!<                                  */
#define	FUNC_LSRESV22                          (0 << 16) | 176      	/*!<                                  */
#define	FUNC_LSRESV23                          (0 << 16) | 177      	/*!<                                  */
#define	FUNC_LSRESV24                          (0 << 16) | 178      	/*!<                                  */
#define	FUNC_LSRESV25                          (0 << 16) | 179      	/*!<                                  */
#define	FUNC_LSRESV26                          (0 << 16) | 180      	/*!<                                  */
#define	FUNC_LSRESV27                          (0 << 16) | 181      	/*!<                                  */
#define	FUNC_LSRESV28                          (0 << 16) | 182      	/*!<                                  */
#define	FUNC_LSRESV29                          (0 << 16) | 183      	/*!<                                  */
#define	FUNC_LSRESV30                          (0 << 16) | 184      	/*!<                                  */
#define	FUNC_LSRESV31                          (0 << 16) | 185      	/*!<                                  */
#define	FUNC_LSRESV32                          (0 << 16) | 186      	/*!<                                  */
#define	FUNC_LSRESV33                          (0 << 16) | 187          /*!<                                  */
#define	FUNC_LSRESV34                          (0 << 16) | 188      	/*!<                                  */
#define	FUNC_LSRESV35                          (0 << 16) | 189      	/*!<                                  */
#define	FUNC_LSRESV36                          (0 << 16) | 190      	/*!<                                  */
#define	FUNC_LSRESV37                          (0 << 16) | 191      	/*!<                                  */
#define	FUNC_LSRESV38                          (0 << 16) | 192      	/*!<                                  */
#define	FUNC_LSRESV39                          (0 << 16) | 193      	/*!<                                  */
#define	FUNC_LSRESV40                          (0 << 16) | 194      	/*!<                                  */
#define	FUNC_LSRESV41                          (0 << 16) | 195      	/*!<                                  */
#define	FUNC_LSRESV42                          (0 << 16) | 196      	/*!<                                  */
#define	FUNC_LSRESV43                          (0 << 16) | 197      	/*!<                                  */
#define	FUNC_LSRESV44                          (0 << 16) | 198      	/*!<                                  */
#define	FUNC_LSRESV45                          (0 << 16) | 199      	/*!<                                  */
#define	FUNC_LSRESV46                          (0 << 16) | 200      	/*!<                                  */
#define	FUNC_LSRESV47                          (0 << 16) | 201      	/*!<                                  */
#define	FUNC_LSRESV48                          (0 << 16) | 202      	/*!<                                  */
#define	FUNC_LSRESV49                          (0 << 16) | 203      	/*!<                                  */
#define	FUNC_LSRESV50                          (0 << 16) | 204      	/*!<                                  */
#define	FUNC_LSRESV51                          (0 << 16) | 205      	/*!<                                  */
#define	FUNC_LSRESV52                          (0 << 16) | 206      	/*!<                                  */
#define	FUNC_LSRESV53                          (0 << 16) | 207      	/*!<                                  */
#define	FUNC_LSRESV54                          (0 << 16) | 208      	/*!<                                  */
#define	FUNC_LSRESV55                          (0 << 16) | 209      	/*!<                                  */
#define	FUNC_LSRESV56                          (0 << 16) | 210      	/*!<                                  */
#define	FUNC_LSRESV57                          (0 << 16) | 211      	/*!<                                  */
#define	FUNC_LSRESV58                          (0 << 16) | 212      	/*!<                                  */
#define	FUNC_LSRESV59                          (0 << 16) | 213      	/*!<                                  */
#define	FUNC_LSRESV60                          (0 << 16) | 214      	/*!<                                  */
#define	FUNC_LSRESV61                          (0 << 16) | 215      	/*!<                                  */
#define	FUNC_LSRESV62                          (0 << 16) | 216      	/*!<                                  */
#define	FUNC_LSRESV63                          (0 << 16) | 217      	/*!<                                  */
#define	FUNC_LSRESV64                          (0 << 16) | 218      	/*!<                                  */
#define	FUNC_LSRESV65                          (0 << 16) | 219      	/*!<                                  */
#define	FUNC_LSRESV66                          (0 << 16) | 220      	/*!<                                  */
#define	FUNC_LSRESV67                          (0 << 16) | 221      	/*!<                                  */
#define	FUNC_LSRESV68                          (0 << 16) | 222      	/*!<                                  */
#define	FUNC_LSRESV69                          (0 << 16) | 223      	/*!<                                  */
#define	FUNC_LSRESV70                          (0 << 16) | 224      	/*!<                                  */
#define	FUNC_LSRESV71                          (0 << 16) | 225      	/*!<                                  */
#define	FUNC_LSRESV72                          (0 << 16) | 226      	/*!<                                  */
#define	FUNC_LSRESV73                          (0 << 16) | 227      	/*!<                                  */
#define	FUNC_LSRESV74                          (0 << 16) | 228      	/*!<                                  */
#define	FUNC_LSRESV75                          (0 << 16) | 229      	/*!<                                  */
#define	FUNC_LSRESV76                          (0 << 16) | 230      	/*!<                                  */
#define	FUNC_LSRESV77                          (0 << 16) | 231      	/*!<                                  */
#define	FUNC_LSRESV78                          (0 << 16) | 232      	/*!<                                  */
#define	FUNC_LSRESV79                          (0 << 16) | 233      	/*!<                                  */
#define	FUNC_LSRESV80                          (0 << 16) | 234      	/*!<                                  */
#define	FUNC_LSRESV81                          (0 << 16) | 235      	/*!<                                  */
#define	FUNC_LSRESV82                          (0 << 16) | 236      	/*!<                                  */
#define	FUNC_LSRESV83                          (0 << 16) | 237      	/*!<                                  */
#define	FUNC_LSRESV84                          (0 << 16) | 238      	/*!<                                  */
#define	FUNC_LSRESV85                          (0 << 16) | 239      	/*!<                                  */
#define	FUNC_LSRESV86                          (0 << 16) | 240      	/*!<                                  */
#define	FUNC_LSRESV87                          (0 << 16) | 241      	/*!<                                  */
#define	FUNC_LSRESV88                          (0 << 16) | 242      	/*!<                                  */
#define	FUNC_LSRESV89                          (0 << 16) | 243      	/*!<                                  */
#define	FUNC_LSRESV90                          (0 << 16) | 244      	/*!<                                  */
#define	FUNC_LSRESV91                          (0 << 16) | 245      	/*!<                                  */
#define	FUNC_LSRESV92                          (0 << 16) | 246      	/*!<                                  */
#define	FUNC_LSRESV93                          (0 << 16) | 247      	/*!<                                  */
#define	FUNC_LSRESV94                          (0 << 16) | 248      	/*!<                                  */
#define	FUNC_LSRESV95                          (0 << 16) | 249      	/*!<                                  */
#define	FUNC_LSRESV96                          (0 << 16) | 250      	/*!<                                  */
#define	FUNC_LSRESV97                          (0 << 16) | 251      	/*!<                                  */
#define	FUNC_LSRESV98                          (0 << 16) | 252      	/*!<                                  */
#define	FUNC_LSRESV99                          (0 << 16) | 253      	/*!<                                  */
#define	FUNC_LSRESV100                         (0 << 16) | 254      	/*!<                                  */
#define	FUNC_LSRESV_MAX                        (0 << 16) | 255      	/*!<                                  */
#define	FUNC_RESET                             (0 << 16) | 256      	/*!<                                  */
#define	FUNC_CLK25M_IN                         (1 << 16) | 257      	/*!<                                  */
#define	FUNC_CLK25M_OUT                        (2 << 16) | 258      	/*!<                                  */
#define	FUNC_CLK32K_IN                         (3 << 16) | 259      	/*!<                                  */
#define	FUNC_CLK32K_OUT                        (4 << 16) | 260      	/*!<                                  */
#define	FUNC_TESTEN                            (5 << 16) | 261      	/*!<                                  */
#define	FUNC_BOOT_CTL1                         (6 << 16) | 262      	/*!<                                  */
#define	FUNC_BOOT_CTL0                         (7 << 16) | 263      	/*!<                                  */
#define	FUNC_JTAG_TCK                          (8 << 16) | 264      	/*!<                                  */
#define	FUNC_JTAG_TDI                          (9 << 16) | 265      	/*!<                                  */
#define	FUNC_JTAG_TDO                          (10 << 16) | 266     	/*!<                                  */
#define	FUNC_JTAG_TMS                          (11 << 16) | 267     	/*!<                                  */
#define	FUNC_JTAG_NTRS                         (12 << 16) | 268     	/*!<                                  */
#define	FUNC_TEST_PIN0                         (8 << 16) | 269      	/*!<                                  */
#define	FUNC_TEST_PIN1                         (9 << 16) | 270      	/*!<                                  */
#define	FUNC_TEST_PIN2                         (10 << 16) | 271     	/*!<                                  */
#define	FUNC_TEST_PIN3                         (11 << 16) | 272     	/*!<                                  */
#define	FUNC_TEST_PIN4                         (12 << 16) | 273     	/*!<                                  */
#define	FUNC_MMC0_CLK                          (13 << 16) | 274     	/*!<                                  */
#define	FUNC_MMC0_CMD                          (14 << 16) | 275     	/*!<                                  */
#define	FUNC_MMC0_DATA7                        (15 << 16) | 276     	/*!<                                  */
#define	FUNC_MMC0_DATA6                        (16 << 16) | 277     	/*!<                                  */
#define	FUNC_MMC0_DATA5                        (17 << 16) | 278     	/*!<                                  */
#define	FUNC_MMC0_DATA4                        (18 << 16) | 279     	/*!<                                  */
#define	FUNC_MMC0_DATA3                        (19 << 16) | 280     /*!<                                  */
#define	FUNC_MMC0_DATA2                        (20 << 16) | 281     /*!<                                  */
#define	FUNC_MMC0_DATA1                        (21 << 16) | 282     /*!<                                  */
#define	FUNC_MMC0_DATA0                        (22 << 16) | 283      /*!<                                  */
#define	FUNC_SPI0_CLK                          (13 << 16) | 284      /*!<                                  */
#define	FUNC_SPI0_CS                           (14 << 16) | 285      /*!<                                  */
#define	FUNC_SPI0_D7                           (15 << 16) | 286      	/*!<                                  */
#define	FUNC_SPI0_D6                           (16 << 16) | 287      	/*!<                                  */
#define	FUNC_SPI0_D5                           (17 << 16) | 288      	/*!<                                  */
#define	FUNC_SPI0_D4                           (18 << 16) | 289      	/*!<                                  */
#define	FUNC_SPI0_D3                           (19 << 16) | 290      	/*!<                                  */
#define	FUNC_SPI0_D2                           (20 << 16) | 291      	/*!<                                  */
#define	FUNC_SPI0_D1                           (21 << 16) | 292      	/*!<                                  */
#define	FUNC_SPI0_D0                           (22 << 16) | 293      	/*!<                                  */
#define	FUNC_MMC1_CLK                          (23 << 16) | 294      	/*!<                                  */
#define	FUNC_MMC1_CMD                          (24 << 16) | 295      	/*!<                                  */
#define	FUNC_MMC1_DATA3                        (25 << 16) | 296      	/*!<                                  */
#define	FUNC_MMC1_DATA2                        (26 << 16) | 297      	/*!<                                  */
#define	FUNC_MMC1_DATA1                        (27 << 16) | 298      	/*!<                                  */
#define	FUNC_MMC1_DATA0                        (28 << 16) | 299      	/*!<                                  */
#define	FUNC_MMC2_CLK                          (29 << 16) | 300      	/*!<                                  */
#define	FUNC_MMC2_CMD                          (30 << 16) | 301      	/*!<                                  */
#define	FUNC_MMC2_DATA3                        (31 << 16) | 302      	/*!<                                  */
#define	FUNC_MMC2_DATA2                        (32 << 16) | 303      	/*!<                                  */
#define	FUNC_MMC2_DATA1                        (33 << 16) | 304      	/*!<                                  */
#define	FUNC_MMC2_DATA0                        (34 << 16) | 305      /*!<                                  */
#define	FUNC_EMAC_TX_CLK_OUT                   (35 << 16) | 306      	/*!< EMAC output tx clock             */
#define	FUNC_EMAC_TX_CLK_IN                    (35 << 16) | 307      	/*!< EMAC input tx clock              */
#define	FUNC_EMAC_REF_OUT                      (35 << 16) | 308      	/*!< EMAC RMII output ref clock       */
#define	FUNC_EMAC_REF_IN                       (35 << 16) | 309      	/*!< EMAC RMII input erf clock        */
#define	FUNC_EMAC_RX_CLK_OUT                   (36 << 16) | 310      	/*!< EMAC output rx clock             */
#define	FUNC_EMAC_RX_CLK_IN                    (36 << 16) | 311      	/*!< EMAC input rx clock              */
#define	FUNC_EMAC_COL                          (37 << 16) | 312      	/*!< EMAC Collision detect from the PHY */
#define	FUNC_EMAC_CRS                          (38 << 16) | 313      	/*!< EMAC Carrier sense from the PHY  */
#define	FUNC_EMAC_TX_ER                        (39 << 16) | 314      	/*!< EMAC Transmit error signal to the PHY */
#define	FUNC_EMAC_RX_ER                        (40 << 16) | 315      /*!< EMAC Receive error signal from the PHY */
#define	FUNC_EMAC_MDC                          (41 << 16) | 316      	/*!< EMAC Management data clock to pin */
#define	FUNC_EMAC_MDIO                         (42 << 16) | 317      /*!< EMAC Management data input/out pin */
#define	FUNC_EMAC_RX_CTL                       (43 << 16) | 318      	/*!< EMAC Receive control signal from the PHY. */
#define	FUNC_EMAC_TX_CTL                       (44 << 16) | 319      /*!< EMAC Transmit control signal to the PHY */
#define	FUNC_EMAC_TX_EN                        (45 << 16) | 320      	/*!< EMAC RMII Transmit enable to the PHY */
#define	FUNC_EMAC_RX_D3                        (45 << 16) | 321      	/*!< EMAC Receive data from the PHY   */
#define	FUNC_EMAC_RX_D2                        (46 << 16) | 322      	/*!< EMAC Receive data from the PHY   */
#define	FUNC_EMAC_RX_D1                        (47 << 16) | 323      	/*!< EMAC Receive data from the PHY   */
#define	FUNC_EMAC_RX_D0                        (48 << 16) | 324      	/*!< EMAC Receive data from the PHY   */
#define	FUNC_EMAC_TX_D3                        (49 << 16) | 325      	/*!< EMAC Transmit data to the PHY    */
#define	FUNC_EMAC_TX_D2                        (50 << 16) | 326      	/*!< EMAC Transmit data to the PHY    */
#define	FUNC_EMAC_TX_D1                        (51 << 16) | 327      	/*!< EMAC Transmit data to the PHY    */
#define	FUNC_EMAC_TX_D0                        (52 << 16) | 328      	/*!< EMAC Transmit data to the PHY    */
#define	FUNC_DVP_D0                            (53 << 16) | 329      	/*!<                                  */
#define	FUNC_DVP_D1                            (54 << 16) | 330      	/*!<                                  */
#define	FUNC_DVP_D2                            (55 << 16) | 331      	/*!<                                  */
#define	FUNC_DVP_D3                            (56 << 16) | 332      	/*!<                                  */
#define	FUNC_DVP_D4                            (57 << 16) | 333      	/*!<                                  */
#define	FUNC_DVP_D5                            (58 << 16) | 334      	/*!<                                  */
#define	FUNC_DVP_D6                            (59 << 16) | 335      	/*!<                                  */
#define	FUNC_DVP_D7                            (60 << 16) | 336      	/*!<                                  */
#define	FUNC_DVP_D8                            (61 << 16) | 337      	/*!<                                  */
#define	FUNC_DVP_D9                            (62 << 16) | 338      	/*!<                                  */
#define	FUNC_DVP_D10                           (63 << 16) | 339      	/*!<                                  */
#define	FUNC_DVP_D11                           (64 << 16) | 340      	/*!<                                  */
#define	FUNC_DVP_D12                           (65 << 16) | 341      	/*!<                                  */
#define	FUNC_DVP_D13                           (66 << 16) | 342      	/*!<                                  */
#define	FUNC_DVP_D14                           (67 << 16) | 343      	/*!<                                  */
#define	FUNC_DVP_D15                           (68 << 16) | 344      	/*!<                                  */
#define	FUNC_DVP_VSYNC                         (69 << 16) | 345      	/*!<                                  */
#define	FUNC_DVP_HREF                          (70 << 16) | 346      	/*!<                                  */
#define	FUNC_DVP_PCLK                          (71 << 16) | 347      	/*!<                                  */
#define	FUNC_BT1120_D0                         (53 << 16) | 348      	/*!<                                  */
#define	FUNC_BT1120_D1                         (54 << 16) | 349      	/*!<                                  */
#define	FUNC_BT1120_D2                         (55 << 16) | 350      	/*!<                                  */
#define	FUNC_BT1120_D3                         (56 << 16) | 351      	/*!<                                  */
#define	FUNC_BT1120_D4                         (57 << 16) | 352      	/*!<                                  */
#define	FUNC_BT1120_D5                         (58 << 16) | 353      	/*!<                                  */
#define	FUNC_BT1120_D6                         (59 << 16) | 354      	/*!<                                  */
#define	FUNC_BT1120_D7                         (60 << 16) | 355      	/*!<                                  */
#define	FUNC_BT1120_D8                         (61 << 16) | 356      	/*!<                                  */
#define	FUNC_BT1120_D9                         (62 << 16) | 357      	/*!<                                  */
#define	FUNC_BT1120_D10                        (63 << 16) | 358      	/*!<                                  */
#define	FUNC_BT1120_D11                        (64 << 16) | 359      	/*!<                                  */
#define	FUNC_BT1120_D12                        (65 << 16) | 360      	/*!<                                  */
#define	FUNC_BT1120_D13                        (66 << 16) | 361      	/*!<                                  */
#define	FUNC_BT1120_D14                        (67 << 16) | 362      	/*!<                                  */
#define	FUNC_BT1120_D15                        (68 << 16) | 363      	/*!<                                  */
#define	FUNC_BT1120_PCLK                       (69 << 16) | 364      	/*!<                                  */
#define	FUNC_MUX                               (255 << 16) | 365     	/*!<                                  */
