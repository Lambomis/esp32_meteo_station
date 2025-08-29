#include "display_manager.h"

TFT_eSPI tft = TFT_eSPI();

static void my_disp_flush(lv_display_t *display, const lv_area_t *area, uint8_t *color_p)
{
    uint32_t w = lv_area_get_width(area);
    uint32_t h = lv_area_get_height(area);

    tft.startWrite();
    tft.setAddrWindow(area->x1, area->y1, w, h);
    tft.pushColors((uint16_t *)&color_p[0], w * h, true);
    tft.endWrite();

    lv_disp_flush_ready(display);
}

static void displayTask(void* pvParameters)
{
    while(1){
        lv_timer_handler();
        vTaskDelay(pdMS_TO_TICKS(5));
    }
}

static uint32_t my_tick(void)
{
    return millis();
}

void displayManagerInit(){
    lv_init();
    lv_tick_set_cb(my_tick);
    tft.begin();
    tft.setRotation(1);
    disp = lv_tft_espi_create(TFT_HOR_RES, TFT_VER_RES, draw_buf, sizeof(draw_buf));

    xTaskCreate(displayTask, "DisplayTask", 4096, NULL, 5, NULL);
}

void displayUpdateWeather(float tempC, const char* condition) {
    if(labelTemp) {
        lv_label_set_text_fmt(labelTemp, "Temp: %.1f C", tempC);
    }
    if(labelCondition) {
        lv_label_set_text(labelCondition, condition);
    }
}