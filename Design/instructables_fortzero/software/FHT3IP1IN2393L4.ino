void Cords() {


  int hold = 300; // Time between each servo move
  int inByte;

  if (Serial.available() > 0) {
    inByte = Serial.read();


    switch (inByte) {

      case 'q':

        Serial.println("Q selected");
        Pick();
        Home();
        base.write(90);
        delay(hold);
        elbow.write(77);
        delay(hold);
        shoulder.write(130);
        delay(hold);
        pinch.write(130);
        delay(hold);
        Home();

        break;

      case 'w':

        Serial.println("W selected");
        Pick();
        Home();
        base.write(79);
        delay(hold);
        elbow.write(79);
        delay(hold);
        shoulder.write(130);
        delay(hold);
        pinch.write(130);
        delay(hold);
        Home();

        break;

      case 'e':

        Serial.println("E selected");
        Pick();
        Home();
        base.write(69);
        delay(hold);
        elbow.write(75);
        delay(hold);
        shoulder.write(132);
        delay(hold);
        pinch.write(130);
        delay(hold);
        Home();

        break;

      case 'a':

        Serial.println("A selected");
        Pick();
        Home();
        base.write(92);
        delay(hold);
        elbow.write(102);
        delay(hold);
        shoulder.write(116);
        delay(hold);
        pinch.write(130);
        delay(hold);
        Home();

        break;

      case 's':

        Serial.println("S selected");
        Pick();
        Home();
        base.write(78);
        delay(hold);
        elbow.write(103);
        delay(hold);
        shoulder.write(116);
        delay(hold);
        pinch.write(130);
        delay(hold);
        Home();

        break;

      case 'd':

        Serial.println("D selected");
        Pick();
        Home();
        base.write(65);
        delay(hold);
        elbow.write(101);
        delay(hold);
        shoulder.write(116);
        delay(hold);
        pinch.write(130);
        delay(hold);
        Home();

        break;

      case 'z':

        Serial.println("Z selected");
        Pick();
        Home();
        base.write(95);
        delay(hold);
        elbow.write(126);
        delay(hold);
        shoulder.write(105);
        delay(hold);
        pinch.write(130);
        delay(hold);
        Home();

        break;

        case 'x':

        Serial.println("X selected");
        Pick();
        Home();
        base.write(77);
        delay(hold);
        elbow.write(128);
        delay(hold);
        shoulder.write(105);
        delay(hold);
        pinch.write(130);
        delay(hold);
        Home();

        break;

        case 'c':

        Serial.println("C selected");
        Pick();
        Home();
        base.write(59);
        delay(hold);
        elbow.write(123);
        delay(hold);
        shoulder.write(106);
        delay(hold);
        pinch.write(130);
        delay(hold);
        Home();

        break;

    }
  }

}
