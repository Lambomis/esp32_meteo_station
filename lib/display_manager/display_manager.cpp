#include "display_manager.h"

TFT_eSPI tft = TFT_eSPI();
uint32_t draw_buf[DRAW_BUF_SIZE / 4];
static lv_disp_t *disp;

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

void displayUpdateWeather(QueueHandle_t xQueueMeteo) {
    WeatherData data;
    if (xQueueReceive(xQueueMeteo, &data, 0) == pdPASS) {
        return;
        // Aggiorna la visualizzazione con i nuovi dati meteo
        // Esempio: crea una label e mostra la temperatura attuale
        //TODO aggiornare interfaccia
        // lv_label_set_text_fmt(label, "Temp: %.1f C\nFeels like: %.1f C\nHumidity: %.1f%%\nCondition: %s",
        //                       data.today.tempC, data.today.tempFeelsLike, data.today.humidity, data.today.condition);
    }
}

static void displayTask(void* pvParameters)
{
    QueueHandle_t queue = (QueueHandle_t) pvParameters;
    while(1){
        lv_timer_handler();
        displayUpdateWeather(queue);
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

static uint32_t my_tick(void)
{
    return millis();
}

void displayManagerInit(QueueHandle_t xQueueMeteo){
    lv_init();
    lv_tick_set_cb(my_tick);
    tft.begin();
    tft.setRotation(1);
    disp = lv_tft_espi_create(TFT_HOR_RES, TFT_VER_RES, draw_buf, sizeof(draw_buf));

    xTaskCreate(displayTask, "DisplayTask", 4096, (void*)xQueueMeteo, 5, NULL);
}