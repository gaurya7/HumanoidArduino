//Face Tracker using OpenCV and Arduino
//neck

#include<Servo.h>
#define ml 4
#define mr 5
Servo y, y1;//y1 

int x;
int width = 640, height = 480;  // total resolution of the video
int xpos = 90, ypos = 40, y1pos;
int motorspeed = 0;
int xspeed = 0;// initial positions of both Servos
void setup() {
//
  Serial.begin(115200);
  pinMode(ml, OUTPUT);
  pinMode(mr, OUTPUT);
  y.attach(3);
  y1.attach(6);
  // Serial.print(width);
  //Serial.print("\t");
  //Serial.println(height);  
  y.write(ypos);
  y1.write(y1pos);
}
const int angle = 2;   // degree of increment or decrement

void loop() {
  if (Serial.available() > 0)
  {
    int x_mid, y_mid, y1_mid;
    if (Serial.read() == 'X')
    {
      x_mid = Serial.parseInt();  // read center x-coordinate
      if (Serial.read() == 'Y')
        y_mid = Serial.parseInt();
        y1_mid = y_mid;// read center y-coordinate
    }
    /* adjust the servo within the squared region if the coordinates
        is outside it
    */
    if ((x_mid > width / 2 + 30)&&(x_mid > 0 && x_mid < width))
      xpos += angle;
     if ((x_mid < width / 2 - 30)&&(x_mid > 0 && x_mid < width))
      xpos -= angle;   
    if (y_mid < height / 2 + 30)
      {
        ypos -= angle;
        y1pos -= angle;
      }
      
    if (y_mid > height / 2 - 30)
      {
        ypos += angle;
        y1pos += angle;
      }


       if (x_mid > width / 2 + 30) {
        digitalWrite(ml, LOW);//H
        digitalWrite(mr, HIGH);//L
        delay(7);
        digitalWrite(ml, LOW);
        digitalWrite(mr, LOW);
        motorspeed = map(xpos, 320, 0, 0, 255);
      }
      else if(x_mid < width / 2 - 30) {
        digitalWrite(ml, HIGH);//L
        digitalWrite(mr, LOW);//H
        delay(7);
        digitalWrite(ml, LOW);
        digitalWrite(mr, LOW);
        motorspeed = map(xpos, 320, 1023, 0, 255);
      }
      else {
        motorspeed = 0;
        digitalWrite(ml, LOW);
        digitalWrite(mr, LOW);
      }
      if (motorspeed < 70) {
        motorspeed = 0;
      }

    // if the servo degree is outside its range//error handling code 
    if (xpos >= 180)//180
      xpos = 180;
    else if (xpos <= 0)
      xpos = 0;
    if (ypos >= 80)
      ypos = 80;
    else if (ypos <= 0)
      ypos = 0;
    if (y1pos  >= 80)
      y1pos = 80;
    else if (y1pos <= 0)
      y1pos = 0;

  
    y.write(ypos);
    y1.write(ypos);
  }
  else {
    digitalWrite(ml, LOW);
    digitalWrite(mr, LOW); 
 }
    // used for testing
    //Serial.print("\t");
    // Serial.print(x_mid);
    // Serial.print("\t");
    // Serial.println(y_mid);
  
}
