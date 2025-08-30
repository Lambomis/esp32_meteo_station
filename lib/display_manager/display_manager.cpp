#include "display_manager.h"

TFT_eSPI tft = TFT_eSPI();
static lv_disp_t *disp = nullptr;
static uint32_t* draw_buf = nullptr;

const void* getWeatherIcon(int code, bool isDay) {
    switch(code) {
        case 0: case 1: return isDay ? &img_icon_sereno : &img_icon_sereno_notte;
        case 2: return isDay ? &img_icon_parzialmente_nuvoloso : &img_icon_parzialmente_nuvoloso_notte;
        case 3: return &img_icon_coperto;
        case 45: case 48: return isDay ? &img_icon_nebbia : &img_icon_nebbia_notte;
        case 51: case 53: case 55: return &img_icon_pioviggine;
        case 56: case 57: return &img_icon_pioggia_congelante;
        case 61: case 63: case 65: return &img_icon_pioggia;
        case 66: case 67: return &img_icon_pioggia_congelante;
        case 71: case 73: case 75: return &img_icon_neve;
        case 77: return &img_icon_granelli_neve;
        case 80: case 81: case 82: case 85: case 86: return &img_icon_pioggia;
        case 95: return &img_icon_temporale;
        case 96: case 99: return &img_icon_temporale_grandine;
        default: return &img_icon_sconosciuto;
    }
}

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
        lv_obj_t* labels[] = {objects.label_day_left_2, objects.label_day_left_1,
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


void displayUpdateWeather(QueueHandle_t xQueueMeteo) {
    static WeatherData data;
    if (xQueueReceive(xQueueMeteo, &data, 0) == pdPASS) {
        lv_label_set_text(objects.label_luogo, CITY);
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