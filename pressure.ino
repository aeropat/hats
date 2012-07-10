void presPrint(){
  int pApxF = analogRead(presApxF);
  int pApxB = analogRead(presApxB);
  int pNacaF = analogRead(presNacaF);
  int pNacaB = analogRead(presNacaB);
  int pAm = analogRead(presAm);
  Serial.print(pApxF);
  Serial.print(",");
  Serial.print(pApxB);
  Serial.print(",");
  Serial.print(pNacaF);
  Serial.print(",");
  Serial.print(pNacaB);
  Serial.print(",");
  Serial.print(pAm);
  Serial.print(",");
//  Serial3.print(pApxF);
//  Serial3.print(",");
//  Serial3.print(pApxB);
//  Serial3.print(",");
//  Serial3.print(pNacaF);
//  Serial3.print(",");
//  Serial3.print(pNacaB);
//  Serial3.print(",");
//  Serial3.print(pAm);
//  Serial3.print(",");
}
