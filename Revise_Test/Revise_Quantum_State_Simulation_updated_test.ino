#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#define layer1 11
#define layer2 10
#define layer3 9

#define potX A3
#define potY A2
#define potZ A1

unsigned short int pins[] = {0,0,0};
unsigned short int states[] = {0,0,0};
unsigned short int layers[] = {layer1,layer2,layer3};

LiquidCrystal_I2C lcd(0x27,16,2);

const unsigned short int outputPins[] = {13, 12, layer1, layer2, layer3};
const unsigned short int inputPins[] = {potX, potY, potZ};

unsigned short int xVal = analogRead(potX);
unsigned short int yVal = analogRead(potY);
unsigned short int zVal = analogRead(potZ);

unsigned short int xAngle = map(xVal, 0, 1023, 360, 0);
unsigned short int yAngle = map(yVal, 0, 1023, 360, 0);
unsigned short int zAngle = map(zVal, 0, 1023, 360, 0);

float xRadians = radians(xAngle);
float yRadians = radians(yAngle);
float zRadians = radians(zAngle);

unsigned short int brightnessLayer1 = map(xAngle, 360, 0, 0, 85);
unsigned short int brightnessLayer2 = map(yAngle, 360, 0, 0, 85);
unsigned short int brightnessLayer3 = map(zAngle, 360, 0, 0, 85);

unsigned char finalBrightness = brightnessLayer1 + brightnessLayer2 + brightnessLayer3;

void setup() {
  for (int i = 8; i > 1; i--) {
    pinMode(i, OUTPUT);
  }

  // Initialize output pins
  for (int i = 0; i < sizeof(outputPins) / sizeof(outputPins[0]); i++) {
    pinMode(outputPins[i], OUTPUT);
    digitalWrite(outputPins[i], HIGH);
  }

  // Initialize input pins
  for (int i = 0; i < sizeof(inputPins) / sizeof(inputPins[0]); i++) {
    pinMode(inputPins[i], INPUT);
  }
}

