#include "weather_manager.h"

void weatherInit(QueueHandle_t xQueueMeteo) {
    WiFi.begin("YOUR_SSID", "YOUR_PASSWORD");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("Wi-Fi connesso");

    xTaskCreate(weatherTask, "WeatherTask", 8192, NULL, 5, NULL);
}

void getWeatherData() {
    if (WiFi.status() != WL_CONNECTED) return;

    HTTPClient http;
    String url = "http://api.weatherapi.com/v1/forecast.json?key=YOUR_API_KEY&q=Rome&days=5&aqi=no&alerts=no";
    http.begin(url);
    int httpCode = http.GET();
    if (httpCode == HTTP_CODE_OK) {
        String payload = http.getString();

        DynamicJsonDocument doc(8192);
        deserializeJson(doc, payload);

        WeatherData data;

        // --- Dati di oggi ---
        JsonObject current = doc["current"];
        JsonObject todayForecast = doc["forecast"]["forecastday"][0]["day"];

        data.today.tempC = current["temp_c"];
        data.today.tempFeelsLike = current["feelslike_c"];
        data.today.tempMax = todayForecast["maxtemp_c"];
        data.today.tempMin = todayForecast["mintemp_c"];
        data.today.humidity = current["humidity"];
        data.today.windKph = current["wind_kph"];
        data.today.pressureMb = current["pressure_mb"];
        data.today.visKm = current["vis_km"];
        strcpy(data.today.condition, current["condition"]["text"]);

        // --- Dati successivi 4 giorni ---
        for (int i = 1; i <= 4; i++) {
            JsonObject f = doc["forecast"]["forecastday"][i]["day"];
            data.nextDays[i-1].tempMax = f["maxtemp_c"];
            data.nextDays[i-1].tempMin = f["mintemp_c"];
            data.nextDays[i-1].humidity = f["avghumidity"];
            strcpy(data.nextDays[i-1].condition, f["condition"]["text"]);
        }

        // Invia alla queue
        if (xQueueSend(xQueueMeteo, &data, portMAX_DELAY) != pdPASS) {
            Serial.println("Errore invio dati meteo");
        }

    } else {
        Serial.printf("Errore HTTP: %d\n", httpCode);
    }

    http.end();
}

void weatherTask(void *pvParameters) {
    for (;;) {
        getWeatherData();
        vTaskDelay(pdMS_TO_TICKS(600000)); // aggiorna ogni 10 minuti
    }
}

