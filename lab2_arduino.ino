#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

int xPrev = -1;
int yPrev = -1;
int buzz_status = HIGH;
int incomingByte = 0;
int buzzPin = 12;

void setup() {
  Serial.begin(9600);
  pinMode(9,INPUT);     // SW pin
  digitalWrite(9,HIGH);

  Serial.begin(115200);
  // Initialize MPU6050
  Serial.println("Initialize MPU6050");
  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }
  // Check settings
  checkSettings();
}

void checkSettings()
{
   
  Serial.println();
  
}

void loop() {
Vector rawGyro = mpu.readRawGyro();
  Vector normGyro = mpu.readNormalizeGyro();

  Serial.print(" Xraw = ");
  Serial.print(rawGyro.XAxis);
  Serial.print(" Yraw = ");
  Serial.print(rawGyro.YAxis);
  Serial.print(" Zraw = ");
  Serial.println(rawGyro.ZAxis);

  Serial.print(" Xnorm = ");
  Serial.print(normGyro.XAxis);
  Serial.print(" Ynorm = ");
  Serial.print(normGyro.YAxis);
  Serial.print(" Znorm = ");
  Serial.println(normGyro.ZAxis);
  
  delay(10);
  
  int z=0,xpos=0,ypos=0;
  int x=0, y=0;
  x=analogRead(A0);
  y=analogRead(A1);

  

  pinMode(buzzPin, OUTPUT);
  
  digitalWrite(buzzPin, LOW);
     
  buzz_status = LOW;

  int sensitivityGyro = 80;
  if(rawGyro.XAxis>=5)                     // when moved forward 
  xpos=map(x,5,1023,0,sensitivityGyro); 
  if(rawGyro.XAxis<=-5)                   // when moved backwards
  xpos=map(x,-5,0,0,-sensitivityGyro);
  if(rawGyro.YAxis>=5)                    // when moved right
  ypos=map(y,5,1023,0,sensitivityGyro);
  if(rawGyro.YAxis<=-5)                  // when moved left
  ypos=map(y,-5,0,0,-sensitivityGyro); 

  int sensitivity=80;    
  if(x>=550)                     // when moved up 
  xpos=map(x,550,1023,0,sensitivity); 
  if(x<=450)                   // when moved down
  xpos=map(x,450,0,0,-sensitivity);
  if(y>=550)                    // when moved right
  ypos=map(y,550,1023,0,sensitivity);
  if(y<=450)                  // when moved left
  ypos=map(y,450,0,0,-sensitivity); 
  
  
if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();
    //Serial.println(incomingByte);
    
    if(incomingByte == 'E') {
      // buzz
      buzz_status = (buzz_status == LOW)? HIGH : LOW;
      digitalWrite(buzzPin, buzz_status);
    }
  }


if (xPrev == xpos && yPrev == ypos)
{ }
else {
  Serial.print(xpos);    // print the data and separating by ":"
  Serial.print(" ");
  Serial.println(ypos);
  xPrev = xpos;
  yPrev = ypos;
  }
 


  delay(75);         // for normal operation
}
