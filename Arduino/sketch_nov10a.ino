#include <Adafruit_CircuitPlayground.h>

#define DELAY_AMOUNT 100
#define MEASURE_EVERY 600

int value, loopcounter, r, g, b;
bool light;
float tempF;

void setup() {
  // put your setup code here, to run once:
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  pinMode(12, OUTPUT);
  digitalWrite(12,LOW);
  Serial.begin(57600);
  //Serial.println("Circuit Playground test!");
  loopcounter = 1;
  light = false;
  CircuitPlayground.begin();
}

void loop() {
  String input;
  int inputVal;
  // put your main code here, to run repeatedly:

  if(loopcounter == MEASURE_EVERY){
    digitalWrite(13, HIGH);
    if(light){
      value = CircuitPlayground.lightSensor();
      Serial.print("Light Sensor: ");
      Serial.println(value);
    }
    //delay(2500);
      /************* TEST SLIDE SWITCH */
    if (CircuitPlayground.slideSwitch()) {
      Serial.println("Slide to the left");
    } else {
      Serial.println("Slide to the right");
      CircuitPlayground.playTone(500 + 5 * 500, 40);
    }
      /************* TEST SOUND SENSOR */
    Serial.print("Sound sensor: ");
    Serial.println(CircuitPlayground.mic.soundPressureLevel(10));
  
    /************* TEST ACCEL */
    // Display the results (acceleration is measured in m/s*s)
    //Serial.print("X: "); Serial.print(CircuitPlayground.motionX());
    //Serial.print(" \tY: "); Serial.print(CircuitPlayground.motionY());
    //Serial.print(" \tZ: "); Serial.print(CircuitPlayground.motionZ());
    //Serial.println(" m/s^2");
 
    //Serial.print("Capsense #3: "); 
    //Serial.println(CircuitPlayground.readCap(3,100));
    //if(!light){
    tempF = CircuitPlayground.temperatureF();
    Serial.print("tempF: ");
    Serial.println(tempF);
    if(tempF < 60.0){
      r = 0;
      g = 0;
      b = 255;
    } else if(tempF < 90.0) {
      r = 0;
      g = 255;
      b = 0;
    } else {
      r = 255;
      g = 0;
      b = 0;
    }
    for( int j = 0; j < 10; j++) {
      CircuitPlayground.setPixelColor(j, r, g, b);
    }
    //}

    digitalWrite(13, LOW);
    //delay(DELAY_AMOUNT);

    loopcounter = 0;
    //light ^= true;
  }

  if (Serial.available() > 0){
    input = Serial.readStringUntil('\n');
    //Serial.println(input);
    inputVal = getIntVal(input);
    flash(inputVal); //Converts Serial message into a number
  }

  loopcounter++;
  delay(DELAY_AMOUNT);
}

int getIntVal(String strVal){
  int myVal;
  if(strVal == "0"){
    myVal = 0;
  } else if(strVal == "1") {
    myVal = 1;
  } else if(strVal == "2") {
    myVal = 2;
  } else if(strVal == "3") {
    myVal = 3;
  } else if(strVal == "4") {
    myVal = 4;
  } else if(strVal == "5") {
    myVal = 5;
  } else if(strVal == "6") {
    myVal = 6;
  } else if(strVal == "7") {
    myVal = 7;
  } else if(strVal == "8") {
    myVal = 8;
  } else if(strVal == "9") {
    myVal = 9;
  }
  return myVal;
}


void flash(int repetitions){
  bool initLight;
  initLight = light;
  
  if(repetitions > 9){
    repetitions = repetitions / 10;
  }
  //Serial.println(repetitions);
  if(repetitions < 4){
    for (int i = 0; i < repetitions; i ++){
      CircuitPlayground.setPixelColor(3, CircuitPlayground.colorWheel(25 * 3));
      delay(1000);
      CircuitPlayground.clearPixels();
      delay(500);
    }
  } else {
    if(repetitions == 4){
      //CircuitPlayground.setPixelColor(6, 0, 0, 255);
      //CircuitPlayground.setPixelColor(7, 0, 0, 255);
      //CircuitPlayground.setPixelColor(8, 0, 0, 255);
    } else if(repetitions == 5){
      //CircuitPlayground.setPixelColor(6, 0, 255, 0);
      //CircuitPlayground.setPixelColor(7, 0, 255, 0);
      //CircuitPlayground.setPixelColor(8, 0, 255, 0);
    } else if(repetitions == 6){
      //CircuitPlayground.setPixelColor(6, 255, 0, 0);
      //CircuitPlayground.setPixelColor(7, 255, 0, 0);
      //CircuitPlayground.setPixelColor(8, 255, 0, 0);
    } else if(repetitions == 7){
      r = rand() % 256;
      g = rand() % 256;
      b = rand() % 256;
      //for( int j = 0; j < 10; j++) {
        //CircuitPlayground.setPixelColor(j, r, g, b);
      //}
      digitalWrite(12, HIGH);
      digitalWrite(13, HIGH);
      light = true;
      
    } else if(repetitions == 8){
      digitalWrite(12, LOW);
      digitalWrite(13, LOW);
      light = false;
    } else {
      
      CircuitPlayground.clearPixels();
    }
    if(initLight != light){
      //Serial.println("One hour delay");
      //delay(500 * 1 * 1);
      //delay(1000 * 3600);
    }
  }
}
