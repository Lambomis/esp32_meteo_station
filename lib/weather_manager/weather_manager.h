#pragma once

#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "data_types.h"
#include "secrets.h"
#include "images.h"
#include "secrets.h"

typedef struct{
    QueueHandle_t queue_meteo;
    DeviceState* device_state;
} WeatherTaskData;

enum WeatherErrors {
    WEATHER_NO_ERROR = 0,
    WEATHER_HTTP_ERROR = 1,
    WEATHER_JSON_ERROR = 2,
    WEATHER_QUEUE_ERROR = 3,
    WEATHER_WIFI_ERROR = 4,
};

// --- Variabili globali (visibili agli altri moduli) --- //
extern QueueHandle_t xQueueMeteo;
extern DeviceState state;

// --- Funzioni pubbliche --- //
void weatherInit(QueueHandle_t xQueueMeteo, DeviceState &state);   // Inizializza WiFi, queue e avvia il task meteo

