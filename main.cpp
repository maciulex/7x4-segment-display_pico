//#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/multicore.h"

#include "segment_display.cpp"

uint16_t counter = 0;

int main() {
    stdio_init_all();
    printf("ddad");
    sleep_ms(1000);
    printf("ddad");
    SEGMENT_DISPLAY::init();
    multicore_launch_core1(SEGMENT_DISPLAY::display_loop);
    while(1){
        SEGMENT_DISPLAY::put_digits(counter);
        counter++;
        if (!SEGMENT_DISPLAY::DOTS_STATUS[0]) {
            SEGMENT_DISPLAY::DOTS_STATUS[0] = 1;
            SEGMENT_DISPLAY::DOTS_STATUS[1] = 1;
            SEGMENT_DISPLAY::DOTS_STATUS[2] = 1;
            SEGMENT_DISPLAY::DOTS_STATUS[3] = 1;
        } else {
            SEGMENT_DISPLAY::DOTS_STATUS[0] = 0;
            SEGMENT_DISPLAY::DOTS_STATUS[1] = 0;
            SEGMENT_DISPLAY::DOTS_STATUS[2] = 0;
            SEGMENT_DISPLAY::DOTS_STATUS[3] = 0;
        }
        sleep_ms(60);
    }
    return 0;
}