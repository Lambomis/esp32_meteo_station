#pragma once

#include "DHT.h"
#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include "data_types.h"

#define DHTPIN 25
#define DHTTYPE DHT11

extern QueueHandle_t xQueueDHT;
extern DeviceState state;

typedef struct {
    QueueHandle_t queue_dht;
    DeviceState* state;
} DHTTaskData;

enum DHTErrors {
    DHT_NO_ERROR = 0,
    DHT_QUEUE_ERROR = 1,
    DHT_ERROR = 2,
};

void DHTManagerInit(QueueHandle_t xQueueDHT, DeviceState &state);