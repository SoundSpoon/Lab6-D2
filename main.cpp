//▶︎ •၊၊||၊|။|||| |၊၊•    •၊၊||၊|။||||။‌‌‌‌‌၊|• 
// Universidad del Valle de Guatemala
// BE3029- Electronica digital 2
// Allan Lemus
// 5/08/25
// Laboratorio 3
// MCU: ESP32
//▶︎ •၊၊||၊|။|||| |၊၊•    •၊၊||၊|။||||။‌‌‌‌‌၊|•


//▶︎ •၊၊||၊|။|||| |၊၊•  Librerías  •၊၊||၊|။||||။‌‌‌‌‌၊|• 

#include <Arduino.h>
#include <stdint.h>
#include <LiquidCrystal.h>
#include "driver/ledc.h"
#include "config.h"

//▶︎ •၊၊||၊|။|||| |၊၊•  Definiciones  •၊၊||၊|။||||။‌‌‌‌‌၊|• 

#define rs 5
#define en 18
#define d4 19
#define d5 21 
#define d6 22
#define d7 23
#define pot1 13
#define pot2 14
#define l1 15
#define l2 12
#define l3 26
#define Freq   50
#define Res   12
#define Min 1000   
#define Canal1 0
#define Canal2 1  
#define Canal3 2    
int lecturaP1;
int lecturaP2;
int contador = 0;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);






//▶︎ •၊၊||၊|။|||| |၊၊•  Variables Globales  •၊၊||၊|။||||။‌‌‌‌‌၊|• 




//▶︎ •၊၊||၊|။|||| |၊၊•  ISRs rutinas de interrupción  •၊၊||၊|။||||။‌‌‌‌‌၊|• 




//▶︎ •၊၊||၊|။|||| |၊၊•  Configuraciones  •၊၊||၊|။||||။‌‌‌‌‌၊|• 

void setup() {
  
  Serial.begin(115200);
  lcd.begin(16,2);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Rojo Verde Azul");
  ledcSetup(Canal1, Freq, Res);
  ledcAttachPin(l1, Canal1);
  ledcSetup(Canal2, Freq, Res);
  ledcAttachPin(l2, Canal2);
  ledcSetup(Canal3, Freq, Res);
  ledcAttachPin(l3, Canal3);
}

//▶︎ •၊၊||၊|။|||| |၊၊•  Loop infinito  •၊၊||၊|။||||။‌‌‌‌‌၊|• 

void loop() {
  ledcWrite(Canal1, contador);
  ledcWrite(Canal2, lecturaP1);
  ledcWrite(Canal3, lecturaP2);
  lecturaP1 = analogRead(pot1) >> 4;
  lecturaP2 = analogRead(pot2) >> 4;
  Serial.println("Intensidad Led Roja:");
  Serial.println(lecturaP1);
  Serial.println("Intensidad Led Verde:");
  Serial.println(lecturaP2);
   if (Serial.available()) {
    char dato = Serial.read();
    if (dato == '+' && contador < 255) contador++;
    if (dato == '-' && contador > 0) contador--;
    Serial.print("Azul: ");
    Serial.println(contador);
  }
  lcd.setCursor(0, 1);
  lcd.print(lecturaP1);
  lcd.print("   "); 
  lcd.print(lecturaP2);
  lcd.print("   "); 
  lcd.print(contador);
  lcd.print("   "); 
  delay(500);
}

//▶︎ •၊၊||၊|။|||| |၊၊•  Otras funciones  •၊၊||၊|။||||။‌‌‌‌‌၊|• 


