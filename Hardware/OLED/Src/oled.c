
#include "oled.h"
#include "oledfont.h"

void OLED_WR_Byte(u8 dat, u8 cmd)
{
	u8 i;
	if (cmd)
		OLED_DC_Set();
	else
		OLED_DC_Clr();
	OLED_CS_Clr();
	for (i = 0; i < 8; i++)
	{
		OLED_SCLK_Clr();
		if (dat & 0x80)
			OLED_SDIN_Set();
		else
			OLED_SDIN_Clr();
		OLED_SCLK_Set();
		dat <<= 1;
	}
	OLED_CS_Set();
	OLED_DC_Set();
}

void OLED_Set_Pos(unsigned char x, unsigned char y)
{
	OLED_WR_Byte(0xb0 + y, OLED_CMD);
	OLED_WR_Byte(((x & 0xf0) >> 4) | 0x10, OLED_CMD);
	OLED_WR_Byte((x & 0x0f) | 0x01, OLED_CMD);
}

void OLED_Display_On(void)
{
	OLED_WR_Byte(0X8D, OLED_CMD);
	OLED_WR_Byte(0X14, OLED_CMD);
	OLED_WR_Byte(0XAF, OLED_CMD);
}

void OLED_Display_Off(void)
{
	OLED_WR_Byte(0X8D, OLED_CMD);
	OLED_WR_Byte(0X10, OLED_CMD);
	OLED_WR_Byte(0XAE, OLED_CMD);
}

void OLED_Clear(void)
{
	u8 i, n;
	for (i = 0; i < 8; i++)
	{
		OLED_WR_Byte(0xb0 + i, OLED_CMD);
		OLED_WR_Byte(0x00, OLED_CMD);
		OLED_WR_Byte(0x10, OLED_CMD);
		for (n = 0; n < 128; n++)
			OLED_WR_Byte(0, OLED_DATA);
	}
}

void OLED_ShowChar(u8 x, u8 y, u8 chr)
{
	unsigned char c = 0, i = 0;
	c = chr - ' ';
	if (x > Max_Column - 1)
	{
		x = 0;
		y = y + 2;
	}
	if (SIZE == 16)
	{
		OLED_Set_Pos(x, y);
		for (i = 0; i < 8; i++)
			OLED_WR_Byte(F8X16[c * 16 + i], OLED_DATA);
		OLED_Set_Pos(x, y + 1);
		for (i = 0; i < 8; i++)
			OLED_WR_Byte(F8X16[c * 16 + i + 8], OLED_DATA);
	}
	else
	{
		OLED_Set_Pos(x, y + 1);
		for (i = 0; i < 6; i++)
			OLED_WR_Byte(F6x8[c][i], OLED_DATA);
	}
}

u32 oled_pow(u8 m, u8 n)
{
	u32 result = 1;
	while (n--)
		result *= m;
	return result;
}

void OLED_ShowNum(u8 x, u8 y, u32 num, u8 len, u8 size)
{
	u8 t, temp;
	u8 enshow = 0;
	for (t = 0; t < len; t++)
	{
		temp = (num / oled_pow(10, len - t - 1)) % 10;
		if (enshow == 0 && t < (len - 1))
		{
			if (temp == 0)
			{
				OLED_ShowChar(x + (size / 2) * t, y, ' ');
				continue;
			}
			else
				enshow = 1;
		}
		OLED_ShowChar(x + (size / 2) * t, y, temp + '0');
	}
}

void OLED_ShowString(u8 x, u8 y, u8 *chr)
{
	unsigned char j = 0;
	while (chr[j] != '\0')
	{
		OLED_ShowChar(x, y, chr[j]);
		x += 8;
		if (x > 120)
		{
			x = 0;
			y += 2;
		}
		j++;
	}
}

void OLED_ShowCHinese(u8 x, u8 y, u8 no)
{
	u8 t, adder = 0;
	OLED_Set_Pos(x, y);
	for (t = 0; t < 16; t++)
	{
		OLED_WR_Byte(Hzk[2 * no][t], OLED_DATA);
		adder += 1;
	}
	OLED_Set_Pos(x, y + 1);
	for (t = 0; t < 16; t++)
	{
		OLED_WR_Byte(Hzk[2 * no + 1][t], OLED_DATA);
		adder += 1;
	}
}

void OLED_DrawBMP(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, unsigned char BMP[])
{
	unsigned int j = 0;
	unsigned char x, y;

	if (y1 % 8 == 0)
		y = y1 / 8;
	else
		y = y1 / 8 + 1;
	for (y = y0; y < y1; y++)
	{
		OLED_Set_Pos(x0, y);
		for (x = x0; x < x1; x++)
		{
			OLED_WR_Byte(BMP[j++], OLED_DATA);
		}
	}
}

void OLED_Init(void)
{

	GPIO_InitTypeDef GPIO_InitStruct = {0};
	__HAL_RCC_GPIOB_CLK_ENABLE();
	GPIO_InitStruct.Pin = GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15, GPIO_PIN_SET);

	HAL_Delay(100);

	OLED_WR_Byte(0xAE, OLED_CMD);
	OLED_WR_Byte(0x00, OLED_CMD);
	OLED_WR_Byte(0x10, OLED_CMD);
	OLED_WR_Byte(0x40, OLED_CMD);
	OLED_WR_Byte(0x81, OLED_CMD);
	OLED_WR_Byte(0xCF, OLED_CMD);
	OLED_WR_Byte(0xA1, OLED_CMD);
	OLED_WR_Byte(0xC8, OLED_CMD);
	OLED_WR_Byte(0xA6, OLED_CMD);
	OLED_WR_Byte(0xA8, OLED_CMD);
	OLED_WR_Byte(0x3f, OLED_CMD);
	OLED_WR_Byte(0xD3, OLED_CMD);
	OLED_WR_Byte(0x00, OLED_CMD);
	OLED_WR_Byte(0xd5, OLED_CMD);
	OLED_WR_Byte(0x80, OLED_CMD);
	OLED_WR_Byte(0xD9, OLED_CMD);
	OLED_WR_Byte(0xF1, OLED_CMD);
	OLED_WR_Byte(0xDA, OLED_CMD);
	OLED_WR_Byte(0x12, OLED_CMD);
	OLED_WR_Byte(0xDB, OLED_CMD);
	OLED_WR_Byte(0x40, OLED_CMD);
	OLED_WR_Byte(0x20, OLED_CMD);
	OLED_WR_Byte(0x02, OLED_CMD);
	OLED_WR_Byte(0x8D, OLED_CMD);
	OLED_WR_Byte(0x14, OLED_CMD);
	OLED_WR_Byte(0xA4, OLED_CMD);
	OLED_WR_Byte(0xA6, OLED_CMD);
	OLED_WR_Byte(0xAF, OLED_CMD);

	OLED_WR_Byte(0xAF, OLED_CMD); /*display ON*/
	OLED_Clear();
	OLED_Set_Pos(0, 0);
}
