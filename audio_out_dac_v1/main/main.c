#include <stdio.h>
#include "audio_in/audio_in.h"
#include"audio_out_dac/audio_out_dac.h"

void app_main(void)
{
    audio_in_init();
    audio_out_dac_init();

    int32_t audio_data_buffer[I2S_BUFF_LEN / 2];
    size_t bytes_read;

    while(1)
    {
        audio_in(audio_data_buffer, &bytes_read);
        audio_out_dac(audio_data_buffer, &bytes_read);
    }
}
