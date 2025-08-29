#include <lvgl.h>
#include <TFT_eSPI.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#define TFT_HOR_RES   240
#define TFT_VER_RES   320

extern TFT_eSPI tft;

#define DRAW_BUF_SIZE (TFT_HOR_RES * TFT_VER_RES / 10 * (LV_COLOR_DEPTH / 8))
extern uint32_t draw_buf[DRAW_BUF_SIZE / 4];

static lv_disp_t *disp;