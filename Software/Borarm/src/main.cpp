#include <Arduino.h>
#include <Servo.h>
#include <Wire.h>

Servo servoBase;
Servo servoShoulder;
Servo servoElbow;
Servo servoGripper;

int servoBasePosition = 90;
int servoShoulderPosition = 120;
int servoElbowPosition = 60;
int servoGipperPosition = 90;

int analogPotPin = 0;     // potentiometer wiper (middle terminal) connected to analog pin 3
                       // outside leads to ground and +5V

int gyroCounter = 0;
int oldAccelY = 0;

// Wiichuck Calibration
#define ZEROX 1024/2
#define ZEROY 400
#define ZEROZ 530

#define ZEROXX 512
#define ZEROYY 515

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
    servoBase.write(servoBasePosition);
    servoShoulder.write(servoShoulderPosition);
    servoElbow.write(servoElbowPosition);
    // servoGripper.write(0);

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

    servoBase.write(servoBasePosition);

    // potentiometer
    float potValue = analogRead(analogPotPin);
    potValue = map(potValue, 0, 1023, 0, 180);
    //Serial.println(potValue);

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
      // Get data
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

      // Mapping Data
      int x_value = map(joy_x_axis, -512, 512, -100, 100);
      int y_value = map(joy_y_axis, -512, 512, -100, 100);

      int accelY_value = map(accelY, -300, 150, 0, 90);

      if(x_value > -50 && x_value < 50)
      {
        // Nothing to do
      }
      else if(x_value < 50)
      {
        if(servoBasePosition <= 180)
          servoBasePosition += 1;
      }
      else if(x_value > 50)
      {
        if(servoBasePosition >= 0)
          servoBasePosition -= 1;
      }

      servoBase.write(servoBasePosition);


      //Serial.println(servoShoulderPosition); //-180

      if(y_value > -50 && y_value < 50)
      {
        // Nothing to do
      }
      else if(y_value < 50)
      {
        if(servoShoulderPosition <= 180)
          servoShoulderPosition += 1;
      }
      else if(y_value > 50)
      {
        if(servoShoulderPosition >= 70)
          servoShoulderPosition -= 1;
      }

      servoShoulder.write(servoShoulderPosition);

      //Elbow
      // if(accelY_value > -50 && accelY_value < 50)
      // {
      //   // Nothing to do
      // }
      // else if(accelY_value < 30)
      // {
      //   if(servoElbowPosition <= 180)
      //     servoElbowPosition += 1;
      // }
      // else if(accelY_value > 30)
      // {
      //   if(servoElbowPosition >= 0)
      //     servoElbowPosition -= 1;
      // }

      gyroCounter++;
      if(gyroCounter > 5)
      {
        servoElbow.write(accelY_value);
        gyroCounter = 0;
      }


      if(z_button == 1)
      {
        Serial.print("Base: ");
        Serial.print(servoBase.read());
        Serial.print(", Shoulder: ");
        Serial.print(servoShoulder.read());
        Serial.print(", Elbow: ");
        Serial.print(servoElbow.read());
        Serial.print(", Gripper: ");
        Serial.print(servoGripper.read());
        Serial.println("-------------------");

        delay(500);
      }


      // un petit delai pour pas saturer le servomoteur
      delay(10);
    }
}
