#include <Wire.h>

#define pwmR 3
#define pwmL 9

int front, left, right;
int rightSpeed = 150;
int leftSpeed = 150;
float target; float heading;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  compass = HMC5883L();
  setupHMC5883L();
  
  pinMode(pwmL, OUTPUT);
  pinMode(pwmR, OUTPUT);

  for(int i = 0; i < 100; i++){ target += getHeading(); }
  target /= 100;

  Serial.println(target);

}


void loop() {
  front = analogRead(A0); left = analogRead(A1); right = analogRead(A2);
  Serial.println(getHeading());

  delay(3000);
}


void moveForward() {
  rightSpeed += target - getAbsolute();
  leftSpeed -= target - getAbsolute();

  analogWrite(pwmL, leftSpeed);
  analogWrite(pwmR, rightSpeed);
}


void stop() {
  analogWrite(pwmL, 0);
  analogWrite(pwmR, 0);
}


void setupHMC5883L(){
  int error;
  error = compass.SetScale(1.3);
  if(error != 0) Serial.println(compass.GetErrorText(error));
  
  error = compass.SetMeasurementMode(Measurement_Continuous);
  if(error != 0) Serial.println(compass.GetErrorText(error));
}


float getHeading(){
  MagnetometerScaled scaled = compass.ReadScaledAxis();
  float heading = atan2(scaled.YAxis, scaled.XAxis);
  
  if(heading < 0) heading += 2*PI;
  if(heading > 2*PI) heading -= 2*PI;

  return heading * RAD_TO_DEG;
}


float getAbsolute(){
  getHeading();
}
