void strainPrint(){
    float sApx1 = analogRead(strainApx1);
    float sApx2 = analogRead(strainApx2);
    float sNaca1= analogRead(strainNaca1);
    float sNaca2 = analogRead(strainNaca2);
    Serial.print(sApx1);
    Serial.print(",");
    Serial.print(sApx2);
    Serial.print(",");
    Serial.print(sNaca1);
    Serial.print(",");
    Serial.print(sNaca2);
    Serial.print(",");
//    Serial3.print(sApx1);
//    Serial3.print(",");
//    Serial3.print(sApx2);
//    Serial3.print(",");
//    Serial3.print(sNaca1);
//    Serial3.print(",");
//    Serial3.print(sNaca2);
//    Serial3.print(",");
  }
