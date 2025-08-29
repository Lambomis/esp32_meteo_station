#include <main.h>


void setup()
{
    lv_init();
    lv_tick_set_cb(my_tick);
    tft.begin();
    tft.setRotation(1);

    disp = lv_tft_espi_create(TFT_HOR_RES, TFT_VER_RES, draw_buf, sizeof(draw_buf));

    // esempio: label
    lv_obj_t *label = lv_label_create(lv_screen_active());
    lv_label_set_text(label, "Hello ESP32 + LVGL 9.3!");
    lv_obj_center(label);
}

void loop()
{
    lv_timer_handler(); /* let the GUI do its work */
    delay(5); /* let this time pass */
}