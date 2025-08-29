#include "weather_manager.h"
#include "display_manager.h"
#include "data_types.h"
#include <freertos/queue.h>


void setup()
{
    Serial.begin(115200);
    xQueueMeteo = xQueueCreate(5, sizeof(WeatherData));
    if (xQueueMeteo == NULL) {
      Serial.println("Errore creazione queue!");
      return;
    }

    weatherInit(xQueueMeteo);
    // displayManagerInit(xQueueMeteo);
}

void loop()
{
  WeatherData data;

    // Controllo se ci sono nuovi dati nella queue
    if (xQueueReceive(xQueueMeteo, &data, pdMS_TO_TICKS(1000)) == pdPASS) {
        Serial.println("=== Meteo Oggi ===");
        Serial.printf("Temp: %.1f°C, Feels like: %.1f°C, Max: %.1f°C, Min: %.1f°C\n",
                      data.today.tempC, data.today.tempFeelsLike,
                      data.today.tempMax, data.today.tempMin);
        Serial.printf("Umidità: %.1f%%, Vento: %.1f km/h, Pressione: %.1f mb, Visibilità: %.1f km\n",
                      data.today.humidity, data.today.windKph,
                      data.today.pressureMb, data.today.visKm);
        Serial.printf("Condizione: %s\n", data.today.condition);

        Serial.println("--- Prossimi 4 giorni ---");
        for (int i = 0; i < 4; i++) {
            Serial.printf("Giorno %d: Max %.1f°C, Min %.1f°C, Umidità %.1f%%, Condizione: %s\n",
                          i+1, data.nextDays[i].tempMax,
                          data.nextDays[i].tempMin,
                          data.nextDays[i].humidity,
                          data.nextDays[i].condition);
        }
    }
    vTaskDelay(pdMS_TO_TICKS(1000));
}