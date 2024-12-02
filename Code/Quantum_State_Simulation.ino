#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#define layer1 3
#define layer2 2
#define layer3 13

#define potX A3
#define potY A2
#define potZ A1

LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
  for (int i = 12; i > 3;i--) {
    pinMode(i, OUTPUT);
  }
  pinMode(layer1, OUTPUT);
  pinMode(layer2, OUTPUT);
  pinMode(layer3, OUTPUT);

  pinMode(potX, INPUT);
  pinMode(potY, INPUT);
  pinMode(potZ, INPUT);

  digitalWrite(layer1, HIGH);
  digitalWrite(layer2, HIGH);
  digitalWrite(layer3, HIGH);

  lcd.init();

  lcd.backlight();
  lcd.setCursor(0, 0);             // Set cursor to the first column, first row
  lcd.print("Welcome to");    // Print text on the first row
  lcd.setCursor(0, 1);             // Set cursor to the first column, second row
  lcd.print("Quantumania!"); 
  delay(3000);
  Serial.begin(9600);
  lcd.clear();
}

void loop() {
  int xVal = analogRead(potX);
  int yVal = analogRead(potY);
  int zVal = analogRead(potZ);

  int xAngle = map(xVal, 0, 1023, 360, 0);
  int yAngle = map(yVal, 0, 1023, 360, 0);
  int zAngle = map(zVal, 0, 1023, 360, 0);

  lcd.clear();
  lcd.setCursor(0, 0); 
  lcd.print("X:");
  lcd.print(xAngle);
  lcd.print(" Y:");
  lcd.print(yAngle);

  lcd.setCursor(0, 1);
  lcd.print(" Z:");
  lcd.print(zAngle);

  float xRadians = radians(xAngle);
  float yRadians = radians(yAngle);
  float zRadians = radians(zAngle);

  Serial.print("X:");
  Serial.print(xAngle);
  Serial.print(" Y:");
  Serial.print(yAngle);
  Serial.print(" Z: ");
  Serial.println(zAngle);

  if (xAngle == 0 || xAngle == 360 || zAngle > 0 && xAngle == 0 && yAngle == 0) {
    resetCube();
  } else if (xAngle > 0 && xAngle < 90) {
    if(zAngle > 0 && zAngle < 90){
      if(yAngle > 0 && yAngle < 90){
        const int pins[] = {8, 7,4};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle == 90){
        const int pins[] = {8, 7,4};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle > 90 && yAngle < 180){
        const int pins[] = {8, 7,4};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, LOW};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle == 180){
        const int pins[] = {8, 7};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, LOW};
        updateCube(pins, 2, layers, states, 3);
      }else if(yAngle > 180 && yAngle < 270){
        const int pins[] = {8, 7,10};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, LOW};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle > 270 && yAngle < 360){
        const int pins[] = {8, 7,10};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle == 270){
        const int pins[] = {8, 7,10};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else{
        const int pins[] = {8, 7};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 2, layers, states, 3);
      }
    }else if(zAngle == 90){
      if(yAngle > 0 && yAngle < 90){
        const int pins[] = {8, 4,5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle == 90){
        const int pins[] = {8, 4,5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle > 90 && yAngle < 180){
        const int pins[] = {8, 4,5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, LOW};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle == 180){
        const int pins[] = {8, 4};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, LOW};
        updateCube(pins, 2, layers, states, 3);
      }else if(yAngle > 180 && yAngle < 270){
        const int pins[] = {8,4, 7};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, LOW};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle > 270 && yAngle < 360){
        const int pins[] = {8,4, 7};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle == 270){
        const int pins[] = {8,4, 7};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else{
        const int pins[] = {8, 4};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 2, layers, states, 3);
      }
    }else if(zAngle > 90 && zAngle < 180){
      if(yAngle > 0 && yAngle < 90){
        const int pins[] = {8, 5,6};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle == 90){
        const int pins[] = {8, 5,6};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle > 90 && yAngle < 180){
        const int pins[] = {8, 5,6};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, LOW};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle == 180){
        const int pins[] = {8, 5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, LOW};
        updateCube(pins, 2, layers, states, 3);
      }else if(yAngle > 180 && yAngle < 270){
        const int pins[] = {8, 5,4};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, LOW};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle > 270 && yAngle < 360){
        const int pins[] = {8, 5,4};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle == 270){
        const int pins[] = {8, 5,4};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else{
        const int pins[] = {8, 5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 2, layers, states, 3);
      }
    }else if(zAngle == 180){
      if(yAngle > 0 && yAngle < 90){
        const int pins[] = {8, 6,9};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle == 90){
        const int pins[] = {8, 6,9};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle > 90 && yAngle < 180){
        const int pins[] = {8, 6,9};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, LOW};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle == 180){
        const int pins[] = {8, 9};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, LOW};
        updateCube(pins, 2, layers, states, 3);
      }else if(yAngle > 180 && yAngle < 270){
        const int pins[] = {8, 6,5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, LOW};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle > 270 && yAngle < 360){
        const int pins[] = {8, 6,5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle == 270){
        const int pins[] = {8, 6,5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else{
        const int pins[] = {8, 6};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 2, layers, states, 3);
      }
    }else if(zAngle > 180 && zAngle < 270){
      if(yAngle > 0 && yAngle < 90){
        const int pins[] = {8, 9,12};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle == 90){
        const int pins[] = {8, 9,12};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle > 90 && yAngle < 180){
        const int pins[] = {8, 9,12};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, LOW};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle == 180){
        const int pins[] = {8, 9};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, LOW};
        updateCube(pins, 2, layers, states, 3);
      }else if(yAngle > 180 && yAngle < 270){
        const int pins[] = {8, 9,6};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, LOW};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle > 270 && yAngle < 360){
        const int pins[] = {8, 9,6};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle == 270){
        const int pins[] = {8, 9,6};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else{
        const int pins[] = {8, 9};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 2, layers, states, 3);
      }
    }else if(zAngle > 270 && zAngle < 360){
      if(yAngle > 0 && yAngle < 90){
        const int pins[] = {8, 11,10};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle == 90){
        const int pins[] = {8, 11,10};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle > 90 && yAngle < 180){
        const int pins[] = {8, 11,10};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, LOW};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle == 180){
        const int pins[] = {8, 11};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, LOW};
        updateCube(pins, 2, layers, states, 3);
      }else if(yAngle > 180 && yAngle < 270){
        const int pins[] = {8, 11,12};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, LOW};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle > 270 && yAngle < 360){
        const int pins[] = {8, 11,12};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle == 270){
        const int pins[] = {8, 11,12};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else{
        const int pins[] = {8, 11};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 2, layers, states, 3);
      }
    }else if(zAngle == 270){
      if(yAngle > 0 && yAngle < 90){
        const int pins[] = {8, 12,11};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle == 90){
        const int pins[] = {8, 12,11};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle > 90 && yAngle < 180){
        const int pins[] = {8, 12,11};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, LOW};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle == 180){
        const int pins[] = {8, 12};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, LOW};
        updateCube(pins, 2, layers, states, 3);
      }else if(yAngle > 180 && yAngle < 270){
        const int pins[] = {8, 12,9};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, LOW};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle > 270 && yAngle < 360){
        const int pins[] = {8, 12,9};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle == 270){
        const int pins[] = {8, 11,9};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else{
        const int pins[] = {8, 12};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 2, layers, states, 3);
      }
    }else{
      if(yAngle > 0 && yAngle < 90){
        const int pins[] = {8, 7,10};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle == 90){
        const int pins[] = {8, 7,10};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle > 90 && yAngle < 180){
        const int pins[] = {8, 7,10};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, LOW};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle == 180){
        const int pins[] = {8, 10};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, LOW};
        updateCube(pins, 2, layers, states, 3);
      }else if(yAngle > 180 && yAngle < 270){
        const int pins[] = {8, 11,10};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, LOW};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle > 270 && yAngle < 360){
        const int pins[] = {8, 11,10};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle == 270){
        const int pins[] = {8, 11,10};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else{
        const int pins[] = {8, 10};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 2, layers, states, 3);
      }
    }
  }else if (xAngle == 90 && yAngle == 0) {
    if(zAngle > 0 && zAngle < 90){
      const int pins[] = {8, 7};
      const int layers[] = {layer1, layer2, layer3};
      const int states[] = {HIGH, LOW, HIGH};
      updateCube(pins, 2, layers, states, 3);
    }else if(zAngle == 90){
      const int pins[] = {8, 4};
      const int layers[] = {layer1, layer2, layer3};
      const int states[] = {HIGH, LOW, HIGH};
      updateCube(pins, 2, layers, states, 3);
    }else if(zAngle > 90 && zAngle < 180){
      const int pins[] = {8, 5};
      const int layers[] = {layer1, layer2, layer3};
      const int states[] = {HIGH, LOW, HIGH};
      updateCube(pins, 2, layers, states, 3);
    }else if(zAngle == 180){
      const int pins[] = {8, 6};
      const int layers[] = {layer1, layer2, layer3};
      const int states[] = {HIGH, LOW, HIGH};
      updateCube(pins, 2, layers, states, 3);
    }else if(zAngle > 180 && zAngle < 270){
      const int pins[] = {8, 9};
      const int layers[] = {layer1, layer2, layer3};
      const int states[] = {HIGH, LOW, HIGH};
      updateCube(pins, 2, layers, states, 3);
    }else if(zAngle > 270 && zAngle < 360){
      const int pins[] = {8, 11};
      const int layers[] = {layer1, layer2, layer3};
      const int states[] = {HIGH, LOW, HIGH};
      updateCube(pins, 2, layers, states, 3);
    }else if(zAngle == 270){
      const int pins[] = {8, 12};
      const int layers[] = {layer1, layer2, layer3};
      const int states[] = {HIGH, LOW, HIGH};
      updateCube(pins, 2, layers, states, 3);
    }else{
      const int pins[] = {8, 10};
      const int layers[] = {layer1, layer2, layer3};
      const int states[] = {HIGH, LOW, HIGH};
      updateCube(pins, 2, layers, states, 3);
    }
  } else if (xAngle > 90 && xAngle < 180) {
    if(zAngle > 0 && zAngle < 90){
      if(yAngle > 0 && yAngle < 90){
        const int pins[] = {8, 7,10};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, LOW};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle == 90){
        const int pins[] = {8, 7,10};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle > 90 && yAngle < 180){
        const int pins[] = {8, 7,10};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle == 180){
        const int pins[] = {8, 7};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 2, layers, states, 3);
      }else if(yAngle > 180 && yAngle < 270){
        const int pins[] = {8, 7,4};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle > 270 && yAngle < 360){
        const int pins[] = {8, 7,4};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, LOW};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle == 270){
        const int pins[] = {8, 7,4};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else{
        const int pins[] = {8, 7};
      const int layers[] = {layer1, layer2, layer3};
      const int states[] = {HIGH, LOW, LOW};
      updateCube(pins, 2, layers, states, 3);
      }
    }else if(zAngle == 90){
      if(yAngle > 0 && yAngle < 90){
        const int pins[] = {8, 4,7};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, LOW};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle == 90){
        const int pins[] = {8, 4,7};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle > 90 && yAngle < 180){
        const int pins[] = {8, 4,7};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle == 180){
        const int pins[] = {8, 4};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 2, layers, states, 3);
      }else if(yAngle > 180 && yAngle < 270){
        const int pins[] = {8, 4,5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle > 270 && yAngle < 360){
        const int pins[] = {8, 4,5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, LOW};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle == 270){
        const int pins[] = {8, 4,5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else{
        const int pins[] = {8, 4};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, LOW};
        updateCube(pins, 2, layers, states, 3);
      }
    }else if(zAngle > 90 && zAngle < 180){
      if(yAngle > 0 && yAngle < 90){
        const int pins[] = {8, 4,5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, LOW};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle == 90){
        const int pins[] = {8, 4,5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle > 90 && yAngle < 180){
        const int pins[] = {8, 4,5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle == 180){
        const int pins[] = {8, 5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 2, layers, states, 3);
      }else if(yAngle > 180 && yAngle < 270){
        const int pins[] = {8, 5,6};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle > 270 && yAngle < 360){
        const int pins[] = {8, 5,6};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, LOW};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle == 270){
        const int pins[] = {8, 5,6};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else{
        const int pins[] = {8, 5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, LOW};
        updateCube(pins, 2, layers, states, 3);
      }
    }else if(zAngle == 180){
      if(yAngle > 0 && yAngle < 90){
        const int pins[] = {8, 5,6};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, LOW};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle == 90){
        const int pins[] = {8, 5,6};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle > 90 && yAngle < 180){
        const int pins[] = {8, 5,6};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle == 180){
        const int pins[] = {8, 5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 2, layers, states, 3);
      }else if(yAngle > 180 && yAngle < 270){
        const int pins[] = {8, 9,6};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle > 270 && yAngle < 360){
        const int pins[] = {8, 9,6};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, LOW};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle == 270){
        const int pins[] = {8, 9,6};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else{
        const int pins[] = {8, 6};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, LOW};
        updateCube(pins, 2, layers, states, 3);
      }
    }else if(zAngle > 180 && zAngle < 270){
      if(yAngle > 0 && yAngle < 90){
        const int pins[] = {8, 9,6};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, LOW};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle == 90){
        const int pins[] = {8, 9,6};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle > 90 && yAngle < 180){
        const int pins[] = {8, 9,6};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle == 180){
        const int pins[] = {8, 9};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 2, layers, states, 3);
      }else if(yAngle > 180 && yAngle < 270){
        const int pins[] = {8, 9,12};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle > 270 && yAngle < 360){
        const int pins[] = {8, 9,12};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, LOW};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle == 270){
        const int pins[] = {8, 9,12};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else{
        const int pins[] = {8, 9};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, LOW};
        updateCube(pins, 2, layers, states, 3);
      }
    }else if(zAngle > 270 && zAngle < 360){
      if(yAngle > 0 && yAngle < 90){
        const int pins[] = {8, 12,11};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, LOW};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle == 90){
        const int pins[] = {8, 12,11};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle > 90 && yAngle < 180){
        const int pins[] = {8, 12,11};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle == 180){
        const int pins[] = {8, 11};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 2, layers, states, 3);
      }else if(yAngle > 180 && yAngle < 270){
        const int pins[] = {8, 10,11};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle > 270 && yAngle < 360){
        const int pins[] = {8, 10,11};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, LOW};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle == 270){
        const int pins[] = {8, 10,11};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else{
        const int pins[] = {8, 11};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, LOW};
        updateCube(pins, 2, layers, states, 3);
      }
    }else if(zAngle == 270){
      if(yAngle > 0 && yAngle < 90){
        const int pins[] = {8, 12,9};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, LOW};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle == 90){
        const int pins[] = {8, 12,9};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle > 90 && yAngle < 180){
        const int pins[] = {8, 12,9};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle == 180){
        const int pins[] = {8, 12};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 2, layers, states, 3);
      }else if(yAngle > 180 && yAngle < 270){
        const int pins[] = {8, 12,11};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle > 270 && yAngle < 360){
        const int pins[] = {8, 12,11};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, LOW};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle == 270){
        const int pins[] = {8, 12,11};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else{
        const int pins[] = {8, 12};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, LOW};
        updateCube(pins, 2, layers, states, 3);
      }
    }else{
      if(yAngle > 0 && yAngle < 90){
        const int pins[] = {8, 11,10};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, LOW};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle == 90){
        const int pins[] = {8, 11,10};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle > 90 && yAngle < 180){
        const int pins[] = {8, 11,10};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle == 180){
        const int pins[] = {8, 11};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 2, layers, states, 3);
      }else if(yAngle > 180 && yAngle < 270){
        const int pins[] = {8, 10,7};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle > 270 && yAngle < 360){
        const int pins[] = {8, 10,7};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, LOW};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle == 270){
        const int pins[] = {8, 10,7};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else{
        const int pins[] = {8, 10};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, LOW};
        updateCube(pins, 2, layers, states, 3);
      }
    }
  } else if (xAngle == 180) {
    if(yAngle > 0 && yAngle < 90){
        const int pins[] = {8,12};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, LOW};
        updateCube(pins, 2, layers, states, 3);
      }else if(yAngle == 90){
        const int pins[] = {8,12};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, HIGH};
        updateCube(pins, 2, layers, states, 3);
      }else if(yAngle > 90 && yAngle < 180){
        const int pins[] = {8,12};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 2, layers, states, 3);
      }else if(yAngle == 180){
        const int pins[] = {8};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 1, layers, states, 3);
      }else if(yAngle > 180 && yAngle < 270){
        const int pins[] = {8,4};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 2, layers, states, 3);
      }else if(yAngle > 270 && yAngle < 360){
        const int pins[] = {8,4};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, LOW};
        updateCube(pins, 2, layers, states, 3);
      }else if(yAngle == 270){
        const int pins[] = {8,4};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, HIGH};
        updateCube(pins, 2, layers, states, 3);
      }else{
        const int pins[] = {8};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, LOW};
        updateCube(pins, 1, layers, states, 3);
      }
  } else if (xAngle < 270 && xAngle > 180) {
    if(zAngle > 0 && zAngle < 90){
      if(yAngle > 0 && yAngle < 90){
        const int pins[] = {8, 9,6};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, LOW};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle == 90){
        const int pins[] = {8, 9,6};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle > 90 && yAngle < 180){
        const int pins[] = {8, 9,6};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle == 180){
        const int pins[] = {8,9};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 1, layers, states, 3);
      }else if(yAngle > 180 && yAngle < 270){
        const int pins[] = {8, 9,12};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle == 270){
        const int pins[] = {8, 9,12};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle > 270 && yAngle < 360){
        const int pins[] = {8, 9,12};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, LOW};
        updateCube(pins, 3, layers, states, 3);
      }else{
        const int pins[] = {8, 9};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, LOW};
        updateCube(pins, 2, layers, states, 3);
      }
    }else if(zAngle == 90){
      if(yAngle > 0 && yAngle < 90){
        const int pins[] = {8, 9,12};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, LOW};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle == 90){
        const int pins[] = {8, 9,12};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle > 90 && yAngle < 180){
        const int pins[] = {8, 9,12};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle == 180){
        const int pins[] = {8,12};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 1, layers, states, 3);
      }else if(yAngle > 180 && yAngle < 270){
        const int pins[] = {8, 11,12};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle == 270){
        const int pins[] = {8, 11,12};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle > 270 && yAngle < 360){
        const int pins[] = {8, 11,12};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, LOW};
        updateCube(pins, 3, layers, states, 3);
      }else{
        const int pins[] = {8, 12};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, LOW};
        updateCube(pins, 2, layers, states, 3);
      }
    }else if(zAngle > 90 && zAngle < 180){
      if(yAngle > 0 && yAngle < 90){
        const int pins[] = {8, 11,12};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, LOW};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle == 90){
        const int pins[] = {8, 11,12};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle > 90 && yAngle < 180){
        const int pins[] = {8, 11,12};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle == 180){
        const int pins[] = {8,11};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 1, layers, states, 3);
      }else if(yAngle > 180 && yAngle < 270){
        const int pins[] = {8, 11,10};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle == 270){
        const int pins[] = {8, 11,10};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle > 270 && yAngle < 360){
        const int pins[] = {8, 11,10};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, LOW};
        updateCube(pins, 3, layers, states, 3);
      }else{
        const int pins[] = {8, 11};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, LOW};
        updateCube(pins, 2, layers, states, 3);
      }
    }else if(zAngle == 180){
      if(yAngle > 0 && yAngle < 90){
        const int pins[] = {8, 11,10};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, LOW};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle == 90){
        const int pins[] = {8, 11,10};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle > 90 && yAngle < 180){
        const int pins[] = {8, 11,10};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle == 180){
        const int pins[] = {8,10};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 1, layers, states, 3);
      }else if(yAngle > 180 && yAngle < 270){
        const int pins[] = {8, 7,10};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle == 270){
        const int pins[] = {8, 7,10};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle > 270 && yAngle < 360){
        const int pins[] = {8, 7,10};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, LOW};
        updateCube(pins, 3, layers, states, 3);
      }else{
        const int pins[] = {8, 10};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, LOW};
        updateCube(pins, 2, layers, states, 3);
      }
    }else if(zAngle > 180 && zAngle < 270){
      if(yAngle > 0 && yAngle < 90){
        const int pins[] = {8, 7,10};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, LOW};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle == 90){
        const int pins[] = {8, 7,10};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle > 90 && yAngle < 180){
        const int pins[] = {8, 7,10};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle == 180){
        const int pins[] = {8,7};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 1, layers, states, 3);
      }else if(yAngle > 180 && yAngle < 270){
        const int pins[] = {8, 7,4};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle == 270){
        const int pins[] = {8, 7,4};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle > 270 && yAngle < 360){
        const int pins[] = {8, 7,4};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, LOW};
        updateCube(pins, 3, layers, states, 3);
      }else{
        const int pins[] = {8, 7};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, LOW};
        updateCube(pins, 2, layers, states, 3);
      }
    }else if(zAngle == 270){
      if(yAngle > 0 && yAngle < 90){
        const int pins[] = {8, 7,4};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, LOW};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle == 90){
        const int pins[] = {8, 7,4};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle > 90 && yAngle < 180){
        const int pins[] = {8, 7,4};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle == 180){
        const int pins[] = {8,4};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 1, layers, states, 3);
      }else if(yAngle > 180 && yAngle < 270){
        const int pins[] = {8, 5,4};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle == 270){
        const int pins[] = {8, 5,4};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle > 270 && yAngle < 360){
        const int pins[] = {8, 5,4};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, LOW};
        updateCube(pins, 3, layers, states, 3);
      }else{
        const int pins[] = {8, 4};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, LOW};
        updateCube(pins, 2, layers, states, 3);
      }
    }else if(zAngle > 270 && zAngle < 360){
      if(yAngle > 0 && yAngle < 90){
        const int pins[] = {8, 5,4};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, LOW};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle == 90){
        const int pins[] = {8, 5,4};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle > 90 && yAngle < 180){
        const int pins[] = {8, 5,4};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle == 180){
        const int pins[] = {8,5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 1, layers, states, 3);
      }else if(yAngle > 180 && yAngle < 270){
        const int pins[] = {8, 5,6};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle == 270){
        const int pins[] = {8, 5,6};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle > 270 && yAngle < 360){
        const int pins[] = {8, 5,6};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, LOW};
        updateCube(pins, 3, layers, states, 3);
      }else{
        const int pins[] = {8, 5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, LOW};
        updateCube(pins, 2, layers, states, 3);
      }
    }else{
      if(yAngle > 0 && yAngle < 90){
        const int pins[] = {8, 6,9};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, LOW};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle == 90){
        const int pins[] = {8, 6,9};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle > 90 && yAngle < 180){
        const int pins[] = {8, 6,9};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle == 180){
        const int pins[] = {8,6};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 1, layers, states, 3);
      }else if(yAngle > 180 && yAngle < 270){
        const int pins[] = {8, 6,5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle == 270){
        const int pins[] = {8, 6,5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle > 270 && yAngle < 360){
        const int pins[] = {8, 6,5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, LOW};
        updateCube(pins, 3, layers, states, 3);
      }else{
        const int pins[] = {8, 6};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, LOW};
        updateCube(pins, 2, layers, states, 3);
      }
    }
  } else if (xAngle == 270) {
    if(zAngle > 0 && zAngle < 90){
      const int pins[] = {8, 9};
      const int layers[] = {layer1, layer2, layer3};
      const int states[] = {HIGH, LOW, LOW};
      updateCube(pins, 2, layers, states, 3);
    }else if(zAngle == 90){
      const int pins[] = {8, 12};
      const int layers[] = {layer1, layer2, layer3};
      const int states[] = {HIGH, LOW, LOW};
      updateCube(pins, 2, layers, states, 3);
    }else if(zAngle > 90 && zAngle < 180){
      const int pins[] = {8, 11};
      const int layers[] = {layer1, layer2, layer3};
      const int states[] = {HIGH, LOW, LOW};
      updateCube(pins, 2, layers, states, 3);
    }else if(zAngle == 180){
      const int pins[] = {8, 10};
      const int layers[] = {layer1, layer2, layer3};
      const int states[] = {HIGH, LOW, LOW};
      updateCube(pins, 2, layers, states, 3);
    }else if(zAngle > 180 && zAngle < 270){
      const int pins[] = {8, 7};
      const int layers[] = {layer1, layer2, layer3};
      const int states[] = {HIGH, LOW, LOW};
      updateCube(pins, 2, layers, states, 3);
    }else if(zAngle > 270 && zAngle < 360){
      const int pins[] = {8, 5};
      const int layers[] = {layer1, layer2, layer3};
      const int states[] = {HIGH, LOW, LOW};
      updateCube(pins, 2, layers, states, 3);
    }else if(zAngle == 270){
      const int pins[] = {8, 4};
      const int layers[] = {layer1, layer2, layer3};
      const int states[] = {HIGH, LOW, LOW};
      updateCube(pins, 2, layers, states, 3);
    }else{
      const int pins[] = {8, 6};
      const int layers[] = {layer1, layer2, layer3};
      const int states[] = {HIGH, LOW, HIGH};
      updateCube(pins, 2, layers, states, 3);
    }
  } else if (xAngle > 270 && xAngle < 360) {
    if(zAngle > 0 && zAngle < 90){
      if(yAngle > 0 && yAngle < 90){
        const int pins[] = {8, 6,9};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle == 90){
        const int pins[] = {8, 6,9};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle > 90 && yAngle < 180){
        const int pins[] = {8, 6,9};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, LOW};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle == 180){  
        const int pins[] = {8,9};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 2, layers, states, 3);
      }else if(yAngle > 180 && yAngle < 270){
        const int pins[] = {8, 12,9};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, LOW};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle == 270){
        const int pins[] = {8, 12,9};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle > 270 && yAngle < 360){
        const int pins[] = {8, 12,9};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else{
        const int pins[] = {8, 9};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 2, layers, states, 3);
      }
    }else if(zAngle == 90){
      if(yAngle > 0 && yAngle < 90){
        const int pins[] = {8, 9,12};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle == 90){
        const int pins[] = {8, 9,12};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle > 90 && yAngle < 180){
        const int pins[] = {8, 9,12};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, LOW};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle == 180){  
        const int pins[] = {8,12};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 2, layers, states, 3);
      }else if(yAngle > 180 && yAngle < 270){
        const int pins[] = {8, 11,12};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, LOW};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle == 270){
        const int pins[] = {8, 11,12};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle > 270 && yAngle < 360){
        const int pins[] = {8, 11,12};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else{
        const int pins[] = {8, 12};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 2, layers, states, 3);
      }
    }else if(zAngle > 90 && zAngle < 180){
      if(yAngle > 0 && yAngle < 90){
        const int pins[] = {8, 11,12};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle == 90){
        const int pins[] = {8, 11,12};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle > 90 && yAngle < 180){
        const int pins[] = {8, 11,12};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, LOW};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle == 180){  
        const int pins[] = {8,11};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 2, layers, states, 3);
      }else if(yAngle > 180 && yAngle < 270){
        const int pins[] = {8, 11,10};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, LOW};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle == 270){
        const int pins[] = {8, 11,10};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle > 270 && yAngle < 360){
        const int pins[] = {8, 11,10};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else{
        const int pins[] = {8, 11};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 2, layers, states, 3);
      }
    }else if(zAngle == 180){
      if(yAngle > 0 && yAngle < 90){
        const int pins[] = {8, 11,10};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle == 90){
        const int pins[] = {8, 11,10};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle > 90 && yAngle < 180){
        const int pins[] = {8, 11,10};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, LOW};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle == 180){  
        const int pins[] = {8,10};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 2, layers, states, 3);
      }else if(yAngle > 180 && yAngle < 270){
        const int pins[] = {8, 7,10};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, LOW};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle == 270){
        const int pins[] = {8, 7,10};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle > 270 && yAngle < 360){
        const int pins[] = {8, 7,10};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else{
        const int pins[] = {8, 10};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 2, layers, states, 3);
      }
    }else if(zAngle > 180 && zAngle < 270){
      if(yAngle > 0 && yAngle < 90){
        const int pins[] = {8, 7,10};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle == 90){
        const int pins[] = {8, 7,10};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle > 90 && yAngle < 180){
        const int pins[] = {8, 7,10};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, LOW};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle == 180){  
        const int pins[] = {8,7};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 2, layers, states, 3);
      }else if(yAngle > 180 && yAngle < 270){
        const int pins[] = {8, 7,4};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, LOW};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle == 270){
        const int pins[] = {8, 7,4};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle > 270 && yAngle < 360){
        const int pins[] = {8, 7,4};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else{
        const int pins[] = {8, 7};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 2, layers, states, 3);
      }
    }else if(zAngle > 270 && zAngle < 360){
      if(yAngle > 0 && yAngle < 90){
        const int pins[] = {8, 5,4};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle == 90){
        const int pins[] = {8, 5,4};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle > 90 && yAngle < 180){
        const int pins[] = {8, 5,4};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, LOW};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle == 180){  
        const int pins[] = {8,5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 2, layers, states, 3);
      }else if(yAngle > 180 && yAngle < 270){
        const int pins[] = {8, 5,6};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, LOW};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle == 270){
        const int pins[] = {8, 5,6};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle > 270 && yAngle < 360){
        const int pins[] = {8, 5,6};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else{
        const int pins[] = {8, 5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 2, layers, states, 3);
      }
    }else if(zAngle == 270){
      if(yAngle > 0 && yAngle < 90){
        const int pins[] = {8, 7,4};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle == 90){
        const int pins[] = {8, 7,4};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle > 90 && yAngle < 180){
        const int pins[] = {8, 7,4};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, LOW};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle == 180){  
        const int pins[] = {8,4};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 2, layers, states, 3);
      }else if(yAngle > 180 && yAngle < 270){
        const int pins[] = {8, 5,4};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, LOW};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle == 270){
        const int pins[] = {8, 5,4};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle > 270 && yAngle < 360){
        const int pins[] = {8, 5,4};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else{
        const int pins[] = {8, 4};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 2, layers, states, 3);
      }
    }else{
      if(yAngle > 0 && yAngle < 90){
        const int pins[] = {8, 6,5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle == 90){
        const int pins[] = {8, 6,5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle > 90 && yAngle < 180){
        const int pins[] = {8, 6,5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, LOW};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle == 180){
        const int pins[] = {8,6};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 2, layers, states, 3);
      }else if(yAngle > 180 && yAngle < 270){
        const int pins[] = {8, 6,9};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, LOW};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle == 270){
        const int pins[] = {8, 6,9};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {HIGH, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else if(yAngle > 270 && yAngle < 360){
        const int pins[] = {8, 6,9};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 3, layers, states, 3);
      }else{
        const int pins[] = {8, 6};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {LOW, LOW, HIGH};
        updateCube(pins, 2, layers, states, 3);
      }
    }
  }
}

void resetCube() {
  const int pins[] = {8};
  const int layers[] = {layer1, layer2, layer3};
  const int states[] = {LOW, LOW, HIGH};
  updateCube(pins, 1, layers, states, 3);
}

void updateCube(const int* pins, int pinCount, const int* layers, const int* states, int layerCount) {
  for (int i = 12; i > 3; i--) {
    digitalWrite(i, LOW);
  }

  for (int i = 0; i < pinCount; i++) {
    digitalWrite(pins[i], HIGH);
  }

  for (int i = 0; i < layerCount; i++) {
    digitalWrite(layers[i], states[i]);
  }
}