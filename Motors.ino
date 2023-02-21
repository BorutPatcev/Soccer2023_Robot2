void motorsOn() {
  digitalWrite(24,HIGH);
  digitalWrite(25,HIGH);
  digitalWrite(26,HIGH);
  digitalWrite(27,HIGH);
}

void motorsOff() {
  digitalWrite(24,LOW);
  digitalWrite(25,LOW);
  digitalWrite(26,LOW);
  digitalWrite(27,LOW);
}

void motorSetSpeed(int n, int speedMotor) {
  speedMotor = int(speedMotor * 2.55);
  if (speedMotor < 0) {
    digitalWrite(motorPins[n][2], 1 - reverseMotor[n]);
  } else {
    digitalWrite(motorPins[n][2], 0 + reverseMotor[n]);
  }
  analogWrite(motorPins[n][1], abs(speedMotor) - int((speedLevel[n]*abs(speedMotor)/10)));
}

void go(float speedMotor, float angle, float rotation, int speedLimit = maxSpeed) {
  
  angle += 135;
  angle *= -1;
  angle = toRad(angle);
  float si = sin(angle);
  float co = cos(angle);
  float motorSpeed[4];
  
  motorSpeed[0] = -speedMotor * si - rotation;
  motorSpeed[1] =  speedMotor * co - rotation;
  motorSpeed[2] =  speedMotor * si - rotation;
  motorSpeed[3] = -speedMotor * co - rotation;

  float maxMotorSpeed = abs(motorSpeed[0]);
  for (int i = 0; i < 4; i++) {
    if (abs(motorSpeed[i]) > maxMotorSpeed) 
      maxMotorSpeed = abs(motorSpeed[i]);
  }
  for (int i = 0; i < 4; i++) {

    /*Serial.print(int(motorSpeed[i]*2.55));
    Serial.print("  ");
    Serial.print(speedLimit);
    Serial.print("  ");
    Serial.println(maxMotorSpeed);

    Bluetooth.print(int(motorSpeed[i]*2.55));
    Bluetooth.print("  ");
    Bluetooth.print(speedLimit);
    Bluetooth.print("  ");
    Bluetooth.println(maxMotorSpeed);*/
    
    if (speedLimit == 0)
      motorSetSpeed(i, 0);
    else if (maxMotorSpeed > speedLimit)
      motorSetSpeed(i, motorSpeed[i] / maxMotorSpeed * speedLimit);
    else
      motorSetSpeed(i, motorSpeed[i]);
  }
}