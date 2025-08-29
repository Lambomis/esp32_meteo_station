#ifndef WEATHER_TASK_H
#define WEATHER_TASK_H

#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

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

// --- Variabili globali (visibili agli altri moduli) --- //
extern QueueHandle_t xQueueMeteo;

// --- Funzioni pubbliche --- //
void weatherInit();   // Inizializza WiFi, queue e avvia il task meteo

#endif

