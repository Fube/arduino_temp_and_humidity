#include "DHT.h"
#include <LiquidCrystal.h>
#define DHTPIN 13
#define DHTTYPE DHT11 
#define SWITCH_PIN 8
DHT dht(DHTPIN, DHTTYPE);

byte degree[8]= { // Array of bytes
  B00111,  // B stands for binary formatter and the 5 numbers are the pixels
  B00101,
  B00111,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
};


// Creates an LC object. Parameters: (rs, enable, d4, d5, d6, d7)
LiquidCrystal lcd(2, 3, 4, 5, 6, 7); 

void setup() {
  Serial.begin(9600);
  dht.begin();

  pinMode(SWITCH_PIN, INPUT_PULLUP);

  lcd.begin(16,2);
  lcd.createChar(7, degree); 
}

void loop() {
  
  float h = dht.readHumidity();
  float t = dht.readTemperature();
//  float f = dht.convertCtoF(t);

  if (isnan(h) || isnan(t) /*|| isnan(f)*/) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }


  char fToS[2];
  char strBuf[16];
  dtostrf(t, 2, 0, fToS);

  sprintf(strBuf, "%-8s : %-2s ", "Temp", fToS);

  lcd.clear();
  
  lcd.print(strBuf);
  lcd.write(7);
  lcd.print("C");

  dtostrf(h, 2, 0, fToS);
  sprintf(strBuf, "%-8s : %-2s RH", "Humidity", fToS);

  lcd.setCursor(0, 1);
  lcd.print(strBuf);

  delay(2000);

}
