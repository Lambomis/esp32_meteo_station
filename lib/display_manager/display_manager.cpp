#include "display_manager.h"

TFT_eSPI tft = TFT_eSPI();
static lv_disp_t *disp = nullptr;
static uint32_t* draw_buf = nullptr;

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

void displayUpdateDateTime(){
    struct tm timeinfo;
    if (getLocalTime(&timeinfo)) {
        // Aggiorna orario
        char buf[16];
        strftime(buf, sizeof(buf), "%H:%M:%S", &timeinfo);
        lv_label_set_text(objects.label_orario, buf);

        // Aggiorna data di oggi
        char dateStr[32];
        const char* days[]   = {"Domenica","Lunedi","Martedi","Mercoledi","Giovedi","Venerdi","Sabato"};
        const char* months[] = {"Gen","Feb","Mar","Apr","Mag","Giu","Lug","Ago","Set","Ott","Nov","Dic"};
        sprintf(dateStr, "%s, %02d-%s-%d", days[timeinfo.tm_wday], timeinfo.tm_mday,
                months[timeinfo.tm_mon], timeinfo.tm_year + 1900);
        lv_label_set_text(objects.label_data, dateStr);

        // Aggiorna i prossimi 4 giorni
        static lv_obj_t* labels[] = {objects.label_day_left_2, objects.label_day_left_1,
                        objects.label_day_right_1, objects.label_day_right_2};

        time_t now = mktime(&timeinfo); // timestamp di oggi
        for (int i = 0; i < 4; i++) {
            time_t nextDayTime = now + (i+1) * 24 * 60 * 60;
            struct tm nextDay;
            localtime_r(&nextDayTime, &nextDay); // versione thread-safe

            char nextDayStr[16];
            sprintf(nextDayStr, "%02d", nextDay.tm_mday); // solo numero giorno
            lv_label_set_text(labels[i], nextDayStr);
        }
    }
}

void setLabelFloat(lv_obj_t* label, float value, const char* fmt = "%.1f") {
    static char buf[32];
    snprintf(buf, sizeof(buf), fmt, value);
    lv_label_set_text(label, buf);
}


void displayUpdateWeather(QueueHandle_t xQueueMeteo) {
    static WeatherData data;
    if (xQueueReceive(xQueueMeteo, &data, 0) == pdPASS) {
        lv_label_set_text(objects.label_luogo, CITY);
        lv_img_set_src(objects.icon_meteo_today, data.today.weatherIcon.icon);
        lv_label_set_text(objects.labl_meteo_today, data.today.weatherIcon.description);
        setLabelFloat(objects.label_temp_current, data.today.tempC, "%.1f°C");
        setLabelFloat(objects.label_tempt_current_perc, data.today.tempFeelsLike, "%.1f°C");
        setLabelFloat(objects.label_temp_max, data.today.tempMax, "%.1f°C");
        setLabelFloat(objects.label_temp_min, data.today.tempMin, "%.1f°C");
        setLabelFloat(objects.label_umid_current, data.today.humidity, "%.0f%%");
        setLabelFloat(objects.label_vento_value, data.today.windKph, "%.1f km/h");
        setLabelFloat(objects.label_pressione_value, data.today.pressureMb, "%.1f hPa");
        setLabelFloat(objects.label_visibilita_value, data.today.visKm, "%.1f km");

        static lv_obj_t* labels_umid[] = {objects.umidita_day_left_2, objects.umidita_day_left_1,
                                        objects.umidita_day_right_1, objects.umidita_day_right_2};

        static lv_obj_t* labels_temp[] = {objects.temperatura_day_left_2, objects.temperatura_day_left_1,
                                        objects.temperatura_day_right_1, objects.temperatura_day_right_2};

        static lv_obj_t* icons_status[] = {objects.icon_day_left_2, objects.icon_day_left_1,
                                            objects.icon_day_right_1, objects.icon_day_right_2};

        for (int i = 0; i < 4; i++){
            setLabelFloat(labels_umid[i], data.nextDays[i].humidity,"%.0f%%");
            setLabelFloat(labels_temp[i], data.nextDays[i].tempMax, "%.0f°");
            lv_img_set_src(icons_status[i], data.nextDays[i].weatherIcon.icon);
        }
    }
}

static void displayTask(void* pvParameters)
{
    QueueHandle_t queue = (QueueHandle_t) pvParameters;
    while(1){
        lv_timer_handler();
        displayUpdateDateTime();
        displayUpdateWeather(queue);
        vTaskDelay(pdMS_TO_TICKS(50));
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
    draw_buf = (uint32_t*) heap_caps_malloc(DRAW_BUF_SIZE / 4 * sizeof(uint32_t), MALLOC_CAP_DMA);
    if (!draw_buf) {
        Serial.println("Errore allocazione buffer LVGL!");
        return;
    }
    disp = lv_tft_espi_create(TFT_HOR_RES, TFT_VER_RES, draw_buf, DRAW_BUF_SIZE / 4 * sizeof(uint32_t));
    ui_init();

    xTaskCreate(displayTask, "DisplayTask", 20480, (void*)xQueueMeteo, 5, NULL);
}