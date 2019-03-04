#include <Adafruit_CircuitPlayground.h>

#define DELAY_AMOUNT 100
//#define MEASURE_EVERY 15000

int value, loopcounter, r, g, b;
int light = 0;
float tempF;
int lasttimeChecked = 0;
int delayTime = 60000;

void setup() {
  // put your setup code here, to run once:
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  pinMode(12, OUTPUT);
  digitalWrite(12,LOW);
  Serial.begin(57600);
  //Serial.println("Circuit Playground test!");
  loopcounter = 1;
  light = 0;
  CircuitPlayground.begin();
}

void loop() {
  String input;
  int inputVal, slideState;
  float soundPressureLevel;
  // put your main code here, to run repeatedly:
  unsigned long curTime = millis();
  
  if(curTime > (lasttimeChecked + delayTime)){
    digitalWrite(13, HIGH);

    value = CircuitPlayground.lightSensor();
    //Serial.print("Light Sensor: ");
    //Serial.println(value);


      /************* TEST SLIDE SWITCH */
      slideState = CircuitPlayground.slideSwitch();
    if (slideState) {
      //Serial.println("Slide to the left");
    } else {
      //Serial.println("Slide to the right");
      CircuitPlayground.playTone(500 + 5 * 500, 40);
    }
      /************* TEST SOUND SENSOR */
    //Serial.print("Sound sensor: ");
    soundPressureLevel = CircuitPlayground.mic.soundPressureLevel(10);
    //Serial.println(soundPressureLevel);
  
    /************* TEST ACCEL */
    // Display the results (acceleration is measured in m/s*s)
    //Serial.print("X: "); Serial.print(CircuitPlayground.motionX());
    //Serial.print(" \tY: "); Serial.print(CircuitPlayground.motionY());
    //Serial.print(" \tZ: "); Serial.print(CircuitPlayground.motionZ());
    //Serial.println(" m/s^2");
 
    //Serial.print("Capsense #3: "); 
    //Serial.println(CircuitPlayground.readCap(3,100));

    tempF = CircuitPlayground.temperatureF();
    //Serial.print("tempF: ");
    //Serial.println(tempF);
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

    serialTransfer(tempF, soundPressureLevel, value, slideState, light);
    
    digitalWrite(13, LOW);

    lasttimeChecked = curTime;

  }

  if (Serial.available() > 0){
    input = Serial.readStringUntil('\n');
    //Serial.println(input);
    inputVal = getIntVal(input);
    flash(inputVal); //Converts Serial message into a number
  }

  loopcounter++;
  //delay(DELAY_AMOUNT);
}
