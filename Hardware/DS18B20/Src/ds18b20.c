#include "ds18b20.h"

uint8_t flag = 0;
uint8_t rec_data[9];

uint8_t Ds18b20_Temp_m = 0;
uint8_t Ds18b20_Temp_l = 0;
const unsigned char CrcTable[256] = {
    0, 94, 188, 226, 97, 63, 221, 131, 194, 156, 126, 32, 163, 253, 31, 65,
    157, 195, 33, 127, 252, 162, 64, 30, 95, 1, 227, 189, 62, 96, 130, 220,
    35, 125, 159, 193, 66, 28, 254, 160, 225, 191, 93, 3, 128, 222, 60, 98,
    190, 224, 2, 92, 223, 129, 99, 61, 124, 34, 192, 158, 29, 67, 161, 255,
    70, 24, 250, 164, 39, 121, 155, 197, 132, 218, 56, 102, 229, 187, 89, 7,
    219, 133, 103, 57, 186, 228, 6, 88, 25, 71, 165, 251, 120, 38, 196, 154,
    101, 59, 217, 135, 4, 90, 184, 230, 167, 249, 27, 69, 198, 152, 122, 36,
    248, 166, 68, 26, 153, 199, 37, 123, 58, 100, 134, 216, 91, 5, 231, 185,
    140, 210, 48, 110, 237, 179, 81, 15, 78, 16, 242, 172, 47, 113, 147, 205,
    17, 79, 173, 243, 112, 46, 204, 146, 211, 141, 111, 49, 178, 236, 14, 80,
    175, 241, 19, 77, 206, 144, 114, 44, 109, 51, 209, 143, 12, 82, 176, 238,
    50, 108, 142, 208, 83, 13, 239, 177, 240, 174, 76, 18, 145, 207, 45, 115,
    202, 148, 118, 40, 171, 245, 23, 73, 8, 86, 180, 234, 105, 55, 213, 139,
    87, 9, 235, 181, 54, 104, 138, 212, 149, 203, 41, 119, 244, 170, 72, 22,
    233, 183, 85, 11, 136, 214, 52, 106, 43, 117, 151, 201, 74, 20, 246, 168,
    116, 42, 200, 150, 21, 75, 169, 247, 182, 232, 10, 84, 215, 137, 107, 53};

void Ds18b20_Init(void)
{
    Ds18b20_Configure();
}

void Ds18b20_Rest(void)
{
    HAL_GPIO_WritePin(DS18B20_DAT_GPIO_Port, DS18B20_DAT_Pin, GPIO_PIN_SET);
    Delay_Us(2);

    HAL_GPIO_WritePin(DS18B20_DAT_GPIO_Port, DS18B20_DAT_Pin, GPIO_PIN_RESET);
    Delay_Us(500);

    HAL_GPIO_WritePin(DS18B20_DAT_GPIO_Port, DS18B20_DAT_Pin, GPIO_PIN_SET);

    if (HAL_GPIO_ReadPin(DS18B20_DAT_GPIO_Port, DS18B20_DAT_Pin) == GPIO_PIN_RESET)
        flag = 1;
    else
        flag = 0;
}

void Ds18b20_WriteByte(uint8_t data)
{
    for (uint8_t i = 0; i < 8; i++)
    {
        HAL_GPIO_WritePin(DS18B20_DAT_GPIO_Port, DS18B20_DAT_Pin, GPIO_PIN_RESET);
        if ((data >> i) & 0x01)
            Delay_Us(2);
        else
            Delay_Us(30);
        HAL_GPIO_WritePin(DS18B20_DAT_GPIO_Port, DS18B20_DAT_Pin, GPIO_PIN_SET);
        Delay_Us(60);
    }
}

uint8_t Ds18b20_ReadByte(void)
{
    uint8_t data = 0;
    for (uint8_t i = 0; i < 8; i++)
    {
        data >>= 1;
        HAL_GPIO_WritePin(DS18B20_DAT_GPIO_Port, DS18B20_DAT_Pin, GPIO_PIN_RESET);
        Delay_Us(2);
        HAL_GPIO_WritePin(DS18B20_DAT_GPIO_Port, DS18B20_DAT_Pin, GPIO_PIN_SET);
        Delay_Us(10);
        if (HAL_GPIO_ReadPin(DS18B20_DAT_GPIO_Port, DS18B20_DAT_Pin) == GPIO_PIN_SET)
            data |= 0x80;
        Delay_Us(60);
    }
    return data;
}

void Ds18b20_ReadBytes(uint8_t size)
{
    unsigned char i;
    for (i = 0; i < size; i++)
    {
        rec_data[i] = Ds18b20_ReadByte();
    }
}

uint8_t Ds18b20_Crc(uint8_t size)
{
    unsigned char i, crc_data = 0;
    for (i = 0; i < size; i++)
        crc_data = CrcTable[crc_data ^ rec_data[i]];
    return (crc_data);
}

void Ds18b20_GetTemperture(void)
{

    Ds18b20_Configure();

    Ds18b20_Rest();
    HAL_Delay(20);
    Ds18b20_WriteByte(0xCC); // skip rom
    Ds18b20_WriteByte(0x44); // Temperature convert
    // while (HAL_GPIO_ReadPin(DS18B20_DAT_GPIO_Port, DS18B20_DAT_Pin) == GPIO_PIN_RESET);

    HAL_Delay(20);

    Ds18b20_Rest();
    HAL_Delay(20);
    Ds18b20_WriteByte(0xCC); // skip rom
    Ds18b20_WriteByte(0xBE); // read Temperature

    Ds18b20_ReadBytes(9);
    Ds18b20_Rest();
    if (Ds18b20_Crc(9) == 0) // 校验正确
    {
        Ds18b20_Temp_m = (uint8_t)(((uint16_t)(rec_data[1] << 8) | rec_data[0]) >> 4);
        Ds18b20_Temp_l = (uint8_t)(rec_data[0] & 0x0F) * 6;
    }
    Ds18b20_Rest();
    // HAL_Delay(1000);
}

void Ds18b20_Configure(void) // 重新配置报警限定值和分辨率
{
    Ds18b20_Rest();
    Ds18b20_WriteByte(0xcc); // skip rom
    Ds18b20_WriteByte(0x4e); // write scratchpad
    Ds18b20_WriteByte(0x19); // 上限
    Ds18b20_WriteByte(0x1a); // 下限
    Ds18b20_WriteByte(0x7f); // set 12 bit (0.125)
    Ds18b20_Rest();
    Ds18b20_WriteByte(0xcc); // skip rom
    Ds18b20_WriteByte(0x48); // 保存设定值
    Ds18b20_Rest();
    Ds18b20_WriteByte(0xcc); // skip rom
    Ds18b20_WriteByte(0xb8); // 回调设定值
}
