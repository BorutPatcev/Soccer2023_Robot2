void Setup() {
  
  Wire.begin();
  Serial.begin(115200);
  Bluetooth.begin(9600);
  Camera.begin(115200);
  delay(500);

  Serial.println("Communications....OK");
  Serial.println();
  Bluetooth.println("Communications....OK");
  Bluetooth.println();
  
  setupMotors();
  setupLineSensors();
  setupButtonsSwitches();
  setupLidars();

  compass.add(false);
  Serial.println("IMU....OK");
  Bluetooth.println("IMU....OK");

}

void setupMotors() {

  // Motor 1
  pinMode(27,OUTPUT); //SLP
  pinMode(8,OUTPUT);  //PWM
  pinMode(7,OUTPUT);  //DIR

  // Motor 2
  pinMode(24,OUTPUT); //SLP
  pinMode(0,OUTPUT);  //PWM
  pinMode(1,OUTPUT);  //DIR

  // Motor 3
  pinMode(25,OUTPUT); //SLP
  pinMode(2,OUTPUT);  //PWM
  pinMode(3,OUTPUT);  //DIR

  // Motor 4
  pinMode(26,OUTPUT); //SLP
  pinMode(4,OUTPUT);  //PWM
  pinMode(5,OUTPUT);  //DIR

  Serial.println("Motors....OK");
  Bluetooth.println("Motors....OK");
  
}

void setupLineSensors() {

  pinMode(A16, INPUT);  // 1-16
  pinMode(A17, INPUT);  // 17-32
  pinMode(30,OUTPUT);
  pinMode(31,OUTPUT);
  pinMode(32,OUTPUT);
  pinMode(33,OUTPUT);

  Serial.println("Line sensors....OK");
  Bluetooth.println("Line sensors....OK");
  
}

void setupButtonsSwitches() {

  pinMode(16, INPUT);  // BUT1
  pinMode(39, INPUT);  // BUT2
  pinMode(38, INPUT);  // BUT3
  pinMode(37, INPUT);  // BUT4

  Serial.println("Buttons....OK");
  Bluetooth.println("Buttons....OK");
  
  pinMode(23, INPUT);  // SWC1
  pinMode(22, INPUT);  // SWC2
  pinMode(17, INPUT);  // SWC3

  Serial.println("Swithes....OK");
  Bluetooth.println("Swithes....OK");
  
}

void setupLidars() {

  Serial.print("Lidars....OK  ");
  Bluetooth.print("Lidars....OK  ");
  
  for (int i = 0; i < 8; ++i) {
    selectLidar(i);
    lidar.setTimeout(500);
    if (lidar.init()) {
      Serial.print("+ ");
      Bluetooth.print("+ ");
      lidar.setDistanceMode(VL53L1X::Short);
      lidar.setMeasurementTimingBudget(50000);
      lidar.startContinuous(50);
    } else {
      Serial.print("- ");
      Bluetooth.print("- ");
    }
  }

  Serial.println();
  Bluetooth.println();
  
}
