#include "MS5611.h"
#include <TinyMPU6050.h>
#include <Wire.h>

MPU6050 mpu (Wire);
MS5611 MS5611(0x77);

void setup() {
  Serial.begin(115200);
  // put your setup code here, to run once:
  Wire.begin();
  MS5611.begin();
  mpu.Initialize();
  mpu.Calibrate();
  Serial.println("P,T,Ax,Ay,Az,FGx,FGy,FGz,ms");

}

void loop() {
  // put your main code here, to run repeatedly:
  mpu.Execute();
  
  Serial.println(String(MS5611.getPressure() * 0.01, 2)+","+String(MS5611.getTemperature() * 0.01, 2)+","+String(mpu.GetAccX()- 0.08)+","+String(mpu.GetAccY())+","+String(mpu.GetAccZ())+","+String(mpu.GetAngX())+","+String(mpu.GetAngY())+","+String(mpu.GetAngZ())+","+String(millis()));
  int result=MS5611.read();
}
