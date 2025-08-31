#pragma once

#include "DHT.h"
#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include "data_types.h"

#define DHTPIN 25
#define DHTTYPE DHT11

extern QueueHandle_t xQueueDHT;

void DHTManagerInit(QueueHandle_t xQueueDHT);