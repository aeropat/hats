void pressPrint() {
  int pressure = analogRead(presAm);
  Serial.print(pressure);
  Serial.print(" ");
  Serial3.print(pressure);
  Serial3.print(" ");
}

