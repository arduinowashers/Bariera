#include <Servo.h>  // За Uno използваме стандартната Servo библиотека

// Пинове за ултразвуковия сензор
const int TRIG_PIN = 7;   // Trigger пин
const int ECHO_PIN = 8;   // Echo пин
const int SERVO_PIN = 9;  // Пин за сервомотора (трябва да е PWM пин)

// Създаване на обект за сервомотора
Servo gateServo;

// Константи
const int GATE_CLOSED = 0;     // Затворена позиция на бариерата
const int GATE_OPEN = 90;      // Отворена позиция на бариерата
const int DISTANCE_THRESHOLD = 20;  // Разстояние в см, при което да се задейства
const int GATE_DELAY = 3000;    // Колко време да остане отворена бариерата (3 секунди)

// Променливи за състоянието
bool isGateOpen = false;
unsigned long gateOpenTime = 0;

void setup() {
  Serial.begin(9600);  // За Uno използваме 9600 baud rate
  
  // Конфигуриране на пиновете за ултразвуковия сензор
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  // Инициализация на сервомотора
  gateServo.attach(SERVO_PIN);
  gateServo.write(GATE_CLOSED);
}

// Функция за измерване на разстоянието
int measureDistance() {
  // Изпращане на ултразвуков импулс
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  // Получаване на времето за връщане на ехото
  long duration = pulseIn(ECHO_PIN, HIGH);
  
  // Изчисляване на разстоянието в сантиметри
  int distance = duration * 0.034 / 2;
  
  return distance;
}

