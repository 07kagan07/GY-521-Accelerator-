#include<Wire.h>
#include <Ultrasonic.h>
//60ms 16,6
//Ultrasonic ultrasonic(5, 4);
Ultrasonic ultrasonic2(14, 12);
const int MPU=0x68; 
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
float velocity = 0.0;
float displacement = 0.0 ;

float delta_t = 1;
float tmp = ultrasonic2.read();
void setup(){
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B); 
  Wire.write(0);    
  Wire.endTransmission(true);
  Serial.begin(9600);
}
  
void loop(){
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,12,true);  
  AcX=Wire.read()<<8|Wire.read();    
  AcY=Wire.read()<<8|Wire.read();  
  AcZ=Wire.read()<<8|Wire.read();  
  GyX=Wire.read()<<8|Wire.read();  
  GyY=Wire.read()<<8|Wire.read();  
  GyZ=Wire.read()<<8|Wire.read();  



  //int s1 = ultrasonic.read();
  float s2 = ultrasonic2.read();
  
  int accelerometer =update(AcX/16384*981);
  float sonar=sonarupdate(s2);
  

  //Serial.print("Accelerometer: ");
 // Serial.print("X = "); Serial.print(AcX);
 // Serial.print(" | Y = "); Serial.print(AcY);
 // Serial.print(" | Z = "); Serial.println(AcZ); 
  
  //Serial.print("Gyroscope: ");
 // Serial.print("X = "); Serial.print(GyX);
 // Serial.print(" | Y = "); Serial.print(GyY);
 // Serial.print(" | Z = "); Serial.println(GyZ);
 // Serial.println(" ");
  
//unsigned long start = micros();
  Serial.print(accelerometer);
  Serial.print("\t");
  Serial.println(sonar);
//unsigned long end = micros();
//unsigned long delta = end - start;
//Serial.print("Geçen zmn");
//Serial.println(delta);
//0.25cm/sec
  
  delay(1000);


}

 int update(int16_t AcX) {
   float acceleration = AcX/32768*16*9.81 ;
   velocity = acceleration * delta_t ;
   return displacement = velocity * delta_t ;
  }

  
  int sonarupdate(float x){
     if (tmp != x) {
      float n = x - tmp;
      tmp = x;
      return n;
     }
     else return 0;
    }
