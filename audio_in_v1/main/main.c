#include <stdio.h>
#include "audio_in/audio_in.h"

void app_main(void)
{
    int32_t audio_in_buffer[I2S_BUFF_LEN / 4];
    size_t bytes_read;
    float mean = 0;

    audio_in_init();

    while(1)
    {
        audio_in(audio_in_buffer, &bytes_read);

        for(int i=0; i < bytes_read/4; i = i+4)
        {
            mean += audio_in_buffer[i];
        }

        mean /= (bytes_read/2);

        printf("%f\n", mean);
    }
}
