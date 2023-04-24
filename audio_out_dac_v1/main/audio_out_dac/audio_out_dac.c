#include"audio_out_dac.h"

i2s_chan_handle_t tx_handle;

void audio_out_dac_init(void)
{
    i2s_chan_config_t tx_chan_cfg = I2S_CHANNEL_DEFAULT_CONFIG(I2S_NUM_1, I2S_ROLE_MASTER);
    ESP_ERROR_CHECK(i2s_new_channel(&tx_chan_cfg, &tx_handle, NULL));

    i2s_std_config_t tx_std_cfg= {
        .clk_cfg = {
            .sample_rate_hz = I2S_SAMPLE_RATE,
            .clk_src = I2S_CLK_SRC_DEFAULT, \
            .mclk_multiple = MCLK_MULTIPLE,
        },
        .slot_cfg = I2S_STD_MSB_SLOT_DEFAULT_CONFIG(I2S_BIT_RATE, I2S_NUM_CH),
        .gpio_cfg = {
            .mclk = I2S_GPIO_UNUSED,
            .bclk = I2S_SCK_OUT,
            .ws = I2S_WS_OUT,
            .dout = I2S_SD_OUT,
            .din = I2S_GPIO_UNUSED,
            .invert_flags = {
                .mclk_inv = false,
                .bclk_inv = false,
                .ws_inv = false,
            },
        },
    };

    ESP_ERROR_CHECK(i2s_channel_init_std_mode(tx_handle, &tx_std_cfg));
    ESP_ERROR_CHECK(i2s_channel_enable(tx_handle));
}



#if (I2S_BIT_RATE == 16)

esp_err_t audio_out_dac(int16_t *tx_buffer, size_t *bytes_wrote)
{
    return i2s_channel_write(tx_handle, (void *) tx_buffer, I2S_BUFF_LEN, bytes_wrote, portMAX_DELAY);
}

#elif ((I2S_BIT_RATE == 24) || (I2S_BIT_RATE == 32))

esp_err_t audio_out_dac(int32_t *tx_buffer, size_t *bytes_wrote)
{
    return i2s_channel_write(tx_handle, (void *) tx_buffer, I2S_BUFF_LEN, bytes_wrote, portMAX_DELAY);
}

#endif