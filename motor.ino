void motorControl() {
  analogWrite(motorPin, runValue); //makes sure motor is stopped
  if (Serial3.available()>0){
    String readString;
    while (Serial3.available()>0) {  //if there's an input via keyboard
      keyboardInput = Serial3.read();
      readString += keyboardInput;
    }
    if (readString.length()>0){
      int enteredVal;
      char carray[6];
      readString.toCharArray(carray, sizeof(carray));
      enteredVal = atoi(carray);    // the above steps turned the character entry into an int val        
      runValue = convertPercent(enteredVal);  //converts from percent, to analog motor run val
    }
  }
}
// <Maps 100-199 entry (percent) to 0-255 analog value
int convertPercent(int pVal){
  int runVal = map(pVal, 0, 9, 0, 255);
  runVal = constrain(runVal, 0, 255);
  return runVal;  
}
