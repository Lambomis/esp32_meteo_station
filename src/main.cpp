#include "data_types.h"
#include "weather_manager.h"
#include "display_manager.h"
#include <freertos/queue.h>

QueueHandle_t xQueueMeteo;

void setup()
{
  Serial.begin(115200);
  xQueueMeteo = xQueueCreate(5, sizeof(WeatherData));
  if (xQueueMeteo == NULL) {
    Serial.println("Errore creazione queue!");
    return;
  }

  weatherInit(xQueueMeteo);
  displayManagerInit(xQueueMeteo);
}

void loop()
{
    vTaskDelay(pdMS_TO_TICKS(1000));
}