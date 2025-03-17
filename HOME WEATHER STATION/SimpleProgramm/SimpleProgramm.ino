#include <LiquidCrystal.h>
#include <dht.h>
dht DHT;
//Constants
#define DHT11_PIN 2
//LCD pin to Arduino


int redpin = 11;
int bluepin = 13;
int greenpin = 12;
const int pin_RS = 8; 
const int pin_EN = 9; 
const int pin_d4 = 4; 
const int pin_d5 = 5; 
const int pin_d6 = 6; 
const int pin_d7 = 7; 
const int pin_BL = 10; 
float hum;  //Stores humidity value
float tempc; //Stores temperature value
float tempf; //Stores temperature value
LiquidCrystal lcd( pin_RS,  pin_EN,  pin_d4,  pin_d5,  pin_d6,  pin_d7);
void setup() {
  pinMode(11,OUTPUT);
pinMode(12,OUTPUT);
pinMode(13,OUTPUT);
 Serial.begin(9600);
 lcd.begin(16, 2);
 lcd.setCursor(0,0);
 lcd.print("Temp:");
 lcd.setCursor(0,1);
 lcd.print("Humi:");
}
void loop() {
  int chk = DHT.read11(DHT11_PIN);
    //Read data and store it to variables hum and temp
    hum = DHT.humidity;
    tempc= DHT.temperature;
    tempf= (tempc*1.8)+32;
    //Print temp and humidity values to serial monitor    
    lcd.setCursor(6,0);
    lcd.print(tempc); 
    lcd.print(" C");  
    lcd.setCursor(6,1);
    lcd.print(hum);
    lcd.print(" %");
    if(tempc<19){
    digitalWrite(bluepin, LOW);
    digitalWrite(redpin, HIGH);
    digitalWrite(greenpin, HIGH);  
  }
  else if(tempc>22){
    digitalWrite(bluepin, HIGH);
    digitalWrite(redpin, LOW);
    digitalWrite(greenpin, HIGH);
  }
  else{
    digitalWrite(bluepin, HIGH);
    digitalWrite(redpin, HIGH);
    digitalWrite(greenpin, LOW);
  }

  delay(2000);
}
