#include <Arduino.h>
#include <Servo.h>
// smt8 documentation on https://github.com/tenbaht/sduino
// constants won't change. They're used here to
// set pin numbers:
//int soundPin = 6;
const int ojoPin = PD3; //pwm pin
const int botonPin = PD4; //digital pin
const int servoPin = PC3; //analog pin
Servo servo;

// variables will change:
int botonEstado = 0;         // variable for reading the pushbutton status

void setup() {
  // Eye led
  pinMode(ojoPin, OUTPUT);
  pinMode(botonPin, INPUT);
  //servo
  servo = Servo_attach(servoPin);
  Servo_write(servo,90);
}

void loop() {
  botonEstado = digitalRead(botonPin);
  if (botonEstado == HIGH) {
    delay(500);
    ojo_prender();
    delay(1000);
    vigilar();
    delay(3000);
    vigilar();
    delay(2000);
    ojo_apagar();
    delay(500);
  }
}
// eye on
void ojo_prender() {
    int t = 0;
    for (int fadeValue = 0 ; fadeValue <= 200; fadeValue += 5) {
      analogWrite(ojoPin, fadeValue);
      t += 75;
      delay(75);
    }
    for (int fadeValue = 200 ; fadeValue >= 150; fadeValue -= 5) {
      analogWrite(ojoPin, fadeValue);
      t += 10;
      delay(10);
    }

    for (int fadeValue = 150 ; fadeValue <= 255; fadeValue += 5) {
      analogWrite(ojoPin, fadeValue);
      delay(5);
      t += 5;
    }
}
// eye off
void ojo_apagar() {
    for (int fadeValue = 255 ; fadeValue >= 0; fadeValue -= 5) {
      analogWrite(ojoPin, fadeValue);
      delay(30);
    }
}
// watch
void vigilar() {
  int pos;
  int pos_max = 145;
  int pos_min = 45;

  for (pos = pos_min; pos <= pos_max; pos += 1) {
    Servo_write(servo,pos);
    delay(10);
  }
  delay(500);
  for (pos = pos_max; pos >= pos_min; pos -= 1) {
    Servo_write(servo,pos);
    delay(10);
  }
  delay(500);
  Servo_write(servo,90);
}
