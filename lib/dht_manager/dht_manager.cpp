#include "dht_manager.h"

DHTData dht_data = {0};
DHT dht_sensor(DHTPIN, DHTTYPE);

void getDataFromDHT(QueueHandle_t xQueueDHT, DeviceState &state) {
  float h = dht_sensor.readHumidity();
  float t = dht_sensor.readTemperature();

  if (isnan(h) || isnan(t)) {
    state.state_dht11.errorCode = DHT_ERROR;
    state.state_dht11.description = "DHT Read Error.";
    Serial.println("Errore nella lettura dal DHT11!");
    delay(2000);
    return;
  }

  dht_data.temp = t;
  dht_data.umid = h;

  if (xQueueSend(xQueueDHT, &dht_data, portMAX_DELAY) != pdPASS) {
        state.state_dht11.errorCode = DHT_QUEUE_ERROR;
        state.state_dht11.description = "Queue Send Error.";
        Serial.println("Errore invio dati dht");
  }
  
  state.state_dht11.errorCode = DHT_NO_ERROR;
  state.state_dht11.description = "OK";

}

void DHTask(void *pvParameters) {
    DHTTaskData* task_data = (DHTTaskData*) pvParameters;
    for (;;) {
        getDataFromDHT(task_data->queue_dht, *(task_data->state));
        vTaskDelay(pdMS_TO_TICKS(3000));
    }
}

void DHTManagerInit(QueueHandle_t xQueueDHT, DeviceState &state) {
    dht_sensor.begin();
    Serial.println("Inizializzazione DHT11 completata...");
    DHTTaskData* task_data = new DHTTaskData;
    task_data->queue_dht = xQueueDHT;
    task_data->state = &state;

    xTaskCreate(DHTask, "DHTask", 2048, task_data, 5, NULL);
}
