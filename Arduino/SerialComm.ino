void serialTransfer(float Temperature, float SoundLevel, int LightLevel, int SlideState, int LightStatus){
  Serial.print(Temperature);
  Serial.print(",");
  Serial.print(SoundLevel);
  Serial.print(",");
  Serial.print(LightLevel);
  Serial.print(",");
  Serial.print(SlideState);
  Serial.print(",");
  Serial.println(LightStatus);

  //return true;
}
