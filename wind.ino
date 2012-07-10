void windPrint() {
  int rawX = analogRead(windX);
  int rawY = analogRead(windY);
  int rawZ = analogRead(windZ);
  int rawAll = analogRead(windAll);
  Serial.print(rawX);
  Serial.print(",");
  Serial.print(rawY);
  Serial.print(",");
  Serial.print(rawZ);
  Serial.print(",");
  Serial.print(rawAll);
//  Serial3.print(rawX);
//  Serial3.print(",");
//  Serial3.print(rawY);
//  Serial3.print(",");
//  Serial3.print(rawZ);
//  Serial3.print(",");
//  Serial3.print(rawAll);
}

