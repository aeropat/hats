void windPrint() {
  int rawX = analogRead(windX);
  int rawY = analogRead(windY);
  int rawZ = analogRead(windZ);
  int rawAll = analogRead(windAll);
  Serial.print(rawX);
  Serial.print(" ");
  Serial.print(rawY);
  Serial.print(" ");
  Serial.print(rawZ);
  Serial.print(" ");
  Serial.print(rawAll);
  Serial.print(" ");
}

