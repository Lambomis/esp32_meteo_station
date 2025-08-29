#pragma once

#include <lvgl.h>
#include <TFT_eSPI.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "data_types.h"

// Risoluzioni schermo
#define TFT_HOR_RES   240
#define TFT_VER_RES   320

// Buffer per LVGL (dichiarazione esterna)
#define DRAW_BUF_SIZE (TFT_HOR_RES * TFT_VER_RES / 10 * (LV_COLOR_DEPTH / 8))
extern uint32_t draw_buf[DRAW_BUF_SIZE / 4];

// TFT (dichiarazione esterna)
extern TFT_eSPI tft;

// --- Variabili globali (visibili agli altri moduli) --- // 
extern QueueHandle_t xQueueMeteo;

// --- API pubbliche --- //
void displayManagerInit(QueueHandle_t xQueueMeteo); // Inizializza display e LVGL, avvia il task display