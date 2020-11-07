int xPrev = -1;
int yPrev = -1;
int buzz_status = HIGH;
int incomingByte = 0;
int buzzPin = 12;

void setup() {
  Serial.begin(9600);
  pinMode(9,INPUT);     // SW pin
  digitalWrite(9,HIGH);
  
}

void loop() {
  int z=0,xpos=0,ypos=0;
  int x=0, y=0;
  x=analogRead(A0);
  y=analogRead(A1);

  pinMode(buzzPin, OUTPUT);
  
  digitalWrite(buzzPin, LOW);
     
  buzz_status = LOW;
  

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
