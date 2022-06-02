//Face Tracker using OpenCV and Arduino.
//Ai-RON.
//this code run with python open cv code.
//for servo we use 5V power supply.
//for DC motor we use 12V power supply.
//this code run 4 servo and 1 DC motor in respective X and Y axis .
// 1 dc motor and 1 servo motor run on X-Axis. 
// 3 servos run on Y-Axis.
//in neck mechanisum part, there is 2 servos and 1 dc motor are run. 
//in this code 2 servos are run at same time in oppesite direction which is in neck (Y-Axis, Up-Down).
//1 dc run on X-axis (Left-Right) for neck .
//2 servo run respectively X and Y Axis for eye mechanisum (Up-Down , Left-Right).
//jaw is pending ...
//eye lash is pending...

#include<Servo.h>// servo lib
#define ml 4//Dc motor wire connection Red , here we define DC motor's both connection or declaretion for one DC motor 
#define mr 5//Dc motor wire connection Black, DC motor required two pin connections.
Servo y, y1, y2, e;// here we declare 4 servos. 

int x;// this veriable for dc motor 
int width = 640, height = 480;  // total resolution of the video
int xpos = 90, epos = 30, ypos = 20, y1pos = 20, y2pos; // initial positions of all Servos (as per our calculations)
int motorspeed = 0;
int xspeed = 0;
void setup() {
//
  Serial.begin(115200);//
  pinMode(ml, OUTPUT);
  pinMode(mr, OUTPUT);
  y.attach(3);// declared pin number which connect on arduino uno
  y1.attach(6);
  y2.attach(9);
  e.attach(10);
  // Serial.print(width);
  //Serial.print("\t");
  //Serial.println(height);  
  y.write(ypos); // read-write function
  y1.write(y1pos);
  y2.write(y2pos);
  e.write(epos);
}
const int angle = 2;   // degree of increment or decrement

void loop() {
  if (Serial.available() > 0)
  {
    int x_mid, e_mid, y_mid, y1_mid, y2_mid;// intinaliz all mid 
    if (Serial.read() == 'X')//logic for X-axis
    {
      x_mid = Serial.parseInt(); 
      e_mid = x_mid;// read center x-coordinate
      if (Serial.read() == 'Y')//logic for Y-axis
        y_mid = Serial.parseInt();
        y1_mid = y1_mid;//Serial.parseInt();//y_mid;
        y2_mid = y_mid;// read center y-coordinate
    }
    /* adjust the servo within the squared region if the coordinates
        is outside it
    */
    if ((x_mid > width / 2 + 30)&&(x_mid > 0 && x_mid < width))
      {
      xpos += angle;
      epos += angle;//
      }
     if ((x_mid < width / 2 - 30)&&(x_mid > 0 && x_mid < width))
      {
      xpos -= angle;
      epos -= angle;//
      }   
    if (y_mid < height / 2 + 30)
      {
        ypos -= angle;
        y1pos += angle;//-
        y2pos -= angle;
      }
      
    if (y_mid > height / 2 - 30)
      {
        ypos += angle;
        y1pos -= angle;//+
        y2pos += angle;
      }

//logic for DC motor
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
    if (epos >= 60)
      epos = 60;
    else if (epos <= 0)
      epos = 0;    
    if (ypos >= 40)
      ypos = 40;
    else if (ypos <= 0)
      ypos = 0;
    if (y1pos  >= 20)//40
      y1pos = 20;
    else if (y1pos <= 0)
      y1pos = 0;
    if (y2pos  >= 40)
      y2pos = 40;
    else if (y2pos <= 0)
      y2pos = 0;

    e.write(epos);
    y.write(ypos);
    y1.write(y1pos);//y
    y2.write(ypos);//y
  }
  else {
    digitalWrite(ml, LOW);//using this we can stop DC motor ,control.
    digitalWrite(mr, LOW); 
 }
    // used for testing
    //Serial.print("\t");
    // Serial.print(x_mid);
    // Serial.print("\t");
    // Serial.println(y_mid);
  
}
