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

    }
  }
}
