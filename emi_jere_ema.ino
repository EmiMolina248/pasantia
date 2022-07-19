/*
 Controlling a servo position using a potentiometer (variable resistor)
 by Michal Rinott <http://people.interaction-ivrea.it/m.rinott>

 modified on 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Knob
*/

//#include <Servo.h>

//Servo myservo;  // create servo object to control a servo
int sensorValue, servoValue,cont;
int arraySensor[10];

int promValues(int b){
  int sum  = 0;
  for(int i= 1;i<10;i++){
   arraySensor[i-1] = arraySensor[i]; 
   sum += arraySensor[i-1];
  }
  arraySensor[9] = b;
  sum += b ; 
  return sum/10;
}
String arrayMessage(){
  String mess = "{";
  for(int i = 0; i<10;i++){
    mess += String(arraySensor[i])+ ", ";
    } 
    mess += "}";
    return mess;
  } 
void setup() {
  //myservo.attach(6);  // attaches the servo on pin 9 to the servo object
  Serial.begin(9600);
}

void loop() {
   sensorValue = analogRead(A3);
   //Serial.println(sensorValue);
  cont = promValues(sensorValue);
  Serial.println(String(sensorValue) +","+ String(cont));
  delay(100);        // delay in between reads for stability
  servoValue = map(sensorValue, 100, 800, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
 // myservo.write(servoValue);                  // sets the servo position according to the scaled value
  //delay(15);                           // waits for the servo to get there
}
