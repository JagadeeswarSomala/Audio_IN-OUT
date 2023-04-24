#include "audio_in.h"

static i2s_chan_handle_t rx_handle;

void audio_in_init(void)
{
    i2s_chan_config_t rx_chan_cfg = I2S_CHANNEL_DEFAULT_CONFIG(I2S_NUM_AUTO, I2S_ROLE_MASTER);
    ESP_ERROR_CHECK(i2s_new_channel(&rx_chan_cfg, NULL, &rx_handle));

    i2s_std_config_t rx_std_cfg= {
        .clk_cfg = {
            .sample_rate_hz = I2S_SAMPLE_RATE,
            .clk_src = I2S_CLK_SRC_DEFAULT, \
            .mclk_multiple = MCLK_MULTIPLE,
        },
        .slot_cfg = I2S_STD_MSB_SLOT_DEFAULT_CONFIG(I2S_BIT_RATE, I2S_NUM_CH),
        .gpio_cfg = {
            .mclk = I2S_GPIO_UNUSED,
            .bclk = I2S_SCK_IN,
            .ws   = I2S_WS_IN,
            .dout = I2S_GPIO_UNUSED,
            .din  = I2S_SD_IN,
            .invert_flags = {
                .mclk_inv = false,
                .bclk_inv = false,
                .ws_inv = false,
            },
        },
    };

    ESP_ERROR_CHECK(i2s_channel_init_std_mode(rx_handle, &rx_std_cfg));
    ESP_ERROR_CHECK(i2s_channel_enable(rx_handle));
}


#if (I2S_BIT_RATE == 16)

esp_err_t audio_in(int16_t *rx_buffer, size_t *bytes_read)
{
    return i2s_channel_read(rx_handle, (void *) rx_buffer, I2S_BUFF_LEN, bytes_read, portMAX_DELAY);
}

#elif ((I2S_BIT_RATE == 24) || (I2S_BIT_RATE == 32))

esp_err_t audio_in(int32_t *rx_buffer, size_t *bytes_read)
{
        return i2s_channel_read(rx_handle, (void *) rx_buffer, I2S_BUFF_LEN, bytes_read, portMAX_DELAY);
}

#endif