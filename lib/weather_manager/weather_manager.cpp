#include "weather_manager.h"

String url = "https://api.open-meteo.com/v1/forecast?";

void getWeatherData() {
    if (WiFi.status() != WL_CONNECTED) return;

    HTTPClient http;
    url = url + "latitude="+ String(LATITUDE) +
                "&longitude=" + String(LONGITUDE) +
                "&hourly=relativehumidity_2m" +
                "&daily=temperature_2m_max,temperature_2m_min,apparent_temperature_max,apparent_temperature_min,weathercode" +
                "&current_weather=true&timezone=Europe/Rome";
    Serial.println(url);
    http.begin(url);
    int httpCode = http.GET();
    if (httpCode == HTTP_CODE_OK) {

        String payload = http.getString();
        Serial.println(payload);

        DynamicJsonDocument doc(16*1024);
        deserializeJson(doc, payload);

        WeatherData data = {0};

        // --- Dati di oggi ---

        data.today.tempC = doc["current_weather"]["temperature"];
        data.today.tempFeelsLike = doc["daily"]["apparent_temperature_max"][0];
        data.today.tempMax = doc["daily"]["temperature_2m_max"][0];
        data.today.tempMin = doc["daily"]["temperature_2m_min"][0];
        data.today.windKph = doc["current_weather"]["windspeed"];
        data.today.pressureMb = 0.000;
        data.today.visKm = 0.000;
        data.today.weathercode = doc["daily"]["weathercode"][0];
        
        JsonArray hourlyHumidity = doc["hourly"]["relativehumidity_2m"];
        float sumHumidity = 0;
        for (int i = 0; i < 24; i++) sumHumidity += hourlyHumidity[i].as<float>();
        data.today.humidity = sumHumidity / 24;

        // --- Dati successivi 4 giorni ---
        for (int i = 1; i <= 4; i++) {
            data.nextDays[i-1].tempMax = doc["daily"]["temperature_2m_max"][i];
            data.nextDays[i-1].weathercode = doc["daily"]["weathercode"][i];

            // umidità media giorno i dalle 24 ore corrispondenti
            int startHour = i * 24;
            float sum = 0;
            for (int h = 0; h < 24; h++) sum += hourlyHumidity[startHour + h].as<float>();
            data.nextDays[i-1].humidity = sum / 24;
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

void weatherInit(QueueHandle_t xQueueMeteo) {
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("Wi-Fi connesso");

    xTaskCreate(weatherTask, "WeatherTask", 8192, NULL, 5, NULL);
}

