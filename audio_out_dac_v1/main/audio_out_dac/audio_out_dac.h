#ifndef __AUDIO_OUT_DAC__
#define __AUDIO_OUT_DAC__

#include"audio_in.h"

#include"driver/i2s_std.h"
#include"driver/gpio.h"
#include"esp_log.h"
#include"esp_check.h"

#include"freertos/FreeRTOS.h"

// Pin Configuration

#define I2S_SCK_OUT 14
#define I2S_SD_OUT  22
#define I2S_WS_OUT  5

// Uncomment below only if audio_in.h is not included

// // Audio COnfig

// #define I2S_SAMPLE_RATE 44100
// #define I2S_BIT_RATE    16
// #define I2S_NUM_CH      1   // 1 -> Mono, 2 -> Stereo

// // Buffer Size

// #define I2S_BUFF_LEN 512

// // mclk multiple 

// #if I2S_BIT_RATE == 24
//     #define MCLK_MULTIPLE I2S_MCLK_MULTIPLE_384
// #else
//     #define MCLK_MULTIPLE I2S_MCLK_MULTIPLE_256
// #endif


void audio_out_dac_init(void);

    #if (I2S_BIT_RATE == 16)

        esp_err_t audio_out_dac(int16_t *tx_buffer, size_t *bytes_wrote);

    #elif ((I2S_BIT_RATE == 24) || (I2S_BIT_RATE == 32))

        esp_err_t audio_out_dac(int32_t *tx_buffer, size_t *bytes_wrote);
    #endif


#endif