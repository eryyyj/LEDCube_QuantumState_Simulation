#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#define layer1 11
#define layer2 10
#define layer3 9

#define potX A3
#define potY A2
#define potZ A1

LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
  for(int i = 8; i > 1; i--){
  	pinMode(i, OUTPUT);
  }
  pinMode(13,OUTPUT);
  pinMode(12,OUTPUT);
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

  int brightnessLayer1 = map(xAngle, 360, 0, 0, 85);
  int brightnessLayer2 = map(yAngle, 360, 0, 0, 85);
  int brightnessLayer3 = map(zAngle, 360, 0, 0, 85);
  
  int finalBrightness = brightnessLayer1 + brightnessLayer2 + brightnessLayer3;
  Serial.print("X:");
  Serial.print(xRadians);
  Serial.print(" Y:");
  Serial.print(yRadians);
  Serial.print(" Z: ");
  Serial.println(zRadians);

  if (xAngle == 0 || xAngle == 360 || zAngle > 0 && xAngle == 0 && yAngle == 0) {
    resetCube();
  } else if (xAngle > 0 && xAngle < 90) {
    if(zAngle > 0 && zAngle < 90){
      if (yAngle > 0 && yAngle < 90) {
          const int pins[] = {6, 2,3};
          const int layers[] = {layer1, layer2, layer3};
          const int states[] = {finalBrightness, finalBrightness, 255};
          updateCube(pins, 3, layers, states, 3);
      }else if (yAngle == 90){
          const int pins[] = {6, 2,3};
          const int layers[] = {layer1, layer2, layer3};
          const int states[] = {255, finalBrightness, 255};
          updateCube(pins, 3, layers, states, 3);
      }else if (yAngle > 90 && yAngle < 180){
          const int pins[] = {6, 2,3};
          const int layers[] = {layer1, layer2, layer3};
          const int states[] = {255, finalBrightness, finalBrightness};
          updateCube(pins, 3, layers, states, 3);
      }else if (yAngle == 180){
          const int pins[] = {6, 3};
          const int layers[] = {layer1, layer2, layer3};
          const int states[] = {255, finalBrightness, finalBrightness};
          updateCube(pins, 2, layers, states, 3);
      }else if (yAngle > 180 && yAngle < 270){
          const int pins[] = {6, 4,3};
          const int layers[] = {layer1, layer2, layer3};
          const int states[] = {255, finalBrightness, finalBrightness};
          updateCube(pins, 3, layers, states, 3);
      }else if (yAngle > 270 && yAngle < 360){
          const int pins[] = {6, 4,3};
          const int layers[] = {layer1, layer2, layer3};
          const int states[] = {finalBrightness, finalBrightness, 255};
          updateCube(pins, 3, layers, states, 3);
      }else if (yAngle == 270){
          const int pins[] = {6, 4,3};
          const int layers[] = {layer1, layer2, layer3};
          const int states[] = {255, finalBrightness, 255};
          updateCube(pins, 3, layers, states, 3);
      }else{
          const int pins[] = {6, 3};
          const int layers[] = {layer1, layer2, layer3};
          const int states[] = {finalBrightness, finalBrightness, 255};
          updateCube(pins, 2, layers, states, 3);
      }
    }else if(zAngle == 90){
      if (yAngle > 0 && yAngle < 90) {
        const int pins[] = {6, 4,3};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {finalBrightness, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle == 90){
        const int pins[] = {6, 4,3};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle > 90 && yAngle < 180){
        const int pins[] = {6, 4,3};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, finalBrightness};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle == 180){
        const int pins[] = {6, 4};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, finalBrightness};
        updateCube(pins, 2, layers, states, 3);
      }else if (yAngle > 180 && yAngle < 270){
        const int pins[] = {6, 4,7};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, finalBrightness};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle > 270 && yAngle < 360){
        const int pins[] = {6, 4,7};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {finalBrightness, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle == 270){
        const int pins[] = {6, 4,7};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else{
        const int pins[] = {6, 4};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {finalBrightness, finalBrightness, 255};
        updateCube(pins, 2, layers, states, 3);
      }
    }else if(zAngle > 90 && zAngle < 180){
      if (yAngle > 0 && yAngle < 90) {
        const int pins[] = {6, 4,7};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {finalBrightness, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle == 90){
        const int pins[] = {6, 4,7};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle > 90 && yAngle < 180){
        const int pins[] = {6, 4,7};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, finalBrightness};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle == 180){
        const int pins[] = {6, 7};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, finalBrightness};
        updateCube(pins, 2, layers, states, 3);
      }else if (yAngle > 180 && yAngle < 270){
        const int pins[] = {6, 13,7};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, finalBrightness};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle > 270 && yAngle < 360){
        const int pins[] = {6, 13,7};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {finalBrightness, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle == 270){
        const int pins[] = {6, 13,7};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else{
        const int pins[] = {6, 7};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {finalBrightness, finalBrightness, 255};
        updateCube(pins, 2, layers, states, 3);
      }
    }else if(zAngle == 180){
      if (yAngle > 0 && yAngle < 90) {
        const int pins[] = {6, 13,7};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {finalBrightness, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle == 90){
        const int pins[] = {6, 13,7};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle > 90 && yAngle < 180){
        const int pins[] = {6, 13,7};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, finalBrightness};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle == 180){
        const int pins[] = {6, 13};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, finalBrightness};
        updateCube(pins, 2, layers, states, 3);
      }else if (yAngle > 180 && yAngle < 270){
        const int pins[] = {6, 13,12};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, finalBrightness};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle > 270 && yAngle < 360){
        const int pins[] = {6, 13,12};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {finalBrightness, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle == 270){
        const int pins[] = {6, 13,12};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else{
        const int pins[] = {6, 13};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {finalBrightness, finalBrightness, 255};
        updateCube(pins, 2, layers, states, 3);
      }
    }else if(zAngle > 180 && zAngle < 270){
      if (yAngle > 0 && yAngle < 90) {
        const int pins[] = {6, 12,13};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {finalBrightness, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle == 90){
        const int pins[] = {6, 12,13};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle > 90 && yAngle < 180){
        const int pins[] = {6, 12,13};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, finalBrightness};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle == 180){
        const int pins[] = {6, 12};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, finalBrightness};
        updateCube(pins, 2, layers, states, 3);
      }else if (yAngle > 180 && yAngle < 270){
        const int pins[] = {6, 12,8};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, finalBrightness};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle > 270 && yAngle < 360){
        const int pins[] = {6, 12,8};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {finalBrightness, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle == 270){
        const int pins[] = {6, 12,8};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else{
        const int pins[] = {6, 12};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {finalBrightness, finalBrightness, 255};
        updateCube(pins, 2, layers, states, 3);
      }
    }else if(zAngle > 270 && zAngle < 360){
      if (yAngle > 0 && yAngle < 90) {
        const int pins[] = {6, 8,5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {finalBrightness, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle == 90) {
        const int pins[] = {6, 8,5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle > 90 && yAngle < 180) {
        const int pins[] = {6, 8,5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, finalBrightness};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle == 180) {
        const int pins[] = {6, 5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, finalBrightness};
        updateCube(pins, 2, layers, states, 3);
      }else if (yAngle > 180 && yAngle < 270) {
        const int pins[] = {6, 2,5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, finalBrightness};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle > 270 && yAngle < 360) {
        const int pins[] = {6, 2,5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {finalBrightness, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle == 270) {
        const int pins[] = {6, 2,5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else {
        const int pins[] = {6, 5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {finalBrightness, finalBrightness, 255};
        updateCube(pins, 2, layers, states, 3);
      }
    }else if(zAngle == 270){
      if (yAngle > 0 && yAngle < 90) {
        const int pins[] = {6, 8,12};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {finalBrightness, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle == 90){
        const int pins[] = {6, 8,12};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle > 90 && yAngle < 180){
        const int pins[] = {6, 8,12};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, finalBrightness};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle == 180){
        const int pins[] = {6, 8};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, finalBrightness};
        updateCube(pins, 2, layers, states, 3);
      }else if (yAngle > 180 && yAngle < 270){
        const int pins[] = {6, 8,5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, finalBrightness};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle > 270 && yAngle < 360){
        const int pins[] = {6, 8,5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {finalBrightness, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle == 270){
        const int pins[] = {6, 8,5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else{
        const int pins[] = {6, 8};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {finalBrightness, finalBrightness, 255};
        updateCube(pins, 2, layers, states, 3);
      }
    }else{
      if (yAngle > 0 && yAngle < 90) {
        const int pins[] = {6, 2,5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {finalBrightness, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle == 90){
        const int pins[] = {6, 2,5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle > 90 && yAngle < 180){
        const int pins[] = {6, 2,5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, finalBrightness};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle == 180){
        const int pins[] = {6, 2};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, finalBrightness};
        updateCube(pins, 2, layers, states, 3);
      }else if (yAngle > 180 && yAngle < 270){
        const int pins[] = {6, 2,3};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, finalBrightness};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle > 270 && yAngle < 360){
        const int pins[] = {6, 2,3};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {finalBrightness, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle == 270){
        const int pins[] = {6, 2,3};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else{
        const int pins[] = {6, 5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {finalBrightness, finalBrightness, 255};
        updateCube(pins, 2, layers, states, 3);
      }
    }
  } else if (xAngle == 90 && yAngle == 0) {
    if (zAngle > 0 && zAngle < 90) {
        const int pins[] = {6, 3};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, 255};
        updateCube(pins, 2, layers, states, 3);
      } else if (zAngle == 90) {
        const int pins[] = {6, 4};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, 255};
        updateCube(pins, 2, layers, states, 3);
      } else if (zAngle > 90 && zAngle < 180) {
        const int pins[] = {6, 7};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, 255};
        updateCube(pins, 2, layers, states, 3);
      } else if (zAngle == 180) {
        const int pins[] = {6, 13};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, 255};
        updateCube(pins, 2, layers, states, 3);
      } else if (zAngle > 180 && zAngle < 270) {
        const int pins[] = {6, 12};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, 255};
        updateCube(pins, 2, layers, states, 3);
      } else if (zAngle > 270 && zAngle < 360) {
        const int pins[] = {6, 5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, 255};
        updateCube(pins, 2, layers, states, 3);
      } else if (zAngle == 270) {
        const int pins[] = {6, 8};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, 255};
        updateCube(pins, 2, layers, states, 3);
      } else {
        const int pins[] = {6, 2};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, 255};
        updateCube(pins, 2, layers, states, 3);
    }
  } else if (xAngle > 90 && xAngle < 180) {
    if (zAngle > 0 && zAngle < 90) {
      if (yAngle > 0 && yAngle < 90) {
          const int pins[] = {6, 2,3};
          const int layers[] = {layer1, layer2, layer3};
          const int states[] = {255, finalBrightness, finalBrightness};
          updateCube(pins, 3, layers, states, 3);
      }else if (yAngle == 90) {
          const int pins[] = {6, 2,3};
          const int layers[] = {layer1, layer2, layer3};
          const int states[] = {255, finalBrightness, 255};
          updateCube(pins, 3, layers, states, 3);
      }else if (yAngle > 90 && yAngle < 180) {
          const int pins[] = {6, 2,3};
          const int layers[] = {layer1, layer2, layer3};
          const int states[] = {finalBrightness, finalBrightness, 255};
          updateCube(pins, 3, layers, states, 3);
      }else if (yAngle == 180) {
          const int pins[] = {6, 3};
          const int layers[] = {layer1, layer2, layer3};
          const int states[] = {finalBrightness, finalBrightness, 255};
          updateCube(pins, 2, layers, states, 3);
      }else if (yAngle > 180 && yAngle < 270) {
          const int pins[] = {6, 4,3};
          const int layers[] = {layer1, layer2, layer3};
          const int states[] = {finalBrightness, finalBrightness, 255};
          updateCube(pins, 3, layers, states, 3);
      }else if (yAngle > 270 && yAngle < 360) {
          const int pins[] = {6, 4,3};
          const int layers[] = {layer1, layer2, layer3};
          const int states[] = {255, finalBrightness, finalBrightness};
          updateCube(pins, 3, layers, states, 3);
      }else if (yAngle == 270) {
          const int pins[] = {6, 4,3};
          const int layers[] = {layer1, layer2, layer3};
          const int states[] = {255, finalBrightness, 255};
          updateCube(pins, 3, layers, states, 3);
      }else{
          const int pins[] = {6, 3};
          const int layers[] = {layer1, layer2, layer3};
          const int states[] = {255, finalBrightness, finalBrightness};
          updateCube(pins, 2, layers, states, 3);
      } 
    }else if (zAngle == 90) {
      if (yAngle > 0 && yAngle < 90) {
          const int pins[] = {6, 4,3};
          const int layers[] = {layer1, layer2, layer3};
          const int states[] = {255, finalBrightness, finalBrightness};
          updateCube(pins, 3, layers, states, 3);
      } else if (yAngle == 90) {
          const int pins[] = {6, 4,3};
          const int layers[] = {layer1, layer2, layer3};
          const int states[] = {255, finalBrightness, 255};
          updateCube(pins, 3, layers, states, 3);
      } else if (yAngle > 90 && yAngle < 180) {
          const int pins[] = {6, 4,3};
          const int layers[] = {layer1, layer2, layer3};
          const int states[] = {finalBrightness, finalBrightness, 255};
          updateCube(pins, 3, layers, states, 3);
      } else if (yAngle == 180) {
          const int pins[] = {6, 4};
          const int layers[] = {layer1, layer2, layer3};
          const int states[] = {finalBrightness, finalBrightness, 255};
          updateCube(pins, 2, layers, states, 3);
      } else if (yAngle > 180 && yAngle < 270) {
          const int pins[] = {6, 4,7};
          const int layers[] = {layer1, layer2, layer3};
          const int states[] = {finalBrightness, finalBrightness, 255};
          updateCube(pins, 3, layers, states, 3);
      } else if (yAngle > 270 && yAngle < 360) {
          const int pins[] = {6, 4,7};
          const int layers[] = {layer1, layer2, layer3};
          const int states[] = {255, finalBrightness, finalBrightness};
          updateCube(pins, 3, layers, states, 3);
      } else if (yAngle == 270) {
          const int pins[] = {6, 4,7};
          const int layers[] = {layer1, layer2, layer3};
          const int states[] = {255, finalBrightness, 255};
          updateCube(pins, 3, layers, states, 3);
      } else {
          const int pins[] = {6, 4};
          const int layers[] = {layer1, layer2, layer3};
          const int states[] = {255, finalBrightness, finalBrightness};
          updateCube(pins, 2, layers, states, 3);
      }
    }else if(zAngle > 90 && zAngle < 180){
      if (yAngle > 0 && yAngle < 90) {
        const int pins[] = {6, 4,7};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, finalBrightness};
        updateCube(pins, 3, layers, states, 3);
      } else if (yAngle == 90) {
        const int pins[] = {6, 4,7};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      } else if (yAngle > 90 && yAngle < 180) {
        const int pins[] = {6, 4,7};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {finalBrightness, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      } else if (yAngle == 180) {
        const int pins[] = {6, 7};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {finalBrightness, finalBrightness, 255};
        updateCube(pins, 2, layers, states, 3);
      } else if (yAngle > 180 && yAngle < 270) {
        const int pins[] = {6, 13,7};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {finalBrightness, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      } else if (yAngle > 270 && yAngle < 360) {
        const int pins[] = {6, 13,7};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, finalBrightness};
        updateCube(pins, 3, layers, states, 3);
      } else if (yAngle == 270) {
        const int pins[] = {6, 13,7};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      } else {
        const int pins[] = {6, 7};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, finalBrightness};
        updateCube(pins, 2, layers, states, 3);
      }
    }else if(zAngle == 180){
      if (yAngle > 0 && yAngle < 90) {
        const int pins[] = {6, 13,7};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, finalBrightness};
        updateCube(pins, 3, layers, states, 3);
      } else if (yAngle == 90) {
        const int pins[] = {6, 13,7};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      } else if (yAngle > 90 && yAngle < 180) {
        const int pins[] = {6, 13,7};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {finalBrightness, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      } else if (yAngle == 180) {
        const int pins[] = {6, 13};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {finalBrightness, finalBrightness, 255};
        updateCube(pins, 2, layers, states, 3);
      } else if (yAngle > 180 && yAngle < 270) {
        const int pins[] = {6, 13,12};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {finalBrightness, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      } else if (yAngle > 270 && yAngle < 360) {
        const int pins[] = {6, 13,12};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, finalBrightness};
        updateCube(pins, 3, layers, states, 3);
      } else if (yAngle == 270) {
        const int pins[] = {6, 13,12};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      } else {
        const int pins[] = {6, 7};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, finalBrightness};
        updateCube(pins, 2, layers, states, 3);
      }
    }else if(zAngle > 180 && zAngle < 270){
      if (yAngle > 0 && yAngle < 90) {
        const int pins[] = {6, 12,13};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, finalBrightness};
        updateCube(pins, 3, layers, states, 3);
      } else if (yAngle == 90) {
        const int pins[] ={6, 12,13};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      } else if (yAngle > 90 && yAngle < 180) {
        const int pins[] = {6, 12,13};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {finalBrightness, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      } else if (yAngle == 180) {
        const int pins[] = {6, 12};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {finalBrightness, finalBrightness, 255};
        updateCube(pins, 2, layers, states, 3);
      } else if (yAngle > 180 && yAngle < 270) {
        const int pins[] = {6, 12,8};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {finalBrightness, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      } else if (yAngle > 270 && yAngle < 360) {
        const int pins[] = {6, 12,8};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, finalBrightness};
        updateCube(pins, 3, layers, states, 3);
      } else if (yAngle == 270) {
        const int pins[] = {6, 12,8};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      } else {
        const int pins[] = {6,12};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, finalBrightness};
        updateCube(pins, 2, layers, states, 3);
      }
    }else if(zAngle > 270 && zAngle < 360){
      if (yAngle > 0 && yAngle < 90) {
        const int pins[] = {6, 8,5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, finalBrightness};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle == 90) {
        const int pins[] = {6, 8,5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle > 90 && yAngle < 180) {
        const int pins[] = {6, 8,5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {finalBrightness, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle == 180) {
        const int pins[] = {6, 5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {finalBrightness, finalBrightness, 255};
        updateCube(pins, 2, layers, states, 3);
      }else if (yAngle > 180 && yAngle < 270) {
        const int pins[] = {6, 2,5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {finalBrightness, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle > 270 && yAngle < 360) {
        const int pins[] = {6, 2,5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, finalBrightness};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle == 270) {
        const int pins[] = {6, 2,5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else {
        const int pins[] = {6,5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, finalBrightness};
        updateCube(pins, 2, layers, states, 3);
      }
    }else if(zAngle == 270){
      if (yAngle > 0 && yAngle < 90) {
        const int pins[] = {6, 8,12};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, finalBrightness};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle == 90) {
        const int pins[] = {6, 8,12};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle > 90 && yAngle < 180) {
        const int pins[] = {6, 8,12};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {finalBrightness, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle == 180) {
        const int pins[] = {6, 8};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {finalBrightness, finalBrightness, 255};
        updateCube(pins, 2, layers, states, 3);
      }else if (yAngle > 180 && yAngle < 270) {
        const int pins[] = {6, 8,5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {finalBrightness, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle > 270 && yAngle < 360) {
        const int pins[] = {6, 8,5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, finalBrightness};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle == 270) {
        const int pins[] = {6, 8,5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else {
        const int pins[] = {6,8};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, finalBrightness};
        updateCube(pins, 2, layers, states, 3);
      }
    }else{
      if (yAngle > 0 && yAngle < 90) {
      const int pins[] = {6, 2,5};
      const int layers[] = {layer1, layer2, layer3};
      const int states[] = {255, finalBrightness, finalBrightness};
      updateCube(pins, 3, layers, states, 3);
      }else if (yAngle == 90) {
        const int pins[] = {6, 2,5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle > 90 && yAngle < 180) {
        const int pins[] = {6, 2,5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {finalBrightness, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle == 180) {
        const int pins[] = {6, 2};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {finalBrightness, finalBrightness, 255};
        updateCube(pins, 2, layers, states, 3);
      }else if (yAngle > 180 && yAngle < 270) {
        const int pins[] = {6, 2,3};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {finalBrightness, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle > 270 && yAngle < 360) {
        const int pins[] = {6, 2,3};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, finalBrightness};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle == 270) {
        const int pins[] = {6, 2,3};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else {
        const int pins[] = {6,2};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, finalBrightness};
        updateCube(pins, 2, layers, states, 3);
      }
    }
  } else if (xAngle == 180) {
    if (yAngle > 0 && yAngle < 90) {
      const int pins[] = {6, 12};
      const int layers[] = {layer1, layer2, layer3};
      const int states[] = {255, finalBrightness, finalBrightness};
      updateCube(pins, 2, layers, states, 3);
    }else if (yAngle == 90) {
      const int pins[] = {6, 12};
      const int layers[] = {layer1, layer2, layer3};
      const int states[] = {255, finalBrightness, 255};
      updateCube(pins, 2, layers, states, 3);
    }else if (yAngle > 90 && yAngle < 180) {
      const int pins[] = {6, 12};
      const int layers[] = {layer1, layer2, layer3};
      const int states[] = {finalBrightness, finalBrightness, 255};
      updateCube(pins, 2, layers, states, 3);
    }else if (yAngle == 180) {
      const int pins[] = {6};
      const int layers[] = {layer1, layer2, layer3};
      const int states[] = {finalBrightness, finalBrightness, 255};
      updateCube(pins, 1, layers, states, 3);
    }else if (yAngle > 180 && yAngle < 270) {
      const int pins[] = {6, 4};
      const int layers[] = {layer1, layer2, layer3};
      const int states[] = {finalBrightness, finalBrightness, 255};
      updateCube(pins, 2, layers, states, 3);
    }else if (yAngle > 270 && yAngle < 360) {
      const int pins[] = {6, 4};
      const int layers[] = {layer1, layer2, layer3};
      const int states[] = {255, finalBrightness, finalBrightness};
      updateCube(pins, 2, layers, states, 3);
    }else if (yAngle == 270) {
      const int pins[] = {6, 4};
      const int layers[] = {layer1, layer2, layer3};
      const int states[] = {255, finalBrightness, 255};
      updateCube(pins, 2, layers, states, 3);
    }else {
      const int pins[] = {6};
      const int layers[] = {layer1, layer2, layer3};
      const int states[] = {255, finalBrightness, finalBrightness};
      updateCube(pins, 1, layers, states, 3);
    }
  } else if (xAngle < 270 && xAngle > 180) {
    if(zAngle > 0 && zAngle < 90){
      if (yAngle > 0 && yAngle < 90) {
        const int pins[] = {8, 6, 9};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, finalBrightness};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle == 90) {
        const int pins[] = {8, 6, 9};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle > 90 && yAngle < 180) {
        const int pins[] = {8, 6, 9};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {finalBrightness, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle == 180) {
        const int pins[] = {8, 6};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {finalBrightness, finalBrightness, 255};
        updateCube(pins, 2, layers, states, 3);
      }else if (yAngle > 180 && yAngle < 270) {
        const int pins[] = {8, 6, 5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {finalBrightness, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle == 270) {
        const int pins[] = {8, 6, 5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle > 270 && yAngle < 360) {
        const int pins[] = {8, 6, 5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, finalBrightness};
        updateCube(pins, 3, layers, states, 3);
      }else {
        const int pins[] = {8, 6};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, finalBrightness};
        updateCube(pins, 2, layers, states, 3);
      }
    }else if(zAngle == 90){
      if (yAngle > 0 && yAngle < 90) {
        const int pins[] = {8, 6, 9};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, finalBrightness};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle == 90) {
        const int pins[] = {8, 6, 9};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle > 90 && yAngle < 180) {
        const int pins[] = {8, 6, 9};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {finalBrightness, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle == 180) {
        const int pins[] = {8, 6};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {finalBrightness, finalBrightness, 255};
        updateCube(pins, 2, layers, states, 3);
      }else if (yAngle > 180 && yAngle < 270) {
        const int pins[] = {8, 6, 5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {finalBrightness, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle == 270) {
        const int pins[] = {8, 6, 5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle > 270 && yAngle < 360) {
        const int pins[] = {8, 6, 5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, finalBrightness};
        updateCube(pins, 3, layers, states, 3);
      }else {
        const int pins[] = {8, 6};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, finalBrightness};
        updateCube(pins, 2, layers, states, 3);
      }
    }else if(zAngle > 90 && zAngle < 180){
      if (yAngle > 0 && yAngle < 90) {
        const int pins[] = {8, 6, 9};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, finalBrightness};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle == 90) {
        const int pins[] = {8, 6, 9};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle > 90 && yAngle < 180) {
        const int pins[] = {8, 6, 9};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {finalBrightness, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle == 180) {
        const int pins[] = {8, 6};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {finalBrightness, finalBrightness, 255};
        updateCube(pins, 2, layers, states, 3);
      }else if (yAngle > 180 && yAngle < 270) {
        const int pins[] = {8, 6, 5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {finalBrightness, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle == 270) {
        const int pins[] = {8, 6, 5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle > 270 && yAngle < 360) {
        const int pins[] = {8, 6, 5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, finalBrightness};
        updateCube(pins, 3, layers, states, 3);
      }else {
        const int pins[] = {8, 6};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, finalBrightness};
        updateCube(pins, 2, layers, states, 3);
      }
    }else if(zAngle == 180){
      if (yAngle > 0 && yAngle < 90) {
        const int pins[] = {8, 6, 9};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, finalBrightness};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle == 90) {
        const int pins[] = {8, 6, 9};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle > 90 && yAngle < 180) {
        const int pins[] = {8, 6, 9};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {finalBrightness, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle == 180) {
        const int pins[] = {8, 6};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {finalBrightness, finalBrightness, 255};
        updateCube(pins, 2, layers, states, 3);
      }else if (yAngle > 180 && yAngle < 270) {
        const int pins[] = {8, 6, 5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {finalBrightness, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle == 270) {
        const int pins[] = {8, 6, 5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle > 270 && yAngle < 360) {
        const int pins[] = {8, 6, 5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, finalBrightness};
        updateCube(pins, 3, layers, states, 3);
      }else {
        const int pins[] = {8, 6};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, finalBrightness};
        updateCube(pins, 2, layers, states, 3);
      }
    }else if(zAngle > 180 && zAngle < 270){
      if (yAngle > 0 && yAngle < 90) {
        const int pins[] = {8, 6, 9};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, finalBrightness};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle == 90) {
        const int pins[] = {8, 6, 9};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle > 90 && yAngle < 180) {
        const int pins[] = {8, 6, 9};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {finalBrightness, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle == 180) {
        const int pins[] = {8, 6};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {finalBrightness, finalBrightness, 255};
        updateCube(pins, 2, layers, states, 3);
      }else if (yAngle > 180 && yAngle < 270) {
        const int pins[] = {8, 6, 5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {finalBrightness, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle == 270) {
        const int pins[] = {8, 6, 5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle > 270 && yAngle < 360) {
        const int pins[] = {8, 6, 5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, finalBrightness};
        updateCube(pins, 3, layers, states, 3);
      }else {
        const int pins[] = {8, 6};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, finalBrightness};
        updateCube(pins, 2, layers, states, 3);
      }
    }else if(zAngle == 270){
      if (yAngle > 0 && yAngle < 90) {
        const int pins[] = {8, 6, 9};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, finalBrightness};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle == 90) {
        const int pins[] = {8, 6, 9};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle > 90 && yAngle < 180) {
        const int pins[] = {8, 6, 9};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {finalBrightness, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle == 180) {
        const int pins[] = {8, 6};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {finalBrightness, finalBrightness, 255};
        updateCube(pins, 2, layers, states, 3);
      }else if (yAngle > 180 && yAngle < 270) {
        const int pins[] = {8, 6, 5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {finalBrightness, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle == 270) {
        const int pins[] = {8, 6, 5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle > 270 && yAngle < 360) {
        const int pins[] = {8, 6, 5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, finalBrightness};
        updateCube(pins, 3, layers, states, 3);
      }else {
        const int pins[] = {8, 6};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, finalBrightness};
        updateCube(pins, 2, layers, states, 3);
      }
    }else if(zAngle > 270 && zAngle < 360){
      if (yAngle > 0 && yAngle < 90) {
        const int pins[] = {8, 6, 9};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, finalBrightness};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle == 90) {
        const int pins[] = {8, 6, 9};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle > 90 && yAngle < 180) {
        const int pins[] = {8, 6, 9};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {finalBrightness, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle == 180) {
        const int pins[] = {8, 6};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {finalBrightness, finalBrightness, 255};
        updateCube(pins, 2, layers, states, 3);
      }else if (yAngle > 180 && yAngle < 270) {
        const int pins[] = {8, 6, 5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {finalBrightness, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle == 270) {
        const int pins[] = {8, 6, 5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle > 270 && yAngle < 360) {
        const int pins[] = {8, 6, 5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, finalBrightness};
        updateCube(pins, 3, layers, states, 3);
      }else {
        const int pins[] = {8, 6};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, finalBrightness};
        updateCube(pins, 2, layers, states, 3);
      }
    }else{
      if (yAngle > 0 && yAngle < 90) {
        const int pins[] = {8, 6, 9};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, finalBrightness};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle == 90) {
        const int pins[] = {8, 6, 9};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle > 90 && yAngle < 180) {
        const int pins[] = {8, 6, 9};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {finalBrightness, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle == 180) {
        const int pins[] = {8, 6};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {finalBrightness, finalBrightness, 255};
        updateCube(pins, 2, layers, states, 3);
      }else if (yAngle > 180 && yAngle < 270) {
        const int pins[] = {8, 6, 5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {finalBrightness, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle == 270) {
        const int pins[] = {8, 6, 5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle > 270 && yAngle < 360) {
        const int pins[] = {8, 6, 5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, finalBrightness};
        updateCube(pins, 3, layers, states, 3);
      }else {
        const int pins[] = {8, 6};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, finalBrightness};
        updateCube(pins, 2, layers, states, 3);
      }
    }
  } else if (xAngle == 270) {
    if (zAngle > 0 && zAngle < 90) {
      const int pins[] = {8, 9};
      const int layers[] = {layer1, layer2, layer3};
      const int states[] = {255, finalBrightness, finalBrightness};
      updateCube(pins, 2, layers, states, 3);
    }else if (zAngle == 90) {
      const int pins[] = {8, 12};
      const int layers[] = {layer1, layer2, layer3};
      const int states[] = {255, finalBrightness, finalBrightness};
      updateCube(pins, 2, layers, states, 3);
    }else if (zAngle > 90 && zAngle < 180) {
      const int pins[] = {8, 11};
      const int layers[] = {layer1, layer2, layer3};
      const int states[] = {255, finalBrightness, finalBrightness};
      updateCube(pins, 2, layers, states, 3);
    }else if (zAngle == 180) {
      const int pins[] = {8, 10};
      const int layers[] = {layer1, layer2, layer3};
      const int states[] = {255, finalBrightness, finalBrightness};
      updateCube(pins, 2, layers, states, 3);
    }else if (zAngle > 180 && zAngle < 270) {
      const int pins[] = {8, 7};
      const int layers[] = {layer1, layer2, layer3};
      const int states[] = {255, finalBrightness, finalBrightness};
      updateCube(pins, 2, layers, states, 3);
    }else if (zAngle > 270 && zAngle < 360) {
      const int pins[] = {8, 5};
      const int layers[] = {layer1, layer2, layer3};
      const int states[] = {255, finalBrightness, finalBrightness};
      updateCube(pins, 2, layers, states, 3);
    }else if (zAngle == 270) {
      const int pins[] = {8, 4};
      const int layers[] = {layer1, layer2, layer3};
      const int states[] = {255, finalBrightness, finalBrightness};
      updateCube(pins, 2, layers, states, 3);
    }else {
      const int pins[] = {8, 6};
      const int layers[] = {layer1, layer2, layer3};
      const int states[] = {255, finalBrightness, 255};
      updateCube(pins, 2, layers, states, 3);
    }
  } else if (xAngle > 270 && xAngle < 360) {
    if(zAngle > 0 && zAngle < 90){
      if (yAngle > 0 && yAngle < 90) {
        const int pins[] = {8, 6, 5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {finalBrightness, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle == 90) {
        const int pins[] = {8, 6, 5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle > 90 && yAngle < 180) {
        const int pins[] = {8, 6, 5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, finalBrightness};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle == 180) {
        const int pins[] = {8, 6};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {finalBrightness, finalBrightness, 255};
        updateCube(pins, 2, layers, states, 3);
      }else if (yAngle > 180 && yAngle < 270) {
        const int pins[] = {8, 6, 9};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, finalBrightness};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle == 270) {
        const int pins[] = {8, 6, 9};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle > 270 && yAngle < 360) {
        const int pins[] = {8, 6, 9};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {finalBrightness, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else {
        const int pins[] = {8, 6};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {finalBrightness, finalBrightness, 255};
        updateCube(pins, 2, layers, states, 3);
      }
    }else if(zAngle == 90){
      if (yAngle > 0 && yAngle < 90) {
        const int pins[] = {8, 6, 5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {finalBrightness, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle == 90) {
        const int pins[] = {8, 6, 5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle > 90 && yAngle < 180) {
        const int pins[] = {8, 6, 5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, finalBrightness};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle == 180) {
        const int pins[] = {8, 6};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {finalBrightness, finalBrightness, 255};
        updateCube(pins, 2, layers, states, 3);
      }else if (yAngle > 180 && yAngle < 270) {
        const int pins[] = {8, 6, 9};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, finalBrightness};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle == 270) {
        const int pins[] = {8, 6, 9};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle > 270 && yAngle < 360) {
        const int pins[] = {8, 6, 9};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {finalBrightness, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else {
        const int pins[] = {8, 6};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {finalBrightness, finalBrightness, 255};
        updateCube(pins, 2, layers, states, 3);
      }
    }else if(zAngle > 90 && zAngle < 180){
      if (yAngle > 0 && yAngle < 90) {
        const int pins[] = {8, 6, 5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {finalBrightness, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle == 90) {
        const int pins[] = {8, 6, 5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle > 90 && yAngle < 180) {
        const int pins[] = {8, 6, 5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, finalBrightness};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle == 180) {
        const int pins[] = {8, 6};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {finalBrightness, finalBrightness, 255};
        updateCube(pins, 2, layers, states, 3);
      }else if (yAngle > 180 && yAngle < 270) {
        const int pins[] = {8, 6, 9};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, finalBrightness};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle == 270) {
        const int pins[] = {8, 6, 9};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle > 270 && yAngle < 360) {
        const int pins[] = {8, 6, 9};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {finalBrightness, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else {
        const int pins[] = {8, 6};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {finalBrightness, finalBrightness, 255};
        updateCube(pins, 2, layers, states, 3);
      }
    }else if(zAngle == 180){
      if (yAngle > 0 && yAngle < 90) {
        const int pins[] = {8, 6, 5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {finalBrightness, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle == 90) {
        const int pins[] = {8, 6, 5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle > 90 && yAngle < 180) {
        const int pins[] = {8, 6, 5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, finalBrightness};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle == 180) {
        const int pins[] = {8, 6};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {finalBrightness, finalBrightness, 255};
        updateCube(pins, 2, layers, states, 3);
      }else if (yAngle > 180 && yAngle < 270) {
        const int pins[] = {8, 6, 9};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, finalBrightness};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle == 270) {
        const int pins[] = {8, 6, 9};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle > 270 && yAngle < 360) {
        const int pins[] = {8, 6, 9};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {finalBrightness, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else {
        const int pins[] = {8, 6};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {finalBrightness, finalBrightness, 255};
        updateCube(pins, 2, layers, states, 3);
      }
    }else if(zAngle > 180 && zAngle < 270){
      if (yAngle > 0 && yAngle < 90) {
        const int pins[] = {8, 6, 5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {finalBrightness, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle == 90) {
        const int pins[] = {8, 6, 5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle > 90 && yAngle < 180) {
        const int pins[] = {8, 6, 5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, finalBrightness};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle == 180) {
        const int pins[] = {8, 6};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {finalBrightness, finalBrightness, 255};
        updateCube(pins, 2, layers, states, 3);
      }else if (yAngle > 180 && yAngle < 270) {
        const int pins[] = {8, 6, 9};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, finalBrightness};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle == 270) {
        const int pins[] = {8, 6, 9};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle > 270 && yAngle < 360) {
        const int pins[] = {8, 6, 9};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {finalBrightness, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else {
        const int pins[] = {8, 6};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {finalBrightness, finalBrightness, 255};
        updateCube(pins, 2, layers, states, 3);
      }
    }else if(zAngle > 270 && zAngle < 360){
      if (yAngle > 0 && yAngle < 90) {
        const int pins[] = {8, 6, 5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {finalBrightness, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle == 90) {
        const int pins[] = {8, 6, 5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle > 90 && yAngle < 180) {
        const int pins[] = {8, 6, 5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, finalBrightness};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle == 180) {
        const int pins[] = {8, 6};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {finalBrightness, finalBrightness, 255};
        updateCube(pins, 2, layers, states, 3);
      }else if (yAngle > 180 && yAngle < 270) {
        const int pins[] = {8, 6, 9};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, finalBrightness};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle == 270) {
        const int pins[] = {8, 6, 9};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle > 270 && yAngle < 360) {
        const int pins[] = {8, 6, 9};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {finalBrightness, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else {
        const int pins[] = {8, 6};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {finalBrightness, finalBrightness, 255};
        updateCube(pins, 2, layers, states, 3);
      }
    }else if(zAngle == 270){
      if (yAngle > 0 && yAngle < 90) {
        const int pins[] = {8, 6, 5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {finalBrightness, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle == 90) {
        const int pins[] = {8, 6, 5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle > 90 && yAngle < 180) {
        const int pins[] = {8, 6, 5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, finalBrightness};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle == 180) {
        const int pins[] = {8, 6};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {finalBrightness, finalBrightness, 255};
        updateCube(pins, 2, layers, states, 3);
      }else if (yAngle > 180 && yAngle < 270) {
        const int pins[] = {8, 6, 9};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, finalBrightness};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle == 270) {
        const int pins[] = {8, 6, 9};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle > 270 && yAngle < 360) {
        const int pins[] = {8, 6, 9};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {finalBrightness, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else {
        const int pins[] = {8, 6};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {finalBrightness, finalBrightness, 255};
        updateCube(pins, 2, layers, states, 3);
      }
    }else{
      if (yAngle > 0 && yAngle < 90) {
        const int pins[] = {8, 6, 5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {finalBrightness, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle == 90) {
        const int pins[] = {8, 6, 5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle > 90 && yAngle < 180) {
        const int pins[] = {8, 6, 5};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, finalBrightness};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle == 180) {
        const int pins[] = {8, 6};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {finalBrightness, finalBrightness, 255};
        updateCube(pins, 2, layers, states, 3);
      }else if (yAngle > 180 && yAngle < 270) {
        const int pins[] = {8, 6, 9};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, finalBrightness};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle == 270) {
        const int pins[] = {8, 6, 9};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {255, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else if (yAngle > 270 && yAngle < 360) {
        const int pins[] = {8, 6, 9};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {finalBrightness, finalBrightness, 255};
        updateCube(pins, 3, layers, states, 3);
      }else {
        const int pins[] = {8, 6};
        const int layers[] = {layer1, layer2, layer3};
        const int states[] = {finalBrightness, finalBrightness, 255};
        updateCube(pins, 2, layers, states, 3);
      }
    }
  }
}

void resetCube() {
  const int pins[] = {6};
  const int layers[] = {layer1, layer2, layer3};
  const int states[] = {0, 0, 255};
  updateCube(pins, 1, layers, states, 3);
}
void updateCube(const int* pins, int pinCount, const int* layers, const int* states, int layerCount) {
  for (int i = 8; i > 1 ; i--) {
    analogWrite(i, 0);
  }
  analogWrite(13, 0);
  analogWrite(12, 0);
  
  for (int i = 0; i < pinCount; i++) {
    analogWrite(pins[i], 255);
  }

  for (int i = 0; i < layerCount; i++) {
    analogWrite(layers[i], states[i]);
  }
}
