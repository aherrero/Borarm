#include <Arduino.h>
#include <Servo.h>
#include <Wire.h>

Servo servoBase;
Servo servoShoulder;
Servo servoElbow;
Servo servoGripper;

int analogPotPin = 0;     // potentiometer wiper (middle terminal) connected to analog pin 3
                       // outside leads to ground and +5V

// Wiichuck Calibration
#define ZEROX 1024/2
#define ZEROY 530
#define ZEROZ 530

#define ZEROXX 1024/2
#define ZEROYY 1024/2

// Address I2C Wiichuck
#define WII_NUNCHUK_I2C_ADDRESS 0x52

// définition d'une variable counter
int counter;

// définition d'un tableau de données
uint8_t data[6];

void setup()
{
    // put your setup code here, to run once:
    pinMode(LED_BUILTIN, OUTPUT);

    Serial.begin(9600);              //  setup serial

    // Attach servo
    servoBase.attach(7);
    servoShoulder.attach(6);
    servoElbow.attach(5);
    servoGripper.attach(4);

    // Servo Init position
    servoBase.write(0);
    servoShoulder.write(0);
    servoElbow.write(0);
    servoGripper.write(0);

    // initialisation du nunchuck
    Wire.begin();

    Wire.beginTransmission(WII_NUNCHUK_I2C_ADDRESS);
    Wire.write(0xF0);
    Wire.write(0x55);
    Wire.endTransmission();

    Wire.beginTransmission(WII_NUNCHUK_I2C_ADDRESS);
    Wire.write(0xFB);
    Wire.write(0x00);
    Wire.endTransmission();
}

void loop()
{
    // put your main code here, to run repeatedly:

    // potentiometer
    float potValue = analogRead(analogPotPin);
    potValue = map(potValue, 0, 1023, 0, 180);
    //Serial.println(potValue);
    delay(100);

    //
    // for (int pos = 0; pos <= 180; pos++) {
    //   // in steps of 1 degree
    //   servoBase.write(pos);
    //   servoShoulder.write(pos);
    //   servoElbow.write(pos);
    //   servoGripper.write(pos);
    //   delay(15);
    // }
    // for (int pos = 180; pos > 0; pos--) {
    //   // in steps of 1 degree
    //   servoBase.write(pos);
    //   servoShoulder.write(pos);
    //   servoElbow.write(pos);
    //   servoGripper.write(pos);
    //   delay(15);
    // }

    // on demande 6 octets au nunchuck
    Wire.requestFrom(WII_NUNCHUK_I2C_ADDRESS, 6);

    counter = 0;
    // tant qu'il y a des données
    while(Wire.available())
    {
      // on récupère les données
      data[counter++] = Wire.read();
    }

    // on réinitialise le nunchuck pour la prochaine demande
    Wire.beginTransmission(WII_NUNCHUK_I2C_ADDRESS);
    Wire.write(0x00);
    Wire.endTransmission();

    if(counter >= 5)
    {
      // on extrait les données
      double joy_x_axis = ((data[0] << 2) + ((data[5] >> 2) & 0x03) - ZEROXX);
      double joy_y_axis = ((data[1] << 2) + ((data[5] >> 2) & 0x03) - ZEROYY);

      double accelX = ((data[2] << 2) + ((data[5] >> 2) & 0x03) - ZEROX);
      double accelY = ((data[3] << 2) + ((data[5] >> 4) & 0x03) - ZEROY);
      double accelZ = ((data[4] << 2) + ((data[5] >> 6) & 0x03) - ZEROZ);

      int z_button = 1;
      if ((data[5] >> 0) & 1)
          z_button = 0;

      int c_button = 1;
      if ((data[6] >> 1) & 1)
          c_button = 0;

      Serial.print(joy_x_axis); Serial.print("|");
      Serial.print(joy_y_axis); Serial.print("|");

      Serial.print(accelX); Serial.print("|");
      Serial.print(accelY); Serial.print("|");
      Serial.print(accelZ); Serial.print("|");

      Serial.print(z_button); Serial.print("|");
      Serial.print(c_button); Serial.print("|");

      Serial.println("");

      // données d'accélération de l'axe Y
      // on limite la valeur entre -180 et 180
      int value = constrain(joy_x_axis, -180, 180);
      // on mappe cette valeur pour le servomoteur soit entre 0 et 180
      value = map(value, -180, 180, 0, 180);
      // on écrit sur le servomoteur la valeur
      //servoBase.write(180-value);

      // données d'accélération de l'axe X
      value = constrain(joy_y_axis, -180, 180);
      value = map(value, -180, 180, 0, 180);
      //servoShoulder.write(180-value);

      // un petit delai pour pas saturer le servomoteur
      delay(100);
    }
}
