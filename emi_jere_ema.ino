/*
 Controlling a servo position using a potentiometer (variable resistor)
 by Michal Rinott <http://people.interaction-ivrea.it/m.rinott>

 modified on 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Knob
*/

//#include <Servo.h>

//Servo myservo;  // create servo object to control a servo
int sensorValue,regulaUmbral, servoValue,cont;
int optionUmbral = 2;
int led;
const int largoArray = 100; // variable que contiene el largo del array del sensor
int arraySensor[largoArray]; 
//int arrayRegulador[largoArray];



int promValues(int b){
  int sum  = 0;
  for(int i= 1;i<largoArray ;i++){
   arraySensor[i-1] = arraySensor[i]; //funcion para sacar el promedio de los valores del sensor guardados en el array
   sum += arraySensor[i-1];
  }
  arraySensor[9] = b;
  sum += b ; 
  return sum/largoArray ;
}



int getUmbral(int p,int o, int um){
  switch(o){
  case 0:
    return 700;
   break; 
  case 1:
    return 200 + um;
    break;
  
  case 2:
     return p*2;
     break;
  }
}

String arrayMessage(){
  String mess = "{";
  for(int i = 0; i<largoArray ;i++){      // funcion para mostrar los elementos del array
    mess += String(arraySensor[i])+ ", ";
  } 
    mess += "}";
    return mess;
  } 
void setup() {
   led = 8;
  pinMode(led, OUTPUT);
  //myservo.attach(6);  // attaches the servo on pin 9 to the servo object
  Serial.begin(9600);
}

void loop() {
  regulaUmbral = analogRead(A2);
  sensorValue = analogRead(A3);
  cont = promValues(sensorValue);
  Serial.println(String(sensorValue) +","+ String(cont)+ ", "+ String(getUmbral(cont,optionUmbral,regulaUmbral)));
  if(sensorValue > getUmbral(cont, optionUmbral,regulaUmbral)){
    digitalWrite(led, HIGH);
    }
    else{
      digitalWrite(led, LOW);
      }
  delay(100);        // delay in between reads for stability
  servoValue = map(sensorValue, 100, 800, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
 // myservo.write(servoValue);                  // sets the servo position according to the scaled value
  //delay(15);                           // waits for the servo to get there
}