void resetCube() {
  pins[0] = {6};
  states[0] = {0};
  states[1] = {0};
  states[2] = {255};
  updateCube(pins, 1, layers, states, 3);
}
void updateCube(unsigned short int* pins, int pinCount, unsigned short int* layers, unsigned short int* states, int layerCount) {
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

void displayAngles(int x, int y, int z) {
  lcd.clear();  // Clear the display before updating
  
  lcd.setCursor(0, 0); 
  lcd.print("X:"); 
  lcd.print(x); 
  lcd.print(" Y:"); 
  lcd.print(y); 
  
  lcd.setCursor(0, 1); 
  lcd.print("Z:"); 
  lcd.print(z);
}

void loop() {
  xVal = analogRead(potX);
  yVal = analogRead(potY);
  zVal = analogRead(potZ);

  xAngle = map(xVal, 0, 1023, 360, 0);
  yAngle = map(yVal, 0, 1023, 360, 0);
  zAngle = map(zVal, 0, 1023, 360, 0);

  displayAngles(xAngle, yAngle, zAngle);

  xRadians = radians(xAngle);
  yRadians = radians(yAngle);
  zRadians = radians(zAngle);

  brightnessLayer1 = map(xAngle, 360, 0, 0, 85);
  brightnessLayer2 = map(yAngle, 360, 0, 0, 85);
  brightnessLayer3 = map(zAngle, 360, 0, 0, 85);
  
  finalBrightness = brightnessLayer1 + brightnessLayer2 + brightnessLayer3;
  Serial.print("X:");
  Serial.print(xRadians);
  Serial.print(" Y:");
  Serial.print(yRadians);
  Serial.print(" Z: ");
  Serial.println(zRadians);

  if ((yAngle > 0 && yAngle < 90) && (zAngle > 0 && zAngle < 90)&&(xAngle > 0 && xAngle < 90)) {
          pins[0] = {6};
          pins[1] = {2};
          pins[2] = {3};
          states[0] = {finalBrightness};
          states[1] = {finalBrightness};
          states[2] = {255};
          updateCube(pins, 3, layers, states, 3);
  }else if ((yAngle == 90) && (zAngle > 0 && zAngle < 90) &&(xAngle > 0 && xAngle < 90)){
          pins[0] = {6};
          pins[1] = {2};
          pins[2] = {3};
          states[0] = {255};
          states[1] = {finalBrightness};
          states[2] = {255};
          updateCube(pins, 3, layers, states, 3);
  }else if ((yAngle > 90 && yAngle < 180)&& (zAngle > 0 && zAngle < 90)&&(xAngle > 0 && xAngle < 90)){
          pins[0] = {6};
          pins[1] = {2};
          pins[2] = {3};
          states[0] = {255};
          states[1] = {finalBrightness};
          states[2] = {finalBrightness};
          updateCube(pins, 3, layers, states, 3);
  }else if ((yAngle == 180)&& (zAngle > 0 && zAngle < 90)&&(xAngle > 0 && xAngle < 90)){
          pins[0] = {6};
          pins[1] = {3};
          states[0] = {255};
          states[1] = {finalBrightness};
          states[2] = {finalBrightness};
          updateCube(pins, 2, layers, states, 3);
  }else if ((yAngle > 180 && yAngle < 270)&& (zAngle > 0 && zAngle < 90)&&(xAngle > 0 && xAngle < 90)){
          pins[0] = 6; // Update the first element
          pins[1] = 4; // Update the second element
          pins[2] = 3;
          states[0] = 255;             // Update the first element
          states[1] = finalBrightness; // Update the second element
          states[2] = finalBrightness; // Update the third element
          updateCube(pins, 3, layers, states, 3);
  }else if ((yAngle > 270 && yAngle < 360)&& (zAngle > 0 && zAngle < 90)&&(xAngle > 0 && xAngle < 90)){
          pins[0] = 6; // Update the first element
          pins[1] = 4; // Update the second element
          pins[2] = 3;
          states[0] = finalBrightness;  // Update first element
          states[1] = finalBrightness;  // Update second element
          states[2] = 255;              // Update third element
          updateCube(pins, 3, layers, states, 3);
  }else if ((yAngle == 270)&& (zAngle > 0 && zAngle < 90)&&(xAngle > 0 && xAngle < 90)){
          pins[0] = 6; // Update the first element
          pins[1] = 4; // Update the second element
          pins[2] = 3;
          states[0] = 255;             // Update the first element
          states[1] = finalBrightness; // Update the second element
          states[2] = 255;
          updateCube(pins, 3, layers, states, 3);
  }else if ((yAngle == 0 || yAngle == 360) && (zAngle > 0 && zAngle < 90)&&(xAngle > 0 && xAngle < 90)){
          pins[0] = {6};
          pins[1] = {3};
          states[0] = finalBrightness; // Update the first element
          states[1] = finalBrightness; // Update the second element
          states[2] = 255;
          updateCube(pins, 2, layers, states, 3);
  }else if ((yAngle > 0 && yAngle < 90) &&(zAngle == 90)&&(xAngle > 0 && xAngle < 90)) {
        pins[0] = 6; // Update the first element
        pins[1] = 4; // Update the second element
        pins[2] = 3;
        states[0] = finalBrightness; // Update the first element
        states[1] = finalBrightness; // Update the second element
        states[2] = 255;
        updateCube(pins, 3, layers, states, 3);
  }else if ((yAngle == 90)&&(zAngle == 90)&&(xAngle > 0 && xAngle < 90)){
        pins[0] = 6; // Update the first element
        pins[1] = 4; // Update the second element
        pins[2] = 3;
        states[0] = 255;              // Update the first element
        states[1] = finalBrightness;  // Update the second element
        states[2] = 255; 
        updateCube(pins, 3, layers, states, 3);
  }else if ((yAngle > 90 && yAngle < 180)&&(zAngle == 90)&&(xAngle > 0 && xAngle < 90)){
        pins[0] = 6; // Update the first element
        pins[1] = 4; // Update the second element
        pins[2] = 3;
        states[0] = 255;              // Update the first element
        states[1] = finalBrightness;  // Update the second element
        states[2] = finalBrightness;
        updateCube(pins, 3, layers, states, 3);
  }else if ((yAngle == 180)&&(zAngle == 90)&&(xAngle > 0 && xAngle < 90)){
        pins[0] = 6; // Update the first element
        pins[1] = 4; // Update the second element
        states[0] = 255;             // Set the first element to 255
        states[1] = finalBrightness; // Set the second element to finalBrightness
        states[2] = finalBrightness;
        updateCube(pins, 2, layers, states, 3);
  }else if ((yAngle > 180 && yAngle < 270)&&(zAngle == 90)&&(xAngle > 0 && xAngle < 90)){
        pins[0] = 6;  // Set the first element to 6
        pins[1] = 4;  // Set the second element to 4
        pins[2] = 7;
        states[0] = 255;              // Set the first element to 255
        states[1] = finalBrightness;  // Set the second element to finalBrightness
        states[2] = finalBrightness;
        updateCube(pins, 3, layers, states, 3);
  }else if ((yAngle > 270 && yAngle < 360)&&(zAngle == 90)&&(xAngle > 0 && xAngle < 90)){
        pins[0] = 6;  // Set the first element to 6
        pins[1] = 4;  // Set the second element to 4
        pins[2] = 7;
        states[0] = finalBrightness;  // Set the first element to finalBrightness
        states[1] = finalBrightness;  // Set the second element to finalBrightness
        states[2] = 255; 
        updateCube(pins, 3, layers, states, 3);
  }else if ((yAngle == 270)&&(zAngle == 90)&&(xAngle > 0 && xAngle < 90)){
        pins[0] = 6;  // Set the first element to 6
        pins[1] = 4;  // Set the second element to 4
        pins[2] = 7;
        states[0] = 255;              // Set the first element to 255
        states[1] = finalBrightness;  // Set the second element to finalBrightness
        states[2] = 255;  
        updateCube(pins, 3, layers, states, 3);
  }else if ((yAngle == 360 || yAngle == 0) && (zAngle == 90)&&(xAngle > 0 && xAngle < 90)){
        pins[0] = 6; // Update the first element
        pins[1] = 4; // Update the second element
        states[0] = finalBrightness;  // Set the first element to finalBrightness
        states[1] = finalBrightness;  // Set the second element to finalBrightness
        states[2] = 255;  
        updateCube(pins, 2, layers, states, 3);
  }else if ((yAngle > 0 && yAngle < 90)&&(zAngle > 90 && zAngle < 180)&&(xAngle > 0 && xAngle < 90)) {
        // Update pins and states arrays
        pins[0] = 6;
        pins[1] = 4;
        pins[2] = 7;
        states[0] = finalBrightness;
        states[1] = finalBrightness;
        states[2] = 255;
        updateCube(pins, 3, layers, states, 3);
  }else if ((yAngle == 90)&&(zAngle > 90 && zAngle < 180)&&(xAngle > 0 && xAngle < 90)) {
        pins[0] = 6;
        pins[1] = 4;
        pins[2] = 7;
        states[0] = 255;
        states[1] = finalBrightness;
        states[2] = 255;
        updateCube(pins, 3, layers, states, 3);
  }else if ((yAngle > 90 && yAngle < 180)&&(zAngle > 90 && zAngle < 180)&&(xAngle > 0 && xAngle < 90)) {
        pins[0] = 6;
        pins[1] = 4;
        pins[2] = 7;
        states[0] = 255;
        states[1] = finalBrightness;
        states[2] = finalBrightness;
        updateCube(pins, 3, layers, states, 3);
  }else if ((yAngle == 180)&&(zAngle > 90 && zAngle < 180)&&(xAngle > 0 && xAngle < 90)) {
        pins[0] = 6;
        pins[1] = 7;
        states[0] = 255;
        states[1] = finalBrightness;
        states[2] = finalBrightness;
        updateCube(pins, 2, layers, states, 3);
  }else if ((yAngle > 180 && yAngle < 270)&&(zAngle > 90 && zAngle < 180)&&(xAngle > 0 && xAngle < 90)) {
        pins[0] = 6;
        pins[1] = 13;
        pins[2] = 7;
        states[0] = 255;
        states[1] = finalBrightness;
        states[2] = finalBrightness;
        updateCube(pins, 3, layers, states, 3);
  }else if ((yAngle > 270 && yAngle < 360)&&(zAngle > 90 && zAngle < 180)&&(xAngle > 0 && xAngle < 90)) {
        pins[0] = 6;
        pins[1] = 13;
        pins[2] = 7;
        states[0] = finalBrightness;
        states[1] = finalBrightness;
        states[2] = 255;
        updateCube(pins, 3, layers, states, 3);
  }else if ((yAngle == 270)&&(zAngle > 90 && zAngle < 180)&&(xAngle > 0 && xAngle < 90)) {
        pins[0] = 6;
        pins[1] = 13;
        pins[2] = 7;
        states[0] = 255;
        states[1] = finalBrightness;
        states[2] = 255;
        updateCube(pins, 3, layers, states, 3);
  }else if ((yAngle == 0 || yAngle == 360)&&(zAngle > 90 && zAngle < 180)&&(xAngle > 0 && xAngle < 90)){
        pins[0] = 6;
        pins[1] = 7;
        states[0] = finalBrightness;
        states[1] = finalBrightness;
        states[2] = 255;
        updateCube(pins, 2, layers, states, 3);
  }else if ((yAngle > 0 && yAngle < 90)&&(zAngle == 180)&&(xAngle > 0 && xAngle < 90)) {
          pins[0] = 6;
          pins[1] = 13;
          pins[2] = 7;
          states[0] = finalBrightness;
          states[1] = finalBrightness;
          states[2] = 255;
          updateCube(pins, 3, layers, states, 3);
  }else if ((yAngle == 90)&&(zAngle == 180)&&(xAngle > 0 && xAngle < 90)) {
          pins[0] = 6;
          pins[1] = 13;
          pins[2] = 7;
          states[0] = 255;
          states[1] = finalBrightness;
          states[2] = 255;
          updateCube(pins, 3, layers, states, 3);
  }else if ((yAngle > 90 && yAngle < 180)&&(zAngle == 180)&&(xAngle > 0 && xAngle < 90)) {
          pins[0] = 6;
          pins[1] = 13;
          pins[2] = 7;
          states[0] = 255;
          states[1] = finalBrightness;
          states[2] = finalBrightness;
          updateCube(pins, 3, layers, states, 3);
  }else if ((yAngle == 180)&&(zAngle == 180)&&(xAngle > 0 && xAngle < 90)) {
          pins[0] = 6;
          pins[1] = 13;
          states[0] = 255;
          states[1] = finalBrightness;
          states[2] = finalBrightness;
          updateCube(pins, 2, layers, states, 3);
  }else if ((yAngle > 180 && yAngle < 270)&&(zAngle == 180)&&(xAngle > 0 && xAngle < 90)) {
          pins[0] = 6;
          pins[1] = 13;
          pins[2] = 12;
          states[0] = 255;
          states[1] = finalBrightness;
          states[2] = finalBrightness;
          updateCube(pins, 3, layers, states, 3);
  }else if ((yAngle > 270 && yAngle < 360)&&(zAngle == 180)&&(xAngle > 0 && xAngle < 90)) {
          pins[0] = 6;
          pins[1] = 13;
          pins[2] = 12;
          states[0] = finalBrightness;
          states[1] = finalBrightness;
          states[2] = 255;
          updateCube(pins, 3, layers, states, 3);
  }else if ((yAngle == 270)&&(zAngle == 180)&&(xAngle > 0 && xAngle < 90)) {
          pins[0] = 6;
          pins[1] = 13;
          pins[2] = 12;
          states[0] = 255;
          states[1] = finalBrightness;
          states[2] = 255;
          updateCube(pins, 3, layers, states, 3);
  }else if ((yAngle == 0 || yAngle == 360)&&(zAngle == 180)&&(xAngle > 0 && xAngle < 90)) {
          pins[0] = 6;
          pins[1] = 13;
          states[0] = finalBrightness;
          states[1] = finalBrightness;
          states[2] = 255;
          updateCube(pins, 2, layers, states, 3);
  }else if ((yAngle > 0 && yAngle < 90)&&(zAngle > 180 && zAngle < 270)&&(xAngle > 0 && xAngle < 90)) {
          pins[0] = 6;
          pins[1] = 12;
          pins[2] = 13;
          states[0] = finalBrightness;
          states[1] = finalBrightness;
          states[2] = 255;
          updateCube(pins, 3, layers, states, 3);
  }else if ((yAngle == 90)&&(zAngle > 180 && zAngle < 270)&&(xAngle > 0 && xAngle < 90)) {
          pins[0] = 6;
          pins[1] = 12;
          pins[2] = 13;
          states[0] = 255;
          states[1] = finalBrightness;
          states[2] = 255;
          updateCube(pins, 3, layers, states, 3);
  }else if ((yAngle > 90 && yAngle < 180)&&(zAngle > 180 && zAngle < 270)&&(xAngle > 0 && xAngle < 90)) {
          pins[0] = 6;
          pins[1] = 12;
          pins[2] = 13;
          states[0] = 255;
          states[1] = finalBrightness;
          states[2] = finalBrightness;
          updateCube(pins, 3, layers, states, 3);
  }else if ((yAngle == 180)&&(zAngle > 180 && zAngle < 270)&&(xAngle > 0 && xAngle < 90)) {
          pins[0] = 6;
          pins[1] = 12;
          states[0] = 255;
          states[1] = finalBrightness;
          states[2] = finalBrightness;
          updateCube(pins, 2, layers, states, 3);
  }else if ((yAngle > 180 && yAngle < 270)&&(zAngle > 180 && zAngle < 270)&&(xAngle > 0 && xAngle < 90)) {
          pins[0] = 6;
          pins[1] = 12;
          pins[2] = 8;
          states[0] = 255;
          states[1] = finalBrightness;
          states[2] = finalBrightness;
          updateCube(pins, 3, layers, states, 3);
  }else if ((yAngle > 270 && yAngle < 360)&&(zAngle > 180 && zAngle < 270)&&(xAngle > 0 && xAngle < 90)) {
          pins[0] = 6;
          pins[1] = 12;
          pins[2] = 8;
          states[0] = finalBrightness;
          states[1] = finalBrightness;
          states[2] = 255;
          updateCube(pins, 3, layers, states, 3);
  }else if ((yAngle == 270)&&(zAngle > 180 && zAngle < 270)&&(xAngle > 0 && xAngle < 90)) {
          pins[0] = 6;
          pins[1] = 12;
          pins[2] = 8;
          states[0] = 255;
          states[1] = finalBrightness;
          states[2] = 255;
          updateCube(pins, 3, layers, states, 3);
  }else if ((yAngle == 0 || yAngle == 360)&&(zAngle > 180 && zAngle < 270)&&(xAngle > 0 && xAngle < 90)) {
          pins[0] = 6;
          pins[1] = 12;
          states[0] = finalBrightness;
          states[1] = finalBrightness;
          states[2] = 255;
          updateCube(pins, 2, layers, states, 3);
  }else if ((yAngle > 0 && yAngle < 90)&&(zAngle == 270)&&(xAngle > 0 && xAngle < 90)) {
          pins[0] = 6;
          pins[1] = 8;
          pins[2] = 12;
          states[0] = finalBrightness;
          states[1] = finalBrightness;
          states[2] = 255;
          updateCube(pins, 3, layers, states, 3);
  } else if ((yAngle == 90)&&(zAngle == 270)&&(xAngle > 0 && xAngle < 90)) {
          pins[0] = 6;
          pins[1] = 8;
          pins[2] = 12;
          states[0] = 255;
          states[1] = finalBrightness;
          states[2] = 255;
          updateCube(pins, 3, layers, states, 3);
  } else if ((yAngle > 90 && yAngle < 180)&&(zAngle == 270)&&(xAngle > 0 && xAngle < 90)) {
          pins[0] = 6;
          pins[1] = 8;
          pins[2] = 12;
          states[0] = 255;
          states[1] = finalBrightness;
          states[2] = finalBrightness;
          updateCube(pins, 3, layers, states, 3);
  } else if ((yAngle == 180)&&(zAngle == 270)&&(xAngle > 0 && xAngle < 90)) {
          pins[0] = 6;
          pins[1] = 8;
          states[0] = 255;
          states[1] = finalBrightness;
          states[2] = finalBrightness;
          updateCube(pins, 2, layers, states, 3);
  } else if ((yAngle > 180 && yAngle < 270)&&(zAngle == 270)&&(xAngle > 0 && xAngle < 90)) {
          pins[0] = 6;
          pins[1] = 8;
          pins[2] = 5;
          states[0] = 255;
          states[1] = finalBrightness;
          states[2] = finalBrightness;
          updateCube(pins, 3, layers, states, 3);
  } else if ((yAngle > 270 && yAngle < 360)&&(zAngle == 270)&&(xAngle > 0 && xAngle < 90)) {
          pins[0] = 6;
          pins[1] = 8;
          pins[2] = 5;
          states[0] = finalBrightness;
          states[1] = finalBrightness;
          states[2] = 255;
          updateCube(pins, 3, layers, states, 3);
  } else if ((yAngle == 270)&&(zAngle == 270)&&(xAngle > 0 && xAngle < 90)) {
          pins[0] = 6;
          pins[1] = 8;
          pins[2] = 5;
          states[0] = 255;
          states[1] = finalBrightness;
          states[2] = 255;
          updateCube(pins, 3, layers, states, 3);
  } else if ((yAngle == 0 || yAngle == 360)&&(zAngle == 270)&&(xAngle > 0 && xAngle < 90)) {
          pins[0] = 6;
          pins[1] = 8;
          states[0] = finalBrightness;
          states[1] = finalBrightness;
          states[2] = 255;
          updateCube(pins, 2, layers, states, 3);
  } else if ((yAngle > 0 && yAngle < 90)&&(zAngle > 270 && zAngle < 360)&&(xAngle > 0 && xAngle < 90)) {
          pins[0] = 6;
          pins[1] = 8;
          pins[2] = 5;
          states[0] = finalBrightness;
          states[1] = finalBrightness;
          states[2] = 255;
          updateCube(pins, 3, layers, states, 3);
  } else if ((yAngle == 90)&&(zAngle > 270 && zAngle < 360)&&(xAngle > 0 && xAngle < 90)) {
          pins[0] = 6;
          pins[1] = 8;
          pins[2] = 5;
          states[0] = 255;
          states[1] = finalBrightness;
          states[2] = 255;
          updateCube(pins, 3, layers, states, 3);
  } else if ((yAngle > 90 && yAngle < 180)&&(zAngle > 270 && zAngle < 360)&&(xAngle > 0 && xAngle < 90)) {
          pins[0] = 6;
          pins[1] = 8;
          pins[2] = 5;
          states[0] = 255;
          states[1] = finalBrightness;
          states[2] = finalBrightness;
          updateCube(pins, 3, layers, states, 3);
  } else if ((yAngle == 180)&&(zAngle > 270 && zAngle < 360)&&(xAngle > 0 && xAngle < 90)) {
          pins[0] = 6;
          pins[1] = 5;
          states[0] = 255;
          states[1] = finalBrightness;
          states[2] = finalBrightness;
          updateCube(pins, 2, layers, states, 3);
  } else if ((yAngle > 180 && yAngle < 270)&&(zAngle > 270 && zAngle < 360)&&(xAngle > 0 && xAngle < 90)) {
          pins[0] = 6;
          pins[1] = 2;
          pins[2] = 5;
          states[0] = 255;
          states[1] = finalBrightness;
          states[2] = finalBrightness;
          updateCube(pins, 3, layers, states, 3);
  } else if ((yAngle > 270 && yAngle < 360)&&(zAngle > 270 && zAngle < 360)&&(xAngle > 0 && xAngle < 90)) {
          pins[0] = 6;
          pins[1] = 2;
          pins[2] = 5;
          states[0] = finalBrightness;
          states[1] = finalBrightness;
          states[2] = 255;
          updateCube(pins, 3, layers, states, 3);
  } else if ((yAngle == 270)&&(zAngle > 270 && zAngle < 360)&&(xAngle > 0 && xAngle < 90)) {
          pins[0] = 6;
          pins[1] = 2;
          pins[2] = 5;
          states[0] = 255;
          states[1] = finalBrightness;
          states[2] = 255;
          updateCube(pins, 3, layers, states, 3);
  } else if ((yAngle == 0 || yAngle == 360)&&(zAngle > 270 && zAngle < 360)&&(xAngle > 0 && xAngle < 90)) {
          pins[0] = 6;
          pins[1] = 5;
          states[0] = finalBrightness;
          states[1] = finalBrightness;
          states[2] = 255;
          updateCube(pins, 2, layers, states, 3);
  }else if ((yAngle > 0 && yAngle < 90)&&(zAngle == 0 || zAngle == 360)&&(xAngle > 0 && xAngle < 90)) {
          pins[0] = 6;
          pins[1] = 2;
          pins[2] = 5;
          states[0] = finalBrightness;
          states[1] = finalBrightness;
          states[2] = 255;
          updateCube(pins, 3, layers, states, 3);
  } else if ((yAngle == 90)&&(zAngle == 0 || zAngle == 360)&&(xAngle > 0 && xAngle < 90)) {
          pins[0] = 6;
          pins[1] = 2;
          pins[2] = 5;
          states[0] = 255;
          states[1] = finalBrightness;
          states[2] = 255;
          updateCube(pins, 3, layers, states, 3);
  } else if ((yAngle > 90 && yAngle < 180)&&(zAngle == 0 || zAngle == 360)&&(xAngle > 0 && xAngle < 90)) {
          pins[0] = 6;
          pins[1] = 2;
          pins[2] = 5;
          states[0] = 255;
          states[1] = finalBrightness;
          states[2] = finalBrightness;
          updateCube(pins, 3, layers, states, 3);
  } else if ((yAngle == 180)&&(zAngle == 0 || zAngle == 360)&&(xAngle > 0 && xAngle < 90)) {
          pins[0] = 6;
          pins[1] = 2;
          states[0] = 255;
          states[1] = finalBrightness;
          states[2] = finalBrightness;
          updateCube(pins, 2, layers, states, 3);
  } else if ((yAngle > 180 && yAngle < 270)&&(zAngle == 0 || zAngle == 360)&&(xAngle > 0 && xAngle < 90)) {
          pins[0] = 6;
          pins[1] = 2;
          pins[2] = 3;
          states[0] = 255;
          states[1] = finalBrightness;
          states[2] = finalBrightness;
          updateCube(pins, 3, layers, states, 3);
  } else if ((yAngle > 270 && yAngle < 360)&&(zAngle == 0 || zAngle == 360)&&(xAngle > 0 && xAngle < 90)) {
          pins[0] = 6;
          pins[1] = 2;
          pins[2] = 3;
          states[0] = finalBrightness;
          states[1] = finalBrightness;
          states[2] = 255;
          updateCube(pins, 3, layers, states, 3);
  } else if ((yAngle == 270)&&(zAngle == 0 || zAngle == 360)&&(xAngle > 0 && xAngle < 90)) {
          pins[0] = 6;
          pins[1] = 2;
          pins[2] = 3;
          states[0] = 255;
          states[1] = finalBrightness;
          states[2] = 255;
          updateCube(pins, 3, layers, states, 3);
  } else if ((yAngle == 0 || yAngle == 360)&&(zAngle == 0 || zAngle == 360)&&(xAngle > 0 && xAngle < 90)) {
          pins[0] = 6;
          pins[1] = 2;
          states[0] = finalBrightness;
          states[1] = finalBrightness;
          states[2] = 255;
          updateCube(pins, 2, layers, states, 3);
  }else if ((zAngle > 0 && zAngle < 90)&&(xAngle == 90 && yAngle == 0)) {
        pins[0] = 6;
        pins[1] = 3;
        states[0] = 255;
        states[1] = finalBrightness;
        states[2] = 255;
        updateCube(pins, 2, layers, states, 3);
  } else if ((zAngle == 90)&&(xAngle == 90 && yAngle == 0)) {
        pins[0] = 6;
        pins[1] = 4;
        states[0] = 255;
        states[1] = finalBrightness;
        states[2] = 255;
        updateCube(pins, 2, layers, states, 3);
  } else if ((zAngle > 90 && zAngle < 180)&&(xAngle == 90 && yAngle == 0)) {
        pins[0] = 6;
        pins[1] = 7;
        states[0] = 255;
        states[1] = finalBrightness;
        states[2] = 255;
        updateCube(pins, 2, layers, states, 3);
  } else if ((zAngle == 180)&&(xAngle == 90 && yAngle == 0)) {
        pins[0] = 6;
        pins[1] = 13;
        states[0] = 255;
        states[1] = finalBrightness;
        states[2] = 255;
        updateCube(pins, 2, layers, states, 3);
  } else if ((zAngle > 180 && zAngle < 270)&&(xAngle == 90 && yAngle == 0)) {
        pins[0] = 6;
        pins[1] = 12;
        states[0] = 255;
        states[1] = finalBrightness;
        states[2] = 255;
        updateCube(pins, 2, layers, states, 3);
  } else if ((zAngle > 270 && zAngle < 360)&&(xAngle == 90 && yAngle == 0)) {
        pins[0] = 6;
        pins[1] = 5;
        states[0] = 255;
        states[1] = finalBrightness;
        states[2] = 255;
        updateCube(pins, 2, layers, states, 3);
  } else if ((zAngle == 270)&&(xAngle == 90 && yAngle == 0)) {
        pins[0] = 6;
        pins[1] = 8;
        states[0] = 255;
        states[1] = finalBrightness;
        states[2] = 255;
        updateCube(pins, 2, layers, states, 3);
  } else if ((zAngle == 0 || zAngle == 360)&&(xAngle == 90 && yAngle == 0)) {
        pins[0] = 6;
        pins[1] = 2;
        states[0] = 255;
        states[1] = finalBrightness;
        states[2] = 255;
        updateCube(pins, 2, layers, states, 3);
  }else if (((yAngle > 0 && yAngle < 90)&&(xAngle == 180&& zAngle == 0)) || ((yAngle > 180 && yAngle < 270))) {
        pins[0] = 6;
        pins[1] = 4;
        states[0] = 255;
        states[1] = finalBrightness;
        states[2] = finalBrightness;
        updateCube(pins, 2, layers, states, 3);
  } else if (((yAngle == 90)&&(xAngle == 180&& zAngle == 0)) || ((yAngle == 270)&&(xAngle == 0&& zAngle == 0))) {
        pins[0] = 6;
        pins[1] = 4;
        states[0] = 255;
        states[1] = finalBrightness;
        states[2] = 255;
        updateCube(pins, 2, layers, states, 3);
  } else if (((yAngle > 90 && yAngle < 180)&&(xAngle == 180&& zAngle == 0)) || ((yAngle > 270 && yAngle < 360)&&(xAngle == 0&& zAngle == 0))) {
        pins[0] = 6;
        pins[1] = 4;
        states[0] = finalBrightness;
        states[1] = finalBrightness;
        states[2] = 255;
        updateCube(pins, 2, layers, states, 3);
  } else if (((yAngle == 180)&&(xAngle == 180&& zAngle == 0)) || ((yAngle == 0 || yAngle == 360)&&(xAngle == 0&& zAngle == 0))) {
        pins[0] = 6;
        states[0] = finalBrightness;
        states[1] = finalBrightness;
        states[2] = 255;
        updateCube(pins, 1, layers, states, 3);
  } else if (((yAngle > 180 && yAngle < 270)&&(xAngle == 180&& zAngle == 0)) || ((yAngle > 0 && yAngle < 90)&&(xAngle == 0&& zAngle == 0))) {
        pins[0] = 6;
        pins[1] = 8;
        states[0] = finalBrightness;
        states[1] = finalBrightness;
        states[2] = 255;
        updateCube(pins, 2, layers, states, 3);
  } else if (((yAngle > 270 && yAngle < 360)&&(xAngle == 180&& zAngle == 0)) || ((yAngle > 90 && yAngle < 180)&&(xAngle == 0&& zAngle == 0))) {
        pins[0] = 6;
        pins[1] = 8;
        states[0] = 255;
        states[1] = finalBrightness;
        states[2] = finalBrightness;
        updateCube(pins, 2, layers, states, 3);
  } else if (((yAngle == 270)&&(xAngle == 180&& zAngle == 0)) || ((yAngle == 90)&&(xAngle == 0&& zAngle == 0))) {
        pins[0] = 6;
        pins[1] = 8;
        states[0] = 255;
        states[1] = finalBrightness;
        states[2] = 255;
        updateCube(pins, 2, layers, states, 3);
  } else if(((yAngle == 0 || yAngle == 360)&&(xAngle == 180&& zAngle == 0))|| ((yAngle == 180)&&(xAngle == 0&& zAngle == 0))) {
        pins[0] = 6;
        states[0] = 255;
        states[1] = finalBrightness;
        states[2] = finalBrightness;
        updateCube(pins, 1, layers, states, 3);
  }else{
    resetCube();
  }
  Serial.print("Brightness: ");
  Serial.println(finalBrightness);
  delay(100);
}