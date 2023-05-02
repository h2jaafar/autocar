#include <Arduino.h>
int In1 = 8;
int In2 = 7;
int In3 = 6;
int In4 = 4;
int EnA = 9;
int EnB = 5;

#define channumber 10 // Number of Radio Channels
int channel[channumber]; //read Channel values
int PPMin =10; // PPM pin
float throttle_val = 0;
float steering_val = 0;

/**
Notes:
CH1 = Right stick Left right
CH2 = Right stick up
CH3 = Throttle
CH4 = Steering
*/


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // motor cotrols 
  pinMode(EnA, OUTPUT);
  pinMode(EnB, OUTPUT);
  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);
  pinMode(In3, OUTPUT);
  pinMode(In4, OUTPUT);

  // turn off motors
  digitalWrite(In1, LOW);
  digitalWrite(In2, LOW);
  digitalWrite(In3, LOW);
  digitalWrite(In4, LOW);

  // reciever
  pinMode(PPMin, INPUT); // Pin 10 as input
}

void controller()   //run both motors in the same direction
{
  int motor_speed_A = 0;
  int motor_speed_B = 0;

  if(throttle_val > 10)
  {
    // move forward
    digitalWrite(In1, LOW);
    digitalWrite(In2, HIGH);
    digitalWrite(In3, LOW);
    digitalWrite(In4, HIGH);
    motor_speed_A = throttle_val;
    motor_speed_B = throttle_val;
  }
  else if(throttle_val < -10)
  {
    // move backwards
    digitalWrite(In1, LOW);
    digitalWrite(In2, HIGH);
    digitalWrite(In3, LOW);
    digitalWrite(In4, HIGH);
    motor_speed_A = -1*throttle_val;
    motor_speed_B = -1*throttle_val;
  }
  else {
    motor_speed_A = 0;
    motor_speed_B = 0;
  }

  if(steering_val < -10)
  {
    // steer left
    motor_speed_A = motor_speed_A + -1*steering_val;
    motor_speed_B = motor_speed_B - -1*steering_val;
    if(motor_speed_A > 255){motor_speed_A = 255;}
    if(motor_speed_B < 0){motor_speed_B = 0;}

  }
  else if(steering_val > 10)
  {
    // steer right
    motor_speed_A = motor_speed_A - steering_val;
    motor_speed_B = motor_speed_B + steering_val;
    if(motor_speed_A < 0){motor_speed_A = 0;}
    if(motor_speed_B > 255){motor_speed_B = 255;}

  }
  Serial.print("throttle: ");
  Serial.print(throttle_val);
  Serial.print("\t");
  Serial.print("steering ");
  Serial.print(steering_val);
  Serial.print("\n");


  Serial.print("A: ");
  Serial.print(motor_speed_A);
  Serial.print("\t");
  Serial.print("B ");
  Serial.print(motor_speed_B);
  Serial.print("\n");

  analogWrite(EnA, motor_speed_A);
  analogWrite(EnB, motor_speed_B);
  delay(100);
  // now turn off motors
  // digitalWrite(In1, LOW);
  // digitalWrite(In2, LOW);  
  // digitalWrite(In3, LOW);
  // digitalWrite(In4, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:

  if(pulseIn(PPMin , HIGH) > 4000) //If pulse > 4 miliseconds, continues
  {
    for(int i = 1; i <= channumber; i++) //Read the pulses of the remainig channels
    {
    channel[i-1]=pulseIn(PPMin, HIGH);
    }
  
    // for(int i = 1; i <= 4; i++) //Prints all the values readed
    // {
    //   // Serial.print("CH"); //Channel
    //   // Serial.print(i); //Channel number
    //   // Serial.print(": "); 
    //   // Serial.println(channel[i-1]); //Print the value
    // }
    // // delay(200);//Give time to print values.
    // controls part here
    throttle_val = map(channel[2-1], 600, 1600,-255, 255);
    steering_val = map(channel[1-1], 600, 1600,-255, 255);
    controller();
    
  }

}
