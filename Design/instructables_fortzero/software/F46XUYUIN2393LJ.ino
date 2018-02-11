void recording() {



  int hold = 300;

  recState = digitalRead(recPin);
  runState = digitalRead(runPin);
  if (recState != recLast) {

    if (recState == HIGH) {
      recCounter++;
//      Serial.println(recCounter % 3);
      delay(200);
      
    if (recCounter % 3 == 0) {
      digitalWrite(ledPin1, LOW);
      digitalWrite(ledPin2, LOW);
      Serial.println("Clear");
      
    }

    if (recCounter % 3 == 1) { // Here we write cords for pick place in array.
      pick[0][0] = valBase;
      pick[0][1] = valShoulder;
      pick[0][2] = valElbow;
      pick[0][3] = valPinch;
      Serial.println("Pick place done");
      digitalWrite(ledPin1, HIGH);
      
    }

    if (recCounter % 3 == 2) { // Here we write cords for deposit place in array.
      dep[0][0] = valBase;
      dep[0][1] = valShoulder;
      dep[0][2] = valElbow;
      dep[0][3] = valPinch;
      Serial.println("Deposit place done");
      digitalWrite(ledPin2, HIGH);
    }
   }
  }
  recLast = recState;

  if (runState != runLast) {


    if (runState == HIGH) {
      runCounter++;
//      Serial.println(runCounter % 2);
      delay(200);
    }

    if (runCounter % 2 == 1) {
      Serial.println("Automation Starting");

      while (runCounter % 2 == 1) { 
        runState = digitalRead(runPin);
        if (runState == HIGH) {
          runCounter++;
//          Serial.println(runCounter % 2);
          if (runCounter % 2 == 0) {
            break;
            }
        }


        Home();
        pinch.write(130);
        delay(hold);

        base.write(pick[0][0]);
        delay(hold);
        elbow.write(pick[0][2]);
        delay(hold);
        shoulder.write(pick[0][1]);
        delay(hold);
        pinch.write(pick[0][3]);
        delay(hold);

        Home();

        base.write(dep[0][0]);
        delay(hold);
        elbow.write(dep[0][2]);
        delay(hold);
        shoulder.write(dep[0][1]);
        delay(hold);
        pinch.write(dep[0][3]);
        delay(hold);


      }
      Serial.println("Automation Stopped");
      Home();
        pinch.write(100);
        delay(hold);
    }
  }

  runLast = runState;






  

}
