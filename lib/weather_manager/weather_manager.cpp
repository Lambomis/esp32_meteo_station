#include "weather_manager.h"

WeatherData getWeatherData_openmeteo() {
    WeatherData data = {0};
    HTTPClient http;
    String url = "https://api.open-meteo.com/v1/forecast?latitude="+ String(LATITUDE) +
                "&longitude=" + String(LONGITUDE) +
                "&hourly=relativehumidity_2m" +
                "&daily=temperature_2m_max,temperature_2m_min,apparent_temperature_max,apparent_temperature_min,weathercode" +
                "&current_weather=true&timezone=Europe/Rome";

    http.begin(url);
    int httpCode = http.GET();
    if (httpCode == HTTP_CODE_OK) {

        String payload = http.getString();

        DynamicJsonDocument doc(16*1024);
        deserializeJson(doc, payload);

        // --- Dati di oggi ---

        data.today.tempC = doc["current_weather"]["temperature"];
        data.today.tempFeelsLike = doc["daily"]["apparent_temperature_max"][0];
        data.today.tempMax = doc["daily"]["temperature_2m_max"][0];
        data.today.tempMin = doc["daily"]["temperature_2m_min"][0];
        data.today.windKph = doc["current_weather"]["windspeed"];
        data.today.weathercode = doc["daily"]["weathercode"][0];
        
        float sumHumidity = 0;
        for (int i = 0; i < 24; i++) sumHumidity += doc["hourly"]["relativehumidity_2m"][i].as<float>();
        data.today.humidity = sumHumidity / 24;

        // --- Dati successivi 4 giorni ---
        for (int i = 1; i <= 4; i++) {
            data.nextDays[i-1].tempMax    = doc["daily"]["temperature_2m_max"][i].as<float>();
            data.nextDays[i-1].weathercode= doc["daily"]["weathercode"][i].as<int>();

            // umidità media giorno i dalle 24 ore corrispondenti
            int startHour = i * 24;
            float sum = 0;
            for (int h = 0; h < 24; h++) {
                sum += doc["hourly"]["relativehumidity_2m"][startHour + h].as<float>();
            }
            data.nextDays[i-1].humidity = sum / 24.0f;
        }

    } else {
        Serial.printf("Errore HTTP: %d\n", httpCode);
    }
    http.end();
    return data;
}

WeatherData getWeatherData_openweather(WeatherData &data) {
    HTTPClient http;
    String url = "https://api.openweathermap.org/data/2.5/weather?lat="+ String(LATITUDE) +
                "&lon=" + String(LONGITUDE) +
                "&appid=" + OPEN_WEATHER_API_KEY +
                "&units=metric&lang=it";

    http.begin(url);
    int httpCode = http.GET();
    if (httpCode == HTTP_CODE_OK) {

        String payload = http.getString();

        DynamicJsonDocument doc(8*1024);
        deserializeJson(doc, payload);

        // --- Dati di oggi ---
        data.today.windKph    = doc["wind"]["speed"];
        data.today.visKm      = doc["visibility"].as<float>() / 1000.0f;
    } else {
        Serial.printf("Errore HTTP: %d\n", httpCode);
    }
    http.end();
    return data;
}

void getWeatherData() {
    if (WiFi.status() != WL_CONNECTED) return;
    WeatherData data = {0};
    data = getWeatherData_openmeteo();
    data = getWeatherData_openweather(data);
    
    if (xQueueSend(xQueueMeteo, &data, portMAX_DELAY) != pdPASS) {
        Serial.println("Errore invio dati meteo");
    }
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

