#pragma once

#include <lvgl.h>
#include <TFT_eSPI.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "data_types.h"
#include "ui.h"
#include "images.h"
#include "secrets.h"

// Risoluzioni schermo
#define TFT_HOR_RES   240
#define TFT_VER_RES   320

// Buffer per LVGL (dichiarazione esterna)
#define DRAW_BUF_SIZE (TFT_HOR_RES * TFT_VER_RES / 10 * (LV_COLOR_DEPTH / 8))

// TFT (dichiarazione esterna)
extern TFT_eSPI tft;

// --- Variabili globali (visibili agli altri moduli) --- // 
extern QueueHandle_t xQueueMeteo;
extern QueueHandle_t xQueueDHT;
typedef struct {
    QueueHandle_t queue_meteo;
    QueueHandle_t queue_dht;
} TaskQueues;


// --- API pubbliche --- //
void displayManagerInit(QueueHandle_t xQueueMeteo, QueueHandle_t xQueueDHT); // Inizializza display e LVGL, avvia il task display