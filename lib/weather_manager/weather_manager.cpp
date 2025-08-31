#include "weather_manager.h"

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 3600;
const int   daylightOffset_sec = 3600;

WeatherIcon getWeatherIcon(int code, bool isDay) {
    switch(code) {
        case 0: case 1: 
            return (WeatherIcon){ isDay ? &img_icon_sereno : &img_icon_sereno_notte,
                                  isDay ? "Soleggiato" : "Sereno notte" };
        case 2: 
            return (WeatherIcon){ isDay ? &img_icon_parzialmente_nuvoloso : &img_icon_parzialmente_nuvoloso_notte,
                                  "Parzialmente nuvoloso" };
        case 3: 
            return (WeatherIcon){ &img_icon_coperto, "Coperto" };
        case 45: case 48: 
            return (WeatherIcon){ isDay ? &img_icon_nebbia : &img_icon_nebbia_notte,
                                  "Nebbia" };
        case 51: case 53: case 55: 
            return (WeatherIcon){ &img_icon_pioviggine, "Pioviggine" };
        case 56: case 57: 
            return (WeatherIcon){ &img_icon_pioggia_congelante, "Pioggia congelante" };
        case 61: case 63: case 65: 
            return (WeatherIcon){ &img_icon_pioggia, "Pioggia" };
        case 66: case 67: 
            return (WeatherIcon){ &img_icon_pioggia_congelante, "Pioggia congelante" };
        case 71: case 73: case 75: 
            return (WeatherIcon){ &img_icon_neve, "Neve" };
        case 77: 
            return (WeatherIcon){ &img_icon_granelli_neve, "Neve a grani" };
        case 80: case 81: case 82: case 85: case 86: 
            return (WeatherIcon){ &img_icon_pioggia, "Rovesci" };
        case 95: 
            return (WeatherIcon){ &img_icon_temporale, "Temporale" };
        case 96: case 99: 
            return (WeatherIcon){ &img_icon_temporale_grandine, "Temporale con grandine" };
        default: 
            return (WeatherIcon){ &img_icon_sconosciuto, "Sconosciuto" };
    }
}

bool isDaytime() {
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) return true;
    int hour = timeinfo.tm_hour;
    return hour >= 6 && hour < 18;
}

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
        data.today.weatherIcon = getWeatherIcon(doc["current_weather"]["weathercode"], isDaytime());

        
        float sumHumidity = 0;
        for (int i = 0; i < 24; i++) sumHumidity += doc["hourly"]["relativehumidity_2m"][i].as<float>();
        data.today.humidity = sumHumidity / 24;

        // --- Dati successivi 4 giorni ---
        for (int i = 1; i <= 4; i++) {
            data.nextDays[i-1].tempMax    = doc["daily"]["temperature_2m_max"][i].as<float>();
            data.nextDays[i-1].weatherIcon = getWeatherIcon(doc["daily"]["weathercode"][i].as<int>(), true);

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
        Serial.println(payload);

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

void getWeatherData(QueueHandle_t xQueueMeteo) {
    if (WiFi.status() != WL_CONNECTED) return;
    WeatherData data = {0};
    data = getWeatherData_openmeteo();
    data = getWeatherData_openweather(data);
    
    if (xQueueSend(xQueueMeteo, &data, portMAX_DELAY) != pdPASS) {
        Serial.println("Errore invio dati meteo");
    }
}

void weatherTask(void *pvParameters) {
    QueueHandle_t xQueue = (QueueHandle_t) pvParameters;
    for (;;) {
        getWeatherData(xQueue);
        vTaskDelay(pdMS_TO_TICKS(600000));
    }
}

void weatherInit(QueueHandle_t xQueueMeteo) {
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("Wi-Fi connesso");
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

    xTaskCreate(weatherTask, "WeatherTask", 8192, (void*)xQueueMeteo, 5, NULL);
}

