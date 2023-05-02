#include <Arduino.h>
int In1 = 6;
int In2 = 5;
int In3 = 4;
int In4 = 3;
int EnA = 7;
int EnB = 2;
int ppm_signal_pin = 10;
unsigned long int a,b,c;
int x[15],ch1[15],ch[7],i;

void  read_me()  {
 //this code reads value from RC reciever from PPM pin (Pin 2 or  3)
 //this code gives channel values from 0-1000 values 
 //    -: ABHILASH  :-    //
a=micros(); //store time value a when pin value falling
c=a-b;      //calculating  time inbetween two peaks
b=a;        // 
x[i]=c;     //storing 15 value in  array
i=i+1;       if(i==15){for(int j=0;j<15;j++) {ch1[j]=x[j];}
             i=0;}}//copy  store all values from temporary array another array after 15 reading  
void read_rc(){
int  i,j,k=0;
  for(k=14;k>-1;k--){if(ch1[k]>10000){j=k;}}  //detecting separation  space 10000us in that another array                     
  for(i=1;i<=6;i++){ch[i]=(ch1[i+j]-1000);}}     //assign 6 channel values after separation space



void setup() {
  // put your setup code here, to run once:
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

  Serial.begin(9600);
  pinMode(ppm_signal_pin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), read_me,  FALLING);

}

void directionControl() {
	// Set motors to maximum speed
	// For PWM maximum possible values are 0 to 255
	analogWrite(EnA, 255);
	analogWrite(EnB, 255);

	// Turn on motor A & B
	digitalWrite(In1, HIGH);
	digitalWrite(In2, LOW);
	digitalWrite(In3, HIGH);
	digitalWrite(In4, LOW);
	delay(2000);
	
	// Now change motor directions
	digitalWrite(In1, LOW);
	digitalWrite(In2, HIGH);
	digitalWrite(In3, LOW);
	digitalWrite(In4, HIGH);
	delay(2000);
	
	// Turn off motors
	digitalWrite(In1, LOW);
	digitalWrite(In2, LOW);
	digitalWrite(In3, LOW);
	digitalWrite(In4, LOW);
}


void loop() {
  // put your main code here, to run repeatedly:
  read_rc();
  Serial.print("--------\n");
  Serial.print(ch[1]);
  Serial.print("\n");
  Serial.print(ch[2]);
  Serial.print("\n");
  Serial.print(ch[3]);
  Serial.print("\n");
  Serial.print(ch[4]);
  Serial.print("\n");
  Serial.print(ch[5]);
  Serial.print("\n");
  Serial.print(ch[6]);
  Serial.print("\n");
  // directionControl();
	delay(500);
}