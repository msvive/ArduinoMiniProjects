// The Mustang Barrier by Mona Safari / Nov 2022
// MDes in Digital Future, OCAD University
// Creation & Computation Course, Nick Pucket
// - - - - - - - - - - - - - - - - - - - - - - - - -
// For this sketch, I used a basic circuit, an ultrasonic sensor, a micro servo, a bread board and some jumper wires. 
// When a vehicle arrives, the ultrasonic sensor will be activated to raise/lower the gate according to the distance between objects. 
// When an obstacle is detected by the sensor, the Arduino board will send a command to the servo to raise the shaft by degrees. 
// After a few delays, the shaft will return to its original position. I also used a USB power supply, but battery power would also work.


#include <Servo.h>   //servo library
Servo servo;     
int trigPin = 2;    
int echoPin = 3;   
int servoPin = 9; 

long duration, dist, average;   
long aver[3];   //array for average


void setup() {       
    servo.attach(servoPin);  
    pinMode(trigPin, OUTPUT);  
    pinMode(echoPin, INPUT);  
    servo.write(0);         //close cap on power on
    delay(1000);
    servo.detach();
} 

void measure() {  
digitalWrite(trigPin, LOW);
delayMicroseconds(5);
digitalWrite(trigPin, HIGH);
delayMicroseconds(15);
digitalWrite(trigPin, LOW);
pinMode(echoPin, INPUT);
duration = pulseIn(echoPin, HIGH);
dist = (duration/2) / 29.1;    //obtain distance
}
void loop() { 
  for (int i=0;i<=2;i++) {   //average distance
    measure();               
   aver[i]=dist;            
    delay(50);              //delay between measurements
  }
 dist=(aver[0]+aver[1]+aver[2])/3;    //average distance by 3 measurements

if ( dist<15 ) {
 //if hand on the distance 10...15 cm
 servo.attach(servoPin);
  delay(1);
 servo.write(150);  
 delay(3000);       //wait 5 seconds for the Mustang! 
 servo.write(0);    
 delay(1000);
 servo.detach();      
}
}

