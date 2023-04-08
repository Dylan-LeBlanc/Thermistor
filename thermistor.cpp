/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"
#include <math.h>

int main() {
    stdio_init_all();
    printf("ADC Example, measuring GPIO26\n");

    adc_init();

    // Make sure GPIO is high-impedance, no pullups etc
    adc_gpio_init(26);
    // Select ADC input 0 (GPIO26)
    adc_select_input(0);

    /*while (1) {
        // 12-bit conversion, assume max value == ADC_VREF == 3.3 V
        const float conversion_factor = 3.3f / (1 << 12);
        uint16_t result = adc_read();
        printf("Raw value: 0x%03x, voltage: %f V\n", result, result * conversion_factor);
        sleep_ms(500);   
    }
    */
   while (1) {
   const float conversion_factor = 3.3f / (1 << 12);
   uint16_t result = adc_read();
   float vout = result * conversion_factor;
   int Ro = 10000;
   float Rt = (vout * Ro) / (3.3f - vout);
   double A = 0.001129148; 
   double B = 0.000234125;
   double C = 0.0000000876741;
   float TempK = 1 / (A + (B * log(Rt)) + C * pow(log(Rt), 3));
   float TempC = TempK -273.15;
   float TempF = (TempC * (1.8f)) + 32.0f;
   printf("Temperature %f F, Celsius: %f C\n",TempF, TempC);
   sleep_ms(1000);
   }

}
