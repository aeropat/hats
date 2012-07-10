//   Best Performance: both pins have interrupt capability
//   MEGA Interupt Pins - 2,3,18,19,20,21

long positionLeft  = -999;
long positionRight = -999;

void encoderPrint() {
  long newLeft, newRight;
  newLeft = motor1.read() / 140;
  newRight = motor2.read() / 140;
  if (newLeft != positionLeft || newRight != positionRight) {
    Serial.print(",");
    Serial.print(newLeft);
    Serial.print(",");
    Serial.print(newRight);
//    Serial3.print(",");
//    Serial3.print(newLeft);
//    Serial3.print(",");
//    Serial3.print(newRight);
    positionLeft = newLeft;
    positionRight = newRight; }
  }
