#pragma once
#include <Arduino.h>

// --- Strutture dati --- //

typedef struct {
    const void* icon;
    const char* description;
} WeatherIcon;

typedef struct {
    float tempC;          // Temperatura attuale
    float tempFeelsLike;  // Temperatura percepita
    float tempMax;        // Max oggi
    float tempMin;        // Min oggi
    float humidity;       // Umidità %
    float windKph;        // Vento km/h
    float pressureMb;     // Pressione in mbar
    float visKm;          // Visibilità in km
    bool isDay;           // flag se è giorno
    int weather_code;     // codice stato meteo
    WeatherIcon weatherIcon;   // stato meteo
} TodayWeather;

typedef struct {
    float tempMax;
    float humidity;
    WeatherIcon weatherIcon;
} ForecastWeather;

typedef struct {
    TodayWeather today;
    ForecastWeather nextDays[4]; // Previsioni 4 giorni
} WeatherData;

typedef struct {
    float umid;
    float temp;
} DHTData;