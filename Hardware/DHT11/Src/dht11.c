#include "dht11.h"

// uint8_t flag = 0;
uint8_t dht11_rec_data[5] = {0};

uint8_t DHT11_Decimal = 0;
uint8_t DHT11_Integral = 0;

void DHT11_Start(void)
{
    // flag = 0;
    HAL_GPIO_WritePin(DHT11_GPIO_Port, DHT11_GPIO_Pin, GPIO_PIN_RESET);
    HAL_Delay(20);
    HAL_GPIO_WritePin(DHT11_GPIO_Port, DHT11_GPIO_Pin, GPIO_PIN_SET);
    Delay_Us(60);
    if (HAL_GPIO_ReadPin(DHT11_GPIO_Port, DHT11_GPIO_Pin) == RESET)
    {
        // flag = 1;
        while (HAL_GPIO_ReadPin(DHT11_GPIO_Port, DHT11_GPIO_Pin) == RESET)
            ;
        while (HAL_GPIO_ReadPin(DHT11_GPIO_Port, DHT11_GPIO_Pin) == SET)
            ;
    }
}

uint8_t DHT11_Read(void)
{
    uint8_t data = 0;
    for (uint8_t i = 0; i < 8; i++)
    {
        data <<= 1;
        while (HAL_GPIO_ReadPin(DHT11_GPIO_Port, DHT11_GPIO_Pin) == RESET)
            ;
        Delay_Us(40);
        if (HAL_GPIO_ReadPin(DHT11_GPIO_Port, DHT11_GPIO_Pin) == SET)
        {
            data |= 0x01;
        }
    }
    return data;
}

void DHT11_GetHumidity(void)
{

    DHT11_Start();

    for (uint8_t i = 0; i < 5; i++)
        dht11_rec_data[i] = DHT11_Read();

    //    if (DHT11_Crc()){
    DHT11_Integral = dht11_rec_data[0];
    DHT11_Decimal = dht11_rec_data[1];
    //    }
}

uint8_t DHT11_Crc(void)
{
    uint32_t sum = 0;
    for (uint8_t i = 0; i < 4; i++)
        sum += dht11_rec_data[i];

    return sum == dht11_rec_data[4];
}
