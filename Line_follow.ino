#include "DHT.h"
#include <LiquidCrystal_I2C.h>
#define DHTPIN 11
#define DHTTYPE DHT21 // AM2301 
LiquidCrystal_I2C lcd(0x27, 16, 2);
DHT dht(DHTPIN, DHTTYPE);

int LEFT_SENSORPIN = 10;
int CENTER_SENSORPIN = 9;
int RIGHT_SENSORPIN = 8;

int motor_1a = 4;
int motor_1b = 5;
int motor_2a = 6;
int motor_2b = 7;

int ledDreapta = 12;
int ledInainte = 3;
int ledStanga = 2;


void setup()
{
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  Serial.println("DHT test!");
  dht.begin();

  pinMode(ledDreapta, OUTPUT);
  pinMode(ledInainte, OUTPUT);
  pinMode(ledStanga, OUTPUT);

  Serial.println("***LINE FOLLOWER***");
  pinMode(LEFT_SENSORPIN, INPUT);
  pinMode(CENTER_SENSORPIN, INPUT);
  pinMode(RIGHT_SENSORPIN, INPUT);

  pinMode(motor_1a, OUTPUT);
  pinMode(motor_1b, OUTPUT);
  pinMode(motor_2a, OUTPUT);
  pinMode(motor_2b, OUTPUT);

}

void loop()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  // check if returns are valid, if they are NaN (not a number) then something went wrong!
  if (isnan(t) || isnan(h))
  {
    Serial.println("Failed to read from DHT");
  }
  else
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("T: ");
    lcd.setCursor(0, 1);
    lcd.print("H: ");
    lcd.setCursor(3, 0);
    lcd.print(t);
    lcd.setCursor(3, 1);
    lcd.print(h);
    lcd.setCursor(7, 0);
    lcd.print("   LINE  ");
    lcd.setCursor(7, 1);
    lcd.print(" FOLLOWER");
  }

  byte leftSensor = digitalRead(LEFT_SENSORPIN);
  byte centerSensor = digitalRead(CENTER_SENSORPIN);
  byte rightSensor = digitalRead(RIGHT_SENSORPIN);

  //Serial.println(leftSensor);
  //Serial.println(centerSensor);
  //Serial.println(rightSensor);

  if (leftSensor == 1 && centerSensor == 0 && rightSensor == 1)
  {
    digitalWrite(motor_1b, HIGH);
    digitalWrite(motor_1a, LOW);
    digitalWrite(motor_2b, HIGH);
    digitalWrite(motor_2a, LOW);
    digitalWrite(ledStanga, LOW);
    digitalWrite(ledDreapta, LOW);
    digitalWrite(ledInainte, HIGH);

  }

  else if (leftSensor == 0 && centerSensor == 1 && rightSensor == 1)
  {
    digitalWrite(motor_1b, LOW);
    digitalWrite(motor_1a, LOW);
    digitalWrite(motor_2b, HIGH);
    digitalWrite(motor_2a, LOW);
    digitalWrite(ledInainte, LOW);
    digitalWrite(ledStanga, LOW);
    digitalWrite(ledDreapta, HIGH);
  }

  else if (leftSensor == 1 && centerSensor == 1 && rightSensor == 0)
  { digitalWrite(motor_1b, HIGH);
    digitalWrite(motor_1a, LOW);
    digitalWrite(motor_2b, LOW);
    digitalWrite(motor_2a, LOW);
    digitalWrite(ledStanga, HIGH);
    digitalWrite(ledInainte, LOW);
    digitalWrite(ledDreapta, LOW);

  }

}
