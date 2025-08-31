#include "dht_manager.h"

DHTData dht_data = {0};
DHT dht_sensor(DHTPIN, DHTTYPE);

void getDataFromDHT(QueueHandle_t xQueueDHT) {
  float h = dht_sensor.readHumidity();
  float t = dht_sensor.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Errore nella lettura dal DHT11!");
    delay(2000);
    return;
  } else Serial.println("Dati letti correttamente dal DHT11");

  dht_data.temp = t;
  dht_data.umid = h;

  if (xQueueSend(xQueueDHT, &dht_data, portMAX_DELAY) != pdPASS) {
        Serial.println("Errore invio dati dht");
    }

}

void DHTask(void *pvParameters) {
    QueueHandle_t xQueue = (QueueHandle_t) pvParameters;
    for (;;) {
        getDataFromDHT(xQueue);
        vTaskDelay(pdMS_TO_TICKS(30000));
    }
}

void DHTManagerInit(QueueHandle_t xQueueDHT) {
    dht_sensor.begin();
    Serial.println("Inizializzazione DHT11 completata...");

    xTaskCreate(DHTask, "DHTask", 2048, (void*)xQueueDHT, 5, NULL);
}
