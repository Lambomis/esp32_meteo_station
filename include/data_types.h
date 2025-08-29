#pragma once
// --- Strutture dati --- //
typedef struct {
    float tempC;          // Temperatura attuale
    float tempFeelsLike;  // Temperatura percepita
    float tempMax;        // Max oggi
    float tempMin;        // Min oggi
    float humidity;       // Umidità %
    float windKph;        // Vento km/h
    float pressureMb;     // Pressione in mbar
    float visKm;          // Visibilità in km
    char condition[64];   // Testo condizione (es: "Partly cloudy")
} TodayWeather;

typedef struct {
    float tempMax;
    float tempMin;
    float humidity;
    char condition[32];
} ForecastWeather;

typedef struct {
    TodayWeather today;
    ForecastWeather nextDays[4]; // Previsioni 4 giorni
} WeatherData;