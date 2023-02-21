void readAll() {

  readLineSensors();
  //readLidars();
  readSwitches();
  readButtons();
  readCamera();
  
}

void readLineSensors() {

  int counter = 0;
  bool found = false;
  
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      for (int k = 0; k < 2; k++) {
        for (int l = 0; l < 2; l++) {
          
          digitalWrite(32,i);
          digitalWrite(33,j);
          digitalWrite(30,k);
          digitalWrite(31,l);

          delay(1);

          lin[counter] = analogRead(A16);
          lin[counter + 16] = analogRead(A17);

          if (lin[counter] > treshold || lin[counter + 16] > treshold) found = true;
          counter++;
          
        }
      }
    }
  }
  if (found) {
    line = true;
  } else {
    line = false;
  }
  //Bluetooth.println(lin[0]);

}

void readLidars() {

  for (int i = 0; i < 8; i++) {
    selectLidar(i);
    lid[i] = lidar.read();
  }
  
}

void readSwitches() {
  
  swc[0] = digitalRead(23);
  swc[1] = digitalRead(22);
  swc[2] = digitalRead(17);
  
}

void readButtons() {
  but[0] = digitalRead(16);
  but[1] = digitalRead(39);
  but[2] = digitalRead(38);
  but[3] = digitalRead(37);
  
}

void readCamera() {
  
  if (Camera.available()) {

    String msg = Camera.readStringUntil('#');
    Camera.clear();

    //Serial.println(msg);
    //Bluetooth.println(msg);

    bool XorY = false;
    int counter = 0;

    int xCam = 0;
    int yCam = 0;

    for (int i = msg.length() - 1; i > -1; i--) {
      
      if (msg[i] == ' ') {
        XorY = true;
        counter = 0;
      } else {
        if (XorY) {
          xCam += (int(msg[i]) - 48) * pow10(counter);
        } else {
          yCam += (int(msg[i]) - 48) * pow10(counter);
        }
        counter++;
      }
    }

    ballX = xCam;
    ballY = yCam;

  }

 /* Bluetooth.print(ballX);
  Bluetooth.print(" ");
  Bluetooth.println(ballY);*/

}