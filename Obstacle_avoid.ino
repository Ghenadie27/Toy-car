#include <Servo.h>
int servoPin = 12;
int unghi = 0;
Servo motor_servo;

int motor_1a = 4;
int motor_1b = 5;
int motor_2a = 6;
int motor_2b = 7;
int TrigPin = 9;
int EchoPin = 11;
float pingTime;
int ledRed = 2;
int ledGreen = 3;

void setup() {
  Serial.begin(9600);
  pinMode(TrigPin, OUTPUT);
  pinMode(EchoPin, INPUT);
  pinMode(motor_1a, OUTPUT);
  pinMode(motor_1b, OUTPUT);
  pinMode(motor_2a, OUTPUT);
  pinMode(motor_2b, OUTPUT);
  pinMode(ledRed, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  motor_servo.attach(servoPin);

}

void loop() {

  digitalWrite(TrigPin, LOW);
  delay(2);//milisecunde 1/1000
  digitalWrite(TrigPin, HIGH);
  delayMicroseconds(10);//microsecunde 1/1000000
  digitalWrite(TrigPin, LOW);

  pingTime = pulseIn(EchoPin, HIGH); //returneaza microsecunde
  float secunde = pingTime / 1000000;
  float distanta = secunde * 343; // viteza este 343m pe secunda
  float centimetri = distanta * 100;
  centimetri = centimetri / 2;

  Serial.print("Distanta:");
  Serial.println(centimetri);

  if (centimetri >= 25)
  { digitalWrite(motor_1b, HIGH);
    digitalWrite(motor_1a, LOW);
    digitalWrite(motor_2b, HIGH);
    digitalWrite(motor_2a, LOW);
    digitalWrite(ledGreen, HIGH);
    digitalWrite(ledRed, LOW);
  } else {
    digitalWrite(motor_1a, HIGH);
    digitalWrite(motor_1b, LOW);
    digitalWrite(motor_2a, LOW);
    digitalWrite(motor_2b, LOW);
    digitalWrite(ledRed, HIGH);
    digitalWrite(ledGreen, LOW);
    
    for (unghi = 0; unghi < 180; unghi++) {
      motor_servo.write(unghi);
      delay(2);
    }
    for (unghi = 180; unghi > 90; unghi--) {
      motor_servo.write(unghi);
      delay(2);
    }
    
  }

}
