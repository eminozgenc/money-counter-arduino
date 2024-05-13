#include<LCD5110_Basic.h>

#define PIN_IR_SENSOR_500 2
#define PIN_IR_SENSOR_100 3
#define PIN_IR_SENSOR_50 4
#define PIN_IR_SENSOR_25 5
#define PIN_IR_SENSOR_10 6
#define PINS_IR_SENSOR \
  { 2, 3, 4, 5, 6 }
#define PINS_IR_SENSOR_LENGTH 5
#define PINS_LCD \
  { 8, 9, 10, 11, 12 }
#define ACTIVE 0
#define DEACTIVE 1
#define NOT_FOUND -1
#define PIN_LED 7
#define SENSOR_INDEX 0
#define VALUE_INDEX 0

#define LCD_CLK 8
#define LCD_DIN 9
#define LCD_DO 10
#define LCD_CE 12
#define LCD_RST 11

LCD5110 display(LCD_CLK, LCD_DIN, LCD_DO, LCD_RST, LCD_CE);
extern uint8_t SmallFont[];
extern uint8_t MediumNumbers[];
extern uint8_t BigNumbers[];

int totalAmount = 0;

void setup() {
  pinMode(PIN_IR_SENSOR_500, INPUT);
  pinMode(PIN_IR_SENSOR_100, INPUT);
  pinMode(PIN_IR_SENSOR_50, INPUT);
  pinMode(PIN_IR_SENSOR_25, INPUT);
  pinMode(PIN_IR_SENSOR_10, INPUT);

  display.InitLCD();
  Serial.begin(9600);
}

void loop() {
  displayAmount(totalAmount);
  int activatedSensor = findActivatedSensor();
  if (activatedSensor != NOT_FOUND) {
    totalAmount = increaseAmount(activatedSensor, totalAmount);
    displayAmount(totalAmount);
    delay(500);
  }
}

int findActivatedSensor() {
  int pins[] = PINS_IR_SENSOR;
  for (int i = 0; i < PINS_IR_SENSOR_LENGTH; i++) {
    if (digitalRead(pins[i]) == ACTIVE) {
      return pins[i];
    }
  }

  return -1;
}

int increaseAmount(int sensor, int amount) {

  switch (sensor) {
    case PIN_IR_SENSOR_500:
      amount += 500;
      break;
    case PIN_IR_SENSOR_100:
      amount += 100;
      break;
    case PIN_IR_SENSOR_50:
      amount += 50;
      break;
    case PIN_IR_SENSOR_25:
      amount += 25;
      break;
    case PIN_IR_SENSOR_10:
      amount += 10;
      break;
  }

  return amount;
}

void printAmount(int amount) {
  int lira = amount / 100;
  int penny = amount % 100;

  Serial.print(lira);
  Serial.print(" TL ");
  Serial.print(penny);
  Serial.print(" kr");
  Serial.println();
}

void displayAmount(int amount) {
  float lira = (float)amount / (float)100;
  
  display.clrScr();
  display.setFont(BigNumbers);
  display.printNumF(lira, 2, CENTER, 16);
}