#ifndef __AUDIO_IN__
#define __AUDIO_IN__

#include <stdio.h>
#include "driver/i2s_std.h"
#include"driver/gpio.h"
#include"esp_log.h"
#include"esp_check.h"
#include"freertos/FreeRTOS.h"

// Pin Configuration

#define I2S_SCK_IN  12
#define I2S_SD_IN   15
#define I2S_WS_IN   13

// Audio Configuration

#define I2S_SAMPLE_RATE 44100
#define I2S_BIT_RATE    32
#define I2S_NUM_CH      1   // 1 -> Mono, 2 -> Stereo

// Buffer Size

#define I2S_BUFF_LEN 512

// mclk multiple 

#if I2S_BIT_RATE == 24
    #define MCLK_MULTIPLE I2S_MCLK_MULTIPLE_384
#else
    #define MCLK_MULTIPLE I2S_MCLK_MULTIPLE_256
#endif

// Functions Declaration

void audio_in_init(void);

// For 16 bit

    #if (I2S_BIT_RATE == 16)

        esp_err_t audio_in(int16_t *rx_buffer, size_t *bytes_read);

    #endif

// For 24/32 Bit

    #if ((I2S_BIT_RATE == 24) || (I2S_BIT_RATE == 32))

        esp_err_t audio_in(int32_t *rx_buffer, size_t *bytes_read);

    #endif

#endif