#pragma once

#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "data_types.h"
#include "secrets.h"

// --- Variabili globali (visibili agli altri moduli) --- //
extern QueueHandle_t xQueueMeteo;

// --- Funzioni pubbliche --- //
void weatherInit(QueueHandle_t xQueueMeteo);   // Inizializza WiFi, queue e avvia il task meteo

