/* u8g2_d_setup.c */
/* generated code, codebuild, u8g2 project */

#include "u8g2.h"
#include "stm32g0xx_hal.h"

//-----------------OLED∂Àø⁄∂®“Â----------------

#define OLED_SCLK_Clr() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET) // CLK π‹Ω≈≈‰÷√
#define OLED_SCLK_Set() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET)

#define OLED_SDIN_Clr() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET) // DIN π‹Ω≈≈‰÷√
#define OLED_SDIN_Set() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET)

#define OLED_DC_Clr() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET) // DC π‹Ω≈≈‰÷√
#define OLED_DC_Set() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET)

#define OLED_CS_Clr() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET) // CS π‹Ω≈≈‰÷√
#define OLED_CS_Set() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET)

/* ssd1305 */
/* ssd1305 1 */

/* ssd1306 f */
void u8g2_Setup_ssd1306_128x64_noname_f(u8g2_t *u8g2, const u8g2_cb_t *rotation, u8x8_msg_cb byte_cb, u8x8_msg_cb gpio_and_delay_cb)
{
  uint8_t tile_buf_height;
  uint8_t *buf;
  u8g2_SetupDisplay(u8g2, u8x8_d_ssd1306_128x64_noname, u8x8_cad_001, byte_cb, gpio_and_delay_cb);
  buf = u8g2_m_16_8_f(&tile_buf_height);
  u8g2_SetupBuffer(u8g2, buf, tile_buf_height, u8g2_ll_hvline_vertical_top_lsb, rotation);
}

uint8_t u8x8_gpio_and_delay(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr)
{
  switch (msg)
  {
  case U8X8_MSG_GPIO_SPI_DATA:
    if (arg_int)
      OLED_SDIN_Set();
    else
      OLED_SDIN_Clr();
    break;
  case U8X8_MSG_GPIO_SPI_CLOCK:
    if (arg_int)
      OLED_SCLK_Set();
    else
      OLED_SCLK_Clr();
    break;
  case U8X8_MSG_GPIO_AND_DELAY_INIT:
    OLED_Init();
    HAL_Delay(1);
    break;
  case U8X8_MSG_DELAY_MILLI:
    HAL_Delay(arg_int);
    break;
  case U8X8_MSG_GPIO_CS:
    if (arg_int)
      OLED_CS_Set();
    else
      OLED_CS_Clr();
  case U8X8_MSG_GPIO_DC:
    if (arg_int)
      OLED_DC_Set();
    else
      OLED_DC_Clr();
    break;
  case U8X8_MSG_GPIO_RESET:
    break;
  }
  return 1;
}

void u8g2_Init(u8g2_t *u8g2)
{
  u8g2_Setup_ssd1306_128x64_noname_f(u8g2, U8G2_R0, u8x8_byte_4wire_sw_spi, u8x8_gpio_and_delay);
  u8g2_InitDisplay(u8g2);
  u8g2_SetPowerSave(u8g2, 0);
  u8g2_SetFontMode(u8g2, 1);
  u8g2_SetFontDirection(u8g2, 0);
  u8g2_SetFont(u8g2, u8g2_font_6x10_mf);
  u8g2_ClearBuffer(u8g2);
}